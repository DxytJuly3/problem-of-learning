#include <reg51.h>
sbit P1_0=P1^0;
void main(void)
{
  TMOD=0x02;
  TR0=1;
  while(1)
    {
	TH0=0x06;
	TL0=0x06;
	do{}
	while(!TF0);
	P1_0=!P1_0;
	TF0=0;}
}
