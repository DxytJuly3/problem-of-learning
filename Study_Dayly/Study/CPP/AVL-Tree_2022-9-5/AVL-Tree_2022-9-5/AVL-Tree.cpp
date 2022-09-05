#include <iostream>
using namespace std;

template<class T>
struct AVLTreeNode{
	AVLTreeNode(const T& data)
		: _pLeft(nullptr)
		, _pRight(nullptr)
		, _pParent(nullptr)
		, _data(data)
		, _bf(0)
	{}

	AVLTreeNode<T>* _pLeft; // 该节点的左孩子
	AVLTreeNode<T>* _pRight; // 该节点的右孩子
	AVLTreeNode<T>* _pParent; // 该节点的双亲
	T _data;
	int _bf; // 该节点的平衡因子
};

template<class T>
class AVLTree {
	typedef AVLTreeNode<T> Node;

public:
	bool insert(const T& data) {
		// 首先按照 二叉搜索树的方式 查找插入位置并插入节点
		if (_root == nullptr) {
			// 树为空 插入节点 直接将新节点作为树的根
			_root = new Node(data);
			_root->_bf = 0;		// 只有根节点的树，根节点平衡因子为 0

			return true;		// 插入成功，直接返回
		}

		// 走到这里就说明需要查找插入位置了
		Node* cur = _root;	// 从根节点开始比较
		Node* parent = nullptr;	// 需要记录父亲节点 供插入时连接
		while (cur) {
			// 循环结束的条件是 cur为空，cur为空时就说明 插入位置找到了
			if (cur->_data > data) {
				// 插入值比当前节点值 小，则向左孩子找
				parent = cur;
				cur = cur->_pLeft;
			}
			else if (cur->_data < data) {
				// 插入值比当前节点值 大，则向右孩子找
				parent = cur;
				cur = cur->_pRight;
			}
			else {
				// 走到这里 说明数中已存在相同数据
				return false;
			}
		}

		// 出循环之后，cur 即为数据需要插入的位置
		cur = new Node(data);
		// 将cur与树连接起来
		if (data > parent->_data) {
			parent->_pRight = cur;		// 插入数据比父亲节点数据大，则插入到父亲节点的右孩子
		}
		else if (data < parent->_data) {
			parent->_pLeft = cur;			// 插入数据比父亲节点数据小，则插入到父亲节点的左孩子
		}
		// 三叉链结构，cur节点虚存储父亲节点
		cur->_pParent = parent;

		// 代码走到这里，就说明 节点已经插入到树中 应该插入的位置了
		// 接下来要做的就是 分析平衡 调整平衡
		// 首先是分析平衡：
		//	需要根据节点的平衡因子来分析是否平衡
		//	而 已经在树中插入了新的节点，所以新节点的祖先节点的子树高度差一定会发生变化
		//	首先要做的就是 更新新节点的祖先节点的平衡因子
		// 怎么更新？
		//	首先要知道，如果插入新数据之前，此树已经是平衡二叉搜索树
		//			 那么插入新数据之后，其祖先节点的平衡因子会发生什么变化？
		//		1. 祖先节点的平衡因子 变为 1
		//			此时只有一种可能：
		//				插入前，祖先节点左右子树的高度相等，新节点插在了祖先节点的 右子树 里
		//				_bf 由 0 -> 1
		//		2. 祖先节点的平衡因子 变为 -1
		//			此时同样只有一种可能：
		//				插入前，祖先节点左右子树的高度相等，新节点插在了祖先节点的 左子树 里
		//				_bf 由 0 -> -1
		//		3. 祖先节点的平衡因子 变为 0
		//			可能1：
		//				插入前，祖先节点 左 比 右子树 高度高 1，新节点插在了祖先节点的 右子树 里
		//				_bf 由 -1 -> 0
		//			可能2：
		//				插入前，祖先节点 右 比 左子树 高度高 1，新节点插在了祖先节点的 左子树 里
		//				_bf 由 1 -> 0
		//		4. 祖先节点的平衡因子 变为 2
		//				插入前，祖先节点 右 比 左子树 高度高 1，新节点依旧插在了祖先节点的 右子树 里
		//				_bf 由 1 -> 2
		//		5. 祖先节点的平衡因子 变为 -2
		//				插入前，祖先节点 左 比 右子树 高度高 1，新节点依旧插在了祖先节点的 左子树 里
		//				_bf 由 -1 -> -2
		//	祖先节点的平衡因子 需要 从新节点向上 循环 找祖先节点更新
		//	那么 循环应该什么时候停止？
		//
	}

private:
	Node* _root = nullptr;
};