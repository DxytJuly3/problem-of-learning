/*
描述
输入一个英文句子，把句子中的单词(不区分大小写)按出现次数按从多到少把单词和次数在屏幕上输出来
次数一样的按照单词小写的字典序排序输出，要求能识别英文单词和句号。
输入描述：
输入为一行，由若干个单词和句号组成
输出描述：
输出格式参见样例。
示例1
输入：
A blockhouse is a small castle that has four openings through which to shoot.

输出：
a:2
blockhouse:1
castle:1
four:1
has:1
is:1
openings:1
shoot:1
small:1
that:1
through:1
to:1
which:1

来源：牛客（NowCoder）
链接：https://www.nowcoder.com/practice/16f59b169d904f8898d70d81d4a140a0
商业转载请联系官方授权，非商业转载请注明出处。
*/

#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
using std::vector;
using std::cout;
using std::cin;
using std::endl;
using std::map;
using std::string;

int main() {
    string str;
    getline(cin, str);
    for(int i = 0; i < str.length(); i++) {
        if(str[i] <= 'Z' && str[i] >= 'A')
            str[i] += 32;
    }
    vector<string> wordV;
    string::iterator sBegin = str.begin();
    string::iterator sEnd = str.begin();
    while(sEnd != str.end()) {
        if((*sEnd == ' ' || *sEnd == '.') && *sBegin != ' ') {
            wordV.push_back(string(sBegin, sEnd));
            sBegin = sEnd + 1;
        }
        else if(*sEnd != ' ' && *sBegin == ' ') {
            sBegin = sEnd;
        }
        sEnd++;
    }
    
    map<string, int> wordsCount;
    for(auto& word : wordV) {
        wordsCount[word]++;
    }
    map<string, int>::iterator mBegin = wordsCount.begin();
    while(mBegin != wordsCount.end()) {
        cout << mBegin->first << ':' << mBegin->second << endl;
        mBegin++;
    }
    
    return 0;
}