/*
给你一棵二叉树的根节点 root ，返回其节点值的 后序遍历 。

示例 1：
输入：root = [1,null,2,3]
输出：[3,2,1]

示例 2：
输入：root = []
输出：[]

示例 3：
输入：root = [1]
输出：[1]

来源：力扣（LeetCode）
链接：https://leetcode.cn/problems/binary-tree-postorder-traversal
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
// 二叉树后序遍历 递归：
/*class Solution {
public:
    void _postorderTraversal(vector<int>& ret, TreeNode* root) {
        if(root == nullptr)
            return;

        _postorderTraversal(ret, root->left);
        _postorderTraversal(ret, root->right);
        ret.push_back(root->val);
    }

    vector<int> postorderTraversal(TreeNode* root) {
        vector<int> retV;
        _postorderTraversal(retV, root);

        return retV;
    }
};*/

//  二叉树后序遍历的非递归，还是把整个树的所有节点 分为 左路节点 和 左路节点的右子树
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
//  后序遍历的顺序是，左子树、右子树、根
//  所以 后序遍历的非递归 应该在什么时候将 节点值入 vector呢？
//  先由例子分析一下：
//  左路节点入栈—— st: 1、2、5、9
//      访问 9的左子树为空；回到9，访问 9的右子树为空，则访问9本身，9入vector 并出栈，st: 1、2、5; retV: 9
//      回到5，访问 5的右子树为空，则访问5本身，5入vector 并出栈， st: 1、2; retV: 9、5
//      回到2，访问 2的右子树，存在左路节点6，入栈，st: 1、2、6
//      访问 6的左子树为空；回到6，访问 6的右子树为空，则访问6本身，6入vector 并出栈， st: 1、2; retV: 9、5、6
//      再次回到 2，此时应该将2出栈 并将 2入vector了，因为 2的右子树已经遍历访问过了，该访问2本身了
//      则 2出栈，并入vector   st: 1; retV: 9、5、6、2
//      回到1，访问 1的右子树，存在左路节点 3、7，入栈：st: 1、3、7;
//      访问 7的左子树为空，7的右子树为空，则访问 7本身，即 7入vector，并出栈：st: 1、3; retV: 9、5、6、2、7
//      回到3，访问 3的右子树，存在左路节点8，入栈，st: 1、3、8
//      访问 8的左子树为空，8的右子树为空，则访问 8本身，即 8入vector，并出栈：st: 1、3; retV: 9、5、6、2、7、8
//      再次回到3，3的右子树已经遍历访问，所以该访问3本身，则 3入vector 并出栈：st: 1; retV: 9、5、6、2、7、8、3
//      再次回到1，1的右子树已经遍历访问，所以该访问1本身，则 1入vector 并出栈：st: ; retV: 9、5、6、2、7、8、3、1
//  此时 栈为空，表示后序遍历结束
//
//  可以看到 整个过程中 拥有右子树的节点是经过了两遍的，比如 2、3、1，遍历完左子树回到节点，然后再遍历节点的右子树
//  并且 再遍历完右子树时，节点才出栈并 入vector的
//  怎么判断 节点的右子树已经遍历过了 或 不需要遍历呢？
//  当节点的右子树未空时，不需要遍历其右子树，直接将节点出栈 并将节点值 入vector
//  节点右子树遍历访问结束时，也需要将节点出栈，并将节点值 入vector
//  怎么才能判断节点的右子树 是否遍历过了呢？
//  通过 观察分析可以发现，节点的右子树遍历完成时，上一次出栈的元素即为节点的右孩子
//  也就是说可以通过 比较 上一次出栈的节点 与 节点的右孩子 是否相等，来判断出 节点的右子树是否已经遍历完成
//
//  具体实现

class Solution {
public:
    vector<int> postorderTraversal(TreeNode* root) {
        vector<int> retV;
        stack<TreeNode*> st;

        TreeNode* cur = root;
        TreeNode* prev = nullptr;       // 记录上一次出栈的节点
        while(cur || !st.empty())
        {
            while(cur)
            {
                st.push(cur);
                cur = cur->left;
            }

            TreeNode* top = st.top();       //记录出栈节点
            if(top->right == nullptr || prev == top->right)    // 左路节点的右子树为空 或者 上一次出栈的元素是节点的右孩子，则表示没有右子树 或 右子树已经遍历过了
            {
                st.pop();
                prev = top;     // 更新 prev

                retV.push_back(top->val);   // 节点入 vector
            }
            else
            {
                cur = top->right;
            }
        }

        return retV;
    }
};