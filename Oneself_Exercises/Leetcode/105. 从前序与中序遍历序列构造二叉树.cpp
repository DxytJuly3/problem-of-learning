/*
给定两个整数数组 preorder 和 inorder ，其中 preorder 是二叉树的先序遍历， inorder 是同一棵树的中序遍历，请构造二叉树并返回其根节点。

示例 1:
输入: preorder = [3,9,20,15,7], inorder = [9,3,15,20,7]
输出: [3,9,20,null,null,15,7]

示例 2:
输入: preorder = [-1], inorder = [-1]
输出: [-1]

来源：力扣（LeetCode）
链接：https://leetcode.cn/problems/construct-binary-tree-from-preorder-and-inorder-traversal
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

 // 题目要求：
 //     题目的要求是 根据提供的前序和中序遍历 来构造二叉树
 //         前序遍历：根、左、右，所以 前序遍历的首元素即为整个树的根
 //         中序遍历：左、根、右，所以 根据前序遍历判断出的根，根 左边的元素即为 根左子树的元素，右边的元素即为 根右子树的元素
 //     比如：前序：3,9,20,15,7；中序：9,3,15,20,7
 //     由 两个序列逐个判断可以分析：
 //         1. 首先前序首元素3，表示树的根为 3；中序里 3左边区间是 9(0)，右边区间是 15、20、7(2-4)
 //         2. 前序走到9，在3的左子树，，可分析出 9即为3的左孩子
 //         3. 9在中序里 没有左右子树的区间，就表示 9没有左右孩子，表示 3的左子树遍历完
 //         4. 前序3的左子树遍历完，开始遍历右子树到20，即可分析出 20为3的右孩子，且 20的左边区间是15(2) 右边区间是 7(4)
 //         5. 前序里 20后紧邻15，15又是20的左子树元素，15即为20的左孩子
 //         6. 15在中序里，没有左右子树区间，表示 15没有左右孩子，即 20的左子树遍历完
 //         7. 前序 20的左子树遍历完，继续遍历右子树 到 7，表示20的右孩子为 7，7无左右子树
 //         8. 前序序列走完，树建立完成
 //     大致分析：
 //     其实 就是遍历前序序列，遍历过程中 由中序序列判断 此元素在树中是否存在左右子树，进而判断前序中下一个元素是左孩子还是右孩子：
 //         前序 3为根，中序 3 存在左右子树，则前序中 3 的下一元素9 为其左孩子
 //         前序 9为3左树的根，中序 9不存在左右子树，则 前序中 9的下一元素20 为3的右孩子
 //         前序 20为 3右树的根，中序 20存在左右子树，则 前序中  20的下一元素15 为20的左孩子
 //         前序 15为 20的左树的根，中序 15不存在左右子树，则 前序中 15的下一元素7 为20的右孩子
 //         前序 7为 20的右树的根，中序 7不存在左右子树，且前序遍历序列遍历结束，建树结束
 // 思路分析：
 //     按照上面示例分析的过程，其实就是 前序遍历建树
 //     前序走到当前根时，再在中序里判断根的左右子树，所以 本题的具体方法就是：
 //         定义子函数，参数为 固定的前序序列、中序序列，当前 前序序列元素位置，当前元素位置的左子树区间 和 右子树区间
class Solution {
public:
    TreeNode* _buildTree(vector<int>& preorder, vector<int>& inorder, size_t& prei, int inBegin, int inEnd) {
        if(inBegin > inEnd)
            return nullptr;
        
        // prei 表示当前元素 在前序序列中的位置，prei需要&
        TreeNode* root = new TreeNode(preorder[prei]);
        prei++;

        size_t rooti = inBegin;
        while(rooti <= inEnd) {     // 需要从inBegin向 inEnd位置遍历查找 root元素在 中序的位置，以区分左右子树
            if(root->val == inorder[rooti])
                break; 
            else
                rooti++;
        }
        //  找到 root 在中序的位置 rooti，就可以划分出 root的左右子树：左子树区间[inBegin, rooti-1], 右子树区间[rooti+1, inEnd]
        root->left = _buildTree(preorder, inorder, prei, inBegin, rooti - 1);   // 在左子树递归
        root->right = _buildTree(preorder, inorder, prei, rooti + 1, inEnd);    // 在右子树递归

        return root;
    }

    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        size_t prei = 0;        // 前序从 0位置开始
        int inBegin = 0;     // 初始左树区间 也从 0位置开始 
        int inEnd = inorder.size() - 1;       // 初始右树区间 到 末元素位置结束，可能变为负数 所以需要int

        return _buildTree(preorder, inorder, prei, inBegin, inEnd);
    }
};