#include <stdio.h>
//给定秒数 seconds ，把秒转化成小时、分钟和秒。
int main()
{
    int seconds = 0;
    scanf("%d", &seconds);
    printf("%d %d %d\n", seconds / 3600, seconds % 3600 / 60, seconds % 3600 % 60);
    
    return 0;
}