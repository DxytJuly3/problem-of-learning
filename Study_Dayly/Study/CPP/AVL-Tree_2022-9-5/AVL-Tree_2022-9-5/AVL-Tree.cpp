﻿#include "AVL-Tree.h"	

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
		//	首先要知道 从新节点 向上 更新祖先节点的平衡因子，是有可能更新到整棵树的根的，其次就是 当某祖先节点的平衡因子变为0时，停止更新
		//	
		//	祖先节点的平衡因子变为0 停止更新是因为 平衡因子变为0了，就说明以此节点为根的树的高度没有变化，只是把低的子树拔高了一层
		//	也就意味着 此节点的祖先节点的平衡因子不会变化
		//	而 如果某节点的平衡因子变为了 1 或 -1, 就说明 以此节点为根的树 高度发生了变化，进而会影响其祖先节点的平衡因子
		//	如果某节点的平衡因子变为了 -2 或 2，那么就需要 调整以此节点为根的树保持平衡了
		//	所以 从新节点 向上修改祖先节点的平衡因子的循环结束条件是 某祖先节点的平衡因子变为 0
		while (parent) {
			if (cur == parent->_pLeft)
				parent->_bf--;			// 新节点在父亲节点的左孩子，则父亲节点的左子树高度+1，则父亲节点的平衡因子-1
			else
				parent->_bf++;

			// 更新完之后，就需要判断 需要继续更新 还是停止更新 或是调整平衡了
			if(parent->_bf == 0) {
				// 某祖先节点的平衡因子 从 -1 或 1 -> 0，说明 插入新节点使此祖先节点的左右子树高度相等了
				// 不会再影响更上边的节点，所以可以结束
				break;
			}
			else if (parent->_bf == -1 || parent->_bf == 1) {
				// 某祖先节点的平衡因子从 0 变成了 -1 或 1，说明 此祖先节点的左右子树原先没有高度差，但是插入新节点使其左右子树有了高度差
				// 可能会继续影响更高节点的平衡 所以需要更新parent 和 cur，进而继续更新祖先节点的平衡因子
				cur = cur->_pParent;
				parent = parent->_pParent;
			}
			else if (parent->_bf == -2 || parent->_bf == 2) {
				// 当某祖先节点的平衡因子 从 -1 -> -2 或 从 1 -> 2，就说明 插入新节点使此祖先节点的高子树变得更高了
				// 进而已经影响了以此祖先节点为根的树的平衡，所以就需要调节节点进而维持平衡了
				// AVL树 调节平衡的方法是 旋转
				// 但是 根据树的形态以及插入节点的位置不同，会有不同的旋转方式，需要画图理解


			}
			else {
				// 以上情况都是在保证插入新节点时，树已经是平衡二叉搜索树
				// 如果不是 则会走到此处 触发断言 进而发现错误
				assert(false);
			}
		}
	}

private:
	Node* _root = nullptr;
};