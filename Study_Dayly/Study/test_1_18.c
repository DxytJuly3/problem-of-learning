#define _CRT_SECURE_NO_WARNINGS 1
//
//#include <stdio.h>
//#include <string.h>
//
//int main() {
//
//	/*int arr[4] = { 1,2,3,4 };
//	int* prt2 = (int*)((int)arr + 1);
//
//	printf("%x", *prt2);*/
//	/*int arr[3][2] = { (0,1), (1,2), (2,3) };
//	int* p;
//	p = arr[0];
//	printf("%d", p[0]);*/
//	int a[5][5];
////	[][][][][][][][][][][][][][][][][][][][][][] [][][]
////	[][][][][][][][][][][][][][][][][][] [][][][][][][]
//	int(*p)[4];
//	p = a;
//	printf("%p, %d", &p[4][2] - &a[4][2], &p[4][2] - &a[4][2]);
//
//
//	return 0;
//}

//#include <stdio.h>
//
//print(char* s);
//
//int main()
//{
//    char str[] = "Geneius";
//    print(str);
//    return 0;
//}
//print(char* s)
//{
//    if (*s)
//    {
//        print(++s);
//        printf("%c", *s);
//    }
//}

//#include <stdio.h>
//int fun(int x)
//{
//	return (x == 1) ? 1 : (x + fun(x - 1));
//}
//int main()
//{
//	int ret = fun(10);
//	printf("%d", ret);
//
//	return 0;
//}

//#include <stdio.h>
//#include <string.h>
//
//int cmp_char(const void* a, const void* b)
//{
//    return (*(char*)a - *(char*)b);
//}
//
//int main()
//{
//    char chs[1025] = { 0 };
//    while (gets(chs) != EOF)
//    {
//        int ch_len = strlen(chs);
//        qsort(chs, ch_len, sizeof(chs[0]), cmp_char);
//        printf("%s\n", chs);
//    }
//
//    return 0;
//}

#include <stdio.h>



int pivotIndex(int* nums, int numsSize)
{
    for (int i = 0; i < numsSize; i++)
    {//从中心点为 0 开始，计算左右两边和
        int sum_left = 0;
        int sum_right = 0;
        for (int j = 0; j < numsSize; j++)
        {//i 每递增一次  左边多一个元素，右边少一个元素
            if (j < i)//小于i  的都是左元素
                sum_left += *(nums + j);
            else if (j > i)//大于i  的都是右元素
                sum_right += *(nums + j);
        }
        if (sum_right == sum_left)
            return i;
    }

    return -1;
}

int main()
{
    int arr[] = { -1,-1,-1,-1,-1,-1 };
    int ret = pivotIndex(arr, 6);
    printf("%d", ret);

    return 0;
}

