#include <stdio.h>
//BoBo教KiKi字符常量或字符变量表示的字符在内存中以ASCII码形式存储。
//BoBo出了一个问题给KiKi，输入一个字符，输出该字符相应的ASCII码。
int main()
{
    char ch = 0;
    scanf("%c", &ch);
    //%d即可控制按整数输出
    printf("%d\n", ch);
    
    return 0;
}