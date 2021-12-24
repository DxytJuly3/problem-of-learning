#include<stdio.h>
//小乐乐在课上学习了二进制八进制与十六进制后，对进制转换产生了浓厚的兴趣。因为他的幸运数字是6，所以他想知道一个数表示为六进制后的结果。请你帮助他解决这个问题。
void print(int x)
{
    if (x > 5)
    {
        print(x / 6);
    }
    printf("%d", x % 6);
}
int main()
{
    int n = 0;
    scanf("%d", &n);
    print(n);
    
    return 0;
}