#include <iostream>
#include <cassert>
using namespace std;

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
	bool insert(T1& data) {
		if (_root == nullptr) {
			_root = Node(data);

			return true;
		}

		Node* cur = _root;				// 从根节点开始找 插入结点的位置
		Node* parent = cur->_pParent;
		while (cur) {
			if (data > cur->_data) {
				// data大 向右找
				cur = cur->_pRight;
				parent = cur->_pParent;
			}
			else if (data < cur->_data) {
				// data小 向左找
				cur = cur->_pLeft;
				parent = cur->_pParent;
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
			if (grandFa->_pLeft = parent) {
				Node* uncle = grandFa->_pRight;

				// 此时 也会因为 叔叔节点的情况不同 存在不同的处理方法
				// 情况1：叔叔节点存在 且为 红节点时
				//	直接将 parent和uncle节点改为黑节点, 且把 grandFa节点改为红节点
				//	为什么 将parent 和 uncle节点改为黑节点的同时, 要把 grandFa 节点变为红节点？
				//	因为 要满足 红黑树的条件之一：每条路径的黑节点数目相等
				//		因为叔叔节点和父亲节点原来都是红节点, 也就说名祖父节点本来是黑节点
				//		既然 已经将 parent 和 uncle节点改为黑节点了, 那么就需要将这两个节点的父亲节点 也就是grandFa节点改为红节点
				//		来保证路径上的黑节点数目是不变的
				if (uncle->_color == RED) {
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
						rotateL(grandFa);

						cur->_color = BLACK;
						grandFa->_color = RED;
					}
					
					break;
				}
			}
			// 当 parent是祖父节点的右孩子时
			else {
				Node* uncle = grandFa->_pLeft;
				
				if (uncle->_color == RED) {
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
		cur->_color = BLACK;

		return true;
	}

	void rotateR(Node* parent) {
		Node* subR = parent->_pParent;
		Node* subRL = subR->_pLeft;
		
		parent->_pLeft = subR;
		if (subR)
			subR->_pParent = parent;

		// 为了链接subR 作为新的根节点, 需要将 parent的_pParent记录下来
		Node* ppNode = parent->_pParent;

		subR->_pRight = parent;
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

	void rotateL(Node* parent) {
		Node* subL = parent->_pLeft;
		Node* subLR = subL->_pRight;

		parent->_pRight = subLR;
		if (subLR)
			subL->_pParent = parent;

		Node* ppNode = parent->_pParent;

		subL->_pLeft = parent;
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

private:
	Node _root = nullptr;
};
