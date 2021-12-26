#include <stdio.h>
#include <math.h>
//KiKi知道了什么是质数（只能被1和他自身整除的数），他现在想知道所有三位整数中，有多少个质数。
int main()
{
    int count = 0;
    for(int i = 100; i < 1000; i++)
    {
        int flag = 0;
        for(int j = 2; j <= sqrt(i); j++)   //优化
        {
            if(i % j == 0)
            {
                flag = 1;
                break;
            }
        }
        if(flag == 0)
            count++;
    }
    printf("%d\n", count);
    
    return 0;
}