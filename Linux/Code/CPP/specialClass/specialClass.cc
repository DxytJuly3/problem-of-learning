#include <iostream>

// 禁止拷贝 复制的类
class CopyBan {
public:
	// ...
	CopyBan() {}

	CopyBan(const CopyBan&) = delete;
	CopyBan& operator=(const CopyBan&) = delete;

private:
	//	CopyBan(const CopyBan&);
	//	CopyBan& operator=(const CopyBan&);
	//...
};

// 只能在堆上创建的类
class HeapOnly {
public:
	static HeapOnly* CreateObj() {
		return new HeapOnly;
	}

	HeapOnly(const HeapOnly&) = delete;
	// ~HeapOnly() {}

private:
	// 构造函数私有
	HeapOnly() {}
};

//class StackOnly {
//public:
//	StackOnly()
//		: _a(0) {}
//	// 禁掉operator new可以把下面用new 调用拷贝构造申请对象给禁掉
//	// StackOnly obj = StackOnly::CreateObj();
//	// StackOnly* ptr3 = new StackOnly(obj);
//	void* operator new(size_t size) = delete;
//	void operator delete(void* p) = delete;
//	StackOnly(const StackOnly&) = delete;
//
//private:
//	int _a;
//};

// 只能在栈上创建的类
class StackOnly {
public:
	static StackOnly CreateObj() {
		// 这里会Clang会提示报错: 使用了删除的拷贝构造
		// 是因为 这里传值返回, 会先调用构造函数 然后发生拷贝构造临时对象
		// 但实际上 构造->析构 的连续操作 会被编译器自动优化成 构造, 所以这里的报错不用担心
		return StackOnly();
		//		StackOnly st;
		//		return st;
	}

	StackOnly(const StackOnly& a) = delete;

private:
	// 构造函数私有
	StackOnly() {}
};

// 不能被继承的类
class NonInherit final {
//class NonInherit {
public:
	static NonInherit GetInstance() {
		return NonInherit();
	}

private:
	NonInherit() {}
};

//class sonNonInhert: public NonInherit {};

int main() {

	return 0;
}

//int main() {
//	//	StackOnly stO1;
//	//	StackOnly* stO2 = new StackOnly;
//	//	StackOnly stO3(stO1);
//
//	StackOnly stO1 = StackOnly::CreateObj();
//
//	return 0;
//}

//int main() {
//	//	HeapOnly h1;
//	//	static HeapOnly h2;
//	//	HeapOnly* ph3 = new HeapOnly;
//
//	HeapOnly* ph4 = HeapOnly::CreateObj();
//	HeapOnly* ph5 = HeapOnly::CreateObj();
//
//	//HeapOnly copy(*ph3);
//
//	delete ph4;
//	delete ph5;
//
//	return 0;
//}

//int main() {
//	CopyBan cB1;
//	CopyBan cB2(cB1);
//	CopyBan cB3 = cB1;
//
//	CopyBan cB4;
//	cB4 = cB1;
//
//	return 0;
//}
