/*
链接：https://www.nowcoder.com/questionTerminal/30c1674ad5694b3f8f0bc2de6f005490
来源：牛客网

给定两个32位整数n和m，同时给定i和j，将m的二进制数位插入到n的二进制的第j到第i位,保证n的第j到第i位均为零，且m的二进制位数小于等于i-j+1，其中二进制的位数从0开始由低到高。
测试样例：
1024，19，2，6
返回：
1100
*/
/*
题意分析：
    给定两个 int整数, 将n二进制位的第 j ~ i 位替换为 m的二进制位, i-j如果大于m的位数, 则只替换m对应位
    然后返回替换过后的 n 的值
    末位 为 0
思路分析：
    使用string 统计n和m的二进制位, 之后将n的 j~i 位替换为m
    然后再遍历string 计算十进制值
*/
// 第一次的最捞的写法
class BinInsert {
public:
    int binInsert(int n, int m, int j, int i) {
        string strN;
        string strM;
        while(n != 0) {
            if((n & 1) == 1)
                strN += '1';
            else
                strN += '0';
            n >>= 1;
        }
        while(m != 0) {
            if((m & 1) == 1)
                strM += '1';
            else
                strM += '0';
            m >>= 1;
        }
        string strRet;
        for(int k = 0; k < j; k++)
            strRet += strN[k];
        strRet += strM;
        for(int k = strM.length()+j; k < strN.length(); k++)
            strRet += strN[k];
         
        int ret = 0;
        for(int l = 0; l < strRet.length(); l++) {
            ret += (strRet[l]-'0') * pow(2,l);
        }
         
        return ret;
    }
};

// 直接位运算, 因为是替换对应二进制位的数, 而不是将所有位覆盖 不会改变位数 所以可以直接 |
class BinInsert {
public:
    int binInsert(int n, int m, int j, int i) {
        return n | (m << j);
    }
};