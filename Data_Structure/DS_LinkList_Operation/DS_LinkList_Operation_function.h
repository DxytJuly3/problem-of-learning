#pragma once
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct node ListNode;   //������


typedef ListNode* LinkList; //�Զ���LinkList����������

LinkList CreatListRl();     //��������β���뷨������ͷ���ĵ�����

LinkList CreatList(void);     //��������ͷ���뷨������ͷ���ĵ�����

ListNode* LocateNode();		 //��������ֵ���ҽ��

void DeleteList();     		 //������ɾ��ָ��ֵ�Ľ��

void printlist();    		 //��������ӡ�����е�����ֵ

void DeleteAll(); 			 //������ɾ�����н�㣬�ͷ��ڴ�

ListNode* AddNode();    //�޸ĳ���:���ӽڵ㡣��ͷ�巨������ͷָ��
