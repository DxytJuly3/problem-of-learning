#include <stdio.h>
//输入10科成绩，换行显示输入的10科成绩。
int main()
{
    int arr[10] = { 0 };
    int i = 0;
    for(i = 0; i < 10; i++)
    {
        scanf("%d", &arr[i]);
    }
    for(i = 0; i < 10; i++)
    {
        printf("%d ", arr[i]);
    }
    
    return 0;
}