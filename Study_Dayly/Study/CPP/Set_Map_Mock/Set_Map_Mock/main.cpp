#include <map>
#include <set>
#include <string>
#include "Map.h"
#include "Set.h"
void test_set1()
{
set<int> s;
s.insert(4);
s.insert(5);
s.insert(2);
s.insert(1);
s.insert(1);
s.insert(3);
s.insert(2);
s.insert(1);


// 排序 + 去重 
set<int>::iterator it = s.begin();
while (it != s.end())
{
	//*it = 10;
	cout << *it << " ";
	++it;
}
cout << endl;

for (auto e : s)
{
	cout << e << " ";
}
cout << endl;
}

void test_set2()
{
	set<int> s;
	s.insert(4);
	s.insert(5);
	s.insert(2);
	s.insert(1);
	s.insert(1);
	s.insert(3);
	s.insert(2);
	s.insert(1);

	set<int>::iterator pos = s.find(20);  // O(logN)
	if (pos != s.end())
	{
		cout << "set.find找到了" << endl;
	}

	pos = find(s.begin(), s.end(), 2); // O(N)
	if (pos != s.end())
	{
		cout << "find找到了" << endl;
	}
}


void test_set3()
{
	set<int> s;
	s.insert(4);
	s.insert(5);
	s.insert(2);
	s.insert(1);
	s.insert(1);
	s.insert(3);
	s.insert(2);
	s.insert(1);

	cout << s.erase(3) << endl;
	cout << s.erase(30) << endl;

	for (auto e : s)
	{
		cout << e << " ";
	}
	cout << endl;

	set<int>::iterator pos = s.find(3);
	if (pos != s.end())
		s.erase(pos);

	for (auto e : s)
	{
		cout << e << " ";
	}
	cout << endl;

	/*int x;
	while (cin >> x)
	{
		set<int>::iterator pos = s.find(x);
		if (pos != s.end())
		{
			s.erase(pos);
			cout << "删除" << x << "成功" << endl;
		}
		else
		{
			cout << x << "不在set中" << endl;
		}

		for (auto e : s)
		{
			cout << e << " ";
		}
		cout << endl;
	}*/

	if (s.count(5))
	{
		cout << "5在" << endl;
	}

	if (s.find(5) != s.end())
	{
		cout << "5在" << endl;
	}
}

void test_set4()
{
	set<int> s;
	s.insert(4);
	s.insert(5);
	s.insert(1);
	s.insert(3);
	s.insert(2);
	s.insert(7);
	s.insert(9);

	// 返回>= val得位置迭代器  3返回3位置  6 返回7位置
	/*set<int>::iterator lowIt = s.lower_bound(3); 存在
	lowIt = s.lower_bound(6); 不存在*/
	for (auto e : s)
	{
		cout << e << " ";
	}
	cout << endl;

	// 要求删除>=x的所有值
	int x;
	cin >> x;
	set<int>::iterator lowIt = s.lower_bound(x);
	s.erase(lowIt, s.end());

	for (auto e : s)
	{
		cout << e << " ";
	}
	cout << endl;
}

void test_set5()
{
	set<int> s;
	s.insert(4);
	s.insert(5);
	s.insert(1);
	s.insert(3);
	s.insert(2);
	s.insert(7);
	s.insert(9);

	for (auto e : s)
	{
		cout << e << " ";
	}
	cout << endl;

	// 返回>x位置的迭代器  -》 都是返回 7位置的迭代器
	//set<int>::iterator upIt = s.upper_bound(5);  // 存在
	//upIt = s.upper_bound(6); // 不存在

	// 删除x <=  <= y的区间 删除 [x,y]
	int x, y;
	cin >> x >> y;
	auto leftIt = s.lower_bound(x);  // [
	auto rightIt = s.upper_bound(y); // )
	s.erase(leftIt, rightIt);
	for (auto e : s)
	{
		cout << e << " ";
	}
	cout << endl;
}

void test_set6()
{
	multiset<int> s;
	s.insert(4);
	s.insert(5);
	s.insert(2);
	s.insert(1);
	s.insert(1);
	s.insert(3);
	s.insert(2);
	s.insert(1);
	s.insert(3);
	s.insert(3);
	s.insert(3);
	s.insert(3);

	// 排序 
	set<int>::iterator it = s.begin();
	while (it != s.end())
	{
		//*it = 10;
		cout << *it << " ";
		++it;
	}
	cout << endl;

	for (auto e : s)
	{
		cout << e << " ";
	}
	cout << endl;

	cout << s.count(1) << endl;
	cout << s.erase(1) << endl;
	for (auto e : s)
	{
		cout << e << " ";
	}
	cout << endl;

	// 多个x的话，find返回中序第一个x
	auto pos = s.find(3);
	while (pos != s.end())
	{
		cout << *pos << " ";
		++pos;
	}
	cout << endl;
}

void test_map1()
{
	map<string, string> dict;

	// pair构造函数
	dict.insert(pair<string, string>("sort", "排序"));
	pair<string, string> kv("insert", "插入");
	dict.insert(kv);

	// make_pair
	auto ret1 = dict.insert(make_pair("left", "左边"));
	auto ret2 = dict.insert(make_pair("left", "剩余"));

	dict["operator"] = "重载"; // 插入+修改
	dict["left"] = "左边、剩余"; // 修改
	dict["erase"];  // 插入
	cout << dict["left"] << endl; // 查找


	// C++11 再讲
	//dict.insert({ "right", "右边" });

	// 遍历
	//map<string, string>::iterator it = dict.begin();
	auto it = dict.begin();
	while (it != dict.end())
	{
		//cout << *it << " "; // it->operator*()
		//cout << (*it).first << ":" << (*it).second << endl;
		cout << it->first << ":" << it->second << endl;
		++it;
	}
	cout << endl;

	for (const auto& kv : dict)
	{
		cout << kv.first << ":" << kv.second << endl;
	}
}

//mapped_type& operator[] (const key_type& k)
//{
//	pair<iterator,bool> ret = insert(make_pair(k, mapped_type()));
//
//	//return (*(ret.first)).second;
//	return ret.first->second;
//}

void test_map2()
{
	string arr[] = { "苹果", "西瓜", "苹果", "西瓜", "苹果", "苹果", "西瓜", "苹果", "香蕉", "苹果", "香蕉" };

	// 17:08继续
	/*map<string, int> countMap;
	for (auto& str : arr)
	{
		map<string, int>::iterator it = countMap.find(str);
		if (it != countMap.end())
		{
			it->second++;
		}
		else
		{
			countMap.insert(make_pair(str, 1));
		}
	}*/

	//map<string, int> countMap;
	//for (auto& str : arr)
	//{
	//	//pair<map<string, int>::iterator, bool> ret = countMap.insert(make_pair(str, 1));
	//	auto ret = countMap.insert(make_pair(str, 1));
	//	if (ret.second == false)
	//	{
	//		ret.first->second++;
	//	}
	//}

	map<string, int> countMap;
	for (auto& str : arr)
	{
		countMap[str]++;
	}

	for (const auto& kv : countMap)
	{
		cout << kv.first << ":" << kv.second << endl;
	}
}

void test_map3()
{
	map<string, string> dict;
	dict.insert(make_pair("left", "左边"));
	dict.insert(make_pair("left", "剩余"));
	dict.insert(make_pair("left", "左边"));
}

//输出
//["qkjzgws", "nftk", "qrkgmliewc", "qengse", "nsfspyox", "htpvnmozay", "zskaqzwo", "fqizrrnmif", "glarko", "hdemkfr", "qggx", "pwqvwmlgri", "zlfiwwb", "ijy"]
//
//预期
//["nftk", "qkjzgws", "qrkgmliewc", "nsfspyox", "qengse", "htpvnmozay", "fqizrrnmif", "glarko", "hdemkfr", "pwqvwmlgri", "qggx", "zskaqzwo", "ijy", "zlfiwwb"]
//
//qkjzgws:10
//nftk : 10
//qrkgmliewc : 9
//qengse : 8
//nsfspyox : 8
//	
//int main()
//{
//	//test_set6();
//	//test_map3();
//	//TestAVLTree2();
//	//TestRBTree2();
//
//
//
//	return 0;
//}

int main() {
	//July::test_set1();
	July::test_map1();
	July::test_map2();

	return 0;
}