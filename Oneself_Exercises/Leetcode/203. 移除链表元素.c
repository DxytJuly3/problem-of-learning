/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 
给你一个链表的头节点 head 和一个整数 val 
请你删除链表中所有满足 Node.val == val 的节点，并返回 新的头节点 。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/remove-linked-list-elements
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

struct ListNode* removeElements(struct ListNode* head, int val)
{
    struct ListNode *prev = NULL;
    struct ListNode *cur = head;
    while(cur != NULL)
    {
        if(cur->val != val)
        {
            prev = cur;
            cur = cur->next;
        }
        else
        {
            struct ListNode *next = cur->next;
            if(prev == NULL)
            {//即头节点的值 就为val
                free(cur);
                head = next;            // 头节点（cur）就为 val，则head 赋予 cur释放前的next (next)
                cur = next;             // cur = cur释放前的next
            }
            else
            {
                free(cur);
                prev->next = next;      // 把prev赋予 cur释放前的位置
                cur = next;             // cur = cur释放前的next (next)
            }
        }
    }

    return head;
}