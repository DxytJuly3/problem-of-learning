#include "sort.hpp"
#include <vector>

void print(const std::vector<int>& v) {
	for (const auto& e : v) {
		std::cout << e << " ";
	}
	std::cout << std::endl;
}

void test() {
	std::vector<int> v = {1, 23748, 574, 35421, 4253, 67456, 76, 754, 321, 123, 34, 77, 78765324, 31, 2, 35, 787, 6875, 645342, 31, 23};

	// insertSort(v);
	// selectSort1(v);
	// bubbleSort(v);
	// shellSort(v);
	selectSort2(v);

	print(v);
}

int main() {
	test();

	return 0;
}
