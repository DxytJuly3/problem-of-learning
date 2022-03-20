/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 
给你单链表的头节点 head ，请你反转链表，并返回反转后的链表。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/reverse-linked-list
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
 */


struct ListNode* reverseList(struct ListNode* head)
{
    if(head == NULL)
        return NULL;

    struct ListNode *prev = NULL;
    struct ListNode *cur = head;
    while(cur)
    {
        struct ListNode *next = cur->next;
        cur->next = prev;
        prev = cur;
        if(cur != NULL)
           cur = next;
    }

    return prev;
}