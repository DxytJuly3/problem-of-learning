#include <stdio.h>
//确定不同整型数据类型在内存中占多大（字节），输出不同整型数据类型在内存中占多大（字节）。 
int main()
{
    int a = sizeof(short),b = sizeof(int),c = sizeof(long),d = sizeof(long long);
    printf("The size of short is %d bytes.\n",a);
    printf("The size of int is %d bytes.\n",b);
    printf("The size of long is %d bytes.\n",c);
    printf("The size of long long is %d bytes.\n",d);
    
    return 0;
}