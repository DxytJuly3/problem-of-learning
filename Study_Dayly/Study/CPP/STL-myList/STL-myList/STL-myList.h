#include <iostream>
#include <cassert>

namespace July
{
	template<class Iterator, class Ref, class Ptr>
	struct reverseIterator
	{
		typedef reverseIterator<Iterator, Ref, Ptr> Self;

		Iterator _it;

		// 构造函数
		// 反向迭代器的成员变量是正向迭代器，构造函数都是在对象实例化时调用的
		// 反向迭代器就是在 类的 rbegin() 或 rend() 中，构造函数的传参也是
		// 需要将反向迭代器的成员变量初始化为 其调用对象的相应的正向迭代器
		reverseIterator(Iterator it)
			:_it(it)
		{}

		// * 操作符重载
		// 作用是 *解引用反向迭代器，可提供对返回值的修改，所以要用&返回
		// 返回的是 当前位置正向迭代器的前一位的解引用，实质返回的是什么需要看 正向迭代器的实现
		// 为什么是正向迭代器的前一位？
		// 以 rbegin() 获取的反向迭代器为例，获取的是最后一个元素的下一位，即不在容器的数据范围内，如果直接对当前位置的正向迭代器解引用，会发生错误，前一位才数据容器的数据范围
		Ref operator*()
		{
			Iterator tmp(_it);

			return *(--tmp);
		}

		// -> 操作符重载
		// -> 一般用于指针操作，所以返回应该是指针
		// 返回的也是 当前位置正向迭代器的迁移位置解引用的取地址
		Ptr operator->()
		{
			return &(operator*()); 		// 复用 *重载
		}
		// 前置++重载
		// 前置 ++\-- 都直接改变原值所以不需要拷贝，且返回的都是修改后的迭代器
		// 后置 ++\-- 返回修改前的迭代器，所以需要保存修改前的迭代器
		Self& operator++()
		{
			--_it; 			// 反向迭代器 ++其实是 --

			return *this;
		}
		// 后置++
		Self operator++(int)
		{
			Self tmp(_it); 		// 保存修改前的迭代器
			--_it;

			return tmp;  			// 返回临时变量所以 传值返回
		}
		// 前置--
		Self& operator--()
		{
			++_it; 			// 反向迭代器 --其实是 ++

			return *this;
		}
		// 后置--
		Self operator--(int)
		{
			Self tmp(_it);
			++_it;

			return tmp;
		}

		// != 与 == 的重载
		bool operator!=(const Self& sit)
		{
			return _it != sit._it;
		}
		bool operator==(const Self& sit)
		{
			return _it == sit._it;
		}
	};

	// 模拟STL-List中的 __list_node类
	template<class T>
	struct list_node
	{
		list_node<T>* _next;		// C++ 可以在类内直接使用本类名
		list_node<T>* _prev;
		T _val;

		list_node(const T& val = T())	// 构造函数
			:_next(nullptr)
			, _prev(nullptr)
			, _val(val)
		{}
	};


	template<class T, class Ref, class Ptr>
	struct __list_iterator
	{
		typedef list_node<T> Node;		// 
		typedef __list_iterator<T, Ref, Ptr> self;
		// self 有许多作用
		// self是在迭代器类内 typedef的，所以self 其实是已经知道数据类型的 __list_iterator 类
		// 1. 所以 self可以作为 ++、-- 重载函数的返回值类型，因为 ++、-- 应该返回 迭代器对象 的类型
		// 2. self 在 ++、-- 重载函数内，实例化 __list_iterator类的 对象

		Node* _node;		// __list_iterator 的成员变量，其实就是 Node* 类型的变量

		__list_iterator(Node* node)
			:_node(node)
		{}
		// __list_iterator 构造函数的参数为Node*，实际使用的iterator 即为 由传入的数据节点地址 构造的对象

		// 迭代器的重载都有：++、--、*(解引用)、->、!=、==
		self& operator++()	// 前置++，返回引用类型
		{
			_node = _node->_next;

			return *this;
		}
		self operator++(int)
		{
			self tmp(*this);	// self的运用，使用self 使用此迭代器成员 实例化迭代器对象，即保存迭代器
			_node = _node->_next;

			return tmp;
		}
		self& operator--()
		{
			_node = _node->_prev;
			return *this;
		}
		self operator--(int)
		{
			self tmp(*this);
			_node = _node->_prev;

			return *this;
		}

		Ref operator*()
		{
			return _node->_val;
		}

		Ptr operator->()
		{
			return &(_node->_val);
		}

		bool operator==(const self& it)
		{
			return _node == it._node;
		}

		bool operator!=(const self& it)
		{
			return _node != it._node;
		}

	};
	// 读STL 关于List的源码
	// 可以找到list类中的 成员变量只有一个 link_type node;
	// (link_type 是list_node* 的typedef, 而list_node* 是 __list_node<T>的typedef)
	// __list_node<T>是一个模板类  (在上面模拟实现)
	// 此模板类 List中的一个节点的的类型，即 拥有两个指针和一个数据
	//
	// 但是只看库中成员变量的实际内容，还不能够完全确定 库中的 List究竟是什么结构的链表
	// 所以，需要查看库中 List的构造函数，看实例化出的对象初始状态来进行结构的判断
	// 找到 构造函数List() 可以看到 其调用了另一个函数 empty_initialize();
	// 在库中 empty_initialize();函数的作用是：从内存池中定义一个node节点，并将node->next 和 node->prev 指向node
	// 可以看出，库中的 List其实是 双向带头循环结构的 链表
	// 因为 List类实例化对象的初始状态就是 只有头节点没有数据的 双向循环链表
	// 下面就可以根据库中的源代码框架 来自己模拟实现List，其实模拟实现的操作与之前的 双向带头循环链表类似
	template<class T>
	class list
	{
		typedef list_node<T> Node;	// 将节点的类 typedef为 Node 更容易表达含义
	public:
		typedef __list_iterator<T, T&, T*> iterator;					// 非const迭代器
		typedef __list_iterator<T, const T&, const T*> const_iterator;	// const迭代器

		typedef reverseIterator<iterator, T&, T*> reverse_iterator;		// 非 const反向迭代器
		typedef reverseIterator<const_iterator, const T&, const T*> const_reverse_iterator;		//  const反向迭代器

		// 由于List结构是带头结点的双向循环链表，头节点不需要存数据，所以构造函数不用传参
		list()
		{
			/*_head = new Node();			// _node 为Node类的实例化对象的指针，new 调用Node构造函数实例化对象 并将其地址赋予_node
			_head->_next = _head;
			_head->_prev = _head;*/

			empty_init();
		}

		void empty_init()				// 此函数的作用在于，对象实例化时对成员变量初始化，因为这个过程用到的次数较多，所以写成函数
		{
			_head = new Node();
			_head->_next = _head;
			_head->_prev = _head;
		}

		//===== list 传统写法的拷贝构造函数=====
		/*list(const list<T>& lt)
		{
			empty_init();			// 先初始化成员变量

			for(auto VAL : lt)		// 使用迭代器遍历 lt 并尾插至需要拷贝实例化的对象中
				push_back(VAL);
		}
		// 其实list 拷贝构造函数的传统写法(编译器生成的默认拷贝构造不行)，比较简单明了
		*/

		// ===== STL源码中list的 同样实现了迭代器区间方法的构造函数 =====
		template <class InputIterator>
		list(InputIterator first, InputIterator last)
		{
			empty_init();

			while (first != last)		// 注意，从list 往后的迭代器就不能使用 > < <= >= 这种逻辑比较了
			{							// 只能用 == 或 != 
				push_back(*first);		// 铭记 list迭代器的成员变量是节点类型的，直接解引用就是一个节点
				++first;
			}
		}

		// list 拷贝构造函数的现代写法
		// list 拷贝构造和赋值的现代写法，还是利用中间变量直接交换数据
		// ====== 先实现一个专属于list的swap函数=====
		void swap(list<T>& lt)
		{
			std::swap(_head, lt._head);			// 带头结点的链表的数据交换只交换头节点就已经完成了所有数据的交换
		}
		//====== 拷贝构造现代写法 ======
		list(const list<T>& lt)
		{
			empty_init();

			list<T> TMP(lt.begin(), lt.end());
			swap(TMP);
		}

		// ====== '=' 赋值重载函数 现代写法
		list<T> operator=(list<T> lt)
		{
			swap(lt);

			return *this;
		}

		// 析构函数
		// 析构函数是清理资源的函数，在list中就是需要将每个节点的数据清理掉，只能一个一个清理,所以在实现析构之前，先实现一个clear() 函数，清理数据节点
		void clear()
		{
			iterator ltIt = begin();		// 每个数据节点都只是 list_node类实例化的对象，没有动态开辟空间
			while (ltIt != end())			// 从首数据节点开始erase每个节点 直到迭代器回到头结点
			{
				ltIt = erase(ltIt);
				// erase完之后不用让迭代器++, 而是用迭代器接收erase的返回值, 是因为 erase的返回值就是删除节点的下一节点的迭代器
				// 这个操作可以有效避免 list中迭代器失效的问题
			}
		}

		// ====== 析构函数 ======
		~list()
		{
			clear();				// 先直接clear清理数据节点
			delete _head;			// 然后delete释放头节点空间, 头节点空间是 new出来的
			_head = nullptr;		// 再然后再将头节点置空

		}
		// ===== 尾插=====
		// 双向带头循环链表尾插其实就是 在头节点的prev插入
		void push_back(const T& val)
		{
			/*Node* tail = _head->_prev;	// 记录头结点的 prev
			Node* newNode = new Node(val);

			newNode->_next = tail;
			_head->_prev = newNode;
			newNode->_prev = _head;
			_head->_next = newNode;*/

			insert(end(), val);		// 复用 insert 尾插(insert可在pos位置之前插入数据)
										// 切记 insert 和 erase pos参数是 迭代器
		}
		// ===== 头插=====
		void push_front(const T& val)
		{
			/*Node* tail = _head->_next;
			Node* newNode = new Node(val);

			newNode->_next = tail;
			newNode->_prev = _head;
			_head->_next = newNode;
			tail->_prev = newNode;*/

			insert(begin(), val);		// 复用 insert 头插
		}

		// 实现了尾插，如果想要遍历 list 就需要 iterator迭代器
		// 而 list 存储数据并不是一块连续的物理空间，所以iterator是无法使用简单的内置类型指针实现的
		// 要实现 iterator 和 const_iterator 还要去阅读 STL-源码查看 iterator源码部分是如何实现的，再来模拟实现
		// 在源码中，迭代器是由模板类实现的，但是其模板参数有 3个
		// 为什么STL源码实现 list的迭代器 需要三个模板参数？
		//
		// 因为 list的迭代器本质上是由 类实现的, 但是如果想要实现可以针对不同数据类型的迭代器，就需要使用泛型编程
		// 又由于模板传参只能传与 实际数据类型相同的类型，因为模板参数不同就表示数据类型不同，而迭代器的实现需要用实际类型数据赋值模板参数类型数据的，如果模板参数的类型与实际数据类型不符是无法进行赋值的。所以迭代器的泛型编程的模板参数如果只有一个的话，那对于 const 和 非const 类型的数据就需要实现两个不同的类名的模板，因为只能传参实际数据类型(即，如果list数据类型为 int，模板传参就只能传int，不能传const int，因为会造成类不同)，类不同就无法实现操作
		// 所以如果泛型编程的模板参数只有一个的话，就需要分别实现操作 const 和 非const类型数据的类模板，然而这种类模板内容几乎都是相同的，重复编写就是浪费资源
		// 
		// 为什么三个模板参数就可以获得 一个模板类同时可以针对 const和非const类型数据的操控的效果呢？
		// 在之前的string和vector迭代器种，迭代器可以实现 ++、--、*等
		// 所以就需要在迭代器类中 对这些运算符进行重载，这些重载函数的返回值也无非就，T, T&, T*, const T, const T&, const T*这六种，不区分const的话也就只有三种即 T, T&, T*
		// STL源码 list迭代器的实现 使用了 3个模板参数，分别是 T(传数据类型), Ref(传类型的&), Ptr(传类型的*);
		// const 和 非const 迭代器使用时，就是有 Ref和Ptr类型是否带有 const来区分调用的
		// 即 const_iterator 可以为 __list_iterator<T, const T&, const T*>
		// 非const 的iterator 可以为 __list_iterator<T, T&, T*>
		//
		// 接下来就在 list类外 模拟实现一下iterator 类，以及 list的begin和end 函数
		// 在STL源码中， list的begin 是链表中第一个数据节点的位置而不是头结点的位置
		//				 list的end 是才是链表头节点的位置
		iterator begin()
		{
			return iterator(_head->_next);
		}
		iterator end()
		{
			return iterator(_head);
		}

		const_iterator begin() const
		{
			return const_iterator(_head->_next);
		}
		const_iterator end() const
		{
			return const_iterator(_head);
		}

		reverse_iterator rbegin()
		{
			return reverse_iterator(_head);
		}
		reverse_iterator rend()
		{
			return reverse_iterator(_head->_next);
		}

		const_reverse_iterator rbegin() const
		{
			return const_reverse_iterator(_head);
		}
		const_reverse_iterator rend() const
		{
			return const_reverse_iterator(_head->_next);
		}

		// ====== insert 插入操作, 在pos位置之前插入数据 ======
		// STL源码 中返回的是 新插入的节点的迭代器
		iterator insert(iterator pos, const T& val)
		{
			Node* newNode = new Node(val);
			Node* cur = pos._node;
			Node* prev = cur->_prev;

			newNode->_next = cur;
			newNode->_prev = prev;
			cur->_prev = newNode;
			prev->_next = newNode;

			return iterator(newNode);		// 新节点的迭代器
		}


		// ====== earse 删除节点，返回值为被删除节点的下一节点的迭代器======
		// 由于 list结构为双向带头循环链表，所以 迭代器不能指向pos
		iterator erase(iterator pos)
		{
			assert(pos != end());

			Node* cur = pos._node;
			Node* next = cur->_next;
			Node* prev = cur->_prev;

			next->_prev = prev;
			prev->_next = next;
			delete cur;				// delete pos._node 即为指定节点，因为 pos._node 是由指定节点初始化的

			return iterator(next);
		}

		// ====== 头删、尾删 直接复用 erase ======
		void pop_back()
		{
			erase(--end());
		}

		void pop_front()
		{
			erase(begin());
		}

	private:
		Node* _head;	// 成员变量：Node 指针类型的 头节点
	};
}
