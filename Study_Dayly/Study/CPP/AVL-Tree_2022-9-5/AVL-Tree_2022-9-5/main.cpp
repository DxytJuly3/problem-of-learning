#include "AVL-Tree.h"

void AVLtest() {
	const size_t N = 1024*1024*10;
	vector<int> v;
	v.reserve(N);
	srand(time(0));
	for (size_t i = 0; i < N; ++i)
	{
		//v.push_back(rand());
		v.push_back(i);
	}

	AVLTree<int> t;
	for (auto e : v)
	{
		t.insert(e);
	}

//	t.levelOrder();
	//cout << endl;
	cout << "是否平衡?" << t.isBalanceTree() << endl;
	cout << "高度:" << t.treeHeight() << endl;

}

int main() {
	AVLtest();

	return 0;
}