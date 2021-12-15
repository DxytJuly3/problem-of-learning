#include <stdio.h>
//KiKi访问网站，得到HTTP状态码，但他不知道什么含义，BoBo老师告诉他常见HTTP状态码：
//200（OK，请求已成功）
//202（Accepted，服务器已接受请求，但尚未处理。）
//400（Bad Request，请求参数有误）
//403（Forbidden，被禁止）
//404（Not Found，请求失败）
//500（Internal Server Error
//服务器内部错误）
//502（Bad Gateway，错误网关）。
int main()
{
    int state = 0;
    while(scanf("%d", &state) != EOF)
    {
        if(state == 200)
            printf("OK\n");
        else if(state == 202)
            printf("Accepted\n");
        else if(state == 400)
            printf("Bad Request\n");
        else if(state == 403)
            printf("Forbidden\n");
        else if(state == 404)
            printf("Not Found\n");
        else if(state == 500)
            printf("Internal Server Error\n");
        else if(state == 502)
            printf("Bad Gateway\n");
    }
    
    return 0;
}