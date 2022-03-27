#define _CRT_SECURE_NO_WARNINGS 1

//#include <stdio.h>
//
//struct student {
//    char name[20];
//    int age;
//    char sex[10];
//};
//
//int main()
//{
//    struct student xxs = { "July", 20, "male" };
//    FILE* pf = fopen("test.txt", "w");
//    if (pf == NULL)
//    {
//        printf("文件打开失败\n");
//        return 0;
//    }
//    fprintf(pf, "%s %d %s", xxs.name, xxs.age, xxs.sex);
//
//    fclose(pf);
//    pf = NULL;
//
//    return 0;
//}

#include <stdio.h>

struct student {
    char name[20];
    int age;
    char sex[10];
};

int main()
{
    struct student xxs = { 0 };
    FILE* pf = fopen("test2.txt", "r");
    if (pf == NULL)
    {
        printf("文件打开失败\n");
        return 0;
    }
    fscanf(pf, "%s %d %s", xxs.name, &(xxs.age), xxs.sex);
    printf("%s %d %s", xxs.name, xxs.age, xxs.sex);

    fclose(pf);
    pf = NULL;

    return 0;
}