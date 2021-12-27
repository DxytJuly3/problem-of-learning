#include<stdio.h>
//据说智商140以上者称为天才，KiKi想知道他自己是不是天才，请帮他编程判断。
//输入一个整数表示一个人的智商，如果大于等于140，则表明他是一个天才，输出“Genius”。
int main()
{
    int a=0;
    while(scanf("%d",&a)!=EOF);    //注意多行输入
    if(a>=140)
    {
        printf("Genius\n");
    }
    
    return 0;
}