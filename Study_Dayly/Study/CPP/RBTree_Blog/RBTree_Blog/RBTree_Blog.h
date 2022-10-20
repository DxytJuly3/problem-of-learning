#pragma once
#include <iostream>
#include <vector>
#include <cassert>
#include <queue>
using namespace std;

// 枚举常量, 表示 红 黑
enum Color {
    RED,
    BLACK
};

template<class T1>
struct RBTreeNode {
    // RedBlackTreeNode 红黑树节点
    RBTreeNode(const T1& data = T1())
        : _pLeft(nullptr), _pRight(nullptr), _pParent(nullptr)
        , _data(data)
        , _color(RED) 	// 新节点默认为红节点 
    {}

    RBTreeNode<T1>* _pLeft;			// 节点左孩子
    RBTreeNode<T1>* _pRight;		// 节点右孩子
    RBTreeNode<T1>* _pParent;		// 节点父亲节点

    T1 _data;					     // 节点数据
    Color _color;					// 节点颜色
};

template<class T1>
class RBTree {
    typedef RBTreeNode<T1> Node;			// 对节点类型进行typedef

public:
    bool insert(const T1& data) {
        if (_root == nullptr) {
            // 树为空时, 插入新节点
            _root = new Node(data);
            _root->_color = BLACK;			// 根节点要为 黑

            return true;
        }

        // 树不为空, 就从根节点开始找位置
        Node* cur = _root;
        Node* parent = cur->_pParent;
        while (cur) {
            if (data > cur->_data) {
                // 插入数据大, 就向右子树找
                parent = cur;
                cur = cur->_pRight;
            }
            else if (data < cur->_data) {
                // 插入数据小, 就向左子树找
                parent = cur;
                cur = cur->_pLeft;
            }
            else {
                // 树中已存在插入数据, 返回 false 插入失败
                return false;
            }
        }

        // 出循环之后, cur所在位置就是 新节点需要插入的位置
        cur = new Node(data);
        cur->_color = RED;
        // parent 与 cur连接起来
        if (data > parent->_data) {
            // 数据大, 即新节点是父亲节点的右节点
            parent->_pRight = cur;
        }
        else {
            // 数据小, 即新节点是父亲节点的左节点
            parent->_pLeft = cur;
        }
        cur->_pParent = parent;

        // 上面插入新节点时 已经记录了 cur 和 parent节点
        while (parent && parent->_color == RED) {
            // 父亲节点存在, 且父亲节点也为红色时
            Node* grandFa = parent->_pParent; 			// 记录祖先节点
            assert(grandFa);						 // 断言祖父节点存在
            // 如果祖父节点不存在, 就说明 parent节点是树的根, 是不可能的 因为红黑树根不可能是红色的

            if (parent == grandFa->_pLeft) {
                // 父亲节点是祖先节点的左孩子
                Node* uncle = grandFa->_pRight;			// 记录叔叔节点
                if (uncle && uncle->_color == RED) {
                    // 叔叔节点存在 且是红节点
                    parent->_color = uncle->_color = BLACK;			// 父亲节点 和 叔叔节点改为黑色
                    grandFa->_color = RED;						 // 祖父节点 改为红色

                    cur = grandFa;								// 更新 grandFa节点为新的cur节点
                    parent = cur->_pParent;						  // 更新 新的parent节点
                }
                else {
                    // uncle为空 或 为黑时
                    if (cur == parent->_pLeft) {
                        // parent是grandFa的左孩子, cur是parent的左孩子, 即 直线的情况
                        rotateR(grandFa);				// 将 祖先节点作为rotateR的parent, 右单旋

                        parent->_color = BLACK;			 // 更新 parent节点颜色为黑
                        grandFa->_color = RED;			 // 更新 grandFa节点颜色为红
                    }
                    else {
                        // parent是grandFa的左孩子, cur是parent的右孩子, 即 折线的情况
                        rotateL(parent);				// 先将 parent节点作为rotateL的parent, 左单旋
                        rotateR(grandFa); 				// 再将 grandFa节点作为rotateR的parent, 右单旋

                        cur->_color = BLACK;			// 更新 cur节点颜色为黑
                        grandFa->_color = RED;			// 更新 grandFa节点颜色为红
                    }
                    // 处理之后 结束循环
                    break;
                }
            }
            else {
                // 父亲节点是祖先节点的右孩子
                Node* uncle = grandFa->_pLeft;			// 记录叔叔节点
                if (uncle && uncle->_color == RED) {
                    parent->_color = uncle->_color = BLACK;
                    grandFa->_color = RED;

                    cur = grandFa;
                    parent = cur->_pParent;
                }
                else {
                    // uncle为空 或 为黑时
                    if (cur == parent->_pRight) {
                        // parent是grandFa的右孩子, cur是parent的右孩子, 即 直线的情况
                        rotateL(grandFa);				// 将 祖先节点作为rotateL的parent, 左单旋

                        parent->_color = BLACK;			 // 更新 parent节点颜色为黑
                        grandFa->_color = RED;			 // 更新 grandFa节点颜色为红
                    }
                    else {
                        // parent是grandFa的右孩子, cur是parent的左孩子, 即 折线的情况
                        rotateR(parent);				// 先将 parent节点作为rotateR的parent, 右单旋
                        rotateL(grandFa); 				// 再将 grandFa节点作为rotateL的parent, 左单旋

                        cur->_color = BLACK;			// 更新 cur节点颜色为黑
                        grandFa->_color = RED;			// 更新 grandFa节点颜色为红
                    }
                    // 处理之后 结束循环
                    break;
                }
            }
        }
        _root->_color = BLACK;				  // 无论如何 最后更新根节点的颜色为黑

        return true;						// 插入完成, 返回true
    }

    
    void treeHeight() {
        cout << "最长路径长度：" << _maxHeight(_root) << endl;
        cout << "最短路径长度：" << _minHeight(_root) << endl;
    }

    bool isRBTree() {
        if (_root == nullptr)
            return true;			// 空树 也可看做红黑树

        if (_root->_color == RED)
            return false;			// 根节点为红, 不可能是红黑树

        // 取任意一条路径上的黑节点数目 作为比较基准
        Node* pCur = _root;
        size_t blackCount = 0;
        while (pCur) {
            if (pCur->_color == BLACK)
                blackCount++;

            pCur = pCur->_pLeft;
        }

        size_t pathBlack = 0;
        return _pathBlackCom(_root, pathBlack, blackCount);
    }

    void inOrder() {
        _inOrder(_root);
        cout << endl;
    }

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

private:
    void _inOrder(Node* pRoot) {
        if (pRoot == nullptr)
            return;

        _inOrder(pRoot->_pLeft);
        cout << pRoot->_data << " ";
        _inOrder(pRoot->_pRight);
    }

    void rotateL(Node* parent) {
        Node* subR = parent->_pRight;
        Node* subRL = subR->_pLeft;

        parent->_pRight = subRL;
        if (subRL)
            subRL->_pParent = parent;

        Node* ppNode = parent->_pParent;

        subR->_pLeft = parent;
        parent->_pParent = subR;

        if (parent == _root) {
            _root = subR;
            _root->_pParent = nullptr;
        }
        else {
            if (parent == ppNode->_pLeft)
                ppNode->_pLeft = subR;
            else
                ppNode->_pRight = subR;

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
            if (parent == ppNode->_pLeft)
                ppNode->_pLeft = subL;
            else
                ppNode->_pRight = subL;

            subL->_pParent = ppNode;
        }
    }

    bool _pathBlackCom(Node* pRoot, size_t pathBlack, const size_t& blackCount) {
        // pRoot为空时, 比较计算路径和基准路径黑节点数目
        if (pRoot == nullptr) {
            if (pathBlack != blackCount) {
                // 计算出的路径黑节点数目 与 基准路径黑节点数目不等时
                cout << "违反 每条路径黑节点数目相等 规则" << endl;
                return false;
            }
            return true;
        }

        if (pRoot->_color == BLACK)
            pathBlack++;

        if (pRoot->_color == RED && pRoot->_pParent && pRoot->_pParent->_color == RED) {
            // 当前节点 以及父亲节点同时为红时
            cout << "违反 不能存在连续的红节点 规则" << endl;
            return false;
        }

        return _pathBlackCom(pRoot->_pLeft, pathBlack, blackCount) &&
            _pathBlackCom(pRoot->_pRight, pathBlack, blackCount);		// 递归判断左右子树
    }

    int _maxHeight(Node* pRoot) {
        if (pRoot == nullptr)
            return 0;

        int leftHeight = _maxHeight(pRoot->_pLeft);
        int rightHeight = _maxHeight(pRoot->_pRight);

        return leftHeight > rightHeight ? leftHeight + 1 : rightHeight + 1;
    }

    int _minHeight(Node* pRoot) {
        if (pRoot == nullptr)
            return 0;

        int leftHeight = _minHeight(pRoot->_pLeft);
        int rightHeight = _minHeight(pRoot->_pRight);

        return leftHeight < rightHeight ? leftHeight + 1 : rightHeight + 1;
    }

    Node* _root = nullptr;
};
