/*
给定两个用链表表示的整数，每个节点包含一个数位。
这些数位是反向存放的，也就是个位排在链表首部。
编写函数对这两个整数求和，并用链表形式返回结果

示例：
输入：(7 -> 1 -> 6) + (5 -> 9 -> 2)，即617 + 295
输出：2 -> 1 -> 9，即912

进阶：思考一下，假设这些数位是正向存放的，又该如何解决呢?

示例：
输入：(6 -> 1 -> 7) + (2 -> 9 -> 5)，即617 + 295
输出：9 -> 1 -> 2，即912

来源：力扣（LeetCode）
链接：https://leetcode.cn/problems/sum-lists-lcci
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
/*
思路分析：
    1. 两链表数位反向
        同时遍历两个链表, 计算对应两个数位的和(需要加进位), 记录进位和余数
        对新链表插入余数, 或者直接修改长的旧链表
        怎么写？
        首先判断长链表并记录长链表的首节点 以便于返回
        然后遍历短链表次数 进行位数相加 记录进位 和 余数, 将余数作为长链表当前节点的新值
        出循环之后 进位可能不是0, 进位不是0 时, 也有两种情况
            1. l1 和 l2 长度相等, 则需要在返回的链表尾 插入值为进位值得新节点
            2. 则需要继续在长链表上 位数相加 记录进位、余数 将余数作为长链表当前节点的新值, 直到进位为0

    2. 两链表位数正向
        如果提供了创建链表的接口, 则可以先遍历两个链表 将链表各节点的值分别存储到 两个string中
        然后反向遍历两个string 用相同的计算方法计算, 并创建新链表

        如果要求 空间复杂度为 O(1):
        
*/
class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode* curL = l1;
        ListNode* curS = l2;
        int carry = 0;
        while(curS != nullptr && curL != nullptr) {
            curL = curL->next;
            curS = curS->next;
        }
        if(curL == nullptr) {
            curL = l2;
            curS = l1;
        }
        else {
            curL = l1;
            curS = l2;
        }
        ListNode* retNode = curL;

        ListNode* prevL = nullptr;
        while(curS != nullptr) {
            int sum = curS->val + curL->val + carry; 
            int remainder = sum % 10;
            curL->val = remainder;
            prevL = curL;
            curL = curL->next;
            curS = curS->next;
            carry = sum / 10;
        }
        while(carry != 0) {
            if(!curL) {
                ListNode* newNode = new ListNode(carry);
                prevL->next = newNode;
                break;
            }
            else {
                int sum = curL->val + carry; 
                int remainder = sum % 10;
                curL->val = remainder;
                prevL = curL;
                curL = curL->next;
                carry = sum / 10;
            }
        }

        return retNode;
    }
};