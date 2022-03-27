//#include <stdio.h>
//
//int main()
//{
//    int n = 0;
//    int arr[50] = { 0 };
//    scanf("%d", &n);
//    for (int i = 1; i <= n; i++)
//    {
//        scanf("%d", &arr[i]);
//    }
//    scanf("%d", &arr[0]);
//    for (int j = 0; j < n; j++)
//    {
//        if (arr[j] > arr[j + 1])
//        {
//            int tmp = arr[j];
//            arr[j] = arr[j + 1];
//            arr[j + 1] = tmp;
//        }
//        else
//            break;
//    }
//    for (int i = 0; i <= n; i++)
//    {
//        printf("%d ", arr[i]);
//    }
//
//    return 0;
//}

#include <stdio.h>

int main()
{
    int n = 0;
    int m = 0;
    int arr[100][100] = { 0 };
    int i = 0;
    int j = 0;
    scanf("%d %d", &n, &m);
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < m; j++)
        {
            scanf("%d", &arr[i][j]);
        }
    }
    int sum = 0;
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < m; j++)
        {
            if (arr[i][j] > 0)
                sum += arr[i][j];
        }
    }
    printf("%d", sum);

    return 0;
}