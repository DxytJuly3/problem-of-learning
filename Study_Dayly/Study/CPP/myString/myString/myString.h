#pragma once
#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <string>
#include <cassert>
using namespace std;

namespace July
{
	class string
	{
		friend istream& operator>>(istream& in, string& s);
		friend istream& operator<<(istream& in, string& s);
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

		// 拷贝构造传统写法
		/*string(const string& s)
			:_size(s._size)
			, _capacity(s._capacity)
		{
			_str = new char[_capacity + 1];
			strcpy(_str, s._str);
		}*/
		void swap(string& s)
		{
			std::swap(_str, s._str);
			std::swap(_size, s._size);
			std::swap(_capacity, s._capacity);
		}
		// 拷贝构造现代写法
		// 由传入对象的字符串，创建局部对象，再将this与局部对象的内容交换，完成拷贝构造
		string(const string& s)
		{
			string tmp(s._str);
			swap(tmp);
		}

		// 关于类对象赋值 还有个赋值重载函数
		// 赋值重载函数的使用结果与 拷贝构造函数非常相似
		// 即，将一个对象的所有数据内容，拷贝至一个已经实例化的对象中，使两对象数据内容相同
		// 想要实现这种作用，最好的写法之一就是，创建一个新的临时字符串并 strcpy 传参字符串
		// 再将需要赋值的对象的字符串 delete掉，再将临时字符串赋值给它
		// 因为，如果直接给原对象的原字符串空间 赋值，如果原字符串空间小，则会发生错误
		// 如果原字符串空间过大 则会浪费空间

		// 赋值重载传统写法
		/*string& operator=(const string& s)
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
		}*/
		// 如果不禁止 自我赋值，则必须将 delete[] _str; 的操作 放在 strcpy(tmp, s._str) 之后
		// 因为 如果自我赋值，则参数s 即为 自己的引用，delete[] _str 也是 delete s._str，这会导致 strcpy 一堆随机值进而导致复制错误
		// 所以 要么禁止 自我赋值，要么 delete[] _str 放在 strcpy(tmp, s._str) 之后

		// 赋值重载现代写法
		// 赋值重载的第一种现代写法，与拷贝构造的现代写法 几乎一样
		/*string& operator=(const string& s)
		{
			if (this != &s)		// 禁止自我赋值
			{
				string tmp(s._str);
				swap(tmp);
			}

			return *this;
		}*/
		// 赋值重载的第二种写法，更加简单
		// 利用了传值传参 会对实参进行临时拷贝的特性，直接与这个临时拷贝的数据交换
		string& operator=(string s)
		{
			swap(s);

			return *this;
		}

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

		// 迭代器的实现
		// 在 string 和 vector中，迭代器其实就是指针
		typedef char* iterator;				// 普通迭代器
		typedef const char* const_iterator;		// const 类型迭代器

		// begin()函数 返回string中字符串首字符地址
		iterator begin()
		{
			return _str;
		}
		const_iterator begin() const
		{
			return _str;
		}
		// end()函数 返回string中字符串结尾的'\0'地址
		iterator end()
		{
			return _str + _size;
		}
		const_iterator end() const
		{
			return _str + _size;
		}

		// 还有 c_str 返回对象中字符串的 C类指针形式
		// 按照库中的类型 const修饰
		const char* c_str() const
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

		// 还有两个非常重要的函数实现
		// reserve 和 resize
		// reserve 需要实现 指定大小扩容，但是不能缩容，且不改变实际size只改变 capacity
		// C++ 中new 取消了 realloc扩容 的思路，因为 realloc实现机制有些麻烦
		// 所以C++ 中一般采用直接重新开辟一块新空间 来代替原空间
		void reserve(size_t n)
		{
			if (n > _capacity)			// n 比 _capacity大才改变容量，不缩容
			{
				char* tmp = new char[n + 1];
				strcpy(tmp, _str);		// 原空间数据存入新空间内
				delete[] _str;

				_str = tmp;
				_capacity = n;			// _capacity 大小改为n
			}
		}

		// resize 需要实现 ：
		// 1. 当 n < _size 时, _size 变为 n, 并需要在 _size 位置放入'\0' 截断原字符串
		// 2. 当 n > _size 时, _size 变为 n, 并且在原数据之后新增的空间初始化为 '\0' 或 指定字符
		//	  
		// 总结, resize 改变当前字符串有效长度, 
		// n 比当前长度小, 则截断字符串;
		// n 比当前长度大,但比容量小, 则不扩容, 只将有效字符串长度改为 n
		// n 比当前长度大,但比容量大, 则扩容,_capacity和_size都需要变为n, 至少 _capacity要 >= n
		// 并且, 改变 字符串长度会改变非原字符串的空间
		void resize(size_t n, char ch = '\0')
		{
			if (n < _size)		// 截断字符串
			{
				_size = n;
				_str[_size] = '\0';
			}
			else
			{
				if (n > _capacity)		//n 比 _capacity大时, 需要扩容 
				{
					reserve(n);
				}

				for (size_t i = _size; i < n; i++)		// 从 _size 位置向后初始化 置 n-1, 因为 n位置, 需要放入'\0' 表示字符串结束
				{
					_str[i] = ch;
				}
				_size = n;;
				_str[n] = '\0';
			}
		}

		// 尾插字符函数  push_back
		// 容量不够需扩容
		void push_back(char ch)
		{
			if (_size == _capacity)
			{
				reserve(_capacity == 0 ? 4 : _capacity * 2);	// 判断_capacity是否为零是 防止空字符串 扩容错误
			}

			_str[_size] = ch;
			_size++;
			_str[_size] = '\0';		// 尾插完，记得补'\0'

			/*insert(_size, ch);*/	// 复用 insert
		}

		void append(const char* str)
		{
			size_t len = strlen(str);
			if (_size + len > _capacity)
			{
				reserve(_capacity == 0 ? len : _capacity + len);
			}

			strcpy(_str + _size, str);	// 从 _str + _size 位置开始拷贝 str
			_size = _size + len;
			// strcpy 会拷贝 字符串末尾的 '\0' 所以不用手动补'\0'

			/*insert(_size, str);*/	// 复用 insert
		}

		// insert 在指定位置插入 字符、字符串、对象
		// insert 的实现有一个非常重要的步骤就是: 挪动数据
		// 无论是插入什么, 只要不是尾插都需要挪动数据
		// 如果是插入一个字符，则 pos位置及后面的数据，都需要向后挪动 1 位
		// 如果是字符串或对象, 则需要向后挪动 n 位
		// 
		// 先来实现字符的插入
		string& insert(size_t pos, char ch)
		{
			assert(pos <= _size);		// pos位置 需要合法

			if (_size == _capacity)
			{
				reserve(_capacity == 0 ? 4 : _capacity * 2);
			}

			size_t end = _size + 1;
			// 1. end位置在 _size+1, 挪动数据的步骤就是将 end-1 位置的数据一个一个挪至end
			// 2. 如果 end位置在 _size, 则挪动数据的步骤是将 end位置的数据 挪至 end+1
			// (两种方法 从 '\0' 开始挪动)
			// 表面看 两种方法好像都一样，但是 如果end的初始位置是_size, 需要额外处理 pos位置为0的情况
			// 因为 当pos位置为零时, 方案二 end的结束位置应该在 -1, 但是 end是 size_t 类型的数据, 所以end永远不会为-1, 即会死循环
			// 而 方案一 不会有这种情况，方案一 如果 pos为0, 循环结束时 end == pos, 会退出循环
			while (end > pos)
			{
				_str[end] = _str[end - 1];
				end--;
			}
			_str[pos] = ch;
			_size++;

			return *this;
		}
		// insert 插入字符串实现
		// insert插入字符串 数据就不能一位一位的向后挪动了
		// 
		string& insert(size_t pos, const char* str)
		{
			assert(pos <= _size);

			size_t len = strlen(str);
			if (_size + len > _capacity)
			{
				reserve(_capacity == 0 ? len : _capacity + len);
			}

			size_t end = _size + len;
			while (end > pos + len - 1)		// 可以画图判断一下end结束位置
			{
				_str[end] = _str[end - len];
				end--;
			}
			strncpy(_str + pos, str, len);		// 使用strncpy 可以防止字符串的'\0' 也被拷贝进去
			_size += len;

			return *this;
		}
		// insert 插入 对象  直接复用insert插入字符串就可以
		string& insert(size_t pos, const string& s)
		{
			assert(pos <= _size);

			insert(pos, s._str);

			return *this;
		}
		/*实现了 insert之后, append 和 push_back 可以直接复用 insert*/


		// 下面实现 += 的重载都可以直接复用 append 或者 push_back 或者 insert
		string& operator+=(const string& s)
		{
			insert(_size, s);		// += 对象复用 insert
			return *this;
		}
		string& operator+=(const char* str)
		{
			append(str);			// += 字符串复用 append
			return *this;
		}
		string& operator+=(char ch)
		{
			push_back(ch);		// += 字符 复用 push_back
			return *this;
		}

		// earse 的作用是, 从pos位置 向后删除指定长度
		// 如果不传参指定长度, 则从 pos 向后删完
		string& earse(size_t pos, size_t len = npos)
		{
			assert(pos < _size);
			
			// 当从pos位置向后删除的长度大于 字符串长度时, 不用考虑挪动数据 直接修改 _size 和 结尾符 '\0'
			if (len == npos || pos + len >= _size)		
			{
				_str[pos] = '\0';
				_size = pos;
			}
			else
			{
				size_t begin = pos + len;
				while (begin <= _size)
				{
					_str[begin - len] = _str[begin];
					begin++;
				}
				_size -= len;
			}

			return *this;
		}

		// find 就是找字符然后返回其位置
		// 找到就返回位置 找不到就返回 npos
		size_t find(char ch, size_t pos = 0)
		{
			assert(pos < _size);

			for (; pos < _size; pos++)
			{
				if (_str[pos] = ch)
					return pos;
			}

			return npos;
		}

		// 还有find找字符串
		size_t find(const char* str, size_t pos = 0)
		{
			assert(pos < _size);

			//直接用strstr()找字符串的地址，找到就返回字符串首字符的地址，找不到就返回空指针
			// 找到的话  找到的str的地址 - 原字符串的地址 就是字符串首字符的在string中的位置
			const char* ps = strstr(_str + pos, str);
			if (ps != nullptr)
			{
				return ps - _str;
			}

			return npos;
		}

		void clear()
		{
			resize(0);
		}

	private:
		char* _str;
		size_t _size;
		size_t _capacity;

		const static size_t npos;
	};

	const size_t string::npos = -1;

	// 然后就是 对象大小的比较了
	// 按照之前日期类的思路，只需要实现两个逻辑判断的重载函数，其他判断只需要复用就可以了

	// 实现 > 和 == 都用strcmp来对字符串作比较
	bool operator>(const string& s1, const string& s2)
	{
		return strcmp(s1.c_str(), s2.c_str()) > 0;
	}
	bool operator==(const string& s1, const string& s2)
	{
		return strcmp(s1.c_str(), s2.c_str()) == 0;
	}
	bool operator>=(const string& s1, const string& s2)
	{
		return s1 > s2 || s1 == s2;
	}
	bool operator<(const string& s1, const string& s2)
	{
		return !(s1 >= s2);
	}
	bool operator<=(const string& s1, const string& s2)
	{
		return s1 < s2 || s1 == s2;
	}
	bool operator!=(const string& s1, const string& s2)
	{
		return !(s1 == s2);
	}

	// 还有就是 string 的流插入和流提取操作符的重载
	// 首先是流插入，实现对string类字符串的输出
	ostream& operator<<(ostream& out, const string& s)
	{
		// 其实就是string类的字符串遍历
		// 三种方法使用哪种方法都行
		// 下面使用 范围for 比较简单 (使用之前需要实现 迭代器)
		for (auto ch : s)
		{
			out << ch;
		}

		return out;
	}

	// 流提取操作符重载 以实现string类字符串的写入
	istream& operator>>(istream& in, string& s)
	{
		// C++库中 string 类的 cin 效果是 完全将原字符串替换为写入的字符串，被替换的还有_size
		// 且 如果原来的 _capacity 不足以容纳输入的字符串，就扩容；如果足以容纳，则_capacity 不变
		// 并且 cin >> 的操作 会以 ' ' 和 '\n' 为结束标志
		// 具体操作就是:
		// 首先 实现的效果是 完全将原字符串替换为写入的字符串, 所以需要先清楚 string 类中的内容
		// C++库中 string 有 clear()函数 是清楚字符串内容的，这里需要自己实现
		// 然后就是 定义一个char变量 来循环接收输入的字符 并 += 至s字符串中(字符串已用clear清除，所以用+=)
		// 但是注意，接收输入的字符不能用 cin>> 接收，因为 cin也不能接收' ' 和 '\n'，所以会导致无法判断结尾
		// 这里接受字符 会用到输入流类的一个成员函数 get() 这个函数接收 单个字符没有限制
		// 因为 ch的内容要用来判断循环结束，所以ch第一次接收无法在循环内接收，所以需要在循环外第一次接收字符
		// 然后在设置循环就可以了
		/*char ch;
		s.clear();
		ch = in.get();
		while (ch != ' ' && ch != '\n')
		{
			s += ch;
			ch = in.get();
		}

		return in;*/


		// 对与 >> 的重载，还有一种上面那个方法的优化版本
		// 如果使用上面那种方法 输入一个很长的字符串, 由于是一个一个字符接收并 += 的, 会造成频繁的扩容，就会消耗许多资源
		// 所以有一种优化方法
		// 将输入的字符串先存在一个字符数组中，字符数组满了再一次性 += 至string字符串中
		// 如果字符数组未满时，就已经换行或者接收到了' ' 就直接将当前的字符数组内容 += 至 string字符串中
		// 这样 可以有效地优化 当输入一个长字符串时 频繁扩容的消耗
		char ch;
		s.clear();		// 清理string原字符串
		ch = in.get();
		char tmp[128] = { '\0' };		//字符数组内容初始化为 '\0'，大小适合就可以
		size_t i = 0;			// 用来访问字符数组下标赋值，以及记录字符数组中字符个数
		while (ch != ' ' && ch != '\n')
		{
			tmp[i++] = ch;
			if (i == 127)	// 字符数组大小为 128, 看作字符串的话, 可容纳有效字符数就是 127, 因为最后一位'\0'作为结束标志
			{
				// 字符数组一满, 就将字符数组中的内容 += 至string对象, 然后清空字符数组
				s += tmp;
				memset(tmp, '\0', 128);	// 使用 memset 将字符数组所有空间设置为 '\0' 以防下次 += 会出错
				i = 0;
			}
			ch = in.get();
		}
		s += tmp;		// 循环结束, 再将字符数组中还有的内容 += 至string对象

		return in;
	}

	// 上面访问私有成员的类外函数 建立为友元函数
}
