#define _CRT_SECURE_NO_WARNINGS 1

//#include <stdio.h>

//int main()
//{
//	int n = 0;
//	char ch = 0;
//	for (ch = getchar(); ch != '\n'; n++)
//	{
//	
//	}
//	printf("%d", n);
//
//	return 0;
//}
////A:n=0; while (ch = getchar() != '\n')n++;		B:n=0; while (getchar() != '\n')n++;
//
////C:for(n = 0; getchar() != '\n'; n++);			D:n=0; for (ch = getchar(); ch != '\n'; n++);

//int main()
//{
//    int m, n;
//    printf("Enter m,n;");
//    scanf("%d%d", &m, &n);
//    while (m != n)          //1
//    {
//        while (m > n) m = m - n; //2
//        while (n > m) n = n - m; //3
//    }
//    printf("m=%d\n", m);
//
//    return 0;
//}
/* 解析：
m = 64, n = 14
m > n: m = m - n == 64 - 14 = 50	m === 50	n === 14
m > n: m = m - n == 50 - 14 = 36	m === 36	n === 14
m > n: m = m - n == 36 - 14 = 22	m === 22	n === 14
m > n: m = m - n == 22 - 14 = 8		m === 8		n === 14
m < n: n = n - m == 14 - 8 = 6		m === 8		n === 6
m > n: m = m - n == 8 - 6 = 2		m === 2		n === 6
m < n: n = n - m == 6 - 2 = 4		m === 2		n === 4
m < n: n = n - m == 4 - 2 = 2		m === 2		n === 2
所以输出 m = 2
*/

//#include <stdio.h> 
//int main()
//{
//    char c;
//    int v0 = 0, v1 = 0, v2 = 0;
//        do
//        {
//            switch (c = getchar())
//            {
//            case'a':case'A':
//            case'e':case'E':
//            case'i':case'I':
//            case'o':case'O':
//            case'u':case'U':v1 += 1;
//            default:
//                    v0 += 1; 
//                    v2 += 1;
//            }
//        } while (c != '\n');
//        printf("v0=%d,v1=%d,v2=%d\n", v0, v1, v2);
//        return 0;
//}
/* 解析：
输入 'A' 'E' 'I' 'O' 'U' 'a' 'e' 'i' 'o' 'u' 	v0, v1, v2 均加一
输入其他	v0, v2 加一
*/

//#include <stdio.h>
//
//int main()
//{
    /*int a[] = { 4, 0, 2, 3, 1 }, i, j, t;
    for (i = 1; i < 5; i++)
    {
        t = a[i];
        j = i - 1;
        while (j >= 0 && t < a[j])
        {
            a[j + 1] = a[j];
            --j;
        }
        a[j + 1] = t;
    }*/
//}

//#include <stdio.h>
//
//int main()
//{
//	for (int i = 0; i <= 5 - 1; i++)   // (1)
//		for (int j = 5; j > i; j--)  // (2)
//			printf("bit\n");       // (3)
//	// 5 
//
//	return 0;
//}
#include <stdio.h>

int returnNum[2] = { 0 };
void sort(int* nums, int numsSize)
{
    int i, j, t;
    for (i = 1; i < numsSize; i++)
    {
        t = nums[i];
        j = i - 1;
        while (j >= 0 && t < nums[j])
        {
            nums[j + 1] = nums[j];
            --j;
        }
        nums[j + 1] = t;
    }
}
void/*int*/ findErrorNums(int* nums, int numsSize/*, int* returnSize*/)
{
    sort(nums, numsSize);
    int* first = nums;
    int count = 0;
    if (*nums == *(nums + 1))
        returnNum[0] = *nums;
    while (*nums != *(nums + 1))
    {
        nums++;
        if (*nums == *(nums + 1))
        {
            returnNum[0] = *nums;
            break;
        }
    }
    nums = first;
    while (count < numsSize)
    {
        if (*(nums + 1) - *nums == 2)
        {
            returnNum[1] = *nums + 1;
            break;
        }
        nums++;
        count++;
    }
    nums = first;
    if (*nums != 1)
        returnNum[1] = 1;
    else if (*(nums + numsSize - 1) != numsSize)
        returnNum[1] = numsSize;

    //return returnNum;
}

int main()
{
    int arr[4] = { 1,2,2,4 };
    // 1,3,4,5,5,6
    findErrorNums(arr, 4);
    printf("%d", returnNum[0]);
    printf("%d", returnNum[1]);

    return 0;
}