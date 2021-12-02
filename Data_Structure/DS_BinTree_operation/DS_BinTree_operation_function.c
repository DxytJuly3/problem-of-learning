#define _CRT_SECURE_NO_WARNINGS 1

#include "DS_BinTree_operation_function.h"

typedef struct node {
    char data;
    struct node* lchild, * rchild;
}BinTNode;              //自定义二又树的结点类型

//=========基于先序遍历算法创建二又树===============
//========要求输入先序序列，其中加入虚结点”#"以示空指针的位置========
BinTree CreatBinTree(void)
{
    BinTree T;
    char ch;
    if ((ch = getchar()) == '#')
        return(NULL);               //读入#，返回空指针
    else
    {
        T = (BinTNode*)malloc(sizeof(BinTNode));	//生成结点
        T->data = ch;
        T->lchild = CreatBinTree();	           	    //构造左子树
        T->rchild = CreatBinTree();                 //构造右子树
        return(T);
    }
}

//============DLR先序遍历===============
void Preorder(BinTree T)
{
    if (T)
    {
        printf("%c", T->data);          //访问结点
        Preorder(T->lchild);		    //先序遍历左子树
        Preorder(T->rchild);		    //先序遍历右子树
    }
}

//============LDR中序遍历==============
void Inorde(BinTree T)
{
    if (T)
    {
        Inorde(T->lchild);              //中序遍历左子树
        printf("%c",T->data);	        //访问结点
        Inorde(T->rchild);              //中序遍历右子树
    }
}

//==========LRD后序遍历============
void Postorder(BinTree T)
{
    if (T)
    {
        Postorder(T->lchild);               //后序遍历左子树
        Postorder(T->rchild);               //后序遍历右子树
        printf("%c", T->data);		        //访问结点
    }
}

//===========采用后序遍历求二又树的深度、结点数及叶子数的递归算法
int TreeDepth(BinTree T)
{
    int hl, hr, max;
    if (T)
    {
        hl = TreeDepth(T->lchild);	            //求左深度
        hr = TreeDepth(T->rchild);	            //求右深度
        max = hl > hr ? hl : hr;                //左右深度的最大值
        NodeNum = NodeNum + 1;                  //求结点数
        if (hl == 0 && hr == 0)
            leaf = leaf + 1;		            //若左右深度为0，即为叶子。
        return(max + 1);
    }
    else return(0);
}

//========利用”先进先出” (FIFO)队列，按层次遍历二叉树============
void Levelorder(BinTree T)
{
    int front = 0, rear = 1;
    BinTNode* cq[Max], * p;		        //定义结点的指针数组cq
    cq[1] = T;			                //根入队
    while (front != rear)
    {
        front = (front + 1) % NodeNum;
        p = cq[front];			        //出队
        printf("%c", p->data);          //出队，输出结点的值
        if (p->lchild != NULL)
        {
            rear = (rear + 1) % NodeNum;
            cq[rear] = p->lchild;       //左子树入队
        }
        if (p->rchild != NULL)
        {
            rear = (rear + 1) % NodeNum;
            cq[rear] = p->rchild;       //右子树入队
        }
    }
}

//===============数叶子节点个数=============
int countleaf(BinTree T)
{
    int hl, hr;
    if (T)
    {
        hl = countleaf(T->lchild);
        hr = countleaf(T->rchild);
        if (hl == 0 && hr == 0) 		        //若左右深度为0，即为叶子。
            return(1);
        else
            return hl + hr;
    }
    else
        return 0;
}
