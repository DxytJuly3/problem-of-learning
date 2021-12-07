//两数异或，后求异或后的数二进制位有多少1 
#include <stdio.h>
//求两整数二进制位 不同的个数
int main()
{
    int a = 0;
    int b = 0;
    int c = 0;
    int count = 0;
    scanf("%d%d", &a, &b);
    c = a ^ b;    // 异或符（二进制位 相同为 0， 相异为1）while (c)
    {
        count++;
        c = c & (c - 1);    //& 按位与，同 1 为 1，
    }
    printf("%d", count);
    
    return 0;
}