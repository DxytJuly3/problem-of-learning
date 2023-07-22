#include <iostream>

int add(int a, int b) {
	return a + b;
}

double add(double a, double b) {
	return a + b;
}

int main() {
	int a = 1, b = 2;
	double c = 1.1, d = 2.2;

	add(a, b);
	add(c, d);

	return 0;
}
