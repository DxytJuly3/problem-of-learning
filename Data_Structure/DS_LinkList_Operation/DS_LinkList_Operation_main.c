#define _CRT_SECURE_NO_WARNINGS 1

#include "DS_tset1_function.h"

//=========主函数=================
void main()
{
    char num[5];
    int dt;
    LinkList head;
    head = CreatList();            //用头插入法建立单链表，返回头指针
 
    printlist(head);				  //遍历链表输出其值
    printf("Delete node ？ (y / n):");//输入”y”或”n”去选择是否删除结点
    scanf("%s", num);
    if (strcmp(num, "y") == 0 || strcmp(num, "Y") == 0)
    {
        printf("Please input Delete data:");
        scanf("%d", &dt);          //输入要删除的数值
        DeleteList(head, dt);
        printlist(head);
    }

    printf("Add node ？ (y / n):"); //输入”y”或''n"去选择是否增加结点
    scanf("%s", num);
    if ( strcmp(num,"y") == 0 || strcmp(num, "Y") == 0)
    {
        head = AddNode(head);
    }
    printlist(head);
    DeleteAll(head);             //删除所有结点，释放内存
}

