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
// 本题的要求是，不创建新节点的情况下，原地将二叉搜索树改为排序 双向链表
// 排序：即要求类中序遍历；双向链表：即要求 按中序遍历连接前后
// 分析：
//    在示例中，先递归左树 至 4节点时，应将其left 指nullptr，将其 right 指向 6节点，但是，此时从 4节点 找不到 6节点
//  不过，在 4节点找不到 6节点，但是 在6节点 可以找到 4节点，可以在 6节点时，把4节点的 right 指向6节点
//    当递归到 8节点处时，应该左连6节点，右连10节点的，但是两个都找不到

// 那么 本题应该怎么解决呢？
//    思路就是，既然 left 和 right 可能找不到节点，则可以记录上一个修改过的节点为prev
//    此时 当前节点的left即为prev：prev 刚开始为 nullptr，即 4的left为nullptr；到8节点时，prev为6节点，即 8的left 为 6节点
//    并且，像 8节点这样，即使记录prev也找不到 10节点
//    那么就可以：当递归到10节点时， prev刚好为 8节点 (prev记录上一个修改过的节点)，再将prev的right指向自己
//    可以解决 right 找不到节点的问题
//  即 在 6节点处 连接 4节点的right，在 8节点处 连接 6节点的right，在 10节点处 连接 8节点的right…………
//       6节点的prev是4节点           8节点的prev是6节点           10节点的prev是8节点
//
// 程序怎么写呢？
//    肯定不能修改原函数的参数，所以需要一个子函数，子函数参数 一个传当前节点，一个传记录的prev
//    然后按照 先递归左子树，然后修改节点的连接，最后递归右子树 的顺序进行 中序遍历连接
//    修改节点的连接操作：
//        首先是 当前节点的left 指向记录的 prev节点，但是 不对当前节点的right进行连接，right需要在修改下一个节点连接关系时修改
//        然后 如果 prev不为空，不为空，prev的right应该指向当前节点
//        最后 将当前节点记录为 新的prev 就 OK了
// 传参 全部递归完成之后，再找新链表的头节点，返回头节点就好了
//
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