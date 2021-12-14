#include <stdio.h>
//老师给了小乐乐一个正整数序列，要求小乐乐把这个序列去重后按从小到大排序。但是老师给出的序列太长了，小乐乐没办法耐心的去重并排序，请你帮助他。
int main()
{
    int n = 0;
    int arr[100000] = { 0 };
    int i = 0;
    int tmp = 0;
    scanf("%d", &n);
    for (i = 0; i < n; i++)
    {
        scanf("%d", &tmp);		
        arr[tmp] = tmp;				//输入一个数，并把该数存入数组该数位 的位置
									//可保证输入相同的数 输入在同一位置，还可以保证 大数在后 小数在前，不用排序和查重
    }
    for (i = 0; i < 100000; i++)
    {
        if (arr[i] != 0)
            printf("%d ", arr[i]);
    }

    return 0;
}