#include <iostream>

int add1(int a, int b) {
    return a + b;
}
inline int add2(int a, int b) {
    return a + b;
}

int main() {
    int a = 1, b = 2;
    add1(a, b);
    add2(a, b);
    
    return 0;
}
