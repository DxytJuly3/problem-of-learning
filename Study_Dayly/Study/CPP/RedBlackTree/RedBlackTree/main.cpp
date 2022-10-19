#include "RedBlackTree.h"

void TestRBTree1()
{
	//int a[] = { 1, 2, 3, 4, 5, 6, 7, 8 };
	int a[] = { 12,4,25,34,545,63,57,4678,4,256,5678,437,6478,35,756,78,243,635,68,64,4257,6478,35,7 };
	
	RBTree<int> t;
	for (auto e : a) {
		t.insert(e);
	}

	t.InOrder();
	cout << "ÊÇ·ñÊÇºìºÚÊ÷£¿  " << t.isRedBlackTree() << endl;
	t.levelOrder();
	t.Height();
}

void TestRBTree2()
{
	const size_t N = 1024;
	vector<int> v;
	v.reserve(N);
	srand(time(0));
	for (size_t i = 0; i < N; ++i)
	{
		v.push_back(rand());
		//v.push_back(i);
	}

	RBTree<int> t;
	for (auto e : v)
	{
		cout << e << " ";
		t.insert(e);
	}

	//t.levelOrder();
	cout << endl;
	cout << "ÊÇ·ñÊÇºìºÚÊ÷£¿  " << t.isRedBlackTree() << endl;
	t.Height();

	//t.InOrder();
}

int main() {
	TestRBTree1();
	TestRBTree2();

	return 0;
}