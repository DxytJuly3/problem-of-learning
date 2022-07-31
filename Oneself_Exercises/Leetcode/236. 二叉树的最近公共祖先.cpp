/*
给定一个二叉树, 找到该树中两个指定节点的最近公共祖先。
百度百科中最近公共祖先的定义为：
“对于有根树 T 的两个节点 p、q，最近公共祖先表示为一个节点 x，满足 x 是 p、q 的祖先且 x 的深度尽可能大（一个节点也可以是它自己的祖先）”

示例 1：
输入：root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 1
输出：3
解释：节点 5 和节点 1 的最近公共祖先是节点 3 。

示例 2：
输入：root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 4
输出：5
解释：节点 5 和节点 4 的最近公共祖先是节点 5 。因为根据定义最近公共祖先节点可以为节点本身。

示例 3：
输入：root = [1,2], p = 1, q = 2
输出：1

来源：力扣（LeetCode）
链接：https://leetcode.cn/problems/lowest-common-ancestor-of-a-binary-tree
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
 // 普通二叉树：
 // 思路1：
 // 题目说树不为空，且q和p一定在树中,找给定的两个节点是在左子树还是在右子树：
 //     1. 如果两节点 一个在左子树，另一个在右子树，那么当前节点即为其 最近公共祖先
 //     2. 如果在同子树上，就在此字数上继续判断两个节点是否
 //     3. 如果 找到了其中一个节点，则说明 此节点为最近公共祖先
 //  此思路的时间复杂度是 O(n^2)

 // 思路2：
 // 本题与另一个题非常相似：两链表相交求交点
 // 只不过本题是在一个普通二叉树中，不过普通二叉树有普通二叉树的解法
 // 在此题中，可以从根开始，向每个子树遍历找指定的节点，并且记录路径
 // 找到之后，将两节点的路径 根据两链表相交求交点的思路就可以求出 最近公共祖先

 // 搜索二叉树、三叉链二叉树，都可以更简单的求公共祖先
 // 搜索二叉树可以直接找到路径，三叉链则可以从节点倒推
 // 但是本题只是普通的二叉树，只能遍历找节点记录路径
class Solution {
public:
    // 思路1：
    /*bool inTree(TreeNode* root, TreeNode* key) {
        if(root == nullptr)
            return false;

        if(root == key)
            return true;
        
        return inTree(root->left, key) || inTree(root->right, key);
    }
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if(root == nullptr || p == root || q == root)
            return root;
        
        // 设定四个状态
        bool qInLeft = inTree(root->left, q);
        bool qInRight = !qInLeft;
        bool pInLeft = inTree(root->left, p);
        bool pInRight = !pInLeft;

        if( (qInLeft && pInRight) || (pInLeft && qInRight))
            return root;
        else if(qInLeft && pInLeft)
            return lowestCommonAncestor(root->left, p, q);
        else if(qInRight && pInRight)
            return lowestCommonAncestor(root->right, p, q);
        else
            return nullptr;
    }*/
    bool NodePath(TreeNode* root, TreeNode* key,stack<TreeNode*>& Path) {
        if(root == nullptr)
            return false;
        
        Path.push(root);
        if(key == root)
            return true;
        
        bool isKey = false;
        if(isKey = NodePath(root->left, key, Path))     // 左子树找
            return true;        // 找到了就返回true

        // 左子树没找到 在向右子树找    
        if(isKey = NodePath(root->right, key, Path))
            return true;
        
        // 走到这里说明都没有找到，即 指定节点不在此路径中
        Path.pop();     // 删除记录的路径
        return false;
    }

    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        stack<TreeNode*> qPath;
        stack<TreeNode*> pPath;
        NodePath(root, q, qPath);
        NodePath(root, p, pPath);

        while(qPath.size() > pPath.size())
            qPath.pop();
        
        while(pPath.size() > qPath.size())
            pPath.pop();
        
        // 路径长度相等时，两栈一起 出栈直到 栈顶相等，此时栈顶即为最近公共祖先
        while(pPath.top() != qPath.top())
        {
            pPath.pop();
            qPath.pop();
        }

        return pPath.top();
    }
};