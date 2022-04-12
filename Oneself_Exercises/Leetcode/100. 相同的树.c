/*
给你两棵二叉树的根节点 p 和 q ，编写一个函数来检验这两棵树是否相同。

如果两个树在结构上相同，并且节点具有相同的值，则认为它们是相同的。
示例 1：
输入：p = [1,2,3], q = [1,2,3]
输出：true

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/same-tree
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


bool isSameTree(struct TreeNode* p, struct TreeNode* q)
{
    // 两棵树的根同为空
    if(p == NULL && q == NULL)
        return true;
    // 只有一棵树的根为空   此时已经有同位置的节点不相等
    if(p == NULL || q == NULL)
        return false;
    // 当 两棵树根位置的值不相同
    if(p->val != q->val)
        return false;

    // 以上条件都成立，表明当前两树根节点相等，再比较两棵树的左孩子 和 右孩子
    return isSameTree(p->left, q->left) && isSameTree(p->right, q->right);
}