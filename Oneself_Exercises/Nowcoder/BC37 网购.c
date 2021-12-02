//如果今天是“双11”（11月11日）则这件衣服打7折，“双12” （12月12日）则这件衣服打8折，如果有优惠券可以额外减50元（优惠券只能在双11或双12使用）

#include <stdio.h>
 
int main()
{
    double price = 0;
    int month = 0;
    int date = 0;
    int pre = 0;
    double actual = 0;
    scanf("%lf%d%d%d", &price, &month, &date, &pre);
    if(month == 11 && date == 11)
    {
        if(pre == 1)
            actual = price * 0.7 - 50;
        else
            actual = price * 0.7;
    }
    else if(month == 12 && date == 12)
    {
        if(pre == 1)
            actual = price * 0.8 - 50;
        else
            actual = price * 0.8;
    }
    else
    {
        if(pre == 1)
            actual = price - 50;
        else
            actual = price;
    }
    if(actual < 0)
        printf("0.00");
    else
        printf("%.2lf",actual);
     
    return 0;
}