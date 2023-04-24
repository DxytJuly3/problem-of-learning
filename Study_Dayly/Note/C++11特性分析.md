---
layout: '../../layouts/MarkdownPost.astro'
title: '[C++] C++11新特性分析介绍：列表初始化、右值引用'
pubDate: 2023-04-21
description: ''
author: '七月.cc'
cover:
    url: ''
    square: ''
    alt: 'cover'
tags: ["C++", "C++11", "语法"]
theme: 'light'
featured: false
---



---

# C++11

## 介绍

在2003年C++标准委员会曾经提交了一份技术勘误表(简称TC1)，使得C++03这个名字已经取代了C++98称为C++11之前的最新C++标准名称。不过由于`C++03`主要是`对C++98标准`中的漏洞进行`修复`，语言的`核心部分则没有改动`，因此人们习惯性的把`两个标准合并称为C++98/03标准`。

从C++0x到C++11，C++标准10年磨一剑，第二个真正意义上的标准珊珊来迟。相比于C++98/03，`C++11`则带来了`数量可观的变化`，其中包含了约`140个新特性`，以及对`C++03标准中约600个缺陷的修正`，这使得C++11更像是从C++98/03中孕育出的一种新语言。

相比较而言，`C++11能更好地用于系统开发和库开发、语法更加泛华和简单化、更加稳定和安全`，不仅功能更强大，而且能提升程序员的开发效率，公司实际项目开发中也用得比较多。

C++11增加的语法特性非常篇幅非常多，我们这里没办法一一讲解，所以关于C++11只介绍实际中`比较实用的语法` 

## 列表初始化

C++11, 为变量、对象、容器提供的一种新的初始化的方式：`{} 初始化`

具体的使用就像这样：

```cpp
struct Point {
    int _x;
    int _y;
};

int main() {
    int a = 1;
    int b = {2};
    int c{3};

    Point po1 = {1, 2};
    Point po2{1, 2};

    int array1[] = {1, 2, 3, 4, 5};
    int array2[5]{1, 2, 3, 4, 5};

    return 0;
}
```

我们可以在定义变量时, 直接使用 `{}` 对对象进行初始化.

除了简单的对象初始化, 还可以对多成员变量的自定义类进行初始化：

```cpp
class Date {
public:
    Date(int year, int month, int day)
        : _year(year)
        , _month(month)
        , _day(day) {
        cout << "Date(int year, int month, int day)" << endl;
    }

private:
    int _year;
    int _month;
    int _day;
};

int main() {
    Date d1(2022, 1, 1);

    // C++11支持的列表初始化，这里会调用构造函数初始化
    Date d2{2022, 1, 2};
    Date d3 = {2022, 1, 3};

    return 0;
}
```

以前, 对于自定义类实例化对象, 我们一般都会使用 `Date d1(2022, 1, 1);`

C++11 之后, 就也可以使用 `{} 列表初始化`

但是, 这些使用好像有些没用. 

不过下面这样的使用, 就比之前初始化要好用一些：

```cpp
int main() {
	 vector<int> v1{1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
    vector<int> v2 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
    vector<int>* v3 = new vector<int>[4]{ {1,2,3,4},{5,6,7,8},{9,10,11,12},{12,13,14,15} };
    
    return 0;
}
```

我们可以直接使用 `{}` 对容器进行初始化, 更可以在 `new` 时使用 `{}` 对数组进行初始化.

而, C++11 是怎么实现这样的东西的呢？

## `std::initializer_list`

我们可以这样来查看 `{}` 的类型：

```cpp
int main() {
	 auto li = {1,2,3,4,5};
    cout << typeid(li).name() << endl;

    return 0;
}
```

![|inline](https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/image-20230421230206878.png)

可以看到, `auto` 接收 `{}` 的类型是： `initializer_list`

![ ](https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/image-20230421230507279.png)

其实, `{}` 本身就是一个类型. `{1, 2, 3, 4, 5}`  就是通过 `initializer_list<int>` 实例化出的一个对象. 

我们这样初始化：

```cpp
int main() {
	 vector<int> v1{1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
    vector<int> v2 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
    vector<int>* v3 = new vector<int>[4]{ {1,2,3,4},{5,6,7,8},{9,10,11,12},{12,13,14,15} };
    
    return 0;
}
```

本质上, 其实就是调用了 以 `{}` 对象为参数的构造函数来实例化对象. 

因为, STL容器中其实定义有 使用 `{}` 对象的构造函数. 

![ ](https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/image-20230421231101708.png)

其他STL 容器中 也同样如此：

`set:`

![ ](https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/image-20230421231220240.png)

```cpp
int main() {
 	 set<int> s1{1, 2, 3, 4, 5, 6, 7};
    set<int> s2 = {1, 2, 3, 4, 5, 6, 7};

	 return 0;
}
```

`map:`

![ ](https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/image-20230421231410254.png)

```cpp
int main() {
	 map<string, string> dict ={ {"apple", "苹果"}, {"banana", "香蕉"}, {"sun", "太阳"} };
    
	 return 0;
}
```

STL容器, 在C++11 之后 都支持了以 `initializer_list` 对象为参数的构造函数.

也就是说, STL容器实现`{}`初始化对象是通过 实现了针对 `initializer_list` 类型的构造函数. 

而我们自己自定义的多成员变量的类是怎么实现的呢？

其实是 `隐式类型转换 + 编译优化`. 比较`类似 C++11 之前, 单个成员变量的类的直接赋值初始化`.

## 新的声明

C++中, 我们除了可以使用各种类型来声明变量、对象、函数之外.

C++11 提供了一些新的声明方式

### `auto`

首先就是 auto. auto我们经常使用, 并且很早就已经介绍过了

auto 会根据对象、变量的赋值类型去自动推导 对象、变量的类型.

```cpp
int main() {
    int b = 1;
    auto c = 3.3;
    cout << typeid(c).name() << endl;
    
    return 0;
}
```

![|inline](https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/image-20230421235831586.png)

不过, auto 一般用于非常长的容器的迭代器的自动推导

### `decltype`

`decltype` 可以用来推导 表达式的类型：

```cpp
int main() {
    decltype(2 * 2.2) d;
    cout << typeid(d).name() << endl;
    
    return 0;
}
```

![|inline](https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/image-20230422000102443.png)

### `nullptr`

我们一直在C++中使用 `nullptr` 来表示空指针. 而 `nullptr` 实际上是C++11才提出的

在C语言中, 通常使用NULL作为空指针. 不过 NULL 在C语言中其实就是0. 有时可能会被检测为整型. 

所以 C++11 就是用了nullptr.

## 范围for

范围for, 其实是一种变量容器数据的一种方法. 可以对所有支持 `iterator 迭代器` 的容器使用：

```cpp
int main() {
    vector<int> v = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    for(auto e : v) {
        cout << e << " ";
    }

    return 0;
}
```

![ |inline](https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/image-20230422000634152.png)

## 智能指针

C++11 提出一个很重要的概念, 就是智能指针. 

不过本篇文章不做介绍, 会单独写一篇文章介绍 C++11 的智能指针.

## STL 新容器

C++11 为STL 添加了四个新容器：

![ |wide](https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/image-20230422000948161.png)

处理哈希表, 另外两个其实没有什么值得介绍的. 

`array`就是静态数组, 与我们平时 `int arr[10];` 没什么区别. 值得说的就是 `默认支持了越界检查`

`forward_list` 就是单链表. 以方便使用来说, 还是 `list` 好用.

而另外的 哈希表, 博主有专门介绍的文章：

> 文章

## 右值引用 **

