#pragma once
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct node ListNode;   //定义结点


typedef ListNode* LinkList; //自定义LinkList单链表类型

LinkList CreatListRl();     //函数，用尾插入法建立带头结点的单链表

LinkList CreatList(void);     //函数，用头插入法建立带头结点的单链表

ListNode* LocateNode();		 //函数，按值查找结点

void DeleteList();     		 //函数，删除指定值的结点

void printlist();    		 //函数，打印链表中的所有值

void DeleteAll(); 			 //函数，删除所有结点，释放内存

ListNode* AddNode();    //修改程序:增加节点。用头插法，返回头指针
