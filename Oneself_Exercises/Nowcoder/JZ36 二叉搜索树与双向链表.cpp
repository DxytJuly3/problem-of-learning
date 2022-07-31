/*
 输入一棵二叉搜索树，将该二叉搜索树转换成一个排序的双向链表。如下图所示

数据范围：输入二叉树的节点数 0≤n≤10000 \le n \le 10000≤n≤1000，二叉树中每个节点的值 0≤val≤10000\le val \le 10000≤val≤1000
要求：空间复杂度O(1)O(1)O(1)（即在原树上操作），时间复杂度 O(n)O(n)O(n)

注意:
1.要求不能创建任何新的结点，只能调整树中结点指针的指向。当转化完成以后，树中节点的左指针需要指向前驱，树中节点的右指针需要指向后继
2.返回链表中的第一个节点的指针
3.函数返回的TreeNode，有左右指针，其实可以看成一个双向链表的数据结构
4.你不用输出双向链表，程序会根据你的返回值自动打印输出
输入描述：
二叉树的根节点
返回值描述：
双向链表的其中一个头节点。
示例1
输入：
{10,6,14,4,8,12,16}
返回值：
From left to right are:4,6,8,10,12,14,16;From right to left are:16,14,12,10,8,6,4;
说明：
输入题面图中二叉树，输出的时候将双向链表的头节点返回即可。     

示例2
输入：
{5,4,#,3,#,2,#,1}
返回值：
From left to right are:1,2,3,4,5;From right to left are:5,4,3,2,1;
说明：

                    5
                  /
                4
              /
            3
          /
        2
      /
    1
树的形状如上图       
*/

/*
struct TreeNode {
	int val;
	struct TreeNode *left;
	struct TreeNode *right;
	TreeNode(int x) :
			val(x), left(NULL), right(NULL) {
	}
};
来源：牛客网（NowCoder）
链接：https://www.nowcoder.com/practice/947f6eb80d944a84850b0538bf0ec3a5
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

// 思路：
// 本题的要求是，不创建新节点的情况下，原地将二叉搜索树改为排序双向链表
// 其实就是要求 中序遍历 并原地修改为双向链表
// 其实就是需要 将节点的left 指向中序遍历的prev，将节点的 right指向中序遍历的next
class Solution {
public:
    void InOrder(TreeNode* cur, TreeNode*& prev) {
        if(cur == nullptr)
            return;
        
        InOrder(cur->left, prev);
        
        cur->left = prev;
        if(prev)
            prev->right = cur;
        prev = cur;
        
        InOrder(cur->right, prev);
    }
    TreeNode* Convert(TreeNode* pRootOfTree) {
        if(pRootOfTree == nullptr)
            return nullptr;
        
        TreeNode* Prev = nullptr;
        InOrder(pRootOfTree, Prev);
        
        TreeNode* Head = pRootOfTree;
        while(Head->left)
            Head = Head->left;
        
        return Head;
    }
};