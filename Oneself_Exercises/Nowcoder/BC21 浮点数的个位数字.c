#include <stdio.h>
//给定一个浮点数，要求得到该浮点数的个位数。
int main()
{
    float f = 0.f;
    scanf("%f", &f);
    //使用int强制输出结果
    printf("%d", int(f)%10);
    return 0;
}