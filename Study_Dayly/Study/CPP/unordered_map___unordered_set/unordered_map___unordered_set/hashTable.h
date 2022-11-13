#pragma once
#include <iostream>
#include <vector>
#include <string>
using std::vector;
using std::string;
using std::pair;
using std::make_pair;

namespace July {

	template<class Key>
	struct defaultHashFunc {
		size_t operator()(const Key& key) {
			return (size_t)key;
		}
	};
	template<>
	struct defaultHashFunc<string> {
		size_t operator()(const string& str) {
			size_t hash = 0;
			for (auto c : str) {
				hash = hash * 131 + c;
			}

			return hash;
		}
	};

	// 数据节点
	template<class T>
	struct hashNode {
		T _data;
		hashNode<T>* _next;

		hashNode(const T& data)
			:_data(data)
			,_next(nullptr)
		{}
	};

	template<class Key, class T, class KeyOfT, class hashFunc>
	class hashTable;
	// 迭代器类内 定义使用了哈希表类的指针, 哈希表类内同样定义使用了迭代器类, 所以 需要在迭代器类前声明哈希表类
	// 如果迭代器类 定义在 哈希表类下, 就需要在哈希表类前声明迭代器类
	
	template<class Key, class T, class KeyOfT, class hashFunc>
	class __hashTableIterator {
		typedef hashNode<T> Node;
		typedef __hashTableIterator<Key, T, KeyOfT, hashFunc> Self;
	public:
		__hashTableIterator() {}

		__hashTableIterator(Node* node, hashTable<Key, T, KeyOfT, hashFunc>* pht)
			:_node(node)
			,_pht(pht)
		{}

		Self& operator++() {
			// 哈希表迭代器++ 从头到尾的移动过程是 从第一个桶的头节点开始 到 最后一个桶的尾节点
			// 所以迭代器指向桶中非最后一个数据节点的某个节点时, ++ 直接移向 _next节点便可
			// 若迭代器当前节点是 桶中最后一个数据节点, 则 ++之后 迭代器应该指向下一个桶的头节点
			// 迭代器找下一个桶, 也是迭代器中 最重要的一个操作
			if (_node->_next) {				// _node->next不为空 即表示 _node不为最后一个数据节点
				_node = _node->_next;
			}
			else {
				// 当 迭代器指向桶中最后一个数据节点时, 就需要找下一个桶
				hashFunc hf;
				KeyOfT kot;

				// 计算当前迭代器所在桶位置
				size_t hashI = hf(kot(_node->_data)) % _pht->_tables.size();
				// 这里需要访问 迭代器节点所在哈希表的私有成员变量 _tables. 所以 需要将 迭代器类设置为哈希表类的友元类
				hashI++;
				for (; hashI < _pht->_tables.size(); hashI++) {		// 向后遍遍历桶位置
					if (_pht->_tables[hashI]) {							// 向后找到第一个非空桶的位置, 记录桶的头节点, 跳出循环
						_node = _pht->_tables[hashI];
						break;
					}
				}

				// 如果 上面的循环正常走完, hashI 会 == _pht->_tables.size()
				// 此时 就说明 迭代器指向的位置的后面没有非空桶了 即 迭代器指向的就是哈希表中最后一个数据节点
				// 此时的 ++ 会使迭代器走向 nullptr
				if (hashI == _pht->_tables.size()) {
					_node = nullptr;
				}
			}

			return *this;				// 返回更新后的迭代器
		}
		
		Node& operator*() {
			return _node->_data;
		}

		Node* operator->() {
			return &_node->_data;
		}

		bool operator!=(const Self& htIt) const {
			return _node != htIt._node;
		}

		bool operator==(const Self& htIt) const {
			return _node == htIt._node;
		}
	private:
		Node* _node;
		hashTable<Key, T, KeyOfT, hashFunc>* _pht;							// 因为迭代器 需要在哈希表中判断移动, 所以迭代器需要存储哈希表的指针
	};

	// 哈希表 模板参数分别为 Key:关键词类型  T:数据类型	 KeyOfT:由数据取关键字的仿函数  hashFunc:计算Key哈希值的仿函数
	template<class Key, class T, class KeyOfT, class hashFunc>
	class hashTable {
		typedef hashNode<T> Node;
		
		template<class Key, class T, class KeyOfT, class hashFunc>
		friend class __hashTableIterator;
	public:
		typedef __hashTableIterator<Key, T, KeyOfT, hashFunc> iterator;

		iterator end() {
			return iterator(nullptr, this);
		}

		iterator begin() {
			// 找到第一个桶的头节点 实例化迭代器 并返回
			for (size_t i = 0; i < _tables.size(); i++) {
				Node* cur = _tables[i];
				if (cur) {
					return iterator(cur, this);
				}
			}

			return end();
		}

		~hashTable() {
			for (size_t i = 0; i < _tables.size(); i++) {
				Node* cur = _tables[i];
				while (cur) {
					Node* next = cur->_next;
					delete cur;

					cur = next;
				}
				
				_tables[i] = nullptr;
			}
		}
		
		// 插入操作返回的是 所给数据的所在节点的迭代器, 以及插入结果
		// 所以 用pair做返回值, first存储迭代器, second 存储bool
		//bool insert(const T& data) {
		pair<iterator, bool> insert(const T& data) {
			hashFunc hf;						// 实例化 计算 Key 的哈希值的仿函数的 对象
			KeyOfT kot;							// 实例化 取关键字的仿函数的 对象

			/*if (find(kot(data))) {					// 判断哈希表中是否 已经存在此数据
				return false;
			}*/
			iterator pos = find(kot(data));
			if (pos != end())
			{
				return make_pair(pos, false);
			}


			// 当 负载因子 == 1 时, 扩容哈希表
			if (_tables.size() == _n) {
				size_t newSize = _tables.size() == 0 ? 10 : _tables.size() * 2;

				vector<Node*> newTables;
				newTables.resize(newSize, nullptr);
				for (int i = 0; i < _tables.size(); i++) {
					Node* cur = _tables[i];
					while (cur) {
						Node* next = cur->_next;

						size_t hashI = hf(kot(cur->_data)) % newSize;
						cur->_next = newTables[hashI];
						newTables[hashI] = cur;

						cur = next;
					}
					_tables[i] = nullptr;
				}

				//	扩容完毕 交换新旧数组
				_tables.swap(newTables);
			}

			// 计算桶的位置
			size_t hashI = hf(kot(data)) % _tables.size();
			
			// 创建数据节点 并头插至桶中
			Node* newNode = new Node(data);
			newNode->_next = _tables[hashI];
			_tables[hashI] = newNode;

			++_n;

			return make_pair(iterator(newNode, this), true);
		}

		// Node* find(const Key& key)
		iterator find(const Key& key) {
			if (_n == 0) {							// _n 为 0, 表示表中没有数据
				// return nullptr;
				return iterator(nullptr, this);		// 返回迭代器
			}

			hashFunc hf;
			KeyOfT kot;

			size_t hashI = hf(key) % _tables.size();
			Node* cur = _tables[hashI];
			while (cur) {
				if (kot(cur->_data) == key) {
					//return cur;
					return iterator(cur, this);
				}

				cur = cur->_next;
			}

			return iterator(nullptr, this);
		}

		bool erase(const Key& key) {
			if (_n == 0) {
				return false;
			}

			hashFunc hf;
			KeyOfT kot;

			size_t hashI = hf(key) % _tables.size();
			Node* cur = _tables[hashI];
			Node* prev = nullptr;
			while (cur) {
				if (kot(cur->_data) == key) {
					if (cur == _tables[hashI]) {					// cur 是当前桶的头节点
						_tables[hashI] = cur->_next;
					}
					else {
						prev->_next = cur->_next;					// 链接prev->_next 为 cur->_next
					}

					delete cur;
					--_n;
				}

				prev = cur;
				cur = cur->_next;
			}

			return false;
		}

	private:
		vector<Node*> _tables;
		size_t _n = 0;
	};
}
