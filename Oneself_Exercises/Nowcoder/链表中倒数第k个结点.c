/**
 * struct ListNode {
 *	int val;
 *	struct ListNode *next;
 * };
 *
 * C语言声明定义全局变量请加上static，防止重复定义
 */

/**
 * 
 * @param pListHead ListNode类 
 * @param k int整型 
 * @return ListNode类
 */

//  输入一个链表，输出该链表中倒数第k个结点。

struct ListNode* FindKthToTail(struct ListNode* pListHead, int k )
{
    struct ListNode *slow = pListHead;
    struct ListNode *fast = pListHead;
    while(k--)
    {
        if(fast == NULL)    // k 大于链表长度 直接返回 NULL
            return NULL;
        
        fast = fast->next;
    }
    while(fast)
    {
        slow = slow->next;
        fast = fast->next;
    }

    return slow;
}