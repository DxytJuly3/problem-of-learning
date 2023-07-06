#include <iostream>

using std::cout;
using std::endl;

// 递归终止函数
template <class T>
void ShowList(const T& t) {
	cout << typeid(t).name() << ":";
    cout << t << endl;
}

//// 展开函数
//template <class T, class ...Args>
//void ShowList(T value, Args... args) {
//	cout << typeid(value).name() << ":";
//    cout << value <<"    ";
//    ShowList(args...);
//}

template <class T>
int PrintArg(T t) {
    cout << typeid(t).name() << ":";
    cout << t << "    ";
    
    return 0;
}

//展开函数
template <class ...Args>
void ShowList(Args... args) {
    int arr[] = { PrintArg(args)... };
    cout << endl;
}

int main() {
	cout << "列表初始化方法 展开参数包" << endl;
    ShowList(1);
    ShowList(1, 'A');
    ShowList(1, 'A', std::string("sort"));

    return 0;
}
