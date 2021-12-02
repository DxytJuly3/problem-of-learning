//从键盘任意输入一个字符，编程判断是否是字母（包括大小写）。
#include <stdio.h>
 
int main()
{
    char c = 0;
    c = getchar();
    if((c >= 'a' && c <= 'z' )|| (c >= 'A' && c <= 'Z'))
        printf("YES");
    else
        printf("NO");
     
    return 0;
}
