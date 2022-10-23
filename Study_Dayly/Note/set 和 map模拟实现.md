# set 和 map 模板参数

STL容器中, set 和 map 虽然底层都是红黑树, 但是这两个容器的模板参数是不一样的, 在只考虑数据类型的情况下：

set 是 `template<class key>`

map 则是 `template<class key, class val>`

很明显, 两种容器的模板参数数量都是不同的

要如何解决 相同的底层实现, 但是不同的模板参数呢？

有两种很简单粗暴的解决方法：

1. 对set设计一个只有单个数据的红黑树; 对map设计一个 两个数据类型的红黑树
2. 设计一个 两个数据类型的红黑树, 但是实现set时, 模板参数默认传0

但是 这两种方法 一个浪费, 一个粗暴，都不是那么的优秀

简单分析一下 STL源码是怎么解决这个问题的：

>  STL关于 set的部分源码： <img src="https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/image-20221023161225036.png" alt="image-20221023161225036" style="zoom:67%;" />
>
> 可以看到, typedef红黑树的部分, 红黑树的模板参数传参是 `<key_type, value_type>`
>
> 而 `key_type` 和 `value_type` 其实都是 `Key`

>  STL关于 map的部分源码： <img src="https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/image-20221023161511574.png" alt="image-20221023161511574" style="zoom:67%;" />
>
> map中 typedef红黑树的部分, 红黑树的模板参数传参 也是 `<key_type, value_type>`
>
> 但是 map的 `key_type` 是 `Key`, 而 `value_type` 是 `pair<const Key, T>`

只看 set 和 map 类型的部分源码基本看不出什么, 只能看出 STL实现两容器 底层使用的是有两个数据模板参数的红黑树

想要进一步看出具体的解决方案, 还要阅读一下 红黑树的部分源码

>  STL关于 红黑树的部分源码：<img src="https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/image-20221023155204283.png" alt="image-20221023155204283" style="zoom: 67%;" />
>
>  图中, 左半部分 是关于红黑树节点的部分源码; 右半部分 是关于红黑树结构的部分源码
>
>  阅读左半部分的源码, 可以发现 STL实现红黑树节点, 使用了继承：
>
>  ​	将 每个节点都具有的部分：颜色 父亲 左孩子 右孩子 定义为类 `rb_tree_node_base`; 定义另一个类 只拥有一个Value类型的成员变量, 其他继承于子类
>
>  再阅读右半部分的源码, 发现 Key 被typedef为 key_type, Value 被typedef为 value_type. 而 __rb_tree_node<Value> 被typedef为 rb_tree_node