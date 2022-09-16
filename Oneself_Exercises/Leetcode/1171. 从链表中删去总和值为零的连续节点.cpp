/*
给你一个链表的头节点 head，请你编写代码，反复删去链表中由 总和 值为 0 的连续节点组成的序列，直到不存在这样的序列为止。
删除完毕后，请你返回最终结果链表的头节点。

你可以返回任何满足题目要求的答案。
（注意，下面示例中的所有序列，都是对 ListNode 对象序列化的表示。）

示例 1：
输入：head = [1,2,-3,3,1]
输出：[3,1]
提示：答案 [1,2,1] 也是正确的。

示例 2：
输入：head = [1,2,3,-3,4]
输出：[1,2,4]

示例 3：
输入：head = [1,2,3,-3,-2]
输出：[1]

提示：
    给你的链表中可能有 1 到 1000 个节点。
    对于链表中的每个节点，节点的值：-1000 <= node.val <= 1000.

来源：力扣（LeetCode）
链接：https://leetcode.cn/problems/remove-zero-sum-consecutive-nodes-from-linked-list
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
/*
思路分析：
    删除链表中的总和值为0的 连续节点   重点：要求删除的是连续节点
    以 数组为例寻找思路：
    1 2 3 -3 4 5 -5 1 2 3 -6 7 8 -8 9
    怎么删除总和为 0 的连续值?
    可以求 前缀和, 即 0 到 当前位 的和:
    1 3 6 3 7 12 7 8 10 13 7 14 22 14 9
    可以发现 1 和 3位相等; 4 和 6、10位相等; 11 和 13位相等
    就可以知道 2 3位和为0; 5 6位相加和为0; 7 8 9 10位相加和为0; 12 13位相加和为0
    那么就可以将 2 3 5 6 7 8 9 10 12 13 位的元素删除
    即 遇到与 之前的前缀和 相同的 前缀和 时, 将 (上一个前缀和位, 当前前缀和位] 的元素全部删除
    链表中该如何操作呢？
    可以遍历链表 用哈希表存储 前缀和 以及 节点的位置
    如果当前前缀和没有在哈希表中出现过, 则将 前缀和 和 节点位置放入哈希表中
    如果已经出现过, 则 将上一个前缀和的节点的 next 直接指向 当前前缀和的next
        并将 哈希表中的 (上一个前缀和, 当前节点的前缀和] 删除
*/
class Solution {
public:
    ListNode* removeZeroSumSublists(ListNode* head) {
        unordered_map<int, ListNode*> sumTable;
        // 以后记得使用虚拟头节点
        ListNode* dummyNode = new ListNode(0);
        dummyNode->next = head;

        sumTable[0] = dummyNode;
        ListNode* cur = head;
        int sum = 0;
        while(cur != nullptr) {
            sum += cur->val;
            if(sumTable.find(sum) != sumTable.end()) {
                // 哈希表中已经存在当前的前缀和
                ListNode* tmpNode = sumTable[sum]->next;    // 记录哈希表中上一个前缀和记录的节点
                sumTable[sum]->next = cur->next;
                int tmpSum = sum;
                while(tmpNode != cur) {
                    // 记录上一个前缀和记录的节点是为了确定删除 哈希表中数据 循环的次数
                    tmpSum += tmpNode->val;
                    sumTable.erase(tmpSum);
                    tmpNode = tmpNode->next;
                }
            }
            else {
                // 哈希表中没有当前前缀和
                sumTable[sum] = cur;
            }
            cur = cur->next;
        }

        return dummyNode->next;
    }
};