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

## 处理进程信号

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

 
