//Lily上课时使用字母数字图片教小朋友们学习英语单词，每次都需要把这些图片按照大小（ASCII码值从小到大）排列收好。请大家给Lily帮忙，通过C语言解决。
//本题含有多组样例输入。
//数据范围：每组输入的字符串长度满足 1 ≤ n ≤ 1000 

#include <stdio.h>
#include <string.h>

int cmp_char(const void* a, const void* b)
{
    return (*(char*)a - *(char*)b);
}

int main()
{
    char chs[1025] = { 0 };
    while (scanf("%s", &chs) != EOF)
    {
        int ch_len = strlen(chs);
        qsort(chs, ch_len, sizeof(chs[0]), cmp_char);
        printf("%s\n", chs);
    }

    return 0;
}