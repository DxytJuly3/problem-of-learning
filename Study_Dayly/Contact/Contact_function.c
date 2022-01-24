#define _CRT_SECURE_NO_WARNINGS 1

#include "Contact.h"

// 菜单函数
void menu()
{
	printf("*******************************************\n");
	printf("*                 通讯录                  *\n");
	printf("*******************************************\n");
	printf("*****  1.添加联系人	2.删除联系人  *****\n");
	printf("*****  3.查找联系人	4.修改联系人  *****\n");
	printf("*****  5.按名字排序	6.显示通讯录  *****\n");
	printf("*****  0.退出通讯录                   *****\n");
	printf("*******************************************\n");
}

// 退出函数
void exits()
{
	printf("正在退出通讯录\n");
	printf(". ");
	Sleep(1000);
	printf(". ");
	Sleep(1000);
	printf(". ");
	Sleep(1000);
	printf(". ");
	Sleep(1000);
	printf(". \n");
	Sleep(1000);
	printf("退出成功\n");
	Sleep(1000);
}

// 初始化通讯录函数
void InitCon(Contact* con)
{
	assert(con);
	memset(con->Info, 0, sizeof(con->Info));
	con->peo_num = 0;
}

// 添加联系人函数
void AddPeople(Contact* con)
{
	assert(con);
	if (con->peo_num == Peo_Max)
	{
		printf("通讯录已满，无法添加\n");
		return;
	}
	printf("请输入联系人姓名:>");
	scanf("%s", con->Info[con->peo_num].name);
	printf("请输入联系人年龄:>");
	scanf("%d", &(con->Info[con->peo_num].age));
	printf("请输入联系人性别:>");
	scanf("%s", con->Info[con->peo_num].sex);
	printf("请输入联系人电话:>");
	scanf("%s", con->Info[con->peo_num].tele);
	printf("请输入联系人住址:>");
	scanf("%s", con->Info[con->peo_num].addr);

	con->peo_num++;
	printf("添加联系人成功\n");
}

// 显示通讯录函数
void ShowContact(const Contact* con)
{
	assert(con);
	printf("%-4s\t%-4s\t%-4s\t%-15s\t%s\t\n", "姓名", "性别", "年龄", "电话", "家庭住址");
	for (int i = 0; i < con->peo_num; i++)
	{
		printf("%-4s\t%-4s\t%-4d\t%-15s\t%s\t\n",
			con->Info[i].name , con->Info[i].sex, con->Info[i].age, con->Info[i].tele, con->Info[i].addr);
	}
}