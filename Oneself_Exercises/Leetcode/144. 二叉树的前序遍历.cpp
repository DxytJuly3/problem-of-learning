/*
给你二叉树的根节点 root ，返回它节点值的 前序 遍历。

示例 1：
输入：root = [1,null,2,3]
输出：[1,2,3]

示例 2：
输入：root = []
输出：[]

示例 3：
输入：root = [1]
输出：[1]

示例 4：
输入：root = [1,2]
输出：[1,2]

示例 5：
输入：root = [1,null,2]
输出：[1,2]

来源：力扣（LeetCode）
链接：https://leetcode.cn/problems/binary-tree-preorder-traversal
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

 // 本题的递归写法非常简单
 // 直接 根、左、右 顺序递归就行了
/*class Solution {
public:
    void _preorderTraversal(vector<int>& ret, TreeNode* root) {
        if(root == nullptr)
            return;

        ret.push_back(root->val);
        _preorderTraversal(ret, root->left);
        _preorderTraversal(ret, root->right);
    }
    vector<int> preorderTraversal(TreeNode* root) {
        vector<int> ret;
        _preorderTraversal(ret, root);

        return ret;
    }
};*/

// 但是 二叉树遍历的非递归写法 就没有那么简单了
// 非递归写法可以解决 二叉树很大时，递归遍历可能出现栈溢出的问题 
// 因为 递归会重复建立栈帧，比较占用空间，所以 非递归遍历写法更好
// 那么前序遍历的非递归写法 是什么思路呢？
// 思路：
//  因为 前序遍历的顺序为：根、左子树、右子树
//  所以可以把整个树的所有节点 分为 左路节点 和 左路节点的右子树
//    例：          1
//                /  \
//               2    3
//              / \  / \
//             5   67   8
//            /
//           9
//      此树分为 左路节点(左孩子节点)：1、2、5、9
//              和 左路节点1 的右子树、左路节点2 的右子树、左路节点5 的右子树、左路节点9 的右子树
//                 左路节点1 的右子树 又有 左路节点 3、7
//                 左路节点2 的右子树 又有 左路节点 6
//                 左路节点5 和 左路节点9 右子树为空
//      即 将每个树都分为 左路节点 和 其右子树

//  将当前树的左路节点逐个入栈 并 入vector
//  再然后循环 将各左路节点的 右子树的左路节点入栈并入 vector，形成一个循环
//  其实就是一个 先逐个访问一个树的左路节点，再从末左路节点开始 访问其右子树 的过程
//  访问右子树的过程又是一个 访问树的左路节点，再从末左路节点开始 访问其右子树 的过程
//  是一个循环的子问题，知道 右子树为空时，回到上一个左路节点，继续循环解决子问题
//  
//  比如：
//      按照上面的例子：先 逐个将左路节点cur 入栈 并 入vector
//          栈 st：1、2、5、9      vector retV：1、2、5、9
//  后面的循环 应该依此访问 左路节点的右子树，即 cur应该为左路节点的右子树
//  所以 cur = st.top()->right; 逐个访问，所以从栈顶开始
//  下次循环就访问此节点的右子树了，所以 此节点应该出栈了
//  保证 下次循环结束之后 访问另一个左路节点的右子树
//  建议 画图理解
class Solution {
public:
    vector<int> preorderTraversal(TreeNode* root) {
        vector<int> retV;
        stack<TreeNode*> st;

        TreeNode* cur = root;
        while(cur || !st.empty())
        {
            while(cur)                      // 左路节点入栈 入vector
            {
                st.push(cur);
                retV.push_back(cur->val);
                cur = cur->left;
            }
            // 退出循环时，cur为nullptr

            TreeNode* top = st.top();   // 栈顶元素即为最后一个未开始访问右子树的左路节点
            st.pop();                   // 出栈

            cur = top->right;           // 下次循环 访问左路节点的右子树
        }

        return retV;
    }
};