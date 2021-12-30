//一个字符串如果没有 三个连续 相同字符，那么它就是一个 好字符串 。
//给你一个字符串 s ，请你从 s 删除 最少 的字符，使它变成一个 好字符串 。
//请你返回删除后的字符串。题目数据保证答案总是 唯一的 。

//来源：力扣（LeetCode）
//链接：https://leetcode-cn.com/problems/delete-characters-to-make-fancy-string

char* makeFancyString(char* s)
{//焯，目前所学知识只能超时了
    int sSize = 0;
    char* str = s;
    while (*(str++) != '\0')
        sSize++;
    str = s;
    if (sSize >= 3)
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