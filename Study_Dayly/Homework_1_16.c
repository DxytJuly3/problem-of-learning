#define _CRT_SECURE_NO_WARNINGS 1

//#include <stdio.h>
//
//int main()
//{
//	int t = 0;
//    while ('0')
//    {
//        printf("*");
//        t++;
//        if (t < 3)
//            break;
//    }
//
//	return 0;
//}
//
//#include <stdio.h>
//static int k_count = 0;
//int GetNumberOfK(int* data, int dataLen, int k) {
//    int left = 0;
//    int right = dataLen - 1;
//    int len = 0;
//    if (k < *data || k > *(data + dataLen - 1) || data == NULL)
//        return 0;
//    else if (dataLen == 1 && *data == k)
//        return 1;
//    else if (*data == *(data + right))
//        return dataLen;
//    else
//    {
//        while (len != dataLen)
//        {
//            int mid = (left + right) / 2;
//            if (k > *(data + mid))
//                left = mid;
//            else if (k < *(data + mid))
//                right = mid - 1;
//            else
//            {
//                k_count++;
//                if (mid > 0)
//                    left = mid - 1;
//                if (mid < dataLen)
//                    right = mid + 1;
//                while (k == *(data + left))
//                {
//                    k_count++;
//                    if (left == 0)
//                        break;
//                    if (left != 0)
//                        left--;
//                }
//                while (k == *(data + right))
//                {
//                    k_count++;
//                    if (right == dataLen)
//                        break;
//                    if (right != dataLen)
//                        right++;
//                }
//                if (k_count != 0)
//                    return k_count;
//            }
//            len++;
//        }
//        return k_count;
//    }
//}
//int main()
//{
//    int arr[6] = { 3,3,3,3,4,5 };
//    int ret = GetNumberOfK(arr, 6, 3);
//    printf("%d", ret);
//
//	return 0;
//}
//
//#include <stdio.h>
//convertInteger(int A, int B)
//{
//    int returnNum = 0;
//    unsigned int tmp = A ^ B;
//    while (tmp != 0)
//    {
//        int ret = tmp & 1;
//        if (ret == 1)
//            returnNum++;
//        tmp = tmp >> 1;
//        
//    }
//}
//main()
//{
//    int a = 1429394115, b = -2122891310;
//    int ret = convertInteger(a, b);
//    printf("%d", ret);
//}

//#include <stdio.h>
//int dominantIndex(int* nums, int numsSize) {
//    if (numsSize == 1)
//        return 0;
//    int max = *nums;
//    int max_2 = *nums;
//    int returnSign = 0;
//    for (int i = 0; i < numsSize; i++)
//    {
//        if (*(nums + i) > max)
//        {
//            returnSign = i;
//            max = *(nums + i);
//        }
//        if (*(nums + i) > max_2 && *(nums + i) <= max)
//            max_2 = *(nums + i);
//    }
//    if (max - 2 * max_2 >= 0)
//        return returnSign;
//    else
//        return -1;
//
//}
//
//int main()
//{
//    int arr[] = { 6,6,1,0 };
//    int ret = dominantIndex(arr, 4);
//    printf("%d", ret);
//
//	return 0;
//}

#include <stdio.h>
#include <stdlib.h>

int* intersection(int* nums1, int nums1Size, int* nums2, int nums2Size/*, int* returnSize*/) {
    int len = nums1Size + nums2Size;
    int* returnNum = malloc(sizeof(int) * len);
    for (int i = 0; i < nums1Size; i++)
    {
        for (int j = 0; j < nums2Size; j++)
        {
            if (*(nums1 + i) == *(nums2 + j))
            {
                *(returnNum + i) = *(nums1 + i);
                break;
            }
        }
    }

    return returnNum;
}

int main()
{
    int arr1[] = { 1,2,2,1 };
    int arr2[] = { 2,2 };
    int* arr = intersection(arr1, 4, arr2, 2);

    return 0;
}