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
//  ����˼·:
//  ��Ϊͳ��CHN����
//  ��ÿһ�� C �������� H ��� CH, ÿһ�� CH �ֶ������� N ��� CHN
//  ���Դ� C ��ʼ����
//  ���ѵ� C ,�� num_C ++;
//  �����һ���� H ,�� num_CH += num_C;
//  �������һ���� N, �� num_CHN += num_CH;
//  
//  CCCHN
//	�ѵ� C ,�� num_C++;
//	��Ϊǰ�������� C , �� num_C == 3;
//	Ȼ���ѵ� H , ǰ�ߵ� C �����Ժ� �� H ��� CH ��, num_CH = num_CH + num_C == 0 + 3 == 3;
//	Ȼ���ѵ� N , ǰ�ߵ����� CH �����Ժ� �� N ��� CHN, �� num_CHN = num_CHN + num_CH == 0 + 3 == 3;
//
//  CCHNCHCHN
//	�ѵ� C, �� num_C++;
//	ǰ������ C , �� num_C == 2��
//	�������� H , �� num_CH = num_CH + num_C == 2;
//	���ĸ��� N , ǰ�ߵ����� CH �����Ժ� �� N ��� CHN, �� num_CHN = num_CHN + num_CH == 0 + 2 == 2;
//	������� C , �� num_C++ == 3;
//	�������� H , ǰ�ߵ� C �����Ժ� �� H ��� CH ��, num_CH = num_CH + num_C == 2 + 3 == 5;
//	���߸��� C , �� num_C++ == 4;
//	�ڰ˸��� H , ǰ�ߵ� C �����Ժ� �� H ��� CH ��, num_CH = num_CH + num_C == 5 + 4 == 9;
//	�ھŸ��� N , ǰ�ߵ����� CH �����Ժ� �� N ��� CHN, �� num_CHN = num_CHN + num_CH == 2 + 9 == 11;
//
//	���� CHN ��11��
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