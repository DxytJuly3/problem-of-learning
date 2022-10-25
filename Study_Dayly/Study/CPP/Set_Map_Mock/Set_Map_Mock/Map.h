#pragma once
#include "RBTree.h"

namespace July {
	template<class Key, class Value>
	class Map {
		typedef Key key_type;
		typedef pair<Key, Value> value_type;		// pair<Key, Value>作为数据类型

		// 取key值的仿函数
		struct MapKeyOfValue {
			const key_type& operator() (const value_type& kv) {
				return kv.first;
			}
		};


	public:
	private:
		RB_Tree<key_type, value_type, MapKeyOfValue> _tree;
	};
}

