//输入一个字符串和一个整数 k ，截取字符串的前k个字符并输出

#include <stdio.h>

int main()
{
    char str[101];
    while(scanf("%s", str) != EOF)
    {
        int n;
        scanf("%d", &n);
        str[n] = '\0';
        printf("%s\n", str);
    }
    
    return 0;
}