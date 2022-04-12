// ¿ª¹Ø×´Ì¬¼ì²â

#include <REGX51.H>
#include <intrins.h>

void delay()
{
	int i,j;
	for(i = 0; i < 130; j++)
		for(j = 0; j < 255; j++);	

}

void main()
{
	while(1)
	{
		unsigned char tmp;
		P1 = 0xFF;
		tmp = P1&0xF0;
		tmp = tmp>>4;
		P1 = tmp;
		delay();
	}	
}