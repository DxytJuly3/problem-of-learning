#include <iostream>
#include <iterator>
#include <vector>
#include <string>
#include <algorithm>
#include <functional>

using std::string;
using std::vector;
using std::greater;
using std::cout;
using std::endl;

struct Goods {
    string _name;   // 名字
    double _price;  // 价格
    int _evaluate;  // 评价
    Goods(const char* str, double price, int evaluate)
        : _name(str)
        , _price(price)
        , _evaluate(evaluate) 
    {}
};

// 价格升序仿函数
struct ComparePriceLess {
    bool operator()(const Goods& gl, const Goods& gr) {
        return gl._price < gr._price;
    }
};

// 价格降序仿函数
struct ComparePriceGreater {
    bool operator()(const Goods& gl, const Goods& gr) {
        return gl._price > gr._price;
    }
};

void printGoods(vector<Goods>& v) {
    cout << "物品   价格   评价" << endl;
    for (auto e : v) {
        cout << e._name << "   " << e._price << "    " << e._evaluate << endl;
    }
	cout << endl;
}

void (*pF)();

int main() {
//    int array[] = {4, 1, 8, 5, 3, 7, 0, 9, 2, 6};
//    
//    // 默认按照小于比较，排出来结果是升序
//    std::sort(array, array + sizeof(array) / sizeof(array[0]));
//	cout << "升序" << endl;
//	for(auto e : array) {
//		cout << e << " ";
//	}
//	cout << endl;
//	cout << endl;
//
//    // 如果需要降序，需要改变元素的比较规则
//    std::sort(array, array + sizeof(array) / sizeof(array[0]), greater<int>());
//	cout << "降序" << endl;
//	for(auto e : array) {
//		cout << e << " ";
//	}
//	cout << endl;
//	cout << endl;
//
//    vector<Goods> v = {
//        {"苹果", 2.1, 5},
//        {"香蕉", 3.1, 4},
//        {"橙子", 2.2, 3},
//        {"菠萝", 1.5, 4}
//    };
//
//    sort(v.begin(), v.end(), ComparePriceLess());
//	cout << "价格升序" << endl;
//	cout << "物品   价格   评价" << endl;
//	for(auto e : v) {
//		cout << e._name << "   " << e._price << "    " << e._evaluate << endl;
//	}
//	cout << endl;
//
//    sort(v.begin(), v.end(), ComparePriceGreater());
//	cout << "价格降序" << endl;
//	cout << "物品   价格   评价" << endl;
//	for(auto e : v) {
//		cout << e._name << "   " << e._price << "    " << e._evaluate << endl;
//	}
//	cout << endl;
//
//	auto priceUp = [](const Goods& g1, const Goods& g2) {
//        return g1._price < g2._price; };
//    sort(v.begin(), v.end(), priceUp);
//    cout << "价格升序" << endl;
//    printGoods(v);
//    
//    sort(v.begin(), v.end(), [](const Goods& g1, const Goods& g2){
//        return g1._price > g2._price; });
//    cout << "价格降序" << endl;
//    printGoods(v);
//    
//    sort(v.begin(), v.end(), [](const Goods& g1, const Goods& g2){
//        return g1._evaluate < g2._evaluate; });
//    cout << "评价升序" << endl;
//    printGoods(v);
//    
//    sort(v.begin(), v.end(), [](const Goods& g1, const Goods& g2){
//        return g1._evaluate > g2._evaluate; });
//    cout << "评价降序" << endl;
//    printGoods(v);
//    int a = 10, b = 20;
//    cout << a << "  " << b << endl;
 
//    auto lamSwap1 = [](int x, int y){
//        int tmp = x;
//        x = y;
//        y = tmp;
//    };
//    auto lamSwap2 = [](int& x, int& y){
//        int tmp = x;
//        x = y;
//        y = tmp;
//    };
//	auto lamSwap1 = [a, a]()mutable{
//        int tmp = a;
//        a = b;
//        b = tmp;
//    };
//    auto lamSwap2 = [&, &a](){
//        int tmp = a;
//        a = b;
//        b = tmp;
//    };

//    lamSwap1();
//    cout << "lamSwap1:: "<< a << "  " << b << endl;
//    
//    lamSwap2();
//    cout << "lamSwap2:: "<< a << "  " << b << endl;

//	auto f1 = []{cout << "hello world" << endl; };
//    auto f2 = []{cout << "hello world" << endl; };
//    f1 = f2;

	auto f1 = []{cout << "hello world" << endl; };
    
    auto f2(f1);
    f2();
    
    pF = f1;
    pF();

    return 0;
}
