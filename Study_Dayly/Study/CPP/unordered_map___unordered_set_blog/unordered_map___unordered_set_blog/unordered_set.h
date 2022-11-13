#pragma once
#include "hashTable.h"

namespace July {
	template<class Key, class hashFunc = defaultHashFunc<Key>>
	class unordered_set {
		struct KeyOfT_set{
			const Key& operator()(const Key & key) {
				return key;
			}
		};
	public:
		typedef typename hashTable<Key, Key, KeyOfT_set, hashFunc>::iterator iterator;

		iterator begin() {
			return _ht.begin();
		}

		iterator end() {
			return _ht.end();
		}

		pair<iterator, bool> insert(const Key& key) {
			return _ht.insert(key);
		}

		iterator find(const Key& key) {
			return _ht.find(key);
		}

		bool erase(const Key& key) {
			return _ht.erase(key);
		}

	private:
		hashTable<Key, Key, KeyOfT_set, hashFunc> _ht;
	};
}
