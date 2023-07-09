#include <iostream>
#include <exception>

using std::cin;
using std::cout;
using std::endl;
using std::exception;
using std::invalid_argument;

int div() {
    int a, b;
    cin >> a >> b;
    if (b == 0)
        throw invalid_argument("除0错误");

    return a / b;
}

void Func() {
    // 1、如果p1这里new 抛异常会如何？
    // 2、如果p2这里new 抛异常会如何？
    // 3、如果div调用这里又会抛异常会如何？
    int* p1 = new int;
    int* p2 = new int;

    try {
        cout << div() << endl;
    }
    catch (...) {
        delete p1;
        delete p2;
        throw;
    }

    delete p1;
    delete p2;
}

int main() {
    try {
        Func();
    }
    catch (exception& e) {
        cout << e.what() << endl;
    }

    return 0;
}
