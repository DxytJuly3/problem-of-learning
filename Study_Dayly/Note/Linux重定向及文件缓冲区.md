Linux中, 使用系统接口打开文件时, 系统会为打开的文件在此进程中分配fd, 而且是按照数组下标的顺序进行分配的

那么如果在打开新的文件之前, 有文件关闭了呢？再打开新的文件, 此文件的fd会分配什么呢？

# 文件描述符的分配规则

一般情况下, 进程会默认先打开至少三个文件：标准输入、标准输出、标准错误, 并分配fd为0、1、2

也就是说, 当进程使用open()打开磁盘文件时, 会从3开始分配fd.

那么如果在使用open()打开文件之前, 先关闭了0、1、2的描述的某个文件, 那么打开的文件会怎么分配fd呢？

```c
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
	umask(0);
	close(0);		// 什么都不干, 先关闭fd=0的文件
	
	int fd = open("new_log.txt", O_WRONLY | O_CREAT | O_TRUNC, 0666);		//以清空只写方式打开文件, 若文件不存在则创建文件
	if(fd < 0) {
		perror("open");
	}

	printf("打开文件的fd为: %d\n", fd);

	close(fd);

	return 0;
}
```

执行这段代码的结果是：

<img src="https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/image-20230317211153325.png" alt="image-20230317211153325" style="zoom:80%;" />

可以看到, 新打开的文件分配的fd变成了`0`. 如果我们关闭0、2文件, 再打开两个文件, 新打开文件的fd会怎么分配呢？

<img src="https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/image-20230317211753825.png" alt="image-20230317211753825" style="zoom:80%;" />

这意味着什么？这其实意味着, `打开文件分配fd的规则其实是, 从头遍历fd_array[]数组, 将没有使用的最小下标分配给新打开的文件`

# 重定向



## 理解重定向

上面的测试中, 将fd = 0 和 2的文件关闭了, 并且打开的新文件的fd会被分配为0和2 

那么也就是说, 如果我们把fd=1的文件关闭, 新打开文件的fd也会被分配为1

而我们知道, fd = 1是进程默认打开的标准输出, 对应着C语言中的stdout指针, stdout又被称为标准输出流, 使用fprint()可以向标准输出流写入内容, 从而可以将写入的内容打印在屏幕上. 

> ```c
> #include <stdio.h>
> #include <sys/types.h>
> #include <sys/stat.h>
> #include <fcntl.h>
> #include <unistd.h>
> 
> int main() {
> 	umask(0);
> 	close(0);
> 	
> 	int fd = open("new_log.txt", O_WRONLY | O_CREAT | O_TRUNC, 0666);		//以清空只写方式打开文件, 若文件不存在则创建文件
> 	if(fd < 0) {
> 		perror("open");
> 	}
> 	fprintf(stdout, "打开文件成功, fd: %d\n", fd);
> 
> 	close(fd);
> 
> 	return 0;
> }
> ```
>
> <img src="https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/image-20230317214202374.png" alt="image-20230317214202374" style="zoom:80%;" />

那么, 如果我们关闭fd=1的文件, 再打开一个新的文件, 并使用C语言文件操作向stdout写入内容, 那么会发生什么呢？

```c
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
	umask(0);
	close(1);		// 什么都不干, 先关闭fd=1的文件
	
	int fd = open("new_log.txt", O_WRONLY | O_CREAT | O_TRUNC, 0666);		//以清空只写方式打开文件, 若文件不存在则创建文件
	if(fd < 0) {
		perror("open");
	}
	fprintf(stdout, "打开文件成功, fd: %d\n", fd);
	fflush(stdout); 		// 刷新文件缓冲区操作

	close(fd);

	return 0;
}
```

<img src="https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/image-20230317214441303.png" alt="image-20230317214441303" style="zoom:80%;" />

> 关闭fd=1, fprintf()之后, 必须要手动刷新文件缓冲区, 不过暂时不做解释
>
> 本文章后面详析介绍文件缓冲区

代码的执行结果并没有在屏幕中输出任何信息. 那信息打印到哪里了呢？

<img src="https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/image-20230317214727485.png" alt="image-20230317214727485" style="zoom:80%;" />

此时当你查看刚刚打开文件的内容, 会发现, `原来应该打印到标准输出流的信息 打印到了刚刚打开的文件中`

`这是否就是重定向？`

是的, 这就是重定向. 

我们关闭了原来的fd=1文件(标准输出), 然后打开了一个新的文件分配了fd=1, 此时再向fd=1的文件中写入数据, 其实并没有向标准输出写入信息, 而是向指定文件写入了信息. 这其实就是输出重定向

整个过程可以用这个图表示：

<img src="https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/image-20230317221950902.png" alt="image-20230317221950902" style="zoom:80%;" />

我们把fd=1描述标准输出改为了描述一个指定文件, 这可以被称为重定向

那么重定向究竟是什么？

其实, **`Linux系统的上层只认0、1、2、3等这样的fd值, 我们在OS内部通过一定的方式 调整 数组特定下标的指向, 这样的操作就是重定向`**

## 如何重定向

上面再介绍重定向的概念时, 其实是通过关闭文件来实现重定向. 难道重定向都需要手动关闭文件, 然后再打开文件来实现吗？

其实不是的. 重定向归根结底是修改了系统内核中的数据来实现的, 既然是修改系统内核数据, 那么其实只有操作系统有权限. 那么对于上层来说, 想要实现重定向, 操作系统就一定会提供接口：

<img src="https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/image-20230317233430849.png" alt="image-20230317233430849" style="zoom:80%;" />

操作系统提供了几个重定向的接口, 不过在本篇文章中只介绍`dup2()`

```c
int dup2(int oldfd, int newfd);
```

man手册中, 关于此系统接口的描述是：`复制一个文件描述符, 将 newfd 变为 oldfd 的复制`

这是什么意思？

dup2()使用时需要传入两个参数, `oldfd` 和 `newfd`. 并且 会将newfd变为oldfd的复制, 也就是说`dup2()操作的是两个已经打开的文件`

dup2()是系统为重定向提供的接口, 也就是说 `dup2()会将一个fd描述的文件重定向为另一个文件`

那么 newfd 和 oldfd, 哪个是重定向之后的文件, 哪个又是重定向之前的文件呢？

读dup2()的描述其实可以了解到, `dup2()其实会将 newfd 变为 oldfd`, 也就是说执行过dup2()之后, 其实`进程中已经不在维护原来的newfd, newfd和oldfd 只剩了oldfd`. 从这个结果可以看出来, `oldfd其实是重定向之后的文件, 而newfd是被重定向掉的文件`

**`即, dup2(oldfd, newfd); 是将 newfd位置的内容变成了oldfd位置的内容.`**

再用 将stdout重定向到了指定文件 来举例就是：

<img src="https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/image-20230318000027867.png" alt="image-20230318000027867" style="zoom:80%;" />

### dup2()实现输出、追加重定向

上面介绍了dup2()的作用和用法, 那么就可以使用此系统接口实现重定向

先来实现一下输出和追加重定向：

```c
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main() {
	umask(0);
	
	int fd = open("new_log.txt", O_WRONLY | O_CREAT | O_TRUNC, 0666);		//以清空只写方式打开文件, 若文件不存在则创建文件
	if(fd < 0) {
		perror("open");
	}

	dup2(fd, 1);		// 将标准输出重定向到只写打开文件, 实现输出重定向
	const char *buffer = "Hello world, hello July\n";
	write(stdout->_fileno, buffer, strlen(buffer));

	close(fd);

	return 0;
}
```

<img src="https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/image-20230318000914397.png" alt="image-20230318000914397" style="zoom:80%;" />

当, 以 追加并写入的方式打卡文件时, 就可以实现追加重定向：

```c
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main() {
	umask(0);
	
	int fd = open("new_log.txt", O_WRONLY | O_CREAT | O_APPEND, 0666);		//以清空只写方式打开文件, 若文件不存在则创建文件
	if(fd < 0) {
		perror("open");
	}

	dup2(fd, 1);		// 将标准输出重定向到只写打开文件, 实现输出重定向
	const char *buffer = "Hello world, hello July\n";
	write(stdout->_fileno, buffer, strlen(buffer));

	close(fd);

	return 0;
}
```

<img src="https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/image-20230318001111053.png" alt="image-20230318001111053" style="zoom:80%;" />

### dup2()实现输入重定向

将标准输出重定向到指定文件可以实现输出重定向

那么将标准输入重定向到指定文件, 是否就可以实现输入重定向呢？

```c
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main() {
	int fd = open("new_log.txt", O_RDONLY);		//以只读方式打开文件, 只读打开一般都是已存在的文件
	if(fd < 0) {
		perror("open");
	}

	dup2(fd, 0);	// 将标准输入重定向到只读方式打开的文件, 实现输入重定向
	char buffer[128];
	// 从stdin中获取数据到buffer中
	while(fgets(buffer, sizeof(buffer), stdin) != NULL) {
		printf("%s", buffer);
	}

	close(fd);

	return 0;
}
```

<img src="https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/image-20230318003004837.png" alt="image-20230318003004837" style="zoom:80%;" />

# 文件缓冲区

在学习C语言时, 可能就有人听说过文件缓冲区. 但是对其并没有一个正确的认识

下面就来介绍一下, Linux系统中的文件缓冲区

## 什么是文件缓冲区

简单的来讲, `文件缓冲区其实就是一块内存空间`

这块空间是用来, 存储 向系统内核中写入的数据 的. 

就向我们在使用printf(), 并且不刷新文件缓冲区时, 并不会直接将数据打印到屏幕上：

```c
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h> 

int main() {
	printf("Hello world");
	write(stdout->_fileno, "I am a process", strlen("I am a process"));

	sleep(3);

	return 0;
}
```

这段代码的执行结果是：

<img src="https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/printfBuffer.gif" alt="printfBuffer" style="zoom:80%;" />

可以看到, 明明在printf()之后的 write()语句先输出了. 

这就`可以说明文件缓冲区的存在, 并且只有在刷新文件缓冲区时, 文件缓冲区内的数据才会写入系统内核中`

## 为什么要存在文件缓冲区

首先, 文件缓冲区是存放 进程向操作系统内核写入的数据 的

就以向屏幕上输出信息为例：

1. 我们知道, 进程在等待硬件资源时是会进入`阻塞状态`的

	处于阻塞状态的进程, 无法执行其他代码, 只能等到阻塞结束

	而进程向屏幕输出信息时, 其实也是需要屏幕资源的

	如果此时屏幕资源已经被占用满了, 并且没有文件缓冲区的存在, 输出语句执行就会进入阻塞状态等待屏幕资源

	而如果有文件缓冲区的存在, 即使屏幕资源已经被占满了, 输出语句执行之后, 会将需要输出的信息存入文件缓冲区中, 然后进程继续执行其他代码. 等到合适的时候, 再刷新文件缓冲区 将需要打印的信息打印到屏幕上

	这样看, 其实`文件缓冲区的存在, 在一定程度上节省了进程的时间`

2. 如果没有文件缓冲区的存在, 我们打印信息就会立马在屏幕上打印出来.

	这样看起来似乎不错, 但其实会加重操作系统的负担.

	如果没有限制的、死循环地向屏幕上打印信息, 那么数据就会在操作系统与硬件之间疯狂地I/O操作. 

	这样显然会加重操作系统的负担.

	而有了文件缓冲区地存在, 在不满足刷新文件缓冲区地条件时, 我们需要打印的信息就会先存放在文件缓冲区中, 暂时不与硬件发生I/O操作. 直到达成刷新文件缓冲区的条件时, 再将文件缓冲区内的所有数据刷新到屏幕上.

	这样, `文件缓冲区的存在, 其实可以集中处理数据刷新, 有效的减少操作系统与硬件之间的I/O次数, 进而提高整机的效率`

## 文件缓冲区在什么地方