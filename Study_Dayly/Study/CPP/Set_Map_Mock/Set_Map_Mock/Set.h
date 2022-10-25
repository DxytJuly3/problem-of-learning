#pragma once
#include "RBTree.h"

namespace July {
	template<class Key>
	class Set {
		typedef Key key_type;
		typedef Key value_type;

		// ȡkeyֵ�ķº���
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

