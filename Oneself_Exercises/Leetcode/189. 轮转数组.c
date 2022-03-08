/* 给你一个数组，将数组中的元素向右轮转 k 个位置，其中 k 是非负数。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/rotate-array
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。*/

void reverse(int* nums, int begin, int end)
{
    if(begin < 0)
        return;
    int* start = nums + begin;
    int* end1 = nums + end;
    while(start <= end1)
    {
        int tmp = *start;
        *start = *end1;
        *end1 = tmp;
        start++;
        end1--;
    }
}

void rotate(int* nums, int numsSize, int k)
{
    int realk = k % numsSize;
    reverse(nums, numsSize - realk, numsSize - 1);
    reverse(nums, 0, numsSize - realk - 1);
    reverse(nums, 0, numsSize - 1);
}