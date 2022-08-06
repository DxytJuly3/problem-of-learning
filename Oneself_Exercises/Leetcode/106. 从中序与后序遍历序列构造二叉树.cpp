/*
给定两个整数数组 inorder 和 postorder ，其中 inorder 是二叉树的中序遍历， postorder 是同一棵树的后序遍历，请你构造并返回这颗 二叉树 。

示例 1:
输入：inorder = [9,3,15,20,7], postorder = [9,15,7,20,3]
输出：[3,9,20,null,null,15,7]

示例 2:
输入：inorder = [-1], postorder = [-1]
输出：[-1]

来源：力扣（LeetCode）
链接：https://leetcode.cn/problems/construct-binary-tree-from-inorder-and-postorder-traversal
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
 // 本题 与 上一题 前中序构造二叉树 类似，不过 后序遍历是从尾开始
 // 后序遍历：左、右、根
 // 除了 从尾开始，并且 从后序的尾开始向前走，需要先递归右子树，再递归左子树
 // 其他的 与 前中序构造 没有区别
class Solution {
public:
    TreeNode* _buildTree(vector<int>& inorder, vector<int>& postorder, size_t& posi, int inBegin, int inEnd) {
        if(inBegin > inEnd)
            return nullptr;
        
        // posi 表示当前元素 在后序序列中的位置，prei需要&
        TreeNode* root = new TreeNode(postorder[posi]);
        posi--;

        size_t rooti = inBegin;
        while(rooti <= inEnd) {     // 需要从inBegin向 inEnd位置遍历查找 root元素在 中序的位置，以区分左右子树
            if(root->val == inorder[rooti])
                break; 
            else
                rooti++;
        }
        //  找到 root 在中序的位置 rooti，就可以划分出 root的左右子树：左子树区间[inBegin, rooti-1], 右子树区间[rooti+1, inEnd]
        root->right = _buildTree(inorder, postorder, posi, rooti + 1, inEnd);    // 在右子树递归
        root->left = _buildTree(inorder, postorder, posi, inBegin, rooti - 1);   // 在左子树递归

        return root;
    }
    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
        size_t posi = postorder.size() - 1;        // 后序从 末位置开始
        int inBegin = 0;     // 初始左树区间 也从 0位置开始 
        int inEnd = inorder.size() - 1;       // 初始右树区间 到 末元素位置结束，可能变为负数 所以需要int

        return _buildTree(inorder, postorder, posi, inBegin, inEnd);
    }
};