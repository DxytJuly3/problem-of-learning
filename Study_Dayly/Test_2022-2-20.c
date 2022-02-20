#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <string.h>

void reverse_char(char* arr_left, char* arr_right)
{
    while (arr_left < arr_right)
    {
        char tmp = *arr_left;
        *arr_left = *arr_right;
        *arr_right = tmp;
        arr_left++;
        arr_right--;
    }
}

int main()
{
    char arr[10001] = { 0 };
    gets(arr);
    size_t arr_len = strlen(arr);
    reverse_char(arr, arr + arr_len - 1);

    char* arr_left = arr;
    while (*arr_left)
    {
        char* char_end = arr_left;
        while ((*char_end <= 'z' && *char_end >= 'a') || (*char_end <= 'Z' && *char_end >= 'A'))
            char_end++;     //次循环记录一个单词的最后一个字母的后一位地址
        reverse_char(arr_left, char_end - 1);
        if (*char_end)
        {
            arr_left = char_end + 1;
            *char_end = ' ';
        }
        else
            arr_left = char_end;
    }

    printf("%s", arr);

    return 0;
}

