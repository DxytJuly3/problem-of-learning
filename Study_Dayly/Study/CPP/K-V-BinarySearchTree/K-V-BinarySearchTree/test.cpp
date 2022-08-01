#include "K-V-BinarySearchTree.h"

void TestKVBSTree1()
{
	KVBSTree<string, string> dict;
	dict.Insert("insert", "插入");
	dict.Insert("erase", "删除");
	dict.Insert("left", "左边");
	dict.Insert("string", "字符串");

	string str;
	while (cin >> str)
	{
		auto ret = dict.Find(str);
		if (ret)
		{
			cout << str << ":" << ret->_val << endl;
		}
		else
		{
			cout << "单词拼写错误" << endl;
		}
	}

	string strs[] = { "苹果", "西瓜", "苹果", "樱桃", "苹果", "樱桃", "苹果", "樱桃", "苹果", "西瓜", "樱桃", "苹果", "西瓜"
	, "樱桃", "苹果", "西瓜", "樱桃", "苹果", "西瓜", "樱桃", "苹果", "西瓜", "樱桃", "苹果", "西瓜", "樱桃", "苹果", "西瓜", "樱桃"
	, "苹果", "西瓜", "樱桃" , "苹果", "西瓜", "樱桃" , "苹果", "西瓜", "樱桃" , "苹果", "西瓜", "樱桃" , "苹果", "西瓜", "樱桃" , "苹果"
	, "苹果", "西瓜", "樱桃" , "苹果", "西瓜", "樱桃" , "苹果", "西瓜", "樱桃" , "苹果", "西瓜", "樱桃" };
	// 统计水果出现的次
	// 思路是：
	// 遍历strs，同时查找树中是否存在当前水果
	//	1. 不存在，则 插入水果 且对应val为1
	//	2. 存在，则 对应 val++
	// strs遍历一遍之后，数中就统计了 各种类及数量
	//
	KVBSTree<string, int> countTree;
	for (auto str : strs)
	{
		auto ret = countTree.Find(str);
		if (ret == NULL)
		{
			countTree.Insert(str, 1);
		}
		else
		{
			ret->_val++;
		}
	}
	countTree.InOrder();
}

void TestKVBSTree2()
{
	KVBSTree<int, char> kvBst1;
	kvBst1.Insert(1, 'a');
	kvBst1.Insert(3, 'c');
	kvBst1.Insert(2, 'b');
	kvBst1.Insert(9, 'i');
	kvBst1.Insert(4, 'd');
	kvBst1.Insert(8, 'g');
	kvBst1.Insert(6, 'f');
	kvBst1.Insert(5, 'e');
	kvBst1.Insert(10, 'j');
	kvBst1.InOrder();

	KVBSTree<int, char> kvBst2(kvBst1);
	kvBst2.InOrder();
	kvBst2.Erase(1);
	kvBst2.Erase(5);
	kvBst2.Erase(9);
	kvBst2.InOrder();


	KVBSTree<int, char> kvBst3;
	kvBst3 = kvBst2;
	kvBst3.InOrder();
	kvBst3.Insert(5, 'e');
	kvBst3.Insert(9, 'i');
	kvBst3.InOrder();
}
int main()
{
	TestKVBSTree1();
	TestKVBSTree2();

	return 0;
}