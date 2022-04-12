// ¿ª¹Ø×´Ì¬¼ì²â

#include <REGX51.H>
#include <intrins.h>

void delay(int times)
{
	int i,j;
	while(times--)
	{
		for(i = 0; i < 130; i++)
			for(j = 0; j < 255; j++);
	}
}

void main()
{
	while(1)
	{
		unsigned char temp;
		P1=0xff;
		temp=P1&0xf0;
		temp=_cror_(temp, 4);
		P1=temp;
		delay(1);
	}	
}