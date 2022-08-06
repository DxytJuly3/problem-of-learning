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
//  把整个树的所有节点 分为 左路节点 和 左路节点的右子树
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
//                 左路节点5 和 左路节点9 没有右子树
//      即 将每个树都分为 左路节点 和 其右子树
//  
//  将 左路节点入栈

//  将当前树的左路节点入栈 并 入vector
//  再然后循环 将各左路节点的 右子树的左路节点入栈并入 vector，形成一个循环
//  在进入下一个循环之前，要将栈顶元素出栈，因为栈顶元素栈顶元素是一个树的最后一个未遍历左路节点
//  进入下一次循环时 就是在此左路节点的右子树进行操作的
//  如果 不出栈，那么就会在此节点的右子树 无限循环
// 
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

            // 直接
            TreeNode* top = st.top();   // 栈顶元素即为最后一个左路节点
            st.pop();

            cur = top->right;
        }

        return retV;
    }
};