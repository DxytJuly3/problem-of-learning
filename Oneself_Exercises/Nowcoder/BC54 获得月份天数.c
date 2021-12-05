//KiKi想获得某年某月有多少天，请帮他编程实现。输入年份和月份，计算这一年这个月有多少天。
#include <stdio.h>

int main()
{
    int year = 0;
    int month = 0;
    while(scanf("%d %d", &year, &month) != EOF)
    {
        if( month == 1 || month == 3 || month == 5 || month == 7 || month == 8 ||
            month == 10 || month == 12 )
        printf("31\n");
        if( month == 4 || month == 6 || month == 9 || month == 11 )
            printf("30\n");
        if( month == 2)
        {
            if((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
                printf("29\n");
            else
                printf("28\n");
        }
    }
    
    return 0;
}