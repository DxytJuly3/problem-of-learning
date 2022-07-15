#include <iostream>
#include <list>
#include <deque>
#include <vector>
#include <stack>
#include <queue>
using namespace std;

////typedef vector<int> Container;
//typedef deque<int> Container;
////typedef list<int> Container;
//int main()
//{
//	Container cont = { 1, 2, 3, 4, 5 };
//	Container::iterator iter, tempIt;
//
//	for (iter = cont.begin(); iter != cont.end();)
//	{
//		tempIt = iter;
//
//		++iter;
//		cont.erase(tempIt);
//	}
//
//	return 0;
//}

//int main()
//{
//	stack<char> S;
//	char x, y;
//	x = 'n'; y = 'g';
//	S.push(x); S.push('i'); S.push(y);
//	S.pop(); S.push('r'); S.push('t'); S.push(x);
//	S.pop(); S.push('s');
//	while (!S.empty())
//	{
//		x = S.top();
//		S.pop();
//		cout << x;
//	};
//	cout << y;
//
//	return 0;
//}

//int main()
//{
//	// g r t n s g
//	queue<char> Q;
//	char x, y;
//	x = 'n'; y = 'g';
//	Q.push(x); Q.push('i'); Q.push(y);
//	Q.pop(); Q.push('r'); Q.push('t'); Q.push(x);
//	Q.pop(); Q.push('s');
//	while (!Q.empty())
//	{
//		x = Q.front();
//		Q.pop();
//		cout << x;
//	};
//	cout << y;
//	
//	return 0;
//}

/*
	1

   2 3

 4 5 6 7

	queue.push(tree.root)
	while(true)
	{
		node = queue.pop()
		output(node.value)//输出节点对应数字
		if(null == node)
			break
	}
	for(child_node in node.children)
	queue.push(child_node)
*/

int main()
{
	priority_queue<int> a;
	priority_queue<int, vector<int>, greater<int> > c;
	priority_queue<string> b;

	for (int i = 0; i < 5; i++)
	{
		a.push(i);		
		//	  4			3		  2
		//	 3 1	   2 1		 0 1 
		//  0 2       0
		c.push(i);
		//	  0		    1		  2		   
		//	 1 2	   4 2		 4 3
		//  3 4		  3
		// a 建大堆 c 建小堆
	}

	while (!a.empty())
	{
		cout << a.top() << ' ';
		a.pop();	// 4 3 2 1 0
	}
	cout << endl;

	while (!c.empty())
	{
		cout << c.top() << ' ';		// 0 1 2 3 4
 		c.pop();
	}
	cout << endl;

	// b 建大堆
	b.push("abc");			//		 cbd
	b.push("abcd");			//   abc	abcd
	b.push("cbd");			// 

	while (!b.empty())
	{
		cout << b.top() << ' ';		// cbd	abcd abc
		b.pop();
	}
	cout << endl;

	return 0;
}