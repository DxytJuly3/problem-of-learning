---
layout: '../../layouts/MarkdownPost.astro'
title: '[Linux] 多线程相关分析'
pubDate: 2023-04-11
description: ''
author: '七月.cc'
cover:
    url: 'https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/image-20230411163745002.png'
    square: 'https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/image-20230411163745002.png'
    alt: 'cover'
tags: ["Linux", "线程", "系统"]
theme: 'light'
featured: false
---

![ ](https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/image-20230411163745002.png)

---

我们已经了解了Linux操作系统进程部分相关知识：

> 博主有关Linux进程相关介绍的文章：
>
> - 💥[[Linux\] 系统进程相关概念、系统调用、Linux进程详析、进程查看、fork()初识](https://www.julysblog.cn/posts/Linux-Process-Concept&Processes)
>
> - 💥[[Linux\] 进程状态相关概念、Linux实际进程状态、进程优先级](https://www.julysblog.cn/posts/Linux-Process-States&System-Process-Actual-States)
>
> - 💥[[Linux\] 什么是进程地址空间？父子进程的代码时如何继承的？程序是怎么加载成进程的？为什么要有进程地址空间？](https://www.julysblog.cn/posts/Linux-Process-Addr-Space)
>
> - 💥[[Linux\] 详析进程控制：fork子进程运行规则？怎么回收子进程？什么是进程替换？进程替换怎么操作？](https://www.julysblog.cn/posts/Linux-Process-Control)

通过阅读这几篇文章, 至少可以让我们对Linux系统中的进程 有一个最基本又相对全面的认识.

但是今天这篇文章, 可能又会对之前介绍过的进程多少有一些推翻.

本篇文章的主要内容是：Linux操作系统中, 有关多线程的相关介绍.

# Linux线程概念

线程可以说是实际区别于进程的一个概念, 但也可以说是实际没有区别于进程的一个概念.

而实际区别与否, 其实 **`与平台有关`**

## 什么是线程

有关线程的概念, 大概可以通过三个要点介绍: 

1. 线程是在进程内部运行的执行流
2. 线程相比进程, 粒度更细, 调用成本更低
3. 线程是CPU调度的基本单位

不过这三个要点只能让你大概的对线程有一个最最最基本的认识：线程比进程要小. 但具体怎么小 是不知道的.

不过可以举个例子来简单的介绍一下, Linux下的线程：

在之前有关进程的介绍中, Linux系统中的进程 = PCB + 被加载到内存中的程序数据, 不过 PCB和内存中的程序数据 并不是直接相映射的.

之间还要通过 进程地址空间和相应的页表, 不过CPU实际只是是通过访问PCB 来实现对进程的调度的：

![ ](https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/image-20230411175200325.png)

`PCB(task_struct)中描述着进程地址空间, 进程地址空间与物理内存 通过两张页表来相互映射.` 

这是Linux系统中, 单个进程实际在操作系统中的存在形式.

系统创建进程会创建这所有的格式和数据.

不过我们也介绍过, 如果通过fork创建子进程, 在未作数据修改时 子进程与父进程是共享进程的数据和代码的. (子进程也存在自己的进程地址空间和页表, 只不过指向同一块数据和代码)

而且, 我们可以`通过对fork()返回值的判断, 让父子进程执行不同的代码块`.

这, 其实说明了一个 **细节**：**`不同的执行流, 可以做到执行不同的资源, 即 可以做到对特定资源的划分`**

那么, 如果下次创建进程, 操作系统并不创建有关进程的所有结构, 而是`只创建 PCB`. 将新的PCB 指向已经存在的进程.

![不同PCB指向同一个进程地址空间 - CPU与PCB之间的虚线表示, 此PCB也被CPU调度, 但当前可能没有被调度](https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/image-20230411190606396.png)

然后, 以子进程划分程序资源类似的手段, 将进程的代码划分为不同的区域, 并将不同的PCB设置为实际分别负责执行不同的区域的代码：

![PCB与代码区之间连接的红色虚线表示, PCB实际负责执行的代码区域](https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/image-20230411191733677.png)

最终, 不同的PCB可以访问进程地址空间内代码区的不同区域, 并通过相应的页表来访问到实际的物理内存.

实际上这样就在进程内部创建了多个PCB执行流, 而每个PCB执行流都只能访问一小部分的代码一小部分的页表.

那么, **`在Linux操作系统中`**, 我们就 `可以将这样的PCB执行流称作 "线程"`.

> **这里只是介绍了一下Linux操作系统中, 线程的** **`粗粒度`** **的实现原理**

---

介绍了Linux平台下 线程的粗粒度的实现原理, 我们应该可以理解一个内容：**`线程 : 进程 = N : 1`**

操作系统 对 比线程数量要少的进程 都会用 `PCB` 将进程的所有属性 描述、组织、管理起来, 那么对线程, 毫无疑问也是需要用一个结构体描述、组织、管理起来的. 在大多数的操作系统中, `描述线程的结构体`叫做 `TCB`

如果一个操作系统, 为了描述管理进程和线程, 在内核分别实现了不同的 `PCB` 和 `TCB`. 那么 `PCB` 和 `TCB` 之间一定存在非常复杂的耦合关系. 因为 `PCB` 描述一个进程, 而 `TCB` 描述进程内部的线程. 这两部分一定存在相当一部分的重叠属性, 还有一定的包含关系. 

那么, 在以后维护一个进程与其内线程的关系时, 一定是一个非常复杂的维护过程.

---

其实文章介绍线程概念到现在, 一举到具体的例子, 就在强调 `在Linux操作系统下`.

什么原因呢？ 其实 `不同操作系统实现线程的方式可能是不同的`.

我们在上面提到, 操作系统会存在一个描述线程属性的结构体, 以维护线程.

但是, 实际上 并不是所有的操作系统都会对线程另外描述一个结构体, 使TCB与PCB之间的关系变得非常复杂.

**`Linux操作系统`** 就没有另外实现一个描述线程的结构体, 而是 **`用task_struct(进程PCB)模拟了线体`**. 即Linux操作系统中, 描述进程和描述线程的结构体实际上是同一个结构体: `task_struct`

而我们常用的 Windows操作系统, 则是真正将进程与线程区分开, 分别实现了PCB和TCB 以分别用来维护线程和进程. 这样的被称为 `真·线程 操作系统`

**为什么不同的操作系统会对进程和线程之间的关系, 设计出这样的差别呢？**

其实是开发者对 进程和线程在执行流层面的理解不同.

以 Windows 来说, Win为了维护线程真正实现了一个不同于PCB的TCB. 也就是说, `Win的开发者认为进程和线程在执行流层面是不同的东西`. 进程有自己的执行流, 线程在进程内部也有自己的执行流

而 Linux 则认为 `进程和线程在概念上不做区分`, **`都是执行流`**. PCB要不要被CPU调度？TCB要不要被CPU调度？PCB调度要不要优先级？TCB要不要？要不要通过PCB找到代码和数据？要不要通过TCB找到代码和数据？进程切换要不要保护进程的上下文数据？线程切换要不要保护上下文数据？…… 

在Linux看来, 种种迹象表明 PCB和TCB的功能 不从更细节来细分的话, 其实是大致相同的. 无非就是PCB和TCB中描述的代码量和数据量的不同, 所以 进程和线程都只看成一个执行流.

所以 **`Linux线程, 其实就使用task_struct(进程PCB)模拟实现的.`**

**`只不过, 线程的TCB(实际上还是PCB)只能访问执行 整个进程中的一小块的代码和数据`**

> 这样做有什么好处？
>
> 用进程PCB模拟实现线程, 对线程 `可以复用操作系统中已经针对进程实现的各种调度算法`, 因为进程和线程的描述结构是相同的.
>
> 也不用维护进程和线程之间的关系.
>
> 也就是说, Linux操作系统中 **`线程TCB底层就可以看作进程PCB`**

Linux复用PCB实现TCB, 那么从CPU的角度看待线程, 其实与进程没有区别. CPU调度线程实际上看到的还是PCB(task_strcut)

---

## Linux进程-再理解

上面已经介绍了, Linux中 线程使用进程PCB来模拟实现的, 那么现在又该如何理解进程呢？

在没有介绍线程之前, 我们可以说 `CPU看到的所有task_struct都是一个进程`

而现在, `CPU看到的所有task_struct都是一个执行流`

之前我们说, 进程 = PCB + 内存中对应的代码和数据.

而现在, 我们知道进程内部可以存在许多task_srtuct, 那么又可以怎样理解进程呢？

![ ](https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/image-20230412093635919.png)

现在, 不能只认为 PCB + 代码和数据 就是一个进程. 而是 需要理解, 上图中的所有结构加起来才能叫一个进程.

我们可以说, **`进程是 承担操作系统资源分配的基本实体`**. 即 进程是 **`向系统申请资源的基本单位`**

在没有介绍线程时, 我们可以说 PCB可以表示一个进程, 因为之前进程只有一个执行流, 即只有一个task_struct.

现在 **`我们可以称 只有一个执行流的进程 为 但单执行流进程, 称 内部存在多个执行流的进程 为 多执行流进程`**

那么现在, 以CPU的视角来再次看待 task_struct, 我们 现在理解的CPU看到的task_struct 比 没有介绍线程时CPU看到的task_struct **`体量要小`**

因为 Linux中, 现在我们理解的CPU看到的 task_struct 可能是 `线程`, 可以看作是 **`轻量化的进程`**

进程是向系统申请资源的基本单位, CPU调度进程是通过 PCB(task_struct) 调度的, 所以 现在我们说 **`线程, 是CPU调度的基本单位`**

那么此时, 我们应该就可以理解 有关线程的概念三个要点介绍: 

1. 线程是在进程内部运行的执行流

	线程只访问执行进程的一部分数据和代码

2. 线程相比进程, 粒度更细, 调用成本更低

	进程切换调度, 需要切换PCB、进程地址空间、页表等

	而线程切换调度, 只需要切换TCB(实际还是PCB)就可以

3. 线程是CPU调度的基本单位

## Linux线程的创建、查看

介绍线程介绍了这么多, 那么 Linux中如何创建并查看线程呢？

下面我们来直接简单演示一下, 不做太多的介绍. 只创建和查看线程. 

### `pthread_create` 和 `pthread_join`

Linux操作系统为我们提供了创建线程的系统调用：

![ ](https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/image-20230412100123205.png)

```cpp
int pthread_create(pthread_t *thread, const pthread_attr *attr, void *(*start_routine)(void *), void *arg);
```

这个接口看起来, 非常的复杂

不过, 实际上也没有太复杂. `pthread_t` 就是一个无符号长整型：

![|inline](https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/image-20230412101716321.png)

第一个参数就是此类型的指针, 第一个参数是一个输出型参数, 用于获取线程id

第二个参数, 是线程属性结构体的指针, 暂时不过多介绍 现在我们传入 `nullptr`

第三个参数, 返回值为`空指针` 参数为`空指针`的 函数指针, 用于 `传入此线程需要执行的函数`.

第四个参数, 一个空指针, 此空指针其实就是 `第三个参数(函数指针)所指向的函数的参数`

处理创建线程之外, 线程与子进程一样, 还需要等待：

![ ](https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/image-20230412110550933.png)

```cpp
int pthread_join(pthread_t thread, void **retval);
```

此函数的参数很简单：

1. 第一个参数传入 需要等待的线程的id
2. 第二个参数接收退出结果, 暂时不关心. 我们只是看一看现象

简单的了解之后, 我们就可以使用此接口 创建线程:

```cpp
#include <iostream>
#include <string>
#include <pthread.h>
#include <unistd.h>
using std::cout;
using std::endl;
using std::string;

void* threadFun1(void* args) {
    string str = (char*)args;
    while (true) {
        cout << str << ": " << getpid() << " " << endl;
        sleep(1);
    }
}

void* threadFun2(void* args) {
    string str = (char*)args;
    while (true) {
        cout << str << ": " << getpid() << " " << endl;
        sleep(1);
    }
}

int main() {
    pthread_t tid1, tid2;

    pthread_create(&tid1, nullptr, threadFun1, (void*)"thread_1");
    pthread_create(&tid2, nullptr, threadFun2, (void*)"thread_2");
    sleep(1);

    while (true) {
        cout << " 主线程运行: " << getpid() << " " << endl;
        sleep(1);
    }

    pthread_join(tid1, nullptr);
    pthread_join(tid2, nullptr);

    return 0;
}
```

不过, 我们编译时会发现有错误：

![ ](https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/image-20230412105448190.png)

是连接错误, 为什么呢？

其实 man 手册中已经说了, 使用`pthread_create()` 接口, 编译连接时需要链接 pthread 库

因为, pthread 是第三方库, 所以我们需要手动链接：

![ ](https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/image-20230412105716705.png)

此时, 编译链接成功. 

我们运行程序：

![thread_show](https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/thread_show.gif)

可以看到线程在分别运行, 所输出的进程pid都是相同的. 

> 输出结果可能会混乱, 可能与线程的优先级与CPU核心、线程数有关
>
> 输出结果混乱, 也说明了线程可以并行运行

我们进程运行时查看系统的进程表：

![系统中只有一个有关threadTest的进程](https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/thread_onlyone_process.gif)

可以看到, 有关threadTest 的进程只有一个. 

即, 只有一个进程但是进程内存在多个线程.

那么如何查看线程呢？

我们可以在命令行使用 `ps -aL` 命令 来查看线程(a: all, -L: 轻量级进程)：

![ ](https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/image-20230412112247311.png)

可以看到, 线程列表中 存在三个相同命令名的线程. 且这`三个线程同时属于一个PID 23412. 还拥有各自的 LWP 轻量级进程编号`. 

并且此 **`有一个线程的LWP与PID相同, 表示此线程是主线程`** 

> 有兴趣的话, 可以在创建两个线程之后, 再创建一个子进程. 
>
> 创建之后, 观察子进程有没有什么地方与之前创建的子进程时的情况不同

