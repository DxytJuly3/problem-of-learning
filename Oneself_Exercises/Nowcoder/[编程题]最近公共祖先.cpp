/*
链接：https://www.nowcoder.com/questionTerminal/70e00e490b454006976c1fdf47f155d9
来源：牛客网

将一棵无穷大满二叉树的结点按根结点一层一层地从左往右编号，根结点编号为1。现给定a，b为两个结点。设计一个算法，返回a、b最近的公共祖先的编号。注意其祖先也可能是结点本身。
测试样例：
2，3
返回：
1
*/
/*
题意分析：
    满二叉树的节点编号 从 1 开始, 层序遍历 从左往右编号
    给定两个节点的编号, 返回这两个节点的 最近公共祖先
思路分析：
                1
           /        \
          2          3
        /  \       /   \
       4    5     6     7
      / \  / \   / \   / \
     8  9 10 11 12 13 14  15
      
     以上树为例：
     除根节点以外, 左孩子都是偶数, 右孩子都是奇数
     右孩子的父节点编号 是 (其编号-1)/2, 左孩子的父亲节点是 其编号/2
     思路1：
        从两个节点的编号向上推出所有的 父亲节点, 并记录
        在对比记录的节点编号, 求出最近公共祖先
        此思路将题转化成了 类链表相交问题
*/
class LCA {
public:
    // 思路1：
    int getLCA(int a, int b) {
        vector<int> parA;
        vector<int> parB;
        while(a != 0) {
            parA.push_back(a);
            a /= 2;
        }
        while(b != 0) {
            parB.push_back(b);
            b /= 2;
        }
        auto aIt = parA.begin();
        auto bIt = parB.begin();
        if(parA.size() > parB.size())
            aIt = aIt + parA.size() - parB.size();
        else
            bIt = bIt + parB.size() - parA.size();
         
        while(*bIt != *aIt) {
            bIt++;
            aIt++;
        }
         
        return *bIt;
    }
};