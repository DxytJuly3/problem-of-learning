#define _CRT_SECURE_NO_WARNINGS 1

//#include <stdio.h>

//long long compute_gcd(long long n, long long m)
//{
//    if (m > n)
//    {
//        long long tmp = m;
//        m = n;
//        n = tmp;
//    }
//    while (n % m != 0)
//    {
//        int tmp = n % m;
//        n = m;
//        m = tmp;
//    }
//    return m;
//}

//int main()
//{
//    long long n = 0;
//    long long m = 0;
//    scanf("%lld%lld", &n, &m);
//    long long gcd = compute_gcd(n, m);
//    long long lcm = n * m / gcd;
//    long long sum_gcd_lcm = gcd + lcm;
//    printf("%lld", sum_gcd_lcm);
//
//    return 0;
//}


///*
//  具体思路:
//  因为统计CHN个数
//  且每一个 C 都可以与 H 组成 CH, 每一个 CH 又都可以与 N 组成 CHN
//  所以从 C 开始搜索
//  当搜到 C ,则 num_C ++;
//  如果下一个是 H ,则 num_CH += num_C;
//  如果再下一个是 N, 则 num_CHN += num_CH;
//  
//  CCCHN
//	搜到 C ,则 num_C++;
//	因为前三个都是 C , 则 num_C == 3;
//	然后搜到 H , 前边的 C 均可以和 此 H 组成 CH 则, num_CH = num_CH + num_C == 0 + 3 == 3;
//	然后搜到 N , 前边的所有 CH 均可以和 此 N 组成 CHN, 则 num_CHN = num_CHN + num_CH == 0 + 3 == 3;
//
//  CCHNCHCHN
//	搜到 C, 则 num_C++;
//	前两个是 C , 则 num_C == 2；
//	第三个是 H , 则 num_CH = num_CH + num_C == 2;
//	第四个是 N , 前边的所有 CH 均可以和 此 N 组成 CHN, 则 num_CHN = num_CHN + num_CH == 0 + 2 == 2;
//	第五个是 C , 则 num_C++ == 3;
//	第六个是 H , 前边的 C 均可以和 此 H 组成 CH 则, num_CH = num_CH + num_C == 2 + 3 == 5;
//	第七个是 C , 则 num_C++ == 4;
//	第八个是 H , 前边的 C 均可以和 此 H 组成 CH 则, num_CH = num_CH + num_C == 5 + 4 == 9;
//	第九个是 N , 前边的所有 CH 均可以和 此 N 组成 CHN, 则 num_CHN = num_CHN + num_CH == 2 + 9 == 11;
//
//	所以 CHN 共11个
//*/
//#include <stdio.h>
//
//int main()
//{
//	char str[8001] = { 0 };
//	scanf("%s", &str);
//	char* ps = str;
//	long long num_C = 0;
//	long long num_CH = 0;
//	long long num_CHN = 0;
//	while (*ps)
//	{
//		if (*ps == 'C')
//			num_C++;
//		if (*ps == 'H')
//			num_CH += num_C;
//		if (*ps == 'N')
//			num_CHN += num_CH;
//		ps++;
//	}
//	printf("%lld\n", num_CHN);
//
//	return 0;
//}

//#include <stdio.h>
//
//int main()
//{
//    printf("printf(\"Hello world!\\n\");\ncout << \"Hello world!\" << endl;\n");
//
//    return 0;
//}

#include <stdio.h>
#include <math.h>

int main()
{
    int count = 0;
    for (int i = 100; i < 1000; i++)
    {
        int flag = 0;
        for (int j = 2; j <= sqrt(i); j++)
        {
            if (i % j == 0)
            {
                flag = 1;
                break;
            }
        }
        if (flag == 0)
            count++;
    }
    printf("%d\n", count);

    return 0;
}