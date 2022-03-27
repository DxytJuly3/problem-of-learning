#define _CRT_SECURE_NO_WARNINGS 1

//#include <stdio.h>
//int i;
//void prt()
//{
//    for (i = 5; i < 8; i++)
//        printf("%c", '*');
//    printf("\t");
//}
//int main()
//{
//    for (i = 5; i <= 8; i++)
//        prt();
//
//    return 0;
//}
/* 解析：
代码中只有一个全局变量 i
main函数中,for循环从 i = 5开始第一次循环,调用 prt 函数
进入prt函数中,for循环从i = 5开始, 循环三次 输出三个 '*', i递增至 8
prt函数调用结束，再返回main函数for循环的第一次循环
此时 i = 8, 在main函数的for循环中 i 再递增至 9
i > 8, main函数中循环条件不成立
所以只输出一次 '***'
*/


//#include <stdio.h>
//
//int main()
//{
//	int a = 248, b = 4;
//	int const* c = 21;
//	const int* d = &a;
//	int* const e = &b;
//	int const* const f = &a;
//
//	return 0;
//}


//#include <stdio.h>
//
//int main()
//{
//    int a = 3;
//    printf("%d\n", (a += a -= a * a));
//
//    return 0;
//}
/* 解析：
操作符优先级判断	*(乘号) 优先级 3		—= 和 += 优先级 14, 但从右向左计算
所以 计算顺序为
a * a
a -= a * a
a += a
结果是
a -= 9		a ==> -6
a += a		a ==> -12
*/

#include <stdio.h>

//int minNumberInRotateArray(int* arr, int arrSize)
//{
//    int left = 0;
//    int right = arrSize - 1;
//    while (left < right)
//    {
//        int mid = (left + right) / 2;
//        if (arr[mid] < arr[right])
//            right = mid;
//        else if (arr[mid] > arr[right])
//            left = mid + 1;
//        else
//            right -= 1;
//    }
//    return arr[left];
//}


//int minNumberInRotateArray(int* rotateArray, int rotateArrayLen)
//{
//    int left = 0;
//    int right = rotateArrayLen - 1;
//    while (left < right)
//    {
//        int mid = (left + right) / 2;
//        if (*(rotateArray + mid) < *(rotateArray + right))
//            right = mid;
//        else if (*(rotateArray + mid) > *(rotateArray + right))
//            left = mid + 1;
//        else
//            right--;
//    }
//
//    return *(rotateArray + left);
//}
//
//int main()
//{
//    int arr1[5] = { 1,0,1,1,1 };
//    int ret = minNumberInRotateArray(arr1, 5);
//    printf("%d", ret);
//
//    return 0;
//}
