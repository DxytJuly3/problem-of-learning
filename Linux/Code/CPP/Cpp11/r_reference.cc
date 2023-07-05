#include <iostream>

using std::cout;
using std::endl;

int main() {
	int x = 1, y = 2;
	int &&a = 1;
	a = 2;
	int &&b = 1;
	int &&c = x + y;
	c = 4;

	cout << a << endl;
	cout << b << endl;
	cout << c << endl;

	// 这个是编译不通过的
    // int &g = 10;
    
    // 这个是可以编译通过的
	const int &g = 10;
	
    int m = 1;
   //	int &&n = m;

	return 0;
}
