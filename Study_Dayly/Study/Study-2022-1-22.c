#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <assert.h>
#include <string.h>

// strlen ģ��ʵ��
int my_strlen(const char* string)
{
	int count = 0;
	while (*string++)
	{
		count++;
	}

	return count;
}

// strcpy ģ��ʵ��
char* my_strcpy(char* dest, const char* src)
{
	char* ret = dest;
	assert(dest && src);

	while (*dest++ = *src++)
	{
		;
	}

	return ret;
}

// strcmp ģ��ʵ��
int my_strcmp(const char* str1, const char* str2)
{
	int ret = 0;
	assert(str1 && str2);

	while ( !(ret = *str1 - *str2) && *str2)
	{
		str1++;
		str2++;
	}

	return ret;
}

// strcat ģ��ʵ��
char* my_strcat(char* dest, const char* src)
{
	char* ret = dest;
	assert(dest && src);

	while (*dest)
	{// ������ѭ���ж������� �� "++"�� ��Ȼ������ Ŀ���ַ����е�'/0'
		dest++;
	}

	while (*dest++ = *src++)
	{
		;
	}

	return ret;
}

// strstr ģ��ʵ��
char* my_strstr(const char* str, const char* substr)
{
	assert(str && substr);
	if (*substr == '\0')
		return (char*)str;
	char* flag = (char*)str;	//��¼���β��ҵ���ʼ��ַ
	char* str1;
	char* str2;					//��¼ ���ҵ��ַ���

	while (*flag)
	{
		str1 = flag;			//�򱾴β����� ��ʼλ����Ҫһֱ֪�������Խ� flag ������һ��ָ�����
		str2 = (char*)substr;	//ÿ��ѭ���� �����ַ��������ַ���ʼ����
		while (*str1 && *str2 && !(*str1 - *str2))
		{/*�ڴ�ѭ���в��ң�str1 �� str2 ָ����ַ�����Ϊ'\0'���� ���ʱ������������һ���ַ�
		   str2ָ����ַ�Ϊ'\0'ʱ�����ҳɹ�
		   ���ַ��������0 �����*/
			str1++;
			str2++;
		}
		if (*str2 == '\0')
			return flag;

		flag++;
	}

	return NULL;
}

int main()
{
	/*	��֤ my_strstr
	char arr1[] = "abcdefgabcdefg";
	char arr2[] = "defg";
	char* ret = my_strstr(arr1, arr2);
	if (ret)
		printf("%s\n", ret);
	else
		printf("û�ҵ�\n");*/

	/*	��֤ my_strcat
	char arr1[20] = "asdasdasd";
	char arr2[] = "fghfghfgh";
	my_strcat(arr1, arr2);
	printf("%s\n", arr1);*/

	
	/*	��֤ my_strcmp
	char arr1[] = "123aaafffghj";
	char arr2[] = "123aaafffghy";
	int ret = my_strcmp(arr1, arr2);
	if (ret == 0)
		printf("arr1 ���� arr2\n");
	else if (ret > 0)
		printf("arr1 ���� arr2\n");
	else
		printf("arr1 С�� arr2\n");*/

	/*	��֤ my_strlen
	char arr[] = "auihgiosjfihobdf";
	int len = my_strlen(arr);
	printf("%d", len);*/

	/*	��֤ my_strcpy
	char arr1[] = "Dxyt-July3";
	char arr2[20] = { 0 };
	my_strcpy(arr2, arr1);
	printf("%s\n", arr2);*/

	return 0;
}
