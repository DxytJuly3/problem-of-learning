#include <stdio.h>
//BoBo教KiKi字符常量或字符变量表示的字符在内存中以ASCII码形式存储。
//BoBo出了一个问题给KiKi，转换以下ASCII码为对应字符并输出他们。

73, 32, 99, 97, 110, 32, 100, 111, 32, 105, 116 , 33
int main()
{
    char strings[] = {73, 32, 99, 97, 110, 32, 100, 111, 32, 105, 116 , 33};
    printf("%s\n",strings);
    
    return 0;
}