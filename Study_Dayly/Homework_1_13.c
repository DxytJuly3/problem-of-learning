#define _CRT_SECURE_NO_WARNINGS 1

//#include <stdio.h>
//
//int main()
//{
//	char s[] = "\\123456\123456\t";
//	printf("%d\n", strlen(s));
//
//	return 0;
//}

//#include <stdio.h>
//#define N 2
//#define M N + 1
//#define NUM (M + 1) * M / 2
//int main()
//{
//	printf("%d\n", NUM);
//
//	return 0;
//}
/* 解析：
#define(预处理)不封装
所以 NUM = (N + 1 + 1) * N + 1 / 2 === 4 * 2 + 0.5 === 8.5
输出整型 8
*/

//#include <stdio.h>
//
//int f(int n)
//{
//    static int i = 1;
//    if (n >= 5)
//        return n;
//    n = n + i;
//    i++;
//    return f(n);
//}
//
//int main()
//{
//    printf("%d", f(1));
//
//    return 0;
//}
/* 解析：
f(1):
n = 1; i = 1;
n < 5
n += i ==> n = 2
i++ => i = 2
     ↓
f(2):
n = 2;i = 2;
n < 5
n += i ==> n = 4
i++ => i = 3
      ↓
f(4):
n = 4;i = 3;
n < 5
n += i ==> n = 7
i++ => i = 4
      ↓
f(7):
n = 7;i = 4;
n > 5;
return n;//n = 7
*/

//#include <stdio.h>
//
//int main()
//{
//    double a = 1;
//    double b = 0;
//    if (a == 0.0)
//        printf("1");
//    if (b == 0.0)
//        printf("5");
//
//    return 0;
//}

//#include <stdio.h>
//
//int main()
//{
//    int m = 0;
//    while (scanf("%d", &m) != EOF)
//    {
//        int m_num = m * m;
//        if (m % 2 == 0)
//        {
//            m_num = m_num - 2 * (int)(m / 2) + 1;
//            for (int i = 0; i < m; i++)
//            {
//                if (i == m - 1)
//                    printf("%d", m_num);
//                else
//                    printf("%d+", m_num);
//                m_num += 2;
//            }
//            printf("\n");
//        }
//        else
//        {
//            m_num = m_num - 2 * (int)(m / 2);
//            for (int i = 0; i < m; i++)
//            {
//                if (i == m - 1)
//                    printf("%d", m_num);
//                else
//                    printf("%d+", m_num);
//                m_num += 2;
//            }
//            printf("\n");
//        }
//    }
//
//    return 0;
//}