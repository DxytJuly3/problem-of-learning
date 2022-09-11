/*
在日常书面表达中，我们经常会碰到很长的单词，比如"localization"、"internationalization"等。
为了书写方便，我们会将太长的单词进行缩写。这里进行如下定义：
如果一个单词包含的字符个数达到或者超过10则我们认为它是一个长单词。
所有的长单词都需要进行缩写，缩写的方法是先写下这个单词的首尾字符，然后再在首尾字符中间写上这个单词去掉首尾字符后所包含的字符个数。
比如"localization"缩写后得到的是"l10n"，"internationalization"缩写后得到的是"i18n"。现给出n个单词，将其中的长单词进行缩写，其余的按原样输出。

输入描述：
第一行包含要给整数n。1≤n≤100
接下来n行每行包含一个由小写英文字符构成的字符串，字符串长度不超过100。
输出描述：
按顺序输出处理后的每个单词。

来源：牛客网
地址：https://www.nowcoder.com/practice/af2c953f9fc8464fa0e3252da8eb4131
*/
/*
思路分析：
    使用string 存储输入的单词 如果此 string的length >= 10 则 输出 头length-2尾
                           否则 直接输出此string
*/

#include <iostream>
#include <string>
using namespace std;

int main() {
    int n;
    cin >> n;
    for(int i = 0; i < n; i++) {
        string word;
        cin >> word;
        if(word.size() >= 10) {
            cout << *word.begin() << word.size() - 2 << *(word.end()-1) << endl;
        }
        else {
            cout << word << endl;
        }
    }
    
    return 0;
}