/*
数码管显示 4x4 矩阵式键盘键号

扫描逻辑：
P 1.4~1.7 连接行
P 1.0~1.3 连接列
P1 寄存器中,某位为 0 表示本行 或者 本列 为输入状态

默认按行扫描，即：将P1寄存器中代表 P1.4 P1.5 P1.6 P1.7 的位置地值按顺序循环置 0
表示为：1110xxxx    1101xxxx    1011xxxx    0111xxxx
扫描一直循环
然后 P1.0 P1.1 P1.2 P1.3 连接到列，按下某个键时，其所在列 在寄存器中位置 置0

当 表示某一行的位 为0 ，表示某一列的位 为0，就表示这一行和列的交点处的按钮被按下
数码管就显示这个按键表示的符号
*/


#include <REGX51.H>
#define uchar unsigned char

sbit L1 = P1^0;
sbit L2 = P1^1;
sbit L3 = P1^2;
sbit L4 = P1^3;
uchar dis[16] = { 0xc0, 0xf9, 0xa4, 0xb0, 0x99, 0x92, 0x82, 0xf8, 0x80, 0x90, 0x88, 0x83, 0xc6, 0xa1, 0x86, 0x8e };

void delay()
{
	int i,j;
	for(i = 0; i < 13; i++)
		for(j = 0; j < 255; j++);
}


int main()
{
    uchar temp;
    uchar k = 0;
    uchar i = 0;
    while(1)
    {
        P1 = 0xef;
        for(i = 0; i <= 3; i++)
        {
            if(L1 == 0)
                P0 = dis[i * 4 + 0];
            if(L2 == 0)
                P0 = dis[i * 4 + 1];
            if(L3 == 0)
                P0 = dis[i * 4 + 2];
            if(L4 == 0)
                P0 = dis[i * 4 + 3];

			delay();
            temp = P1;
            temp |= 0x0f;
            temp <<= 1;
            temp |= 0x0f;
            P1 = temp;
        }
    }

    return 0;
} 
