/*
描述
某种特殊的数列a1, a2, a3, ...的定义如下：a1 = 1, a2 = 2, ... , an = 2 * an − 1 + an - 2 (n > 2)。
给出任意一个正整数k，求该数列的第k项模以32767的结果是多少？

输入描述：
第1行是测试数据的组数n，后面跟着n行输入。每组测试数据占1行，包括一个正整数k (1 ≤ k < 1000000)。
输出描述：
n行，每行输出对应一个输入。输出应是一个非负整数。

示例1
输入：
2
1
8
输出：
1
408

来源：牛客
链接：https://www.nowcoder.com/practice/1843c3b052984e3f98c68935ea3c0d79
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/*
思路分析：
    本题的思路都是需要建立表格的
    但是建立表格也有两种方式：
        1. 直接建立一个大小为 k 最大值的表格
            此方法可以通过
            不过可以进一步进行优化：
                在重复计算数列并%32767时, 可以发现每150位 就会重复
                所以只需要存储 前150个元素就可以了
                在对输入的 k % 150 选定元素
        2. 每输入一个 k 建立一个大小为 k 的表格
            经测试此方法超出时间限制, 所以需要之间建立一个最大的表格
*/

#include <iostream>
#include <map>
#include <unordered_map>
using namespace std;

int main() {
    unordered_map<long long, long long> numsTable;
    numsTable[1] = 1;
    numsTable[2] = 2;
    for(int i = 1; i <= 150; i++) {
        if(numsTable[i] == 0)
            numsTable[i] = (2*numsTable[i-1] + numsTable[i-2]) % 32767;
    }
    int n;
    cin >> n;
    for(int i = 0; i < n; i++) {
        int k;
        cin >> k;
        cout << numsTable[k%150] << endl;
    }
    
    return 0;
}