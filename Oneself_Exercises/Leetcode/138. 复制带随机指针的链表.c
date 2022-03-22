/*
给你一个长度为 n 的链表，每个节点包含一个额外增加的随机指针 random ，该指针可以指向链表中的任何节点或空节点。

构造这个链表的 深拷贝。 深拷贝应该正好由 n 个 全新 节点组成,其中每个新节点的值都设为其对应的原节点的值.
新节点的 next 指针和 random 指针也都应指向复制链表中的新节点，并使原链表和复制链表中的这些指针能够表示相同的链表状态.
复制链表中的指针都不应指向原链表中的节点 。

例如，如果原链表中有 X 和 Y 两个节点，其中 X.random --> Y 。
那么在复制链表中对应的两个节点 x 和 y ，同样有 x.random --> y 。
返回复制链表的头节点。


来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/copy-list-with-random-pointer
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/**
 * Definition for a Node.
 * struct Node {
 *     int val;
 *     struct Node *next;
 *     struct Node *random;
 * };
 */

 /*
 具体思路：
 在原链表的每个节点后，复制一个 值相等的节点并链接在链表中
 即：若原链表为     7   13  11  10  1
    则复制为       7 7 13 13 11 11 10 10 1 1
然后 复制出的节点的 random 就为 前一个节点的 random (不为空的情况下)的next节点
更改完复制出的节点的 random，再把复制节点给剥离出来，并还原原链表
 */
typedef struct Node Node;

struct Node* copyRandomList(struct Node* head)
{
    // 1、复制原链表的对应新节点
    Node* cur = head;
    while(cur)
    {
        Node* newNode = (Node*)malloc(sizeof(Node));
        newNode->val = cur->val;

        newNode->next = cur->next;
        cur->next = newNode;

        cur = cur->next->next;
    }

    // 2、对复制节点random 进行更改
    cur = head;
    while(cur)
    {
        if(cur->random == NULL)
        {
            cur->next->random = NULL;
        }
        else
        {
            cur->next->random = cur->random->next;
        }
        cur = cur->next->next;
    }

    // 3、对复制节点从原链表中剥离
    cur = head;
    Node *newHead = NULL, *tail = NULL;
    while(cur)
    {
        Node* newCur = cur->next;
        Node* next = newCur->next;

        cur->next = next;
        if(tail == NULL)
        {
            newHead = tail = newCur;
        }
        else
        {
            tail->next = newCur;
            tail = newCur;
        }

        cur = next;
    }

    return newHead;
}