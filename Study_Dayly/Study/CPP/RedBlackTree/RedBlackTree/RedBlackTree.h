#pragma once
#include <iostream>
#include <vector>
#include <cassert>
#include <queue>
using std::cout;
using std::vector;
using std::endl;
using std::queue;

enum Color
{
	RED,
	BLACK
};

template<class T1>
struct RBTreeNode {
	RBTreeNode(const T1& data = T1(), Color color = RED) 
		: _pLeft(nullptr), _pRight(nullptr), _pParent(nullptr)
		, _data(data)
		, _color(color)
	{}
	// 为什么 节点默认红色呢？
	// 因为插入新节点为 红色时, 对 红黑树的结构的影响更小
	// 举个例子：
	//		如果插入的新节点是红色的, 且如果其父亲节点是黑色的, 那么插入直接完成不需要调整树
	//		只有新插入节点的父亲节点是红色时, 才会进行调节
	//		而 如果插入的新节点是 黑色的话, 必定会对树的结构造成破坏
	//		因为, 红黑树中每条路径的黑节点数目是相等的, 如果再插入一个黑节点, 则新插入的黑节点所在路径的黑节点数目就一定不与其他路径相等
	//		即 新插入黑节点 势必会对整棵树的其他所有路径造成影响, 调节可能会 非常非常非常麻烦
	//		所以 新节点要用 红色

	RBTreeNode<T1>* _pLeft;			// 左孩子节点
	RBTreeNode<T1>* _pRight;		// 左孩子节点
	RBTreeNode<T1>* _pParent;		// 左孩子节点

	T1 _data;		// 节点数据
	Color _color;	// 节点颜色状态
};

template<class T1>
class RBTree {
	typedef RBTreeNode<T1> Node;

public:
	bool insert(const T1& data) {
		if (_root == nullptr) {
			_root = new Node(data);
			_root->_color = BLACK;

			return true;
		}

		Node* cur = _root;				// 从根节点开始找 插入结点的位置
		Node* parent = cur->_pParent;
		while (cur) {
			if (data > cur->_data) {
				// data大 向右找
				parent = cur;
				cur = cur->_pRight;
			}
			else if (data < cur->_data) {
				// data小 向左找
				parent = cur;
				cur = cur->_pLeft;
			}
			else {
				// 树中已有 data
				return false;
			}
		}

		// cur 即为新节点需要插入的位置
		cur = new Node(data);
		if (data > parent->_data) {
			// data大, 即cur是parent 的右孩子
			parent->_pRight = cur;
		}
		else if (data < parent->_data) {
			parent->_pLeft = cur;
		}
		cur->_pParent = parent;		// 三叉链 链接

		// 节点插入完成, 需要判断红黑树的结构
		// 由于新插入的节点是 红节点, 插入新节点之后 所以一般会存在两种情况
		// 新节点的父亲节点是 黑节点  或 新节点的父亲节点是红节点
		//	1. 如果新节点的父亲节点是黑节点, 则 红黑树的结构正常 可以不做处理
		//	2. 如果新节点的父亲节点是红节点, 那么 根据红黑树的原则, 红节点的孩子不能为红节点
		//		那么就需要向上 调整红黑树的结构
		// 所以需要对 存在连续红节点的情况进行处理：
		while (parent && parent->_color == RED) {
			// 约定 cur是当前节点, parent是父亲节点
			//		grandFa是祖父节点, uncle是叔叔节点
			/*
						grandFa
						/     \
				   parent      uncle
					 /
				   cur
			*/
			// 记录
			Node* grandFa = parent->_pParent;
			assert(grandFa);

			// 当 parent是祖父节点的左孩子时
			if (grandFa->_pLeft == parent) {
				Node* uncle = grandFa->_pRight;

				// 此时 也会因为 叔叔节点的情况不同 存在不同的处理方法
				// 情况1：叔叔节点存在 且为 红节点时
				//	直接将 parent和uncle节点改为黑节点, 且把 grandFa节点改为红节点
				//	为什么 将parent 和 uncle节点改为黑节点的同时, 要把 grandFa 节点变为红节点？
				//	因为 要满足 红黑树的条件之一：每条路径的黑节点数目相等
				//		因为叔叔节点和父亲节点原来都是红节点, 也就说名祖父节点本来是黑节点
				//		既然 已经将 parent 和 uncle节点改为黑节点了, 那么就需要将这两个节点的父亲节点 也就是grandFa节点改为红节点
				//		来保证路径上的黑节点数目是不变的
				if (uncle && uncle->_color == RED) {
					parent->_color = uncle->_color = BLACK;
					grandFa->_color = RED;

					// 更新了当前节点的 parent、uncle、grandFa 节点的颜色后
					// 需要更新当前节点 以及父亲节点, 继续向上更新
					cur = grandFa;
					parent = cur->_pParent;
				}
				// 叔叔节点不存在 或 叔叔节点存在 且为黑
				// 以下情况的解决方案的前提：parent节点是grandFa节点的左孩子
				else {
					// 当叔叔节点不存在 或 为黑时
					if (cur == parent->_pLeft) {
						// 当前节点是其父亲节点的左孩子
						// 则直接 以祖父节点为右单旋的parent, 进行右单旋
						// 并更新 祖父节点和父亲节点 颜色
						// 最好画图理解一下
						// 右单旋操作 与 AVL数中的右单旋是一样的思路
						rotateR(grandFa);

						grandFa->_color = RED;
						parent->_color = BLACK;
					}
					else {
						// 否则 当前节点是 其父亲节点的右孩子, 就会像 AVL树中一样出现了 折现的情况
						// 需要左右双旋：
						//	1. 将 parent节点作为左单旋的parent 进行左单旋
						//	2. 再将 grandFa节点作为右单旋的parent 进行右单旋
						// 然后再调节 当前节点 和 grandFa的颜色
						rotateL(parent);
						rotateR(grandFa);

						cur->_color = BLACK;
						grandFa->_color = RED;
					}
					
					break;
				}
			}
			// 当 parent是祖父节点的右孩子时
			else {
				Node* uncle = grandFa->_pLeft;
				
				if (uncle && uncle->_color == RED) {
					parent->_color = uncle->_color = BLACK;
					grandFa->_color = RED;

					// 更新了当前节点的 parent、uncle、grandFa 节点的颜色后
					// 需要更新当前节点 以及父亲节点, 继续向上更新
					cur = grandFa;
					parent = cur->_pParent;
				}
				// 叔叔节点不存在 或 叔叔节点存在 且为黑
				// 以下情况的解决方案的前提：parent节点是grandFa节点的右孩子
				//	所以出现的情况需要与 上边的相反
				else {
					// 当叔叔节点不存在 或 为黑时
					if (cur == parent->_pRight) {
						// 当前节点是其父亲节点的右孩子
						// 则直接 以祖父节点为左单旋的parent, 进行左单旋
						// 并更新 祖父节点和父亲节点 颜色
						rotateL(grandFa);

						grandFa->_color = RED;
						parent->_color = BLACK;
					}
					else {
						// 否则 当前节点是 其父亲节点的左孩子
						// 需要右左双旋：
						//	1. 将 parent节点作为右单旋的parent 进行右单旋
						//	2. 再将 grandFa节点作为左单旋的parent 进行左单旋
						// 然后再调节 当前节点 和 grandFa的颜色
						rotateR(parent);
						rotateL(grandFa);

						cur->_color = BLACK;
						grandFa->_color = RED;
					}

					break;
				}
			}
		}
		_root->_color = BLACK;

		return true;
	}

	
	bool isRedBlackTree() {
		// 判断是否为红黑树需要判断 此树是否满足红黑树的各个条件
		//	判断 根节点是否为黑节点	
		//	判断 红节点的父亲节点(孩子节点) 是否还是红节点
		//	判断 每条路径中的黑节点数目是否相等
		if (_root == nullptr)
			return true;					// 空树也可以看作红黑树

		if (_root->_color == RED) {
			cout << "违反 红黑树根节点必须为黑节点 的规则" << endl;
			return false;
		}

		// 计算任意一个路径的 黑节点数目, 为了方便对比其他路径 黑节点数目是否相等
		// 每棵红黑树, 从根节点走到空的位置才算是一条路径
		size_t blackCount = 0;
		Node* pCur = _root;
		while (pCur) {
			if (pCur->_color == BLACK)
				blackCount++;

			pCur = pCur->_pLeft;
		}
		// 然后通过递归函数, 判断：
		//	1. 红节点的父亲节点是否 还是红节点
		//	2. 每条路径中的黑节点数目是否相同
		size_t pathBlack = 0;
		return _isPathRedBlackTree(_root, pathBlack, blackCount);
	}

	int maxHeight() {
		return _maxHeight(_root);
	}

	int minHeight() {
		return _minHeight(_root);
	}

	void Height() {
		cout << "此树最长路径长度： " << _maxHeight(_root) << endl;
		cout << "此树最短路径长度： " << _minHeight(_root) << endl;
	}

	// 层序遍历输出：
	void levelOrder() {
		queue<Node*> q;
		int levelSize = 1;
		q.push(_root);

		while (!q.empty())
		{
			// levelSize控制一层一层出
			vector<int> levelV;
			while (levelSize--)
			{
				Node* front = q.front();
				q.pop();
				levelV.push_back(front->_data);
				if (front->_pLeft)
					q.push(front->_pLeft);

				if (front->_pRight)
					q.push(front->_pRight);
			}
			for (auto e : levelV)
			{
				cout << e << " ";
			}
			cout << endl;

			// 上一层出完，下一层就都进队列
			levelSize = q.size();
		}
	}
	
	void InOrder()
	{
		_InOrder(_root);
		cout << endl;
	}

private:
	void _InOrder(Node* root)
	{
		if (root == nullptr)
			return;

		_InOrder(root->_pLeft);
		cout << root->_data << " ";
		_InOrder(root->_pRight);
	}

	// 求最短路径
	int _minHeight(Node* pRoot) {
		if (pRoot == nullptr)
			return 0;

		int leftHeight = _minHeight(pRoot->_pLeft);
		int rightHeight = _minHeight(pRoot->_pRight);

		return leftHeight < rightHeight ? leftHeight+1 : rightHeight+1;
	}

	// 求最长路径
	int _maxHeight(Node* pRoot) {
		if (pRoot == nullptr)
			return 0;

		int leftHeight = _maxHeight(pRoot->_pLeft);
		int rightHeight = _maxHeight(pRoot->_pRight);

		return leftHeight > rightHeight ? leftHeight+1 : rightHeight+1;
	}

	bool _isPathRedBlackTree(Node* pRoot, size_t pathBlack, const size_t blackCount) {
		// 这是一个子函数 用来递归遍历树 判断 每条路径的黑节点是否相等 和 是否存在连续的 红节点

		if (pRoot == nullptr) {
			// 当 pRoot节点为空时, 就表示此条路径走到底了
			if (pathBlack != blackCount) {
				cout << "违反 红黑树每条路径的黑节点数目相等 规则" << endl;
				
				return false;
			}

			return true;
		}
		
		// 统计路径上的黑色节点
		if (pRoot->_color == BLACK)
			pathBlack++;

		// 判断是否存在连续的红节点
		if (pRoot->_color == RED && pRoot->_pParent && pRoot->_pParent->_color == RED) {
			cout << "违反 红黑树不能存在连续的红节点 规则" << endl;
			
			return false;
		}

		// 递归左右子树
		return _isPathRedBlackTree(pRoot->_pLeft, pathBlack, blackCount) && 
			   _isPathRedBlackTree(pRoot->_pRight, pathBlack, blackCount);
	}

	void rotateL(Node* parent) {
		Node* subR = parent->_pRight;
		Node* subRL = subR->_pLeft;
		
		parent->_pRight = subRL;
		if (subRL)
			subRL->_pParent = parent;

		// 为了链接subR 作为新的根节点, 需要将 parent的_pParent记录下来
		Node* ppNode = parent->_pParent;

		subR->_pLeft = parent;
		parent->_pParent = subR;
		
		if (parent == _root) {
			_root = subR;
			_root->_pParent = nullptr;
		}
		else {
			if (parent == ppNode->_pLeft) {
				ppNode->_pLeft = subR;
			}
			else {
				ppNode->_pRight = subR;
			}

			subR->_pParent = ppNode;
		}
	}

	void rotateR(Node* parent) {
		Node* subL = parent->_pLeft;
		Node* subLR = subL->_pRight;

		parent->_pLeft = subLR;
		if (subLR)
			subLR->_pParent = parent;

		Node* ppNode = parent->_pParent;

		subL->_pRight = parent;
		parent->_pParent = subL;

		if (parent == _root) {
			_root = subL;
			_root->_pParent = nullptr;
		}
		else {
			if (ppNode->_pLeft = parent) {
				ppNode->_pLeft = subL;
			}
			else {
				ppNode->_pRight = subL;
			}

			subL->_pParent = ppNode;
		}
	}
	
	Node* _root = nullptr;
};
