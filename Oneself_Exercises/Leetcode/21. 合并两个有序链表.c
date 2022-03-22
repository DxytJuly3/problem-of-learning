/* 
将两个升序链表合并为一个新的 升序 链表并返回。新链表是通过拼接给定的两个链表的所有节点组成的。 

示例 1：

输入：l1 = [1,2,4], l2 = [1,3,4]
输出：[1,1,2,3,4,4]

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/merge-two-sorted-lists
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。*/


/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
typedef struct ListNode ListNode;

/* 不带哨兵位的头结点的链表
struct ListNode* mergeTwoLists(struct ListNode* list1, struct ListNode* list2)
{
    if(list1 == NULL)
        return list2;
    if(list2 == NULL)
        return list1;

    // 创建新链表的首节点，并用 tail 一直记录新链表的尾节点
    ListNode* newHead = NULL, *tail = NULL;

    ListNode* cur1 = list1;
    ListNode* cur2 = list2;

    while(cur1 && cur2)
    {
        if(cur1->val <= cur2->val)
        {
            // 新链表的首节点为空
            if(tail == NULL)
            {
                newHead = tail = cur1;      // 首节点为空 则 将newNode 和 tail 赋予cur1
            }
            else
            {
                tail->next = cur1;          // cur1 尾插至新链表 即 tail的next
                tail = cur1;                // tail 重新表示尾
            }

            cur1 = cur1->next;              // cur1 移向后一节点
        }
        else
        {
            // 新链表的首节点为空
            if(tail == NULL)
            {
                newHead = tail = cur2;      // 首节点为空 则 将newNode 和 tail 赋予cur1
            }
            else
            {
                tail->next = cur2;          // cur1 尾插至新链表 即 tail的next
                tail = cur2;                // tail 重新表示尾
            }

            cur2 = cur2->next;              // cur1 移向后一节点
        }
    }
    
    // 判断两个链表哪个没有遍历完  直接连接在新链表之后
    if(cur1)
    {
        tail->next = cur1;
    }
    if(cur2)
    {
        tail->next = cur2;
    }

    return newHead;
} */

// 带哨兵位的头结点的链表
struct ListNode* mergeTwoLists(struct ListNode* list1, struct ListNode* list2)
{
    if(list1 == NULL)
        return list2;
    if(list2 == NULL)
        return list1;

    // 创建新链表的首节点，并用 tail 一直记录新链表的尾节点
    ListNode* newHead = NULL, *tail = NULL;
    newHead = tail = (ListNode*)malloc(sizeof(ListNode));

    ListNode* cur1 = list1;
    ListNode* cur2 = list2;

    while(cur1 && cur2)
    {
        // 因为带哨兵位 所以 判断节点值大小之后，直接尾插就可以了，不用再判断是否为首节点 
        if(cur1->val <= cur2->val)
        {
            tail->next = cur1;          // cur1 尾插至新链表 即 tail的next
            tail = cur1;                // tail 重新表示尾

            cur1 = cur1->next;              // cur1 移向后一节点
        }
        else
        {
            tail->next = cur2;          // cur1 尾插至新链表 即 tail的next
            tail = cur2;                // tail 重新表示尾

            cur2 = cur2->next;              // cur1 移向后一节点
        }
    }
    // 判断两个链表哪个没有遍历完  直接连接在新链表之后
    if(cur1)
    {
        tail->next = cur1;
    }
    if(cur2)
    {
        tail->next = cur2;
    }

    ListNode* Head = newHead->next;
    free(newHead);
    return Head;
}