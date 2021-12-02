//不使用累计乘法的基础上，通过移位运算（<<）实现2的n次方的计算。
#include <stdio.h>
 
int main()
{
    int n = 0;
    scanf("%d", &n);
    printf("%d", 2 << n-1);
     
    return 0;
}