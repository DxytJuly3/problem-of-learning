/*
给你一个二叉树的根节点 root ， 检查它是否轴对称。
示例 1：

输入：root = [1,2,2,3,4,4,3]
输出：true

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/symmetric-tree
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

bool isSymmeTree(struct TreeNode* p, struct TreeNode* q)
{
    // 两棵树的根同为空
    if(p == NULL && q == NULL)
        return true;

    if(p == NULL || q == NULL)
        return false;
        
    if(p->val != q->val)
        return false;

    return isSymmeTree(p->left, q->right) && isSymmeTree(p->right, q->left);
}
bool isSymmetric(struct TreeNode* root)
{
    return isSymmeTree(root->left, root->right);
}