/*
给定一个非负整数 numRows，生成「杨辉三角」的前 numRows 行。
在「杨辉三角」中，每个数是它左上方和右上方的数的和。
示例 1:
输入: numRows = 5
输出: [[1],[1,1],[1,2,1],[1,3,3,1],[1,4,6,4,1]]

示例 2:
输入: numRows = 1
输出: [[1]]

来源：力扣（LeetCode）
链接：https://leetcode.cn/problems/pascals-triangle
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

class Solution
{
public:
    vector<vector<int>> generate(int numRows)
    {
        vector<vector<int>> vv;
        vv.resize(numRows);
        for(int i = 0; i < vv.size(); i++)
        {
            // 每行vector<int> 的size递增，且初始化为零
            vv[i].resize(i + 1, 0);

            // 每行的第一个、最后一个元素赋值为1
            vv[i].front() = 1;
            vv[i].back() = 1;
        }

        for(int i = 0; i < vv.size(); i++)
        {
            for(int j = 0; j < vv[i].size(); j++)
            {
                // vector<int> 中所有数据被初始化为0
                // 但是上面已经对杨辉三角外层数据置1
                // 所以数值为0的需要计算
                if(vv[i][j] == 0)
                {
                    vv[i][j] = vv[i-1][j-1] + vv[i-1][j];
                }
            }
        }

        return vv;
    }
};