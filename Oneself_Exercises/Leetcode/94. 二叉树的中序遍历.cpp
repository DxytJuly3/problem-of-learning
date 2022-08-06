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
// 
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