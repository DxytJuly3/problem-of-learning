/* 
给你一个 升序排列 的数组 nums ，请你 原地 删除重复出现的元素，使每个元素 只出现一次 ，返回删除后数组的新长度。元素的 相对顺序 应该保持 一致 。
由于在某些语言中不能改变数组的长度，所以必须将结果放在数组nums的第一部分。更规范地说，如果在删除重复项之后有 k 个元素，那么 nums 的前 k 个元素应该保存最终结果。
将最终结果插入 nums 的前 k 个位置后返回 k 。
不要使用额外的空间，你必须在 原地 修改输入数组 并在使用 O(1) 额外空间的条件下完成。
判题标准:
系统会用下面的代码来测试你的题解:
int[] nums = [...]; // 输入数组
int[] expectedNums = [...]; // 长度正确的期望答案
int k = removeDuplicates(nums); // 调用
assert k == expectedNums.length;
for (int i = 0; i < k; i++) {
    assert nums[i] == expectedNums[i];
}
如果所有断言都通过，那么您的题解将被 通过。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/remove-duplicates-from-sorted-array
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

int removeDuplicates(int* nums, int numsSize)
{
    int src1 = 0;
    int src2 = 1;
    while(src2 < numsSize)
    {
        if(nums[src1] == nums[src2])
        {
            src2++;
        }
        else
        {
            nums[++src1] = nums[src2];
        }
    }

    return src1+1;
}

// 作业参考答案
/*
解题思路：大致思路同上题，用非重复的元素去覆盖重复元素
*/
/*int removeDuplicates(int* nums, int numsSize){
    int src1 = 0, src2 = 1;
    int dst = 0;
    // 跟上题的思路一致，相同的数只保留一个，依次往前放
    while(src2 < numsSize)
    {
        nums[dst] = nums[src1];
        ++dst;
		//如果两个指针指向的元素不重复，则指针同时向后移动
        if(nums[src1] != nums[src2])
        {
            ++src1;
            ++src2;
        }
        else
        {
            //如果重复，找到第一个不重复的元素
            while(src2 < numsSize && nums[src1] == nums[src2])
            {
                ++src2;
            }
            //更新指针
            src1 = src2;
            ++src2;
        }
    }
 
    if(src1 < numsSize)
    {
            nums[dst] = nums[src1];
            ++dst;
    }
 
 
    return dst;
}*/