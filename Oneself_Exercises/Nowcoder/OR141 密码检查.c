//小明同学最近开发了一个网站，在用户注册账户的时候，需要设置账户的密码，为了加强账户的安全性，小明对密码强度有一定要求：
//1. 密码只能由大写字母，小写字母，数字构成；
//2. 密码不能以数字开头；
//3. 密码中至少出现大写字母，小写字母和数字这三种字符类型中的两种；
//4. 密码长度至少为8
//现在小明受到了n个密码，他想请你写程序判断这些密码中哪些是合适的，哪些是不合法的。

#include <stdio.h>
#include <string.h>
int main()
{
    int n = 0;
    scanf("%d", &n);
    for(int i = 0; i < n; i++)
    {
        int password_count = 0;
        int lower_count = 0;
        int num_count = 0;
        int upper_count = 0;
        int other_count = 0;
        char password[200] = { 0 };
        char* ri = password;
        scanf("%s", password);
        int password_len = strlen(password);
        while(*ri != '\0')
        {
            password_count++;
            if(*ri <= 'Z' && *ri >= 'A')
                upper_count++;
            else if(*ri <= 'z' && *ri >= 'a')
                lower_count++;
            else if(*ri <= '9' && *ri>= '0')
                num_count++;
            else
                other_count++;
            ri++;
        }
        if(other_count > 0 || password_count < 8 || (*password <= '9' && *password >= '0'))
            printf("NO\n");
        else if((upper_count > 0 && lower_count > 0) || (upper_count > 0 && num_count > 0) || (lower_count > 0 && num_count > 0))
            printf("YES\n");
        
    }
    
    return 0;
}