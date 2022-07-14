#pragma once
#include "STL-myStack_Queue.h"

// ���� Queue ����һ������Ķ��У��������ȼ����� priority_queue
// �����ȼ����в����� queueһ�� �����Դ�����ݵģ����ȼ����еĵײ�ʵ����ʵ�� ��
// ���� ʵ�����ȼ�������ʹ�õ������� ���ʵ���vector��STLԴ��Ҳ��ʹ��vector<T> ��Ϊ������
//
// �� ���ȼ����еĵײ��ɶ�ʵ�֣���ʵ���ɴ���� �� С����ʵ�ֵģ������������� "���ȼ�"

namespace July
{
	// ���Լ�ʵ�� ����ѵ����ȼ�����
	/*template<class T, class Container = vector<T>>
	class priority_queue
	{
	public:
		// ������ʽ���幹�캯��

		// ���ϵ����������
		void AdjustUP(size_t child)
		{
			size_t parent = (child - 1) / 2;	// ���ӵĸ���λ�ã��Ǻ���λ��-1 ����2�����Ի�ͼ��һ��

			// ��Ȼ��ѭ�� �����һ������λ�ã����ϵ���������ѭ��ֹͣ������Ӧ���� child == 0
			while(child != 0)			// ������ѭ������������
			{
				if(_con[child] > _con[parent])		// ������ѣ����Ժ��Ӵ� ���븸�׽���λ��
				{
					swap(_con[child], _con[parent]);
					child = parent;					// ���Ӹı�λ��
					parent = (child - 1) / 2;		// �����º���λ�õĸ���
				}
				else
				{
					break;			// ���׽ڵ㲻�غ��ӽڵ�����ݴ��ˣ��͵���������
				}
			}
		}
		// ����� β�����ݣ����ϵ��� �������
		void push(const T& val)
		{
			_con.push_back(val);

			AdjustUP(_con.size() - 1);		// ���ϵ������ѣ��������һ�����ݵ�λ��
		}

		// ���µ������� ���� ���ڵ����������ӽڵ��нϴ�Ľ���λ�ã�ֱ������
		void AdjustDOWN(size_t parent)
		{
			// ���� ����������û�� �Һ��ӽڵ㣬����ֻ�������ӽڵ�
			size_t child = parent * 2 + 1;

			// ѭ���������������� Ӧ���Ǽ������ child ��һ�γ����˷�Χ������ѭ������������Ӧ���� child < _con.size()
			while(child < _con.size())
			{
				// ���ڵ� ��Ҫ�����Һ����нϴ��(��������Һ���)����λ�ã�������������Һ��ӽϴ����Ϊ child
				if(child + 1 < _con.size() && _con[child] < _con[child + 1])	// childĬ��Ϊ���ӣ�+1��Ϊ�Һ���
					++child;		// ����Һ��Ӵ��� ���Һ��Ӵ������ӣ���child��Ӧ��ʾ�Һ���

				if(_con[parent] < _con[child])		// ������� ���� С�����µ���
				{
					swap(_con[parent], _con[child]);
					parent = child;
					child = parent * 2 + 1;
				}
				else
				{
					break;
				}
			}
		}

		// ������ ͷɾ���ݣ����µ��� �������
		// �����Ƕѣ���ʵ�����еķ������� �� ���ڵ������һ���ڵ㽻��λ�ã�Ȼ��ɾ�����һ���ڵ�
		// Ȼ���ٴ� ���ڵ����µ����Ϳ�����
		void pop()
		{
			assert(!_con.empty());

			swap(_con[0], _con[_con.size() - 1]);		// ���ڵ���ĩ�ڵ㽻��λ��
			_con.pop_back();							// βɾ

			AdjustDOWN(0);								// �Ӹ�0 ���µ��� ����
		}

		// ȡ��ͷԪ�� ����
		const T& top()
		{
			return _con[0];
		}
		// ���д�С
		size_t size()
		{
			return _con.size();
		}
		// �п�
		bool empty()
		{
			return _con.empty();
		}

	private:
		Container _con;
	};*/

	// ���� ���ȼ����е� ����ѵײ��Ѿ�ȫ��ʵ��
	// ���� ��STLԴ�� �ᷢ�֣����ȼ����е� ģ�����һ��������
	// T, Container֮�⣬����һ��Compare
	// Compare ͬ��Ҳ�ṩ��һ��ȱʡֵ less<T>
	// ��� less<T> ��ʵ��һ�� �º�������ֻ��һ����Ա��������" () "�����غ����������������Ƚϴ�С��
	// ����� ��ʵ�������Ķ��� ����Ϊ ����������Ϊ���������� ��ʹ�ú���һ��ֱ�ӵ������Ա�����Ƚϴ�С
	// ���������һ�� less<T> les; les���������ֱ�� les(x,y) ���Ƚ�x �� y�Ĵ�С
	//
	// �� ���ȼ������ṩ �º���Ϊģ�����������ͨ�� �ı�º������Σ����ı�������ȼ����� ���Ķ�
	// Compare �� less<T> ����ѣ�Compare �� greater<T> �ͽ�С��
	// �� ���ȼ������� �������ϵ����㷨�жԱ� �����뺢�Ӵ�Сʱ ʹ�õ��� Compare ���󣬼���������
	// �������ʵ��һ�� ʹ�÷º��������ȼ�����	
	// ��ʵ ���� ���������� �Աȷ�ʽ���� ����û��ʲô���	
	template<class T>
	struct less
	{
		bool operator()(const T& x, const T& y) const
		{
			return x < y;
		}
	};

	template<class T>
	struct greater
	{
		bool operator()(const T& x, const T& y) const
		{
			return x > y;
		}
	};

	template<class T, class Container = vector<T>, class Compare = less<T>>
	class priority_queue
	{
	public:
		// ������ʽ���幹�캯��

		// ���ϵ����������
		void AdjustUP(size_t child)
		{
			Compare cmp;						// ʵ���� ��������
			size_t parent = (child - 1) / 2;	// ���ӵĸ���λ�ã��Ǻ���λ��-1 ����2�����Ի�ͼ��һ��

			// ��Ȼ��ѭ�� �����һ������λ�ã����ϵ���������ѭ��ֹͣ������Ӧ���� child == 0
			while (child != 0)			// ������ѭ������������
			{
				//if(_con[child] > _con[parent])		// ������ѣ����Ժ��Ӵ� ���븸�׽���λ��
				if (cmp(_con[parent], _con[child]))
				{
					swap(_con[child], _con[parent]);
					child = parent;					// ���Ӹı�λ��
					parent = (child - 1) / 2;		// �����º���λ�õĸ���
				}
				else
				{
					break;			// ���׽ڵ㲻�غ��ӽڵ�����ݴ��ˣ��͵���������
				}
			}
		}
		// ����� β�����ݣ����ϵ��� �������
		void push(const T& val)
		{
			_con.push_back(val);

			AdjustUP(_con.size() - 1);		// ���ϵ������ѣ��������һ�����ݵ�λ��
		}

		// ���µ������� ���� ���ڵ����������ӽڵ��нϴ�Ľ���λ�ã�ֱ������
		void AdjustDOWN(size_t parent)
		{
			Compare cmp;

			// ���� ����������û�� �Һ��ӽڵ㣬����ֻ�������ӽڵ�
			size_t child = parent * 2 + 1;

			// ѭ���������������� Ӧ���Ǽ������ child ��һ�γ����˷�Χ������ѭ������������Ӧ���� child < _con.size()
			while (child < _con.size())
			{
				// ���ڵ� ��Ҫ�����Һ����нϴ��(��������Һ���)����λ�ã�������������Һ��ӽϴ����Ϊ child
				//if(child + 1 < _con.size() && _con[child] < _con[child + 1])	// childĬ��Ϊ���ӣ�+1��Ϊ�Һ���
				if (child + 1 < _con.size() && cmp(_con[child], _con[child + 1]))
					++child;		// ����Һ��Ӵ��� ���Һ��Ӵ������ӣ���child��Ӧ��ʾ�Һ���

				//if(_con[parent] < _con[child])		// ������� ���� С�����µ���
				if (cmp(_con[parent], _con[child]))		// ������� ���� С�����µ���
				{
					swap(_con[parent], _con[child]);
					parent = child;
					child = parent * 2 + 1;
				}
				else
				{
					break;
				}
			}
		}

		// ������ ͷɾ���ݣ����µ��� �������
		// �����Ƕѣ���ʵ�����еķ������� �� ���ڵ������һ���ڵ㽻��λ�ã�Ȼ��ɾ�����һ���ڵ�
		// Ȼ���ٴ� ���ڵ����µ����Ϳ�����
		void pop()
		{
			assert(!_con.empty());

			swap(_con[0], _con[_con.size() - 1]);		// ���ڵ���ĩ�ڵ㽻��λ��
			_con.pop_back();							// βɾ

			AdjustDOWN(0);								// �Ӹ�0 ���µ��� ����
		}

		// ȡ��ͷԪ�� ����
		const T& top()
		{
			return _con[0];
		}
		// ���д�С
		size_t size()
		{
			return _con.size();
		}
		// �п�
		bool empty()
		{
			return _con.empty();
		}

	private:
		Container _con;
	};

	// ���� �º���ģ����������ȼ����У��ı�ģ������Ϳ��Ըı� ���ѷ�ʽ
}
