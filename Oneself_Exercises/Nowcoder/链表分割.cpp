/*
现有一链表的头指针 ListNode* pHead，给一定值x，编写一段代码将所有小于x的结点排在其余结点之前
且不能改变原来的数据顺序，返回重新排列后的链表的头指针。
*/

/*
struct ListNode {
    int val;
    struct ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};*/
class Partition {
public:
    struct ListNode* partition(ListNode* pHead, int x)
    {
        // 创建带哨兵位的链表
        struct ListNode* lessList = NULL, *lessTail = NULL, *greaterList = NULL, *greaterTail = NULL;
        lessList = lessTail = (struct ListNode*)malloc(sizeof(struct ListNode));
        greaterList = greaterTail = (struct ListNode*)malloc(sizeof(struct ListNode));
         
        lessTail->next = greaterTail->next = NULL;
         
        struct ListNode* cur = pHead;
        while(cur)
        {
            struct ListNode* next = cur->next;
            if(cur->val < x)
            {
                lessTail->next = cur;
                lessTail = cur;
            }
            else
            {
                greaterTail->next = cur;
                greaterTail = cur;
            }
            cur = cur->next;
        }
         
        lessTail->next = greaterList->next;
        greaterTail->next = NULL;            // 注意尾节点的 next 指向NULL，表示链表结束
         
        struct ListNode* newList = lessList->next;
        free(lessList);
        free(greaterList);
        lessList = NULL;
        greaterList = NULL;
         
        return newList;
    }
};