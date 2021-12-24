#include <stdio.h>
//KiKi想从n行m列的方阵队列中找到身高最高的人的位置，请你帮助他完成这个任务。
int main()
{
    int n = 0;
    int m = 0;
    scanf("%d%d", &n, &m);
    int x = 0;
    int y = 0;
    int max = 0;
    int height = 0;
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < m; j++)
        {
            scanf("%d", &height);
            if(height > max)
            {
                max = height;
                x = i + 1;
                y = j + 1;
            }
        }
    }
    printf("%d %d\n", x, y);
    
    return 0;
}