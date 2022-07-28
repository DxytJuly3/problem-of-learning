/*
给定一个二叉树的根节点 root ，返回 它的 中序 遍历 。

示例 1：
输入：root = [1,null,2,3]
输出：[1,3,2]

示例 2：
输入：root = []
输出：[]

示例 3：
输入：root = [1]
输出：[1]

来源：力扣（LeetCode）
链接：https://leetcode.cn/problems/binary-tree-inorder-traversal
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

// 非递归
class Solution {
public:
    vector<int> inorderTraversal(TreeNode* root){
        vector<int> ret;
        TreeNode* cur = root;
        stack<TreeNode*> nodeSt;

        while(cur || !nodeSt.empty())
        {
            while(cur)
            {
                nodeSt.push(cur);
                cur = cur->left;
            }
            TreeNode* top = nodeSt.top();
            nodeSt.pop();
            ret.push_back(top->val);

            cur = top->right;
        }

        return ret;
    }
};