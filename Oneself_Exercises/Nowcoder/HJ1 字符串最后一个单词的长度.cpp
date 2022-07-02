/*
描述
计算字符串最后一个单词的长度，单词以空格隔开，字符串长度小于5000。（注：字符串末尾不以空格为结尾）

输入描述：
输入一行，代表要计算的字符串，非空，长度小于5000。
输出描述：
输出一个整数，表示输入字符串最后一个单词的长度。
*/

#include <iostream>
#include <string>
using namespace std;

int main()
{
    string str;
    getline(cin, str);    // 使用 getline 可以输入带空格的字符串
    
    size_t pos = str.rfind(' ');
    cout << str.size() - pos - 1 << endl;
    
    return 0;
}