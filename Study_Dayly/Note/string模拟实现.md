# string类 模拟实现

上篇文章中介绍了 C++的 string类 及 string类的接口

本篇文章着重 模拟实现 string类 及其各接口

## string类的结构

string类 实质上其实就是一个提供了许多功能接口的字符串

但是 string类 除了字符串之外, 类中还提供了 表示字符串大小和容量的变量

所以 string类的结构应该是：

```cpp
class string {
private:
    char* _str;				// 字符串
    size_t _size;			// 字符串实际长度
    size_t _capacity;		 // 字符串指针表示的字符串的容量
};
```

## 构造函数

string类 的构造函数需要实现的功能有：

1. 默认实例化 空string
2. 使用 C字符串 实例化string
3. 使用其他string对象 实例化 新的string对象

`默认构造函数`可以实现前两个功能，`拷贝构造函数`则用于实现第三个功能

### 默认构造函数

> string 的默认构造函数 首先需要实现 实例化空string时的初始化设置
>
> ```cpp
> string() 
>     : _size(0)
>     , _capacity(0);
> {
>     _str = new char[1];
>     _str[0] = '\0';
> }
> ```
>
> 首先 字符串要提供扩容的功能, 所以字符串需要 满足动态管理, 所以 实例化空string类时 需要new char[1] 并将字符串唯一一个空间设置为‘\0’ 表示字符串为空
>
> 若要实现 使用C字符串 实例化string
>
> ```cpp
> string(const char* str) 
>     : _size(strlen(str))
>     , _capacity(_size)
> {
>     _str = new char[_capacity + 1];
>     strcpy(_str, str);
> }
> ```
>
> 使用了 字符串函数 来进行字符串的拷贝
>
> 不过 这两个构造函数可以合并在一起由 一个构造函数来实现：
>
> ```cpp
> string(const char* str = "")
>     : _size(strlen(str))
>     , _capacity(_size)
> {
>     _str = new char[_capacity + 1];
>     strcpy(_str, str);
> }
> ```

### 拷贝构造函数

拷贝构造函数 需要实现用 旧string对象 实例化 新string对象

一般来说 手动实现的拷贝构造函数 提供`深拷贝`功能

> ```cpp
> string(const string& s)
>     : _size(s._size)
>     , _capacity(s._capacity)
> {
>     _str = new char[_capacity + 1];
>     strcpy(_str, s._str);
> }
> ```
>
> 这是传统的 拷贝构造函数的实现方法
>
> 拷贝构造函数的实现还有更加便捷的实现：
>
> ```cpp
> void swap(string& s) {
>     std::swap(_str, s._str);
>     std::swap(_size, s._size);
>     std::swap(_capacity, s._capacity);
> }
> string(const string& s) {
>     string tmp(s._str);
>     swap(tmp);
> }
> ```
>
> 这种拷贝构造函数的写法, 其实是调用了 字符串构造string类的构造函数, 然后使用swap函数将临时string对象的内容与 新string类内容做交换
>
> 就完成了拷贝构造函数