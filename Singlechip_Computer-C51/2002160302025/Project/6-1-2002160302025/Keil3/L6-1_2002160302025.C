#include <REGX51.H>

void Delay(unsigned int i)
{
    unsigned int j = 0;
    while(i--)
    {
        for(j; j < 333; j++)
        {}
    }
}

int main()
{
    EA = 1;
    EX0 = 1;
    IT0 = 1;
    while(1)
    {
        P1 = 0;
    }

    return 0;
}


void int0( )  interrupt 0
{
    unsigned char n = 0;
    EX0 = 0;
    for(n = 0; n < 5; n++)
    {
        P1 = 0x0f;              // 高四位亮
        Delay(5000);
        P1 = 0xf0;              // 低四位亮
        Delay(5000);
    }
    EX0 = 1;
} 
