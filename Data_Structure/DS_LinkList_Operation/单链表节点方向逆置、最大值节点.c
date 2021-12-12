void InverseNode(LinkList head)
{//单链表节点方向逆置
    ListNode* p = head->next;
    head->next = NULL;
    while (p != NULL)
    {
        ListNode* q = p->next;
        p->next = head->next;
        head->next = p;
        p = q;
    }
}

ListNode* MaxNode(LinkList head)
{//寻找单链表中数据域 值最大的节点 及最大值
    ListNode* p = head->next;   //从首元结点比较
    ListNode* maxp = p;
    long long max = p->data;
    while (p != NULL)   //直到p为NULL
    {
        if (max < p->data)
        {
            max = p->data;
            maxp = p;
        }       
        if (p->next != NULL)
            p = p->next;
        else
            break;
    }
    printf("%lld\n", max);

    return maxp;
}

