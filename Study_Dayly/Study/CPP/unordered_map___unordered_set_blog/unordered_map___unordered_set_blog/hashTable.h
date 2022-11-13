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

	// ��Ҫ�� ��������ǰ���� ��ϣ����
	template<class Key, class T, class KeyOfT, class hashFunc>
	class hashTable;

	// ������
	template<class Key, class T, class KeyOfT, class hashFunc>
	struct __hashTableIterator {
		typedef hashNode<T> Node;
		typedef hashTable<Key, T, KeyOfT, hashFunc> hashTable;

		typedef __hashTableIterator<Key, T, KeyOfT, hashFunc> Self;				// �������������� typedefΪ Self
	public:
		__hashTableIterator() {}

		__hashTableIterator(Node* node, hashTable* pht)
			:_node(node)
			, _pht(pht)
		{}

		Self& operator++() {
			if (_node->_next != nullptr) {				// ��ǰ�ڵ�� _next��Ϊ��, ��ʾ����Ͱ��β�ڵ�
				_node = _node->next;
			}
			else {
				KeyOfT kot;						// ����ȡkeyֵ�ķº�������
				hashFunc hf;					// ��������key�Ĺ�ϣֵ�ķº�������
				// ��ʹ��ʱ �º�������ֱ��ʹ����������

				size_t hashI = hf(kot(_node->_data)) % _pht->_tables.size();			// ����kot����ȡkeyֵ�ķº���, ����hf���ü���key�Ĺ�ϣֵ�ķº���, Ȼ�� % ��ϣ�����������, �����ǰͰ�Ĺ�ϣ��ַ
				// ������ ��Ϊ�յ�Ͱ
				hashI++;
				for (; hashI < _pht->_tables.size(); hashI++) {
					if (_pht->_tables[hashI]) {			// ��ϣ������� hashI λ�ò�Ϊ��, ��ʾ��Ͱ��Ϊ��
						_node = _pht->_tables[hashI];		// ���µ������ڵ�Ϊ��Ͱ��ͷ�ڵ�
						break;
					}
				}

				// ���ѭ����������, �ͱ�ʾû���ҵ���һ���ǿ�Ͱ
				// Ҳ�ͱ�ʾ ��ǰ��������ָ��Ľڵ� ��������ϣ���е����һ�����ݽڵ�
				// ��ô ++����֮��, �ڵ�Ӧ��ָ���
				if (hashI == _pht->_tables.size()) {
					_node = nullptr;
				}
				// ���� ����ֱ�ӷ��ʹ�ϣ��˽�б��������, ���� ����������Ҫ����Ϊ��ϣ�������Ԫ����
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
		Node* _node;					    // �ڵ�ָ��
		hashTable* _pht;					// �ڵ����ڹ�ϣ���ָ��
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

			// ��������	
			pair<iterator, bool> insert(const T& data) {
				hashFunc hf;
				KeyOfT kot;

				// �Ȳ��ҹ�ϣ�����Ƿ��Ѿ����ڴ�����
				iterator pos = find(kot(data));
				if (pos != end()) {						// ����������, �� != end(), ����ʾ���ڴ�����
					return make_pair(pos, false);
				}

				// �� �������� == 1 ʱ, ��������
				if (_tables.size() == _n) {
					size_t newSize = _tables.size() == 0 ? 10 : _tables.size() * 2;

					vector<Node*> newTables;
					newTables.resize(newSize, nullptr);
					for (int i = 0; i < _tables.size(); i++) {
						Node* cur = _tables[i];
						while (cur) {
							Node* next = cur->_next;

							size_t hashI = hf(kot(cur->_data)) % newSize;				// ȡkeyֵ ��������Ĵ�Сӳ���ϣ��ַ
							cur->_next = newTables[hashI];
							newTables[hashI] = cur;

							cur = next;
						}
						_tables[i] = nullptr;
					}
					// ������ӳ�����, ��������
					_tables.swap(newTables);
				}
				// ���ݽ���
				// ���� ��Ҫ����Ĺ�ϣͰ��λ��
				size_t hashI = hf(kot(data)) % _tables.size();
				// ͷ������
				Node* newNode = new Node(data);
				newNode->_next = _tables[hashI];
				_tables[hashI] = newNode;

				++_n;

				return make_pair(iterator(newNode, this), true);
			}

			// ��������
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

				// �ߵ��������û���ҵ�
				return iterator(nullptr, this);
			}

			// ɾ������
			bool erase(const Key& key) {
				hashFunc hf;
				KeyOfT kot;

				size_t hashI = hf(key) % _tables.size();
				Node* cur = _tables[hashI];
				Node* prev = nullptr;
				while (cur) {
					if (kot(cur->_data) == key) {
						if (cur == _tables[hashI]) {					// �����Ҫɾ���Ľڵ���Ͱ��ͷ�ڵ�
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

				// �ߵ�����˵�� û�п�ɾ���Ľڵ�
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
			vector<Node*> _tables;						 // �洢Ͱ������
			size_t _n = 0;							// �洢�Ľڵ���
	};
}
