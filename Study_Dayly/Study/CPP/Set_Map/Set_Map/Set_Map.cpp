#include <iostream>
#include <map>
#include <set>

using std::set;
using std::multiset;
using std::map;
using std::cout;
using std::cin;
using std::endl;

void Set_test1() {
    set<int> s1;
    // 先插入 1、3、5 三个数
    s1.insert(1);
    s1.insert(3);
    s1.insert(5);

    // 再插入 3，并接收返回值
    auto ret3 = s1.insert(3);
    // 插入 2，并接收返回值
    auto ret2 = s1.insert(2);

    // 分别查看 两个返回值的成员
    cout << "ret3:: ";
    cout << *(ret3.first) << " ";
    cout << ret3.second << endl;

    cout << "ret2:: ";
    cout << *(ret2.first) << " ";
    cout << ret2.second << endl;

    for (auto kv : s1) {
        cout << kv << ' ';
    }
    cout << endl;
}

void Set_test2() {
    set<int> s1;
    s1.insert(1);
    s1.insert(3);
    s1.insert(5);
    s1.insert(2);
    s1.insert(4);
    s1.insert(6);
    s1.insert(9);
    s1.insert(1);
    s1.insert(2);
    s1.insert(4);

    set<int>::iterator v1 = s1.begin();
    while (v1 != s1.end()) {
        cout << *v1 << " ";
        v1++;
    }
    cout << endl;
}

void Set_test3() {
    set<int> s1;
    s1.insert(1);
    s1.insert(3);
    s1.insert(5);
    s1.insert(2);
    s1.insert(4);
    s1.insert(6);
    s1.insert(9);
    s1.insert(1);
    s1.insert(2);
    s1.insert(4);
    for (auto kv : s1) {
        cout << kv << ' ';
    }
    cout << endl;

    /*s1.erase(1);
    for (auto kv : s1) {
        cout << kv << ' ';
    }
    cout << endl;
    s1.erase(3);
    s1.erase(3);
    s1.erase(3);
    s1.erase(3);
    s1.erase(3);
    for (auto kv : s1) {
        cout << kv << ' ';
    }
    cout << endl;*/

    /*auto pos = s1.find(1);
    if (pos != s1.end()) {
        s1.erase(pos);
    }
    for (auto kv : s1) {
        cout << kv << ' ';
    }
    cout << endl;*/

    s1.erase(s1.begin(), s1.end());
    for (auto kv : s1) {
        cout << kv << ' ';
    }
    cout << endl;
}

void Set_test4() {
    set<int> s1;
    s1.insert(1);
    s1.insert(2);
    s1.insert(3);
    s1.insert(4);
    s1.insert(5);
    s1.insert(6);
    s1.insert(7);
    s1.insert(8);
    s1.insert(9);
    for (auto kv : s1) {
        cout << kv << ' ';
    }
    cout << endl;

    auto posBegin = s1.lower_bound(2);
    auto posEnd = s1.upper_bound(7);
    s1.erase(posBegin, posEnd);

    for (auto kv : s1) {
        cout << kv << ' ';
    }
    cout << endl;
}

void Multiset_test1() {
    multiset<int> ms1;
    ms1.insert(1);
    ms1.insert(1);
    ms1.insert(2);
    ms1.insert(1);
    ms1.insert(1);
    ms1.insert(2);
    ms1.insert(2);
    ms1.insert(2);
    ms1.insert(1);

    for (auto kv : ms1) {
        cout << kv << ' ';
    }
    cout << endl;
    cout << "1 有 " << ms1.count(1) << " 个" << endl;

    ms1.erase(1);
    for (auto kv : ms1) {
        cout << kv << ' ';
    }
    cout << endl;
    cout << "1 有 " << ms1.count(1) << " 个" << endl;
}

int main()
{
    Multiset_test1();
    
    return 0;
}
