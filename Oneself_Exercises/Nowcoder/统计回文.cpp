/*
链接：https://www.nowcoder.com/questionTerminal/9d1559511b3849deaa71b576fa7009dc
来源：牛客网

“回文串”是一个正读和反读都一样的字符串，比如“level”或者“noon”等等就是回文串。
花花非常喜欢这种拥有对称美的回文串，生日的时候她得到两个礼物分别是字符串A和字符串B。
现在她非常好奇有没有办法将字符串B插入字符串A使产生的字符串是一个回文串。
你接受花花的请求，帮助她寻找有多少种插入办法可以使新串是一个回文串。如果字符串B插入的位置不同就考虑为不一样的办法。
例如：
A = “aba”，B = “b”。这里有4种把B插入A的办法：
* 在A的第一个字母之前: "baba" 不是回文
* 在第一个字母‘a’之后: "abba" 是回文
* 在字母‘b’之后: "abba" 是回文
* 在第二个字母'a'之后 "abab" 不是回文
所以满足条件的答案为2

输入描述:
每组输入数据共两行。
第一行为字符串A
第二行为字符串B
字符串长度均小于100且只包含小写字母

输出描述:
输出一个数字，表示把字符串B插入字符串A之后构成一个回文串的方法数

示例1
输入
aba
b

输出
2

*/
/*
题意分析：
    输入字符串 strA 和 strB
    将 strB 插入 strA的不同位置，统计有插入后的新字符串多少个是回文串
思路分析：
    strB 插入 strA 有多少种情况呢？ strB 可以插入 strB的首字符之前 到 尾字符之后
    需要对每个插入后的字符串判断是否回文，所以需要循环遍历 strA
    使用迭代器遍历 strA, 在循环内创建 strC 用于存储插入后的字符
        为什么要用strC存储插入后的字符，而不是直接将strB插入strA中？
        1. 如果直接在strA上操作, 如果复原strA, 则会影响下一次插入的操作. 复原 strA 浪费时间
        2. 直接在strA上插入strB, 需要挪动数据影响效率
        
    strC 怎么存储插入后的字符串？
        分 3或2 种情况：
        1. 当 迭代器=strA.begin() 时, 
           属于在首字符之前插入strB, 直接在 strC 尾插 strB 和 strA(需要先尾插strB)
        2. 当 迭代器=strA.end() 时,
           属于在尾字符之后插入strB, 直接在 strC 尾插 strA 和 strB(需要先尾插strA)
        3. 当迭代器 != strA.begin(), 也 != strA.end() 时 (情况2也适用于情况3)
           属于在其他位置插入 strB, 则需要先后插入：
            1. strA的 [begin(), 迭代器) 区间
            2. strB
            3. strA的 [迭代器, end()) 区间
            
    然后对 strC 判断是否回文, 并统计
    判断是否回文串 可以定义函数: bool isPalindrome(string& str)
    使用两个指针(迭代器) 一个首字符begin, 一个末字符end
    循环判断 两指针指向空间的内容是否相等, 直到 begin 与 end相遇 或 begin > end
    如果期间出现 内容不相等的情况 直接 返回 false
    循环结束 则表示是回文 然后返回 true
*/

#include <iostream>
#include <string>
using namespace std;

bool isPalindrome(string& str) {
    auto strBegin = str.begin();
    auto strEnd = str.end() - 1;
    while(strBegin <= strEnd) {
        if(*strBegin == *strEnd) {
            strBegin++;
            strEnd--;
        }
        else
            return false;
    }
    
    return true;
}

int main() {
    string strA;
    string strB;
    int palCount = 0;
    getline(cin, strA);
    getline(cin, strB);
    auto strIt = strA.begin();
    while(strIt != strA.end() + 1) {
        string strC;
        if(strIt == strA.begin()) {
            strC += strB;
            strC += strA;
        }
        else if(strIt == strA.end()){
            strC += strA;
            strC += strB;
        }
        else {
            strC.append(strA.begin(), strIt);
            strC += strB;
            strC.append(strIt, strA.end());
        }
        if(isPalindrome(strC))
            palCount++;
        
        strIt++;
    }
    cout << palCount;
    
    return 0;
}