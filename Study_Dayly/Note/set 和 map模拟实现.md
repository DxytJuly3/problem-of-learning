# set 和 map 模板参数

STL容器中, set 和 map 虽然底层都是红黑树, 但是这两个容器的模板参数是不一样的, 在只考虑数据类型的情况下：

set 是 `template<class Key>`

map 则是 `template<class Key, class Value>`

很明显, 两种容器的模板参数数量都是不同的

要如何解决 相同的底层实现, 但是不同的模板参数呢？

有两种很简单粗暴的解决方法：

1. 对set设计一个只有单个数据的红黑树; 对map设计一个 两个数据类型的红黑树
2. 设计一个 两个数据类型的红黑树, 但是实现set时, 模板参数默认传0

但是 这两种方法 一个浪费, 一个粗暴，都不是那么的优秀

简单分析一下 STL源码是怎么解决这个问题的：

>  STL关于 set的部分源码： <img src="https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/image-20221023161225036.png" alt="image-20221023161225036" style="zoom:67%;" />
>
> 可以看到, typedef红黑树的部分, 红黑树的模板参数传参是 `<key_type, value_type>`
>
> 而 `key_type` 和 `value_type` 其实都是 `Key`

>  STL关于 map的部分源码： <img src="https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/image-20221023161511574.png" alt="image-20221023161511574" style="zoom:67%;" />
>
> map中 typedef红黑树的部分, 红黑树的模板参数传参 也是 `<key_type, value_type>`
>
> 但是 map的 `key_type` 是 `Key`, 而 `value_type` 是 `pair<const Key, T>`

只看 set 和 map 类型的部分源码基本看不出什么, 只能看出 STL实现两容器 底层使用的是有两个数据模板参数的红黑树

想要进一步看出具体的解决方案, 还要阅读一下 红黑树的部分源码

>  STL关于 红黑树的部分源码：<img src="https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/image-20221023155204283.png" alt="image-20221023155204283" style="zoom: 67%;" />
>
>  图中, 左半部分 是关于红黑树节点的部分源码; 右半部分 是关于红黑树结构的部分源码
>
>  阅读左半部分的源码, 可以发现 STL实现红黑树节点, 使用了继承：
>
>  ​	将 每个节点都具有的部分：颜色 父亲 左孩子 右孩子 定义为类 `rb_tree_node_base`; 定义另一个类 只拥有一个Value类型的成员变量, 其他继承于子类
>
>  再阅读右半部分的源码, 发现 `__rb_tree_node<Value> 被typedef为 rb_tree_node`, 所以 红黑树的节点其实是 `__rb_tree_node<Value>` 类型的
>
>  而 STL中 set 底层红黑树 传入的模板参数是 `<key_type, value_type>`, 且这两个类型相同 都是set的模板参数
>
>  map 底层红黑树传入的模板参数也是 `<key_type, value_type>`, 但是 map中的 value_type 是 `pair<const Key, T>`
>
>  **`总结一下：`**
>
>  1. STL实现set, set的关于数据的模板参数只有一个, 所以实例化 set 对象时 使用`set<Key>`
>
>      set 底层由红黑树实现, 红黑树的数据模板参数有两个, set 内部的 红黑树模板参数实际是 `rb_tree<Key, Key>`
>
>  2. STL实现map. map的关于数据的模板参数有两个, 所以实例化 map 对象时 要 `map<Key, T>`
>
>      不过 与 set不同,  map底层 红黑树的模板参数实际是 `rb_tree<Key, pair<const Key, T>>`

简单的分析过 STL关于set map rb_tree的这一部分源码后, 其实就可以发现：

set底层红黑树模板 这样传参: `rb_tree<Key, Key>`, 红黑树节点中的数据类型是 Key; map底层红黑树模板 这样传参: `rb_tree<Key, pair<const Key, T>>`, 红黑树节点中的数据类型是 `pair<const Key, T>`. 所以, 其实不难发现 **`STL中 红黑树是 以第二个模板参数的类型作数据类型 来创建节点的`**

所以, 红黑树这样创建节点 就不需要再区分 set 和 map 数据模板参数数目不同的问题, 因为 `即使容器的数据模板参数再多, 在调用红黑树进行模板传参时 也需要将所有数据类型整合到一个类型中 作为红黑树的第二个模板参数进行传参`

# 红黑树的实现

STL中红黑树节点的数据类型是 红黑树的第二个模板参数的类型。所以, 此时实现的红黑树 相较于 上一篇文章分析红黑树时所写的红黑树结构 就会有一定的区别：

```cpp
// 枚举常量, 表示 红 黑
enum Color {
    RED,
    BLACK
};

template<class T>
struct RBTreeNode {
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

template<class Key, class Value_type>
class RBTree {
    typedef RBTreeNode<Value_type> Node;			// 以 Value_type 作为节点类的模板参数 并 typedef

public:
    bool insert(const Value_type& data) {}

private:
    void rotateL(Node* parent) {}
    void rotateR(Node* parent) {}

    Node* _root = nullptr;
};
```

> 红黑树节点类模板，只有一个模板参数
>
> 红黑树类模板, 有两个数据类型模板参数, 但是 只用第二个模板参数 作节点的数据类型

## 红黑树节点数据的比较

红黑树是特殊的 二叉搜索树, 所以在插入数据时是一定会比较节点的数据大小的

对于基本的数据类型, 直接使用 `>`、`<` 等比较运算符就可以了

但是 对于复杂的类, 就比如 map 的节点数据类型 pair, 还可以直接使用 `>`、`<` 来实现目的吗？

### pair类 数据大小的比较

<img src="https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/image-20221025160609241.png" alt="image-20221025160609241" style="zoom:80%;" />

图中 蓝紫色部分的代码 就是 pair类中重载的比较运算符, 其中 `==` 和 `<` 运算符的功能是：

1. `==`: `两pair对象的 first 和 second 都相等`, 则为真
2. `<`: `左pair 的first 小于 右pair 的first 时` 或 `左pair的first 不小于 右pair的first时, 且左pair的second 小于 右pair的second时`, 为真

可以发现, pair对象的比较 与 pair对象的两个成员变量 有关

### 红黑树第二个模板参数类型数据的比较

pair对象的比较 与 pair对象的两个成员变量都有关系, 但是 `红黑树中节点的比较应该只对比 Key 的值, 而不对比 T 的值`

所以 对set来说可以直接比较节点数据, 但是 **对map来说不能直接比较节点数据, 因为 map节点数据的类型是 pair**。

那么红黑树该如何设计, 才能兼容不同的容器呢？

其实可以效仿STL中的解决方法： **对不同的 容器 实现针对此容器的 取节点Key值的 `仿函数`**

> <img src="https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/CSDN/image-20221025195746705.png" alt="image-20221025195746705" style="zoom:80%;" />
>
> 这是 在STL源码 分析的部分关于 `取节点数据的Key值的仿函数` 的代码
>
> 所以, STL源码中 `红黑树的第三个模板参数就是 取节点数据的Key值的仿函数`

仿函数需要在各自的容器中编写, 即 在Set中 写 取set的Key值的仿函数, 在Map中 写 取Map的Key值的仿函数

> set 的取key值的仿函数：
>
> ```cpp
> template<class Key>
> class Set{
>     struct SetKeyOfValue {
>         const Key& operator() (const Key& key) {
>             return key;
>         }
>     };
>     
> };
> ```
>
> 在 Set类 中定义一个 私有仿函数

> map 的取key值的仿函数：
>
> ```cpp
> template<class Key, class Value>
> class Map{
>     struct MapKeyOfValue {
>         const Key& operator() (const pair<Key, Value>& kv) {
>             return kv.first;
>         }
>     };
>     
> };
> ```

## Set、Map结构 及 底层红黑树插入实现

既然 Set和Map的底层红黑树 `需要使用仿函数取对应的 key值`, 所以 此时的红黑树 插入节点时, 无论是找位置还是调整节点 都`需要使用仿函数`来操作：

```cpp
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

template<class Key, class Value_type, class KeyOfValue>
class RB_Tree {
    typedef RBTreeNode<Value_type> Node;			// 对节点类型进行typedef

public:
    bool insert(const Value_type& data) {
        if (_root == nullptr) {
            // 树为空时, 插入新节点
            _root = new Node(data);
            _root->_color = BLACK;			// 根节点要为 黑

            return true;
        }
        
        KeyOfValue KOV;				// 实例化仿函数对象, 为调用仿函数
        
        // 树不为空, 就从根节点开始找位置
        Node* cur = _root;
        Node* parent = cur->_pParent;
        while (cur) {
            if (KOV(data) > KOV(cur->_data)) {		// 调用仿函数找key值 对比
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
                return false;
            }
        }

        // 出循环之后, cur所在位置就是 新节点需要插入的位置
        cur = new Node(data);
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

        return true;						// 插入完成, 返回true
    }

private:
    Node* _root = nullptr;
};
```

除了对比key值需要使用仿函数之外, 没有什么需要注意的

然后就是 Set 和 Map的结构

上面分析过：

1. Set 的模板参数只有一个 就是数据的类型, 内部调用红黑树, 模板传参就是 `rb_tree<Key, Key>`
2. Map 的模板参数有两个, 则 内部调用红黑树, 模板传参就是 `rb_tree<Key, pair<Key, Value>>`

而 由于需要兼容不同数据类型的指定方法的key值对比, 所以 添加一个仿函数用来取key值, 所以 set 和 map 的结构定义：

> Set 的结构：
>
> ```cpp
> template<class Key>
> class Set {
> 	typedef Key key_type;
> 	typedef Key value_type;
> 
> 	// 取key值的仿函数
> 	struct SetKeyOfValue {
> 		const key_type& operator() (const value_type& key) {
> 			return key;
> 		}
> 	};
> 
> private:
> 	RB_Tree<key_type, key_type, SetKeyOfValue> _tree;
> };
> ```

> Map 的结构：
>
> ```cpp
> template<class Key, class Value>
> class Map {
> 	typedef Key key_type;
> 	typedef pair<Key, Value> value_type;		// pair<Key, Value>作为数据类型
> 
> 	// 取key值的仿函数
> 	struct MapKeyOfValue {
> 		const key_type& operator() (const value_type& kv) {
> 			return kv.first;
> 		}
> 	};
> 
> private:
> 	RB_Tree<key_type, value_type, MapKeyOfValue> _tree;
> };
> ```

## * 红黑树的迭代器

