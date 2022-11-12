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

void BucketTest() {
	Bucket::HashTable<int, int> ht;
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

	Bucket::HashTable<string, int> strHT;
	strHT.insert(make_pair("ÂìÒÏ", 1));
	strHT.insert(make_pair("ÒÏÂì", 1));
	strHT.insert(make_pair("mayi", 1));
	strHT.insert(make_pair("amyi", 1));
	strHT.insert(make_pair("iyam", 1));
	strHT.insert(make_pair("Æ»¹û", 1));
	strHT.insert(make_pair("¹ûÆ»", 1));
	strHT.insert(make_pair("apple", 1));
	strHT.insert(make_pair("pingguo", 1));
	strHT.insert(make_pair("guoping", 1));
	strHT.insert(make_pair("elppa", 1));
	strHT.insert(make_pair("July", 1));
	strHT.insert(make_pair("yluJ", 1));
	strHT.insert(make_pair("Î÷¹Ï", 1));
	strHT.insert(make_pair("¹ÏÎ÷", 1));
	strHT.insert(make_pair("xigua", 1));
	strHT.insert(make_pair("guaxi", 1));
	strHT.insert(make_pair("Å£Âí", 1));
	strHT.insert(make_pair("ÂíÅ£", 1));
	strHT.insert(make_pair("maniu", 1));
	strHT.insert(make_pair("niuma", 1));
	strHT.insert(make_pair("uinam", 1));
}

int main() {
	BucketTest();

	return 0;
}