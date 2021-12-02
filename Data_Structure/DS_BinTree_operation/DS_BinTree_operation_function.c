#define _CRT_SECURE_NO_WARNINGS 1

#include "DS_BinTree_operation_function.h"

typedef struct node {
    char data;
    struct node* lchild, * rchild;
}BinTNode;              //�Զ���������Ľ������

//=========������������㷨����������===============
//========Ҫ�������������У����м������㡱#"��ʾ��ָ���λ��========
BinTree CreatBinTree(void)
{
    BinTree T;
    char ch;
    if ((ch = getchar()) == '#')
        return(NULL);               //����#�����ؿ�ָ��
    else
    {
        T = (BinTNode*)malloc(sizeof(BinTNode));	//���ɽ��
        T->data = ch;
        T->lchild = CreatBinTree();	           	    //����������
        T->rchild = CreatBinTree();                 //����������
        return(T);
    }
}

//============DLR�������===============
void Preorder(BinTree T)
{
    if (T)
    {
        printf("%c", T->data);          //���ʽ��
        Preorder(T->lchild);		    //�������������
        Preorder(T->rchild);		    //�������������
    }
}

//============LDR�������==============
void Inorde(BinTree T)
{
    if (T)
    {
        Inorde(T->lchild);              //�������������
        printf("%c",T->data);	        //���ʽ��
        Inorde(T->rchild);              //�������������
    }
}

//==========LRD�������============
void Postorder(BinTree T)
{
    if (T)
    {
        Postorder(T->lchild);               //�������������
        Postorder(T->rchild);               //�������������
        printf("%c", T->data);		        //���ʽ��
    }
}

//===========���ú�����������������ȡ��������Ҷ�����ĵݹ��㷨
int TreeDepth(BinTree T)
{
    int hl, hr, max;
    if (T)
    {
        hl = TreeDepth(T->lchild);	            //�������
        hr = TreeDepth(T->rchild);	            //�������
        max = hl > hr ? hl : hr;                //������ȵ����ֵ
        NodeNum = NodeNum + 1;                  //������
        if (hl == 0 && hr == 0)
            leaf = leaf + 1;		            //���������Ϊ0����ΪҶ�ӡ�
        return(max + 1);
    }
    else return(0);
}

//========���á��Ƚ��ȳ��� (FIFO)���У�����α���������============
void Levelorder(BinTree T)
{
    int front = 0, rear = 1;
    BinTNode* cq[Max], * p;		        //�������ָ������cq
    cq[1] = T;			                //�����
    while (front != rear)
    {
        front = (front + 1) % NodeNum;
        p = cq[front];			        //����
        printf("%c", p->data);          //���ӣ��������ֵ
        if (p->lchild != NULL)
        {
            rear = (rear + 1) % NodeNum;
            cq[rear] = p->lchild;       //���������
        }
        if (p->rchild != NULL)
        {
            rear = (rear + 1) % NodeNum;
            cq[rear] = p->rchild;       //���������
        }
    }
}

//===============��Ҷ�ӽڵ����=============
int countleaf(BinTree T)
{
    int hl, hr;
    if (T)
    {
        hl = countleaf(T->lchild);
        hr = countleaf(T->rchild);
        if (hl == 0 && hr == 0) 		        //���������Ϊ0����ΪҶ�ӡ�
            return(1);
        else
            return hl + hr;
    }
    else
        return 0;
}
