/*
给你两个单链表的头节点 headA 和 headB ，请你找出并返回两个单链表相交的起始节点。
如果两个链表不存在相交节点，返回 null 。


来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/intersection-of-two-linked-lists
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */

 /*
 思路：
 求出长链表比短链表 长出的长度 len
 并让长链表先走 len 步
 保证 开始比较的节点 到 首 相交节点的距离相等
 然后开始对比 直到对比到的节点相等
 */
typedef struct ListNode ListNode;

struct ListNode *getIntersectionNode(struct ListNode *headA, struct ListNode *headB)
{
    if(headA == NULL || headB == NULL)
    {
        return NULL;
    }
    
    ListNode *tailA = headA, *tailB = headB;
    int LenB = 0;
    int LenA = 0;
    while(tailA)
    {
        ++LenA;
        tailA = tailA->next;
    }
    while(tailB)
    {
        ++LenB;
        tailB = tailB->next;
    }

    ListNode *longList = headA, *shortList = headB;
    if(LenB > LenA)
    {//如果 lenB 长，则长链表的头节点就是 headB
        longList = headB;
        shortList = headA;
    }
    int len = abs(LenB - LenA);
    while(len--)
    {
        longList = longList->next;
    }
    while(longList && shortList)
    {
        if(longList == shortList) 
            return longList;
        
        longList = longList->next;
        shortList = shortList->next;
    }

    return NULL;
}