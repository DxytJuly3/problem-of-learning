#include <stdio.h>
//判断一个整数是否能5整除是一个挺简单的问题，懒惰的KiKi还是不想自己做，于是找到你帮他写代码，你就帮帮他吧。
int main()
{
    int M = 0;
    scanf("%d",&M);
    int num = M % 5;
    if (num == 0)
        printf("YES");
    else
        printf("NO");
    
    return 0;
}