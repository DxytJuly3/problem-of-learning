/*
递归乘法。 
写一个递归函数，不使用 * 运算符， 实现两个正整数的相乘。可以使用加号、减号、位移，但要吝啬一些。

示例1:
 输入：A = 1, B = 10
 输出：10

示例2:
 输入：A = 3, B = 4
 输出：12

提示:
    保证乘法范围不会溢出


来源：力扣（LeetCode）
链接：https://leetcode.cn/problems/recursive-mulitply-lcci
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/
/*
思路分析：
    递归次数可以是 A, 所以 每次递归可以传入 A-1 和 B, 当 A == 0 是 返回0
    否则 返回 B + multiply(A - 1, B)

    但是 如果 A 太大 会造成栈溢出
    所以 A 要是 A和B 之中较小的 所以A 大时 需要交换位置
*/

class Solution {
public:
    int multiply(int A, int B) {
        if(A > B){
            int tmp = B;
            B = A;
            A = tmp;
        }
        if(A != 0)
            return B + multiply(A - 1, B);
        else
            return 0;
    }
};