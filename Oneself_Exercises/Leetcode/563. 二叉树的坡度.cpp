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
 /*
 给你一个二叉树的根节点 root ，计算并返回 整个树 的坡度 。
一个树的 节点的坡度 定义即为，该节点左子树的节点之和和右子树节点之和的 差的绝对值 。
如果没有左子树的话，左子树的节点之和为 0 ；没有右子树的话也是一样。空结点的坡度是 0 。
整个树 的坡度就是其所有节点的坡度之和。

示例 1：
输入：root = [1,2,3]
输出：1
解释：
节点 2 的坡度：|0-0| = 0（没有子节点）
节点 3 的坡度：|0-0| = 0（没有子节点）
节点 1 的坡度：|2-3| = 1（左子树就是左子节点，所以和是 2 ；右子树就是右子节点，所以和是 3 ）
坡度总和：0 + 0 + 1 = 1

示例 2：
输入：root = [4,2,9,3,5,null,7]
输出：15
解释：
节点 3 的坡度：|0-0| = 0（没有子节点）
节点 5 的坡度：|0-0| = 0（没有子节点）
节点 7 的坡度：|0-0| = 0（没有子节点）
节点 2 的坡度：|3-5| = 2（左子树就是左子节点，所以和是 3 ；右子树就是右子节点，所以和是 5 ）
节点 9 的坡度：|0-7| = 7（没有左子树，所以和是 0 ；右子树正好是右子节点，所以和是 7 ）
节点 4 的坡度：|(3+5+2)-(9+7)| = |10-16| = 6（左子树值为 3、5 和 2 ，和是 10 ；右子树值为 9 和 7 ，和是 16 ）
坡度总和：0 + 0 + 0 + 2 + 7 + 6 = 15

示例 3：
输入：root = [21,7,14,1,1,2,2,3,3]
输出：9

提示：
    树中节点数目的范围在 [0, 104] 内
    -1000 <= Node.val <= 1000

来源：力扣（LeetCode）
链接：https://leetcode.cn/problems/binary-tree-tilt
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
 */
 /*
 题意分析：
    什么是坡度, 如果左右子树只有一个节点, 则此树的坡度即为 节点的左右孩子的值的差的绝对值
    进而 一棵树的坡度 可以看作 其左右子树的坡度的差的绝对值
    
 思路分析：
    将给定的树的左右子树 看作单独的树, 并以此递归
 */
class Solution {
    int dep;
public:
    int findTilt(TreeNode* root) {
        _findTilt(root);

        return dep;
    }
    int _findTilt(TreeNode* root) {
        if(root == nullptr)
            return 0;
        
        int leftDep = _findTilt(root->left);
        int rightDep = _findTilt(root->right);
        dep += abs(leftDep - rightDep);

        return leftDep + rightDep + root->val;      // 返回本树所有节点和, 作为新的坡度
    }
};