/* 给你一个数组 nums 和一个值 val，你需要 原地 移除所有数值等于 val 的元素，并返回移除后数组的新长度。
不要使用额外的数组空间，你必须仅使用 O(1) 额外空间并 原地 修改输入数组。
元素的顺序可以改变。你不需要考虑数组中超出新长度后面的元素。

说明:
为什么返回数值是整数，但输出的答案是数组呢?
请注意，输入数组是以「引用」方式传递的，这意味着在函数里修改输入数组对于调用者是可见的。
你可以想象内部操作如下:
// nums 是以“引用”方式传递的。也就是说，不对实参作任何拷贝
int len = removeElement(nums, val);
// 在函数里修改输入数组对于调用者是可见的。
// 根据你的函数返回的长度, 它会打印出数组中 该长度范围内 的所有元素。
for (int i = 0; i < len; i++)
{
    print(nums[i]);
}

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/remove-element
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。 */

/*int removeElement(int* nums, int numsSize, int val)
{
    int src = 0;
    int dst = 0;

    while(src < numsSize)
    {
        // 将数组中不等于val的值依次挪动到数组的开始位置
        if(nums[src] != val)
        {
            nums[dst] = nums[src];
            src++;
            dst++;
        }
        else
        {
            //如果是被删除的元素，直接++src位置，找到第一个不是val的位置
            src++;
        }
    }

    return dst;
}*/
int removeElement(int* nums, int numsSize, int val)
{
    int count = 0;
    for(int i = 0; i < numsSize; i++)
    {
        if(nums[i] == val)
            count++;
    }
    int flag = 0;
    for(int i = 0; i < numsSize - count; i++)
    {
        if(nums[i] == val)
        {
            while(nums[i] == nums[numsSize - flag - 1])
            {
                flag++;
            }
            nums[i] = nums[numsSize - flag - 1];
            nums[numsSize - flag - 1] = 0;
            flag++;
                        if(flag == count + 1)
                break;
        }
    }

    return numsSize - count;
}