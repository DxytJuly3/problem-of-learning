#include <reg51.h>

void Delay(unsigned int i)
{
    unsigned int j;
    while(i--)
    {
        for(j = 0; j < 255 ; j++)
        {}
    }
}

int main()
{
    TMOD = 0x05;		// 0 0 0 0 0 1 0 1
    TH0 = 0xff;
    TL0 = 0xfc;
    EA = 1;
    ET0 = 1;
    TR0 = 1;
    while(1);

    return 0;
}

void T0_int(void)   interrupt 0
{
    while(1)
    {
        P1 = 0xf0;
        Delay(200);
        P1 = 0x0f;
        Delay(200);
    }
}