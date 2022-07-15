#include "myVector.h"
using namespace July;
using std::cout;
using std::endl;
//
//void Test_Generate()
//{
//	vector<vector<int>> Gen;
//	Gen.generate(10);
//	for (int i = 0; i < Gen.size(); i++)
//	{
//		for (int j = 0; j < Gen[i].size(); j++)
//		{
//			cout << Gen[i][j] << " "; 
//		}
//		cout << endl;
//	}
//	cout << endl;
//
//	vector<vector<int>> Gen1 = Gen.generate(10);
//	for (int i = 0; i < Gen1.size(); i++)
//	{
//		for (int j = 0; j < Gen1[i].size(); j++)
//		{
//			cout << Gen1[i][j] << " ";
//		}
//		cout << endl;
//	}
//	cout << endl;
//}

void Test1()
{
	vector<int> v1;
	v1.push_back(1);
	v1.push_back(2);
	v1.push_back(3);
	v1.push_back(4);
	v1.push_back(5);
	for (auto i : v1)
	{
		cout << i << " ";
	}
	cout << endl;
	vector<int> v2(10, 7);
	v2 = v1;	
	for (auto j : v2)
	{
		cout << j << " ";
	}
	cout << endl;
}

void test_reverseIter()
{
    cout << "test_reverseIter() ::" << endl;
    cout << "主要测试 正\\反向迭代器" << endl;
    July::vector<int> v1;
    v1.push_back(1);
    v1.push_back(2);
    v1.push_back(3);
    v1.push_back(4);
    v1.push_back(5);
    cout << "正向输出 v1 :: ";
    July::vector<int>::iterator it2 = v1.begin();
    while (it2 != v1.end())
    {
        cout << *it2 << " ";
        ++it2;
    }
    cout << endl;
    cout << "反向输出 v1 :: ";
    July::vector<int>::reverse_iterator it1 = v1.rbegin();
    while (it1 != v1.rend())
    {
        cout << *it1 << " ";
        ++it1;
    }
    cout << endl;
}


int main()
{
	Test1();
    test_reverseIter();

	return 0;
}
