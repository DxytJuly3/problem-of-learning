//今天是圣诞节，牛牛要打印一个漂亮的圣诞树送给想象中的女朋友，请你帮助他实现梦想。

//输入：1
//输出：
//        *  
//       * * 
//      * * *
//        *
#include<stdio.h>

int main() 
{
    int h;
    scanf("%d", &h);
    for (int H = 1; H <= h; H++)
    {
        if (H != 1)
        {
            printf("\n");
        }
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 2 - i; j++)
            {
                printf(" ");
            }
            for (int m = 0; m < 3 * (h - H); m++)
            {
                printf(" ");
            }
            for (int k = 0; k < i + 1; k++)
            {
                printf("* ");
            }
            for (int y = 1; y < H; y++)
            {
                for (int z = 0; z < 2; z++)
                {
                    for (int j = 0; j < 2 - i; j++)
                    {
                        printf(" ");
                    }
                }
                for (int k = 0; k < i + 1; k++)
                {
                    printf("* ");
                }
            }
            if (i < 2)
            {
                printf("\n");
            }
        }
    }
    printf("\n");
    for (int p = 0; p < h; p++)
    {//树干
        for (int m = 0; m < 2 + 3 * (h - 1); m++)
        {
            printf(" ");
        }
        printf("*\n");
    }
}