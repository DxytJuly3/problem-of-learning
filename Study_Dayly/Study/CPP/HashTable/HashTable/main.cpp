#include <iostream>
#include "HashTable.h"
using std::cout;
using std::endl;
using std::cin;
using std::make_pair;

void HashTableTest() {
	July::HashTable<int, int> ht;
	ht.insert(make_pair(1, 1));
	ht.insert(make_pair(5, 1));
	ht.insert(make_pair(8, 1));
	ht.insert(make_pair(2, 1));
	ht.insert(make_pair(12, 1));
	ht.insert(make_pair(25, 1));
	ht.insert(make_pair(26, 1));
	ht.insert(make_pair(27, 1));
	ht.insert(make_pair(28, 1));
	ht.insert(make_pair(29, 1));
	ht.insert(make_pair(21, 1));
	ht.insert(make_pair(23, 1));
	ht.insert(make_pair(24, 1));
}

int main() {
	HashTableTest();

	return 0;
}