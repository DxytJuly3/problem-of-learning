/*
链接：https://www.nowcoder.com/questionTerminal/52d382c2a7164767bca2064c1c9d5361
来源：牛客网

密码按如下规则进行计分，并根据不同的得分为密码进行安全等级划分。

一、密码长度:
5 分: 小于等于4 个字符
10 分: 5 到7 字符
25 分: 大于等于8 个字符

二、字母:
0 分: 没有字母
10 分: 密码里的字母全都是小（大）写字母
20 分: 密码里的字母符合”大小写混合“

三、数字:
0 分: 没有数字
10 分: 1 个数字
20 分: 大于1 个数字

四、符号:
0 分: 没有符号
10 分: 1 个符号
25 分: 大于1 个符号

五、奖励（只能选符合最多的那一种奖励）:
2 分: 字母和数字
3 分: 字母、数字和符号
5 分: 大小写字母、数字和符号

最后的评分标准:
>= 90: 非常安全
>= 80: 安全（Secure）
>= 70: 非常强
>= 60: 强（Strong）
>= 50: 一般（Average）
>= 25: 弱（Weak）
>= 0:  非常弱（Very_Weak）

对应输出为：

VERY_SECURE
SECURE
VERY_STRONG
STRONG
AVERAGE
WEAK
VERY_WEAK

请根据输入的密码字符串，进行安全评定。

注：
字母：a-z, A-Z
数字：0-9
符号包含如下： (ASCII码表可以在UltraEdit的菜单view->ASCII Table查看)
!"#$%&'()*+,-./     (ASCII码：0x21~0x2F)
:;<=>?@             (ASCII码：0x3A~0x40)
[\]^_`              (ASCII码：0x5B~0x60)
{|}~                (ASCII码：0x7B~0x7E)

提示:
1 <= 字符串的长度<= 300

输入描述:
输入一个string的密码
输出描述:
输出密码等级

示例1
输入
38$@NoNoN
输出
VERY_SECURE
说明
样例的密码长度大于等于8个字符，得25分；大小写字母都有所以得20分；有两个数字，所以得20分；包含大于1符号，所以得25分；由于该密码包含大小写字母、数字和符号，所以奖励部分得5分，经统计得该密码的密码强度为25+20+20+25+5=95分。

示例2
输入
Jl)M:+
输出
AVERAGE
说明
示例2的密码强度为10+20+0+25+0=55分。
*/
/*
思路分析：
    遍历字符串 分别统计 数字的个数、大写字母的个数、小写字母的个数、其他字符的个数
    然后使用一个变量 对大小写字母的存在情况进行记录
    如果只有大写或只有小写字母 记为0, 若同时存在大小写字母 记为1, 若没有字母 记为-1
    然后 根据统计 和 条件分别加分
    然后再根据分数 输出强度
*/
#include <iostream>
#include <string>
using namespace std;
 
// 因为题目 给定了其他字符的范围, 所以最好确定范围判断一下, 防止存在其他字符(例如中文字符)也记录的情况
bool isOtherSymbol(char c) {
    if((c >= '!' && c <= '/') || (c >= ':' && c <= '@') ||
       (c >= '[' && c <= '`') || (c >= '{' && c <= '~'))
        return true;
     
    return false;
}
 
int main() {
    string passWord;
    cin >> passWord;
    int pwLenth = passWord.size()-1;
    int upperLetter = 0;
    int lowerLetter = 0;
    int both_up_lower = -1;
    int numCount = 0;
    int otherSymbol = 0;
    int score = 0;
    for(auto c : passWord){
        if(c <= 'z' && c >= 'a')
            lowerLetter++;
        else if(c <= 'Z' && c >= 'A')
            upperLetter++;
        else if(c <= '9' && c >= '0')
            numCount++;
        else if(isOtherSymbol(c))
            otherSymbol++;
    }
    // 是否同时具有大小写
    if((upperLetter == 0 && lowerLetter > 0) ||
       (upperLetter > 0 && lowerLetter == 0))
        both_up_lower = 0;
    else if(upperLetter > 0 && lowerLetter > 0)
        both_up_lower = 1;
     
    // 长度得分
    if(pwLenth <= 4)
        score += 5;
    else if(pwLenth <= 7 && pwLenth >= 5)
        score += 10;
    else if(pwLenth >= 8)
        score += 25;
    // 大小写字母得分
    if(both_up_lower == 0)
        score += 10;
    else if(both_up_lower == 1)
        score += 20;
    // 数字得分
    if(numCount == 1)
        score += 10;
    else if (numCount > 1)
        score += 20;
    // 符号得分
    if(otherSymbol == 1)
        score += 10;
    else if (otherSymbol > 1)
        score += 25;
    // 额外加分
    if(both_up_lower == 0 && numCount > 0 && otherSymbol == 0)
        score += 2;
    else if(both_up_lower == 0 && numCount > 0 && otherSymbol > 0)
        score += 3;
    else if(both_up_lower == 1 && numCount > 0 && otherSymbol > 0)
        score += 5;
     
    if(score >= 0 && score < 25)
        cout << "VERY_WEAK" << endl;   
    if(score >= 25 && score < 50)
        cout << "WEAK" << endl;   
    if(score >= 50 && score < 60)
        cout << "AVERAGE" << endl;   
    if(score >= 60 && score < 70)
        cout << "STRONG" << endl;   
    if(score >= 70 && score < 80)
        cout << "VERY_STRONG" << endl;   
    if(score >= 80 && score < 90)
        cout << "SECURE" << endl;   
    if(score >= 90)
        cout << "VERY_SECURE" << endl;
     
    return 0;
}