#pragma once
#include "hashTable.h"

namespace July {
	template<class Key, class Value, class hashFunc = defaultHashFunc<Key>>
	class unordered_map {
		struct KeyOfT_map {
			const Key& operator()(const pair<Key, Value>& kv) {
				return kv.first;
			}
		};
	public:
		typedef typename hashTable<Key, pair<Key, Value>, KeyOfT_map, hashFunc>::iterator iterator;

		iterator begin() {
			return _ht.begin();
		}
		iterator end() {
			return _ht.end();
		}

		pair<iterator, bool> insert(const pair<Key, Value>& kv) {
			return _ht.insert(kv);
		}

		iterator find(const Key& key) {
			return _ht.find(key);
		}

		bool erase(const Key& key) {
			return _ht.erase(key);
		}

	private:
		July::hashTable<Key, pair<Key, Value>, KeyOfT_map, hashFunc> _ht;
	};
}
