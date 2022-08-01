#pragma once

#include <iostream>
#include <string>
using std::string;
using std::cout;
using std::cin;
using std::endl;


//
// K-V 二叉搜索树与 普通二叉搜索树不同的是
// K-V 二叉搜搜树存储的是两个数据：
// 比如 像字典的：英文单词 - 中文， 出门的机票车票：身份信息 - 票信息
// 一个key 对应一个val，这就是K-V 二叉搜索树
// 结构什么的都与 普通二叉搜索树相同 不同的只是节点的不同，K-V二叉搜索树 节点存储的两个数据
// 不过 K-V二叉搜索树 的查找、排列 还都是根据 key 来排列的，而不是根据 val
//
template<class K, class V>
struct KVBinarySearchTreeNode
{
	KVBinarySearchTreeNode<K, V>* _left = nullptr;
	KVBinarySearchTreeNode<K, V>* _right = nullptr;

	K _key;
	V _val;

	KVBinarySearchTreeNode(const K& key, const V& val)
		:_left(nullptr)
		, _right(nullptr)
		, _key(key)
		, _val(val)
	{}
};

template<class K, class V>
class KVBSTree
{
	typedef KVBinarySearchTreeNode<K, V> Node;
public:
	// C++ 11 添加的特性，可以使构造函数 为编译器生成的默认构造函数
	// 当需要默认构造函数，但是已经实现了拷贝构造函数时，可以用此关键词 使类的构造函数为编译器生成的默认构造函数
	KVBSTree() = default;

	KVBSTree(const KVBSTree<K, V>& tree)
	{
		_root = CopyTree(tree._root);
	}

	KVBSTree<K, V>& operator=(KVBSTree<K, V> tree)
	{
		std::swap(_root, tree._root);

		return *this;
	}
	~KVBSTree()
	{
		DestroyTree(_root);
		_root = nullptr;
	}

	bool Insert(const K& key, const V& val)
	{
		if (_root == nullptr)
		{
			_root = new Node(key, val);
			return true;
		}

		Node* parent = nullptr;
		Node* cur = _root;

		while (cur)
		{
			if (cur->_key < key)
			{
				parent = cur;
				cur = cur->_right;
			}
			else if (cur->_key > key)
			{
				parent = cur;
				cur = cur->_left;
			}
			else
			{
				return false;
			}
		}
		
		cur = new Node(key, val);
		if (parent->_key > key)
		{
			parent->_left = cur;
		}
		else
		{
			parent->_right = cur;
		}

		return true;
	}

	Node* Find(const K& key)
	{
		Node* cur = _root;
		while (cur)
		{
			if (cur->_key < key)
			{
				cur = cur->_right;
			}
			else if (cur->_key > key)
			{
				cur = cur->_left;
			}
			else
			{
				return cur;
			}
		}

		return nullptr;
	}

	bool Erase(const K& key)
	{
		Node* parent = nullptr;
		Node* cur = _root;
		while (cur)
		{
			if (cur->_key < key)
			{
				parent = cur;
				cur = cur->_right;
			}
			else if (cur->_key > key)
			{
				parent = cur;
				cur = cur->_left;
			}

			else
			{
				if (cur->_left == nullptr)
				{
					if (cur == _root)
					{
						_root = cur->_right;
					}
					else
					{
						if (cur == parent->_right)
						{
							parent->_right = cur->_right;
						}
						else
						{
							parent->_left = cur->_right;
						}
					}
					delete cur;
				}
				else if (cur->_left == nullptr)
				{
					if (cur == _root)
					{
						_root = cur->_left;
					}
					else
					{
						if (cur == parent->_right)
						{
							parent->_right = cur->_left;
						}
						else
						{
							parent->_left = cur->_left;
						}
					}
					delete cur;
				}
				else
				{
					Node* minParent = cur;
					Node* minRight = cur->_right;
					while (minRight->_left)
					{
						minParent = minRight;
						minRight = minRight->_left;
					}
					
					std::swap(minRight->_key, cur->_key);
					// 由于树中 _key 一般被const修饰 所以不能直接修改_key，即不能直接交换_key
					// 而是可以直接交换节点
					// 可以自己编写swap 实现树中两节点的位置交换
					// 
					// swap(minParent->_left, (cur == parent->_left? parent->_left : parent->_right));
					// 暂时失败

					if (minRight == minParent->_left)
					{
						minParent->_left = minRight->_right;
					}
					else
					{
						minParent->_right = minRight->_right;
					}

					delete minRight;
				}

				return true;
			}
		}

		return false;
	}

	bool FindR(const K& key)
	{
		return _FindR(_root, key);
	}

	bool InsertR(const K& key, const V& val)
	{
		return _InsertR(_root, key, val);
	}

	bool EraseR(const K& key)
	{
		return _EraseR(_root, key);
	}

	void InOrder()
	{
		_InOrder(_root);
		cout << endl;
	}

private:
	/*void swap(Node*& cur1, Node*& cur2)
	{
		Node* tmp1 = new Node(cur1->_key, cur1->_val);
		tmp1->_left = cur2->_left;
		tmp1->_right = cur2->_right;

		Node* tmp2 = new Node(cur2->_key, cur2->_val);
		tmp2->_left = cur1->_left;
		tmp2->_right = cur1->_right;

		cur1 = tmp2;
		cur2 = tmp1;
	}*/

	Node* CopyTree(Node* root)
	{
		if (root == nullptr)
			return nullptr;

		Node* copyNode = new Node(root->_key, root->_val);
		copyNode->_left = CopyTree(root->_left);
		copyNode->_right = CopyTree(root->_right);

		return copyNode;
	}

	void DestroyTree(Node* root)
	{
		if (root == nullptr)
			return;

		DestroyTree(root->_left);
		DestroyTree(root->_right);
		delete root;
	}

	bool _EraseR(Node*& root, const K& key)
	{
		if (root == nullptr)
			return false;

		if (root->_key > key)
		{
			return _EraseR(root->_left, key);
		}
		else if (root->_key < key)
		{
			return _EraseR(root->_right, key);
		}
		else
		{
			Node* del = root;
			if (root->_left == nullptr)
			{
				root = root->_right;
			}
			else if (root->_right == nullptr)
			{
				root = root->_left;
			}
			else
			{
				Node* minRight = root->_right;
				while (minRight->_left)
				{
					minRight = minRight->_left;
				}

				std::swap(minRight->_key, root->_key);
				//swap(minRight, root);

				return _EraseR(root->_right, key);
			}

			delete del;
			return true;
		}
	}
	bool _InsertR(Node*& root, const K& key, const V& val)
	{
		if (root == nullptr)
		{
			root = new Node(key, val);
			return true;
		}

		if (root->_key < key)
		{
			return _InsertR(root->_right, key, val);
		}
		else if (root->_key > key)
		{
			return _InsertR(root->_left, key, val);
		}
		else
		{
			return false;
		}
	}
	bool _FindR(Node* root, const K& key)
	{
		if (root == nullptr)
			return false;

		if (root->_key < key)
		{
			return _FindR(root->_right, key);
		}
		else if (root->_key > key)
		{
			return _FindR(root->_left, key);
		}
		else
		{
			return true;
		}
	}

	void _InOrder(Node* root)
	{
		if (root == nullptr)
			return;

		_InOrder(root->_left);
		cout << root->_key << "-" << root->_val << " ";
		_InOrder(root->_right);
	}

	Node* _root;
};