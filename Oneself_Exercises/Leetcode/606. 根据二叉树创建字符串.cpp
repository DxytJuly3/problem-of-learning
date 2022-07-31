/*
给你二叉树的根节点 root ，请你采用前序遍历的方式，将二叉树转化为一个由括号和整数组成的字符串，返回构造出的字符串。
空节点使用一对空括号对 "()" 表示，转化后需要省略所有不影响字符串与原始二叉树之间的一对一映射关系的空括号对。

示例 1：
输入：root = [1,2,3,4]
输出："1(2(4))(3)"
解释：初步转化后得到 "1(2(4)())(3()())" ，但省略所有不必要的空括号对后，字符串应该是"1(2(4))(3)" 。

示例 2：
输入：root = [1,2,3,null,4]
输出："1(2()(4))(3)"
解释：和第一个示例类似，但是无法省略第一个空括号对，否则会破坏输入与输出一一映射的关系。

来源：力扣（LeetCode）
链接：https://leetcode.cn/problems/construct-string-from-binary-tree
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

 // 本题的具体思路：
 // 首先最好使用子函数递归实现，子函数可以随意控制参数的格式
 // 在子函数中 当 root为空时 返回
 // 若不为空 则在字符串中插入root的值
 // 然后开始 先转化左子树，待左子树全部转化完毕，再转化右子树
 // 当然 在转化过程中需要防止插入 无效的 ()
 //
class Solution {
public:
    void _tree2str(string& str, TreeNode* root){
        if(root == nullptr)
            return;
        
        // 使用字符数组将 val 转化为字符串
        // 因为可能有 负数的存在，所以最好按字符转化
        char valStr[30] = {0};
        sprintf(valStr, "%d", root->val);
        str += valStr;

        if(root->left){
            str += '(';
            _tree2str(str, root->left);
            str += ')';
        }
        else{
            if(root->right)
                str += "()";
            else
                return;
        }

        if(root->right){
            str += '(';
            _tree2str(str, root->right);
            str += ')';
        }
        else{        // 若 节点的右子树为空，可以直接返回，不用插入()
            return;
        }
    }

    string tree2str(TreeNode* root){
        string* ret = new string;

        _tree2str(*ret, root);
        return *ret;
    }
};