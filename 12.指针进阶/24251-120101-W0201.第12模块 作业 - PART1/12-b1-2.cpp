/*2351114 �쿡�� ������*/
#include <iostream>
#include <iomanip>
using namespace std;

#define STUDENT_NUM	4
#define SCORE_NUM	5

/* --- ���������κ���ʽ��ȫ�ֱ��� --- */

/***************************************************************************
  �������ƣ�
  ��    �ܣ����һ�ſε�ƽ����
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void average(int(*score)[STUDENT_NUM])
{
	/* ����������䲿�֣�
	   1���������н������� 1���򵥱��� + 1��ָ����� */

	   /* ����ִ����䲿�֣�
		  1���������ٶ����κ����͵ı��������� for (int i=0;...������ʽ�������
		  2��ѭ������������ָ���������������в��������[]��ʽ��������
			 ������int a[10], i;
					 for(i=0; i<10; i++)
						 cout << a[i];
			 ����  ��int a[10], p;
					 for(p=a; p<a+10; p++)
						 cout << *p;          */

	int sum = 0;
	int* ptr;

	for (ptr = &score[0][0]; ptr < &score[0][0] + STUDENT_NUM; ptr++)
	{
		sum += *ptr;
	}

	//sum =  1.0*(sum) / STUDENT_NUM;  
	cout << "��1�ſ�ƽ���֣�" << 1.0 * (sum) / STUDENT_NUM << endl << endl;

}

/***************************************************************************
  �������ƣ�
  ��    �ܣ��ҳ����������Ͽγ̲������ѧ��
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void fail(int(*score)[STUDENT_NUM])
{
	/* ����������䲿�֣�
	   1���������н������� 3���򵥱��� + 1����ָ����� + 1����ָ����� */

	   /* ����ִ����䲿�֣�Ҫ��ͬaverage��*/
	int sum = 0;
	int idx = 0;
	int cnt;
	int* ptr;
	//int(*rowptr)[4] = score;

	for (; idx <= 3; idx++)
	{
		 cnt = 0;
		for (ptr = score[0] + idx; ptr < &score[0][0] + SCORE_NUM * STUDENT_NUM; ptr += STUDENT_NUM)
		{
			if (*ptr < 60)
				cnt++;
		}
		if (cnt >= 2)
			break;
	}

	cout << "2�����ϲ������ѧ����" << endl;
	cout << "No��" << idx + 1 << " ";

	for (ptr = score[0] + idx; ptr < &score[0][0] + SCORE_NUM * STUDENT_NUM; ptr += STUDENT_NUM)
	{
		sum += *ptr;
		cout << *ptr << " ";
	}
	cout << "ƽ����" << 1.0 * (sum) / SCORE_NUM << endl << endl;
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ��ҳ�ƽ���ɼ���90�����ϻ�ȫ���ɼ���85�����ϵ�ѧ��
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void good(int(*score)[STUDENT_NUM])
{
	/* ����������䲿�֣�
	   1���������н������� 3���򵥱��� + 1����ָ����� + 1����ָ����� */

	   /* ����ִ����䲿�֣�Ҫ��ͬaverage��*/

	int sum = 0;
	int idx = 0;
	int cnt;
	int* ptr;
	//int(*rowptr)[4] = score;
	cout << "ƽ��90���ϻ�ȫ��85���ϵ�ѧ����" << endl;
	for (; idx <= 3; idx++)
	{
		cnt = 0;
		sum = 0;
		for (ptr = score[0] + idx; ptr < &score[0][0] + SCORE_NUM * STUDENT_NUM; ptr += STUDENT_NUM)
		{
			sum += *ptr;
			if (*ptr >= 60)
				cnt++;
		}
		if (cnt >= 5 || sum >= 450)
		{
			sum = 0;
			cout << "No��" << idx + 1 << " ";
			for (ptr = score[0] + idx; ptr <= &score[0][0] + SCORE_NUM * STUDENT_NUM; ptr += STUDENT_NUM)
			{
				sum += *ptr;
				cout << *ptr << " ";
			}
			cout << "ƽ����" << 1.0 * (sum) / SCORE_NUM << endl;
		}
	}
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
int main()
{
	int a[SCORE_NUM][STUDENT_NUM] = {
		{91,92,93,97},  //��1-4��ѧ���ĵ�1�ſγɼ�
		{81,82,83,85},  //��1-4��ѧ���ĵ�2�ſγɼ�
		{71,72,99,87},  //��1-4��ѧ���ĵ�3�ſγɼ�
		{61,32,80,91},  //��1-4��ѧ���ĵ�4�ſγɼ�
		{51,52,95,88} };//��1-4��ѧ���ĵ�5�ſγɼ�
	/* �������Ԥ�������⣬�������н������� 1����ָ����� + 1����ָ����� */
	cout << "��ʼ��Ϣ��" << endl;
	int* ptr;
	int(*rowptr)[4] = a;

	for (; rowptr - a <= 4; rowptr++)
	{
		//cnt=0;
		cout << "No.1-4ѧ���ĵ�" << rowptr - a + 1 << "�ſγɼ���";
		for (ptr = a[rowptr - a]; ptr < a[rowptr - a] + STUDENT_NUM; ptr++)
		{
			cout << *ptr << " ";
		}
		cout << endl;
	}

	cout << endl;
	/* ����ִ����䲿�֣�Ҫ��ͬaverage��*/

	average(a);

	fail(a);

	good(a);

	return 0;
}
