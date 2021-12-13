//A说：不是我。			!= A
//B说：是C。				== C
//C说：是D。				== D
//D说：C在胡说			!= D
//已知3个人说了真话，1个人说的是假话。

#include <stdio.h>

int main()
{
	char killer = 'A';
	for (killer = 'A'; killer < 'D'; killer++)
	{
		if ((killer != 'A') + (killer == 'C') + (killer == 'D') + (killer != 'D') == 3)
			printf("%c ", killer);
	}

	return 0;
}