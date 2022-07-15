#include <iostream>
#include <cassert>

namespace July
{
	template<class Iterator, class Ref, class Ptr>
	struct reverseIterator
	{
		typedef reverseIterator<Iterator, Ref, Ptr> Self;

		Iterator _it;

		// ���캯��
		// ����������ĳ�Ա��������������������캯�������ڶ���ʵ����ʱ���õ�
		// ��������������� ��� rbegin() �� rend() �У����캯���Ĵ���Ҳ��
		// ��Ҫ������������ĳ�Ա������ʼ��Ϊ ����ö������Ӧ�����������
		reverseIterator(Iterator it)
			:_it(it)
		{}

		// * ����������
		// ������ *�����÷�������������ṩ�Է���ֵ���޸ģ�����Ҫ��&����
		// ���ص��� ��ǰλ�������������ǰһλ�Ľ����ã�ʵ�ʷ��ص���ʲô��Ҫ�� �����������ʵ��
		// Ϊʲô�������������ǰһλ��
		// �� rbegin() ��ȡ�ķ��������Ϊ������ȡ�������һ��Ԫ�ص���һλ�����������������ݷ�Χ�ڣ����ֱ�ӶԵ�ǰλ�õ���������������ã��ᷢ������ǰһλ���������������ݷ�Χ
		Ref operator*()
		{
			Iterator tmp(_it);

			return *(--tmp);
		}

		// -> ����������
		// -> һ������ָ����������Է���Ӧ����ָ��
		// ���ص�Ҳ�� ��ǰλ�������������Ǩ��λ�ý����õ�ȡ��ַ
		Ptr operator->()
		{
			return &(operator*()); 		// ���� *����
		}
		// ǰ��++����
		// ǰ�� ++\-- ��ֱ�Ӹı�ԭֵ���Բ���Ҫ�������ҷ��صĶ����޸ĺ�ĵ�����
		// ���� ++\-- �����޸�ǰ�ĵ�������������Ҫ�����޸�ǰ�ĵ�����
		Self& operator++()
		{
			--_it; 			// ��������� ++��ʵ�� --

			return *this;
		}
		// ����++
		Self operator++(int)
		{
			Self tmp(_it); 		// �����޸�ǰ�ĵ�����
			--_it;

			return tmp;  			// ������ʱ�������� ��ֵ����
		}
		// ǰ��--
		Self& operator--()
		{
			++_it; 			// ��������� --��ʵ�� ++

			return *this;
		}
		// ����--
		Self operator--(int)
		{
			Self tmp(_it);
			++_it;

			return tmp;
		}

		// != �� == ������
		bool operator!=(const Self& sit)
		{
			return _it != sit._it;
		}
		bool operator==(const Self& sit)
		{
			return _it == sit._it;
		}
	};

	// ģ��STL-List�е� __list_node��
	template<class T>
	struct list_node
	{
		list_node<T>* _next;		// C++ ����������ֱ��ʹ�ñ�����
		list_node<T>* _prev;
		T _val;

		list_node(const T& val = T())	// ���캯��
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
		// self ���������
		// self���ڵ��������� typedef�ģ�����self ��ʵ���Ѿ�֪���������͵� __list_iterator ��
		// 1. ���� self������Ϊ ++��-- ���غ����ķ���ֵ���ͣ���Ϊ ++��-- Ӧ�÷��� ���������� ������
		// 2. self �� ++��-- ���غ����ڣ�ʵ���� __list_iterator��� ����

		Node* _node;		// __list_iterator �ĳ�Ա��������ʵ���� Node* ���͵ı���

		__list_iterator(Node* node)
			:_node(node)
		{}
		// __list_iterator ���캯���Ĳ���ΪNode*��ʵ��ʹ�õ�iterator ��Ϊ �ɴ�������ݽڵ��ַ ����Ķ���

		// �����������ض��У�++��--��*(������)��->��!=��==
		self& operator++()	// ǰ��++��������������
		{
			_node = _node->_next;

			return *this;
		}
		self operator++(int)
		{
			self tmp(*this);	// self�����ã�ʹ��self ʹ�ô˵�������Ա ʵ�������������󣬼����������
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
	// ��STL ����List��Դ��
	// �����ҵ�list���е� ��Ա����ֻ��һ�� link_type node;
	// (link_type ��list_node* ��typedef, ��list_node* �� __list_node<T>��typedef)
	// __list_node<T>��һ��ģ����  (������ģ��ʵ��)
	// ��ģ���� List�е�һ���ڵ�ĵ����ͣ��� ӵ������ָ���һ������
	//
	// ����ֻ�����г�Ա������ʵ�����ݣ������ܹ���ȫȷ�� ���е� List������ʲô�ṹ������
	// ���ԣ���Ҫ�鿴���� List�Ĺ��캯������ʵ�������Ķ����ʼ״̬�����нṹ���ж�
	// �ҵ� ���캯��List() ���Կ��� ���������һ������ empty_initialize();
	// �ڿ��� empty_initialize();�����������ǣ����ڴ���ж���һ��node�ڵ㣬����node->next �� node->prev ָ��node
	// ���Կ��������е� List��ʵ�� ˫���ͷѭ���ṹ�� ����
	// ��Ϊ List��ʵ��������ĳ�ʼ״̬���� ֻ��ͷ�ڵ�û�����ݵ� ˫��ѭ������
	// ����Ϳ��Ը��ݿ��е�Դ������ ���Լ�ģ��ʵ��List����ʵģ��ʵ�ֵĲ�����֮ǰ�� ˫���ͷѭ����������
	template<class T>
	class list
	{
		typedef list_node<T> Node;	// ���ڵ���� typedefΪ Node �����ױ�ﺬ��
	public:
		typedef __list_iterator<T, T&, T*> iterator;					// ��const������
		typedef __list_iterator<T, const T&, const T*> const_iterator;	// const������

		typedef reverseIterator<iterator, T&, T*> reverse_iterator;		// �� const���������
		typedef reverseIterator<const_iterator, const T&, const T*> const_reverse_iterator;		//  const���������

		// ����List�ṹ�Ǵ�ͷ����˫��ѭ������ͷ�ڵ㲻��Ҫ�����ݣ����Թ��캯�����ô���
		list()
		{
			/*_head = new Node();			// _node ΪNode���ʵ���������ָ�룬new ����Node���캯��ʵ�������� �������ַ����_node
			_head->_next = _head;
			_head->_prev = _head;*/

			empty_init();
		}

		void empty_init()				// �˺������������ڣ�����ʵ����ʱ�Գ�Ա������ʼ������Ϊ��������õ��Ĵ����϶࣬����д�ɺ���
		{
			_head = new Node();
			_head->_next = _head;
			_head->_prev = _head;
		}

		//===== list ��ͳд���Ŀ������캯��=====
		/*list(const list<T>& lt)
		{
			empty_init();			// �ȳ�ʼ����Ա����

			for(auto VAL : lt)		// ʹ�õ��������� lt ��β������Ҫ����ʵ�����Ķ�����
				push_back(VAL);
		}
		// ��ʵlist �������캯���Ĵ�ͳд��(���������ɵ�Ĭ�Ͽ������첻��)���Ƚϼ�����
		*/

		// ===== STLԴ����list�� ͬ��ʵ���˵��������䷽���Ĺ��캯�� =====
		template <class InputIterator>
		list(InputIterator first, InputIterator last)
		{
			empty_init();

			while (first != last)		// ע�⣬��list ����ĵ������Ͳ���ʹ�� > < <= >= �����߼��Ƚ���
			{							// ֻ���� == �� != 
				push_back(*first);		// ���� list�������ĳ�Ա�����ǽڵ����͵ģ�ֱ�ӽ����þ���һ���ڵ�
				++first;
			}
		}

		// list �������캯�����ִ�д��
		// list ��������͸�ֵ���ִ�д�������������м����ֱ�ӽ�������
		// ====== ��ʵ��һ��ר����list��swap����=====
		void swap(list<T>& lt)
		{
			std::swap(_head, lt._head);			// ��ͷ������������ݽ���ֻ����ͷ�ڵ���Ѿ�������������ݵĽ���
		}
		//====== ���������ִ�д�� ======
		list(const list<T>& lt)
		{
			empty_init();

			list<T> TMP(lt.begin(), lt.end());
			swap(TMP);
		}

		// ====== '=' ��ֵ���غ��� �ִ�д��
		list<T> operator=(list<T> lt)
		{
			swap(lt);

			return *this;
		}

		// ��������
		// ����������������Դ�ĺ�������list�о�����Ҫ��ÿ���ڵ�������������ֻ��һ��һ������,������ʵ������֮ǰ����ʵ��һ��clear() �������������ݽڵ�
		void clear()
		{
			iterator ltIt = begin();		// ÿ�����ݽڵ㶼ֻ�� list_node��ʵ�����Ķ���û�ж�̬���ٿռ�
			while (ltIt != end())			// �������ݽڵ㿪ʼeraseÿ���ڵ� ֱ���������ص�ͷ���
			{
				ltIt = erase(ltIt);
				// erase��֮�����õ�����++, �����õ���������erase�ķ���ֵ, ����Ϊ erase�ķ���ֵ����ɾ���ڵ����һ�ڵ�ĵ�����
				// �������������Ч���� list�е�����ʧЧ������
			}
		}

		// ====== �������� ======
		~list()
		{
			clear();				// ��ֱ��clear�������ݽڵ�
			delete _head;			// Ȼ��delete�ͷ�ͷ�ڵ�ռ�, ͷ�ڵ�ռ��� new������
			_head = nullptr;		// ��Ȼ���ٽ�ͷ�ڵ��ÿ�

		}
		// ===== β��=====
		// ˫���ͷѭ������β����ʵ���� ��ͷ�ڵ��prev����
		void push_back(const T& val)
		{
			/*Node* tail = _head->_prev;	// ��¼ͷ���� prev
			Node* newNode = new Node(val);

			newNode->_next = tail;
			_head->_prev = newNode;
			newNode->_prev = _head;
			_head->_next = newNode;*/

			insert(end(), val);		// ���� insert β��(insert����posλ��֮ǰ��������)
										// �м� insert �� erase pos������ ������
		}
		// ===== ͷ��=====
		void push_front(const T& val)
		{
			/*Node* tail = _head->_next;
			Node* newNode = new Node(val);

			newNode->_next = tail;
			newNode->_prev = _head;
			_head->_next = newNode;
			tail->_prev = newNode;*/

			insert(begin(), val);		// ���� insert ͷ��
		}

		// ʵ����β�壬�����Ҫ���� list ����Ҫ iterator������
		// �� list �洢���ݲ�����һ������������ռ䣬����iterator���޷�ʹ�ü򵥵���������ָ��ʵ�ֵ�
		// Ҫʵ�� iterator �� const_iterator ��Ҫȥ�Ķ� STL-Դ��鿴 iteratorԴ�벿�������ʵ�ֵģ�����ģ��ʵ��
		// ��Դ���У�����������ģ����ʵ�ֵģ�������ģ������� 3��
		// ΪʲôSTLԴ��ʵ�� list�ĵ����� ��Ҫ����ģ�������
		//
		// ��Ϊ list�ĵ��������������� ��ʵ�ֵ�, ���������Ҫʵ�ֿ�����Բ�ͬ�������͵ĵ�����������Ҫʹ�÷��ͱ��
		// ������ģ�崫��ֻ�ܴ��� ʵ������������ͬ�����ͣ���Ϊģ�������ͬ�ͱ�ʾ�������Ͳ�ͬ������������ʵ����Ҫ��ʵ���������ݸ�ֵģ������������ݵģ����ģ�������������ʵ���������Ͳ������޷����и�ֵ�ġ����Ե������ķ��ͱ�̵�ģ��������ֻ��һ���Ļ����Ƕ��� const �� ��const ���͵����ݾ���Ҫʵ��������ͬ��������ģ�壬��Ϊֻ�ܴ���ʵ����������(�������list��������Ϊ int��ģ�崫�ξ�ֻ�ܴ�int�����ܴ�const int����Ϊ������಻ͬ)���಻ͬ���޷�ʵ�ֲ���
		// ����������ͱ�̵�ģ�����ֻ��һ���Ļ�������Ҫ�ֱ�ʵ�ֲ��� const �� ��const�������ݵ���ģ�壬Ȼ��������ģ�����ݼ���������ͬ�ģ��ظ���д�����˷���Դ
		// 
		// Ϊʲô����ģ������Ϳ��Ի�� һ��ģ����ͬʱ������� const�ͷ�const�������ݵĲٿص�Ч���أ�
		// ��֮ǰ��string��vector�������֣�����������ʵ�� ++��--��*��
		// ���Ծ���Ҫ�ڵ��������� ����Щ������������أ���Щ���غ����ķ���ֵҲ�޷Ǿͣ�T, T&, T*, const T, const T&, const T*�����֣�������const�Ļ�Ҳ��ֻ�����ּ� T, T&, T*
		// STLԴ�� list��������ʵ�� ʹ���� 3��ģ��������ֱ��� T(����������), Ref(�����͵�&), Ptr(�����͵�*);
		// const �� ��const ������ʹ��ʱ�������� Ref��Ptr�����Ƿ���� const�����ֵ��õ�
		// �� const_iterator ����Ϊ __list_iterator<T, const T&, const T*>
		// ��const ��iterator ����Ϊ __list_iterator<T, T&, T*>
		//
		// ���������� list���� ģ��ʵ��һ��iterator �࣬�Լ� list��begin��end ����
		// ��STLԴ���У� list��begin �������е�һ�����ݽڵ��λ�ö�����ͷ����λ��
		//				 list��end �ǲ�������ͷ�ڵ��λ��
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

		// ====== insert �������, ��posλ��֮ǰ�������� ======
		// STLԴ�� �з��ص��� �²���Ľڵ�ĵ�����
		iterator insert(iterator pos, const T& val)
		{
			Node* newNode = new Node(val);
			Node* cur = pos._node;
			Node* prev = cur->_prev;

			newNode->_next = cur;
			newNode->_prev = prev;
			cur->_prev = newNode;
			prev->_next = newNode;

			return iterator(newNode);		// �½ڵ�ĵ�����
		}


		// ====== earse ɾ���ڵ㣬����ֵΪ��ɾ���ڵ����һ�ڵ�ĵ�����======
		// ���� list�ṹΪ˫���ͷѭ���������� ����������ָ��pos
		iterator erase(iterator pos)
		{
			assert(pos != end());

			Node* cur = pos._node;
			Node* next = cur->_next;
			Node* prev = cur->_prev;

			next->_prev = prev;
			prev->_next = next;
			delete cur;				// delete pos._node ��Ϊָ���ڵ㣬��Ϊ pos._node ����ָ���ڵ��ʼ����

			return iterator(next);
		}

		// ====== ͷɾ��βɾ ֱ�Ӹ��� erase ======
		void pop_back()
		{
			erase(--end());
		}

		void pop_front()
		{
			erase(begin());
		}

	private:
		Node* _head;	// ��Ա������Node ָ�����͵� ͷ�ڵ�
	};
}
