/*
给你二叉树的根节点 root ，返回其节点值的 层序遍历 。 （即逐层地，从左到右访问所有节点）。

示例 1：
输入：root = [3,9,20,null,null,15,7]
输出：[[3],[9,20],[15,7]]

示例 2：
输入：root = [1]
输出：[[1]]

示例 3：
输入：root = []
输出：[]

来源：力扣（LeetCode）
链接：https://leetcode.cn/problems/binary-tree-level-order-traversal
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
 // 思路：
 // 个人认为，本体的关键点在于：返回的是 vector<vector<int>>, 而不是 单层的vector，就代表着需要分别存储每层的数据
 // 一般的 层序遍历 会借助queue，从根开始 将每层的节点入队列 出队列时 再带入下一层的节点，也不用控制什么 直接当队列为空结束遍历
 // 但是 此题要求返回 vector<vector<int>>数据，不能一股脑地将数据全部存入 vector
 // 所以 又有一个思路就是
 // 在循环中创建vector<int> 用来存储每层的节点数据
 // 记录当前队列中的数据个数 qsize，将队列中前qsize个节点数据 逐个存入vector<int>，同时逐个出队列
 // 但在出队列的之前 要将其左右孩子入队列
 // 这样可以保证 只有一层的数据存储到了 vector中，且队列中存储的是下一层的所有节点
 // 再将 存储着一层数据的 vector 尾插到 外层vector 就完成了一层的遍历
 //
 // 太难解释了 有条件还是画图吧
class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode* root){
        queue<TreeNode*> nodeQue;
        vector<vector<int>> ret;
        if(root)        // root 不为空入队列
            nodeQue.push(root);

        while(!nodeQue.empty())
        {
            vector<int> v;
            size_t qsize = nodeQue.size();
            for(int i = 0; i < qsize; i++)
            {
                v.push_back(nodeQue.front()->val);

                if(nodeQue.front()->left)
                    nodeQue.push(nodeQue.front()->left);
                if(nodeQue.front()->right)
                    nodeQue.push(nodeQue.front()->right);
                
                nodeQue.pop();
            }

            ret.push_back(v);
        }

        return ret;
    }
};