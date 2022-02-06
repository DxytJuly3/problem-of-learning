//给出一个整型数组 numbers 和一个目标值 target，请在数组中找出两个加起来等于目标值的数的下标，返回的下标按升序排列。
//（注：返回的数组下标从1开始算起，保证target一定可以由数组里面2个数字相加得到）
/**
 * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
 *
 * 
 * @param numbers int整型一维数组 
 * @param numbersLen int numbers数组长度
 * @param target int整型 
 * @return int整型一维数组
 * @return int* returnSize 返回数组行数
 *
 * C语言声明定义全局变量请加上static，防止重复定义
 */
int* twoSum(int* numbers, int numbersLen, int target, int* returnSize ) {
    *returnSize = 2;
    static int target_num[2] = {0};
    memset(target_num, 0, sizeof(target_num));
    for(int i = 0; i < numbersLen; i++)
    {
        for(int j = i + 1; j < numbersLen; j++)
        {
            if((numbers[i] + numbers[j]) == target)
            {
                target_num[0] = i+1;
                target_num[1] = j+1;
                return target_num;
            }
        }
    }
    
    *returnSize = 0;
    return NULL;
}