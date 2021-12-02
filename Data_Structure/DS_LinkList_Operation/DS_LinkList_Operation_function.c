#define _CRT_SECURE_NO_WARNINGS 1

#include "DS_tset1_function.h"

typedef struct node          //定义结点
{
    int data;                //结点的数据域为整数值
    struct node* next;       //结点的指针域
}ListNode;

//========用尾插入法建立带头结点的单链表==========
LinkList CreatListR(void)
{
    int dt;
    LinkList head = (LinkList)malloc(sizeof(ListNode));	//生成头结点
    ListNode* s, * r, * pp;
    r = head;
    r->next = NULL;
    printf("Input 0 to end\n");         // 输入”0”代表输入结束
    printf("Please input Node_data:>");
    scanf("%d", &dt);		            //输入各结点的数据
    while (dt != 0)
    {
        pp = LocateNode(head, dt);      //按值查找结点，返回结点指针
        if (pp = NULL) 		            //没有重复的字符串，插入到链表中
        {
            s = (ListNode*)malloc(sizeof(ListNode));
            s->data = dt;
            r->next = s;
            r = s;
            r->next = NULL;
        }
        printf("Input 0 to end\n");
        printf("Please input Node_data:>");
        scanf("%d", &dt);
    }
    return head; 		                //返回头指针
}

//============用头插入法建立带头结点的单链表==========
LinkList CreatList(void)
{
    int dt;
    LinkList head, p;
    head = (LinkList)malloc(sizeof(ListNode));
    head->next = NULL;
    while (1)
    {
        printf("Input 0 to end\n");                 // 输入”0”代表输入结束
        printf("Please input Node_data:>");
        scanf("%d", &dt);                           //输入各结点的数据
        if (dt != 0)
        {
            if (LocateNode(head, dt) == NULL)
            {
                p = (LinkList)malloc(sizeof(ListNode));
                p->data = dt;
                p->next = head->next;
                head->next = p;
            }
        }
        else
            break;
    }
    return head;                                    //返回头指针
}

//=======按值查找结点，找到则返回该结点的位置，否则返回NULL
ListNode* LocateNode(LinkList head, int key)
{
    ListNode* p = head->next;		     //从首元结点比较
    while (p != NULL && p->data != key) //直到p为NULL或p->data为key止
        p = p->next;                  //扫描下一个结点
    return p;    //若p=NULL则查找失败，否则p指向找到的值为key的结点
}

//============修改程序:增加节点================
ListNode* AddNode(LinkList head)
{
    int dt;
    ListNode* s, * pp;
    printf("\nPlease input a New Nodees data:");
    scanf("%d", &dt);		                //输入结点的数值
    pp = LocateNode(head, dt);  	        //按值查找结点，返回结点指针
    printf("ok! \n");
    if (pp == NULL) 		                //没有重复的字符串，插入到链表中
    {
        s = (ListNode*)malloc(sizeof(ListNode));
        s->data = dt;
        printf("ok!\n");
        s->next = head->next;
        head->next = s;
    }
    return head;
}

//=======删除带头结点的单链表中的指定结点===============
void DeleteList(LinkList head, int key)
{
    ListNode* p, * r, * q = head;
    p = LocateNode(head, key);      //按key值查找结点的
    if (p == NULL)		            //若没有找到结点，退出
    {
        printf("position error");
        exit(0);
    }
    while (q->next != p)            //P为要删除的结点，q为p的前结点
        q = q->next;
    r = q->next;
    q->next = r->next;
    free(r);                     //释放结点
}

//============打印链表===============
void printlist(LinkList head)
{
    ListNode* p = head->next;      //从首元结点打印
    while (p)
    {
        printf("%d ", p->data);
        p = p->next;
    }
    printf("\n");
}

//============删除所有结点，释放空间==========
void DeleteAll(LinkList head)
{
    //定义指针 p 指向链表头节点，定义指针 r 作为中间指针存储 p -> next
    ListNode* p = head, * r; 

    //若 p->next 不空，则将指针 r 指向 p->next 后，将指针 p 所指地址数据释放
    //释放后 再将指针 r 所指地址 至于指针 p，将指针 p 指向 p->next
    //直至 p->next 为空
    while (p->next)
    {
        r = p->next;
        free(p);
        p = r;
    }
    //若 p->next 为空，代表没有下一节点，直接释放指针 p 所指节点
    free(p);
}
