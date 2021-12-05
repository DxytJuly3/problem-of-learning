//公务员面试现场打分。有7位考官，从键盘输入若干组成绩，每组7个分数（百分制），去掉一个最高分和一个最低分，输出每组的平均成绩。
#include <stdio.h>

int Max_0(int* score)
{//返回数组中最大值所在位置的下标
    int max = score[0];
    int count = 0;
    for(int i = 0; i < 7; i++)
    {
        if(score[i] > max)
        {
            max = score[i];
            count = i;
        }
    }
   
    return count;
}
int Min_0(int* score)
{//返回数组中最小值所在位置的下标
    int min = score[0];
    int count = 0;
    for(int i = 0; i < 7; i++)
    {
        if(score[i] < min)
        {
            min = score[i];
            count = i;
        }
    }
    
    return count;
}

void Max_Min_0(int* score)
{
    int min = score[0];
    int max = score[0];
    int count_max = 0;
    int count_min = 0;
    for(int i = 0; i < 7; i++)
    {
        if(score[i] > max)
        {
            max = score[i];
            count_max = i;
        }
    }
    for(int i = 0; i < 7; i++)
    {
        if(score[i] < min)
        {
            min = score[i];
            count_min = i;
        }
    }
    score[count_max] = 0;
    score[count_min] = 0;
}

int main()
{
    int score[7] = {0};
    double sum = 0;
    for(int i = 0; i < 7; i++)
    {
        scanf("%d", &score[i]);
    }
    
    //int count_min = Min_0(score);
    //int count_max = Max_0(score);
    //score[count_max] = 0;
    //score[count_min] = 0;            //此方法是 返回最大值和最小值所在坐标后 置零
                                     // 还可以写函数直接使最大值最小值置零
    Max_Min_0(score);                // 此方法是用函数直接是最大值和最小值置零
    
    for(int i = 0; i < 7; i++)
    {
        sum += score[i];
    }
    printf("%.2lf",sum / 5.0);
    
    return 0;
}