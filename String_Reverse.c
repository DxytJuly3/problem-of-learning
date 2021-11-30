#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <string.h>

void back_chars(char* left, char* right)
{
	while (left < right)
	{
		int tmp = *left;
		*left = *right;
		*right = tmp;
		left++;
		right--;
	}
}

int main()
{
	char arr[100] = { 0 };
	gets(arr);
	int len = strlen(arr);
	char* left_arr = arr;
	char* right_arr = arr;

	back_chars(left_arr, right_arr + len - 1);		//首先把字符串全部逆置
	while (1)
	{
		right_arr++;
		if(*right_arr == ' ')
		{
			back_chars(left_arr, right_arr-1);
			left_arr = right_arr + 1;
		}
		if (*right_arr == '\0')
		{
			back_chars(left_arr, right_arr-1);
			break;
		}
	}
	printf("%s\n", arr);

	return 0;
}
