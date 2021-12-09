#include <stdio.h>
//判断是不是字母
int main()
{
    char c = 0;
    while(scanf("%c", &c) != EOF)
    {
        if( ('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z') )
            printf("%c is an alphabet.\n",c);
        else
            printf("%c is not an alphabet.\n",c);
        scanf("%c",&c);
    }
    
    return 0;
}