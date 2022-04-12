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

int main()
{
	P1 = 0xFE;
	while(1)
	{
		delay(2);
		P1 = _crol_(P1, 1);
	} 	
}