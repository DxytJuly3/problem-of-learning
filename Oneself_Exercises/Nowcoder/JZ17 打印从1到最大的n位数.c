//输入数字 n，按顺序打印出从 1 到最大的 n 位十进制数。比如输入 3，则打印出 1、2、3 一直到最大的 3 位数 999。
//1. 用返回一个整数列表来代替打印
//2. n 为正整数

/**
 * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
 *
 * 
 * @param n int整型 最大位数
 * @return int整型一维数组
 * @return int* returnSize 返回数组行数
 *
 * C语言声明定义全局变量请加上static，防止重复定义
 */
static int arr[1000000];
int* printNumbers(int n, int* returnSize )
{
    int num = 1;
    for(int i = 0; i < n; i++)
    {//num 为输出上限
        num *= 10;
    }
    for(int i = 1; i < num; i++)
    {//从1到num 给数组赋值
        arr[i - 1] = i;
    }
    *returnSize = num - 1;
    return arr;
}