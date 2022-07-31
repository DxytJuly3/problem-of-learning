#pragma once

#include <iostream>
using std::cout;
using std::cin;
using std::endl;

template<class K>
struct BinarySearchTreeNode
{
	BinarySearchTreeNode<K>* _left = nullptr;
	BinarySearchTreeNode<K>* _right = nullptr;

	K _key;

	BinarySearchTreeNode(const K& key)
		:_left(nullptr)
		,_right(nullptr)
		,_key(key)
	{}
};

// 搜索二叉树，左边比根小，右边比根大
template<class K>
class BSTree
{
	typedef BinarySearchTreeNode<K> Node;
public:
	BSTree()
		:_root(nullptr)
	{}

	BSTree(const BSTree<K>& tree)
	{
		_root = CopyTree(tree._root);
	}

	// 赋值重载函数的现代写法
	BSTree<K>& operator=(BSTree<K> tree)
	{
		// 传值传参 发生拷贝
		// 直接将拷贝出的树 与 需要赋值的树 交换根
		std::swap(_root, tree._root);

		return *this;
	}
	// 析构函数 递归后续遍历 删除节点
	// 为什么是后序遍历？ 因为 后序可以保证到该删除的节点时，该节点没有子节点
	~BSTree()
	{
		DestroyTree(_root);
		_root = nullptr;
	}

	bool Insert(const K& key)
	{
		if (_root == nullptr)			// 二叉树中没有数据的时候
		{
			_root = new Node(key);
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
			else					// 搜索二叉树不允许存入 相同的数据
			{
				return false;
			}
		}
		// 当 cur 为空时，循环结束，cur位置则是新数据需要插入的位置，即 parent 的左孩子 或 右孩子
		// 确认左孩子 还是 右孩子 需要再比较一下
		cur = new Node(key);			// cur位置 给一个新节点
		if (parent->_key > key)			// 再将cur位置与 parent节点连接起来
		{
			parent->_left = cur;
		}
		else
		{
			parent->_right = cur;
		}

		return true;
	}

	//const Node* Find(const K& key)		// 如果返回节点，则需要 const修饰节点，因为二叉搜索树不允许修改，会破坏结构
	bool Find(const K& key)
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
				return true;
			}
		}

		return false;
	}

	// 删除节点比较难搞，因为二叉搜索树的结构是 左子树小，右子树大
	// 直接删除节点可能会造成结构破坏，所以删除节点需要分析一下
	// 首先要知道 删除节点可能会遇到多少种情况？
	// 1. 被删除节点无左右子树
	//	  此种情况直接删除，然后将父亲节点的 _left 或 _right(需要判断被删节点是父亲节点的左孩子还是右孩子) 置空就行了
	//	  而此被删节点的左右孩子刚好是空，所以直接将父亲节点的_left 或 _right 置为 被删节点的左右孩子就行
	// 2. 被删除节点只有左子树
	//	  只有左子树，就表示 父亲节点需要接收左子树，所以 在删除结点之前 要将 父亲节点的 _left 或 _right 连接到 被删节点的左子树上
	// 3. 被删除节点只有右子树
	//	  与 第2种情况相反
	// 4. 被删节点同时存在左右子树
	//	  此时，删除节点就需要更多的分析了了。
	//	  被删除节点同时存在左右子树，且删除结点之后不能改变二叉搜索树的结构
	//	  最佳的思路就是，用一个合适的节点与被删除节点交换位置，然后再删除就行了
	//    这个合适的节点需要满足几个要求：
	//		1. 不能同时拥有左右子树
	//		2. 交换之后，不能改变二叉搜索树的结构
	//	  这两个条件，经过分析之后，有两个节点是满足的：
	//		1. 左子树的最大节点
	//		   因为 左子树都是比父亲节点小的，用左子树的最大节点做新父亲，依旧可以保证 新父亲节点比左子树大 比右子树小
	//		2. 右子树的最小节点
	//		   同理，右子树都是比父亲节点大的，用右子树的最小节点做新父亲，依旧可以保证 新父亲节点比左子树大 比右子树小
	//	  
	// 分析过删除的思路之后，就可以根据 图片编写代码了：
	//
	bool Erase(const K& key)
	{ 
		Node* parent = nullptr;					// 用于记录删除节点的父亲节点
		Node* cur = _root;						// 用于记录删除节点
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
			// 上面的过程是在 找key，即 找需要被删除的值的节点
			else
			{
				if (cur->_left == nullptr)	// 左子树为空，即 只有右子树。所以父节点需要连接被删除节点的右子树
				{
					if (cur == _root)
					{
						_root = cur->_right;	// 删除的节点是 _root，直接将 cur->_right 换为 _root 就可以了
					}
					else
					{
						if (cur == parent->_right)		// cur 为父节点的右子树
						{
							parent->_right = cur->_right;	// 父节点的右子树需要连接
						}
						else							// cur 为父节点的左子树
						{
							parent->_left = cur->_right;	// 父节点的左子树需要连接
						}
					}
					delete cur;
				}
				else if (cur->_left == nullptr)		// 右子树为空，即 只有左子树。所以父节点需要连接被删除节点的左子树
				{
					if (cur == _root)
					{
						_root = cur->_left;	// 删除的节点是 _root，直接将 cur->_left 换为 _root 就可以了
					}
					else
					{
						if (cur == parent->_right)		// cur 为父节点的右子树
						{
							parent->_right = cur->_left;	// 父节点的右子树需要连接
						}
						else							// cur 为父节点的左子树
						{
							parent->_left = cur->_left;	// 父节点的左子树需要连接
						}
					}
					delete cur;
				}
				// 当被删除节点同时拥有左右子树时，就需要找 左子树的最大节点 或 右子树的最小节点 与被删除节点交换位置
				// 然后进行删除
				// 那么 怎么才能找到 左子树的最大节点 或 右子树的最小节点呢？
				// 根据二叉搜索树 左子树小 右子树大的性质，可以分析出
				//		1. 左子树的最大节点 就是左子树中没有右子树的节点
				//		2. 右子树中的最小节点，就是右子树中没有左子树的节点
				// 所以只需要选择一个方向就可以找到了
				else									// cur 有左右节点时，需要换节点然后删除
				{
					// 这里选择 找右子树中的最小节点
					// 因为需要删除cur 所以cur和parent都不能改变，所以需要两个新的变量去找
					Node* minParent = cur;
					Node* minRight = cur->_right;
					while (minRight->_left)
					{
						minRight = minRight->_left;
					}

					std::swap(minParent->_key, cur->_key);		// 删除某个指定值的节点，在本树中没有重复数据 交换数据就可以
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

				return true;		// 删除成功就返回 true
			}
		}

		return false;		// 跳出循环就表示删除失败 没找到指定值的节点，所以返回 false
	}

	//==================================================================================================
	//================================= 以上是二叉搜索树操作的非递归版 ======================================
	//==================================================================================================

	bool FindR(const K& key)
	{
		return _FindR(_root, key);
	}

	bool InsertR(const K& key)
	{
		return _InsertR(_root, key);
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

	// 由于拷贝构造函数需要将：
	//	1. 根节点返回给_root
	//	2. 拷贝过程中 需要将新节点连接到树中
	// 所以需要返回节点指针类型
	//
	Node* CopyTree(Node* root)
	{
		if (root == nullptr)
			return nullptr;

		Node* copyNode = new Node(root->_key);
		copyNode->_left = CopyTree(root->_left);
		copyNode->_right = CopyTree(root->_right);

		return copyNode;		// 返回节点将其与 父亲连接起来
	}

	void DestroyTree(Node* root)
	{
		if (root == nullptr)
			return;

		// 后序遍历，先左后右 再访问
		DestroyTree(root->_left);
		DestroyTree(root->_right);
		delete root;
	}

	// 与 插入的连接思路相似，传 结点指针的引用 可以剩下记录parent的功夫
	// 然后就是有分四种情况删除
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
		else			// 找到了，开始判断 删除节点
		{
			Node* del = root;	// 记录被删除节点
			if (root->_left == nullptr)		// 只有右子树
			{
				root = root->_right;
			}
			else if (root->_right == nullptr)	// 只有左子树
			{
				root = root->_left;
			}
			// 在递归算法中， 删除有 左右子树的节点 还是去找需要删除的节点的：
			//	1. 左子树的最大节点：左子树中没有右子树的节点
			//	2. 右子树的最小节点：右子树中没有左子树的节点
			// 找到到之后与需要删除的节点交换值
			// 但是 接下来的删除操作应该怎么写呢？
			// 其实 直接在 子树中继续递归就可以了：
			//	以 找右子树的最小节点为例，被删除节点与右子树的最小节点交换位置之后，右子树的二叉搜索树的结构是没有被破坏的
			//	因为 被删除节点一定是比 其右子树中的所有节点小的，那么被删除节点与其右子树中的任意节点交换位置 被删除的节点在其中都是最小节点
			//	而 如果被删除节点 与 其右子树中的最小节点交换位置 正好替代了 最小节点的位置，没有破坏右子树的二叉搜索树的结构
			// 所以 被删除节点 与 合适节点交换位置之后，其所在的树 的二叉搜索树的结构没有被破坏，只需要对子树执行递归删除就可以了
			// 
			else						// 左右子树都有
			{
				Node* minRight = root->_right;
				while (minRight->_left)
				{
					minRight = minRight->_left;
				}

				std::swap(minRight->_key, root->_key);			// 交换位置之后，整个树的结构其实是被破坏了的，不能对整个树执行操作

				return _EraseR(root->_right, key);			// 右子树结构没有被破坏，可以直接对其递归删除
			}

			delete del;
			return true;
		}
	}

	// 插入操作 新节点需要与父节点连接，所以递归过程中需要记录 parent节点
	// 由于是递归写法，会创建不同的栈帧，所以在一个函数栈帧中创建局部变量来存储parent节点是行不通的
	// 有一个思路是，添加一个 参数用来传入 parent 节点，进而达到记录parent节点的作用
	// 哈有一个思路就是，将原来的 节点指针作为参数，改为 节点指针的引用 作为参数
	// 这样可以有效解决 找不到父节点的问题，传 节点指针的引用 可以不用找父节点
	// 比如 传右子树时， _InsertR(root->_right, key) 进入函数 root->_right 变为 root
	// 由于是 引用，所以进入函数之后 root 直接为 父节点的右子树，直接就是与父节点连着的，不需要单独记录并连接
	//
	bool _InsertR(Node*& root, const K& key)
	{
		if (root == nullptr)			// root为空时，即为需要插入节点的位置
		{
			root = new Node(key);			// 此时的 root 就是 parent的孩子，无需再次连接
			return true;
		}

		if (root->_key < key)				// key大 向右子树找位置
		{
			return _InsertR(root->_right, key);
		} 
		else if (root->_key > key)			// key小 向左子树找位置
		{
			return _InsertR(root->_left, key);
		}
		else	
		{
			return false;					// 找到与 key相同值的节点，取消插入，插入失败
		}
	}

	// 查找Key 递归就跟遍历一样
	bool _FindR(Node* root, const K& key)
	{
		if (root == nullptr)
			return false;

		if (root->_key < key)	// key大，就向右子树递归查找
		{
			return _FindR(root->_right, key);
		}
		else if (root->_key > key)		// key小，就向左子树递归查找
		{
			return _FindR(root->_left, key);
		}
		else		// 找到 就返回true
		{
			return true;
		}
	}

	void _InOrder(Node* root)
	{
		if (root == nullptr)
			return;

		_InOrder(root->_left);
		cout << root->_key << " ";
		_InOrder(root->_right);
	}

	Node* _root;
};
