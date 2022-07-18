/*
本题思路：
遍历单链表, 将每个节点数据存入vector, 然后逆置vector
注意 遍历单链表的控制

官方思路：
遍历入栈，然后出栈存入数据
官方的好处在于 利用了栈的特性，且没有使用库逆置函数
当然vector逆置也可以手动写
*/

/*
输入一个链表的头节点，从尾到头反过来返回每个节点的值（用数组返回）

示例 1：
输入：head = [1,3,2]
输出：[2,3,1]

来源：力扣（LeetCode）
链接：https://leetcode.cn/problems/cong-wei-dao-tou-da-yin-lian-biao-lcof
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution
{
public:
    vector<int> reversePrint(ListNode* head)
    {
        vector<int> retArray;
        ListNode* cur = head;
        while(cur != nullptr)
        {
            retArray.push_back(cur->val);
            cur = cur->next;
        }
        reverse(retArray.begin(), retArray.end());
        return retArray;
    }
    /* 官方思路实现：
    vector<int> reversePrint(ListNode* head)
    {
        vector<int> retArray;
        stack<int> tmpStack;
        ListNode* cur = head;
        while(cur != nullptr)
        {
            tmpStack.push(cur->val);
            cur = cur->next;
        }
        while(!tmpStack.empty())
        {
            retArray.push_back(tmpStack.top());
            tmpStack.pop();
        }

        return retArray;
    }*/
};