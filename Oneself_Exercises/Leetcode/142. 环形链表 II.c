/*
给定一个链表的头节点  head ，返回链表开始入环的第一个节点。 如果链表无环，则返回 null。

如果链表中有某个节点，可以通过连续跟踪 next 指针再次到达，则链表中存在环。 
为了表示给定链表中的环，评测系统内部使用整数 pos 来表示链表尾连接到链表中的位置（索引从 0 开始）。
如果 pos 是 -1，则在该链表中没有环。
注意：pos 不作为参数进行传递，仅仅是为了标识链表的实际情况。
不允许修改 链表。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/linked-list-cycle-ii
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
这一题，最好能够画图表示出来，
快指针 一次走两步，慢指针 一次走一步
设  头节点 到 入环节点 的距离是 L
    入环节点 到 快指针第一次追上慢指针的位置 的距离是 X     
    // 这里 从慢指针入环开始，到慢指针被追上，慢指针肯定没有走超过一圈

    环长是 C
所以可以计算    
快慢指针第一次相遇时：
                快指针所走距离：lenFast = L + N*C + X  (这里必须画图解释)
                慢指针所走举例：lenSlow = L + X;
                因为 快指针的速度 是 慢指针速度的 二倍
                所以 2* lenSlow == lenFast
                即   2 * (L + X) == L + N * C + X
                即   L + X = N * C
                即   L = N * C - X
由此时，L = N * C - X
可推断出（画图！！！）：
此时(快指针第一次与慢指针相遇的时候)，若有一个指针逐步从链表头节点移向下一位，
同时有另一个指针逐步从 快慢指针第一次相遇点移向下一位
这两个指针一定会在链表的入环节点相遇，相遇节点即为入环节点
*/
 typedef struct ListNode ListNode;

struct ListNode *detectCycle(struct ListNode *head)
{
    ListNode* fastp = head;
    ListNode* slowp = head;
    ListNode* Head = head;

    while(fastp && fastp->next)
    {
        fastp = fastp->next->next;
        slowp = slowp->next;

        if(slowp == fastp)
        {
            while(Head != fastp)
            {
                Head = Head->next;
                fastp = fastp->next;
            }
            return Head;
        }
    }

    return NULL;
}