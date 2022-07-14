#include "STL-myStack_Queue.h"
#include <functional>

// 队列 Queue 还有一种特殊的队列，叫做优先级队列 priority_queue
// 而优先级队列并不像 queue一样 是线性存放数据的，优先级队列的底层实现其实是 堆
// 所以 实现优先级队列所使用的适配器 合适的是vector，STL源码也是使用vector<T> 作为适配器
//
// 而 优先级队列的底层由堆实现，其实是由大根堆 或 小根堆实现的，这样才能体现 "优先级"

namespace July
{
	// 先自己实现 大根堆的优先级队列
	/*template<class T, class Container = vector<T>>
	class priority_queue
	{
	public:
		// 无需显式定义构造函数
		
		// 向上调整建大根堆
		void AdjustUP(size_t child)
		{
			size_t parent = (child - 1) / 2;	// 孩子的父亲位置，是孩子位置-1 除以2，可以画图推一下

			// 既然是循环 从最后一个数据位置，向上调整，所以循环停止的条件应该是 child == 0
			while(child != 0)			// 这里是循环继续的条件
			{
				if(_con[child] > _con[parent])		// 建大根堆，所以孩子大 就与父亲交换位置
				{
					swap(_con[child], _con[parent]);
					child = parent;					// 孩子改变位置
					parent = (child - 1) / 2;		// 计算新孩子位置的父亲
				}
				else
				{
					break;			// 父亲节点不必孩子节点的数据大了，就调整结束了
				}
			}
		}
		// 入队列 尾插数据，向上调整 作大根堆
		void push(const T& val)
		{
			_con.push_back(val);

			AdjustUP(_con.size() - 1);		// 向上调整建堆，传入最后一个数据的位置
		}

		// 向下调整建堆 是用 父节点与两个孩子节点中较大的交换位置，直至结束
		void AdjustDOWN(size_t parent)
		{
			// 由于 二叉树可能没有 右孩子节点，所以只定义左孩子节点
			size_t child = parent * 2 + 1;

			// 循环调整结束的条件 应该是计算出的 child 第一次超出了范围，所以循环继续的条件应该是 child < _con.size()
			while(child < _con.size())
			{
				// 父节点 需要与左右孩子中较大的(如果存在右孩子)交换位置，所以先求出左右孩子较大的作为 child
				if(child + 1 < _con.size() && _con[child] < _con[child + 1])	// child默认为左孩子，+1即为右孩子
					++child;		// 如果右孩子存在 且右孩子大于左孩子，则child就应表示右孩子

				if(_con[parent] < _con[child])		// 建大根堆 所以 小的向下调整
				{
					swap(_con[parent], _con[child]);
					parent = child;
					child = parent * 2 + 1;
				}
				else
				{
					break;
				}
			}
		}
		
		// 出队列 头删数据，向下调整 作大根堆
		// 由于是堆，其实出队列的方法就是 将 根节点与最后一个节点交换位置，然后删除最后一个节点
		// 然后再从 根节点向下调整就可以了
		void pop()
		{
			assert(!_con.empty());

			swap(_con[0], _con[_con.size() - 1]);		// 根节点与末节点交换位置
			_con.pop_back();							// 尾删
			
			AdjustDOWN(0);								// 从根0 向下调整 建堆
		}

		// 取队头元素 即根
		const T& top()
		{
			return _con[0];
		}
		// 队列大小
		size_t size()
		{
			return _con.size();
		}
		// 判空
		bool empty()
		{
			return _con.empty();
		}

	private:
		Container _con;
	};*/

	// 至此 优先级队列的 大根堆底层已经全部实现
	// 但是 读STL源码 会发现，优先级队列的 模板参数一共有三个
	// T, Container之外，还有一个Compare
	// Compare 同样也提供了一个缺省值 less<T>
	// 这个 less<T> 其实是一个 仿函数，他只有一个成员函数，是" () "的重载函数，函数是用来比较大小的
	// 而这个 类实例化出的对象 被称为 函数对象，因为这个对象可以 想使用函数一样直接调用其成员函数比较大小
	// 即，如果有一个 less<T> les; les对象，则可以直接 les(x,y) 来比较x 和 y的大小
	//
	// 而 优先级队列提供 仿函数为模板参数，是想通过 改变仿函数传参，来改变这个优先级队列 建的堆
	// Compare 传 less<T> 建大堆，Compare 传 greater<T> 就建小堆
	// 即 优先级队列中 向下向上调整算法中对比 父亲与孩子大小时 使用的是 Compare 对象，即函数对象
	// 下面就来实现一下 使用仿函数的优先级队列	
	// 其实 除了 调整函数中 对比方式变了 其他没有什么差别	
	template<class T>
	struct less
	{
		bool operator()(const T& x, const T& y) const
		{
			return x < y;
		}
	};
	
	template<class T>
	struct greater
	{
		bool operator()(const T& x, const T& y) const
		{
			return x > y;
		}
	};
	
	template<class T, class Container = vector<T>, class Compare = less<T>>
	class priority_queue
	{
	public:
		// 无需显式定义构造函数
		
		// 向上调整建大根堆
		void AdjustUP(size_t child)
		{
			Compare cmp;						// 实例化 函数对象
			size_t parent = (child - 1) / 2;	// 孩子的父亲位置，是孩子位置-1 除以2，可以画图推一下

			// 既然是循环 从最后一个数据位置，向上调整，所以循环停止的条件应该是 child == 0
			while(child != 0)			// 这里是循环继续的条件
			{
				//if(_con[child] > _con[parent])		// 建大根堆，所以孩子大 就与父亲交换位置
				if(cmp(_con[parent], _con[child]))
				{
					swap(_con[child], _con[parent]);
					child = parent;					// 孩子改变位置
					parent = (child - 1) / 2;		// 计算新孩子位置的父亲
				}
				else
				{
					break;			// 父亲节点不必孩子节点的数据大了，就调整结束了
				}
			}
		}
		// 入队列 尾插数据，向上调整 作大根堆
		void push(const T& val)
		{
			_con.push_back(val);

			AdjustUP(_con.size() - 1);		// 向上调整建堆，传入最后一个数据的位置
		}

		// 向下调整建堆 是用 父节点与两个孩子节点中较大的交换位置，直至结束
		void AdjustDOWN(size_t parent)
		{
			Compare cmp;

			// 由于 二叉树可能没有 右孩子节点，所以只定义左孩子节点
			size_t child = parent * 2 + 1;

			// 循环调整结束的条件 应该是计算出的 child 第一次超出了范围，所以循环继续的条件应该是 child < _con.size()
			while(child < _con.size())
			{
				// 父节点 需要与左右孩子中较大的(如果存在右孩子)交换位置，所以先求出左右孩子较大的作为 child
				//if(child + 1 < _con.size() && _con[child] < _con[child + 1])	// child默认为左孩子，+1即为右孩子
				if(child + 1 < _con.size() && cmp(_con[child], _con[child + 1]))
					++child;		// 如果右孩子存在 且右孩子大于左孩子，则child就应表示右孩子

				//if(_con[parent] < _con[child])		// 建大根堆 所以 小的向下调整
				if(cmp(_con[parent], _con[child]))		// 建大根堆 所以 小的向下调整
				{
					swap(_con[parent], _con[child]);
					parent = child;
					child = parent * 2 + 1;
				}
				else
				{
					break;
				}
			}
		}
		
		// 出队列 头删数据，向下调整 作大根堆
		// 由于是堆，其实出队列的方法就是 将 根节点与最后一个节点交换位置，然后删除最后一个节点
		// 然后再从 根节点向下调整就可以了
		void pop()
		{
			assert(!_con.empty());

			swap(_con[0], _con[_con.size() - 1]);		// 根节点与末节点交换位置
			_con.pop_back();							// 尾删
			
			AdjustDOWN(0);								// 从根0 向下调整 建堆
		}

		// 取队头元素 即根
		const T& top()
		{
			return _con[0];
		}
		// 队列大小
		size_t size()
		{
			return _con.size();
		}
		// 判空
		bool empty()
		{
			return _con.empty();
		}

	private:
		Container _con;
	};

	// 带有 仿函数模板参数的优先级队列，改变模板参数就可以改变 建堆方式
}
