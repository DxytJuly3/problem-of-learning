#define _CRT_SECURE_NO_WARNINGS 1

#include "Sort.h"


void printArr(int *a, int size)
{
	for (int i = 0; i < size; i++)
	{
		printf("%d ", a[i]);
	}
	printf("\n");
}

void Swap(int* a, int* b)
{
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

// ��������
void insertSort(int* a, int size)
{
	for (int i = 0; i < size - 1; i++)
	{
		int end = i;
		int tmp = a[end + 1];
		while (end >= 0)
		{
			if (tmp < a[end])
			{
				a[end + 1] = a[end];
				end--;
			}
			else
			{
				// a[end - 1] = tmp;
				break;
			}
		}

		a[end + 1] = tmp;
	}
}

// ð������
void bubbleSort(int* a, int size)
{
	for (int i = 0; i < size - 1; i++)
	{
		int flag = 0;
		for (int j = 1; j < size - i; j++)
		{
			if (a[j - 1] > a[j])
			{
				Swap(&a[j - 1], &a[j]);
				flag = 1;
			}
		}
		if (flag == 0)
			break;
	}
}

// ϣ������
// ϣ�������˼·��
// �Լ����ͬ�����ݽ��з��飬�ȶԸ�������ֱ�ʹ�ò����������Ԥ����
// ÿһ��Ԥ�������֮�� ���������С��Ȼ���ٴη������Ԥ����
// ֱ�����Ϊ 1 ʱ�����еľ���ֱ�Ӳ�������
void shellSort(int* a, int size)
{
	int gap = size;
	
	// ��ѭ��Ԥ����д��
	/*gap = gap / 3 + 1;
	for (int i = 0; i < gap; i++)
	{
		for (int j = i; j < size - gap; j += gap)
		{
			int end = i;
			int tmp = a[end + gap];
			while (end >= 0)
			{
				if (a[end] < tmp)
				{
					a[end + gap] = a[end];
					end -= gap;
				}
				else
				{
					break;
				}
			}
			a[end + gap] = tmp;
		}
	}*/


	// �Ż�д��
	// Size > 1 �ͼ���ѭ��
	while (gap > 1)
	{
		// �� gap = gap / 3 + 1   �������ݽ��з���ļ������
		gap = gap / 3 + 1;			// ÿ�ν����ѭ���� gap �����С	�� gap �� >= 1��������Ϊ 1 �������һ�ζ�����Ĳ�������
		//��η��飿
		/*  һ������		14��   14 / 3 + 1 ---> 5
		0	1	2	3	4	5	6	7	8	9	10	11	12	13
		67	34	29	91	65	98	56	67	86	34	89	53	80	13
		67					98					89					----��һ��
			34					56					53				----�ڶ���
				29					67					80			----������
					91					86					13		----������
						65					34						----������
		gap ���Ƿ����׼ ��ǰ���� + 5 �ķ�Ϊһ��
		*/
		
		for (int i = 0; i < size - gap; i++)
		{
			// �������� ���������˼�� ���Ƕ��Ѿ��ֹ���ÿһ��ֱ���в�������
			// ������������ û�� gap ���飨�� gap Ϊ 1����������Ϊһ�飩
			// 
			int end = i;
			int tmp = a[end + gap];
			while (end >= 0)
			{
				if (a[end] < tmp)
				{
					a[end + gap] = a[end];
					end -= gap;
				}
				else
				{
					break;
				}
			}
			a[end + gap] = tmp;
		}
	}
}

// ѡ������
void selectSort(int* a, int size)
{
	// �Ż���ѡ������һ��ѡ�������������ֵ����Сֵ
	int left = 0;
	int right = size - 1;
	while (left < right)
	{
		int mini = left;		// ��¼��Сֵλ��
		int maxi = left;		// ��¼���ֵλ��
		for (int i = left + 1; i < right + 1; i++)
		{
			if (a[i] > a[maxi])
			{
				maxi = i;
			}
			if (a[i] < a[mini])
			{
				mini = i;
			}
		}
		Swap(&a[maxi], &a[left]);
		if (left == mini)
		{
			// ��������Ϊ�˷�ֹһ�����������
			// �� left λ�� �պ��� ��Сֵ��λ��
			// �������������������У�left λ�õ�ֵ �������ˣ��������� maxi λ��
			// right Ҳ����ͬ�ĵ���
			// ������� left �� right λ�� �Ѿ�����¼�� ���Ǿ�����������Ӧλ�õ������ֱ�������
			// ����Ҫ�����ж�
			mini = maxi;
		}
		Swap(&a[mini], &a[right]);
		left++;
		right--;
	}
}

// hoare���ŵ�������
int hoarePartSort(int* a, int left, int right)
{
	int keyi = left;
	while (left < right)
	{
		// right �ұ� key С��	Ҫ���� right > left ��ֹԽ��
		// right λ�ñ� key ��ͽ�ѭ�������Կ��Ƶ� right �� key С��ʱ��rightֹͣ�����ƶ�
		while (a[right] >= a[keyi] && left < right)
			right--;

		// left �ұ� key ���		Ҫ���� left < right ��ֹԽ��
		// left λ�ñ� key С�ͽ�ѭ�������Կ��Ƶ� left �� key ���ʱ��leftֹͣ�����ƶ�
		while (a[left] <= a[keyi] && left < right)
			left++;

		Swap(&a[left], &a[right]);
	}
	// ����ʱ������λ�õ�ֵ �� key ����
	Swap(&a[left], &a[keyi]);
	// Ϊ�˱�֤����λ�õ�ֵ ��С�� key�����Կ��� right ���ƶ�����Ϊ right ��С���ҵ� ���� ��left���� �Ż�ֹͣ 
	// �Ž���ͬ��

	return left;		// Ϊ���Ŵ����������������
}

// hoare��������
void hoareQuickSort(int* a, int begin, int end)
{
	if (begin >= end)
		return;

	int keyi = hoarePartSort(a, begin, end);
	hoareQuickSort(a, begin, keyi - 1);
	hoareQuickSort(a, keyi + 1, end);
}

void AdjustDown(HPDataType* data, size_t size, size_t root)
{
	assert(data);
	// ���µ�������Ҫ�Աȸ��׽ڵ�ͺ��ӽڵ�Ĵ�С
	// ������׽ڵ�С�ں��ӽڵ����Ҫ����λ��
	// ���Ǹ��׽ڵ�һ������»����������ӽڵ�  ����Ҫ�жϳ��������ӽڵ��� ������Ǹ����ӽڵ� �� ���׽ڵ���н���
	// Ϊ�˷����ж� ����ֱ�Ӽ��� ���ӽڵ���Ǵ�ĺ��ӽڵ�
	// ������ӽڵ㲻�Ǵ�ĺ��ӽڵ�  �����Һ��ӽ������Ϊ��ĺ��ӽڵ� 
	// Ȼ�����ж� ���׽ڵ�������ĺ��ӽڵ�Ĵ�С
	// Ȼ���ٽ��н���


	// ѭ�������������� ��child > size   �����ӽڵ�λ�ô���ʵ��ӵ�нڵ�����ʱֹͣ
	size_t parent = root;
	size_t child = parent * 2 + 1;
	while (child < size)
	{
		// �ж� ��ĺ��ӽڵ��Ƿ���ȷ
		// ������ �Һ��ӣ�Ȼ������ж����Һ��ӵĴ�С�����Ե����ж� child + 1 < size
		if (child + 1 < size && data[child] > data[child + 1])
		{
			++child;
		}

		// ���׽ڵ�� �� ����
		if (data[parent] > data[child])
		{
			Swap(&data[parent], &data[child]);
			parent = child;
			child = parent * 2 + 1;
		}
		else
		{
			break;
		}
	}
}

void HeapSort(int *data, size_t size)
{// ֱ�Ӷ� ���齨��
	assert(data);


	// ���ϵ�������
	/*for (int i = 0; i < size; i++)
	{
	AdjustUp(data, i);
	}*/


	// ���µ�������
	// ���ֵ�����ʽ����һ����ͬ��ǰ�᣺������Ҫ�������Ǹ��ڵ㣬�������Ѿ��Ƕ�
	// �������µ������ܴ� ������������root ��ʼ
	// Ҫ�� ���һ����Ҷ�ӽڵ㿪ʼ���µ��� ��Ϊʲô�����һ����Ҷ�ӽڵ㣺��ΪҶ�ӽڵ�û�к��ӽڵ㲻�������µ����ˣ�
	// ���һ����Ҷ�ӽڵ��λ���ǣ����һ���ڵ�ĸ��׽ڵ�


	int j = (size - 1 - 1) / 2; //���һ����Ҷ�ӽ���λ��
	for (j; j >= 0; j--)
	{
		AdjustDown(data, size, j);
	}


	// ����ѽ��ã�����
	// ������ ��ɾ�����ݵ�˼��
	// ������ѵ� �� �� ���һ���ڵ� ����λ��
	// Ȼ��Ӹ����µ���
	// Ȼ�� �ٽ��� �� �����ڶ����ڵ� ����λ��
	// Ȼ��Ӹ����µ���  �Դ�����
	size_t end = size - 1;   // end �ȴ����һ���ڵ�λ�ÿ�ʼ
	while (end > 0)
	{
		Swap(&data[0], &data[end]); // ���ڵ� �� end�ڵ� ����λ��
		AdjustDown(data, end, 0);   // �Ӹ��ڵ����µ��� ������ ������
		--end;                      // end λ�� ��һ
	}

}