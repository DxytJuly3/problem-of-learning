//#include <stdio.h>
//
//int main()
//{
//	int i = 0;
//	int flag = 0;
//	for (i = 0; i < 2020; i++)
//	{
//		int set = i;
//		while (set)
//		{
//			if(set % 10 != 9)
//				set /= 10;
//			else
//			{
//				flag++;
//				break;
//			}
//		}
//	}
//	printf("%d ", flag);
//
//	return 0;
//}

#include <stdio.h>

int main()
{
    int n = 0;
    int i = 0;
    int ji = 0;
    int ou = 0;
    scanf("%d", &n);
    for (i = 1; i <= n; i++)
    {
        if (i % 2 == 0)
            ou++;
        else
            ji++;
    }
    printf("%d %d", ji, ou);


    return 0;
}