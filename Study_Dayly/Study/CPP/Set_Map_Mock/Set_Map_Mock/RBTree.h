#pragma once
#include <iostream>
#include <cassert>
using namespace std;

// 枚举常量, 表示 红 黑
enum Color {
    RED,
    BLACK
};

template<class T>
struct RBTreeNode {
    // RedBlackTreeNode 红黑树节点
    RBTreeNode(const T& data = T())
        : _pLeft(nullptr), _pRight(nullptr), _pParent(nullptr)
        , _data(data)
        , _color(RED) 	// 新节点默认为红节点 
    {}

    RBTreeNode<T>* _pLeft;			// 节点左孩子
    RBTreeNode<T>* _pRight;		    // 节点右孩子
    RBTreeNode<T>* _pParent;		// 节点父亲节点

    T _data;					     // 节点数据
    Color _color;					// 节点颜色
};

template<class Type, class Ref, class Ptr>			// 模板参数分别是 原类型，引用类型，指针类型
struct _RB_Tree_Iterator {
    typedef RBTreeNode<Type> Node;
    typedef _RB_Tree_Iterator<Type, Ref, Ptr> Self;

    _RB_Tree_Iterator(Node* node)
        : _node(node)
    {}

    Ref operator*() {
        return _node->_data;					// * 解引用 返回节点中的数据。返回值是引用类型 因为需要提供修改功能
    }

    Ptr operator->() {
        return &_node->_data;					// -> 返回节点中数据的地址。返回值是指针类型
    }
    
    Self& operator++() {        // 无 int参数, 前置++
        if (_node->_pRight == nullptr) {        // 迭代器指向节点 没有 右孩子
            // 需要从此节点向上找 第一个不是右孩子的节点的父亲节点
            Node* cur = _node;
            Node* parent = cur->_pParent;

            while (parent && cur == parent->_pRight) {      // 当父亲节点存在, 且cur节点还是其右孩子时 循环继续
                cur = cur->_pParent;
                parent = parent->_pParent;
            }

            // 走到这里 cur节点就是 第一个不为右孩子的节点
            _node = parent;
            // 如果 迭代器++ 之前 指向的是树中最后一个节点, 则 执行上述代码之后
            // cur会走到 整棵树的根节点, 而根节点的parent为空
            // 所以 迭代器会为空
        }
        else {              // 迭代器指向的节点 存在右子树
            // 找右子树的最左节点
            Node* farLeft = _node->_pRight;
            while (farLeft->_pLeft) {
                farLeft = farLeft->_pLeft;
            }

            _node = farLeft;
        }

        return *this;                       // 返回新的迭代器
    }

    Self& operator++(int) {                 // 后置++
        Self tmp(*this);                    // 拷贝此迭代器

        ++(*this);                          // 复用前置++

        return tmp;                         // 返回++前 拷贝的迭代器
    }

    Self& operator--() {                     // 无 int参数 前置--
        if (_node->_left == nullptr) {          // 当迭代器指向的节点 不存在左孩子 时
            // 需要从此节点向上找 第一个不是左孩子 的节点的父亲节点
            Node* cur = _node;
            Node* parent = cur->_pParent;

            while (parent && cur == parent->_pLeft) {
                cur = cur->_pParent;
                parent = parent->_pParent;
            }

            // 走到这里 cur节点就是 第一个不为左孩子的节点
            _node = parent;
        }
        else {               // 迭代器指向节点 存在 左孩子时
            // 找左子树的最右节点
            Node* subRight = _node->_pLeft;
            while (subRight->_pRight) {
                subRight = subRight->_pRight;
            }

            _node = subRight;
        }

        return *this;
    }

    Self& operator--(int) {
        Self tmp(*this);

        --(*this);

        return tmp;
    }

    bool operator!=(const Self& It) const {
        return _node != It._node;
    }

    bool operator==(const Self& It) const {
        return _node == It._node;
    }

    // 可能需要其他类访问, 所以设置为公有的
    Node* _node;
};

template<class Key, class Value_type, class KeyOfValue>
class RB_Tree {
    typedef RBTreeNode<Value_type> Node;			// 对节点类型进行typedef

public:
    // 由于需要在类外使用  所以 typedef 为公共的
    typedef _RB_Tree_Iterator<Value_type, Value_type&, Value_type*> iterator;
    typedef _RB_Tree_Iterator<Value_type, const Value_type&, const Value_type*> const_iterator;

    iterator begin() {          // begin 取树的最左节点
        Node* farLeft = _root;
        while (farLeft && farLeft->_pLeft) {
            // 判断 farLeft是否存在 是为了防止 树为空时 farLeft->_pLeft 访问使用空指针
            farLeft = farLeft->_pLeft;
        }

        return iterator(farLeft);
    }
    iterator end() {
        return iterator(nullptr);
    }

    const_iterator begin() const {
        Node* farLeft = _root;
        while (farLeft && farLeft->_pLeft) {
            farLeft = farLeft->_pLeft;
        }

        return const_iterator(farLeft);
    }
    const_iterator end() const {
        return const_iterator(nullptr);
    }

    iterator find(const Key& key) {
        //  查找节点 是按照 key 来找的
        Node* cur = _root;
        KeyOfValue KOV;
        while (cur) {
            if (KOV(cur->_data) < key) {
                cur = cur->_pRight;
            }
            else if (KOV(cur->_data) > key) {
                cur = cur->_pLeft;
            }
            else {
                return iterator(cur);
            }
        }

        return end();           // 走到这 就没有找到
    }
       
    // 插入数据之后 要返回新节点的迭代器 和 插入结果
    pair<iterator, bool> insert(const Value_type& data) {
        if (_root == nullptr) {
            // 树为空时, 插入新节点
            _root = new Node(data);
            _root->_color = BLACK;			// 根节点要为 黑

            return make_pair(iterator(_root), true);
        }
        
        KeyOfValue KOV;
        // 树不为空, 就从根节点开始找位置
        Node* cur = _root;
        Node* parent = cur->_pParent;
        while (cur) {
            if (KOV(data) > KOV(cur->_data)) {
                // 插入数据大, 就向右子树找
                parent = cur;
                cur = cur->_pRight;
            }
            else if (KOV(data) < KOV(cur->_data)) {
                // 插入数据小, 就向左子树找
                parent = cur;
                cur = cur->_pLeft;
            }
            else {
                // 树中已存在插入数据, 返回 false 插入失败
                return make_pair(iterator(cur), false);
            }
        }

        // 出循环之后, cur所在位置就是 新节点需要插入的位置
        cur = new Node(data);

        Node* newNode = cur;                // 记录新节点位置 以返回

        cur->_color = RED;
        // parent 与 cur连接起来
        if (KOV(data) > KOV(parent->_data)) {
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

        return make_pair(iterator(newNode), true);
    }

private:
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

    Node* _root = nullptr;
};
