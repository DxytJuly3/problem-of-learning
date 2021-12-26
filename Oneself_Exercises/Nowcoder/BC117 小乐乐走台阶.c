#include <stdio.h>
//小乐乐上课需要走n阶台阶，因为他腿比较长，所以每次可以选择走一阶或者走两阶，那么他一共有多少种走法？
int main()
{
    int n = 0;
    int arr[31] = { 0 };
    arr[1] = 1;
    arr[2] = 2;
    scanf("%d", &n);
    int i = 0;
    for(i = 1; i < 31; i++)
    {
        arr[i+2] = arr[i] + arr[i+1];
    }
    printf("%d",arr[n]);
    
    return 0;
}