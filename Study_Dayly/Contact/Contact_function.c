#define _CRT_SECURE_NO_WARNINGS 1

#include "Contact.h"

// �˵�����
void menu()
{
	printf("*******************************************\n");
	printf("*                 ͨѶ¼                  *\n");
	printf("*******************************************\n");
	printf("*****  1.�����ϵ��	2.ɾ����ϵ��  *****\n");
	printf("*****  3.������ϵ��	4.�޸���ϵ��  *****\n");
	printf("*****  5.����������	6.��ʾͨѶ¼  *****\n");
	printf("*****  0.�˳�ͨѶ¼                   *****\n");
	printf("*******************************************\n");
}

// �˳�����
void exits()
{
	printf("�����˳�ͨѶ¼\n");
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
	printf("�˳��ɹ�\n");
	Sleep(1000);
}

// ��ʼ��ͨѶ¼����
void InitCon(Contact* con)
{
	assert(con);
	memset(con->Info, 0, sizeof(con->Info));
	con->peo_num = 0;
}

// �����ϵ�˺���
void AddPeople(Contact* con)
{
	assert(con);
	if (con->peo_num == Peo_Max)
	{
		printf("ͨѶ¼�������޷����\n");
		return;
	}
	printf("��������ϵ������:>");
	scanf("%s", con->Info[con->peo_num].name);
	printf("��������ϵ������:>");
	scanf("%d", &(con->Info[con->peo_num].age));
	printf("��������ϵ���Ա�:>");
	scanf("%s", con->Info[con->peo_num].sex);
	printf("��������ϵ�˵绰:>");
	scanf("%s", con->Info[con->peo_num].tele);
	printf("��������ϵ��סַ:>");
	scanf("%s", con->Info[con->peo_num].addr);

	con->peo_num++;
	printf("�����ϵ�˳ɹ�\n");
}

// ��ʾͨѶ¼����
void ShowContact(const Contact* con)
{
	assert(con);
	printf("%-4s\t%-4s\t%-4s\t%-15s\t%s\t\n", "����", "�Ա�", "����", "�绰", "��ͥסַ");
	for (int i = 0; i < con->peo_num; i++)
	{
		printf("%-4s\t%-4s\t%-4d\t%-15s\t%s\t\n",
			con->Info[i].name , con->Info[i].sex, con->Info[i].age, con->Info[i].tele, con->Info[i].addr);
	}
}