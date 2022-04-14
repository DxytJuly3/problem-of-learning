/*给你一棵二叉树的根节点 root ，翻转这棵二叉树，并返回其根节点。
示例 1：

输入：root = [4,2,7,1,3,6,9]
输出：[4,7,2,9,6,3,1]

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/invert-binary-tree
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
void _invertTree(struct TreeNode* root)
{
    if(root == NULL)
        return root;
    
    struct TreeNode* newNode;
    newNode = root->left;
    root->left = root->right;
    root->right = newNode;
    _invertTree(root->left);
    _invertTree(root->right);
}

// 本题相当于将原来的二叉树转换成其镜像二叉树
struct TreeNode* invertTree(struct TreeNode* root)
{
    if(root != NULL)
        _invertTree(root);

    return root;
}