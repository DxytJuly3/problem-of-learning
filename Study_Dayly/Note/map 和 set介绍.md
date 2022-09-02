set 和 map 是C++ - STL 中非常重要的两个容器，上一篇文章介绍了 二叉搜索树。

而 set 和 map 的一层就是由一种二叉搜索树来实现的——红黑树

本篇文章先来介绍一下 set 和 map 简单的介绍，以及相关接口的使用

# set

<img src="https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/202209021620449.png" alt="image-20220902162016395" style="zoom:80%;" />

## 什么是 set

按照set模板的定义，其模板参数的意义是：

第一个模板参数T——存储元素类型；第二个模板参数——元素比较的仿函数；第三个模板参数——分配器

> 第二个和第三个模板参数 都给定了缺省值，本篇文章对其使用的介绍暂时不涉及 后两个模板参数的改变

官方文档中对set的介绍是：
<img src="https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/202209021622401.png" alt="image-20220902162240345" style="zoom:80%;" />

总结一下就是：
	`set` 是一个由`二叉搜索树`实现的用于存储 `唯一的` `不可修改的` 元素 的容器；并且，存储的元素按照给定的比较方式进行严格的排序
再解释一下就是：
	`set` 以二叉搜索树的形式存储元素，并且树中没有重复的元素，存储的元素都是`const`修饰的 不可修改，并且存储元素时会按照给定的 `cmp方式(模板参数中的 Compare)` 进行排序

> 其实这里的二叉搜索树再具体一点，就是红黑树

> 除了存储唯一元素的 `set`，STL中还存在另一个可以存储重复元素的容器：`multiset`
> 与set的区别仅在于 其可以存储重复的元素

## set 常用的接口

### 1. insert 插入元素

<img src="https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/202209021717791.png" alt="image-20220902171738747" style="zoom:80%;" />

`insert` 最基本也最常用的用法就是 直接插入指定类型的一个元素：
<img src="https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/202209021720635.png" alt="image-20220902172040598" style="zoom:80%;" />
可以看到 插入的元素会`自动排好顺序`，并且重复插入相同的元素`只会插入一次`

`insert` 也可以指定位置插入指定的值，但是这种方式很少使用，因为`set`是有严格的结构要求的。
为了再插入元素时不破坏结构，即使指定位置插入，也有可能不在指定的位置插入元素。所以，一般在 `已经知道将此元素插入此位置不会造成结构的破坏` 时才可能使用这种方式

最常用的还是直接插入元素

> 仔细看 C++98 中`insert`直接插入元素的用法，其返回值是：`pair<iterator, bool>` 
>
> `pair`是什么？`pair` 是一对，一双的意思
>
> <img src="https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/202209021756854.png" alt="image-20220902175649806" style="zoom:80%;" />
>
> pair 也是一个类模板，有两个模板参数：
> <img src="https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/202209021757230.png" style="zoom:80%;" />
>
> `T1`：第一个元素类型；`T2`：第二个元素类型
>
> 在 `insert` 返回值中两个元素类型分别是 `iterator` 和 `bool`
>
> 为什么要返回一个 `pair<iterator, bool>` 类型的数据呢？
>
> 查看 `insert` 第一个版本关于返回值的描述是：
> <img src="https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/202209021802443.png" alt="image-20220902180221406" style="zoom:80%;" />
>
> 返回 `pair`类型数据的**原因**，其实是 由于`set`存储的是唯一的元素，所以会**存在插入失败的情况(当set中已经存在将要插入的元素，此时的插入操作就会失败)**，而某些场景需要判断当前插入操作是否成功，而某些场景又需要获取插入元素的位置，但是函数的返回值只能由一个，所以就使用了 **`pair` 来将 元素的位置 和 插入是否成功 存储起来**，返回 pair类型的数据就**可以同时 知道元素的位置 和 本次插入是否成功**
>
> 即，当`set`中没有将要插入的元素时，插入就会成功，并会将 插入元素的位置 和 `true`(表示插入成功) 存储到`pair`对象中 并返回
>
> 当`set`中已经存在将要插入的元素时，插入就会失败，并会将 已经存在的元素的位置 和 `false`(表示插入失败) 存储到`pair`对象中 并返回
>
> 举个例子：
>
> <img src="https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/202209021818681.png" alt="image-20220902181841617" style="zoom:80%;" />
>
> > 因为 `set `不存储重复数据所以才会如此，而 `multiset` 的 `insert` 就不需要这样

### 2. 迭代器相关

| 接口      | 功能                   |
| --------- | ---------------------- |
| `begin()` | 返回 首元素 正向迭代器 |
| `end()`   | 返回 末元素 正向迭代器 |

`set` 与其他容器一样 常用两个函数取迭代器，一个 `begin()` 用来取首元素正向迭代器，一个 `end()` 用来取末元素正向迭代器

> 举个栗子：
>
> <img src="https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/202209022034744.png" alt="image-20220902203432693" style="zoom:80%;" />
>
> 关于 set 的迭代器需要注意的是：**`set` 迭代器表示的内容是无法修改的**
>
> 即，即使是 `iterator` 而不是 `const_iterator` ，其表示的内容也是无法修改的：
> <img src="https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/202209022037506.png" alt="image-20220902203731462" style="zoom:80%;" />
>
> 原因其实是，**STL** 设计`set`时，`iterator` 其实也是 `const` 修饰过的`iterator`：
> <img src="https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/202209022045975.png" alt="image-20220902204540931" style="zoom:80%;" />
>
> 查看`STL关于set`的源码，就可以看到 `iterator` 和 `const_iterator` 都是对 `rep_type::const_iterator` 的 `typedef`

set 关于迭代器的其他接口函数还有：`cbegin()` `cend()` `rbegin()` `rend()` `crbgin()` `crend()`
无非是关于 **反向迭代器** 和 **`const`迭代器**

### 3. find 查找位置

<img src="https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/202209022120794.png" alt="image-20220902212042758" style="zoom:80%;" />

`find` 的用法和作用就非常的简单了，只需要传入需要查找的数据内容 就可以使用

`find` 的返回值是一个迭代器，按照文档的介绍：
	如果可以在`set`中找到指定的数据，则返回这个数据位置的迭代器；
	否则 返回 `end()`

> `find` 一般与 `erase` 一起使用，先用 `find` 查找数据位置迭代器，再用 `erase` 删除

### 4. erase 删除元素

<img src="https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/202209022101327.png" alt="image-20220902210136296" style="zoom:80%;" />

erase 删除元素接口，有三个不同的重载版本：

1. 删除指定位置的数据
2. 删除指定值
3. 删除两个迭代器区间内的数据

这三个版本都是可能会用到的

> **删除指定值版本：**
>
> <img src="https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/202209022116800.png" alt="image-20220902211605755" style="zoom:80%;" />
>
> 只需要在调用时传入值就可以完成指定值的删除
>
> 即使是 set 中没有的值，也不会出错：
>
> <img src="https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/202209022117827.png" alt="image-20220902211729787" style="zoom:80%;" />
>
> 多次重复删除 3，也不会出现问题

> **删除指定位置版本：**
>
> `erase` 删除指定位置，一般需要先使用 `find` 在 `set` 中找到相应的位置，然后再 `erase` 进行删除：
> <img src="https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/202209022131483.png" alt="image-20220902213153429" style="zoom:80%;" />
>
> 当find找到了确定值的位置时，就可以正常的删除
>
> 那么 当删除 `pos` 之后，不改变 `pos`，再次删除会发生什么？
> <img src="https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/202209022134420.png" alt="image-20220902213439370" style="zoom:80%;" />
>
> 很明显会报错，此时其实是**迭代器失效**了，`pos` 已经不再表示set中存储的3了，意义已经变了
>
> > STL提供的通用的 `find` 也可以找指定数据的位置，但是效率终究不如`set`本身的
> >
> > 因为 算法提供的通用的 `find` 是 根据提供的迭代器区间进行遍历查找，而 `set` 自己的 `find` 是根据二叉搜索树的特性而实现的 `logN` 时间复杂度的算法

> **删除迭代器区间内数据的版本**
>
> 举个例子：
> <img src="https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/202209022145947.png" alt="image-20220902214503918" style="zoom:80%;" />
>
> 当 传入 `set` 的 `begin()` 和 `end()` 时，就会把 `set` 内的所有数据都删除
>
> 不过 这个版本一般不是在这种情况下使用的
>
> `set` 内存储的数据，是按照给定的规则排好序的，所以 当需要删除某个区间范围内的数据时，一般会用到 这个版本的删除接口
>
> 而取 `set` 中的一个指定的区间范围，将会用到下面介绍的两个接口函数：`lower_bound` `upper_bound`

### 5. lower_bound 和 upper_bound

<img src="https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/202209022252222.png" alt="image-20220902225250184" style="zoom:80%;" />

<img src="https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/202209022253727.png" alt="image-20220902225304692" style="zoom:80%;" />

 这两个接口函数
