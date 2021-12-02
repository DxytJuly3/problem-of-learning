//从键盘输入 n 个学生成绩，输出每组排在前五高的成绩。

#include <stdio.h>
 
int main()
{
    int n = 0;
    int i = 0;
    int max = 0;
    int scores[45] = {0};
    scanf("%d", &n);
    for(i = 0; i < n; i++)
    {//循环输入分数
        scanf("%d",&scores[i]);
    }
    int temp = 0;
    for(i = 0; i < 5; i++)
    {//外循环五次，每次输出最大值
        max = 0;
        int j = 0;
        for(j = 0; j < n; j++)
        {//内循环，遍历循环查找最大值放入 max
            if(scores[j] > max)
            {
                max = scores[j];
                temp = j;
            }
        }
        scores[temp] = 0;    //内循环结束，将当前最大值置为0，消除当前最大值
        printf("%d ", max);//输出数组 当前的最大值
    }
     
    return 0;
}