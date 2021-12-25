#include <stdio.h>
//KiKi写了一个输出“Hello world!”的程序，BoBo老师告诉他printf函数有返回值
//你能帮他写个程序输出printf(“Hello world!”)的返回值吗？
int main()
{
    int ret = printf("Hello world!");
    printf("\n");
    printf("%d",ret);
    
    return 0;
}