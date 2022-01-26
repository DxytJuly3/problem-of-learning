#define _CRT_SECURE_NO_WARNINGS 1

#include "Contact.h"

int main()
{
	int input = 0;
	Contact Con;
	InitCon(&Con);		//初始化通讯录
	do 
	{
		menu();
		printf("请选择:>");
		scanf("%d", &input);
		switch (input)
		{
		case 1:
			AddPeople(&Con);	//添加联系人
			break;
		case 2:
			DelePeopel(&Con);	//删除联系人
			break;
		case 3:
			SearchPeo(&Con);	//查找联系人
			break;
		case 4:
			ModifyPeo(&Con);	//修改联系人
			break;
		case 5:
			SortContact_Name(&Con);	//通讯录排序
			break;
		case 6:
			ShowContact(&Con);	//显示通讯录
			break;
		case 7:
			ClearContact(&Con);	//清空通讯录
			break;
		case 0:
			exits();			//退出通讯录
			break;
		default:
			printf("选择错误,请重新选择\n");
			break;
		}

	} while (input);

	return 0;
}