//从键盘任意输入三个整数表示的分数，编程判断其中的最高分。

#include <stdio.h>
 
int main()
{
    unsigned int scores[3] = {0};
    for(int i = 0; i < 3; i++)
    {
        scanf("%d", &scores[i]);
    }
    int max = 0;
    for(int i = 0; i < 3; i++)
    {
        if(scores[i] > max)
            max = scores[i];
    }
    printf("%d",max);
     
    return 0;
}