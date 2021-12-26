#include <stdio.h>
//2020年来到了，KiKi要对他的n位好朋友说n遍”Happy new year!Good luck!”的祝福语。
int main()
{
    int n = 0;
    scanf("%d", &n);
    while(n)
    {
        printf("Happy new year!Good luck!\n");
        n--;
    }
    
    return 0;
}