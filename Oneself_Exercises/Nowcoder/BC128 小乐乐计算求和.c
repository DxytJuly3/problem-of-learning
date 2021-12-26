#include <stdio.h>
//小乐乐想计算一下1!+2!+3!+...+n!。
int main()
{
    int n = 0;
    int jc = 1;
    int sum_jc = 0;
    scanf("%d", &n);
    for(int i = 1; i <= n; i++)
    {
        jc *= i;
        sum_jc += jc;
    }
    printf("%d", sum_jc);
    
    return 0;
}