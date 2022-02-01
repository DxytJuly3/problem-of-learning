#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
int fun(unsigned int x)
{
    int n = 0;
    while (x + 1)
    {
        n++;
        x = x | (x + 1);
        int y = x + 1;
    }
    return n;
}

int main()
{
    /*unsigned int x = 2014;
    int ret = fun(x);
    printf("%d\n", ret);*/
    int a[8] = { 1,2,3,4,5,6,7,8 };
    printf("%d", *(&a[0]+1));

	return 0;
}