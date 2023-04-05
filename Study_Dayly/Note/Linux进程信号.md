# 进程信号

进程信号, 在Linux系统的学习中, 是一个非常重要的概念.

我们可以通过向进程发送信号来让进程执行某些指定的动作.

以一个简单的例子来说：

一个简单的进程在运行着, 我们给此进程发送信号让子进程终止运行.

![9信号杀进程](https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/9%E4%BF%A1%E5%8F%B7%E6%9D%80%E8%BF%9B%E7%A8%8B.gif)

这就是信号的作用

## 介绍进程信号

在我们日常的生活中, 存在着许多信号的形式: 红绿灯、闹钟、上下课铃声……

我们可以正常的识别每种信号的功能. 比如：红灯停, 绿灯行. 铃声响后是上课或者下课. 闹钟在提醒我们需要做什么事情了……

这些信号在我们生活中的某些场景下可以表示不同的含义. 我们也可以在特定的场所下明白这些信号的含义.

为什么我们在信号出现的时候可以正确的判断出信号的含义？

是 **`因为我们在信号还未发出的时候, 其实就已经知道了某些信号的含义. 所以我们在接收到信号之后, 才会做出相应的动作.`**

而对应的, Linux操作系统中的 进程信号其实也是这样的. 

Linux的进程信号是给进程发送的, 且信号一定具有一定的含义, 也就是说, *`进程接收到信号之后需要 可以正确的处理接收到的信号的能力`*

不过, **`在接收到信号之前, 进程就应该具备处理信号的能力`**, 除此之外, 还需要其他的能力. 也就是说：

1. 进程本来就具有下面的这些能力, 无论是否接收到信号
2. 进程需要有识别进程信号的能力, 可以接收, 也可以分辨出是什么信号
3. 进程需要有处理信号的能力, 即 需要执行信号表示的含义或功能

而`进程的这些能力是操作系统赋予的, 每个进程都具有处理信号的能力`

---

但是, 生活中我们是如何处理信号的？

如果在生活中, 我们有外卖到了, 外卖小哥给我们打电话了. 我们一般会有一种处理方式？

1. 马上放下手头的事情, 去门口取外卖
2. 告诉小哥等一会, 先忙完手头的一点事情在去拿外卖
3. 告诉小哥把外卖放下就行, 然后再决定什么时候去拿

一般会有这几种处理方式. 

在外卖来的时候, 其实有很大的几率我们手头是有其他事情在做的. 其实这就说明, `外卖到了这件事是异步发生的.`

并且, 有时候我们为了先处理手头的事情, 会暂时将外卖小哥搁置一边, 或者跟外卖小哥说一下把外卖搁置一边. 之后我们再去处理外卖.

在告诉外卖小哥把外卖放下之后, 我们其实可以随便处理外卖.

而 进程信号 也是相同的道理

`进程信号 是进程间事件异步通知的一种方式`, 也就是说进程在收到信号的时候其实有极大的可能正在处理自己的事情. 进程就可以选择是否立即处理接收到的信号.

进程可以直接去处理信号, 也可以暂时将信号搁置到一边, 不立即处理. 

不过, **`进程不对信号立即处理, 不代表没有处理信号. 进程接收到信号之后, 一定会先记住这个信号被接收了`**. 只有进程记住了接收到的信号, 进程才能在之后处理信号.

并且, 进程处理信号也会像我们处理外卖一样, 也有几种情况:

1. 默认情况, 默认处理. 即 按照信号的含义进行处理
2. 忽略信号, 不做处理. 不管信号.
3. 接收到信号, 自定义处理. 即 由用户接收信号, 并自定义处理动作

---

在 Linux系统的命令行中, 我们可以使用 kill 命令来给指定进程传递信号. 

在文章的开始, 我们已经使用了 `kill -9` 杀死了一个进程.  `9` 其实就是一个进程信号. 

那么 Linux系统中的进程信号都有什么？我们可以使用 kill -l 查看Linux系统中的进程信号：

<img src="https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/image-20230404091257203.png" alt="image-20230404091257203" style="zoom:80%;" />

kill -l 显示出的Linux进程信号中, **`1 ~ 31 号都是普通的进程信号`**. 

而 **`34 ~ 64 都是属于实时信号`**. 实时信号是需要 `立即处理` 的信号, 而普通信号则不需要立马处理.

这些信号在使用的时候, 可以直接使用各信号前面的数字, 也可以使用信号字母. 数字叫 信号的编号, 而大写字母则是信号的名称

并且, 看到这些都是大写字母组成的信号, 我们第一时间可以想到什么？

其实这些信号都是 **`宏`**. 这些宏定义在 **`signum.h`** 头文件中：

<img src="https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/image-20230404093506092.png" alt="image-20230404093506092" style="zoom:80%;" />

除了直接查看头文件里定义的内容, 还可以通过 `man 7 signal` 来查看man手册中记录的有关信号的内容：
![image-20230404093655013](https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/image-20230404093655013.png)

man 手册中, 不仅记录了信号的宏定义和编号, 还记录的此 **`信号的含义, 即默认处理方法.`**

## 进程信号的处理

在介绍进程信号的产生流程之前, 先来猜测一下 *`进程信号是怎么发送给进程的？`*

我们知道, 进程是由 PCB 控制的, 而 PCB 实际上是由操作系统管理控制的. 

那么是不是说, 进程信号 其实就是操作系统通过 修改进程PCB中的数据 来达到 向进程发送信号的目的 的呢？

是的, 进程PCB中描述着 一个记录进程信号的 **`位图`**, 当使用指令或其他方式 `向进程发送信号时, 操作系统就会在进程信号位图的指定位置写入1`. 位图中指定位置的数据变为了1, 就说明写入了相应的信号. 进程就可以根据位图信息 来判断接收到了什么信号.

这就是 `信号发送给进程的原理`, 并且也解释了 `进程是如何接收信号的`. 

因此, **`向进程发送信号 也可以说 向进程写入信号`**

不过, 我们实际发送进程信号的时候, 一般还是直接使用进程信号的编号. 也就是 `kill -l` 列出信号列表时, 每个信号前面的数字

---

上面在介绍进程信号的时候, 我们提到, 进程对接收到的信号的处理一般分为三种：

1. 默认情况, 默认处理. 即 按照信号的含义进行处理
2. 忽略信号, 不做处理. 不管信号.
3. 接收到信号, 自定义处理. 即 由用户接收信号, 并自定义处理动作

默认情况, 即表示 此信号的默认处理方法.  忽略信号, 即表示不管信号. 

但是 进程接收到信号 自定义处理, 则是一种特殊情况. 自定义处理方法 是由程序的编写者定义的.

当用户编写了指定信号的自定义处理方法时, 进程在接收到信号之后, 本该由系统内核处理的信号 会转换为用户态的指定处理方法 来处理信号. 这种情况被称为 **`信号的捕获`**

### signal() 捕获信号

signal() 是一个系统调用接口, 用于捕获进程信号, 并由用户处理:

![image-20230404102659624](https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/image-20230404102659624.png)

此函数的声明为：`sighandler_t signal(int signum, sighandler_t handler);`

看起来非常的麻烦, 但其实 `sighandler_t` 只是一个 返回值为空 参数为一个int类型 的函数指针：`void (*)(int)`

那么也就是说, `signal()` 函数的返回值是一个函数指针, 其第二个参数也需要传入一个函数指针

那么 signal() 的参数：

1. `int signum`, 此为signal() 的第一个参数, 需要传入指定的信号编号, 表示捕获此信号时 自定义处理

2. `sighandler_t handler`, 此为 signal()的第二个参数, 需要传入一个 返回值为空, 参数为一个int类型 的函数指针, 其实可直接传入一个函数名. 传入的函数, 即为 **`指定信号的自定义处理函数`**.

	即, 当捕获到指定信号之后, 不会按照默认情况去处理此信号, 而是通过我们传入的自定义函数来处理

	> 一般在函数的参数中传入一个函数指针, 此函数指针一般可能用于回调. 此函数可被称为回调函数、回调方法

那么, signal() 究竟是怎么使用的呢？有什么效果呢？

我们可以使用这段代码一探究竟：

```cpp
#include <iostream>
#include <unistd.h>
#include <signal.h>
using std::cout;
using std::endl;

int cnt = 1;

void handler(int signo) {
    cout << "我是进程, 我捕获到一个信号：" << signo << ", 这是第 " << cnt << " 次" << endl;
    cnt++;
}

int main() {
    signal(2, handler);
    sleep(1);
    cout << "进程已经设置完了" << endl;

    while (true)
    {
        cout << "我是一个正在运行中的进程: " << getpid() << endl;
        sleep(1);
    }

    return 0;
}
```

我们知道, `Ctrl + C` 快捷键会给前台进程发送 `2信号(SIGINT)`, 此信号的默认处理方式是：从键盘中断进程.

<img src="https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/SIGINT.gif" alt="SIGINT" style="zoom:80%;" />

而上面的代码中, 我们通过使用 signal() 将2信号的处理方式设置为一个自定义的回调函数. 在使用 `Ctrl + C` 会发生什么呢？

<img src="https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/signal_SIGINT.gif" alt="signal_SIGINT" style="zoom:80%;" />

可以看到, 尽管一直使用 `Ctrl + C` 快捷键, 也不能中断进程了, 而是不断回调我们传入的函数 以自定义处理信号.

这就是 signal() 的作用, **`捕获指定信号, 并自定义处理`**

> 按理论来说, signal() 是可以针对所有的普通信号进行捕获的, 但实际上存在例外：
>
> signal() 无法捕获 `9信号(SIGKILL)`. 也就是说, 即使使用了 `signal(9, handler);`, 给进程发送 9信号, 进程依旧会默认处理：
>
> ```cpp
> #include <iostream>
> #include <unistd.h>
> #include <signal.h>
> using std::cout;
> using std::endl;
> 
> int cnt = 1;
> 
> void handler(int signo) {
>     cout << "我是进程, 我捕获到一个信号：" << signo << ", 这是第 " << cnt << " 次" << endl;
>     cnt++;
> }
> 
> int main() {
>     signal(9, handler);
>     sleep(1);
>     cout << "进程已经设置完了" << endl;
> 
>     while (true)
>     {
>         cout << "我是一个正在运行中的进程: " << getpid() << endl;
>         sleep(1);
>     }
> 
>     return 0;
> }
> ```
>
> <img src="https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/signal_SIGKILL.gif" alt="signal_SIGKILL" style="zoom:80%;" />

这是处理进程信号的一种方式, 即 用户自定义处理方法来处理信号.

并且我们知道了 **`进程信号可以由 键盘 来产生`**. 我们使用键盘组合键 `Ctrl + C`, 产生了 2信号, 并由操作系统发送给了前台进程

那么进程信号究竟可以怎么样产生呢？

## 用户层产生进程信号的方式

### 键盘产生进程信号

上面我们介绍自定义处理进程信号时, 提到了 **`进程信号可以由键盘产生`**. 

比如：`Ctrl + C` 产生 `2) SIGINT` 信号, 可以通过键盘中断进程运行

除此之外, 进程信号还可以通过什么方式产生呢？

### 系统调用产生进程信号

除了键盘产生进程信号之外, Linux系统还提供了一些 系统调用接口来产生进程信号.

#### kill()

kill 除了是一个命令行命令之外, 还是一个系统调用:

![image-20230404164654595](https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/image-20230404164654595.png)

kill()系统调用的用法其实就与 kill命令行命令相同.

只不过 kill 命令行命令是 `kill sig pid`, 而 kill()系统调用则是 `kill(pid, sig)`

也就是说, kill()系统调用的两个参数应该传入:

1. `pid_t pid`, 此参数传入需要发送进程的pid
2. `int sig`, 此参数传入需要发送的进程信号, 可以使用 **`信号编号`** 也可以使用 **`信号宏名`**

且, man 手册中提到, kill()执行成功则返回0, 否则返回 -1

我们可以使用kill()系统调用, 可以模仿实现一下 命令行的kill命令：

`mykill.cc:`

```cpp
#include <iostream>
#include <cstdlib>
#include <string>
#include <cstring>
#include <cerrno>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
using std::cout;
using std::cerr;
using std::endl;
using std::string;

void usage(const string& proc) {
    cout << "Usage:\n\t" << proc << " sig pid" << endl;
}

// 模拟实现 kill命令
// ./mykill sig pid
int main(int argc, char* argv[]) {
    if (argc != 3) {
        usage(argv[0]);             // argv[0] 即为命令行的第一个字符串
        exit(1);
    }

    if (kill( (pid_t)atoi(argv[2]), atoi(argv[1]) ) == -1) {
        cerr << "kill error, " << strerror(errno) << endl;
        exit(2); 
    }
    
    return 0;
    
}
```

执行这段代码的结果是：

![mykill](https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/mykill.gif)

我们不按照要求执行 mykill时, 会提示使用方式, 然后我们可以通过 `./mykill sig pid` 来对 指定pid的进程 发送 sig信号

#### raise()

raise()也是一个系统调用接口：

![image-20230404173228488](https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/image-20230404173228488.png)

如果说kill()的作用是给指定的进程发送信号, 那么 `raise()` 就是 `给调用者发送信号, 也就是给自己发送信号`

那么, raise()的调用结果是什么呢？

```cpp
#include <iostream>
#include <unistd.h>
#include <signal.h>
using std::cout;
using std::endl;

int cnt = 1;

void handler(int signo) {
    cout << "我是进程, pid: " << getpid() << ", 我捕获到一个信号：" << signo << ", 这是第 " << cnt << " 次" << endl
    cnt++;
}

int main(int argc, char* argv[]) {
    signal(2, handler);

    while (true) {      // 循环给自己发送 信号2
        raise(2);
        sleep(1);
    }
    
    return 0;
}
```

在上面这段代码中, 我们先使用 signal() 来捕获2信号, 然后再循环使用 raise(2) 测试raise()发送信号的结果.

最终的执行结果为：

<img src="https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/raise.gif" alt="raise" style="zoom:80%;" />

从结果可以看出, `raise()` 的作用确实是 **`向自己发送信号`**

#### abort()

abort() 是一个使用和作用更加简单的系统调用：

![image-20230404175023714](https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/image-20230404175023714.png)

此系统调用的作用就是, **`使调用它的进程异常终止`**

> man 手册中关于 abort() 系统调用的描述的大致意思是：
>
> 首先接触对 ==SIGABRT== 信号的阻塞, 并向调用的进程发送 ==SIGARBT== 信号. 这会导致进程异常终止, 除非 ==SIGABRT== 信号被捕获, 且自定义的处理信号的函数返回.
>
> 并且, abort() 函数导致进程终止, 会关闭并刷新进程打开的所有流
>
> 如果, ==SIGABRT== 信号被忽略 或 被捕获且处理信号的函数会返回. 则 `abort() 函数仍然会将进程终止`. 他会恢复进程对 ==SIGABRT== 信号的默认配置并通过二次发送信号, 达到终止进程的目的.

也就是说, **`调用 abort() 一般情况下一定会使进程异常退出, 无论 SIGABRT 信号是被忽略还是被捕获`**

abort() 会向自己发送 ==SIGABRT== 信号, SIGABRT 信号的编号是什么呢？

<img src="https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/image-20230404180640582.png" alt="image-20230404180640582" style="zoom:80%;" />

那么, 我们可以在代码中使用 abort() 函数：

```cpp
#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <signal.h>
using std::cout;
using std::endl;

int cnt = 1;

void handler(int signo) {
    cout << "我是进程, pid: " << getpid() << ", 我捕获到一个信号：" << signo << ", 这是第 " << cnt << " 次" << endl
    cnt++;
}

int main(int argc, char* argv[]) {
    signal(2, handler);

    while (true) {      // 循环给自己发送 信号2
        raise(2);
        sleep(1);
        if (cnt > 5)
            abort();
    }
    
    return 0;
}
```

<img src="https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/abort_2023-4-4.gif" alt="abort_2023-4-4" style="zoom:80%;" />

正常情况下, abort() 可以使进程异常退出

如果, 我们在调用 abort() 之前, 捕捉了 ==SIGABRT== 信号, 会如何呢？

```cpp
#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <signal.h>
using std::cout;
using std::endl;

int cnt = 1;

void handler(int signo) {
    cout << "我是进程, pid: " << getpid() << ", 我捕获到一个信号：" << signo << ", 这是第 " << cnt << " 次" << endl
    cnt++;
}

int main(int argc, char* argv[]) {
    signal(2, handler);
    signal(SIGABRT, handler);				// 捕捉 SIGABRT 信号

    while (true) {      // 循环给自己发送 信号2
        raise(2);
        sleep(1);
        if (cnt > 5)
            abort();
    }
    
    return 0;
}
```

<img src="https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/signal_SIGABRT_abort_2023-4-4.gif" alt="signal_SIGABRT_abort_2023-4-4" style="zoom:80%;" />

可以看到, 进程最终还是调用 abort() 终止了. 但是与不捕捉 ==SIGABRT== 信号时不同的是, **`abort() 实际上是调用了两次才成功终止了进程`**

因为, 我们可以看到, 第一次调用 abort() 时, 给进程发送的 ==SIGABRT== 信号被捕获了.

第二次 才使进程终止了

### 软件条件产生进程信号

==SIGALRM== 是一个软件条件产生的信号. 我们可以在程序内 `调用 alarm() 系统调用来设置闹钟`. 

等到闹钟"响" 的时候, 操作系统就会向进程发送 ==SIGALRM== 信号. 此信号的默认处理是 **`终止进程`**

==SIGALRM== 信号的编号是14：

<img src="https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/image-20230404184826180.png" alt="image-20230404184826180" style="zoom:80%;" />

```cpp
#include <iostream>
#include <cerrno>
#include <unistd.h>
using std::cout;
using std::endl;

int cnt = 0;

int main(int argc, char* argv[]) {
    alarm(1);           // 设置 1s 的闹钟

    while (true) {
        cout << "count: " << cnt++ << endl;
    }

    return 0;
}
```

<img src="https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/alarm_2023-4-4.gif" alt="alarm_2023-4-4" style="zoom:80%;" />

这段代码的作用, 其实是计算了 1s 内操作系统的I/O次数.

> 1s 内的 I/O 次数, 不等于1s内硬件计算的次数, 如果将代码改为下面这样：
>
> ```cpp
> #include <iostream>
> #include <unistd.h>
> #include <signal.h>
> using std::cout;
> using std::endl;
> 
> int cnt = 0;
> 
> void handler(int signo) {
>     cout << "我是进程, pid: " << getpid() << ", 我捕获到一个信号：" << signo << endl;
>     cout << "count: " << cnt << endl;
>     exit(1);
> }
> 
> int main(int argc, char* argv[]) {
>     signal(SIGALRM, handler);
>     alarm(1);           // 设置 1s 的闹钟
> 
>     while (true) {
>         cnt++;
>     }
>     
>     return 0;
> }
> ```
>
> <img src="https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/cnt_alarm_2023-4-4.gif" alt="cnt_alarm_2023-4-4" style="zoom:80%;" />
>
> 可以看到, 最终的执行结果就是 亿级的, 而不是万级
>
> 这才是, 计算的速度. 
>
> 所以说, **`I/O速度 相比较于硬件的运行速度 是非常的慢的`**

alarm() 是一个系统调用, 但是 ==SIGALRM== 信号 并**`不是这个系统调用本身产生的`**.

alarm() 的作用只是设置一个闹钟, **`只是设置了一个条件`**.

### 硬件异常产生进程信号

我们在使用语言的时候, 一定会遇到一种情况：程序崩溃了.

比如, 我们在代码中写入 `除0`、`解引用空指针` 或 `越界访问` 操作：

```cpp
#include <iostream>

int main() {
    // 越界访问
    int arr[10];
    arr[100000] = 0;
    
    // 解引用空指针
    //int* pi = nullptr;
    //*pi = 10;
    
    // 除0
    //int i = 10;
    //i /= 0;

    return 0;
}
```

除0, 执行结果: <img src="https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/image-20230405164205433.png" alt="image-20230405164205433" style="zoom:80%;" />
报出 `浮点异常` 的错误

解引用空指针, 执行结果: <img src="https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/image-20230405164430588.png" alt="image-20230405164430588" style="zoom:80%;" />
报出 `段错误`

越界访问, 执行结果: <img src="https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/image-20230405164750973.png" alt="image-20230405164750973" style="zoom:80%;" />
也是报出 `段错误`

这两个错误的结果都是导致进程崩溃退出. 我们现在只能说它是发生了某种错误导致进程崩溃退出了. 

而 **`进程崩溃的本质是什么呢？`**

其实 进程崩溃的本质是 **`进程收到了异常信号`**

我们可以测试一下, 当我们把信号都捕获并自定义处理之后, 再发生 段错误 或 浮点异常 时：

```cpp
#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
using std::cout;
using std::endl;

void handler(int signo) {
    cout << "我是进程, pid: " << getpid() << ", 我捕获到一个信号：" << signo << endl;
    exit(1);
}

int main() {
    // 捕获进程, 自定义处理
    for(int sig = 1; sig <= 31; sig++) {
        signal(sig, handler);
    }
    // 越界访问
    int arr[10];
    arr[100000] = 0;
    
    // 解引用空指针
    //int* pi = nullptr;
    //*pi = 10;

    // 除0	
    //int i = 10;
    //i /= 0;

    return 0;
}
```

此时代码的执行结果是:

1. 越界访问: <img src="https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/image-20230405165616328.png" alt="image-20230405165616328" style="zoom:80%;" />
2. 解引用空指针: <img src="https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/image-20230405165654908.png" alt="image-20230405165654908" style="zoom:80%;" />
3. 除0: <img src="https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/image-20230405165733969.png" alt="image-20230405165733969" style="zoom:80%;" />

可以看到, 当我们将1~31信号自定义处理时, 从代码的执行结果就可以看出来, 其实 进程代码发生异常错误导致进程崩溃退出, **`本质上是 异常错误产生了相应的信号 并发送给了进程, 进而才导致了进程的退出`**

我们看到, `越界访问和解引用空指针` 会产生信号11, 而 `除0` 会产生信号8. 这两个信号在Linux系统中, 可以看到：

<img src="https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/image-20230405170438971.png" alt="image-20230405170438971" style="zoom:80%;" />

这两个信号的默认处理方案都是 使进程终止.

#### 除0 和 越界访问、野指针 如何产生相应信号

通过上面的介绍, 我们知道了 除0错误 和 越界访问或野指针问题 导致进程崩溃退出, 本质上是因为这两个错误产生了信号 并发送给了进程, 才导致进程退出的.

那么, 自然而然就有一个问题：这些错误是如何产生进程信号的？操作系统是如何知道的？

##### 除0

有关 除0错误 产生信号, 过程其实是这样的.

再分析之前, 我们要先明白一点：**`进程的所有非图形计算操作实际上都是由CPU执行的`**.

也就是说, 进程执行的 除0 操作, 其实也是在CPU内部执行的. 而 CPU 内部有一个寄存器, 叫状态寄存器. 当 CPU执行到除0操作时, 很明显CPU是不能正确计算的, 此时CPU就会 **`将状态寄存器设置为有错误`** 的状态：浮点数异常.

即, CPU内部的寄存器设置了错误状态, 操作系统就可以识别到CPU内有报错. 然后 操作系统就会做两件事

1. 操作系统需要识别是谁报的错, 即 操作系统需要知道是哪个进程报的错
2. 操作系统需要识别是什么错误, 即 操作系统需要知道进程因为什么出现了错误

然后, 操作系统就会 构建相应的信号 –> 向目标进程发送信号 –> 进程在合适的时候处理信号 –> 进程终止

##### 越界访问、野指针

除0操作实际上是因为 CPU这个硬件计算时出错, 而产生的信号

那么 越界访问和野指针又是因为什么呢？

首先, 我们知道 我们使用的语言层面的地址, 其实都是虚拟地址. 进程在访问虚拟地址时, 会 **`通过虚拟地址转化为物理地址, 再找到物理内存, 在读取访问对应的数据或代码`**. 

而 地址的转化工作 实际上是由 MMU(内存管理单元——硬件) 和 页表(软件) 结合实现的. 如果 访问的虚拟地址存在问题, 那么 转化过程就会出现错误, 此时的错误会在 MMU硬件上体现出来, 操作系统也就可以发现硬件出现了问题.

然后 操作系统就还会做那两件事：

1. 操作系统需要识别是谁报的错, 即 操作系统需要知道是哪个进程报的错
2. 操作系统需要识别是什么错误, 即 操作系统需要知道进程因为什么出现了错误

然后, 操作系统就会 构建相应的信号 –> 向目标进程发送信号 –> 进程在合适的时候处理信号 –> 进程终止

---

也就是说, 实际上 进程在执行内部代码时出现的这两个错误, 实际上**`都会在硬件上体现出来, 然后产生相应的信号`**, 再通过操作系统发送给进程.

这也就是进程信号产生的第四种方式, 硬件异常产生

我们已经理解了 进程崩溃退出的本质其实是硬件异常产生了会让进程退出的信号. 

那么, **`进程崩溃一定会使进程退出吗？`**

答案是否定的, **`进程崩溃的本质是进程收到了信号, 不能再正常运行了`**. 而信号的处理 处理默认情况, 还是有其他情况的. 比如, 当我们把指定的信号捕获并自定义处理方法时, 进程就不会退出了

下面这段代码的例子, 就很好的展示进程崩溃不退出的情况：

```cpp
#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
using std::cout;
using std::endl;

int cnt = 0;

void handler(int signo) {
    cout << "我是进程, pid: " << getpid() << ", 我捕获到一个信号：" << signo << ", count: " << cnt++ << endl;
}

int main() {
    // 捕获进程, 自定义处理
    signal(8, handler);
    
    // 除0	
    int i = 10;
    i /= 0;

    return 0;
}
```

<img src="https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/code_err_noexit_2023-4-5.gif" alt="code_err_noexit_2023-4-5" style="zoom:80%;" />

这段代码的执行结果是, 无限的输出 捕捉到了8信号.

这是因为, 我们使用 `signal(8, handler);` 捕捉并自定义处理了 8信号, 并且处理方法不会使进程退出. 在此基础上, 操作系统因为检测到了浮点异常错误, 就会不停的向进程发送 8信号, 进程也会不停的接收并处理此信号. 但是由于处理方法并不涉及进程的退出, 所以进程不会退出.

即, 进程崩溃 实际并不一定会退出

## core dump

core dump 是什么？

再我介绍进程等待的时候, 为了获取进程的退出码. 我介绍了获取 进程退出码以及信号码时 的方法和结构.

在那时, 简单的提了一句话：

status指针指向的是一个整型, 而这个整型只需要关注 `低16位`就可以了, `此低16位中的高8位 用来表示退出码, 低8位 用来表示退出信号`

<img src="https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/image-20230308163321498.png" alt="image-20230308163321498" width="80%" />

并且, 还提到表示退出信号的8位, **`暂时只需要关注低7位, 其中最高位是一个单独的 core_dump 标志, 暂时忽略`**

> 博主有关进程控制的文章的相关链接：
>
> [【Linux】[万字] 详析进程控制：fork子进程运行规则？怎么回收子进程？什么是进程替换？进程替换怎么操作？](https://blog.csdn.net/dxyt2002/article/details/129745548)

那么, core dump 究竟是什么？

core dump *`可以是一个动作 叫做 内存快照`*. 

也*`可以是 stutas 整型中的一个标记位`*, 此标记位 表示进程是否执行了 core dump 操作, 如果**`执行了 core dump标记位就会被置为1`**, **`否则会被置为0`**. 

而 进程只有在接收到特定的信号时, 才可能会执行 core dump 操作:

<img src="https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/image-20230405180115554.png" alt="image-20230405180115554" style="zoom:80%;" />

我们可以通过在命令行使用 `man 7 signal` 命令, 来查看man手册中记载的有关进程信号的部分详细信息. 其中记录着各信号以及其编号.

并且, 在信号表中 有着 *`Action一栏`*. 此栏中 *`记录着 Core 的信号被进程接收到之后, 进程就有可能会发生 core dump操作`*, 如果执行了, 对应的 进程退出信息中的 core dump 标志位就会被设置为1.

但是, 我们在测试进程崩溃的原因时, 并没有发现进程有任何 core dump操作的迹象:

```cpp
#include <iostream>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
using std::cout;
using std::endl;

int main() {
    pid_t id = fork();
    if(id == 0) {
        // 子进程 除0错误, 应该接收到 8信号
        int i = 10;
        i /= 0;
        exit(1);
    }

    // 父进程等待子进程
    int status = 0;
    waitpid(id, &status, 0);
    printf("exitcode: %d, signo: %d, core dump flag: %d\n", (status>>8) & 0xFF, status & 0x7F, (status>>7)&0x1);

    return 0;
}
```

我们已经知道了, 除0 错误时 进程其实会接收到 8信号, 而 8信号应该是会执行 core dump操作的, 那么对应进程的推出信息中的core dump 标志位也应该被置为1. 

但实际上, 我们执行上面的代码的结果是：

<img src="https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/image-20230405181416211.png" alt="image-20230405181416211" style="zoom:80%;" />

我们在子进程中执行了除0操作, 并且父进程等待子进程接收退出信息. 但是最终 core dump标志位的值并不是1.

这是为什么呢？

其实这与系统的设置有关, 我们在命令行使用 `ulimit -a` 可以查看系统的一部分相关设置：

<img src="https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/image-20230405181640938.png" alt="image-20230405181640938" style="zoom:80%;" />

其中, 有一个 core file size 的设置, 如果你使用的是云服务器的话, 这个设置应该不是0 就是 unlimited.

如果 **`使用的是虚拟机的话, 这个设置应该是有数值的, 也不会出现进程不执行 core cump的情况`**

当, 我们使用 `ulimit -c 20` 将 core file size 设置为 20 之后, 再执行上面的代码程序：

<img src="https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/image-20230405182006009.png" alt="image-20230405182006009" style="zoom:80%;" />

<img src="https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/image-20230405182254736.png" alt="image-20230405182254736" style="zoom:80%;" />

其实, `core file size` 设置就是 设置系统可生成的 core文件的数量, 服务器默认会设置为0

所以, 在没有更改 `core file size` 时, 即使接收到了某些会执行 core dump操作的信号, 也不会执行 core dump

因为, `core dump 操作其实就是将进程的内存信息和当时的部分运行状态 "快照" 下来, 存储到 core 文件中`

core 文件的命名, 其实就是 **`core.进程pid`**

### core 文件有什么用？

那么 core 文件有什么用?

我们查看core文件的内容：

![image-20230405182851145](https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/image-20230405182851145.png)

可以看到, 都是乱码.

那么 core 文件是怎么用的呢？

其实是这样用的：

1. 首先, 我们将上面的代码重新 以调试模式 编译链接一下：

	`g++ -g mykill.cc -o mykillg`

	<img src="https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/image-20230405183419680.png" alt="image-20230405183419680" style="zoom:80%;" />

2. 然后再执行 `./mykillg`, 会生成一个新的 core文件

	<img src="https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/image-20230405183503574.png" alt="image-20230405183503574" style="zoom:80%;" />

3. 然后我们使用 gdb 调试进程：

	`gdb mykillg`

	<img src="https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/image-20230405183554388.png" alt="image-20230405183554388" style="zoom:80%;" />

4. 在 gdb 调试界面, 直接输入 `core-file core.2127`

	![image-20230405183649016](https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/image-20230405183649016.png)

	可以发现, 我们通过gdb调试进程时使用core文件, 可以 **`直接定位出 进程上次运行的错误位置、信息`**

也就是说 core 文件, 其实是为 事后使用gdb调试程序时 快速定位错误信息 所生成的文件.

---

不过, 在服务器中 core文件的生成 默认是关闭的. 

这是为什么呢？

在我的服务器中, 我们一段这么简单的代码 生成的core文件有多大？

<img src="https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/image-20230405184205019.png" alt="image-20230405184205019" style="zoom:80%;" />

一个 core文件就是16KB.

那如果是企业中的某个服务项目呢？如果某个服务项目代码内部发生了错误, 导致服务崩溃了. 又会生成多么大的 core文件？

并且, 企业中的服务项目发生错的导致关闭之后, 企业首先要做的是什么？ 尝试重启服务, 不停的尝试. 并尝试修复错误.

如果在不停尝试重启服务的过程中, 服务也在不停发生错误, 从而不停的生成 core文件, 那么将会占用服务器的多少资源？这个资源占用是非常庞大的.

所以说, 为了防止 因为core文件占用服务器资源过大, 服务器上的 core file size 一般都是设置为0的

## 进程信号在内核中的表示

文章上面的内容, 着重谈论的是 进程信号的产生 和 简单的处理. 

并没有着重谈论 进程信号产生之后, 进程处理信号的详细操作 以及 进程信号产生 到 进程接收 之间的内核表现.

下面就来着重谈论一下, 进程信号在内核中的表示 以及 进程内部处理进程信号的详细操作

### 进程信号相关概念

为了方便介绍进程信号在进程内核中的表示, 这里还需要介绍几个概念：

1. 进程 执行对进程信号的实际处理 动作, 称为 **`信号递达`**, 传递的递
2. 进程信号 从产生到递达之间的状态, 称为 **`信号未决`**. 即 信号接收到了, 但是没处理的状态
3. 进程 可以选择 **`阻塞某种进程信号`**. 即 接收到了, 但是阻塞信号递达, 就是不做处理
4. 被阻塞信号产生时, 将保持未决状态, 直到进程解除对此信号的阻塞, 信号才会递达
5. 信号阻塞 和 忽略不同, **`忽略是处理的行为, 即信号已经递达`**. 而**`阻塞是递达之前的状态`**

### 在内核中表示

在文章的开头简单介绍进程信号时, 提到过, 进程信号是以位图的形式存储在进程PCB中的.

而实际上, 进程PCB中描述的有关进程信号的位图, 其实有三个：

<img src="https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/image-20230405225334274.png" alt="image-20230405225334274" style="zoom:80%;" />

task_strcut 结构体中描述则两个位图和一个指针数组.

先介绍 `pending 位图`: 

pending 是未决位图, 用来`表示进程收到的信号, 对应位置即为对应编号的信号`. 当`pending位图中的某位为1, 即表示此位的信号在进程中处于未决状态`. 即 接收了但是还未处理

在上图中, pending 位图中表示 SIGINT(2) 的位置为1, 则表示 进程接收到了 SIGINT(2) 信号, 但还未处理.

然后是, `handler 指针数组`:

handler 是`存储进程信号处理方法的数组, 每位对应一个处理方法`. 上图中, 即表示 SIGHUP(1) 信号的处理方法是 SIG_DFL, SIGINT(2) 的处理方法是 SIG_IGN, SIGQUIT(3) 的处理方法是 用户处理方法(sighandler)……一次类推

最后是, `block 位图`:

block 是阻塞位图, 用来表示对应位置的信号是否阻塞. 当`指定位置为1时, 即表示此位置信号会被阻塞`. 上图中 则表示 SIGINT(2) 和 SIGQUIT(3) 被阻塞.

即, 这两个位图和一个指针数组, 需要横着对比观察, 可以更好的分析, 进程内核有关信号的描述信息.
