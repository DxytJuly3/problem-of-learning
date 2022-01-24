#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>

typedef struct User {
    char Name[20];
    char Sex[10];
    char Addr[30];
    char QQ[12];
    char WeChat[25];
}User;

int main()
{
    User CSDN_User = { "July3", "Male", "CSDN", "xxxxxxxxxx", "xxxxxxxx" };

    return 0;
}
