//自除数 是指可以被它包含的每一位数除尽的数。
//例如，128 是一个自除数，因为 128 % 1 == 0，128 % 2 == 0，128 % 8 == 0。
//还有，自除数不允许包含 0 。
//给定上边界和下边界数字，输出一个列表，列表的元素是边界（含边界）内所有的自除数。

//来源：力扣（LeetCode）
//链接：https://leetcode-cn.com/problems/self-dividing-numbers
//著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* selfDividingNumbers(int left, int right, int* returnSize)
{
    int* returnNum = (int *)malloc(sizeof(int) * (right - left));
    (*returnSize) = 0;
    for(int i = left; i < right + 1; i++)
    {
        int flag = i;
        int sum = 0;
        int tmp;
        while(tmp = flag % 10)
        {
            sum += i % tmp;
            flag /= 10;
            if(sum == 0 && flag == 0)
            {
                returnNum[(*returnSize)++] = i;
            }
        }
    }
    
    return returnNum;
}