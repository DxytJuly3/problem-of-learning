/*BoBo买了一箱酸奶，里面有n盒未打开的酸奶
KiKi喜欢喝酸奶，第一时间发现了酸奶
KiKi每h分钟能喝光一盒酸奶，并且KiKi在喝光一盒酸奶之前不会喝另一个
那么经过m分钟后还有多少盒未打开的酸奶？*/
#include <stdio.h>
 
int main()
{
    int n = 0;
    int h = 0;
    int m = 0;
    scanf("%d%d%d", &n, &h, &m);
    if(m % h == 0)
        printf("%d", n - (m / h));
    else
        printf("%d", n - ((m / h) + 1));
     
    return 0;
}