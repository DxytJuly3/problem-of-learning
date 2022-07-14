#include "STL-myStack_Queue.h"
#include "myPriority_Queue.h"
#include "myQueue.h"
#include "myStack.h"

namespace July
{
	void test_stack()
	{
		//July::stack<int> s;
		July::stack<int, vector<int>> s;
		//July::stack<int, list<int>> s;
		//July::stack<int, string> s;

		s.push(1);
		s.push(2);
		s.push(3);
		s.push(4);
		s.push(300);

		while (!s.empty())
		{
			cout << s.top() << " ";
			s.pop();
		}
		cout << endl;
	}

	void test_queue()
	{
		//queue<int> q;
		July::queue<int, list<int>> q;
		//queue<int, vector<int>> q; // 不行

		q.push(1);
		q.push(2);
		q.push(3);
		q.push(4);

		while (!q.empty())
		{
			cout << q.front() << " ";
			q.pop();
		}
		cout << endl;
	}

	void test_priority_queue()
	{
		//priority_queue<int> pq;		
		July::priority_queue<int, vector<int>, greater<int>> pq;

		pq.push(2);
		pq.push(5);
		pq.push(1);
		pq.push(6);
		pq.push(8);

		while (!pq.empty())
		{
			cout << pq.top() << " ";
			pq.pop();
		}
		cout << endl;
	}
}

int main()
{
	July::test_stack();
	July::test_queue();
	July::test_priority_queue();

	return 0;
}
