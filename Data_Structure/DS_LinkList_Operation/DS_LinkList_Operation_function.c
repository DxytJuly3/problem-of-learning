#define _CRT_SECURE_NO_WARNINGS 1

#include "DS_tset1_function.h"

typedef struct node          //������
{
    int data;                //����������Ϊ����ֵ
    struct node* next;       //����ָ����
}ListNode;

//========��β���뷨������ͷ���ĵ�����==========
LinkList CreatListR(void)
{
    int dt;
    LinkList head = (LinkList)malloc(sizeof(ListNode));	//����ͷ���
    ListNode* s, * r, * pp;
    r = head;
    r->next = NULL;
    printf("Input 0 to end\n");         // ���롱0�������������
    printf("Please input Node_data:>");
    scanf("%d", &dt);		            //�������������
    while (dt != 0)
    {
        pp = LocateNode(head, dt);      //��ֵ���ҽ�㣬���ؽ��ָ��
        if (pp = NULL) 		            //û���ظ����ַ��������뵽������
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
    return head; 		                //����ͷָ��
}

//============��ͷ���뷨������ͷ���ĵ�����==========
LinkList CreatList(void)
{
    int dt;
    LinkList head, p;
    head = (LinkList)malloc(sizeof(ListNode));
    head->next = NULL;
    while (1)
    {
        printf("Input 0 to end\n");                 // ���롱0�������������
        printf("Please input Node_data:>");
        scanf("%d", &dt);                           //�������������
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
    return head;                                    //����ͷָ��
}

//=======��ֵ���ҽ�㣬�ҵ��򷵻ظý���λ�ã����򷵻�NULL
ListNode* LocateNode(LinkList head, int key)
{
    ListNode* p = head->next;		     //����Ԫ���Ƚ�
    while (p != NULL && p->data != key) //ֱ��pΪNULL��p->dataΪkeyֹ
        p = p->next;                  //ɨ����һ�����
    return p;    //��p=NULL�����ʧ�ܣ�����pָ���ҵ���ֵΪkey�Ľ��
}

//============�޸ĳ���:���ӽڵ�================
ListNode* AddNode(LinkList head)
{
    int dt;
    ListNode* s, * pp;
    printf("\nPlease input a New Nodees data:");
    scanf("%d", &dt);		                //���������ֵ
    pp = LocateNode(head, dt);  	        //��ֵ���ҽ�㣬���ؽ��ָ��
    printf("ok! \n");
    if (pp == NULL) 		                //û���ظ����ַ��������뵽������
    {
        s = (ListNode*)malloc(sizeof(ListNode));
        s->data = dt;
        printf("ok!\n");
        s->next = head->next;
        head->next = s;
    }
    return head;
}

//=======ɾ����ͷ���ĵ������е�ָ�����===============
void DeleteList(LinkList head, int key)
{
    ListNode* p, * r, * q = head;
    p = LocateNode(head, key);      //��keyֵ���ҽ���
    if (p == NULL)		            //��û���ҵ���㣬�˳�
    {
        printf("position error");
        exit(0);
    }
    while (q->next != p)            //PΪҪɾ���Ľ�㣬qΪp��ǰ���
        q = q->next;
    r = q->next;
    q->next = r->next;
    free(r);                     //�ͷŽ��
}

//============��ӡ����===============
void printlist(LinkList head)
{
    ListNode* p = head->next;      //����Ԫ����ӡ
    while (p)
    {
        printf("%d ", p->data);
        p = p->next;
    }
    printf("\n");
}

//============ɾ�����н�㣬�ͷſռ�==========
void DeleteAll(LinkList head)
{
    //����ָ�� p ָ������ͷ�ڵ㣬����ָ�� r ��Ϊ�м�ָ��洢 p -> next
    ListNode* p = head, * r; 

    //�� p->next ���գ���ָ�� r ָ�� p->next �󣬽�ָ�� p ��ָ��ַ�����ͷ�
    //�ͷź� �ٽ�ָ�� r ��ָ��ַ ����ָ�� p����ָ�� p ָ�� p->next
    //ֱ�� p->next Ϊ��
    while (p->next)
    {
        r = p->next;
        free(p);
        p = r;
    }
    //�� p->next Ϊ�գ�����û����һ�ڵ㣬ֱ���ͷ�ָ�� p ��ָ�ڵ�
    free(p);
}
