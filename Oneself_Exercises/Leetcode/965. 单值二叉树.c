/*
如果二叉树每个节点都具有相同的值，那么该二叉树就是单值二叉树。
只有给定的树是单值二叉树时，才返回 true；否则返回 false。
示例 1：
输入：[1,1,1,1,1,null,1]
输出：true

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/univalued-binary-tree
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

bool isUnivalTree(struct TreeNode* root)
{
    if(root == NULL)
        return true;

    /*if(root->left && root->right)
    {
        if(root->val == root->left->val && root->val == root->right->val)
            return isUnivalTree(root->left) && isUnivalTree(root->right);
        else
            return false;
    }
    else if(root->left == NULL && root->right == NULL)
    {
        return true;
    }
    else if(root->left == NULL)
    {
        if(root->val == root->right->val)
            return isUnivalTree(root->right);
        else
            return false;
    }
    else if(root->right == NULL)
    {
        if(root->val == root->left->val)
            return isUnivalTree(root->left);
        else
            return false;
    }*/
    // 以上代码太反复

    // 想办法优化一下
    // 如果左、右孩子不为空, 则直接判断 左、右孩子的值 是否与当前 root 的值 不相等，不相等则返回 false
    // 相等就再次递归
    // 此时再次递归就不需要关注 左、右孩子是否为空，因为就算为空 也直接返回 true，不会访问空指针的值
    if( (root->left != NULL && root->left->val != root->val) ||
        (root->right != NULL && root->right->val != root->val) )
        return false;

    return isUnivalTree(root->left) && isUnivalTree(root->right);
}