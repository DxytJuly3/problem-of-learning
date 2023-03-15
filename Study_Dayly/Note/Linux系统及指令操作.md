![image-20221031221702230](https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/image-20221031221702230.png)

---



# 什么是 Linux

​	Linux 是一款基于`	 GNU 通用公共许可协议` 的 `自由和开放源代码` 的类UNIX操作系统，该操作系统的内核由 Linus Torvalds 在1991年首次发布。之后，在加上用户空间的应用程序之后，就成为了Linux操作系统。  但是，严格来讲， Linux只是操作系统内核，但通常采用 “Linux内核” 来表达该意思。而 Linux 则常用来指基于Linux内核的完整操作系统，它包括GUI组件和许多其他实用工具。  

上面提到两个词——`GNU 通用公共许可协议` 和 `开放源代码(开源)`，这两个词是什么意思呢？

1. `GNU通用公共许可协议`（GNU General Public License，简称`GNU GPL`或`GPL`），是一个广泛被使用的自由软件许可协议条款， `GPL`给予了计算机程序自由软件的定义， 任何基于`GPL`软件开发衍生的产品在发布时必须采用`GPL`许可证方式，且必须`公开源代码`
2. `开源`，其实从字面意思就可以理解：`开放源代码、公开源代码`，即在协议条件允许的情况下，任何人都可以研究、修改、发布源代码

​	而 Linux 是基于`GNU 通用公共许可协议`发布的，只要符合相应的许可条件，任何人都可以运行、研究、修改和重新分发源代码，甚至还可以销售修改后代码的副本。而正是因为开源，也促使 Linux 更加的可靠、开放、透明、灵活、自由，同时也拥有了众多的 **Linux 发行版**

​	并且，因为**Linux 的开放、灵活、自由、免费** 等特点，全球大多服务器设备都是使用的Linux操作系统，而且很高的几率**不会使用图形化的界面，只有命令行操作**

​	而要使用命令行熟练操作Linux，最重要的知识就是 **Linux 操作系统的内核** 以及 **Linux环境下的指令**，本篇文章的主要内容就是 **Linux 环境下的 指令操作**

# Linux环境下的基本指令

> 以下 **Linux环境** ，采用发行版为 **CentOS 8.2**

## 1. ls

语法：**`ls [选项] [目录或文件]`**
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
> 其实不仅 **Linux** 下文件有详细信息，在 **Windows** 下的文件也有其属性：
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
> > > 一个网站的`url`的域名之后的部分的`/` 是相同的意思
> > > <img src="https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/image-20220706175740592.png" alt="image-20220706175740592" style="zoom:67%;" />
> > > `/video/BV1ua411p7iA` 是与`linux`路径相同意思的东西，也就是说这些网站都是部署在`linux`操作系统上的
> > >
> > > `\` 则是 Windows 系统下的 路径分隔符
> > > <img src="https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/image-20220702224305632.png" alt="image-20220702224305632" style="zoom:80%;" />
> >
> > > 有绝对路径，就有相应的 `相对路径`
> > >
> > > 相对路径是相对当前目录下来说的，比如：
> > > <img src="https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/image-20220702231803250.png" alt="image-20220702231803250" style="zoom:67%;" />
>
> > **`.`** 叫当前`目录(当前路径)`，它有什么用呢？
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

## 4. touch

语法：`touch [选项] 文件...`
功能：`touch`命令参数可`更改文档或目录的日期时间`，包括存取时间和更改时间，或者`新建一个不存在的文件`
常用选项：

| 选项                                              | 功能                                                         |
| ------------------------------------------------- | ------------------------------------------------------------ |
| **`-a或--time=atime或--time=access或--time=use`** | 只更改存取时间                                               |
| **`-c 或 --no-create`**                           | 不建立任何文档                                               |
| **`-d `**                                         | 使用指定的日期时间，而非现在的时间                           |
| **`-f `**                                         | 此参数将忽略不予处理，仅负责解决BSD版本touch指令的兼容性问题 |
| **`-m 或 --time=mtime或 --time=modify`**          | 只更改变动时间                                               |
| **`-r `**                                         | 把指定文档或目录的日期时间，统统设成和参考文档或目录的日期时间相同 |
| **`-t`**                                          | 使用指定的日期时间，而非现在的时间                           |

`touch` 可以用来更改文档或目录的日期时间，但是`touch` 最常用的功能还是 `新建一个不存在的文件`

<img src="https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/image-20220706132908417.png" alt="image-20220706132908417" style="zoom:67%;" />

## 5. mkdir

语法：**`mkdir [选项] dirname...`**
功能：在当前目录下创建一个名为 `“dirname”` 的目录
常用选项：  

| 选项                | 功能                                     |
| ------------------- | ---------------------------------------- |
| **`-p, --parents`** | 可以是一个路径名称，一般用来建立多层目录 |

`mkdir` 其实就是 `make directory` 的简称，意为 创建目录

<img src="https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/image-20220706133851511.png" alt="image-20220706133851511" style="zoom:67%;" />

但是如果想要一次性创建多层目录的话，就需要添加 `-p` 的选项了，单独的 `mkdir` 是无法创建多层目录的

<img src="https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/image-20220706134336986.png" alt="image-20220706134336986" style="zoom:67%;" />

## 6. rmdir && rm 

`rmdir`是一个与`mkdir`相对应的命令。`mkdir`是建立目录，而`rmdir`是删除目录
语法：**`rmdir [选项] dirName`**
适用对象：具有当前目录操作权限的所有使用者
功能：`删除空目录`
常用选项：

| 选项     | 功能                                                         |
| -------- | ------------------------------------------------------------ |
| **`-p`** | 当子目录被删除后如果父目录也变成空目录的话，就连带父目录一起删除 |

`rm` 是 `remove` 的简称

`rmdir` 是删除空目录的操作，如果目录内还有其他文件或目录，是无法删除的。可以跨层删除目录

`rmdir -p` 则是递归删除空目录

<img src="https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/image-20220706135822410.png" alt="image-20220706135822410" style="zoom:67%;" />

`rm` 可以同时删除文件或目录

语法：**`rm [选项] dirName/dir`**
适用对象：所有使用者
功能：删除文件或目录
常用选项：

| 选项     | 功能                                                         |
| -------- | ------------------------------------------------------------ |
| **`-f`** | 即使文件属性为只读(即写保护)，亦直接删除，即强制删除任何文件 |
| **`-i`** | 删除前逐一询问确认，取消确认删除的询问                       |
| **`-r`** | 删除目录及其下所有文件，即递归删除所有文件                   |

`rm` 可以删除文件和目录，但是单独使用不能删除目录，也不能删除只读文件

<img src="https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/image-20220706140819278.png" alt="image-20220706140819278" style="zoom:67%;" />

而 `-f` 选项可以强制删除任何单个文件，当 `-r` 和 `-f` 一起使用，就是将 目录内所有文件强制删除了

> **Linux**命令行，不像 **Windows** 有回收站，所以 **Linux** 最好**不要随意删除文件**

## 7. man

**Linux** 的命令有很多参数，不可能全记住，不过可以通过查看联机手册获取帮助。

访问 **Linux手册页** 的命令就是`man`

语法：**` man [选项] 命令`**
常用选项：

| 选项      | 功能                                         |
| --------- | -------------------------------------------- |
| **`-k`**  | 根据关键字搜索                               |
| **`num`** | 只在第`num`章节找                            |
| **`-a`**  | 将所有章节的都显示出来，一个章节一个章节显示 |

通俗的来讲，`man` 就是查看 **Linux指令用法** 手册的一个指令

**`-k`** 根据关键字搜索

一般用于，由关键字查找指令、与关键字相关的指令：
<img src="https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/image-20220706180903004.png" alt="image-20220706180903004" style="zoom:67%;" />

**`num` **只在第`num`章节找

`man` 查看手册有 9 个章节：<img src="https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/image-20220706181029647.png" alt="image-20220706181029647" style="zoom:80%;" />
可以选择不同的章节来查找不同类型的相同名字的操作：
<img src="https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/image-20220706181351609.png" alt="image-20220706181351609" style="zoom:67%;" />
不选择`num` 默认为 1，查找的是 `shell命令`的用法
如果想要查找C语言中`printf函数`的用法，就需要选择 `3` 查找调用库
<img src="https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/image-20220706181636031.png" alt="image-20220706181636031" style="zoom:67%;" />

> 由于 **Linux** 是由C语言编写的，所以默认查找的库是C语言的库，如果想要查找其他语言库中的的函数，需要手动配置

**`-a`**  将所有章节的都显示出来，一个章节一个章节显示

这个功能只能动图展示出来：
![4_printf](https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/4_printf.gif)

`-a` 选项会将各个章节中能找到的同名指令或函数一一显示出来

## 8. cp

语法：**`cp [选项] 源文件或目录 目标文件或目录`**
功能: 复制文件或目录
说明: `cp ` 指令用于 复制文件或目录。如 同时指定 两个以上的文件或目录，且最后的目的地是 一个已经存在的目录，
则它会把前面 指定的所有文件或目录 复制到此目录中。若 同时指定 多个文件或目录，而最后的目的地 并非一个已存
在的目录，则会出现错误信息

| 选项                      | 功能                                                |
| ------------------------- | --------------------------------------------------- |
| **`-f、--force`**         | 强行复制文件或目录， 不论目的文件或目录是否已经存在 |
| **`-i、--interactive`**   | 覆盖文件之前先询问用户                              |
| **`-r、-R、--recursive`** | 递归处理，将指定目录下的文件与子目录一并处理        |

**Linux** 中的 `cp` 其实就相当于 **Windows中的复制粘贴** 

<img src="https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/image-20220706200500734.png" alt="image-20220706200500734" style="zoom:67%;" />

但是 `cp` 单独使用是不能拷贝目录的：
<img src="https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/image-20220706200643558.png" alt="image-20220706200643558" style="zoom:67%;" />

选项`-r` 可以拷贝目录及其子目录或文件：
<img src="https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/image-20220706200832080.png" alt="image-20220706200832080" style="zoom:67%;" />

若目录下已有同名文件，则`-i` 会询问是否覆盖文件：
<img src="https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/image-20220706201058020.png" alt="image-20220706201058020" style="zoom:67%;" />

## 9. mv

`mv`命令是`move`的缩写，可以用来**移动文件或者重命名**，是Linux系统下常用的命令，**经常用来备份文件或者目录**
语法：**`mv [选项] 源文件或目录 目标文件或目录`**
功能：移动、重命名文件或目录
常用选项：

| 选项     | 功能                                                       |
| -------- | ---------------------------------------------------------- |
| **`-f`** | force 强制的意思，如果目标文件已经存在，不会询问而直接覆盖 |
| **`-i`** | 若目标文件 已经存在时，就会询问是否覆盖                    |

使用`-i` 会对覆盖操作进行询问：
<img src="https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/image-20220706203931853.png" alt="image-20220706203931853" style="zoom:67%;" />

移动文件：
<img src="https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/image-20220706204230393.png" alt="image-20220706204230393" style="zoom:67%;" />

## 10. cat

在 `cp` 操作的介绍中，就使用过 **`cat`** 来查看文件的内容

语法：**`cat [选项] [文件]`**
功能：查看目标文件的内容
常用选项：

| 选项     | 功能               |
| -------- | ------------------ |
| **`-b`** | 对非空输出行编号   |
| **`-n`** | 对输出的所有行编号 |
| **`-s`** | 不输出多行空行     |

`cat` 单独使用，一般用来查看文件的所有内容，但是 `-s` 对多行连续的空行只输出一行，`-n` 会对所有输出行编号，`-b` 只对输出的非空行编号

使用`cat -s -n\-b` 查看文件内容如此的文件：<img src="https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/image-20220706205334237.png" alt="image-20220706205334237" style="zoom:67%;" />

<img src="https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/image-20220706205622891.png" alt="image-20220706205622891" style="zoom:80%;" />

> 其实除 `cat` 之外还有一个 类似用途的查看文件内容的指令 `tac`
>
> 看见这个指令的名字就能想得到这个指令得作用是什么：
> <img src="https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/image-20220706210105377.png" alt="image-20220706210105377" style="zoom:67%;" />
>
> **PS：`tac` 指令无法添加选项使用**

`cat` 也可以单独使用，不操作文件：
<img src="https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/cat_nodir.gif" alt="cat_nodir" style="zoom:80%;" />

`cat` 不操作文件的功能就是：**输入什么，就直接输出什么**

> 单独使用 `cat` 之后，按什么都是输入或输出操作，怎么退出这种模式呢？
>
> `Ctrl + c` 或 `Ctrl + z`
>
> 但是，`Ctrl + z` 是暂停这个进程到后台，并不是终止，所以`Ctrl + z` 不要乱用
>
> > 如果，一个程序被暂停了，怎么从后台调出来终止掉呢？
> >
> > 这又涉及了两个指令：`jobs` `fg %num` **(CentOS 7应该是 `fg num`)**
> > <img src="https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/image-20220706210951863.png" alt="image-20220706210951863" style="zoom:67%;" />
> >
> > 使用 `jobs` 可以看到当前**正在后台的进程及其编号**
> > <img src="https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/image-20220706211417278.png" alt="image-20220706211417278" style="zoom:80%;" />
> >
> > 使用`fg %num` 继续进程，并`Ctrl + c` 终止进程：
> > <img src="https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/image-20220706211846892.png" alt="image-20220706211846892" style="zoom: 67%;" />

`cat` 适合查看短小的文本，不适合查看大文本，因为会将大文本的所有内容输出到屏幕上

<img src="https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/image-20220706212619209.png" alt="image-20220706212619209" style="zoom:67%;" />
如果使用了 `cat` 查看：
<img src="https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/10w_Hello_July.gif" alt="10w_Hello_July" style="zoom:67%;" />

看到这 10w 行文本的快速遍历输出，如果是有效内容，根本无法阅读

而适合大文本查看的是另外两个指令

## 11. more

语法： **`more [选项][文件]`**
功能：` more`命令，功能类似 `cat`
常用选项：

| 选项     | 功能               |
| -------- | ------------------ |
| **`-n`** | 对输出的所有行编号 |

`more` 的功能也是查看文件内容，但是它是一行一行显示的 `Enter` 继续下一行，并且可以`/`查找内容，但无法像上移动查看，也无法向上搜索，按 `Q` 键退出 `more`

<img src="https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/more.gif" alt="more" style="zoom:67%;" />

## 12. less

`less` 的用途与 `more`一样，但是**`less` 的功能比 `more` 强大的多**

语法： **`less [参数] 文件`**
功能：`less`与`more`类似，但使用`less`可以随意浏览文件，而`more`仅能向前移动，却不能向后移动，而且`less`在查看之前不会加载整个文件
常用选项：

| 选项 / 操作符 | 功能                                 |
| ------------- | ------------------------------------ |
| **`-i`**      | 忽略搜索时的大小写                   |
| **`-N`**      | 显示每行的行号                       |
| **`/`**       | 字符串：向下搜索“字符串”的功能       |
| **`?`**       | 字符串：向上搜索“字符串”的功能       |
| **`n`**       | 重复前一个搜索（与 / 或 ? 有关）     |
| **`N`**       | 反向重复前一个搜索（与 / 或 ? 有关） |

<img src="https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/less.gif" alt="less" style="zoom:67%;" />

按 `Q` 退出 `less`

由于 `less` 功能更加强大，所以查看大文本一般使用 `less`而不是用 `more`

> 在将 10w 行 `Hello July` 写入到文件 `file.txt` 中使用了一条指令：
>
> ```shell
> cnt=1; while [ $cnt -le 100000 ]; do echo "Hello July $cnt"; let cnt++; done > file.txt
> ```
>
> 其中 `>` 之前的部分，是 `shell 指令` 输出10w行 `Hello July`：
> <img src="https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/10w_Hello_July_shell.gif" alt="10w_Hello_July_shell" style="zoom: 67%;" />
>
> `> file.txt` 就是将这 10w 行文本写入到 文件`file.txt` 中
>
> `> 输出重定向符号`，将本来输出到屏幕的内容，输出到文件中
> 会清空文件的原始内容：
>  <img src="https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/image-20220706220356119.png" alt="image-20220706220356119" style="zoom:67%;" />
>
> `>> 追加重定向符号`，将本来输出到屏幕的内容，追加到文件中
> 不会清空文件原始内容：
> <img src="https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/image-20220706220548405.png" alt="image-20220706220548405" style="zoom:67%;" />
>
> `< 输入重定向符号` 将原本的从键盘中读取数据的方式，变为从文件中读取：
> <img src="https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/image-20220706220855778.png" alt="image-20220706220855778" style="zoom:67%;" />
>
> > Linux 操作系统中，外设也同样可以当作"文件"理解

## 13. head、tail 和 管道简介

`head` 与 `tail` 就像它的名字一样的浅显易懂，它是用来显示开头或结尾某个数量的文字区块
` head` 用来显示档案的开头至标准输出中，而 `tail`想当然尔就是看档案的结尾

**`head`**

语法：**`head [参数]... [文件]...`**
功能：`head` 用来显示档案的开头至标准输出中，**默认`head`命令打印其相应文件的开头10行**
选项：

| 选项            | 功能       |
| --------------- | ---------- |
| **`-n <行数>`** | 显示的行数 |

还是对 10w 行内容的文件操作：
<img src="https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/image-20220706222303590.png" alt="image-20220706222303590" style="zoom:67%;" />

**`tail`**

`tail`命令从指定点开始将文件写到标准输出

使用`tail`命令的`-f选项` 可以方便的查阅正在改变的日志文件
`tail -f filename`会把 **filename里最尾部的内容显示在屏幕上,并且不但刷新,使你看到最新的文件内容**

语法：**`tail [必要参数] [选择参数] [文件]`**
功能： 用于显示指定文件末尾内容，默认查看未10行。不指定文件时，作为输入信息进行处理。常用查看日志文件。
选项：  

| 选项            | 功能     |
| --------------- | -------- |
| **`-f`**        | 循环读取 |
| **`-n <行数>`** | 显示行数 |

<img src="https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/image-20220706223005765.png" alt="image-20220706223005765" style="zoom:67%;" />

`tail -f` 可以用来查看不断更新的日志文件，日志文件不断更新，`-f`可以**不断刷新显示末尾n行**

> `head` 和 `tail` 分别可查看文件的 **前n行和末n行**
>
> 那么**如何查看文件的中间段内容呢？** 比如：58888行。有两种方法：
>
> 1. 创建临时文件，先用 `head` 将前58888行放入临时文件中，然后在使用 `tail` 查看临时文件的最后一行
>
> 2. 管道
>
>     <img src="https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/image-20220706223610575.png" alt="image-20220706223610575" style="zoom:80%;" />
>
>     ```shell
>     head -n 58888 file.txt | tail -n 1
>     ```
>
>     就可以查看 第 58888 行的内容
>
>     其中 `|` 就是管道
>     `head -n 58888 file.txt` 将 文件中的前 58888 行作为数据放入到`管道|`中，再紧接 `tail -n 1` 查看管道中最后一行的内容，可以实现中间行的操作
>
> **那么什么是管道？**
>
> 在日常生活中，某部分流体资源的运输通过管道运输到各家各户的：天然气、生活用水等
>
> 而仿照这种思想，在 Linux 系统中，可以将数据作为资源放入 系统的管道中，**Linux中的管道 就是用来运输数据的**
>
> **管道的存在，可以级联多条指令，来完成流水线式的数据处理工作**：
> <img src="https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/image-20220706224722957.png" alt="image-20220706224722957" style="zoom:67%;" />
>
> 管道，是 Linux 学习中非常重要的概念

## 14. 时间相关指令

**`date`**

`date` 用来显示当前时间：<img src="https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/image-20220706225539635.png" alt="image-20220706225539635" style="zoom:67%;" />

`date` 还可以手动指定显示时间的格式

date 指定格式显示时间： `date +%Y:%m:%d`
date 用法：**`date [OPTION]... [+FORMAT]`**

根据下表参数可以手动设置格式：

| 参数     | 内容                  |
| -------- | --------------------- |
| **`%H`** | 小时(00..23)          |
| **`%M`** | 分钟(00..59)          |
| **`%S`** | 秒(00..59)            |
| **`%X`** | 相当于`%H:%M:%S`      |
| **`%d`** | 日 (01..31)           |
| **`%m`** | 月份 (01..12)         |
| **`%Y`** | 完整年份 (0000..9999) |
| **`%F`** | 相当于 `%Y-%m-%d`     |

<img src="https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/image-20220706230850967.png" alt="image-20220706230850967" style="zoom:67%;" />

**`时间戳`**

什么是**时间戳**？

**Unix时间戳 是从1970年1月1日（UTC/GMT的00:00）开始所经过的秒数**，不考虑闰秒。 

在 Linux 中使用 `date +%s` 可以显示当前时间戳：<img src="https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/image-20220706231426994.png" alt="image-20220706231426994" style="zoom:80%;" />

在搜索引擎搜索 时间戳在线转换可以转换为时间：<img src="https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/image-20220706231549931.png" alt="image-20220706231549931" style="zoom:80%;" />

时间戳为0时：<img src="https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/image-20220706231629899.png" alt="image-20220706231629899" style="zoom:80%;" />
时间戳是**从 1970年1月1日00:00 开始的，国内转换是 08:00 因为时区不同，存在时差**

也可以使用 `date -d@时间戳` 将时间戳转换为时间：<img src="https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/image-20220706231937699.png" alt="image-20220706231937699" style="zoom:80%;" />

## 15. cal

`cal`命 令可以用来显示公历（阳历）日历

命令格式： **`cal [参数] [月份] [年份]`**
功能：用于查看日历等时间信息，**如只有一个参数，则表示年份**(1-9999)
**如有两个参数，则表示 月份 和 年份 **，月份在前，年份在后
常用选项：

| 选项     | 功能                                                         |
| -------- | ------------------------------------------------------------ |
| **`-1`** | 显示当前月历                                                 |
| **`-3`** | 显示系统前一个月，当前月，下一个月的月历                     |
| **`-j`** | 显示在当年中的第几天（一年日期按天算，从1月1号算起，默认显示当前月在一年中的天数） |
| **`-y`** | 显示当前年份的日历                                           |

<img src="https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/image-20220706232645027.png" alt="image-20220706232645027" style="zoom:67%;" />

<img src="https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/image-20220706232747478.png" alt="image-20220706232747478" style="zoom:67%;" />

## 16. find

> 1. Linux下find命令在目录结构中搜索文件，并执行指定的操作。
> 2. Linux下find命令提供了相当多的查找条件，功能很强大。
> 3. 即使系统中含有网络文件系统( NFS)， find命令在该文件系统中同样有效，只要具有相应的权限。
> 4. 在运行一个非常消耗资源的find命令时，很多人都倾向于把它放在后台执行，因为遍历一个大的文件系统可能会花费很长的时间(这里是指30G字节以上的文件系统)  

语法： **`find pathname -options`**
功能： 用于在文件树种查找文件，并作出相应的处理（可能访问磁盘）
常用选项：  

| 选项        | 功能               |
| ----------- | ------------------ |
| **`-name`** | 按照文件名查找文件 |

`find` **单独使用时，必须指定目录查找或查找当前目录的文件**：
<img src="https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/image-20220706233433942.png" alt="image-20220706233433942" style="zoom:80%;" />

`find -name 文件名` 可以遍历指定位置查找（范围较大时，较费时间）： 
<img src="https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/find_-name.gif" alt="find_-name" style="zoom:80%;" />

## 17. grep

> **`grep` 详细使用可以参考 grep文档**

语法： **`grep [选项] 搜寻字符串 文件`**
功能： 在文件中搜索字符串，将找到的行打印出来，**默认区分大小写**
常用选项：

| 选项     | 功能                         |
| -------- | ---------------------------- |
| **`-i`** | 取消区分大小写               |
| **`-n`** | 输出行号                     |
| **`-v`** | 反向选择，选择不带关键字的行 |

`grep` 是**行文本过滤工具，会将查找到关键字的一行都输出**

<img src="https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/image-20220706234904930.png" alt="image-20220706234904930" style="zoom:67%;" />

还有 `-n` 和 `-v` 的演示：

<img src="https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/image-20220706235048642.png" alt="image-20220706235048642" style="zoom:67%;" />

## 18. zip、unzip

`zip` 是Linux平台下的一种打包压缩的指令；`unzip` 则是解压缩的指令

语法：**`zip 压缩文件.zip 目录或文件`**
功能：将目录或文件压缩成 `zip` 格式
常用选项：

| 选项     | 功能                                             |
| -------- | ------------------------------------------------ |
| **`-r`** | 递归处理，将指定目录下的所有文件和子目录一并处理 |
| **`-d`** | 解压用，用来指定解压目录                         |

`zip` 用来打包压缩文件：
<img src="https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/image-20220707120928659.png" alt="image-20220707120928659" style="zoom:67%;" />
但是 无选项时对目录打包压缩，不会打包目录内的内容：
<img src="https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/image-20220707121444684.png" alt="image-20220707121444684" style="zoom:67%;" />

而`zip`如果想要打包目录内的所有内容，要加上选项`-r`：
<img src="https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/image-20220707121904184.png" alt="image-20220707121904184" style="zoom:60%;" />

再对使用 `-r`压缩的文件，解压缩：
<img src="https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/image-20220707122329494.png" alt="image-20220707122329494" style="zoom:67%;" />

所以 `zip` 压缩目录内所有内容需要选项`-r`递归打包压缩。

## 19. tar

语法：**`tar [-cxtzjvf] 文件与目录 .... 参数`**
功能：将目录或文件压缩成`tar.gz 或 tgz`格式，或解压 `tar.gz、tgz`文件，或直接查看`tar.gz、tgz`文件内容
常用选项：

| 选项     | 功能                                                         |
| -------- | ------------------------------------------------------------ |
| **`-c`** | 建立一个压缩文件的参数指令(create 的意思)                    |
| **`-x`** | 解开一个压缩文件的参数指令                                   |
| **`-t`** | 查看 `tarfile` 里面的文件                                    |
| **`-z`** | 是否同时具有 `gzip` 的属性？亦即是否需要用 `gzip` 压缩？     |
| **`-j`** | 是否同时具有 `bzip2` 的属性？亦即是否需要用 `bzip2` 压缩？   |
| **`-v`** | 压缩的过程中显示文件！这个常用，但不建议用在背景执行过程！   |
| **`-f`** | 使用档名，请留意，**在 `f` 之后要立即接档名！不要再加参数！** |
| **`-C`** | 解压到指定目录                                               |

> `tar` 指令可以分离执行 打包、压缩 这两个过程，`zip` 只能合并两个过程打包压缩文件
>
> 但是 分离执行 不常用且些许麻烦，所以 只介绍一次性执行
>
> 一次性执行后缀为 `.tgz` 是 `.tar.gz` 的合称

<img src="https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/image-20220707123544407.png" alt="image-20220707123544407" style="zoom:67%;" />

`tar` 命令使用选项时，可能需要前加`-` 也可能不需要，与`tar`版本有关
`-z` 选项可以指定压缩文件的属性为 `gzip`，相应的还有`-j` 可指定压缩文件属性为`bzip2`

`-t` 选项可以直接查看压缩文件的内容：
<img src="https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/image-20220707123924349.png" alt="image-20220707123924349" style="zoom:67%;" />

`tar xzvf 档名 -C 目录` 常用来指定目录、显示过程解压缩`gzip`属性的`tar`压缩文件：
<img src="https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/image-20220707124405847.png" alt="image-20220707124405847" style="zoom:67%;" />

这基本就是 `tar` 简单的操作的内容

> 问题1：为什么要压缩文件？
>
> 压缩文件的目的一般有两个：
>
> 1. 节省资源。无论是本地的物理空间资源，还是网络数据传输、存储时的资源占用，独立的压缩文件都会占用更少的资源
> 2. 方便网络传输。
>     众所周知，一个项目、软件的文件不可能只有一个，如果不对这些文件进行打包压缩就直接进行传输，很有可能会发生中途部分数据丢失，进而造成看似文件传输成功了但其实并没有完全成功。
>     使用打包压缩的方法，将一个项目的所有文件打包压缩起来，在网络传输中不会存在部分文件丢失却又无法发觉的情况，因为压缩文件数据丢失 就代表压缩文件的损坏，当一个压缩文件损坏了，根本就无法进行解压。可以很明确的让使用者知道，本次传输失败了。同时，一个文件的传输更胜于多个文件目录的传输。
>     所以，压缩文件其实还是为了`方便快捷节省资源`

> 问题2：Linux是否支持所有的压缩文件格式？为什么？
>
> 是的，Linux 是支持所有的压缩文件格式的。
> 主要原因是因为，不可能所有的开发者都使用同一个平台进行开发。而不同的开发平台(Mac、Windows、Linux) 如果压缩文件格式都不相互支持，将会是一种巨大的折磨。

## 20. bc

Linux 种 `bc` 其实就是计算器：
<img src="https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/bc_show.gif" alt="bc_show" style="zoom:80%;" />

## 21. uname

语法： **`uname [选项]`**
功能： `uname`用来获取电脑和操作系统的相关信息。
补充说明： `uname`可显示`linux`主机所用的**操作系统的版本、硬件的名称等基本信息**。
常用选项：  

| 选项           | 功能                                                         |
| -------------- | ------------------------------------------------------------ |
| **`-a或–all`** | 详细输出所有信息，依次为内核名称，主机名，内核版本号，内核版本，硬件名，处理器类型，硬件平台类型，操作系统名称 |
| **`-r`**       | 输出操作系统内核版本号                                       |

<img src="https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/image-20220707134800918.png" alt="image-20220707134800918" style="zoom:80%;" />

## 22. 扩展命令

Linux 不仅仅只有上面那些指令，还有许多指令需要学习：

- 安装和登录命令：`login`、`shutdown`、`halt`、`reboot`、`install`、`mount`、`umount`、`chsh`、`exit`、`last`；
- 文件处理命令：`file`、`dd`、`diff`、`cat`、`ln`；
- 系统管理相关命令：`df`、`top`、`free`、`quota`、`at`、 `lp`、`adduser`、`groupadd`、`kill`、`crontab`；
- 网络操作命令：`ifconfig`、`ip`、`ping`、`netstat`、`telnet`、`ftp`、`route`、`rlogin`、`rcp`、`finger`、`mail`、`nslookup`；
- 系统安全相关命令：`passwd`、`su`、`umask`、`chgrp`、`chmod`、`chown`、`chattr`、`sudo ps`、`who`；
- 其它命令：`gunzip`、`unarj`、`mtools`、`unendcode`、`uudecode`  

但是这些指令，相比上面的指令 相对没有那么常用罢了

---

感谢阅读~

<img src="https://img-blog.csdnimg.cn/6e5d35b9b94e4b9897743b2ca8e059d0.png#pic_center" alt="万分感谢" width="30%" />
