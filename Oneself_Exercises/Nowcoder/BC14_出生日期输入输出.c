//输入一个人的出生日期（包括年月日），将该生日中的年、月、日分别输出。
#include <stdio.h>
 
int main()
{
    int year = 0;
    int month = 0;
    int date = 0;
    scanf("%4d%2d%2d", &year, &month, &date);
    printf("year=%d\nmonth=%02d\ndate=%02d", year, month, date);
 
    return 0;
}
