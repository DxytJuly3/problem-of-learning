#define _CRT_SECURE_NO_WARNINGS

#include "chess_10_8.h"

int main()
{
	int input = 0;
	//���ֵǰ�ĵ���
	srand((unsigned int)time(NULL));
	do
	{
		mune();
		printf("��ѡ�����:>");
		scanf("%d", &input);
		switch (input)
		{
		case 1:
			//��Ϸ���庯��
			game_main();
			break;
		case 0:
		printf("�˳��ɹ���");
			break;
		default:
			printf("ѡ�����������ѡ��\n");
			break;
		}
	} while(input);

	return 0;
}
