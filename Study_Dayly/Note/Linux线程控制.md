---
layout: '../../layouts/MarkdownPost.astro'
title: '[Linux] 多线程控制分析'
pubDate: 2023-04-11
description: ''
author: '七月.cc'
cover:
    url: ''
    square: ''
    alt: 'cover'
tags: ["Linux", "线程", "系统"]
theme: 'light'
featured: false
---





Linux系统中, 线程是轻量级的进程. 我们已经介绍过了线程的相关概念, 见过了线程再Linux操作系统中的存在形式.

我们知道, 进程有自己相关控制接口, 等待、创建等

而线程作为轻量级的进程, 其实也是有控制接口的.

# 线程控制

在介绍线程的相关概念的时候, 我们简单的演示了一下, 线程的创建和回收. 以及使用ps命令 展示了操作系统中正在运行的线程.

## 线程的创建与回收演示

使用 `pthread_create()` 和 `pthread_join()` 两个接口来创建和回收线程已经演示过了：

```cpp
#include <iostream>
#include <string>
#include <pthread.h>
#include <unistd.h>
using std::cout;
using std::endl;
using std::string;

void* callBack1(void* args) {
    string str = (char*)args;
    while (true) {
        cout << str << ": " << getpid() << " " << endl;
        sleep(1);
    }
}

int main() {
    pthread_t tid1;

    pthread_create(&tid1, nullptr, callBack1, (void*)"thread_1");

    while (true) {
        cout << " 主线程运行: " << getpid() << " " << endl;
        sleep(1);
    }

    pthread_join(tid1, nullptr);

    return 0;
}
```

![ |wide](https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/thread_show_2023-4-14.gif)

这段代码的执行结果, 是两个线程同时运行.

`pthread_create()` 的使用并不复杂, 只需要接收线程id, 并指定线程需要执行的回调函数 和 参数就可以了.

而`pthread_join()` 这个回收线程的函数也不复杂. 只不过 此函数的第二个参数是一个 `二级指针`.

```cpp
int pthread_join(pthread_t thread, void** retval);
```

`void** retval` 参数是一个输出型参数, 是用来接收数据的.

不过为什么, retval是一个二级指针的类型呢？

其实原因很简单, 因为我们在使用 `pthread_create()` 接口创建线程的时候, 给线程指定的回调函数的返回值是 `void*` 类型的.

而 `pthread_join()` 的作用是回收线程, 既然要回收线程那么就一定要接收到线程运行的结果, 即 **`需要接收 线程执行的回调函数的返回值`**.

函数的参数要接收一个指针类型的内容, 就是要用二级指针来接收.

即, `pthread_join()` 接口的第二个参数, 实际上可以接收线程执行的回调函数的返回值.

我们可以使用下面这段代码测试一下：

```cpp
#include <iostream>
#include <string>
#include <pthread.h>
#include <unistd.h>
using std::cout;
using std::endl;
using std::string;

void* callBack1(void* args) {
    string str = (char*)args;
    int cnt = 5;
    while (cnt) {
        cout << str << ": " << getpid() << " " << endl;
        sleep(1);
        cnt--;
    }

    return (void*)"thread_1 is over";
}

int main() {
    pthread_t tid1;

    pthread_create(&tid1, nullptr, callBack1, (void*)"thread_1");

    void* ret = nullptr;
    pthread_join(tid1, &ret);

    cout << "main thread join thread_1 , ready to print thread_1 ret" << endl; 

    sleep(2);
    cout << (char*)ret << endl;
    
    return 0;
}
```

这段代码的执行结果是：

![thread_join_retval](https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/thread_join_retval.gif)

可以看到, 我们输出传入 join接口的参数, 得到的结果是 thread_1 执行的回调函数的返回值.

---

`pthread_create()` 和 `pthread_join()` 这两个接口的使用都不算困难.

其实这两个接口都不是系统调用, 而是`第三方库 pthread` 中的接口. 不过虽然他们不是系统调用, 却胜似系统调用. 因为 Linux中其实是必须装载这个库的.

这两个不是系统调用, Linux操作系统提供的真正的系统调用是什么呢？

Linux操作系统的线程是轻量级进程, 也就是说 Linux其实并没有提供创建线程的系统调用, 因为根本就没有独立的线程这个概念.

所以, Linux操作系统给我们提供的创建线程的系统调用接口：

`vfork():`

![ ](https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/image-20230414175827070.png)

这个系统调用接口是用来创建与父进程共享进程地址空间的子进程的, 其实就是一个线程.

`clone():`

![ ](https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/image-20230414175621677.png) 

还有`clone()` 系统调用. 这个接口作用是创建一个子进程来模拟线程. 

不过看参数就可以看出来这个函数, **`太麻烦了！`**

还需要自己定义方法, 自己定义一个子进程的栈(线程栈)等内容. 

这个接口是为了更加细粒度的定制创建一个线程. 就是太麻烦了. 非常的麻烦. 看看就好.

我们更常用的还是 pthread库中的接口, `pthread_create`等

## 获取线程id

`pthread_create()` 接口的第一个参数是一个输出型参数, 其实就是为了接收线程id的.

也就是说, 创建完线程之后 其实就已经得到了创建的线程的id：

```cpp
#include <iostream>
#include <string>
#include <pthread.h>
#include <unistd.h>
using std::cout;
using std::endl;
using std::string;

void* callBack1(void* args) {
    string str = (char*)args;
    int cnt = 5;
    while (cnt) {
        cout << str << ": " << getpid() << " " << endl;
        sleep(1);
        cnt--;
    }

    return (void*)"thread_1 is over";
}

int main() {
    pthread_t tid1;

    pthread_create(&tid1, nullptr, callBack1, (void*)"thread_1");

    cout << "thread_1 id: " << tid1 << endl;

    while (true) {
        cout << " 主线程运行: " << getpid() << " " << endl;
        sleep(1);
    }

    return 0;
}
```

![thread_id](https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/thread_id.gif)

代码的执行结果显示, 线程的id是一个非常长的数值. 我们暂时不考虑其有什么含义.

上面这种方法是通过创建线程时接收到的id 来获取线程id.

除此之外, pthread 还提供了一个获取线程自己id的接口: `pthread_self()`

### `pthread_self()` 获取线程id

![ ](https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/image-20230414181551428.png)

此接口作用是：获取调用此接口的线程的ID, 并作为返回值返回.

那么, 我们就可以定义一个函数, 来输出哪个线程和此线程的ID.

```cpp
#include <iostream>
#include <string>
#include <pthread.h>
#include <unistd.h>
using std::cout;
using std::endl;
using std::string;

void printTid(const char* threadName, const pthread_t &tid) {
    cout << threadName << " is runing, " << "tid: " << tid << endl;
}

void* callBack1(void* args) {
    char* threadName = (char*)args;
    int cnt = 5;
    while (cnt) {
        printTid(threadName, pthread_self());
        sleep(1);
        cnt--;
    }

    return (void*)"thread_1 is over";
}

int main() {
    pthread_t tid1;

    pthread_create(&tid1, nullptr, callBack1, (void*)"thread_1");

    while(true) {
        cout << "主线程运行: " << getpid() << endl;
        sleep(1);
    }

    pthread_join(tid1, nullptr);

    return 0;
}
```

代码的执行结果为：

![pthread_self](https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/pthread_self.gif)

线程成功获取了自己的ID

## 线程的状态

Linux中 **`不能使用ps像查看进程状态那样细致的查看线程的状态`**.

不过还是可以简单的判断一下的.

对于线程, 如果线程退出了但是没有回收, 线程会怎么样呢？

```cpp
#include <iostream>
#include <string>
#include <pthread.h>
#include <unistd.h>
using std::cout;
using std::endl;
using std::string;

void printTid(const char* threadName, const pthread_t &tid) {
    cout << threadName << " is runing, " << "tid: " << tid << endl;
}

void* callBack1(void* args) {
    char* threadName = (char*)args;
    int cnt = 5;
    while (cnt) {
        printTid(threadName, pthread_self());
        sleep(1);
        cnt--;
    }
    cout << "thread_1 is over" << endl;

    int* ret = new int(123);
    return (void*)ret;				// 返回一个堆区数据 123
}

int main() {
    pthread_t tid1;

    pthread_create(&tid1, nullptr, callBack1, (void*)"thread_1");
    
    sleep(15);  // 等15s，让thread_1运行完

    void* ret = nullptr;
    pthread_join(tid1, &ret);
    cout << "main thread join thread_1 , ready to print thread_1 ret" << endl;
    
    sleep(2);

    cout << "print thread_1 ret: " << *((int*)ret) << endl;
    delete (int*)ret; 		// 释放堆区数据

    return 0;
}
```

我们可以使用命令行监控脚本, 然后在执行这段代码.

```shell
// 监控线程脚本
while :; do ps -aL |head -1 && ps -aL |grep myThread |grep -v grep; sleep 1; done;
```

![线程退出之后, 但还未join](https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/thread_over_beforejoin.gif)

执行和监控结果是, 当`线程退出`但还未被回收时, 线程`会立刻从ps打印的列表中消失`.

这说明什么呢？能说明 线程会被操作系统自动回收, 我们不用join吗？ 

不能, 因为ps终究只是一个软件. 没有证据可以证明 线程退出之后会被立刻回收, 不用手动回收.

事实也的确如此, **`线程退出之后, 并不是自动回收的, 如果不手动join, 就可能会造成类似进程不回收一般的内存泄漏问题`**

---

### 线程与进程共享信号处理方法

线程和进程是共享信号处理方法的. 这个概念在上一篇线程概念的文章中就已经提到过, 但是没有演示.

在本篇文章中, 我们可以演示一下这个特点.

```cpp
#include <iostream>
#include <string>
#include <pthread.h>
#include <unistd.h>
using std::cout;
using std::endl;
using std::string;

void printTid(const char* threadName, const pthread_t &tid) {
    cout << threadName << " is runing, " << "tid: " << tid << endl;
}

void* callBack1(void* args) {
    char* threadName = (char*)args;
    while (true) {
        printTid(threadName, pthread_self());s
        sleep(1);
     }
}

int main() {
    pthread_t tid1;

    pthread_create(&tid1, nullptr, callBack1, (void*)"thread_1");

    while(true) {
        printTid("main thread", pthread_self());
        sleep(1);
    }
}
```

![Thread_Shared_SIG](https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/Thread_Shared_SIG.gif)

我们向进程发送19信号, 所有线程都会暂停运行.

我们向进程发送一个18信号, 所有线程又会恢复运行.

> ps列表中, 表示进程状态的一栏 `l` 即表示 存在轻量化进程, 即多线程进程
>
> `+` 表示前台进程

#### 线程异常

线程异常会影响整个进程, 原因是线程异常影响的是整个进程的代码和数据.

所以, 如果线程异常 则整个进程都会异常

```cpp
#include <iostream>
#include <string>
#include <pthread.h>
#include <unistd.h>
using std::cout;
using std::endl;
using std::string;

void printTid(const char* threadName, const pthread_t &tid) {
    cout << threadName << " is runing, " << "tid: " << tid << ", pid: " << getpid() << endl;
}

void* callBack1(void* args) {
    char* threadName = (char*)args;
    int cnt = 5;
    while (true) {
        printTid(threadName, pthread_self());
        sleep(1);
        cnt--;
        if(cnt == 0) {
            int i = 1;
            i /= 0;
            // 段错误
            //int* pi = nullptr;
            //*pi = 123;
        }
     }
}

int main() {
    pthread_t tid1;

    pthread_create(&tid1, nullptr, callBack1, (void*)"thread_1");

    while(true) {
        printTid("main thread", pthread_self());
        sleep(1);
    }
    return 0;
}
```

![thread_error_float](https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/thread_error_float.gif)

![thread_error_segmentation](https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/thread_error_segmentation.gif)

当线程出现不同的异常, 会影响进程的终止.

这其实是线程的 **`健壮性较低`**

>  不过这其实还是因为出bug了. 

## 线程退出

介绍进程时, 我们分析进程退出存在三种情况：

1. 代码跑完, 结果正确, 正常退出
2. 代码跑完, 结果不正确, 正常退出
3. 代码没跑完, 进程异常退出

其实线程也是一样的, 线程退出也分为这三种.

其实, 这三种情况可以统称为 **`执行流的退出情况`**

在父子进程中, 子进程退出不论是正常退出还是异常退出, **`都会向父进程发送退出信息`**.

而 线程中, 只有线程正常退出且回收时, 主线程可以接收到线程的退出信息. 

那么, 为什么线程异常时 主线程不会接收到来自线程的退出信息？

答案其实很简单, 因为`线程异常`, 也就是`进程异常`, `进程也会随之退出. 接不接受线程的退出信息已经没有意义了`

---

以正常退出的情况来说, 除了回调函数内 return.

线程退出还可以使用接口退出.

### `pthread_exit()`

![ ](https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/image-20230414224857631.png)

`pthread_exit()` 接口也是 pthread 库提供的, 作用就是 `以指定的退出信息使线程退出`.

```cpp
#include <iostream>
#include <string>
#include <pthread.h>
#include <unistd.h>
using std::cout;
using std::endl;
using std::string;

void printTid(const char* threadName, const pthread_t &tid) {
    cout << threadName << " is runing, " << "tid: " << tid << ", pid: " << getpid() << endl;
}

void* callBack1(void* args) {
    char* threadName = (char*)args;
    int cnt = 5;
    while (true) {
        printTid(threadName, pthread_self());
        sleep(1);
        cnt--;
        if(cnt == 0) {
            pthread_exit((void*)123);
        }
     }
}

int main() {
    pthread_t tid1;

    pthread_create(&tid1, nullptr, callBack1, (void*)"thread_1");
    sleep(10);

    void* ret = nullptr;
    pthread_join(tid1, &ret);
    cout << "main thread join thread_1 , ready to print thread_1 ret" << endl;
    sleep(2);
    cout << "print thread_1 ret: " << (long long)ret << endl;
    
    return 0;
}
```

![pthread_exit](https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/pthread_exit.gif)

### `pthread_cancel()`

![ ](https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/image-20230414230626158.png)

`pthread_cancel()` 接口可以向指定的线程发送取消请求. 

此接口可以**`同一进程内, 任意线程调用并向任意线程发送`**. 即, 可以在主线程中调用向新线程发送请求. 也可以自己想自己发送请求

并且, 如果线程是被取消的, 那么此线程的退出信息就是-1.

```cpp
#include <iostream>
#include <string>
#include <pthread.h>
#include <unistd.h>
using std::cout;
using std::endl;
using std::string;

void printTid(const char* threadName, const pthread_t &tid) {
    cout << threadName << " is runing, " << "tid: " << tid << ", pid: " << getpid() << endl;
}

void* callBack1(void* args) {
    char* threadName = (char*)args;
    //pthread_t tid = (pthread_t)args; 			// 这里如果想要向主线程发送取消请求, 则args需要是主线程的id
    int cnt = 5;
    while (true) {
        printTid(threadName, pthread_self());

        sleep(1);
        cnt--;
        if(cnt == 0) {
            // pthread_cancel(tid); 						// 新线程向主线程发送取消请求
            // pthread_cancel(pthread_self());			// 新线程向自己发送取消请求
            pthread_exit((void*)123);
        }
     }
}

int main() {
    pthread_t tid1;

    pthread_create(&tid1, nullptr, callBack1, (void*)"thread_1");
    sleep(2);
	 pthread_cancel(tid1); 						// 主线程向新线程发送取消请求
   	cout << "main thread cancel thread_1" << endl;

    void* ret = nullptr;
    pthread_join(tid1, &ret);
    cout << "main thread join thread_1 , ready to print thread_1 ret" << endl;
    sleep(2);
    cout << "print thread_1 ret: " << (long long)ret << endl;

    return 0;
}
```

首先是, `主线程向新线程发送取消请求`：

![thread_cancel_main2new](https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/thread_cancel_main2new.gif)

新线程被取消 退出, 退出信息为-1. 即为 取消退出.

即 主线程是可以向新线程发送取消信号的. 但是 有可能发生错误. 

我们上述代码中, 向新线程发送取消信号的动作 是在创建新线程2s之后执行的.

如果将那2s的暂停取消(主线程中, cancel动作前的 sleep(2))：

![thread_cancel_main2new_error](https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/thread_cancel_main2new_error.gif)

可以发现, 线程、进程都不正常的退出了.

然后是, `新线程向自己发送信号`：

```cpp
#include <iostream>
#include <string>
#include <pthread.h>
#include <unistd.h>
using std::cout;
using std::endl;
using std::string;

void printTid(const char* threadName, const pthread_t &tid) {
    cout << threadName << " is runing, " << "tid: " << tid << ", pid: " << getpid() << endl;
}

void* callBack1(void* args) {
    char* threadName = (char*)args;
    //pthread_t tid = (pthread_t)args; 			// 这里如果想要向主线程发送取消请求, 则args需要是主线程的id
    int cnt = 5;
    while (true) {
        printTid(threadName, pthread_self());

        sleep(1);
        cnt--;
        if(cnt == 0) {
            // pthread_cancel(tid); 						// 新线程向主线程发送取消请求
            pthread_cancel(pthread_self());			// 新线程向自己发送取消请求
            // pthread_exit((void*)123);
        }
     }
}

int main() {
    pthread_t tid1;

    pthread_create(&tid1, nullptr, callBack1, (void*)"thread_1");
    //sleep(2);
	 //pthread_cancel(tid1); 						// 主线程向新线程发送取消请求
   	//cout << "main thread cancel thread_1" << endl;
	 
    sleep(10);
    
    void* ret = nullptr;
    pthread_join(tid1, &ret);
    cout << "main thread join thread_1 , ready to print thread_1 ret" << endl;
    sleep(2);
    cout << "print thread_1 ret: " << (long long)ret << endl;

    return 0;
}
```

