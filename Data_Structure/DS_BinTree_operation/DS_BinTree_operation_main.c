#define _CRT_SECURE_NO_WARNINGS 1

#include "DS_BinTree_operation_function.h"

//==========������===============
void main()
{
    BinTree root;
    char i;
    int depth;
    printf("Creat Bin Tree;  \nInput preorder:>");

    //������ȫ���������������У�
   //��#�������㣬��ABD####CE##F# #
    root = CreatBinTree();//���������������ظ����
    do 				    	//�Ӳ˵���ѡ�������ʽ��������š�
    {
        printf("\t********** select ************\n");
        printf("\t l: Preorder Traversal\n");
        printf("\t 2: Iorder Traversal\n");
        printf("\t 3: Postorder traversal\n");
        printf("\t 4: PostTreeDepth, Node number, Leaf number\n");
        printf("\t 5: Level Depth\n");

            //����α���֮ǰ����ѡ��4����������Ľ������
        printf("\t 0: Exit\n");
        printf("\t * ******************************\n");
        fflush(stdin);
        scanf("%c", &i);		//����˵����(0-5 )
            switch (i - '0')
            {
            case 1: 	
                printf("Print Bin tree Preorder:");
                Preorder(root);	  //�������
                break;
            case 2: 	
                printf("Print Bin Tree Inorder:");
                Inorde(root);      //�������
                break;
            case 3: 	
                printf("Print Bin Tree Postorder:");
                Postorder(root);  	//�������
                break;
            case 4: 
                depth = TreeDepth(root); //��������ȼ�Ҷ����
                printf("BinTree Depth %d BinTree Node number %d", depth, NodeNum);
                printf(" BinTree Leaf number %d", countleaf(root));
                break;
            case 5: 	
                printf("Leve Print Bin Tree:");
                Levelorder(root);	//����α���
                break;
            default: 
                exit(1);
            }
        printf(" \n");
    } while (i != 0);
}

