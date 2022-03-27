#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>

char* convertToBase7(int num)
{
    char num_7[15] = { 0 };
    int count = 0;
    if (num >= 0)
    {
        int tmp = num / 7;
        *num_7 = num % 7;
        char* tmp7 = num_7;
        count = 2;
        while (tmp > 7)
        {
            for (int i = count - 1; i > 0; i--)
            {
                *(tmp7 + i) = *tmp7;
            }
            *tmp7 = tmp % 7;
            tmp /= 7;
            count++;
        }
        for (int i = count - 1; i > 0; i--)
        {
            *(tmp7 + i) = *tmp7 + i - 1;
        }
        *tmp7 = tmp % 7;
    }
    else
    {
        *num_7 = '-';
        int tmp = num / 7;
        *(num_7 + 1) = num % 7;
        char* tmp7 = num_7 + 1;
        count = 2;
        while (tmp > 7)
        {
            for (int i = count - 1; i > 0; i--)
            {
                *(tmp7 + i) = *tmp7;
            }
            *tmp7 = tmp % 7;
            tmp /= 7;
            count++;
        }
        for (int i = count - 1; i > 0; i--)
        {
            *(tmp7 + i) = *tmp7;
        }
        *tmp7 = tmp % 7;
    }

    return num_7;
}

int main()
{
    int* num = convertToBase7(100);
    printf("%d", *num);

    return 0;
}