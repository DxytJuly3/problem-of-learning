#include <stdio.h>
//小乐乐比较懒惰，他现在想睡觉，然后再去学习。他知道现在的时刻，以及自己要睡的时长
//想设定一个闹钟叫他起床学习，但是他太笨了，不知道应该把闹钟设定在哪个时刻，请你帮助他。(只考虑时和分，不考虑日期)
int main()
{
    int hour = 0;
    int minute = 0;
    long long sleeptime = 0;
    scanf("%d:%d%lld", &hour, &minute, &sleeptime);
    int outhour = 0;
    int outminute = 0;
    outhour = (hour + sleeptime / 60) % 24;
    outminute = minute + sleeptime % 60;
    if(outminute >= 60)
    {
        outhour++;
        outminute -= 60;
    }
    printf("%02d:%02d", outhour, outminute);
    
    return 0;
}