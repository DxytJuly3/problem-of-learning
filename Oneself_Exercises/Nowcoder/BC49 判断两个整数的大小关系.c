#include <stdio.h>
//判断两个整数的大小关系
int main()
{
    int a = 0;
    int b = 0;
    while(scanf("%d%d", &a, &b) != EOF)
    {
        if(a > b)
            printf("%d>%d\n",a,b);
        else if(a < b)
            printf("%d<%d\n",a,b);
        else
            printf("%d=%d\n",a,b);
    }
    
    return 0;
}