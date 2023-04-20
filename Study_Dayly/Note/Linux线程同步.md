---
layout: '../../layouts/MarkdownPost.astro'
title: '[Linux] 线程同步分析'
pubDate: 2023-04-16
description: ''
author: '七月.cc'
cover:
    url: 'https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/image-20230419171853697.png'
    square: 'https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/image-20230419171853697.png'
    alt: 'cover'
tags: ["Linux", "线程", "系统"]
theme: 'light'
featured: false
---

![ ](https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/image-20230419171853697.png)

上一篇文章我们分析了什么是线程互斥, 以及线程互斥的特点和使用.

说白了, 线程互斥就是多线程在争抢使用临界资源, 谁抢到了谁就用, 抢不到的就等.

这样不会因为多线程同时访问临界资源而造成错误. 

虽然没有错误, 但是, 思考另外一个问题：**`这样合理吗？`**

# 只互斥的问题: 饥饿

我们以最极端的例子来分析.

当多线程互斥地争抢临界资源时. 如果存在一部分 `优先级非常高` 的线程, 也存在一部分 `优先级非常低(与高优先级线程存在断层)` 的线程, 其他线程的优先级也不太低. 那么可能会出现什么问题？

假设 高优先级线程A先抢夺到了临界资源, 然后上了互斥锁. 其他线程就只能在临界区外等.

线程A用完临界资源, 解了锁之后. 所有线程又开始抢临界资源、抢锁. 又有线程抢到了临界资源和锁, 也是高优先级的线程.

那么 此线程用完临界资源, 解了锁之后. **`所有线程又会抢临界资源、抢锁. 一直如此.`**

但是, 由于有一部分线程的优先级非常低. 与其他线程的优先级已经出现断层了.

那么, 在这种争抢的机制下, 这部分线程就可能`永远抢不到临界资源`、抢不到锁. 也就`永远无法被调度`, `永远无法分配到资源`.

在这种情况下, 就可能出现 `饥饿 或 饿死` 的问题, 即, **`执行流长时间无法获得某种资源的情况, 被称为饥饿或饿死`**

这种争抢临界资源的机制, 虽然`没有错误`, 但是很可能存在类似的线程饥饿的情况, 所以 是`不太合理`的.

# 线程同步

在线程只使用互斥的方式去访问临界资源时, 就有可能造成线程饥饿的情况.

那么 有没有一种可能, 可以让多线程在访问临界资源时, 还是在某个时刻只能有一个线程访问临界资源. 但是 可以让所有的线程按照一定的顺序访问临界资源.

即, 所有线程像排队一样, 一个一个地访问临界资源. 当一个线程访问完临界资源后, 再重新去队尾排队.

这样就不会出现多线程争夺临界资源地情况, 而可能导致线程饥饿.

确实存在这样的机制, 即 **`在保证临界资源安全的前提下, 让执行流访问临界资源具有一定的顺序性`**, 这种机制被称为`同步`. 也就是本篇文章主要介绍的内容. 

> 虽然同步是指让执行流访问临界资源有一定顺序性的机制, 但是 互斥其实也是同步机制的一种. 
>
> 虽然只采用互斥 执行流访问资源还是乱序的. 但它还是在一定程度上协调了多个线程的执行, 因为 互斥锁可以保证同一时刻 只有一个执行流访问临界资源.
>
> 不过`本篇文章介绍时`会将同步和互斥区别开, 即 `同步不包括互斥`, 不然非常容易混淆.

## 条件变量

同步机制的实现, 一般离不开一个东西：`条件变量`

那么什么是条件变量呢？

条件变量 是一种可以实现线程同步的机制. 通过条件变量, 可以实现让线程有序的访问临界资源.

线程需要访问临界资源时, `有时候如果临界资源不满足一定的条件, 是不允许线程执行一定的操作的`.

比如, 如果线程需要访问一个队列, 但此时队列为空, 那么线程就无法访问, 就必须等待队列中出现新的内容之后, 此线程再访问队列.

而如果 `想要实现 如果某条件不满足时, 需要让线程等待, 并且如果条件满足时, 可以让线程恢复继续执行的机制`, 就需要用到 `条件变量`.

解释了这么多, 究竟什么是条件变量呢？

其实, 代码中的条件变量 与 互斥锁很像. 就是 `pthread`库提供的 一个结构体类型`(pthread_cond_t)`的变量, 并且 `pthread` 库中也提供的操作条件变量的一些接口.

### `cond` 及接口

`cond` 即 `condition`, 是条件的意思.

`pthread_cond_t` 即为 **`定义条件变量的类型`**.

条件变量的使用接口 与 互斥锁基本相似：

![ ](https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/image-20230419184512504.png)

条件变量, 是由 `pthread_cond_t` 类型定义的.

可以通过宏来初始化, 与互斥锁一样, 通过宏初始化的变量 就不需要去手动`destroy`了

也可以通过 `pthread_cond_init()` 接口, 来初始化, 第一个参数是条件变量的地址, 第二个参数是条件变量的属性(可以不考虑).

通过 `init` 接口初始化的条件变量, 在不需要使用时, 需要调用 `pthread_cond_destroy()` 接口进行销毁.

除了这两个接口外. 

还有提供有使用条件变量的接口：

![ ](https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/image-20230419190529442.png)

`pthread_cond_wait()` 是 `pthread` 库提供的 使用条件变量等待的接口. 线程调用此接口, 线程就会立即进入等待.

`pthread_cond_timedwait()` 也是 `pthread` 库提供的 使用条件变量等待的接口, 只不过 此接口是一种定时让线程等待的接口. 即, 可以通过此接口设置一定的时间, 在此时间内让线程等待. 如果此时间内 条件满足了, 则线程会自动被唤醒, 继续执行代码.

这两个接口的参数除了需要条件变量, 还都`需要一个互斥锁`. 从接口就可以反映出来, 条件变量一般是和互斥锁一起使用的. 具体如何一起使用, 由于还没有使用过条件变量, 我们后面再介绍. 

这两个接口, 可以通过条件变量 `让线程等待`.

![ ](https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/image-20230419191343494.png)

有通过条件变量 让线程等待的接口, 就有通过条件变量唤醒线程的接口.

`pthread_cond_signal()`, 调用此接口, 可以让`某个` 通过指定条件变量陷入等待的 `线程被唤醒`.

`pthread_cond_broadcast()`, 调用此接口, 则可以让通过指定条件变量陷入等待的`所有线程唤被醒`

### `cond` 及接口的使用演示

我们介绍了几个有关条件变量的使用接口. 

先来演示一下, 条件变量是如何使用的：

```cpp
#include <iostream>
#include <unistd.h>
#include <pthread.h>
using std::cin;
using std::cout;
using std::endl;

// 定义并初始化全局互斥锁
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
// 定义全局条件变量
pthread_cond_t cond;

void* waitCommand(void* args) {
    pthread_detach(pthread_self()); // 先让线程自己分离自己, 我们就不在主线程中回收线程了
    // 在此例中, 如果不分离, 线程回收会是个问题. 但具体问题后面再解释和解决.
    // 这里我们只是展示一下 接口的最基本的用法和现象
    const char* name = (const char*)args;

    while (true) {
        pthread_cond_wait(&cond, &mutex);
        cout << name << ", tid: " << pthread_self() << ", run……" << endl;
    }

    return nullptr;
}

int main() {
    pthread_cond_init(&cond, nullptr);

    pthread_t tid1, tid2, tid3;
    pthread_create(&tid1, nullptr, waitCommand, (void*)"Thread_1");
    pthread_create(&tid2, nullptr, waitCommand, (void*)"Thread_2");
    pthread_create(&tid3, nullptr, waitCommand, (void*)"Thread_3");
    while (true) {
        char c = 'a';
        cout << "请输入你的命令(N/Q):: ";
        cin >> c;
        if (c == 'N' | c == 'n') {
            pthread_cond_signal(&cond);
        }
        else
            break;
        usleep(1000);       // 让主线程usleep一下, 防止线程之间在屏幕上打印干扰
    }

    pthread_cond_destroy(&cond);
    return 0;
}
```

此代码中, 先定义并初始化了互斥锁 和 条件变量. 然后创建线程, 线程执行的函数会使线程循环由条件变量进入等待.

然后在主线程中通过输入 n 和 N 来调用唤醒函数, 唤醒线程, 观察现象：

![show_cond](https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/show_cond.gif)

在其他线程通过条件变量等待时, 我们在主线程内通过 输入 N 和 n 来唤醒等待的线程.

观察线程的唤醒现象, 其实可以发现 **`线程的唤醒是以一定顺序来执行的`**.

除了 使用 `pthread_cond_signal()` 来单个唤醒等待的线程.

还可以使用 `pthread_cond_broadcast()` 来广播唤醒所有等待的线程：

![使用 broadcast 唤醒所有等待的线程](https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/show_cond_broadcast.gif)

这里演示的是, cond 条件变量的没有场景的用法. 

而我们介绍条件变量时说, 当前有条件不满足时 会使用条件变量让线程等待. 

我们可以设置一个退出条件 quit, 为真时即为满足, 为假时即为不满足

```cpp
#include <iostream>
#include <unistd.h>
#include <pthread.h>
using std::cin;
using std::cout;
using std::endl;

// 定义并初始化全局互斥锁
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
// 定义全局条件变量
pthread_cond_t cond;

// // 定义一个全局退出变量, 用于判断条件
volatile bool quit = false;

void* waitCommand(void* args) {
    pthread_detach(pthread_self()); // 先让线程自己分离自己, 我们就不在主线程中回收线程了
    // 在此例中, 如果不分离, 线程回收会是个问题. 但具体问题后面再解释和解决.
    // 这里我们只是展示一下 接口的最基本的用法和现象
    const char* name = (const char*)args;

    while (!quit) {
        //  不满足退出条件, 就进来等待
        pthread_cond_wait(&cond, &mutex);
        cout << name << ", tid: " << pthread_self() << ", run……" << endl;
    }
    pthread_mutex_unlock(&mutex);       // 暂时不解释 这里解锁的原因
    cout << name << ", tid: " << pthread_self() << ", end……" << endl;

    return nullptr;
}

int main() {
    pthread_cond_init(&cond, nullptr);

    pthread_t tid1, tid2, tid3;
    pthread_create(&tid1, nullptr, waitCommand, (void*)"Thread_1");
    pthread_create(&tid2, nullptr, waitCommand, (void*)"Thread_2");
    pthread_create(&tid3, nullptr, waitCommand, (void*)"Thread_3");
    while (true) {
        char c = 'a';
        cout << "请输入你的命令(N/Q):: ";
        cin >> c;
        if (c == 'N' | c == 'n') {
            pthread_cond_broadcast(&cond);
        }
        else {
            quit = true;			// 修改条件为满足
            pthread_cond_broadcast(&cond); 		// 然后唤醒线程, 再让线程判断条件是否满足
            break;
        }
        usleep(1000);       // 让主线程usleep一下, 防止线程之间在屏幕上打印干扰
    }

    pthread_cond_destroy(&cond);

    return 0;
}
```

这段代码中, 我们随便定义了一个条件 quit. quit 为真时即为满足条件, quit 为假时即为不满足条件.

不满足条件, 就让线程等待. 满足条件就唤醒线程.

我们输入 N 和 n时, 唤醒一下线程让线程在判断一下条件是否满足, **`非 N 和 n 时, 让退出条件被满足, 并唤醒线程`**.

执行结果为：

![ ](https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/show_cond_broadcast_withquit.gif)

这就是条件和条件变量的最简单的使用.

使用条件变量可以让多线程的执行具有一定的顺序性, 即可以实现同步.

而同步和互斥是什么关系呢？

很明显, 是互补的关系.

### 为什么条件变量需要与互斥锁一起使用？

上面展示的例子中, `pthread_cond_wait()` 的使用需要同时用到 条件变量和互斥锁. 

这里为什么需要使用互斥锁呢？

首先, 条件等待是使用条件变量实现同步的一种机制. 如果只有一个线程, 当条件不满足时, 线程就会一直等下去, 因为唯一的线程在等待, 没有其他线程修改条件, 条件也不可能满足.

所以需要一个线程使条件变得满足, 然后再唤醒等待的线程.

这里的`条件`, 其实就是 `线程对应的需要访问的临界资源的状态`. 就像我们介绍互斥时的抢票动作, 需要保证票是>0的 才能抢票.

而, 条件是不可能的无缘无故地没有变化就自己满足的, 所以条件满足势必会存在`临界资源数据的变化`. 所以 需要`用互斥锁来保护临界资源`.

所以, **线程判断条件满足之前 需要`先上锁`, 然后`再判断是否满足`, 如果`不满足` 则`条件等待并解锁`**

**然后 让`其他`可以让条件满足的`线程获取锁`. `条件满足之后`, 再`唤醒`刚才`等待的线程 并 解锁`. **

**让刚`被唤醒的线程再次获取锁 判断条件是否满足`, `满足就去执行操作, 否则再次陷入等待`.**

整个过程的重点就是, **谁需要访问临界资源就上锁, 谁不需要了就解锁**. 即 **`保证整个过程中临界资源是被保护着的`**

而 整个过程中, 除了第一次对临界资源上锁和最后一次对临界资源解锁, 中间所有的上锁和解锁的操作 都是由 `pthread_cond_wait()` 完成的.

在 线程需要等待时要调用 `pthread_cond_wait()` 解锁并等待. 在线程被唤醒时, 会自动再去竞争锁. 解锁和上锁的操作都是在 `pthread_cond_wait()` 接口内部实现的.

这也是为什么, 上面例子中, 我们想让多线程退出时需要在条件满足时先释放锁, 然后再让线程退出. ：

![ |wide](https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/image-20230420121724747.png)

在 `第2行`, 我们让线程分离自己, 不用回收.

在 `第13行`, 我们执行了解锁操作. 因为 `pthread_cond_wait()` 陷入等待时, 会释放锁. 然后被唤醒的时候, 会竞争锁. 如果退出条件满足了. 也就意味着线程将要退出了. 

而 此时 线程是处于对临界资源上了锁的状态. 所以在退出之前要先解锁. 不然后面会出现死锁的状态(如果我们不分离线程的话)：

![ ](https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/cond_exitnounlock_deadlock.gif)

---

那么为什么 `pthread_cond_wait()` 需要条件变量和互斥锁一起使用？

因为 `pthread_cond_wait()` 接口需要执行释放锁和竞争锁的操作. 所以 需要先看到锁.

## 生产者消费者模型介绍 **

生产者消费者模型, 是一种编程模型. 不过如何理解的话, 可以举一个生活中的例子.

> 这里的生产者和消费者, 我们 **`不以生物学的角度`** 看待. 

以生活中的超市为例：

超市是供我们所有人来购买商品的, 那么 可以将我们看作消费者, 以下 `以学生来代表消费者`.

而超市中的商品, 是由工厂供应商来生产供应的, 那么 可以 `将工厂看作生产者`.

那么, 学生购买商品, 工厂供应商品. 其实都是 `通过超市` 这个渠道的.

![ ](https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/image-20230420102219748.png)

---

为什么学生不直接通过工厂来购买商品, 工厂不根据学生的具体需求来生产供应呢？

为什么？来想象一件事情. 有一位学生想要吃一包辣条. 他就直接去了生产辣条的工厂. 

学生说：我想吃一包辣条, 你们给我生产一包. 工厂听到有人需要一包辣条, 就开动机器只生产了一包辣条, 卖给了学生.

这合理吗？很明显不合理啊！

学生想要买一包辣条, 需要先去工厂告诉工厂, 然后等~

工厂听到学生要买一包辣条, 然后就开动机器去制作了一包, 制作完成卖给学生.

这样的成本可太高了吧. 

工厂 为生产一包辣条 机器就开动了, 那这机器、电力等各种损耗一包辣条肯定没法弥补.

还有学生, 像简简单单买包辣条还要告诉工厂, 让工厂现场生产. 这不是浪费时间嘛.

所以, 工厂一般情况下是无法直接与消费者买卖商品的.

---

工厂无法直接与消费者买卖商品, 就可以通过超市这个媒介.

超市因为要供所有的消费者来购买商品, 所以一般需要大量的商品. 这时候 工厂就可以火力全开生产商品了. 而消费者 也可以直接找到现成的商品购买.

那么, 超市的存在 第一个作用就是 `提高了效率`

除此之外, 工厂也不需要直接根据学生的需求再来生产商品. 

假设只要有商品就能卖出去. 那么 工厂就可以不停的生产商品, 为的是给超市供货. 而超市只要保持有商品, 那么 学生过来直接购买就可以了, 也不用再去跟工厂说. 这就把上面例子中 学生与工厂之间的强耦合关系就没有了, 变成了松耦合. 

消费者没有去购买商品, 工厂也可以一直生产. 工厂没有生产商品, 只要超市里有, 消费者也可以直接去购买.

这 也就是超市的第二个作用 `解耦`.

那么, 超市有没有很像 工厂与消费者之间的缓冲区一样的存在？

---

将这样的模型拿到我们编程中, 将 `消费者 看作消费线程`, 将 `生产者 看作生产线程`.

那么, 消费线程需要从超市中拿东西, 生产线程需要向超市中放东西.  超市又可以看做什么呢？

`超市`其实就可以看作是 `临界资源`.

而在生活中, 消费者不可能只有一个, 生产者也不可能只有一个. 

那么：

1. #### 消费者与消费者之间是什么关系？

	消费者与消费者之间好像是没有关系, 你买你的我买我的, 互不干扰. 但是 仔细想一想, `消费者与消费者之间实际是一种 竞争关系`.

	互不干扰是因为商品充足, 如果商品不足的话, 是需要竞争的. 其实是 竞争关系

	而竞争关系, 其实就是 一种 `互斥关系`

2. #### 生产者与生产者之间是什么关系？

	生产者与生产者之间, 其实也是一种竞争关系. 竞争超市内的空间资源. 竞争谁可以给超市供货. 即 `互斥关系`

3. #### 消费者与生产者之间需要什么关系？

	消费者和生产者, 看似是没有之间的关系的. 但是思考一个问题, 既然超市是临界资源. 那么消费者和生产者是可能在同一时间访问临界资源的.

	如果 供应商再给超市供货的时候, 货还没有供完, 货架上的东西还没有放完. 在生活中我们可以直接拿走一个, 然后去超市结账.

	但是如果从计算机的角度来看, 生产线程还没有向临界资源内写完数据, 消费线程可以从临界资源中拿走数据吗？ 很明显是不可以的. 因为 消费线程可能拿不到完整的资源.

	所以, 以计算机的角度来说, 消费者和生产者首先 要`保持`一个`互斥关系`

	而除了互斥之外, 其实还需要 保持`同步`. 

	因为消费者不能在超市没有商品的时候购买商品, 需要等待, 让生产者先向超市供货. 生产者也不能在超市的空间资源已满的情况下继续向超市供货, 需要等待, 让消费者先购买商品. `等到超市有商品了, 再通知消费者来购买. 等到超市有空间了, 再通知生产者来供货.`

**以计算机的角度看待这个生产者消费者模型：**

**生产者消费者模型存在的关系：生产者之间(互斥关系), 消费者之间(互斥关系), 生产者和消费者之间(互斥、同步关系), 共 `3` 类**

**生产者和消费者：线程承担的：`2`种角色**

**超市：为生产者和消费者之间提供缓冲、解耦, 类似 缓冲区、临界资源 的 `1` 个交易场所**

交易场所是让不同的线程之间进行 `"交易"` 的

**即, 可以将生产者消费者模型以这种：`3、2、1`的思想来理解**

而在我们编程中, 就可以围绕这个 `3、2、1` 的模型, 来编写和解决问题. 即, 多线程访问临界资源, 生产线程之间保持互斥、消费线程之间也保持互斥、生产线程和消费线程之间保持互斥、同步. 这样来整理思路, 可以方便解决很多问题.

而最重要的就是. 如何让生产线程和消费线程之间保持互斥和同步.

同步需要根据条件让生产线程和消费线程等待和唤醒. 那么 **`如何让生产线程或消费线程等待？又如何让生产线程和消费线程被唤醒？又如何判断所需条件是否被满足？`**

而 让线程等待和唤醒线程的功能 其实 **`条件变量`** 就可以为我们提供的

### 生产者消费者模型的优点

生产者消费者模型的优点, 可以有三个：

1. 解耦, 可以将两个角色之间的 强耦合关系 变为 松耦合关系.
2. 支持并发.
3. 支持忙闲不均.

这就是生产者消费者模型的优点 

## 以阻塞队列模拟生产者消费者模型 **

阻塞队列：当队列`为空时`, 从队列`获取元素`的操作将会`被阻塞`, 直到队列中被放入了元素; 当`队列满时`, 往队列里`存放元素`的操作也会`被阻塞`, 直到有元素被从队列中取出 (以上的操作都是基于不同的线程来说的，线程在对阻塞队列进程操作时会被阻塞)  

> 阻塞队列的特点像一个管道

我们可以使用阻塞队列, 模拟一个生产者消费者模型.

那么, 阻塞队列的大致结构为：

![|wide](https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/image-20230420151703532.png)

成员变量：

1. `uint32_t _cap` 记录阻塞队列的容量
2. `queue<T> _bq`, 即为阻塞队列本身
3. `_mutex`、`_conCond`、`_proCond` 一个互斥锁, 两个线程分别用的条件变量

构造函数负责初始化容量、互斥锁和条件变量, 析构函数负责摧毁 互斥锁和条件变量

结构定义完成之后, 就需要根据我们需要实现的功能 封装一些私有的成员函数：

上锁、解锁、条件等待、唤醒等待、判空、判满、生产任务、消费任务

![|wide](https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/image-20230420163113768.png)

这些都是私有的接口, 实际还需要两个公共的接口.

完整的从阻塞队列中消费的接口 以及 完整的向阻塞队列中生产的接口:

![|wide](https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/image-20230420163247899.png)

实现了之后, 就可以测试一下了：

`blockQueue.hpp:`

```cpp
#pragma once
#include <iostream>
#include <queue>
#include <pthread.h>
#include <unistd.h>
#include <cstdlib>
using std::queue;
using std::cout;
using std::endl;

const uint32_t gDefultCap = 5;

template <class T>
class blockQueue {
public:
    // 构造函数
    blockQueue(uint32_t cap  = gDefultCap) 
        :_cap(cap) {
        pthread_mutex_init(&_mutex, nullptr);           // 初始化锁
        pthread_cond_init(&_proCond, nullptr);          // 初始化生产线程使用的条件变量
        pthread_cond_init(&_conCond, nullptr);          // 初始化消费线程使用的条件变量
    }
    // 析构函数
    ~blockQueue() {
        pthread_mutex_destroy(&_mutex);
        pthread_cond_destroy(&_conCond);
        pthread_cond_destroy(&_proCond);
    }
    // 生产接口
    void push(const T &in) {
        // 生产的全过程为
        // 1. 上锁
        // 2. 判满. 满不生产 条件等待, 不满则生产.
        // 3. 生产之后, 解锁
        // 4. 唤醒消费接口

        lockQueue();        // 上锁
        while(isFull()) {
            // 满 进入条件等待
            condWait(_proCond);        // 传入生产线程所用的条件变量, 让生产线程等待
        }
        // 不满 则生产
        pushCore(in);
        // 解锁
        unlockQueue();
        condWakeUp(_conCond);          // 传入消费线程所用的条件变量, 唤醒消费线程
    }

    T pop() {
        // 消费的全过程为
        // 1. 上锁
        // 2. 判空. 空则不消费 条件等待, 不空 则消费
        // 3. 消费之后, 解锁
        // 4. 唤醒生产接口

        lockQueue();
        while(isEmpty()) {
            condWait(_conCond);
        }
        T tmp = popCore();
        unlockQueue();
        condWakeUp(_proCond);

        return tmp;
    }


private:
    // 队列上锁
    void lockQueue() {
        pthread_mutex_lock(&_mutex);
    }
    // 队列解锁
    void unlockQueue() {
        pthread_mutex_unlock(&_mutex);
    }
    // 判空
    bool isEmpty() {
        return _bq.empty();
    }
    // 判满
    bool isFull() {
        return _bq.size() == _cap;
    }
    // 条件等待
    void condWait(pthread_cond_t &cond) {
        pthread_cond_wait(&cond, &_mutex);
    }
    // 唤醒等待
    void condWakeUp(pthread_cond_t &cond) {
        pthread_cond_signal(&cond);
    }
    // 生产任务
    void pushCore(const T &in) {
        // 即为向队列中添加任务
        _bq.push(in);
    }
    // 消费任务
    T popCore() {
        // 即从队列中拿出任务
        T tmp = _bq.front();
        _bq.pop();
        return tmp;
    }

private:
    uint32_t _cap;                  // 队列容量
    queue<T> _bq;                   // 阻塞队列
    pthread_mutex_t _mutex;         // 互斥锁
    pthread_cond_t _conCond;        // 消费线程使用的条件变量
    pthread_cond_t _proCond;        // 生产线程使用的条件变量
};
```

`blockQueue.cc:` 

```cpp
#include <iostream>
#include <ctime>
#include "blockQueue.hpp"
using std::cout;
using std::endl;

void* productor(void* args) {
    blockQueue<int>* pBq = static_cast<blockQueue<int>*>(args);
    while (true) {
        // 制作数据
        int data = rand() % 10;
        // 向队列中生产数据
        pBq->push(data);
        cout << "productor 生产数据完成……" << data << endl;
        sleep(2);
    }

    return nullptr;
}

void* consumer(void* args) {
    blockQueue<int>* pBq = static_cast<blockQueue<int>*>(args);
    while (true) {
        int data = pBq->pop();
        cout << "consumer 消费数据完成……" << data << endl;
    }

    return nullptr;
}

int main() {
    // 设置一个随机数种子
    srand((unsigned long)time(nullptr) ^ getpid());
    // 定义阻塞队列
    // 创建两个线程

    blockQueue<int> bq;

    pthread_t pro, con;
    pthread_create(&pro, nullptr, productor, &bq); // 生产线程
    pthread_create(&con, nullptr, consumer, &bq);  // 消费线程

    pthread_join(pro, nullptr);
    pthread_join(con, nullptr);

    return 0;
}
```

我们 使用阻塞队列, 

创建productor生产者 函数, 创建随机数并 `每2s` push入队列中.

创建 consumer消费者 函数, 从队列中取数据, 不做间隔限制. 

执行结果为：

![ ](https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/pro_con_data_test.gif)

productor生产线程 每2s, 生产一个数据. consumer消费线程跟随生产的节奏来消费数据.

如果我们修改一下生产和消费的间隔, 或许更能说明条件变量的作用：

![|wide](https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/image-20230420165209035.png)

消费线程2s一消费, 生产线程1s一生产：

![](https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/pro_con_data_12.gif)

可以看到, 刚开始因为 队列未满, 所以1s生成一个, 顺序为：5 4 3 3 4 0 1 6

而 消费2s一次的顺序为 5 4 3 3.

之后 队列满, 所以 生产数据的速度会跟随消费数据的速度.

---

### 问题1：条件判断的语句

上面我们实现 生产和消费 接口的时候, 我们判断条件是否满足使用的是 `while()` 而不是 `if()` 为什么 ？

首先思考一个问题：当线程被唤醒的时候, 一定代表条件被满足了吗？

即 执行过 `pthread_cond_wait()` 之后, 接着向后执行代码, 一定表示条件已经被满足了吗？

其实`不一定`. 第一种情况就是, 这个函数因为某种情况调用失败了. 调用失败很可能会继续执行之后的代码. 此时 条件很大概率是没有满足的.

其次, 就是 当多线程一起生产或一起消费的时候, 可能也会造成 `伪唤醒` 的情况.

伪唤醒即为条件还未被满足时, 线程被唤醒了.

由于这种情况的存在, 所以,  **`不能只用一个 if() 判断. 唤醒之后  需要再次判断才能保证是否正确的唤醒`**

### 问题2：什么时候唤醒 或者 什么时候解锁？

![ ](https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/image-20230420171705354.png)

我们上面实现的接口, **`队列的解锁是在唤醒线程之前的, 即先解锁, 再唤醒线程`**

那么, **`可不可以 先唤醒线程, 再解锁呢？`**有没有什么影响呢？

其实是没有多少影响的. 我们先解锁, 再唤醒线程. 也就意味着 唤醒线程之前 锁已经准备好了, 线程可以直接竞争锁.

而 如果是先唤醒线程, 再解锁. 其实也就是 线程可以先准备着竞争锁, 等锁被解开之后, 再竞争锁就可以了. 

**`没有数据安全的影响`**

## 理解生产者消费者模型的 `并发`

经过对条件变量的介绍和使用, 以及对生产者消费者模型的介绍和模拟. 

其实我们已经对条件变量 差不多是很熟悉了. 也可以理解 生产者消费者模型的 `解耦` `支持忙闲不均` 的优点.

但是, 我们好像并没有看到, 生产者消费者模型的 `支持并发的这一特点`

消费者从超市消费商品是互斥的, 生产者给超市生产商品也是互斥的. 消费者与生产者也不能同时从超市消费或给超市生产.

`并发` 体现在哪里呢？

我们上面模拟了一个生产者消费者模型, 但是生产数据和消费数据的过程其实并不明显.  因为只有定义和返回 只有一个语句,

下面我们使用另外一个类, 当作阻塞队列的数据类型.

`Task.hpp:`

```cpp
#pragma once
#include <iostream>
#include <string>

class Task {
public:
    Task(int one = 0, int two = 0, char op = 0)
        : elemOne_(one)
        , elemTwo_(two)
        , operator_(op) {}

    // 仿函数定义
    int operator()() {
        return run();
    }

    int run() {
        int result = 0;
        switch (operator_) {
        case '+':
            result = elemOne_ + elemTwo_;
            break;
        case '-':
            result = elemOne_ - elemTwo_;
            break;
        case '*':
            result = elemOne_ * elemTwo_;
            break;
        case '/': 
            // 除0处理
            if (elemTwo_ == 0) {
                std::cout << "div zero, abort" << std::endl;
                result = -1;
            }
            else {
                result = elemOne_ / elemTwo_;
            }
            break;
        case '%': 
            // 除0处理
            if (elemTwo_ == 0) {
                std::cout << "mod zero, abort" << std::endl;
                result = -1;
            }
            else {
                result = elemOne_ % elemTwo_;
            }
            break;
        default:
            std::cout << "非法操作: " << operator_ << std::endl;
            break;
        }

        return result;
    }

    int get(int* e1, int* e2, char* op) {
        *e1 = elemOne_;
        *e2 = elemTwo_;
        *op = operator_;

        return 0;
    }

private:
    int elemOne_;
    int elemTwo_;
    char operator_;
};
```

 `blockQueue.cc:`

```cpp
#include <iostream>
#include <ctime>
#include "blockQueue.hpp"
#include "Task.hpp"
using std::cout;
using std::endl;

const std::string ops = "+-*/%";

// 生产任务接口
void* productor(void* args) {
    blockQueue<Task>* pBq = static_cast<blockQueue<Task>*>(args);
    while (true) {
        // 制作任务
        int elemOne = rand() % 50;
        int elemTwo = rand() % 10;
        char oper = ops[rand() % 4];        // 操作符
        Task t(elemOne, elemTwo, oper);
        // 生产任务
        pBq->push(t);
        cout << "producter[" << pthread_self() << "] " <<
            (unsigned long)time(nullptr) << " 生产了一个任务: " <<
            elemOne << oper << elemTwo << "=?" << endl;
        sleep(1);
    }

    return nullptr;
}

void* consumer(void* args) {
    blockQueue<Task>* pBq = static_cast<blockQueue<Task>*>(args);
    while (true) {
        // 消费任务
        Task t = pBq->pop();
        // 处理任务
        int result = t();
        int elemOne, elemTwo;
        char oper;
        t.get(&elemOne, &elemTwo, &oper);
        cout << "consumer[" << pthread_self() << "] " <<
            (unsigned long)time(nullptr) << " 消费了一个任务: " <<
            elemOne << oper << elemTwo << "=" << result << endl;
    }

    return nullptr;
}

int main() {
    // 设置一个随机数种子
    srand((unsigned long)time(nullptr) ^ getpid());
    // 定义阻塞队列
    // 创建两个线程
    blockQueue<Task> bq;

    pthread_t pro, con;
    pthread_create(&pro, nullptr, productor, &bq); // 生产线程
    pthread_create(&con, nullptr, consumer, &bq);  // 消费线程

    pthread_join(pro, nullptr);
    pthread_join(con, nullptr);

    return 0;
}
```

`blockQueue.hpp` 还是上面的内容.

那么, 这段代码的执行结果：

![ ](https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/pro_con_task.gif)

上面我们实现的代码, 是使用阻塞队列 模拟生产者消费者模型, `生产和消费加减乘除的任务`

---

但是上面这个例子, 好像还是没有表现出 生产者消费者模型对并发的支持. 

依旧是 `消费者从超市消费商品是互斥的, 生产者给超市生产商品也是互斥的. 消费者与生产者也不能同时从超市消费或给超市生产`

那么. 此模型支持并发, 究竟体现在哪里呢？

生产者消费者模型支持并发, 其实`并不是指 消费者和生产者可以并发的向"超市"消费或生产数据`. 

而是指, `生产者制作商品\任务` 、`消费者处理商品\任务` 的这种过程, 其实`是可以并发执行`的.

在上例中, 就是生产者制作任务 和 消费者处理任务的过程 ：

![|wide](https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/image-20230420183123290.png)

虽然 还是不太明显, 但是 多行的语句其实已经可以说明, `制作任务和处理任务的过程其实是需要消耗一定的资源的, 比如时间`.

**并且, 并行的制作任务 在串行的向 队列中生产. 串行的从队列中消费任务, 然后并行的处理任务**.

**向队列中生产任务, 只是将已经制作好的任务 push 入队列的过程. 从队列中消费任务, 只是从队列中将任务 pop 出来的过程.**

**在生产到队列中之前, 还有一个可能会非常漫长的制作任务的过程. 在消费任务之后, 也可能有一个非常漫长的处理任务的过程.**

**制作任务是可以并行制作的, 处理任务也是可以并行处理的, 制作任务和处理任务也是可以并行操作的. 这些过程互不影响 **

也就是说, 生产者消费者模型`支持并发`的情况 `一般`情况下并`不是在临界区`并发, 而是在**`生产前和消费后支持并发`**

生产者消费者模型的`支持忙闲不均`, 同样体现在 `生产前和消费后`的制作和处理上.

## POSIX信号量

`信号量` 也是同步的一种机制.

### 什么是信号量？

那么什么是信号量呢？信号量可以看作是一个计数器. 

以我们生活中的一个例子 来简单的解释一下信号量: 看电影.

如果我们已经有了想要看的电影, 我们去电影院首先要做的事是什么？选放映厅然后选座.

电影院的每一个放映厅的座位都是`有限`的, 不过`每一个空座位都可以被任何人选择`. 

我们要看电影就需要`选座位买票`, `每买一张票选一个座位`, 放映厅内的`空座位就会少一个`.

`买到了电影票`, 实际上就是选了放映厅内指定的座位, 让`空座位减了1`, 即 `预定了放映厅内的座位`. 

那么, 以编程的角度:

就可以将 `放映厅`看作为一个 **`临界资源`**, `每一个座位`都是临界资源的`一小部分资源`, 这`所有的座位`就可以 **`看作是信号量`**. 当有人买票时`选中了座位`, 接下来可选择的座位就少了一个, 可以看作是 **`信号量--`**; 如果有人退票, 就可以看作是 **`信号量++` **

当放映厅里`没有了空座位`, 就表示 **`信号量减到了0`**, 其他人`再想要买票`, 就需要`等有人退票`. 

也就是说, 信号量减1 也就表示着临界资源中的一部分被选中了. 也就表示着之后只能选择临界资源的其他部分.

这样一个看电影选票的例子, 其实就可以很好的解释信号量.

那么, 提问：如果一个放映厅只有一个座位, 也就是说信号量最大为1. 那么 信号量可以表示什么？

`互斥锁！` 如果信号量只有1, 那么此信号量就可以当互斥锁用.

此时, 信号量 1 –> 0 就是上锁的过程. 信号量 0 –> 1 就是解锁的过程.

信号量为1时, 此信号量被称为 **`二元信号量`**

---

上面我们举的例子, 是将放映厅当作了一个临界资源, 每个座位都是临界资源得一部分.

那么, 我们编程中的 **`临界资源也可以分为一小部分一小部分的吗`**？

是可以的.

临界资源分为一小部分一小部分的, 通过 `信号量操作` 来让线程选中. 

另外一个问题：申请信号量, 实际就是对一部分临界资源的申请. 那么 **`如果申请到了信号量, 就表示一定获得了一部分临界资源吗？`**

这个问题的答案也是肯定的. 只要申请到了信号量, 就一定获得了一部分临界资源.
