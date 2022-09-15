/*
描述
输入一行字符，分别统计出包含英文字母、空格、数字和其它字符的个数。
数据范围：输入的字符串长度满足 1≤n≤1000 1 \le n \le 1000 \ 1≤n≤1000 

输入描述：
输入一行字符串，可以有空格
输出描述：
统计其中英文字符，空格字符，数字字符，其他字符的个数

示例1
输入：
1qazxsw23 edcvfr45tgbn hy67uj m,ki89ol.\\/;p0-=\\][

输出：
26
3
10
12
来源：牛客
链接：https://www.nowcoder.com/practice/539054b4c33b4776bc350155f7abd8f5
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/
#include <iostream>
#include <string>
using namespace std;
   
int main(){
    int letterCNT = 0;
    int spaceCNT = 0;
    int numsCNT = 0;
    int otherCNT = 0;
    string inStr;
    getline(cin, inStr);
    auto sIt = inStr.begin();
    while(sIt != inStr.end()) {
        if(*sIt == ' ')
            spaceCNT++;
        else if(*sIt >= '0' && *sIt <= '9')
            numsCNT++;
        else if((*sIt >= 'a' && *sIt <= 'z') || 
                (*sIt >= 'A' && *sIt <= 'Z'))
            letterCNT++;
        else
            otherCNT++;
        
        sIt++;
    }
    cout << letterCNT << endl << spaceCNT << endl << numsCNT << endl << otherCNT << endl;
}