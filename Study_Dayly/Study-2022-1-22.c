#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <assert.h>
#include <string.h>

// strlen 模拟实现
int my_strlen(const char* string)
{
	int count = 0;
	while (*string++)
	{
		count++;
	}

	return count;
}

// strcpy 模拟实现
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

// strcmp 模拟实现
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

// strcat 模拟实现
char* my_strcat(char* dest, const char* src)
{
	char* ret = dest;
	assert(dest && src);

	while (*dest)
	{// 不能在循环判断条件里 加 "++"， 不然会跳过 目标字符串中的'/0'
		dest++;
	}

	while (*dest++ = *src++)
	{
		;
	}

	return ret;
}

// strstr 模拟实现
char* my_strstr(const char* str, const char* substr)
{
	assert(str && substr);
	if (*substr == '\0')
		return (char*)str;
	char* flag = (char*)str;	//记录本次查找的起始地址
	char* str1;
	char* str2;					//记录 查找的字符串

	while (*flag)
	{
		str1 = flag;			//因本次查找中 起始位置需要一直知道，所以将 flag 存入另一个指针变量
		str2 = (char*)substr;	//每次循环从 查找字符串的首字符开始查找
		while (*str1 && *str2 && !(*str1 - *str2))
		{/*在此循环中查找，str1 与 str2 指向的字符都不为'\0'，且 相等时，继续查找下一个字符
		   str2指向的字符为'\0'时，查找成功
		   两字符相减等于0 即相等*/
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
	/*	验证 my_strstr
	char arr1[] = "abcdefgabcdefg";
	char arr2[] = "defg";
	char* ret = my_strstr(arr1, arr2);
	if (ret)
		printf("%s\n", ret);
	else
		printf("没找到\n");*/

	/*	验证 my_strcat
	char arr1[20] = "asdasdasd";
	char arr2[] = "fghfghfgh";
	my_strcat(arr1, arr2);
	printf("%s\n", arr1);*/

	
	/*	验证 my_strcmp
	char arr1[] = "123aaafffghj";
	char arr2[] = "123aaafffghy";
	int ret = my_strcmp(arr1, arr2);
	if (ret == 0)
		printf("arr1 等于 arr2\n");
	else if (ret > 0)
		printf("arr1 大于 arr2\n");
	else
		printf("arr1 小于 arr2\n");*/

	/*	验证 my_strlen
	char arr[] = "auihgiosjfihobdf";
	int len = my_strlen(arr);
	printf("%d", len);*/

	/*	验证 my_strcpy
	char arr1[] = "Dxyt-July3";
	char arr2[20] = { 0 };
	my_strcpy(arr2, arr1);
	printf("%s\n", arr2);*/

	return 0;
}
