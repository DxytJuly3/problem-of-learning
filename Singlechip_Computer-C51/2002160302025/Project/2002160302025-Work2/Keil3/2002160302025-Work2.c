#include <reg51.h>
sbit P2_0 = P2^0;

int main()
{
    TMOD = 0x01;
    TR0 = 1;
    while(1)
    {
        TH0 = 0xEC;
        TL0 = 0x78;
        do{
        }while(!TF0);
        P2_0 = !P2_0;
        TF0 = 0;
    }

    return 0;
}