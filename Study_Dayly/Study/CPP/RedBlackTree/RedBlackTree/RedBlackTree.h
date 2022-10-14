#include <iostream>
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

	}

private:
	Node _root = nullptr;
};
