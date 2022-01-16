//给定一个长度为 n 的非降序数组和一个非负数整数 k ，要求统计 k 在数组中出现的次数
//数据范围：0 \le n \le 1000 , 0 \le k \le 1000≤n≤1000,0≤k≤100，数组中每个元素的值满足 0 \le val \le 1000≤val≤100
//要求：空间复杂度 O(1)O(1)，时间复杂度 O(logn)O(logn)

/**
 * 
 * @param data int整型一维数组 
 * @param dataLen int data数组长度
 * @param k int整型 
 * @return int整型
 *
 * C语言声明定义全局变量请加上static，防止重复定义
 */
static int k_count = 0;
int GetNumberOfK(int* data, int dataLen, int k) {
    int left = 0;
    int right = dataLen - 1;
    int len = 0;
    if (k < *data || k > *(data + dataLen - 1) || data == NULL)
        return 0;
    else if (dataLen == 1 && *data == k)
        return 1;
    else if (*data == *(data + right))
        return dataLen;
    else
    {
        while (len != dataLen)
        {
            int mid = (left + right) / 2;
            if (k > *(data + mid))
                left = mid;
            else if (k < *(data + mid))
                right = mid - 1;
            else
            {
                k_count++;
                if (mid > 0)
                    left = mid - 1;
                if (mid < dataLen)
                    right = mid + 1;
                while (k == *(data + left))
                {
                    k_count++;
                    if (left == 0)
                        break;
                    if (left != 0)
                        left--;
                }
                while (k == *(data + right))
                {
                    k_count++;
                    if (right == dataLen)
                        break;
                    if (right != dataLen)
                        right++;
                }
                if (k_count != 0)
                    return k_count;
            }
            len++;
        }
        return k_count;
    }
}