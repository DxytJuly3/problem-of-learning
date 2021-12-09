#include <stdio.h>
//字母大小写转换
int main()
{
    char c = 0;
    while(scanf("%c", &c) != EOF)
    {
        if('a' <= c && c <= 'z')
            printf("%c\n", c-32);
        else if('A' <= c && c <= 'Z')
            printf("%c\n", c+32);
        scanf("%c",&c);
    }
    
    return 0;
}