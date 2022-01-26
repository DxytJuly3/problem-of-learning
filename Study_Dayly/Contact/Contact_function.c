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
	printf("*****  7.清空通讯录	0.退出通讯录  *****\n");
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
	printf(". \n");
	Sleep(500);
	printf("退出成功\n");
	Sleep(1000);
}

int cmp_name(const void* elem1, const void* elem2)
{
	if (strcmp(((Contact*)elem1)->Info->name, ((Contact*)elem2)->Info->name) > 0)
		return 1;
	else
		return 0;;
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
	printf("请输入联系人备注:>");
	scanf("%s", con->Info[con->peo_num].remark);
	printf("请输入联系人年龄:>");
	scanf("%d", &(con->Info[con->peo_num].age));
	printf("请输入联系人性别:>");
	scanf("%s", con->Info[con->peo_num].sex);
	printf("请输入联系人电话:>");
	scanf("%s", con->Info[con->peo_num].tele);
	printf("请输入联系人住址:>");
	scanf("%s", con->Info[con->peo_num].addr);

	con->peo_num++;
	printf("添加联系人成功\n\n");
}

// 显示通讯录函数
void ShowContact(const Contact* con)
{
	assert(con);
	printf("%-4s\t%-4s\t%-4s\t%-15s\t%s\t\n", "姓名(备注)", "性别", "年龄", "电话", "家庭住址");
	for (int i = 0; i < con->peo_num; i++)
	{
		printf("%-4s(%s) \t%-4s\t%-4d\t%-15s\t%s\t\n",
			con->Info[i].name ,con->Info[i].remark, con->Info[i].sex, con->Info[i].age, con->Info[i].tele, con->Info[i].addr);
	}
	printf("\n");
}

// 简单的查找联系人函数
int SearchPeoByName(Contact* con, char* searchname)
{
	for (int i = 0; i < con->peo_num; i++)
	{
		if (strcmp(con->Info[i].name, searchname) == 0)
			return i;
	}

	return -1;
}

// 删除联系人函数
void DelePeopel(Contact* con)
{
	char delename[Name_Max] = { 0 };
	if (con->peo_num == 0)
	{
		printf("通讯录为空，无法删除\n\n");
		return;
	}
	printf("请输入要删除的联系人:>");
	scanf("%s", delename);
	int peo_n = SearchPeoByName(con, delename);
	if (peo_n == -1)
		printf("查无此人，无法删除\n\n");
	else
	{
		for (int i = peo_n; i < con->peo_num - 1; i++)
		{
			con->Info[i] = con->Info[i + 1];	//同类型结构体 可以直接赋值
		}
		con->peo_num--;
		printf("删除指定联系人成功\n\n");
	}
}

// 查找联系人并输出函数
void SearchPeo(Contact* con)
{
	char SearchPeo_name[Name_Max];
	if (con->peo_num == 0)
	{
		printf("通讯录为空，无法查找\n\n");
		return;
	}
	printf("请输入要查找的联系人:>");
	scanf("%s", SearchPeo_name);
	int peo_n = SearchPeoByName(con, SearchPeo_name);
	if (peo_n == -1)
		printf("抱歉，查无此人\n\n");
	else
	{
		printf("%-4s\t%-4s\t%-4s\t%-15s\t%s\t\n", "姓名(备注)", "性别", "年龄", "电话", "家庭住址");
		printf("%-4s(%s)\t%-4s\t%-4d\t%-15s\t%s\t\n\n",
			con->Info[peo_n].name, con->Info[peo_n].remark,
			con->Info[peo_n].sex, con->Info[peo_n].age, 
			con->Info[peo_n].tele, con->Info[peo_n].addr);
	}
}
// 修改联系人
void ModifyPeo(Contact* con)
{
	char SearchPeo_name[Name_Max];
	if (con->peo_num == 0)
	{
		printf("通讯录为空，无法修改\n\n");
		return;
	}
	printf("请输入要修改的联系人:>");
	scanf("%s", SearchPeo_name);
	int peo_n = SearchPeoByName(con, SearchPeo_name);
	if (peo_n == -1)
		printf("抱歉，查无此人\n\n");
	else
	{
		char flag = 0;
		printf("%-4s\t%-4s\t%-4s\t%-15s\t%s\t\n", "姓名(备注)", "性别", "年龄", "电话", "家庭住址");
		printf("%-4s(%s)\t%-4s\t%-4d\t%-15s\t%s\t\n\n",
			con->Info[peo_n].name, con->Info[peo_n].remark,
			con->Info[peo_n].sex, con->Info[peo_n].age,
			con->Info[peo_n].tele, con->Info[peo_n].addr);
		printf("是否修改？(y/n)\n");
		getchar();
		flag = getchar();
		if (flag == 'y')
		{
			printf("请输入联系人姓名:>");
			scanf("%s", con->Info[peo_n].name);
			printf("请输入联系人备注:>");
			scanf("%s", con->Info[peo_n].remark);
			printf("请输入联系人年龄:>");
			scanf("%d", &(con->Info[peo_n].age));
			printf("请输入联系人性别:>");
			scanf("%s", con->Info[peo_n].sex);
			printf("请输入联系人电话:>");
			scanf("%s", con->Info[peo_n].tele);
			printf("请输入联系人住址:>");
			scanf("%s", con->Info[peo_n].addr);
		}
		else
			return;
		printf("修改成功\n\n");
	}
}
// 通讯录按名字排序函数
void SortContact_Name(Contact* con)
{
	qsort(con->Info, (con->peo_num), sizeof(PeoInfo), cmp_name);
	printf("已按照名字首字母排序\n\n");
}
// 清空通讯录函数
void ClearContact(Contact* con)
{
	InitCon(con);
	printf("通讯录已清空\n\n");
}