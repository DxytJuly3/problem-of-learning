/*
给你一个单链表的引用结点 head。链表中每个结点的值不是 0 就是 1。
已知此链表是一个整数数字的二进制表示形式。
请你返回该链表所表示数字的 十进制值 。

示例 1：
输入：head = [1,0,1]
输出：5
解释：二进制数 (101) 转化为十进制数 (5)

示例 2：
输入：head = [0]
输出：0

示例 3：
输入：head = [1]
输出：1

示例 4：
输入：head = [1,0,0,1,0,0,1,1,1,0,0,0,0,0,0]
输出：18880

示例 5：
输入：head = [0,0]
输出：0

提示：
    链表不为空。
    链表的结点总数不超过 30。
    每个结点的值不是 0 就是 1。

来源：力扣（LeetCode）
链接：https://leetcode.cn/problems/convert-binary-number-in-a-linked-list-to-integer
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/
 /*
 思路分析：
    思路1：
        先遍历一边链表, 将链表的数值以字符的形式存储到字符串中, 然后遍历一遍字符串计算最终的二进制
    思路2：
        先将链表第一个节点的值 作为结果, 如果此节点没有下一个节点, 则返回最终值
        如果此节点还有下一个节点, 则将结果×2, 并将结果加上下一个节点的值, 再进入下一个节点
        直到链表遍历结束
 */
class Solution {
public:
    // 思路1:
    /*int getDecimalValue(ListNode* head) {
        string binaryNum;
        while(head != nullptr) {
            binaryNum += head->val + '0';

            head = head->next;
        }
        int ret = 0;
        for(int i = binaryNum.size()-1, j = 0; i >= 0; i--, j++) {
            ret += (binaryNum[j]-'0') * pow(2, i);
        }

        return ret;
    }*/
    // 思路2：
    int getDecimalValue(ListNode* head) {
        int ret = head->val;
        while(head != nullptr) {
            if(head->next != nullptr)
                ret = ret*2 + head->next->val;
            else
                return ret;

            head = head->next;
        }

        return ret;
    }
};