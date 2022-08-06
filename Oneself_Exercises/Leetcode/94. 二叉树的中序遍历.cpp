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
// 本题的递归写法非常简单
// 直接 左、根、右 顺序递归就行了
/*class Solution {
public:
    void _inorderTraversal(vector<int>& ret, TreeNode* root) {
        if(root == nullptr)
            return;

        _inorderTraversal(ret, root->left);
        ret.push_back(root->val);
        _inorderTraversal(ret, root->right);
    }
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> ret;
        _inorderTraversal(ret, root);

        return ret;
    }
};*/

//  二叉树 中序遍历的非递归写法
//  和 前序遍历非递归 写法基本相同
//  只不过 中序遍历时，不是在 左路节点入栈的同时将 节点值入 vector
//  而是在 节点出栈时，将 节点值入 vector， 其他一致
//  为什么是在节点出栈时，将节点值入 vector？
//  节点出栈，表示已经要开始访问节点的右子树了
//  而中序遍历的 顺序是，左子树、根、右子树
//  所以 需要在节点出栈时，将节点值 入 vector
// 
class Solution {
public:
    vector<int> inorderTraversal(TreeNode* root){
        vector<int> retV;
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
            retV.push_back(top->val);

            cur = top->right;
        }

        return retV;
    }
};