#include <stdio.h>
//小乐乐获得4个最大数，请帮他编程找到最大的数。
int main()
{
    int n = 0;
    int max = 0;
    scanf("%d", &n);
    max = n;
    for(int i = 0; i < 3; i++)
    {
        scanf("%d", &n);
        if(n > max)
            max = n;
    }
    printf("%d", max);
    
    return 0;
}