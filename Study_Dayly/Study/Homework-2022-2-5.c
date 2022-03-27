#define _CRT_SECURE_NO_WARNINGS 1

//#include <stdio.h>
//#include <math.h>
//
//int main()
//{
//    int n = 0;
//    while (scanf("%d", &n) != EOF)
//    {
//        int count = 0;
//        for (int i = 2; i <= n; i++)
//        {
//            int sum = 0;
//            for (int j = 1; j <= sqrt(i); j++)
//            {
//                if (i % j == 0)
//                    sum += (j + i / j);
//            }
//            if (sum - i == i)
//                count++;
//        }
//        printf("%d\n", count);
//    }
//
//    return 0;
//}

#include <stdio.h>

int main()
{
	int n = 0;
	int rubbit[32] = { 0,1,1,2,3,5,8,13,21,34,55,89,144,233,377,610,987,1597,2584,4181,6765,10946,17711,28657,46368,75025,121393,196418,317811,514229,832040,1346269 };
	while (scanf("%d", &n) != EOF)
	{
		printf("%d\n", rubbit[n]);
	}

	return 0;
}