//输入一个整数，将这个整数以字符串的形式逆序输出
//程序不考虑负数的情况，若数字含有0，则逆序形式也含有0，如输入为100，则输出为001

#include <stdio.h>

int main()
{
    int n = 0;
    scanf("%d", &n);
    if(n == 0)
    {
        printf("0");
        return 0;
    }
    while(n)
    {
        printf("%d", n % 10);
        n /= 10;
    }
    
    return 0;
}