#include<stdio.h>
//KiKi和BoBo玩 “井”字棋。
//也就是在九宫格中，只要任意行、列，或者任意对角线上面出现三个连续相同的棋子，就能获胜。请根据棋盘状态，判断当前输赢。
int main()
{
    char qipan[3][3] = { 0 };
    int d[3][3] = { 0 };//笨方法，用整数来代替字符来处理，以算和的方式来统计
    int count = 0;//用于统计每行每列是否都是相同元素
    int xiejiao1 = 0;//用于统计斜角线上的情况
    int xiejiao2 = 0;//用于统计反斜角线的情况
    for(int i = 0; i < 3;i++)
    {
        for(int j = 0; j < 3;j++)
        {
            scanf("%c", &qipan[i][j]);//这里也可以不需要qipan数组，因为最后并不需要输出棋盘上的情况
            getchar();//设置getchar用于吸收掉空格或者回车
            if(qipan[i][j] == 'K')//如果是K下的棋，则将相应的位置为1
                d[i][j] = 1;
            else if(qipan[i][j] == 'B')//如果是B下的棋，则将相应的位置为11
                d[i][j] = 11;
            else//其他的置为0
                d[i][j] = 0;
        }
    }
    for(int i = 0; i < 3; i++)//先按行扫描，顺便把斜角的也一起扫描了
    {
        for(int j=0;j<3;j++)
        {
            count += d[i][j];//扫描行的情况
            if(i == j)//顺带把斜角的情况也扫描了
                xiejiao1 += d[i][j];
            if(i + j == 2)//把反斜角的情况给扫描了//这里纠正一下，可以换成N-1而不是固定死为2
                xiejiao2 += d[i][j];
        }
        if(count == 3 || xiejiao1 == 3 || xiejiao2 == 3)//K赢的情况
        {
            printf("KiKi wins!");
            return 0;
        }
        if(count==33||xiejiao1==33||xiejiao2==33)//B赢的情况
        {
            printf("BoBo wins!");
            return 0;
        }
        count = 0;
    }
    for(int i = 0; i < 3; i++)//扫描列的情况
    {
        for(int j = 0; j < 3; j++)
        {
            count += d[j][i];
        }
        if(count == 3)
        {
            printf("KiKi wins!");
            return 0;
        }
        if(count == 33)
        {
            printf("BoBo wins!");
            return 0;
        }
        count = 0;
    }
     
    printf("No winner!");
    return 0;
}