#include <iostream>
#include "unordered_map.h"
#include "unordered_set.h"
using std::make_pair;

void myUnorderTest() {
	July::unordered_map<string, int> fruitTable;
	July::unordered_set<string> table;

	fruitTable.insert(make_pair("苹果", 1));
	fruitTable.insert(make_pair("果苹", 1));
	fruitTable.insert(make_pair("pingguo", 1));
	fruitTable.insert(make_pair("guoping", 1));
	fruitTable.insert(make_pair("apple", 1));
	fruitTable.insert(make_pair("elppa", 1));
	fruitTable.insert(make_pair("桃子", 1));
	fruitTable.insert(make_pair("子桃", 1));
	fruitTable.insert(make_pair("taozi", 1));
	fruitTable.insert(make_pair("zitao", 1));
	fruitTable.insert(make_pair("peach", 1));
	fruitTable.insert(make_pair("hcaep", 1));
	fruitTable.insert(make_pair("水果", 1));

	table.insert("我套死你猴子");
	table.insert("子猴你死套我");
	table.insert("wotaosinihouzi");
	table.insert("izuohinisoatow");
	table.insert("碎碎平安");
	table.insert("岁岁平安");
	table.insert("平安碎碎");
	table.insert("平安岁岁");
	table.insert("pingansuisui");
	table.insert("suisuipingan");
	table.insert("iusiusnagnip");
	table.insert("嫩娘了个头啊");
	table.insert("啊头个了娘嫩");
	table.insert("nennianglegetoua");
}

int main() {
	myUnorderTest();

	return 0;
}