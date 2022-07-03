#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <string>
#include <cassert>
using namespace std;

namespace July
{
	class string
	{
	public:
		/*
		// 构造函数
		// 字符串指针不能是 nullptr, 初始化也不能有内容, 还要满足动态开辟
		// 所以需要在构造函数内部, new 一个大小的为 1大小的字符数组(字符串)
		// str[0] = '\0' 可以表示内容为空, 因为字符串结束标志为 '\0'
		string()
			:_size(0)
			,_capacity(0)
		{
			_str = new char[1];
			_str[0] = '\0';
		}
		// string 构造函数还需要 实现传字符串实例化对象
		// _capacity 和 _size 的大小直接用 字符串的长度赋值
		// 并且在构造函数内部需要，new 一个大小的为 _capacity + 1大小的字符数组(字符串)
		// _capacity 和 _size 都表示有效内容，所以 + 1是为 '\0'留的
		string(const char* str)
			:_size(strlen(str))
			,_capacity(_size)
		// 初始化列表的初始化顺序是按照声明顺序执行的，所以声明需要 _capacity 放在 _size 之后
		{
			_str = new char[_capacity + 1];
			strcpy(_str, str);
		}*/

		// 其实 上面两个构造函数可以合并为一个构造函数
		string(const char* str = "")
			:_size(strlen(str))
			, _capacity(_size)
		{
			_str = new char[_capacity + 1];
			strcpy(_str, str);
		}
		// 只需要将 参数字符串 添加一个缺省参数 ""。就可以实现不传参时，默认参数其实是一个有效长度为0的字符串

		// string类的 拷贝构造要实现为 深拷贝
		// 因为由于浅拷贝是对对象按每字节拷贝的， 对动态开辟的内存空间浅拷贝，会导致不同对象中的两指针共同指向同一块空间
		// 两个对象中的两个指针指向同一块内存空间，会导致两个结果：
		// 1. 同一块空间会被析构两次，导致错误。因为第一次析构之后，那块空间就已经属于操作系统了，无法再操作
		// 2. 一个对象改变数据内容，另一个对象的数据内容也会改变
		// 所以 像这类拷贝构造函数 都要实现深拷贝

		// 那么string 的深拷贝如何实现呢？
		// 先分析 拷贝构造的作用是什么？
		// 由一个已经存在的对象，实例化、初始化一个内容数据完全一样的新对象
		// 所以其实非常的简单
		string(const string& s)
			:_size(s._size)
			,_capacity(s._capacity)
		{
			_str = new char[_capacity + 1];
			strcpy(_str, s._str);
		}

		// 关于类对象赋值 还有个赋值重载函数
		// 赋值重载函数的使用结果与 拷贝构造函数非常相似
		// 即，将一个对象的所有数据内容，拷贝至一个已经实例化的对象中，使两对象数据内容相同
		// 想要实现这种作用，最好的写法之一就是，创建一个新的临时字符串并 strcpy 传参字符串
		// 再将需要赋值的对象的字符串 delete掉，再将临时字符串赋值给它
		// 因为，如果直接给原对象的原字符串空间 赋值，如果原字符串空间小，则会发生错误
		// 如果原字符串空间过大 则会浪费空间
		string& operator=(const string& s)
		{
			if (this != &s)
			{
				char* tmp = new char[s._capacity + 1];
				strcpy(tmp, s._str);
				delete[] _str;
				_str = tmp;
				_size = s._size;
				_capacity = s._capacity;
			}

			return *this;
		}
		// 如果不禁止 自我赋值，则必须将 delete[] _str; 的操作 放在 strcpy(tmp, s._str) 之后
		// 因为 如果自我赋值，则参数s 即为 自己的引用，delete[] _str 也是 delete s._str，这会导致 strcpy 一堆随机值进而导致复制错误
		// 所以 要么禁止 自我赋值，要么 delete[] _str 放在 strcpy(tmp, s._str) 之后

		// 析构函数就相对比较简单了
		~string()
		{
			if (_str)	// 得先保证 _str 不是空指针
			{
				delete[] _str;
				_str = nullptr;
				_size = _capacity = 0;
			}
		}

		// 还有 c_str 返回对象中字符串的 C类指针形式
		char* c_str()
		{
			return _str;
		}

		// [] 操作符重载，实现下标访问、修改字符串内容
		char& operator[](size_t pos)
		{
			assert(pos < _size);		// 下标要合法

			return _str[pos];
		}
		// 还有一个只读功能的 [] 操作符的重载
		const char& operator[](size_t pos) const
		{
			assert(pos < _size);		// 下标要合法

			return _str[pos];
		}

		// size() 返回string有效字符大小
		size_t size() const		// 不修改原对象的尽量加上 const
		{
			return _size;
		}

		// capacity() 返回 string 有效字符容量
		size_t capacity() const
		{
			return _capacity;
		}



	private:
		char* _str;
		size_t _size;
		size_t _capacity;

		const static size_t npos;
	};

	const size_t string::npos = -1;
}




int main()
{
	July::string s1("hello world");
	July::string s2;

	s2 = s1;
	s2 = s2;

	return 0;
}