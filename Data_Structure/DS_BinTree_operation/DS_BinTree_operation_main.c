#define _CRT_SECURE_NO_WARNINGS 1

#include "DS_BinTree_operation_function.h"

//==========主函数===============
void main()
{
    BinTree root;
    char i;
    int depth;
    printf("Creat Bin Tree;  \nInput preorder:>");

    //输入完全二又树的先序序列，
   //用#代表虚结点，如ABD####CE##F# #
    root = CreatBinTree();//创建二叉树，返回根结点
    do 				    	//从菜单中选择遍历方式，输入序号。
    {
        printf("\t********** select ************\n");
        printf("\t l: Preorder Traversal\n");
        printf("\t 2: Iorder Traversal\n");
        printf("\t 3: Postorder traversal\n");
        printf("\t 4: PostTreeDepth, Node number, Leaf number\n");
        printf("\t 5: Level Depth\n");

            //按层次遍历之前，先选择4，求出该树的结点数。
        printf("\t 0: Exit\n");
        printf("\t * ******************************\n");
        fflush(stdin);
        scanf("%c", &i);		//输入菜单序号(0-5 )
            switch (i - '0')
            {
            case 1: 	
                printf("Print Bin tree Preorder:");
                Preorder(root);	  //先序遍历
                break;
            case 2: 	
                printf("Print Bin Tree Inorder:");
                Inorde(root);      //中序遍历
                break;
            case 3: 	
                printf("Print Bin Tree Postorder:");
                Postorder(root);  	//后序遍历
                break;
            case 4: 
                depth = TreeDepth(root); //求树的深度及叶子数
                printf("BinTree Depth %d BinTree Node number %d", depth, NodeNum);
                printf(" BinTree Leaf number %d", countleaf(root));
                break;
            case 5: 	
                printf("Leve Print Bin Tree:");
                Levelorder(root);	//按层次遍历
                break;
            default: 
                exit(1);
            }
        printf(" \n");
    } while (i != 0);
}

