#pragma once

#include <iostream>
#include <cassert>

namespace July
{
	template<class T>
	class vector
	{
	public:
		typedef T* iterator;
		typedef const T* const_iterator;
		// 构造函数
		vector()
			:_start(nullptr)
			, _finish(nullptr)
			, _endofstoage(nullptr)
		{}

		// vector库中实现了可以用n个val (val 是T类型的数据) 构造对象的构造函数
		vector(size_t n, const T& val = T())
			: _start(nullptr)
			, _finish(nullptr)
			, _endofstoage(nullptr)
		{
			reserve(n);		// 先reserve
			while (_finish < _endofstoage)
			{
				push_back(val);
			}
		}
		// 为解决 vector(int, int) 类型传参时
		// 会去调用 template <class InputIterator>
		//        vector(InputIterator first, InputIterator last)的问题
		// 因为，int int 是相同类型的传参，传参时编译器会调用最适合的传参类型，如果不重载一个传参类型 int, T的构造函数
		// 则传参 int int 类型时，会发生不调用 用n个val (val 是T类型的数据) 构造对象的构造函数
		vector(int n, const T& val = T())
			: _start(nullptr)
			, _finish(nullptr)
			, _endofstoage(nullptr)
		{
			reserve(n);		// 先reserve
			while (_finish < _endofstoage)
			{
				push_back(val);
			}
		}

		// vector库中实现了 可以用两个 iterator 构造对象的构造函数
		template <class InputIterator>
		vector(InputIterator first, InputIterator last)
			: _start(nullptr)
			, _finish(nullptr)
			, _endofstoage(nullptr)
		{
			while (first != last)
			{
				push_back(*first);
				++first;
			}
		}

		void swap(vector<T>& v)
		{
			std::swap(_start, v._start);
			std::swap(_finish, v._finish);
			std::swap(_endofstoage, v._endofstoage);
		}

		// = 赋值重载函数，现代写法
		// 与 string赋值重载现代写法一样，利用传值传参拷贝一个临时变量的特性
		// 直接将this与此临时变量交换数据
		vector<T>& operator=(vector<T> v)
		{
			swap(v);
			return *this;
		}

		/*vector<T>& operator=(vector<T> v)
		{
			swap(v);

			return *this;
		}*/
		//  现代写的拷贝构造 是使用上面那个 两 iterator 构造函数 构造对象tmp
		//  并将 this 与 tmp 用swap交换数据, 由于只交换数据则需要自己实现swap，不能调用库swap
		vector(const vector<T>& v)
			: _start(nullptr)
			, _finish(nullptr)
			, _endofstoage(nullptr)
		{
			vector<T> tmp = vector(v.begin(), v.end());
			swap(tmp);
		}

		// 析构函数
		~vector()
		{
			if (_start)
			{
				delete[] _start;
				_start = _finish = _endofstoage = nullptr;
			}
		}

		void clear()
		{
			delete[] _start;
			_start = _finish = nullptr;
		}

		iterator begin()
		{
			return _start;
		}
		iterator end()
		{
			return _finish;
		}
		const_iterator begin() const
		{
			return _start;
		}
		const_iterator end() const
		{
			return _finish;
		}

		size_t size() const
		{
			return _finish - _start;
		}
		size_t capacity() const
		{
			return _endofstoage - _start;
		}

		// reserve 扩容
		void reserve(size_t n)
		{
			// 需要先记录原本size的大小
			// 因为 vector的实现框架 表示数组、数组大小、数组容量的变量都是 iterator
			// vector的有效数据数量，计算应该是 _finish - _start，但是开辟新空间之后，_finish 会变为 nullptr，无法相减 
			// 所以 vector的扩容之后，不能像 string一样直接首元素地址+_size 改变新对象的大小
			// 而是需要提前记录原对象数据大小，扩容之后，再使用 _start + sz 获得 _finish; 
			size_t sz = size();
			if (_start + n > _endofstoage)
			{
				T* tmp = new T[n];
				if (_start)	// 原对象内有数据 就需要拷贝数据到新数据空间中，并且释放原对象数据空间
				{
					// 这里用 memcpy 可能会发生深浅拷贝的问题，集中于 T为需要动态管理内存的类型时
					// 建议画图、调试分析
					// 所以不能用 memcpy直接拷贝内容，只能对单个空间数据，单独进行复制 赋值
					//  
					// memcpy(tmp, _start, size() * sizeof(T));
					for (int i = 0; i < size(); i++)
					{
						tmp[i] = _start[i];
					}
					delete[] _start;
				}
				// 将新数据空间给_start
				_start = tmp;
			}
			// 不能 _finish = _finish - _start,因为当前的_finish 和 _start 不在同一片空间 
			_finish = _start + sz;
			_endofstoage = _start + n;
		}
		// T() 定义匿名对象，其生命周期仅在其定义的一行
		// T是模板参数，也就意味着在C++中除了自定义类型以外，其实内置类型也有构造函数，可加已测试
		void resize(size_t n, T val = T())
		{
			if (n > capacity())
			{
				reserve(n);
			}
			else if (n > size() && n < capacity())
			{
				while (_finish < _start + n)
				{
					*_finish = val;
					_finish++;
				}
			}
			else
			{
				_finish = _start + n;
			}
		}

		void push_back(const T& val)
		{
			if (_finish == _endofstoage)
			{
				size_t newCapacity = !_endofstoage ? 4 : capacity() * 2;
				reserve(newCapacity);
			}
			*_finish = val;
			_finish++;
		}

		void pop_back()
		{
			if (_finish > _start)
				--_finish;
		}

		T& operator[](size_t pos)
		{
			assert(_start + pos < _finish);

			return _start[pos];
			//return *(_start + pos);
		}
		const T& operator[](size_t pos) const
		{
			assert(_start + pos < _finish);

			return _start[pos];
			//return *(_start + pos);
		}

		// vector 中的 insert 与 string中的 insert参数不同，使用的是 iterator 作为插入位置地址,且有返回值 也为 iterator 类型的
		// vector中的返回值是为了解决 迭代器失效的问题 下面再考虑
		// insert的实现 需要移动数据，但是 iterator作为pos位置，就可以不用像string一样注意 size_t pos = -1的问题
		iterator insert(iterator pos, const T& val)
		{
			assert(pos >= _start && pos <= _finish);

			if (_finish == _endofstoage)
			{
				size_t posForS = pos - _start;
				size_t newCapacity = !_endofstoage ? 4 : capacity() * 2;
				reserve(newCapacity);

				pos = _start + posForS;
			}

			iterator end = _finish - 1;
			while (end >= pos)
			{
				*(end + 1) = *end;
				end--;
			}

			*pos = val;
			_finish++;

			// 模拟实现STL库中的 vector，就需要框架、参数、返回值等相同
			// STL库vector的insert 返回的位置是第一个新插入元素的位置，即 pos
			return pos;
		}

		iterator erase(iterator pos)
		{
			assert(pos >= _start && pos <= _finish);

			iterator begin = pos + 1;
			while (begin < _finish)
			{
				*(begin - 1) = *begin;
				begin++;
			}

			_finish--;

			// vector库中的 erase返回 最后一个被删除元素的下一个元素的位置，其实还是pos位置
			return pos;
		}

		vector<vector<int>> generate(int numRows)
		{
			vector<vector<int>> vv;
			vv.resize(numRows);
			for (int i = 0; i < vv.size(); i++)
			{
				// 每行vector<int> 的size递增，且初始化为零
				vv[i].resize(i + 1, 0);

				// 每行的第一个、最后一个元素赋值为1
				*(vv[i].begin()) = 1;
				*(vv[i].end()) = 1;
			}

			for (int i = 0; i < vv.size(); i++)
			{
				for (int j = 0; j < vv[i].size(); j++)
				{
					// vector<int> 中所有数据被初始化为0
					// 但是上面已经对杨辉三角外层数据置1
					// 所以数值为0的需要计算
					if (vv[i][j] == 0)
					{
						vv[i][j] = vv[i - 1][j - 1] + vv[i - 1][j];
					}
				}
			}

			return vv;
		}

	private:
		iterator _start;
		iterator _finish;
		iterator _endofstoage;
	};
}
