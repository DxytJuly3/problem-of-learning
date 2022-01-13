//等差数列 2，5，8，11，14。。。。
//（从 2 开始的 3 为公差的等差数列）
//输出求等差数列前n项和
//本题有多组输入

#include <stdio.h>

int main()
{
    int n = 0;
    while(scanf("%d", &n) != EOF)
    {
        int sum = 0;
        int now_n = 2;
        for(int i = 0; i < n; i++)
        {
            sum += now_n;
            now_n += 3;
        }
        printf("%d\n", sum);
    }
    
    return 0;
}