//将一个四位数，反向输出。
#include <stdio.h>
 
int main()
{
    int num = 0;
    int i = 0;
    scanf("%d",&num);
    for(i = 0; i < 4; i++)
    {
        printf("%d", num % 10);
        num /= 10;
    }
     
    return 0;
}
