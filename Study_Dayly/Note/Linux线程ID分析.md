---
layout: '../../layouts/MarkdownPost.astro'
title: '[Linux] 如何理解线程ID？什么是线程局部存储？'
pubDate: 2023-04-15
description: '在Linux中, 使用 pthread_create() 创建线程的时候, 第一个参数就是用来接收线程ID的'
author: '七月.cc'
cover:
    url: 'https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/image-20230415173757629.png'
    square: 'https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/image-20230415173757629.png'
    alt: 'cover'
tags: ["Linux", "线程", "系统"]
theme: 'light'
featured: false
---

![ ](https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/image-20230415173757629.png)

---

前面的几篇文章, 介绍了线程的概念与控制的一些基本的内容.

虽然已经介绍了很多了, 但是 一直都没有详细的介绍一个重要的东西：`线程ID`

那么, 本篇文章 就来着重介绍一下, **`如何理解线程ID`**

# Linux线程ID

在Linux中, 使用 `pthread_create()` 创建线程的时候, 第一个参数就是用来接收线程ID的.

> 此线程ID, **`是 pthread 库维护线程时所使用的唯一标识符`**
>
> 而不是 Linux系统内核 中对于表示线程的PCB 的线程ID. Linux内核中的线程ID, 就是PCB的pid, 是LWP.
>
> Linux内核中的LWP 与 pthread 库维护的线程ID, 是 1对1的关系.
>
> `pthread` 创建一个线程, 操作系统就会对新的PCB 分配一个 LWP, `pthread` 库也会分配一个线程ID 作为库维护线程的唯一标识符

那么线程ID是什么？有什么意义呢？

## 什么是线程ID

进程有进程ID, 即 PID, 是进程在操作系统中的唯一标识符.

而线程也有自己的ID, 通常叫做 TID, 是`线程在操作系统中的唯一标识符`. 一般为 `无符号的长整型(pthread_t)`.

TID, 一般都很大：

```cpp
#include <iostream>
#include <pthread.h>
using std::cout;
using std::endl;

int main() {
    pthread_t tid1;
    pthread_create(&tid1, nullptr, nullptr, nullptr);
    cout << "tid1 = " << tid1 << endl;

    return 0;
}
```

![输出一个线程ID |wide](https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/image-20230415174519962.png)

它为什么这么长呢？

虽然线程ID是一个无符号的长整型, 但 **`实际上线程ID表示的是一个地址`**, 如果我们将 获取到的TID以16进制输出：

![线程ID表示一个地址 |wide](https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/image-20230415174848676.png)

## 如何理解线程ID **

我们通过一定方法获取的线程ID, 除了 表示线程在操作系统中的 `唯一标识` 之外. 实际还 `表示一个地址`.

这个地址是什么呢？

我们通过 `pthread_create()` 创建的线程, 在运行时, `一定会产生一些临时数据：临时变量、函数调用等`

所以说, 其实线程也有自己的栈结构, **`新线程的栈是独立与主线程(进程)的`**.

既然线程存在一个独立的栈结构, 那么这个栈结构是谁创建的呢？又在什么地方呢？

### 线程的管理 **

使用过`pthread` 库的接口, 编译生成的可执行程序. 运行时肯定是需要 `libpthread.so` 动态库的

![ ](https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/image-20230415180303802.png)

我们使用的 `pthread` 库, 是用户级的线程库, 程序运行调用接口时, 会被 `加载到内存` 中, 再 `映射到进程地址空间的共享区` 

![ ](https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/image-20230415182322891.png)

当线程需要调用 `pthread` 库中的接口时, 操作系统就会将磁盘中的动态库加载到内存中, 然后线程就会跳到共享区去找内存加载的动态库代码.

> 进程中的代码一定包含三部分:
>
> 1. 程序编写的代码
> 2. 动态库代码
> 3. 系统内核代码

---

我们知道了 `pthread线程库` 会被加载到内存中并被 `映射到进程地址空间的共享区`

那么, 其实就可以将一个简单的调用了 `pthread线程库` 的进程抽象为这样：

![ ](https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/image-20230415183801160.png)

---

再来思考一个问题, Linux中 **`线程 是操作系统内核来管理的吗？`**

Linux内核层面, 实际上没有线程的概念, 只有轻量级进程. 所以 PCB 是操作系统内核管理的没错.

但线程是操作系统内核管理的吗？`并不是`.

`Linux 内核只有轻量级进程的概念、执行流的概念`. 即使可以模拟出线程, 但是线程也不是Linux内核中存在的概念.

操作系统为用户 `提供了` 创建 子进程、共用进程地址空间进程的接口, 而并 `没有提供` 直接创建、管理线程的接口.

我们使用的线程创建、控制等, 其实是 `pthread` 库 封装了系统关于创建子进程相关接口 而成的库接口.

`pthread` 库中 帮我们实现了从轻量级进程到线程的过程：创建线程栈、分配任务, 以及线程的控制等相关接口.

那么, 说到这里其实可以明白了, 线程不是由操作系统内核管理的, 而是由 `pthread` 库管理的.

操作系统内核为线程的模拟提供了轻量级进程的概念, 而 `pthread` 库则通过轻量级进程和操作系统提供的接口 `实现了我们理解的线程`

我们创建进程, 是操作系统内核代码创建的. 操作系统进行对进程的管理, 实现了PCB.

而我们创建线程, 可以说是 `pthread` 库代码创建的. 那么, 为了方便线程的管理 `pthread` 库代码中也实现了 有关`描述线程属性的结构体`. 

假如, `pthread` 库中实现的描述线程属性的结构体 是`struct thread_struct{}`, 那么此结构体的成员就可以抽象为：

```cpp
struct thread_struct {
    pthread_t tid; 			// 线程ID
    void* stack;			// 线程栈
    ……
}
```

即, `pthread` 库维护有线程的栈、线程的分配等结构. 此结构体也是库维护的：

![ ](https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/image-20230415190851469.png)

描述线程属性的结构体, 会由 `pthread` 库创建并维护

> **`图示的意思是, pthread 库会创建并维护 线程属性的结构体, 而不是说此结构体会存储在库所在代码空间中, 更不是会存储在共享区.`**

介绍到现在, 其实已经可以回答两个问题了：

1. 线程的栈是由谁创建的？我们使用 `pthread_create()` 创建线程, 那么 线程的栈就是就是 `pthread` 库创建的. 因为 `pthread` 库在创建线程的时候, 会创建线程的属性结构体, 结构体内维护由线程栈的信息.

	> 这里介绍一个内容:
	>
	> Linux若使用 `pthread` 库创建线程, 则 `进程地址空间内的栈区` 就是 `主线程的栈区`. 其他`新线程的栈区` 是`在 由pthread库维护的一块空间内 分配维护的`.

2. 我们通过 `pthread` 库获取的线程ID, 表示的地址实际就是一个 描述线程属性的结构体的地址.

	`pthread_t` 到底是什么类型呢？**`取决于实现`**. 对于Linux目前实现的 `NPTL` 实现而言, `pthread_t` 是一个 无符号长整型, 可以用来表示 `pthread` 库 维护线程时的唯一标识符, 也可以用来表示进程地址空间中的一个地址. 此地址就是 描述线程属性的结构体的地址.

> pthread 库实现的线程是在Linux轻量级进程的基础上, 又维护了一些属性实现的.
>
> 即 pthread 库中描述线程属性的结构体应该是直接或间接维护有线程的PCB.

> 对于Linux目前实现的 `NPTL` 实现而言, `pthread_t` 是一个 无符号长整型, 可以用来表示进程地址空间中的一个地址.
>
> 但这种实现方式并不是 POSIX 标准规定的. 所以是不符合 POSIX 标准的. 所以最好不要通过 此线程ID 操作线程的属性. 不然可能会影响代码的可移植性.

## 线程局部存储

`pthread` 库中定义的描述线程的属性的结构体中, 维护有一个特殊区域：`线程局部存储区域`

这个区域的作用, 需要用代码来表现.

我们知道, 进程中的数据, 对线程来说都是可以见的, 全局数据更是所有线程都可以修改.

那么, 先来观察下面这段代码的执行结果：

```cpp
#include <iostream>
#include <unistd.h>
#include <syscall.h>
#include <pthread.h>
using std::cout;
using std::endl;

int global_value = 100;

void* startRoutine(void* args) {
    const char* name = static_cast<const char*>(args);

    while (true) {
        printf("%s: %lu global_value: %d &global_value: %p Inc: %d lwp: %ld\n", 
                name, pthread_self(), global_value, &global_value, --global_value, ::syscall(SYS_gettid));

        sleep(1);
    }

    return nullptr;
}

int main() {
    pthread_t tid1, tid2, tid3;

    pthread_create(&tid1, nullptr, startRoutine, (void*)"thread1");
    pthread_create(&tid2, nullptr, startRoutine, (void*)"thread2");
    pthread_create(&tid3, nullptr, startRoutine, (void*)"thread3");

    pthread_join(tid1, nullptr);
    pthread_join(tid2, nullptr);
    pthread_join(tid3, nullptr);

    return 0;
}
```

执行这段代码：

![所有线程都在修改全局变量](https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/all_thread_inc_globalval.gif)

这段代码的执行结果就是, 我们创建的新线程都在对 global_value 执行`--`操作, 并且可以看到, 不同线程访问的global_value地址都是相同的 会互相影响.

但是, 如果我们在全局变量的定义前, 加一个 `__thread`：

```cpp
__thread int global_value = 100;
```

然后在执行代码：

![](https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/all_thread_inc_thread_globalval.gif)

可以看到一个明显的变化, `不同线程看到的是不同的地址, 实际看到的是不同的数据`.

这就是 `线程局部存储`, `只属于线程自己的局部存储数据`

---

感谢阅读~