#include <stdio.h>
//判断整数奇偶性
int main()
{
    int n = 0;
    while(scanf("%d", &n) != EOF)
    {
        if(n % 2 == 0)
            printf("Even\n");
        else
            printf("Odd\n");
    }
    
    return 0;
}