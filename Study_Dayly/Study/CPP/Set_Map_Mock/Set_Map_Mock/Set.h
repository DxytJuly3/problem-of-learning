#pragma once
#include "RBTree.h"

namespace July {
	template<class Key>
	class Set {
		typedef Key key_type;
		typedef Key value_type;

		// 取key值的仿函数
		struct SetKeyOfValue {
			const key_type& operator() (const value_type& key) {
				return key;
			}
		};

	public:
	private:
		RB_Tree<key_type, key_type, SetKeyOfValue> _tree;
	};
}

