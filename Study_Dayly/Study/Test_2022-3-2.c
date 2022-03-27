#define _CRT_SECURE_NO_WARNINGS 1

//#include <stdio.h>
//#include <string.h>
//#include <errno.h>
//
//int main()
//{
//	FILE* pf = fopen("D:\\TEST.txt", "r");
//	if (pf == NULL)
//	{
//		printf("fopen::%s", strerror(errno));
//		return 0;
//	}
//	int ch = 0;
//	for (int i = 0; i < 10; i++)
//	{// ���� 10 ��ѭ�� 
//		ch = fgetc(pf);
//		printf("%c\n", ch);
//	}
//
//	//fseek(pf, 10, SEEK_CUR);	//ʹ�ļ�ָ�룬�ӵ�ǰλ�����ƫ�� 10 ���ַ�
//	//fseek(pf, 15, SEEK_SET);	//ʹ�ļ�ָ�룬���ļ����ݵ���λ�����ƫ�� 15 ���ַ�
//	fseek(pf, -5, SEEK_END);	//ʹ�ļ�ָ�룬���ļ����ݵ�ĩλ�����ƫ�� -5 ���ַ�����ǰƫ�� 5 ���ַ���
//
//	ch = fgetc(pf);
//	printf("ch = %c\n", ch);
//
//	fclose(pf);
//	pf = NULL;
//
//	return 0;
//}

#include <stdio.h>
#include <string.h>
#include <errno.h>

int main()
{
	FILE* pf = fopen("D:\\TEST.txt", "r");
	if (pf == NULL)
	{
		printf("fopen::%s", strerror(errno));
		return 0;
	}
	int ch = 0;

	ch = fgetc(pf);
	printf("%c\n", ch);

	ch = fgetc(pf);
	printf("%c\n", ch);

	long ret = ftell(pf);
	printf("%ld\n", ret);

	rewind(pf);
	ret = ftell(pf);
	printf("%ld\n", ret);

	fclose(pf);
	pf = NULL;

	return 0;
}