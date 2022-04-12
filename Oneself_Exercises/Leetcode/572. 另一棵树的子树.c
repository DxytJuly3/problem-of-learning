/*
给你两棵二叉树 root 和 subRoot 。检验 root 中是否包含和 subRoot 具有相同结构和节点值的子树。
如果存在，返回 true ；否则，返回 false 。

二叉树 tree 的一棵子树包括 tree 的某个节点和这个节点的所有后代节点。tree 也可以看做它自身的一棵子树。
示例 1：

输入：root = [3,4,5,1,2], subRoot = [4,1,2]
输出：true

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/subtree-of-another-tree
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

bool isSubtree(struct TreeNode* root, struct TreeNode* subRoot)
{
    if(root == NULL)
        return;
    /*if(isSameTree(root, subRoot))
    {
        return true;
    }*/

    return isSameTree(root, subRoot) || isSubtree(root->left, subRoot) || isSubtree(root->right, subRoot);
}