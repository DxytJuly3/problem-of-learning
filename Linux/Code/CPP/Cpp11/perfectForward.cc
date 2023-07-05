#include <iostream>
#include <ostream>
#include <string>
#include <cassert>
#include <cstring>

using std::string;
using std::istream;
using std::ostream;
using std::cout;
using std::endl;

namespace July {
	class string {
		friend istream& operator>>(istream& in, string& s);
		friend istream& operator<<(istream& in, string& s);
	public:
		// 默认构造函数
		string(const char* str = "") 
			: _size(strlen(str))
			, _capacity(_size)
		{
			cout << "默认构造" << endl;
			_str = new char[_capacity + 1];
			strcpy(_str, str);
		}

		string(string&& str) {
			cout << "移动构造" << endl;
		}

		// 拷贝构造函数 传统
		string(const string& s)
			: _size(s._size)
			, _capacity(s._capacity)
		{
	        cout << "拷贝构造" << endl;
			_str = new char[_capacity + 1];
			strcpy(_str, s._str);
		}
	    
	    // 赋值重载 传统写法
	    string& operator=(const string& s) {			// string&返回值 可以实现连续赋值
			if (this != &s) {					// 对比 s 与 自己的地址, 禁止自我赋值
				char* tmps = new char[s._capacity + 1];
				strcpy(tmps, s._str);
				delete[] _str;
				_str = tmps;
				_size = s._size;
				_capacity = s._capacity;
			}
	    
			return *this;			// 返回当前对象的地址
		}
	    
		void reserve(size_t n) {
			if(n > _capacity) {				// n 比原空间大才执行操作
				char* tmps = new char[n + 1];
				strcpy(tmps, _str);
				delete[] _str;				// 释放原字符串所在的堆空间
	
				_str = tmps;
				_capacity = n;				// 更改 string对象的_capacity 为n
			}
		}
	
		void resize(size_t n, char ch = '\0') {				// 第二个参数是指定字符
			if (n < _size) {
				// 截断字符串
				_size = n;
				_str[n] = '\0';
			}
			else {
				if (n > _capacity) {
					// 需要扩容
					reserve(n);
				}	
	
				for (size_t i = _size; i < n; i++) {
					_str[i] = ch;					// 填充字符操作
				}
				_size = n;
				_str[n] = '\0';
			}		
		}
	    
	     // 尾插字符
		void push_back(char ch) {
			if (_size == _capacity) {
				reserve(_capacity == 0 ? 4 : _capacity*2);				// 两倍扩容
			}
		
			_str[_size] = ch;							// 在 size位置插入新字符
	 		_size++;
	 		_str[_size] = '\0';							// 结尾放 '\0'
		}
	    
	     // 尾插 字符串
		void append(const char* str) {
			size_t len = strlen(str);
			if (_size + len > _capacity) {
				reserve(_capacity == 0 ? len : _capacity + len);
			}
	
			strcpy(_str + _size, str);				// 从字符串末尾处拷贝 str
			_size += len;
		}
	    
	     // 插入字符
		string& insert(size_t pos, char ch) {
			assert(pos <= _size);		// pos位置 需要合法
	
			if (_size == _capacity) {
				reserve(_capacity == 0 ? 4 : _capacity * 2);
			}
	
			size_t end = _size + 1;
			// 1. end位置在 _size+1, 挪动数据的步骤就是将 end-1 位置的数据一个一个挪至end
			// 2. 如果 end位置在 _size, 则挪动数据的步骤是将 end位置的数据 挪至 end+1
			// (两种方法 从 '\0' 开始挪动)
			// 表面看 两种方法好像都一样，但是 如果end的初始位置是_size, 需要额外处理 pos位置为0的情况
			// 因为 当pos位置为零时, 方案二 end的结束位置应该在 -1, 但是 end是 size_t 类型的数据, 所以end永远不会为-1, 即会死循环
			// 而 方案一 不会有这种情况，方案一 如果 pos为0, 循环结束时 end == pos, 会退出循环
			while (end > pos) {
				_str[end] = _str[end - 1];
				end--;
			}
			_str[pos] = ch;
			_size++;
	
			return *this;
		}
		// 插入字符串
		string& insert(size_t pos, const char* str) {
			assert(pos <= _size);
	
			size_t len = strlen(str);
			if (_size + len > _capacity) {
				reserve(_capacity == 0 ? len : _capacity + len);
			}
	
			size_t end = _size + len;
			while (end > pos + len - 1)	{	// 可以画图判断一下end结束位置 
				_str[end] = _str[end - len];
				end--;
			}
			strncpy(_str + pos, str, len);		// 使用strncpy 可以防止字符串的'\0' 也被拷贝进去
			_size += len;
	
			return *this;
		}
	     // 插入对象
		string& insert(size_t pos, const string& s) {
			assert(pos <= _size);
	
			insert(pos, s._str);				// 直接调用 插入字符串
	
			return *this;
		}
	
	     // += 重载
		string& operator+=(const string& s) {
			insert(_size, s);		// += 对象复用 insert
			return *this;
		}
		string& operator+=(const char* str) {
			append(str);			// += 字符串复用 append
			return *this;
		}
		string& operator+=(char ch) {
			push_back(ch);		// += 字符 复用 push_back
			return *this;
		}
	    
	     // 清除对象内容
		void clear() {
			resize(0);
		}
	    
		// [] 重载
		char& operator[](size_t pos) {
			assert(pos < _size);		// 下标要合法	
	
			return _str[pos];
		}
		
		const char& operator[](size_t pos) const {
			assert(pos < _size);		// 下标要合法
		
			return _str[pos];
		}
	
		// size() 返回string有效字符大小
		size_t size() const {		// 不修改原对象的尽量加上 const 
			return _size;
		}
	
		// capacity() 返回 string 有效字符容量
		size_t capacity() const {
			return _capacity;
		}
	
		// c_str 返回对象中字符串的 C类指针形式
		// 按照库中的类型 const修饰
		const char* c_str() const {
			return _str;
		}
	    
		// 析构函数
		~string() {
			if (_str) {	// 得先保证 _str 不是空指针
				delete[] _str;
				_str = nullptr;
				_size = _capacity = 0;
			}
		}
	    
	private:
		char* _str;				// 字符串
		size_t _size;			// 字符串实际长度
		size_t _capacity;		 // 字符串指针表示的字符串的容量
		
		const static size_t npos; 
	};
	
	const size_t string::npos = -1;
	
	// 实现 > 和 == 都用strcmp来对字符串作比较
	bool operator>(const string& s1, const string& s2) {
		return strcmp(s1.c_str(), s2.c_str()) > 0;
	}
	bool operator==(const string& s1, const string& s2) {
		return strcmp(s1.c_str(), s2.c_str()) == 0;
	}
	bool operator>=(const string& s1, const string& s2) {
		return s1 > s2 || s1 == s2;
	}
	bool operator<(const string& s1, const string& s2) {
		return !(s1 >= s2);
	}
	bool operator<=(const string& s1, const string& s2) {
		return s1 < s2 || s1 == s2;
	}
	bool operator!=(const string& s1, const string& s2) {
		return !(s1 == s2);
	}
}

void Fun1(int &x) {
	cout << "左值引用" << endl; 
}
void fun(int &&x) {
	cout << "右值引用" << endl; 
}

void Fun(int &x) {
	cout << "左值引用" << endl; 
}
void Fun(const int &x) {
	cout << "const 左值引用" << endl; 
}
void Fun(int &&x) {
	cout << "右值引用" << endl; 
}
void Fun(const int &&x) {
	cout << "const 右值引用" << endl; 
}

template<typename T>
void PerfectForward(T&& t) {
    cout << "非完美转发: ";
    Fun(t);
    cout << "完美转发: ";
    Fun(std::forward<T>(t));
	cout << endl;
}

int main() {
	PerfectForward(10);				// 右值
						
	int a;
	PerfectForward(a);				// 左值
	PerfectForward(std::move(a));	// 右值

	const int b = 8;
	PerfectForward(b);				// const 左值
	PerfectForward(std::move(b));	// const 右值

	return 0;
}
