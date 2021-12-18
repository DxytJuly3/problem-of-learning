#include <stdio.h>
//输入数字N，然后输入N个数，计算这N个数的和。
int main()
{
    int n = 0;
    int i = 0;
    int sum = 0;
    int num = 0;
    scanf("%d", &n);
    for(i = 0; i < n; i++)
    {
        scanf("%d", &num);
        sum += num;
    }
    printf("%d", sum);
    
    return 0;
}