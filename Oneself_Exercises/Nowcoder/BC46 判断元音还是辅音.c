#include <stdio.h>
//判断是元音还是辅音
int main()
{
    char c = 0;
    while(scanf("%c", &c) != EOF)
    {
        if(c == 'A' ||
           c == 'a' ||
           c == 'E' ||
           c == 'e' ||
           c == 'I' ||
           c == 'i' ||
           c == 'O' ||
           c == 'o' ||
           c == 'U' ||
           c == 'u')
                printf("Vowel\n");
        else
            printf("Consonant\n");
        scanf("%c", &c);
    }
    
    return 0;
}