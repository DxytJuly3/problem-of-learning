#define _CRT_SECURE_NO_WARNINGS 1

#include "DS_tset1_function.h"

//=========������=================
void main()
{
    char num[5];
    int dt;
    LinkList head;
    head = CreatList();            //��ͷ���뷨��������������ͷָ��
 
    printlist(head);				  //�������������ֵ
    printf("Delete node �� (y / n):");//���롱y����n��ȥѡ���Ƿ�ɾ�����
    scanf("%s", num);
    if (strcmp(num, "y") == 0 || strcmp(num, "Y") == 0)
    {
        printf("Please input Delete data:");
        scanf("%d", &dt);          //����Ҫɾ������ֵ
        DeleteList(head, dt);
        printlist(head);
    }

    printf("Add node �� (y / n):"); //���롱y����''n"ȥѡ���Ƿ����ӽ��
    scanf("%s", num);
    if ( strcmp(num,"y") == 0 || strcmp(num, "Y") == 0)
    {
        head = AddNode(head);
    }
    printlist(head);
    DeleteAll(head);             //ɾ�����н�㣬�ͷ��ڴ�
}

