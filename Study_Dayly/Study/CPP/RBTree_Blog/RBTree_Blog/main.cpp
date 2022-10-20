#include "RBTree_Blog.h"

void TestRBTree1()
{
	const size_t N = 1024 * 1024;
	vector<int> v;
	v.reserve(N);
	srand(time(0));
	for (size_t i = 0; i < N; ++i)
	{
		v.push_back(rand());
	}

	RBTree<int> t;
	for (auto e : v)
	{
		t.insert(e);
	}
	
	t.treeHeight();
	cout << "´ËÊ÷ÊÇ·ñÎªºìºÚÊ÷£º " << t.isRBTree() << endl;
}


int main() {
	TestRBTree1();

	return 0;
}