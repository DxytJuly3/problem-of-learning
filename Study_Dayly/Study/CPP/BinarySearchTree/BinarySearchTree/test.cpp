#include "BinarySearchTree.h"

// ≤‚ ‘ ∑«µ›πÈ≤Ÿ◊˜
void BSTreeTest1()
{
	BSTree<int> bst;

	bst.Insert(5);
	bst.Insert(7);
	bst.Insert(2);
	bst.Insert(8);
	bst.Insert(3);
	bst.Insert(1);
	bst.Insert(4);

	bst.InOrder();

	bst.Erase(7);
	bst.InOrder();
	bst.Erase(6);
	bst.InOrder();
	bst.Erase(3);
	bst.InOrder();
	bst.Erase(1);
	bst.InOrder();
	bst.Erase(8);
	bst.InOrder();
}

// ≤‚ ‘ µ›πÈ≤Ÿ◊˜
void BSTreeTest2()
{
	BSTree<int> bst;

	bst.InsertR(5);
	bst.InsertR(7);
	bst.InsertR(2);
	bst.InsertR(8);
	bst.InsertR(3);
	bst.InsertR(1);
	bst.InsertR(4);

	bst.InOrder();

	bst.EraseR(7);
	bst.InOrder();
	bst.EraseR(6);
	bst.InOrder();
	bst.EraseR(3);
	bst.InOrder();
	bst.EraseR(1);
	bst.InOrder();
	bst.EraseR(8);
	bst.InOrder();
}

// ≤‚ ‘ øΩ±¥ππ‘Ï  ∏≥÷µ÷ÿ‘ÿ
void BSTreeTest3()
{
	BSTree<int> bst1;

	bst1.InsertR(5);
	bst1.InsertR(7);
	bst1.InsertR(2);
	bst1.InsertR(8);
	bst1.InsertR(3);
	bst1.InsertR(1);
	bst1.InsertR(4);
	bst1.InOrder();

	BSTree<int> bst2(bst1);
	bst2.InOrder();

	BSTree<int> bst3;
	bst3 = bst2;
	bst3.InOrder();
}

int main()
{
	BSTreeTest3();

	return 0;
}