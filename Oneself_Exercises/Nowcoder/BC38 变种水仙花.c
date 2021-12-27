#include<stdio.h>
//变种水仙花数 - Lily Number：把任意的数字，从中间拆分成两个数字，比如1461 可以拆分成（1和461）,（14和61）,（146和1)
//如果所有拆分后的乘积之和等于自身，则是一个Lily Number。
//例如：
//655 = 6 * 55 + 65 * 5
//1461 = 1*461 + 14*61 + 146*1
//求出 5位数中的所有 Lily Number。
int main()
{
    int i,j;
    for(i=10000;i<99999;i++)
    {
        int sum=0;
        for(j=10;j<=10000;j=10*j)
        {
            sum+=(i/j)*(i%j);
        }
        if(sum==i)
            printf("%d ",i);
    }
    
    return 0;
}