#include <stdio.h>
//实现字母的大小写转换。多组输入输出。
int main()
{
    char A = 0;
    while ((A = getchar()) != EOF)
    {
        getchar();
        if (A >= 'A' && A <= 'Z')
        {
            putchar(A + 32);
            printf("\n");
        }
        else
        {
            putchar(A - 32);
            printf("\n");
        }
    }
    
    return 0;
}