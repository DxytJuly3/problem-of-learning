#include <stdio.h>
//已知一个函数y=f(x)，当x < 0时，y = 1；当x = 0时，y = 0；当x > 0时，y = -1。   
int main()
{
    int x = 0;
    scanf("%d", &x);
    if(x > 0)
        printf("%d",-1);
    else if(x == 0)
        printf("%d",0);
    else
        printf("%d",1);
    
    return 0;
}