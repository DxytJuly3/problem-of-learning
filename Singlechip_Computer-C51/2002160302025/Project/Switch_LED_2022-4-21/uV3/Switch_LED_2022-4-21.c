#include <REGX51.H>
sbit L1 = P1^4;
sbit L2 = P1^5;
sbit L3 = P1^6;
sbit L4 = P1^7;
unsigned char LED[4] = { 0xfe, 0xfc, 0xf8, 0xf0 };

void delay()
{
	int i,j;
	for(i = 0; i < 13; i++)
		for(j = 0; j < 255; j++);
}

int main()
{
    while(1)
    {
        P1 = 0xff;
        if(L1 == 0)
            P1 = LED[0];
        if(L2 == 0)
            P1 = LED[1];
        if(L3 == 0)
            P1 = LED[2];
        if(L4 == 0)
            P1 = LED[3];

        delay();
    }

    return 0;
}