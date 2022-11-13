#pragma once
#include <iostream>
#include <vector>
#include <string>
using std::pair;
using std::vector;
using std::string;
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

	template<class T>
	struct hashNode {
		T _data;
		hashNode<T>* _next;

		hashNode(const T& data)
			:_data(data)
			, _next(nullptr)
		{}
	};

	// 需要在 迭代器类前声明 哈希表类
	template<class Key, class T, class KeyOfT, class hashFunc>
	class hashTable;

	// 迭代器
	template<class Key, class T, class KeyOfT, class hashFunc>
	struct __hashTableIterator {
		typedef hashNode<T> Node;
		typedef hashTable<Key, T, KeyOfT, hashFunc> hashTable;

		typedef __hashTableIterator<Key, T, KeyOfT, hashFunc> Self;				// 迭代器本身类型 typedef为 Self
	public:
		__hashTableIterator() {}

		__hashTableIterator(Node* node, hashTable* pht)
			:_node(node)
			, _pht(pht)
		{}

		Self& operator++() {
			if (_node->_next != nullptr) {				// 当前节点的 _next不为空, 表示不是桶的尾节点
				_node = _node->next;
			}
			else {
				KeyOfT kot;						// 创建取key值的仿函数对象
				hashFunc hf;					// 创建计算key的哈希值的仿函数对象
				// 在使用时 仿函数可以直接使用匿名对象

				size_t hashI = hf(kot(_node->_data)) % _pht->_tables.size();			// 先用kot调用取key值的仿函数, 再用hf调用计算key的哈希值的仿函数, 然后 % 哈希表数组的容量, 求出当前桶的哈希地址
				// 向后查找 不为空的桶
				hashI++;
				for (; hashI < _pht->_tables.size(); hashI++) {
					if (_pht->_tables[hashI]) {			// 哈希表数组的 hashI 位置不为空, 表示此桶不为空
						_node = _pht->_tables[hashI];		// 更新迭代器节点为此桶的头节点
						break;
					}
				}

				// 如果循环正常走完, 就表示没有找到下一个非空桶
				// 也就表示 当前迭代器所指向的节点 是整个哈希表中的最后一个数据节点
				// 那么 ++操作之后, 节点应该指向空
				if (hashI == _pht->_tables.size()) {
					_node = nullptr;
				}
				// 上面 存在直接访问哈希表私有变量的情况, 所以 迭代器类需要设置为哈希表类的友元函数
			}

			return *this;
		}

		Node& operator*() {
			return _node->_data;
		}

		Node* operator->() {
			return &_node->_data;
		}

		bool operator==(const Self& sIt) const {
			return _node == sIt._node;
		}

		bool operator!=(const Self& sIt) const {
			return _node != sIt._node;
		}

	private:
		Node* _node;					    // 节点指针
		hashTable* _pht;					// 节点所在哈希表的指针
	};

	template<class Key, class T, class KeyOfT, class hashFunc>
		class hashTable {
		typedef hashNode<T> Node;

		template<class Key, class T, class KeyOfT, class hashFunc>
		friend struct __hashTableIterator;

		public:
			typedef __hashTableIterator<Key, T, KeyOfT, hashFunc> iterator;

			~hashTable() {
				for (size_t i = 0; i < _tables.size(); ++i) {
					Node* cur = _tables[i];
					while (cur) {
						Node* next = cur->_next;
						delete cur;
						cur = next;
					}

					_tables[i] = nullptr;
				}
			}

			// 插入数据	
			pair<iterator, bool> insert(const T& data) {
				hashFunc hf;
				KeyOfT kot;

				// 先查找哈希表中是否已经存在此数据
				iterator pos = find(kot(data));
				if (pos != end()) {						// 迭代器存在, 且 != end(), 即表示存在此数据
					return make_pair(pos, false);
				}

				// 当 负载因子 == 1 时, 数组扩容
				if (_tables.size() == _n) {
					size_t newSize = _tables.size() == 0 ? 10 : _tables.size() * 2;

					vector<Node*> newTables;
					newTables.resize(newSize, nullptr);
					for (int i = 0; i < _tables.size(); i++) {
						Node* cur = _tables[i];
						while (cur) {
							Node* next = cur->_next;

							size_t hashI = hf(kot(cur->_data)) % newSize;				// 取key值 以新数组的大小映射哈希地址
							cur->_next = newTables[hashI];
							newTables[hashI] = cur;

							cur = next;
						}
						_tables[i] = nullptr;
					}
					// 新数组映射结束, 交换数组
					_tables.swap(newTables);
				}
				// 扩容结束
				// 计算 需要插入的哈希桶的位置
				size_t hashI = hf(kot(data)) % _tables.size();
				// 头插数据
				Node* newNode = new Node(data);
				newNode->_next = _tables[hashI];
				_tables[hashI] = newNode;

				++_n;

				return make_pair(iterator(newNode, this), true);
			}

			// 查找数据
			iterator find(const Key& key) {
				if (_n == 0) {
					return iterator(nullptr, this);
				}

				hashFunc hf;
				KeyOfT kot;

				size_t hashI = hf(key) % _tables.size();
				Node* cur = _tables[hashI];
				while (cur) {
					if (kot(cur->_data) == key) {
						return iterator(cur, this);
					}
					cur = cur->_next;
				}

				// 走到这里就是没有找到
				return iterator(nullptr, this);
			}

			// 删除数据
			bool erase(const Key& key) {
				hashFunc hf;
				KeyOfT kot;

				size_t hashI = hf(key) % _tables.size();
				Node* cur = _tables[hashI];
				Node* prev = nullptr;
				while (cur) {
					if (kot(cur->_data) == key) {
						if (cur == _tables[hashI]) {					// 如果需要删除的节点是桶的头节点
							_tables[hashI] = cur->_next;
						}
						else {
							prev->_next = cur->_next;
						}
						delete cur;
						--_n;

						return true;
					}

					prev = cur;
					cur = cur->_next;
				}

				// 走到这里说明 没有可删除的节点
				return false;
			}

			iterator begin() {
				for (size_t i = 0; i < _tables.size(); i++) {
					Node* cur = _tables[i];
					if (cur) {
						return iterator(cur, this);
					}
				}

				return end();
			}

			iterator end() {
				return iterator(nullptr, this);
			}

		private:
			vector<Node*> _tables;						 // 存储桶的数组
			size_t _n = 0;							// 存储的节点数
	};
}
