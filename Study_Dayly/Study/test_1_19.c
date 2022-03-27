#define _CRT_SECURE_NO_WARNINGS 1

//#include <stdio.h>
//int main()
//{
//	char* a[] = { "work","at","alibaba" };
//	char** pa = a;
//	pa++;
//	printf("%s\n", *pa);
//	return 0;
//}

//#include <stdio.h>
//
//int main()
//{
//	char* c[] = { "ENTER","NEW","POINT","FIRST" };
//	char** cp[] = { c + 3,c + 2,c + 1,c };		//"FIRST" "POINT" "NEW" "ENTER"
//	char*** cpp = cp;
//
//	printf("%s\n", **++cpp);		//"POINT"
//	printf("%s\n", *-- * ++cpp + 3);	//
//	printf("%s\n", *cpp[-2] + 3);	//
//	printf("%s\n", cpp[-1][-1] + 1);	//
//	return 0;
//}

//#include <stdio.h>
//
//int cmp_int(const void* e1, const void* e2)
//{
//	return (*(int*)e1 - *(int*)e2);
//}
//
//void print(int* arr, int sz)
//{
//	for (int i = 0; i < sz; i++)
//	{
//		printf("%d ", *(arr + i));
//	}
//}
//
//void bubble(int* arr, int sz)
//{
//	for (int i = 0; i < sz - 1; i++)
//	{
//		for (int j = 0; j < sz - 1 - i; j++)
//		{
//			if (arr[j] > arr[j + 1])
//			{
//				int tmp = arr[j + 1];
//				arr[j + 1] = arr[j];
//				arr[j] = tmp;
//			}
//		}
//	}
//}
//
//void Swap(char* e1, char* e2, int width)
//{
//	for (int i = 0; i < width; i++)
//	{
//		char tmp = *(e1 + i);
//		*(e1 + i) = *(e2 + i);
//		*(e2 + i) = tmp;
//	}
//}
//
//void bubble_sort(void* base, int sz, int width, int (*cmp)(void*,void*))
//{
//	for (int i = 0; i < sz - 1; i++)
//	{
//		for (int j = 0; j < sz - 1 - i; j++)
//		{
//			if (cmp( (char*)base + j * width, (char*)base + (j + 1) * width ) > 0)
//			{
//				Swap((char*)base + j * width, (char*)base + (j + 1) * width, width);
//			}
//		}
//	}
//}
//
//int main()
//{
//	int arr[] = { 3,5,1,7,2,7,2,8,0,3,9,3,1,4,9,5,6,2 };
//	int sz = sizeof(arr) / sizeof(arr[0]);
//	bubble_sort(arr, sz, sizeof(arr[0]), cmp_int);
//	//bubble(arr, sz);
//	print(arr, sz);
//
//	return 0;
//}

#include <stdio.h>
#include <string.h>

struct Student
{
	char name[20];
	int age;
	double score;
};

int cmp_int(const void* e1, const void* e2)
{
	return (*(int*)e1 - *(int*)e2);
}
int cmp_char(const void* e1, const void* e2)
{
	return (*(char*)e1 - *(char*)e2);
}
int cmp_student_score(const void* e1, const void* e2)
{
	if (((struct Student*)e1)->score > ((struct Student*)e2)->score)
		return 1;
	else if (((struct Student*)e1)->score < ((struct Student*)e2)->score)
		return -1;
	else
		return 0;
}
int cmp_student_age(const void* e1, const void* e2)
{
	return ((struct Student*)e1)->age - ((struct Student*)e2)->age;
}
int cmp_student_name(const void* e1, const void* e2)
{
	return strcmp(((struct Student*)e1)->name, ((struct Student*)e2)->name);
}

void print_student(struct Student arr[], int sz)
{
	int i = 0;
	for (i = 0; i < sz; i++)
	{
		printf("%s %d %.2lf\n", arr[i].name, arr[i].age, arr[i].score);
	}
	printf("\n");
}

void print(int* arr, int sz)
{
	for (int i = 0; i < sz; i++)
	{
		printf("%d ", *(arr + i));
	}
	printf("\n");
}

int main()
{
	int arr[] = { 2,4,1,7,9,4,1,4,7,3,6,4,7,2,0,9,5,2,5,8,1,3,6 };
	int sz_arr = sizeof(arr) / sizeof(arr[0]);
	char chs[] = "yhdi5kf765lk,89fgjhwe7654jnfguflsuih89";
	int len_chs = strlen(chs);
	struct Student bit[] = { {"222", 21, 66.6}, {"111", 20, 99.9}, {"444", 22, 33.3}, {"333", 19, 77.7}, {"123", 23, 55.5} };
	int sz_bit = sizeof(bit) / sizeof(bit[0]);
	qsort(arr, sz_arr, sizeof(arr[0]), cmp_int);	//整型 快排
	print(arr, sz_arr);
	qsort(chs, len_chs, sizeof(chs[0]), cmp_char);	//字符串 快排
	printf("%s\n", chs);
	qsort(bit, sz_bit, sizeof(bit[0]), cmp_student_age);	// 结构体 整型 快排
	print_student(bit, sz_bit);
	qsort(bit, sz_bit, sizeof(bit[0]), cmp_student_name);	// 结构体 字符串 快排
	print_student(bit, sz_bit);
	qsort(bit, sz_bit, sizeof(bit[0]), cmp_student_score);	// 结构体 双浮点数 快排
	print_student(bit, sz_bit);

	return 0;
}