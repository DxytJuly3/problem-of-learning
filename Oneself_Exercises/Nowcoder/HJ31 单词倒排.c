//对字符串中的所有单词进行倒排。
//说明：
//1、构成单词的字符只有26个大写或小写英文字母；
//2、非构成单词的字符均视为单词间隔符；
//3、要求倒排后的单词间隔符以一个空格表示；如果原字符串中相邻单词间有多个间隔符时，倒排转换后也只允许出现一个空格间隔符；
//4、每个单词最长20个字母；

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