---
layout: '../../layouts/MarkdownPost.astro'
title: '[Linux] 线程互斥'
pubDate: 2023-04-16
description: '多线程可以提高程序的并发性和运行效率，充分利用计算机的多核资源. 
但是, 多线程也可能会导致输出混乱、访问共享资源混乱、竞争等问题. 接下来我们就尝试解决这些问题'
author: '七月.cc'
cover:
    url: 'https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/image-20230416122401579.png'
    square: 'https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/image-20230416122401579.png'
    alt: 'cover'
tags: ["Linux", "线程", "系统"]
theme: 'light'
featured: false
---

![ ](https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/image-20230416122401579.png)

多线程可以提高程序的并发性和运行效率，充分利用计算机的多核资源. 前面的几篇文章已经介绍了, Linux线程的基本概念、基本控制等内容.

我们已经看到了多线程可以提升运行效率等. 但是, 也发现了问题, 多线程可能会导致输出混乱、访问共享资源混乱、竞争等问题.

输出混乱只是小问题, 而像访问资源混乱、错误的问题 就比较大了.

# 线程互斥

在正式分析线程互斥之前. 以线程的角度再介绍三个概念, 这三个概念在介绍共享内存时就已经简单的提过.

## 临界资源和临界区

1. 临界资源: 不同执行流都可以看到的同一资源, 就叫做临界资源
2. 临界区: 访问临界资源的代码, 就叫就临界区
3. 原子性: 一个操作, 如果只存在两种状态: 未完成、已完成, 而没有中间状态, 就称这个操作是具有原子性的.

那么, 一下面这段代码为例:

```cpp
#include <iostream>
#include <unistd.h>
#include <pthread.h>
using std::cout;
using std::endl;

int tickets = 10000;

// 查票
void* inqureTicket(void* args) {
    const char* name = static_cast<const char*>(args);

    int cnt = 10;
    while (cnt--) {
        if (tickets > 0) {
            usleep(100000);
            printf("%s: %lu 查到剩余票了, 还有: %d\n",name, pthread_self(), tickets);
            usleep(100000);
        }
        else {
            printf("没有票了\n", name);
            break;
        }
    }

    return nullptr;
}

int main() {
    pthread_t tid1, tid2, tid3, tid4;

    pthread_create(&tid1, nullptr, inqureTicket, (void*)"thread_1");
    pthread_create(&tid2, nullptr, inqureTicket, (void*)"thread_2");
    pthread_create(&tid3, nullptr, inqureTicket, (void*)"thread_3");
    pthread_create(&tid4, nullptr, inqureTicket, (void*)"thread_4");

    pthread_join(tid1, nullptr);
    pthread_join(tid2, nullptr);
    pthread_join(tid3, nullptr);
    pthread_join(tid4, nullptr);

    return 0;
}
```

![cri_res_cri_sec |wide](https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/cri_res_cri_sec.gif)

这段代码中, 临界资源和临界区都是什么？

首先, 票(`tickets`) 可以被所有线程看到, 并访问. 所以 **`票即为临界资源`**.

而 不同线程所执行的回调函数`inquireTicket()`对临界资源进行了访问, 那么 整个回调函数就都是临界区吗？

并不是, 只有访问了临界资源的那一部分代码被称作临界区, 即：

![ ](https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/image-20230416153122980.png)

首先是, `if (tickets > 0)` 访问临界资源, 对临界资源进行了判断.

然后就是 输出了 `tickets` 也对临界资源进行了访问. 

所以, **`这一部分才叫 临界区`**.

## 多线程访问临界资源的问题

多线程访问临界资源时有可能造成错误的.

上面的代码执行之后, 没有发生错误. 是因为我们只是读取了临界资源, 并没有修改临界资源. 

如果我们将代码改为对临界资源的修改, 我们设置回调函数内循环抢票, 知道抢到0张票:

```cpp
#include <iostream>
#include <unistd.h>
#include <pthread.h>
using std::cout;
using std::endl;

int tickets = 10000;

void* grabTicket(void* args) {
    const char* name = static_cast<const char*>(args);

    while (true) {
        if (tickets > 0) {
            usleep(100);
            printf("%s: %lu 抢到票了, 编号为: %d\n", name, pthread_self(), tickets--);
            usleep(100);
        }
        else {
            printf("没有票了, %s: %lu 放弃抢票\n", name, pthread_self());
            break;
        }
    }

    return nullptr;
}

int main() {
    pthread_t tid1, tid2, tid3, tid4;

    pthread_create(&tid1, nullptr, grabTicket, (void*)"thread_1");
    pthread_create(&tid2, nullptr, grabTicket, (void*)"thread_2");
    pthread_create(&tid3, nullptr, grabTicket, (void*)"thread_3");
    pthread_create(&tid4, nullptr, grabTicket, (void*)"thread_4");

    pthread_join(tid1, nullptr);
    cout << "main thread join thread_1" << endl;
    pthread_join(tid2, nullptr);
    cout << "main thread join thread_2" << endl;
    pthread_join(tid3, nullptr);
    cout << "main thread join thread_3" << endl;
    pthread_join(tid4, nullptr);
    cout << "main thread join thread_4" << endl;

    return 0;
}
```

执行这段代码, 你就会发现有可能会出错误:

![抢票出错](https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/grabTickets_error.gif)

可以看到, 线程3抢到了 编号为0的票, 线程4抢到了编号为-1的票. 这两张票 很明显是不应改存在的. 因为, 我们设置的 只有 `tickets > 0` 才会输出 抢到票了, 这句话.

那么为什么会出现这种情况呢？

根据代码, 临界区是：

![ ](https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/image-20230416160134239.png)

这部分代码存在两个计算： `tickets > 0` 和 `tickets--`

造成 线程抢到负票, 其实就是因为 `tickets > 0` 计算时发生了一些错误.

> 代码中有关算数计算的问题, 都是交给CPU执行的.
>
> 无论是 `+ - * /` 还是 `逻辑运算` 还是 `逻辑判断`. 最终, `CPU 都会通过 ` **`位移运算`**  和 **` 加法运算 `** `来解决`

这个判断的过程时如何发生错误的呢？

当 需要进行判断的时候, CPU 会将判断这个操作分成至少3步来进行：

1. CPU读取判断并放入寄存器中
2. CPU执行数据判断
3. CPU将判断结果返回到代码中

那么, 当 `tickets 为 1`, 且 `线程1` 进行判断时, 正常的情况是这样的:

![ ](https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/image-20230416163216043.png)

> CPU 进行逻辑判断, 其实是通过 判断式子, 计算出一个真值或假值, 进而返回到 判断语句中.
>
> 例如, 此例中 tickets = 1, 判断 `tickets > 0`, CPU 就可能 计算 `1 + -0` 的结果, 然后将结果返回到 判断语句中

此时, 判断的结果肯定是真, 所以会执行抢票语句, 然后 `tickets--`.

这是正常的情况, 那么 如果出现其他情况呢？

还是在 `tickets = 1` 时, 线程 1 需要进行判断, 但是 CPU计算完成之后, 还没有将结果返回给线程1的代码中, 却需要调度线程2了.

然后 操作系统将CPU计算的结果保存到线程1的上下文数据中, 线程1 暂停运行:

![ ](https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/image-20230416165843159.png)

然后 线程2被调度 运行需要进行判断, 现在 `tickets 依旧为1`, 然后 CPU 根据 tickets 为1进行计算, 计算完成之后, 还没有将结果返回给线程2代码中, 又需要调度线程3了.

然后 操作系统又将 CPU计算的结果保存到线程2的上下文数据中, 线程2 暂停运行:

![ ](https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/image-20230416170346077.png)

然后 线程3被调度 运行需要进行判断, 现在的 `tickets 还是1`, 然后CPU 根据tickets为1进行计算, 计算完成之后, 正常将结果返回给了线程3的代码中, 此时 tickets为1, 所以 判断结果肯定为真, 所以线程3 执行抢票操作 `tickets--`, `tickets 变为 0`. 线程3抢到 `编号为1` 的票:

![ ](https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/image-20230416171227547.png)

然后 线程1又被调度, 操作系统恢复线程1的上下文数据, 上次已经计算出了结果, 所以该将线程1上下文数据中保存的上次CPU计算逻辑判断结果返回到代码中, 由于是根据 tickets为1 计算的, 所以结果为真, 此时 线程1 也会执行抢票操作 `tickets--`, `tickets 变为 -1`. 线程1抢到 `编号为0`的票:

![ ](https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/image-20230416172150514.png)

然后 线程2又被调度, 操作系统恢复线程2的上下文数据, 将结果返回到代码中, 结果也是由 tickets 为1 计算的, 所以结果为真. 线程2也会执行抢票操作 `tickets--`, `tickets 变为 -2`. 线程2 抢到 `编号为-1` 的票.

> 线程2的再次调度, 与线程1再次调度的步骤相似, 不再画图演示

由于CPU在执行线程的判断计算时, 突然因为某种情况需要调度其他线程, 就可能会造成最终判断错误的情况.

> 而 如果是执行 `tickets--` 时发生这种情况, 就有可能对票的数量修改混乱
>
> 很可能出现这样的情况: 
>
> 线程1 执行完 `tickets--` 结果是 9999, 但是需要调度其他线程, 所以需要将 9999 存储到线程1的上下文数据中.
>
> 结果, CPU一直在调度其他线程, 票数实际已经被抢到了 5622. 但此时, 如果继续回去调度线程1, CPU就不会再计算, 而是恢复线程1的上下文数据, 然后发现已经计算过了, 就会直接将 9999 返回到线程1的代码中, 就会对全局变量作出修改. 将 5622 改为 9999.
>
> 此时 票的数量就会发生混乱.

然而会造成这种结果的原因是什么？ 

1. 无论 `tickets > 0` 还是 `tickets--` 这 **`两个计算操作都不是原子的`**

	这两个操作都具有中间状态, 即 CPU计算的过程需要读取、计算、返回多个操作. 存在中间状态, 就有可能在处于中间状态的时候 暂停 然后其他线程访问同一个数据.

	如果, 这两个操作都是原子性的, 根本不存在什么中间状态, 就不会再造成这种情况

2. 在已经有一个线程访问临界资源的时候, 其他线程依旧可以访问临界资源.

有关操作的原子性, 本篇文章暂不涉及.

本片文章会从第二个原因入手, 解决上面的线程数据不安全的问题.

## mutex互斥量

第二个原因是: 在已经有一个线程访问临界资源的时候, 其他线程依旧可以访问临界资源

那么要解决这个问题, 其实就是需要达成这三点:

1. 代码必须要有互斥行为：当代码 `进入临界区` 执行时，`不允许其他线程进入该临界区`
2. 如果多个线程同时要执行临界区的代码，并且临界区没有线程在执行，那么`只能允许一个线程进入该临界区`
3. 如果线程 `不在临界区中` 执行，那么该线程 `不能阻止其他线程进入临界区`

这三个要求其实`核心宗旨`只有一个, 即 **`给临界区加一把锁`**！  

当有线程进入临界区的时候, 就给临界区上一把锁, 阻止其他线程进入临界区. 这种锁, 被称为 `互斥锁`. 给代码实现互斥效果

那么, 如何给代码上锁和解锁呢？

### 锁的接口

pthread 库为我们提供了 "造锁/买锁"、"改锁"、"上锁"、"解锁"、"毁锁/卖锁" 的接口:

`定义一个锁(造锁):`

![ ](https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/image-20230416181735071.png)

我们可以像定义变量一样, 使用 `pthread_mutex_t mutex;` 来定义一个互斥锁. 当然, 锁名可以随便设置.

此锁, 即为`互斥量`

> 互斥锁的类型 `pthread_mutex_t` 是一个联合体.

`初始化锁(改锁):`

![ ](https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/image-20230416182201905.png)

`pthread_mutex_init()` 是 pthread 库提供的初始化锁的接口, 第一个参数传入的就是需要初始化的锁的地址.

第二个参数需要传入锁初始化的属性, 在接下来的使用中暂时不考虑.

成功返回0, 否则返回错误码.

`摧毁锁:`

![ ](https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/image-20230416182556253.png)

`pthread_mutex_destroy()` 用来摧毁定义的锁, 传入锁的指针.

成功返回0, 否则返回错误码.

`上锁:`

`pthread` 库为用户提供了, 两种不同的上锁方式：

![ ](https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/image-20230416183336540.png)

`pthread_mutex_lock()`, 阻塞式上锁. 即 线程执行此接口时, 指定的锁已经被锁上了, 那么线程就进入阻塞状态, 知道解锁之后 此线程再上锁.

`pthread_mutex_trylock()`, 非阻塞式上锁. 即 线程执行此接口时, 尝试上锁, 如果指定的锁已经被锁上, 那么线程就先不上锁, 先去执行其他代码.  

上锁接口即为抢锁的接口, 哪个线程可以抢到, 哪个线程就能进入被锁上的区域.

这两个接口, `一般用于 进入临界区之前`

当上锁成功, 则返回0, 否则返回一个错误码.

`解锁:`

![ ](https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/image-20230416184136095.png)

`pthread_mutex_unlock()` 解锁接口, `一般用于出临界区的时候`

当解锁成功, 返回0, 否则返回一个错误码.

---

上面介绍了 `pthread` 库提供的互斥锁, 以及锁的一些接口.

现在我们来使用以下锁.

首先, 锁是需要定义的, 而且需要被可以抢占锁的线程看到.

所以, 我们可以定义一个全局的锁, 然后在主线程内初始化:

```cpp
#include <iostream>
#include <unistd.h>
#include <pthread.h>
using std::cout;
using std::endl;

int tickets = 10000;
pthread_mutex_t mutex;		// 定义锁

void* grabTicket(void* args) {
    const char* name = static_cast<const char*>(args);

    while (true) {
        pthread_mutex_lock(&mutex);     // 在即将进入临界区时加锁
        if (tickets > 0) {
            usleep(100);
            printf("%s: %lu 抢到票了, 编号为: %d\n", name, pthread_self(), tickets--);
            usleep(100);
            pthread_mutex_unlock(&mutex);   // 在即将离开临界区时解锁
        }
        else {
            printf("没有票了, %s: %lu 放弃抢票\n", name, pthread_self());
            break;
        }
    }

    return nullptr;
}

int main() {
    pthread_mutex_init(&mutex, nullptr); 		// 初始化锁

    pthread_t tid1, tid2, tid3, tid4;

    pthread_create(&tid1, nullptr, grabTicket, (void*)"thread_1");
    pthread_create(&tid2, nullptr, grabTicket, (void*)"thread_2");
    pthread_create(&tid3, nullptr, grabTicket, (void*)"thread_3");
    pthread_create(&tid4, nullptr, grabTicket, (void*)"thread_4");

    pthread_join(tid1, nullptr);
    cout << "main thread join thread_1" << endl;
    pthread_join(tid2, nullptr);
    cout << "main thread join thread_2" << endl;
    pthread_join(tid3, nullptr);
    cout << "main thread join thread_3" << endl;
    pthread_join(tid4, nullptr);
    cout << "main thread join thread_4" << endl;

    return 0;
}
```

我们定义了一个全局锁, 以保证所有线程都可以使用. 

我们在回调函数即将进入临界区的时候上锁, 在即将出临界区的时候解锁. 

然后查看代码的执行结果：

![ ](https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/mutex_use_show.gif)

可以看到, 抢票的过程是非常和谐的. `没有发生数据错误`的问题. 

但是, 票被抢完之后, 你会发现, `整个进程卡住了`. 这是为什么？

在`没有上锁`的时候, 整个代码是可以`正常运行`的. 所以 `一定是锁的问题`.

我们在即将进入临界区的时候, 上锁了. 也在即将出临界区的时候解锁的. 应该是没问题的.

不过真的是这样吗？

如果票被抢完了, 最后一次执行判断语句, 会进到 哪个控制块中呢？ 是 if后 还是else后？

我们`在if后的控制块中解锁`了, 但是并 **`没有在else后的控制块中解锁`**. 那么 `最后一次票数判断之后, 就会直接退出线程`.

那么此时在推出线程的时候, 并 **`没有对已经上了的锁进行解锁`**. 

而我们知道, 我们使用的 `pthread_mutex_lock()` 是阻塞式上锁的. 如果执行的时候, 指定的锁已经被锁上了, 那就会阻塞式等待, 线程就会暂停运行.

而 对指定锁上锁的线程已经退出了, 并且没有解锁. 所以其他线程会因为阻塞时等待而一直暂停运行.

所以, 是将我们还需要在else后的控制块中进行解锁：

![ ](https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/image-20230416233736687.png)

此时, 我们再执行代码：

![ ](https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/mutex_use_success.gif)

可以看到, 票抢到很和谐, 而且线程退出的也很正常.

但是, 也可以发现, 加了锁之后 整个进程的运行速度要满了许多. 因为要不停的上锁加解锁. 再加上 我们在 if后 的控制块中使用了 两个usleep(100). 
