#define _CRT_SECURE_NO_WARNINGS 1

#include "Contact.h"

int main()
{
	int input = 0;
	Contact Con;
	InitCon(&Con);		//��ʼ��ͨѶ¼
	do 
	{
		menu();
		printf("��ѡ��:>");
		scanf("%d", &input);
		switch (input)
		{
		case 1:
			AddPeople(&Con);
			break;
		case 2:
			break;
		case 3:
			break;
		case 4:
			break;
		case 5:
			break;
		case 6:
			ShowContact(&Con);
			break;
		case 0:
			exits();
			break;
		default:
			printf("ѡ�����,������ѡ��\n");
			break;
		}

	} while (input);

	return 0;
}