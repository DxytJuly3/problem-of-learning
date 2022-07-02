#define _CRT_SECURE_NO_WARNINGS 1
#include "Stack.h"

// ��ʼ��
void StackInit(Stack *pst)
{
	assert(pst);
	pst->data = NULL;
	pst->Top = pst->Capacity = 0;
}
// ѹջ
void StackPush(Stack *pst, StackDataType x)
{
	assert(pst);

	if (pst->Top == pst->Capacity)		// ��������
	{
		int newCapacity = pst->Capacity == 0 ? 4 : pst->Capacity * 2;
		StackDataType *tmp = (StackDataType*)realloc(pst->data, sizeof(StackDataType)* newCapacity);
		if (tmp == NULL)
		{
			printf("realloc fail\n");
			exit(-1);
		}

		pst->data = tmp;
		pst->Capacity = newCapacity;
	}

	pst->data[pst->Top++] = x;
}

// ��ջ
void StackPop(Stack *pst)
{
	assert(pst);
	assert(pst->Top > 0);		//��֤ջ��Ϊ��
	/*	Top ��ֵΪ -1
	assert(pst->Top > -1);
	*/

	--pst->Top;
}

// ȡջ��Ԫ��
StackDataType StackTop(const Stack *pst)
{
	assert(pst);
	assert(pst->Top > 0);	

	return pst->data[pst->Top - 1];
	/*	Top ��ֵΪ -1
	return pst->data[pst->Top];
	*/
}

// �п�
bool StackEmpty(const Stack *pst)
{
	assert(pst);

	return pst->Top == 0;
	/*	Top ��ֵΪ -1
	return pst->Top == -1;
	*/
}

// ջԪ�ظ���
int StackSize(const Stack *pst)
{
	assert(pst);

	return pst->Top;
	/*	Top ��ֵΪ -1
	return pst->Top + 1;
	*/
}

// ջ����
void StackDestory(Stack *pst)
{
	assert(pst);

	free(pst->data);
	pst->data = NULL;
	pst->Capacity = pst->Top = 0;
}