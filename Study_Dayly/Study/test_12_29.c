#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>

char* makeFancyString(char* s)
{
    int sSize = 0;
    char* str = s;
    while (*(str++) != '\0')
        sSize++;
    str = s;
    if (sSize > 3)
    {
        while (*(str + 2) != '\0')
        {
            if ((*(str) == *(str + 1) && *(str + 1) == *(str + 2)) && *(str + 2) != '\0')
            {
                for (int j = 2; j < sSize - (str - s) - 1; j++)
                {
                    *(str + j) = *(str + j + 1);
                }
                *(s + sSize - 1) = '\0';
            }
            else if ((*(str) != *(str + 1) || *(str) != *(str + 2) || *(str + 1) != *(str + 2)) && *(str + 2) != '\0')
                str++;
        }
    }
    else
        return s;

    return s;
}

int main()
{
    char s[12] = "aaabaaaa";
    makeFancyString(s);
    printf("%s", s);

    return 0;
}