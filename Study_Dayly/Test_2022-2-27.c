#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>

struct Stu
{
	char name[20];
	int age;
	char sex[10];
};

int main()
{
	struct Stu stu[3] = {0};
	FILE* pf = fopen("data.txt", "rb");		//�Զ�����������ʽ���ļ�����ȡ�ļ�����ʽ��
	if (pf == NULL)
	{
		printf("���ļ�ʧ��\n");
		return 0;
	}
	fread(&stu, sizeof(struct Stu), 3, pf);

	printf("%s %d %s\n", stu[0].name, stu[0].age, stu[0].sex);
	printf("%s %d %s\n", stu[1].name, stu[1].age, stu[1].sex);
	printf("%s %d %s\n", stu[2].name, stu[2].age, stu[2].sex);

	fclose(pf);
	pf = NULL;

	return 0;
}