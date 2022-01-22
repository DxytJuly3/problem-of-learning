#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>

int func(int x)
{
    int count = 0;
    while (x)
    {
        count++;
        x = x & (x - 1);//ÓëÔËËã
    }
    return count;
}

int main()
{
    /*int count = 0;
    int x = -1;
    while (x)
    {
        count++;
        x = x >> 1;
    }
    printf("%d", count);*/
    
    int a = 1, b = 2, m = 0, n = 0, k;
    k = (n = b < a) && (m = a);
    printf("%d,%d\n", k, m);
     
    return 0;
}