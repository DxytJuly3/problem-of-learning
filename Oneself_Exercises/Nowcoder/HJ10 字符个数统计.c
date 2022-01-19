//编写一个函数，计算字符串中含有的不同字符的个数。字符在 ASCII 码范围内( 0~127 ，包括 0 和 127 )，换行表示结束符，不算在字符里。
//不在范围内的不作统计。多个相同的字符只计算一次
//例如，对于字符串 abaca 而言，有 a、b、c 三种不同的字符，因此输出 3 。
//数据范围： 1 \le n \le 500 \1≤n≤500 

#include <stdio.h>
#include <string.h>

int main()
{
    char chs[501] = {0};
    gets(chs);
    int Len = strlen(chs);
    char returnChs[129] = { 0 };
    int count = 0;
    for(int i = 0; i < Len; i++)
    {
        int j = (int)chs[i];
        if(returnChs[j] == 0)
        {
            returnChs[j] = j;
            count++;
        }
    }
    printf("%d", count);
    
    return 0;
}