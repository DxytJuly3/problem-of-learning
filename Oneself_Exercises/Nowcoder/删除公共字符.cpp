/*
输入两个字符串，从第一字符串中删除第二个字符串中所有的字符。
例如，输入”They are students.”和”aeiou”，则删除之后的第一个字符
串变成”Thy r stdnts.”

输入描述：
每个测试输入包含2个字符串
输出描述：
输出删除后的字符串

示例1：
输入: They are students. aeiou
输出: Thy r stdnts.
*/

/*
思路分析：
1. 最简单的解法就是，输入完字符串之后，遍历n趟第一个字符串，每趟删除一个字符。但是 这种方法的时间复杂度是 O(M * N)
2. 可以将 第二个字符串中每个字符存储到 set 中，然后遍历第一个字符串 并在set中查找是否有这个字符，如果没有则存储到新字符串中。
此方法的时间复杂度是 O(M*logN), 因为 在set中查找的效率是 logN
暂分析出两种思路
*/
#include <iostream>
#include <string>
#include <set>
using namespace std;
/* 暴力 n*m 遍历
int main(){
    string strResult;
    string strDel;
    getline(cin, strResult);
    cin >> strDel;
    for(long long i = 0; i < strDel.length(); i++) {
        for(long long j = 0; j < strResult.length(); j++) {
            if(strDel[i] == strResult[j])
            strResult = strResult.erase(j,1);
        }
    }
    cout << strResult;
    return 0;
}*/
// set 查找
int main() {
    string str;
    set<char> del;
    getline(cin, str);
    char c;
    while(cin >> c) {
        del.insert(c);
    }
    string resultStr;
    for(long long i = 0; i < str.length(); i++) {
        if(del.find(str[i]) == del.end())
        resultStr += str[i];
    }
    cout << resultStr;
    return 0;
}