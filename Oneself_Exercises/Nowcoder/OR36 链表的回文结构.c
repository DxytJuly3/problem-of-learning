/*
对于一个链表，请设计一个时间复杂度为O(n),额外空间复杂度为O(1)的算法，判断其是否为回文结构。
给定一个链表的头指针A，请返回一个bool值，代表其是否为回文结构。保证链表长度小于等于900。
测试样例：
1->2->2->1
返回：true
*/

/*
struct ListNode {
    int val;
    struct ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};*/
class PalindromeList {
public:
    struct ListNode* middleNode(struct ListNode* head)
    {
        struct ListNode *slow = head;
        struct ListNode *fast = head;
        while(fast != NULL && fast->next != NULL)
        {
            slow = slow->next;
            fast = fast->next->next;
        }

        return slow;
    }
    
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
    
    bool chkPalindrome(ListNode* A)
    {
        ListNode* cur1 = A;
        ListNode* cur2 = middleNode(A);
        cur2 = reverseList(cur2);
        
        while(cur1 && cur2)
        {
            if(cur1->val == cur2->val)
            {
                cur1 = cur1->next;
                cur2 = cur2->next;
            }
            else
            {
                return false;
            }
        }
        
        return true;
    }
};