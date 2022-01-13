//验证尼科彻斯定理，即：任何一个整数m的立方都可以写成m个连续奇数之和。
//例如：
//1^3=1
//2^3=3+5
//3^3=7+9+11
//4^3=13+15+17+19
//输入一个正整数m（m≤100），将m的立方写成m个连续奇数之和的形式输出。
//本题含有多组输入数据。

#include <stdio.h>

int main()
{
    int m = 0;
    while (scanf("%d", &m) != EOF)
    {
        int m_num = m * m;
        if (m % 2 == 0)
        {
            m_num = m_num - 2 * (int)(m / 2) + 1;
            for (int i = 0; i < m; i++)
            {
                if (i == m - 1)
                    printf("%d", m_num);
                else
                    printf("%d+", m_num);
                m_num += 2;
            }
            printf("\n");
        }
        else
        {
            m_num = m_num - 2 * (int)(m / 2);
            for (int i = 0; i < m; i++)
            {
                if (i == m - 1)
                    printf("%d", m_num);
                else
                    printf("%d+", m_num);
                m_num += 2;
            }
            printf("\n");
        }
    }

    return 0;
}