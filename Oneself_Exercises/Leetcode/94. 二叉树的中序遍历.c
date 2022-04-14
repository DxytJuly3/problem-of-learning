/*给定一个二叉树的根节点 root ，返回 它的 中序 遍历 。
示例 1：

输入：root = [1,null,2,3]
输出：[1,3,2]

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/binary-tree-inorder-traversal
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


/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
 /**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */


/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
 int BTreeSize(struct TreeNode* root)
{
    // 当前节点为空就返回 0，表示不加 1
    // 当前节点不为空，就 + 1，并且进入下一个孩子
    return root == NULL ? 0 : BTreeSize(root->left) + BTreeSize(root->right) + 1;
}
void inOrder(struct TreeNode* root, int* a, int* i)
{// 注意因为每次调用函数返回时，i需要跟随变化，所以应该传 i 的地址
    if(root == NULL)
        return;
    
    inOrder(root->left, a, i);
    a[(*i)++] = root->val;
    inOrder(root->right, a, i);
}

int* inorderTraversal(struct TreeNode* root, int* returnSize)
{
    int Size = BTreeSize(root);
    int* returnNums = (int*)malloc(sizeof(int) * Size);

    int i = 0;
    inOrder(root, returnNums, &i);

    *returnSize = Size;
    return returnNums;
}