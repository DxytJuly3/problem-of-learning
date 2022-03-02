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
//	{// 进行 10 次循环 
//		ch = fgetc(pf);
//		printf("%c\n", ch);
//	}
//
//	//fseek(pf, 10, SEEK_CUR);	//使文件指针，从当前位置向后偏移 10 个字符
//	//fseek(pf, 15, SEEK_SET);	//使文件指针，从文件内容的首位，向后偏移 15 个字符
//	fseek(pf, -5, SEEK_END);	//使文件指针，从文件内容的末位，向后偏移 -5 个字符（向前偏移 5 个字符）
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