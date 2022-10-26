#pragma once
#include "RBTree.h"

namespace July {
	template<class Key, class Value>
	class map {
		typedef Key key_type;
		typedef pair<Key, Value> value_type;		// pair<Key, Value>作为数据类型

		// 取key值的仿函数
		struct MapKeyOfValue {
			const key_type& operator() (const value_type& kv) {
				return kv.first;
			}
		};

	public:
		// 封装红黑树的迭代器
		typedef typename RB_Tree<key_type, value_type, MapKeyOfValue>::iterator iterator;
		typedef typename RB_Tree<key_type, value_type, MapKeyOfValue>::const_iterator const_iterator;

		iterator begin() {
			return _tree.begin();
		}

		iterator end() {
			return _tree.end();
		}

		pair<iterator, bool> insert(const value_type& kv) {
			return _tree.insert(kv);
		}

		iterator find(const key_type& k) {
			return _tree.find(k);
		}

		Value& operator[](const key_type& k) {
			pair<iterator, bool> ret = insert(make_pair(k, Value()));				// 调用map的插入

			return ret.first->second;
			// ret 的 first 是 map的迭代器
			// 红黑树中实现过 迭代器的 -> 操作是取 迭代器所指向节点的数据
			// map的数据是 pair<key_type, value_type> 类型的
			// 所以 ret.first->second 即为结果
		}

	private:
		RB_Tree<key_type, value_type, MapKeyOfValue> _tree;
	};

	void test_map1()
	{
		map<string, int> m;
		m.insert(make_pair("111", 1));
		m.insert(make_pair("555", 5));
		m.insert(make_pair("333", 3));
		m.insert(make_pair("222", 2));

		map<string, int>::iterator it = m.begin();
		while (it != m.end())
		{
			cout << it->first << ":" << it->second << endl;
			++it;
		}
		cout << endl;

		for (auto& kv : m)
		{
			cout << kv.first << ":" << kv.second << endl;
		}
		cout << endl;
	}

	void test_map2()
	{
		string arr[] = { "2", "二","2", "二","2", "二","2", "二","2", "二", "3", "二", "2"};

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
		dict["insert"];
		dict["insert"] = "";
		dict["left"] = "";
	}

}

