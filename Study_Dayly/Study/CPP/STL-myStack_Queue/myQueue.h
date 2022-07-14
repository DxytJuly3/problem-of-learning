#include "STL-myStack_Queue.h"

namespace July
{
	// 与stack相似，STL源码中，queue的实现也是用适配器来实现的
	//
	// queue 队列
	// 是一个先进先出的数据结构，类似排队只能尾插头删，可取队头和对位的元素
	template<class T, class Container = deque<T>>
	class queue
	{
	public:
		// 同样的道理，queue不需要显式定义构造函数
		//
		// 入队 --> 尾插
		void push(const T& val)
		{
			_con.push_back(val);
		}
		// 出队 --> 头删
		void pop()
		{
			_con.pop_front();
		}
		// 取队头元素
		const T& front()
		{
			return _con.front();
		}
		// 取队尾元素
		const T& back()
		{
			return _con.back();
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
}
