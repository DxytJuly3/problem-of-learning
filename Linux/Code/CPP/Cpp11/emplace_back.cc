#include <iostream>
#include <iterator>
#include <utility>
#include <vector>
#include <string>

using std::pair;
using std::make_pair;
using std::cout;
using std::endl;

int main() {
	std::vector<pair<int, std::string>> arr;
    arr.emplace_back(11, "十一");
    arr.emplace_back(20, "二十");
    arr.emplace_back(make_pair(30, "三十"));
    arr.push_back(make_pair(40, "四十"));
    arr.push_back({ 50, "五十" });
    
    for (auto e : arr) {
		cout << e.first << ":" << e.second << endl;
    }

	return 0;
}
