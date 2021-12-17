#include <stdio.h>
//任意输入一个正整数N，统计1~N之间奇数的个数和偶数的个数，并输出。
int main()
{
    int n = 0;
    int i = 0;
    int ji = 0;
    int ou = 0;
    scanf("%d", &n);
    for (i = 1; i <= n; i++)
    {
        if (i % 2 == 0)
            ou++;
        else
            ji++;
    }
    printf("%d %d", ji, ou);


    return 0;
}