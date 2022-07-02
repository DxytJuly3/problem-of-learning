# 什么是 Linux

​	Linux 是一款基于`	 GNU 通用公共许可协议` 的 `自由和开放源代码` 的类UNIX操作系统，该操作系统的内核由 Linus Torvalds 在1991年首次发布。之后，在加上用户空间的应用程序之后，就成为了Linux操作系统。  但是，严格来讲， Linux只是操作系统内核，但通常采用 “Linux内核” 来表达该意思。而 Linux 则常用来指基于Linux内核的完整操作系统，它包括GUI组件和许多其他实用工具。  

上面提到两个词——`GNU 通用公共许可协议` 和 `开放源代码(开源)`，这两个词是什么意思呢？

1. `GNU通用公共许可协议`（GNU General Public License，简称`GNU GPL`或`GPL`），是一个广泛被使用的自由软件许可协议条款， `GPL`给予了计算机程序自由软件的定义， 任何基于`GPL`软件开发衍生的产品在发布时必须采用`GPL`许可证方式，且必须`公开源代码`
2. `开源`，其实从字面意思就可以理解：`开放源代码、公开源代码`，即在协议条件允许的情况下，任何人都可以研究、修改、发布源代码

​	而 Linux 是基于`GNU 通用公共许可协议`发布的，只要符合相应的许可条件，任何人都可以运行、研究、修改和重新分发源代码，甚至还可以销售修改后代码的副本。而正是因为开源，也促使 Linux 更加的可靠、开放、透明、灵活、自由，同时也拥有了众多的 Linux 发行版

​	并且，因为 Linux 的开放、灵活、自由、免费等特点，全球大多服务器设备都是使用的Linux操作系统，而且很高的几率**不会使用图形化的界面，只有命令行操作**

​	而要使用命令行熟练操作Linux，最重要的知识就是 **Linux 操作系统的内核** 以及 **Linux环境下的指令**，本篇文章的主要内容就是 **Linux 环境下的 指令操作**

# Linux环境下的基本指令

> 以下Linux环境，采用发行版为 **CentOS 8.2**

## 1. ls

语法：**ls [选项] [目录或文件]**
功能：对于目录，该命令**列出该目录下的所有子目录与文件**。对于文件，将**列出文件名以及其他信息**。
`ls` 指令，常用选项有：

| 选项      | 功能                                                         |
| --------- | ------------------------------------------------------------ |
| **`-a` ** | 列出目录下的所有文件，包括以 `.` 开头的隐含文件              |
| **`-d`**  | 将目录象文件一样显示，而不是显示其下的文件                   |
| **`-i` ** | 输出文件的 i 节点的索引信息                                  |
| **`-k` ** | 以 k 字节的形式表示文件的大小                                |
| **`-l `** | 列出文件的详细信息                                           |
| **`-n`**  | 用数字的 `UID`,`GID` 代替名称                                |
| **`-F`**  | 在每个文件名后附上一个字符以说明该文件的类型<br /> `*`表示可执行的普通文件； `/`表示目录； `@`表示符号链接； `|` 表示FIFOs； `=`表示套接字 |
| **`-r `** | 对目录反向排序                                               |
| **`-t `** | 以时间排序                                                   |
| **`-s`**  | 在 l 文件名后输出该文件的大小                                |
| **`-R`**  | 列出所有子目录下的文件                                       |
| **`-1`**  | 一行只输出一个文件                                           |

`ls` 的作用是 列出该目录下的所有子目录与文件：
<img src="https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/image-20220702212837012.png" alt="image-20220702212837012" style="zoom: 67%;" />

每一个选项都可以合并使用，也可以分离使用，比如：<img src="https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/image-20220702214047165.png" alt="image-20220702214047165" style="zoom:60%;" />

而`ls` 的众多选项中，使用最多的是 `-l` 和 `-a` 这两项

> **`-l` 列出文件的详细信息**
> <img src="https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/image-20220702214407529.png" alt="image-20220702214407529" style="zoom: 80%;" />
>
> 其实不仅 Linux 下文件有详细信息，在 Windows 下的文件也有其属性：
> <img src="https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/image-20220702214616932.png" alt="image-20220702214616932" style="zoom:67%;" />
>
> > 其实不管是 Linux 还是 Windows，类似上面 `新建 文本文档.txt` 的内容为空的文件，也占据一定的硬盘空间
> > 因为，即使文件内容为空，还有文件属性也是属于这个文件的，属性存储也是需要占据空间的
> >
> > 即，`文件 = 文件内容 + 文件属性`

> **`-a` 列出目录下的所有文件，包括以 `.` 开头的隐含文件**
>
> ![image-20220702215218933](https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/image-20220702215218933.png)
> 还是在原来的目录下，只是使用了 `-a` 选项，列出的文件和子目录 就从 3个(已用黄框圈出) 变成了 25 个.
>
> 仔细观察可以发现， 新增列出的 文件或子目录 都是 `.` 开头的。而 `.`开头的文件 就是操作系统中的隐藏文件
> 并且自己也可以创建隐藏文件，只需要以`.` 开头就好
>
> 当前目录如果是空目录的话：
> <img src="https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/image-20220702220240337.png" alt="image-20220702220240337" style="zoom:67%;" />
> 其实也还存在两个隐藏目录：
> <img src="https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/image-20220702220408371.png" alt="image-20220702220408371" style="zoom:67%;" />
>
> 其中**`..` **是上级目录，而 **`.`** 则是当前目录
>
> > 调用 `cd ..` 即可去往上级目录：
> > <img src="https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/image-20220702220930303.png" alt="image-20220702220930303" style="zoom: 67%;" />
> >
> > 但是即使无限制的使用`cd ..` 最多也只会回到一个 叫 `/`的目录
> > <img src="https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/image-20220702222611914.png" alt="image-20220702222611914" style="zoom:67%;" />
> >
> > 那么这个 `/ 目录` 又是一个什么东西呢？
> >
> > 我们都知道，**一个目录里 可以有多个子目录和文件** ，并且 目录与目录之间 可以是上下级也可以是平行关系
> > 这样看来，目录与子目录与文件就好似有一个这样的关系图：
> > <img src="https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/image-20220702223838789.png" alt="image-20220702223838789" style="zoom:80%;" />
> >
> > 这样的关系图，有一个特点，**父目录下可以有多个子目录或文件，但是文件或子目录的父目录只有一个**
> > 这种关系，与 树 这种数据结构很相似，所以 `/ 目录` 作为目录的起始，也叫做 `根目录`
> >
> > 依照这种关系，从其中某个文件开始 向上级推演` Test.c -> July -> home -> /`
> > 会获得一条，且仅有一条路径 `//home/July/Test.c`，这就是文件的绝对路径
> >
> > > 演示时：
> > > <img src="https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/image-20220702231135219.png" alt="image-20220702231135219" style="zoom:67%;" />
> > >
> > > 这里的 `/home/July/myBlog/Demo/Test1` 叫作 `文件的绝对路径`
> > > 绝对路径是绝对生效的，无论你当前在任何目录下，使用绝对路径都能找到最终的文件(只要文件没被删除)
> > >
> > > `/` 是 Linux 系统下的 路径分隔符
> > >
> > > `\` 则是 Windows 系统下的 路径分隔符
> > > <img src="https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/image-20220702224305632.png" alt="image-20220702224305632" style="zoom:80%;" />
> >
> > > 有绝对路径，就有相应的 `相对路径`
> > >
> > > 相对路径是相对当前目录下来说的，比如：
> > > <img src="https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/image-20220702231803250.png" alt="image-20220702231803250" style="zoom:67%;" />
>
> > **`.`** 叫当前目录(当前路径)，它有什么用呢？
> >
> > 随便编写一个c代码并编译，会生成一个可执行文件 `a.out`：
> > <img src="https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/image-20220702222107373.png" alt="image-20220702222107373" style="zoom:67%;" />
> >
> > 但是直接输入 `a.out` 并不能运行，而是需要输入 `./a.out`，表示在当前目录下
> > <img src="https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/image-20220702222339827.png" alt="image-20220702222339827" style="zoom:67%;" />
> >
> > `.` 表示在当前目录下
>
> > Windows下，也有隐藏文件哦
> > <img src="https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/image-20220702215925391.png" alt="image-20220702215925391" style="zoom: 67%;" />

## 2. pwd

语法: **`pwd`**
功能：显示用户当前所在的目录的绝对路径

<img src="https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/image-20220702232018294.png" alt="image-20220702232018294" style="zoom: 80%;" />

## 3. cd

语法：**`cd 目录名`**
功能：改变当前工作目录。将当前工作目录改变到指定的目录下。

| 操作                    | 功能             |
| ----------------------- | ---------------- |
| `cd .. `                | 返回上级目录     |
| `cd /home/July/myApp/ ` | 绝对路径         |
| `cd ../myCode/ `        | 相对路径         |
| `cd ~`                  | 进入用户家目     |
| `cd -`                  | 返回最近访问目录 |

![image-20220702232935617](https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/image-20220702232935617.png)

