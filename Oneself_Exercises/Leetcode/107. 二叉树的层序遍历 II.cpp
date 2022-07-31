/*
给你二叉树的根节点 root ，返回其节点值 自底向上的层序遍历 。 （即按从叶子节点所在层到根节点所在的层，逐层从左向右遍历）

示例 1：
输入：root = [3,9,20,null,null,15,7]
输出：[[15,7],[9,20],[3]]

示例 2：
输入：root = [1]
输出：[[1]]

示例 3：
输入：root = []
输出：[]

来源：力扣（LeetCode）
链接：https://leetcode.cn/problems/binary-tree-level-order-traversal-ii
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */

 // 与 106. 二叉树的层序遍历 I 相同，遍历完 逆置外层vector就好了
class Solution {
public:
    vector<vector<int>> levelOrderBottom(TreeNode* root){
        queue<TreeNode*> nodeQue;
        vector<vector<int>> ret;
        if(root)        // root 不为空入队列
            nodeQue.push(root);

        while(!nodeQue.empty())
        {
            vector<int> v;
            size_t qsize = nodeQue.size();
            for(int i = 0; i < qsize; i++)
            {
                v.push_back(nodeQue.front()->val);

                if(nodeQue.front()->left)
                    nodeQue.push(nodeQue.front()->left);
                if(nodeQue.front()->right)
                    nodeQue.push(nodeQue.front()->right);
                
                nodeQue.pop();
            }

            ret.push_back(v);
        }

        reverse(ret.begin(), ret.end());

        return ret;
    }
};