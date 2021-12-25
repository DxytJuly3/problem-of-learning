#include <stdio.h>
//输入一个字符，用它构造一个边长为5的三角形圣诞树。
//数据范围：保证输入的字符是一个 char 类型的值
int main()
{
    char c;
    scanf("%c",&c);
    for(int i = 1;i <= 5;i++)
    {
        for(int j = 5 - i;j > 0;j--)
            printf(" ");
        for(int k = 1;k <= i;k++)
            printf("%c ",c);
        printf("\n");
    }
    
    return 0;
}