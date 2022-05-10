#include <REGX51.H>

void Delay(unsigned int i)
{
    unsigned int j = 0;
    while(i--)
    {
        for(j; j < 125; j++)
        {}
    }
}

int main()
{
    unsigned char display[] = { 0xff, 0xfe, 0xfd, 0xfb, 0xf7, 0xef, 0xdf, 0xbf, 0x7f};
    unsigned int times = 0;
    while(1)
    {
        EA = 1;
        EX0 = 1;
        EX1 = 1;
        IT0 = 1;
        IT1 = 1;
        IP = 0;
        for(times = 0; times < 9; times++)
        {
            Delay(10000);
            P1 = display[times];
        }
    }

    return 0;
}


void int0_isr(void)  interrupt 0
{
    unsigned char n = 0;
    for(n = 0; n < 10; n++)
    {
        P1 = 0x0f;              // 高四位亮
        Delay(10000);
        P1 = 0xf0;              // 低四位亮
        Delay(10000);
    }
} 

void int1_isr(void)	 interrupt 2
{
    unsigned char m = 0;
    for(m = 0; m < 10; m++)
    {
        P1 = 0xff;              // 全灭
        Delay(10000);
        P1 = 0x00;              // 全亮
        Delay(10000);
    }
} 
