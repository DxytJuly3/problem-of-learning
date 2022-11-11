#pragma once
#include <vector>
#include <iostream>
using std::pair;
using std::make_pair;
using std::vector;

namespace July {

	// 枚举变量 表示状态
	enum State {
		EMPTY,
		EXIST,
		DELETE
	};

	// 哈希表数据类型
	template<class K, class V>
	struct HashData {
		pair<K, V> _data;
		State _state = EMPTY;
	};

	template<class K, class V>
	class HashTable {
	public:
		typedef HashData<K, V> Data;

		bool insert(const pair<K, V>& kv) {
			if (_tables.size() == 0 || _n * 10 / _tables.size() >= 7) {				// 当 哈希表总容量为0, 或 哈希表内存储的数据个数已经达到了总容量的70% 进行扩容
				size_t newSize = _tables.size() == 0 ? 10 : _tables.size() * 2;			// 新容量为10 或 原来的 2倍

				// 哈希表扩容并不是 仅仅在原来的基础上改变容量那么简单, 而是需要以新的容量作为 capacity, 对哈希表内的数据进行重新映射
				HashTable<K, V> newHashTable;
				newHashTable._tables.resize(newSize);				// 调用vector的resize接口将新哈希表的容量改为newSize

				// 遍历原来的哈希表, 将原来的哈希表内的数据映射到 新的哈希表中
				for (auto& e : _tables) {
					if (e._state == EXIST) {						// 将 原哈希表中存在的数据 映射到新哈希表中
						newHashTable.insert(e._data);
					}
				}

				// 遍历重新映射完成之后, 将 两个哈希表的_tables 进行交换
				// 就可以将当前的哈希表扩容为新的哈希表
				_tables.swap(newHashTable._tables);
			}

			size_t startI = kv.first % _tables.size();				// 开始探测的位置

			size_t hashI = startI;
			size_t i = 1;
			while (_tables[hashI]._state == EXIST) {				// 发生哈希冲突就继续向后探测
				hashI = startI + i;
				i++;
				hashI %= _tables.size();							// 更新需要探测的位置
			}

			// 探测到空位置之后
			_tables[hashI]._data = kv;
			_tables[hashI]._state = EXIST;
			_n++;

			return true;
		}

		Data* find(const K& key) {
			if (_tables.size() == 0) {
				return nullptr;						// 哈希表为空 查找失败
			}

			size_t startI = key % _tables.size();

			size_t hashI = startI;
			size_t i = 1;
			while (_tables[hashI]._state != EMPTY) {				// 当 当前探测位置不为空时, 进入循环 继续查找
				if (_tables[hashI]._state != DELETE && _tables[hashI]._data.first == key) {
					// 当 当前探测位置数据没有被删除 且 与查找数据相等时 就返回当前位置地址
					return &_tables[hashI];
				}

				// 当前位置的数据 不是 查找的数据 就更新探测位置 继续查找
				hashI = startI + i;
				i++;
				hashI %= _tables.size();
			}

			return nullptr;					// 走出循环 就表示没有找到 
		}
		
		bool erase(const K& key) {
			Data* ret = find(key);
			if (Data) {
				ret->_state = DELETE;
				_n--;
				
				return true;
			}
			else {
				return false;
			}
		}	

	private:
		vector<Data> _tables;
		size_t _n = 0;
	};
}


namespace Bucket {
	
	// 数据节点 结构
	template<class K, class V>
	struct HashNode {
		pair<K, V> _data;
		HashNode<K, V>* _next;

		HashNode(const pair<K, V>& kv) 
			:_data(kv)
			,_next(nullptr)
		{}
	};

	template<class K, class V>
	class HashTable {
		typedef HashNode<K, V> Node;
	public:
		// 由于 数组内存储的链表是自定义的, 所以需要定义析构函数将链表释放
		~HashTable() {
			// 遍历哈希桶 释放节点
			for (int i = 0; i < _tables.size(); i++) {
				Node* cur = _tables[i];
				while (cur) {
					Node* next = cur->_next;
					delete cur;
					cur = next;
				}

				_tables[i] = nullptr;
			}
		}

		bool insert(const pair<K, V>& kv) {
			if (find(kv.first)) {
				return false;						// 设计 不可重复存储数据
			}

			// 设置 当负载因子== 1时 扩容
			/*if (_tables.size() == _n) {
				size_t newSize = _tables.size() == 0 ? 10 : _tables.size() * 2;

				// 这种方法 非常的影响效率
				// 因为这种方法 调用了 insert接口, 在开散列的处理中使用insert接口 会创建新的节点, 开销过大 
				// 并且, 由于创建了新的 哈希桶, 所以在 下面循环结束的时候 新的临时的哈希桶会被释放 释放需要遍历哈希桶 又是影响效率
				HashTable<K, V> newHashTable;
				newHashTable._tables.resize(newSize, nullptr);

				// 遍历原哈希桶 在新哈希桶中重新映射
				for (int i = 0; i < _tables.size(); i++) {
					Node* cur = _tables[i];
					while (cur) {
						newHashTable.insert(cur->_data);				// 新哈希桶中插入 当前节点的存储数据
						cur = cur->_next;
					}
				}

				_tables.swap(newHashTable._tables);
			}*/

			// 上面的扩容方法 非常的影响效率且开销过大
			// 下面的另一种方法, 不调用insert, 不创建新的哈希桶 不创建新的节点 也不需要释放新的空间
			// 而是 直接将 旧数组中的节点 重新计算映射到新的数组中, 再将 哈希桶的数组更新为新数组就可以了
			if (_tables.size() == n) {
				size_t newSize = _tables.size() == 0 ? 10 : _tables.size() * 2;

				vector<Node*> newTable;
				newTable.resize(newSize, nullptr);
				for (int i = 0; i < _tables.size(); i++) {
					Node* cur = _tables[i];
					while (cur) {
						Node* next = cur->_next;				// 后面会 使cur->_next 变成 数组中存储的头节点, 所以 下一个节点提前记录

						size_t hashI = cur->_data.first % newTable.size();					// 以新数组的容量计算 对应的哈希地址
						cur->_next = newTable[hashI];										// 插入的节点 与 newTable存储的头节点相连接
						newTable[hashI] = cur;

						cur = next;						// 更新 cur
					}

					_tables[i] = nullptr;				// 原数组的内容已被转移到新数组中 将原数组的内容置空
				}

				_tables.swap(newTable);
			}
			
			// 扩容完毕, 下面插入数据
			size_t hashI = kv.first % _tables.size();
			// 找到该向数组中第几个位置插入数据
			// 然后进行头插
			Node* newNode = new Node(kv);						// 以kv数据创建新的节点
			newNode->_next = _tables[hashI];					// 将数组中存储的链表的头节点连接在新节点之后
			_tables[hashI] = newNode;							// 新节点存储到数组中

			_n++;

			return true;
		}

		Node* find(const K& key) {
			if (_tables.size() == 0) {
				return nullptr;
			}

			size_t hashI = key % _tables.size();
			Node* cur = _tables[hashI];
			while (cur) {
				if (cur->_data.first == key) {
					return cur;									// 找到返回节点
				}

				cur = cur->_next;
			}

			return nullptr;
		}

		bool erase(const K& key) {
			/*
			// 一般思路
			size_t hashI = key % _tables.size();
			Node* cur = _tables[hashI];
			Node* prev = nullptr;
			while (cur) {
				if (cur->_data.first == key) {
					if (cur == _tables[hashI]) {
						//	需要删除的节点是 数组中存储链表的头节点
						_tables[hashI] = cur->_next;
					}
					else {
						prev->_next = cur->_next;
					}
					delete cur;

					return true;
				}
				prev = cur;
				cur = cur->_next;
			}*/
			// 特殊思路, 禁止获取 prev 以及 使用next的数据作为判断条件
			// 采用数据替换:
			//		要删除 cur节点的数据, 就将cur的数据 用 cur->next的数据 覆盖掉, 再将 cur与 cur->next->next 建立连接之后 释放cur->next节点
			// 这只是一种思路, 并不是说这种方法更好, 事实上这种方法并没有上面哪一种方法好, 因为 这种方法 一定会产生数据的拷贝
			// 当数据内容过大 过多时, 开销过大
			size_t hashI = key % _tables.size();
			Node* cur = _tables[hashI];
			while (cur) {
				if (cur->_data.first == key) {
					if (cur->_next == nullptr) {
						// 如果当前节点是单链表中的最后一个节点时
						// 是没有下一个结点的, 所以不能与下一个节点进行数据的替代
						// 但是可以与 头节点进行数据的替代, 然后头删
						Node* head = _tables[hashI];
						cur->_data = head->_data;
						_tables[hashI] = head->_next;
						delete head;
						head = nullptr;
					}
					else {
						cur->_data = cur->_next->_data;
						cur->_next = cur->_next->_next;
						delete cur->_next;
					}
					_n--;

					return true;
				}
				cur = cur->_next;
			}

			return false;
		}

	private:
		vector<Node*> _tables;
		size_t _n = 0;					// 记录数组存储数据的数量
	};
}	
