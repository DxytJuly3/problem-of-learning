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
/* ������
������ֻ��һ��ȫ�ֱ��� i
main������,forѭ���� i = 5��ʼ��һ��ѭ��,���� prt ����
����prt������,forѭ����i = 5��ʼ, ѭ������ ������� '*', i������ 8
prt�������ý������ٷ���main����forѭ���ĵ�һ��ѭ��
��ʱ i = 8, ��main������forѭ���� i �ٵ����� 9
i > 8, main������ѭ������������
����ֻ���һ�� '***'
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
/* ������
���������ȼ��ж�	*(�˺�) ���ȼ� 3		��= �� += ���ȼ� 14, �������������
���� ����˳��Ϊ
a * a
a -= a * a
a += a
�����
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
