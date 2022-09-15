/*
描述
将一个节点数为 size 链表 m 位置到 n 位置之间的区间反转，要求时间复杂度 O(n)O(n)O(n)，空间复杂度 O(1)O(1)O(1)。
例如：
给出的链表为 1→2→3→4→5→NULL1\to 2 \to 3 \to 4 \to 5 \to NULL1→2→3→4→5→NULL, m=2,n=4m=2,n=4m=2,n=4,
返回 1→4→3→2→5→NULL1\to 4\to 3\to 2\to 5\to NULL1→4→3→2→5→NULL.

数据范围： 链表长度 0<size≤10000 < size \le 1000 0<size≤1000，0<m≤n≤size0 < m \le n \le size0<m≤n≤size，链表中每个节点的值满足 ∣val∣≤1000|val| \le 1000 ∣val∣≤1000
要求：时间复杂度 O(n)O(n)O(n) ，空间复杂度 O(n)O(n)O(n)
进阶：时间复杂度 O(n)O(n)O(n)，空间复杂度 O(1)O(1)O(1)
示例1
输入：
{1,2,3,4,5},2,4
返回值：
{1,4,3,2,5}

示例2
输入：
{5},1,1
返回值：
{5}

来源：牛客
链接：https://www.nowcoder.com/practice/539054b4c33b4776bc350155f7abd8f5
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

class Solution {
public:
    /**
     * 
     * @param head ListNode类 
     * @param m int整型 
     * @param n int整型 
     * @return ListNode类
     */
    ListNode* reverseBetween(ListNode* head, int m, int n) {
        if(m == n) {
            return head;
        }
        ListNode* prev = nullptr;
        ListNode* cur = head;
        ListNode* next = head->next;
        for(int i = 1; i < m; i++) {
            prev = cur;
            cur = cur->next;
            next = cur->next;
        }
        ListNode* fprev = prev;
        ListNode* fcur = cur;
        
        for(int i = 0; i <= n-m; i++) {
            cur->next = prev;
            prev = cur;
            cur = next;
            if(next)
                next = next->next;
        }
        
        if(!cur && !fprev)
            head = prev;
        else if(!cur && fprev) {
            fprev->next = prev;
            fcur->next = next;
        }
        else if(!fprev && cur) {
            head = prev;
            fcur->next = cur;
        }
        else {
            fprev->next = prev;
            fcur->next = cur;
        }
        
        return head;
    }
};