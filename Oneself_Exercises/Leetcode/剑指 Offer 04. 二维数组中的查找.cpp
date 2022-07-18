/*
在一个 n * m 的二维数组中，每一行都按照从左到右递增的顺序排序，每一列都按照从上到下递增的顺序排序。
请完成一个高效的函数，输入这样的一个二维数组和一个整数，判断数组中是否含有该整数。
示例:
现有矩阵 matrix 如下：
[
  [1,   4,  7, 11, 15],
  [2,   5,  8, 12, 19],
  [3,   6,  9, 16, 22],
  [10, 13, 14, 17, 24],
  [18, 21, 23, 26, 30]
]
给定 target = 5，返回 true。
给定 target = 20，返回 false。

来源：力扣（LeetCode）
链接：https://leetcode.cn/problems/er-wei-shu-zu-zhong-de-cha-zhao-lcof
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

// 题目条件：n * m 的二维数组，且每一行从左到右、每一列从上到下 都按递增排列
// 所以 第一列是每一行中的最小值，最后一列是每一行中的最大值
// 所以可以从 左下角 或者 右上角找
// 如果从左下角比 可以保证对比的首个元素是那一列的最大值且那一行的最小值
// 对比可以排除一整行或者一整列，当target小时，就表示那一行剩余的数据都比target大，不用再考虑，直接 行数--
//                            当tatget大时，就表示那一列剩余的数据都比target小，同样不用考虑，直接 列数++
// 这样可以快速的排除，且不会漏掉数据
// 下面从左下角开始对比
class Solution
{
public:
    bool findNumberIn2DArray(vector<vector<int>>& matrix, int target)
    {
        if(matrix.empty())
        {
            return false;
        }
        size_t mrow = matrix.size();
        size_t mrol = matrix[0].size();     // 判空之后才能用 matrix[0].size();

        int row = mrow - 1, rol = 0;
        while(row >= 0 && rol < mrol)
        {
            if(target == matrix[row][rol])
                return true;

            if(row >= 0 && rol <= mrol && target < matrix[row][rol])        // 记得不能越界
                row--;
            if(row >= 0 && rol <= mrol && target > matrix[row][rol])        // 记得不能越界
                rol++;
        }
        // 从循环退出 就说明没有找到
        return false;
    }
};