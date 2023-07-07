#include <iostream>
#include <functional>
#include <ostream>

using std::cout;
using std::endl;

template<class F, class T>
T useF(F f, T x) {
	static int count = 0;
	cout << "count:" << ++count << endl;
	cout << "count:" << &count << endl;

	return f(x);
}

double f(double i) {
	return i / 2;
}

struct Functor {
	double operator()(double d) {
		return d / 3;
	}
};

int f1(int a, int b) {
	return a + b;
}

struct Functor1 {
public:
	int operator() (int a, int b) {
		return a + b;
	}
};

class Plus{
public:
    static int plusi(int a, int b) {
		return a + b;
	}

    double plusd(double a, double b) {
        return a + b;
    }
};


int Sub1(int a, int b) {
    return a - b;
}
class Sub {
public:
    int sub(int a, int b) {
        return a - b;
    }
};

int main() {
//	// 函数名
//	cout << useF(f, 11.11) << endl;
//
//	// 函数对象
//	cout << useF(Functor(), 11.11) << endl;
//
//	// lamber表达式
//	cout << useF([](double d)->double{ return d / 4; }, 11.11) << endl;
	
//	// 函数名
//	std::function<double(double)> func1 = f;
//    cout << "未使用包装器 f 类型" << typeid(f).name() << endl;
//    cout << "包装器后 类型" << typeid(func1).name() << endl << endl;
//
//	// 函数对象
//	std::function<double(double)> func2 = Functor();
//    cout << "未使用包装器 Functor() 类型" << typeid(Functor()).name() << endl;
//    cout << "包装器后 类型" << typeid(func2).name() << endl << endl;
//
//	// lamber表达式
//	std::function<double(double)> func3 = [](double d)->double{ return d / 4; };
//	auto lam1 = [](double d)->double{ return d / 4; };
//    cout << "未使用包装器 lambda 类型" << typeid(lam1).name() << endl;
//    cout << "包装器后 类型" << typeid(func3).name() << endl;


//    // 函数名(函数指针)
//    std::function<double(double)> func1 = f;
//    cout << func1(1) << endl;
//
//    // 函数对象
//    std::function<double(double)> func2 = Functor();
//    cout << func2(4) << endl;
//
//    // lamber表达式
//    std::function<int(int, int)> func3 = [](const int a, const int b){ return a + b; };
//    cout << func3(1, 2) << endl;

//	// 函数名
//    std::function<double(double)> func1 = f;
//    cout << useF(func1, 11.11) << endl << endl;
//    
//    // 函数对象
//    std::function<double(double)> func2 = Functor();
//    cout << useF(func2, 11.11) << endl << endl;
//    
//    // lamber表达式
//    std::function<double(double)> func3 = [](double d)->double{ return d / 4; };
//    cout << useF(func3, 11.11) << endl;

//	// 包装静态成员变量
//    std::function<int(int, int)> func1 = Plus::plusi;
//	cout << func1(1, 2) << endl;
//    
//	Plus::plusi(1, 2);
//
//    // 包赚非静态成员变量
//    std::function<double(Plus, double, double)> func2 = &Plus::plusd;
//	cout << func2(Plus(), 3.3, 4.4) << endl;

//	std::function<int(int, int)> func1 = std::bind(Sub1, std::placeholders::_1, std::placeholders::_2);
//    cout << func1(4, 8) << endl;
//    
//    std::function<int(int, int)> func2 = std::bind(Sub1, std::placeholders::_2, std::placeholders::_1);
//    cout << func2(4, 8) << endl;

	Sub s;
    // 绑定成员函数
    std::function<int(int, int)> func = std::bind(&Sub::sub, s, std::placeholders::_1, std::placeholders::_2);
	cout << func(3, 4) << endl;

    return 0;
}

