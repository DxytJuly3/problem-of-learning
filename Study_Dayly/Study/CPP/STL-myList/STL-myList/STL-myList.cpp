#include "STL-myList.h"
using std::cout;
using std::endl;

void test_push_pop()
{
    cout << "test_push_pop() ::" << endl;
    cout << "主要测试 插入和删除" << endl;

    July::list<int> lt1;
    lt1.push_back(1);
    lt1.push_back(2);
    lt1.push_back(3);
    lt1.push_back(4);
    lt1.push_back(5);
    lt1.push_front(1);
    lt1.push_front(2);
    lt1.push_front(3);
    lt1.push_front(4);
    lt1.push_front(5);
    July::list<int>::iterator it1 = lt1.begin();
    while (it1 != lt1.end())
    {
        cout << *it1 << " ";
        ++it1;
    }
    cout << endl;

    cout << " 三次头删、三次尾删 ::" << endl;
    lt1.pop_back();
    lt1.pop_back();
    lt1.pop_back();
    lt1.pop_front();
    lt1.pop_front();
    lt1.pop_front();
    July::list<int>::iterator it2 = lt1.begin();
    while (it2 != lt1.end())
    {
        cout << *it2 << " ";
        ++it2;
    }
    cout << endl;
}

void test_list()
{
    cout << "test_list() ::" << endl;
    cout << "主要测试 拷贝构造和赋值重载" << endl;
    July::list<int> lt1;
    lt1.push_back(1);
    lt1.push_back(2);
    lt1.push_back(3);
    lt1.push_back(4);
    lt1.push_back(5);
    cout << "list1 :: ";
    July::list<int>::iterator it1 = lt1.begin();
    while (it1 != lt1.end())
    {
        cout << *it1 << " ";
        ++it1;
    }
    cout << endl;

    July::list<int> lt2(lt1);
    cout << "list1 拷贝构造出的 list2 :: ";
    July::list<int>::iterator it2 = lt2.begin();
    while (it2 != lt2.end())
    {
        cout << *it2 << " ";
        ++it2;
    }
    cout << endl;


    lt2.push_front(9);
    lt2.push_front(9);
    lt2.push_front(9);
    July::list<int> lt3;
    lt3 = lt2;
    cout << "list2头插3个9 后赋值给list3 :: ";
    July::list<int>::iterator it3 = lt3.begin();
    while (it3 != lt3.end())
    {
        cout << *it3 << " ";
        ++it3;
    }
    cout << endl;
}

void test_reverseIter()
{
    cout << "test_reverseIter() ::" << endl;
    cout << "主要测试 正\\反向迭代器" << endl;
    July::list<int> lt1;
    lt1.push_back(1);
    lt1.push_back(2);
    lt1.push_back(3);
    lt1.push_back(4);
    lt1.push_back(5);
    cout << "正向输出 list1 :: ";
    July::list<int>::iterator it2 = lt1.begin();
    while (it2 != lt1.end())
    {
        cout << *it2 << " ";
        ++it2;
    }
    cout << endl;
    cout << "反向输出 list1 :: ";
    July::list<int>::reverse_iterator it1 = lt1.rbegin();
    while (it1 != lt1.rend())
    {
        cout << *it1 << " ";
        ++it1;
    }
    cout << endl;
}

int main()
{
    test_push_pop();
    test_list();
    test_reverseIter();

    return 0;
}
