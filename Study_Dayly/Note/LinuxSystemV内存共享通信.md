System V 是一种操作系统进程间通信的标准. 

System V 给进程间通信指定的标准有三种：

1. System V 消息队列
2. System V 共享内存
3. System V 信号量

本篇文章主要分析介绍 共享内存

# 共享内存

我们知道, **`进程间通信的前提是：先让不同的进程看到同一份资源`**

Linux的管道通信给进程间看到的同一份资源是：管道文件

而 `共享内存 给进程间看到的同一份资源是：物理内存`

## 共享内存原理

Linux操作系统中, 由于进程地址空间的存在, 进程具有独立性

进程的进程地址空间的大致模型是这样的：

<img src="https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/image-20230328180441494.png" alt="image-20230328180441494" style="zoom:80%;" />

在Linux动态库的相关文章中提到过, 动态库在进程运行时是加载到内存中, 再被映射到进程地址空间的共享区的

那么进程所使用的动态库所加载的一块内存其实就可以看作是一块只读共享内存

共享内存进程通信其实就是这个原理.

共享内存进程通信, 其实就是在物理内存中开辟一块可以让所有进程都看到的内存空间.

然后多进程只需要从这块内存空间内读取或写入数据, 就可以达到进程通信的功能：

<img src="https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/image-20230328181610751.png" alt="image-20230328181610751" style="zoom:80%;" />

也就是说, 使用**`共享内存进程间通信的原理就是, 在物理内存中开辟一块共享内存, 然后通过页表将这块物理内存映射到进程地址空间中. 这块物理内存可以被多个进程映射, 所以就可以以此实现进程通信`**

## 共享内存的创建与删除

进程间要通过共享内存实现痛惜, 肯定是是需要先创建一块共享内存的.

创建共享内存和删除贡献内存, Linux操作系统提供的有系统调用

### 共享内存的创建 shmget()

![image-20230328204726605](https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/image-20230328204726605.png)

shmget() 是操作系统提供的`分配共享内存的系统调用`, 需要三个参数：

1. key_t key
2. size_t size
3. int shmflg

> shm 是 share memory 的简写

1. 首先介绍一下 第二个参数: 

	`size_t size`, 此参数传入的是 `需要开辟多大的共享内存`, 单位是 `byte字节`

	系统会按照 `4KB` 为单位开辟空间, 因为系统 I/O 的单位大小就是 `4KB`

	也就是说, size 参数传入 1、1024、2048、4096 时, 系统都会开辟 `4KB`. 当传入 4097 时, 系统就开会开辟 `8KB`

	不过, **`虽然系统会按照 4KB为单位开辟空间, 但实际上能够使用的大小还是 size字节`**

2. 其次是, 第三个参数: 

	`int shmflg`, 此参数传入的是 创建共享内存时的参数, 就像Linux文件操作的open系统调用的 O_WRONLY、O_RDONLY…… 

	此参数, 操作系统提供的最重要的两个宏是: `IPC_CREAT`  `IPC_EXCL``

	`IPC_CREAT`: 传入此宏, 则表示创建一个新的共享内存段. ==若共享内存段已存在, 则获取此内存段. 若不存在, 就创建新的内存段==

	`IPC_EXCL`: 此宏, 必须要与 `IPC_CREAT` 一起用. 传入此宏, 则表示如果==创建的内存段不存在, 则正常创建, 否则返回错误==. 使用这个宏, 可以**`保证此次使用shmget函数成功时, 创建出的共享内存一定是全新的`**

3. 最后介绍, 第一个参数:

	`key_t key`, 此参数其实是传入一个整数. 

	因为 key_t 其实就是整型：<img src="https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/image-20230328221108075.png" alt="image-20230328221108075" style="zoom:67%;" />

	传入的key值, 其实是 `创建的共享内存段在操作系统层面的的唯一标识符`

	共享内存是Linux系统的一种进程通信的手段, 而操作系统中 共享内存段 一定是有许多的, 为了管理这些共享内存段, 操作系统一定会描述共享内存段的各种属性.

	在Linux 操作系统中, 共享内存会被描述为一个结构体, 就像描述进程的task_struct、描述文件的file. 

	描述共享内存的结构体内会维护一个 key值, 表示此共享内存在系统层面的唯一表示符, 此key值一般由用户传入

	也就是 `shmget()` 系统调用的第一个参数 `key_t key`. 

	key值需要表示共享内存的唯一标识符, 所以每块共享内存的key值都需要不同, 也就是说 key 值虽然是用户传入的, 但是 key值 的获取也是需要一定的方法的

	Linux系统也为key值的获取提供了一个系统调用：`ftok()`

	![image-20230328222807427](https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/image-20230328222807427.png)

	pathname 是一个文件的路径, proj_id 则是随意的8比特位的数值

	ftok()执行成功会返回一个 key值, 这个**`key值是由传入文件的 inode值 和 传入的proj_id 值通过一定的算法计算出来的`**

	文件的inode是唯一的, 所以不同的文件计算出的key值, 也会不同

分析完shmget()的参数, 要完整的了解shmget()的作用, 还需要了解其返回值

`shmget()`的返回值：

![image-20230328223740737](https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/image-20230328223740737.png)

若创建共享内存成功, 或找到共享内存, 则返回共享内存id.

此 id 可以让进程找到共享内存, 即可以达成进程通信的前提：让进程看到同一块资源

---

下面这段代码是shmget()的基本的用法：

```cpp
#include <iostream>
#include <sys/ipc.h>
#include <sys/shm.h>
using std::cout;
using std::endl;
using std::cerr;

int main() {
    int key = ftok(".ipcShm", 0x14);
    int shmId = shmget(key, 4096, IPC_CREAT | IPC_EXCL);
    if(shmId == -1) {
        cerr << "shmget error" << endl;
        exit(1);
    }
    
    cout << "shmget success, key: " << key << " , shmId: " << shmId << endl;

    return 0;
}
```

当这段代码执行一次时：

<img src="https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/image-20230328224615468.png" alt="image-20230328224615468" style="zoom:80%;" />

成功一次, 然后再多次执行时：

<img src="https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/image-20230328224647281.png" alt="image-20230328224647281" style="zoom:80%;" />

会发现, 在第一次创建之后, 再次创建就会一直创建失败、创建错误.

这是为什么？

第一次创建共享内存的进程早就退出了, 但是我们再次已相同的key值创建共享内存, 却会创建失败

难道, **`共享内存不会跟随进程的退出而被释放吗？`**

没错, 共享内存并不会随进程的退出而被释放, 也就是说, 创建共享内存的进程退出之后, 共享内存其实时依旧存在在操作系统中的

我们可以在命令行使用 `ipcs -m` 查看操作系统内存在的共享内存：

<img src="https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/image-20230328225149380.png" alt="image-20230328225149380" style="zoom:80%;" />

某key值的共享内存已经存在了, 所以不能再次以相同的key值创建

所以, 之后再创建共享内存的时候, 需要先删除已经创建的共享内存

## 共享内存的删除 ipcrm 和 shmctl()

