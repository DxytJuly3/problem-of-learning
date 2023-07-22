#include <stdio.h>

struct test {
	char c;
	int a;
	char d;
};
#pragma pack(push, 1)
struct MyStruct {
    char c;
    int i;
    short s;
};
#pragma pack(pop)

int main() {
    printf("Default alignment: %zu\n", sizeof(struct MyStruct) - sizeof(char) - sizeof(int) - sizeof(short));
    return 0;
}

//int main() {
//
//	printf("%lu\n", sizeof(struct test));
//
//	return 0;
//}
