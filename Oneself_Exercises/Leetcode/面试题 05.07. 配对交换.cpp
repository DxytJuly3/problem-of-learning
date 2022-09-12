/*
配对交换。
编写程序，交换某个整数的奇数位和偶数位，尽量使用较少的指令（也就是说，位0与位1交换，位2与位3交换，以此类推）。
示例1:
 输入：num = 2（或者0b10）
 输出 1 (或者 0b01)

示例2:
 输入：num = 3
 输出：3
 
提示:
    num的范围在[0, 2^30 - 1]之间，不会发生整数溢出。

来源：力扣（LeetCode）
链接：https://leetcode.cn/problems/exchange-lcci
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/
/*
思路分析：
    不能直接操作原数的位, 但是可以将 原数的二进制位的奇数位和偶数位提取出来
    然后将其错位 再合并到一起
    怎么提取 奇数位 和 偶数位？
    一个数 & 上 ↓↓↓
    10101010 10101010 10101010 10101010 
    就可以将其 奇数位 提取出来
    例如 00000000 00000000 00000000 11111111 &
        10101010 10101010 10101010 10101010 -> 00000000 00000000 00000000 10101010

    一个数 & 上 ↓↓↓
    01010101 01010101 01010101 01010101
    就可以将其 偶数位提取出来
    例如 00000000 00000000 00000000 11111111 &
        01010101 01010101 01010101 01010101 -> 00000000 00000000 00000000 01010101
    
    又由于 奇数位 和 偶数位需要 换位
    所以 需要将提取出来的奇数位 向右移一位 , 将提取出来的偶数位 向左移一位
    然后 再将 移动过的提取位数 | 起来

    注意 优先级结合
*/
class Solution {
public:
    int exchangeBits(int num) {
        return ((num & 0xaaaaaaaa) >> 1) | ((num & 0x55555555) << 1);
    }
};