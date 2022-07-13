#include <iostream>
#include <list>
using namespace std;

int main()
{
	int array[] = { 1, 2, 3, 4, 0, 5, 6, 7, 8, 9 };
	int n = sizeof(array) / sizeof(int);
	list<int> mylist(array, array + n);
	auto it = mylist.begin();
	while (it != mylist.end())
	{
		if (*it != 0)
			cout << *it << " ";
		else
			it = mylist.erase(it);
		++it;
	}

	return 0;
}
