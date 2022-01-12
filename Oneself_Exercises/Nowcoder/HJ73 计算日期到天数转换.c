//根据输入的日期，计算是这一年的第几天。
//保证年份为4位数且日期合法。

#include <stdio.h>

int main()
{
    int Days[12]  = {31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365};
    int year = 0;
    int month = 0;
    int day = 0;
    while(scanf("%d%d%d", &year, &month, &day) != EOF)
    {
        int days = 0;
        if(month >= 2)
            days = Days[month - 2] + day;
        else
            days = day;
        if( ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) && ((month >2) || (month == 2 && day == 29)))
            days++;
        printf("%d\n", days);
    }
    
    return 0;
}