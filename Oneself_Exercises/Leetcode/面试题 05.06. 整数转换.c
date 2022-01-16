//整数转换。编写一个函数，确定需要改变几个位才能将整数A转成整数B。（二进制位）
//来源：力扣（LeetCode）
//链接：https://leetcode-cn.com/problems/convert-integer-lcci/
//著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

int convertInteger(int A, int B)
{
    unsigned int tmp = A ^ B;
    int returnNum = 0;
    while (tmp != 0)
    {
        int ret = tmp & 1;
        if (ret == 1)
            returnNum++;
        tmp = tmp >> 1;
    }

    return returnNum;
}
