/*2150792 �ƿ� ţ»��*/
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <time.h>
/* �������Ҫ���˴��������ͷ�ļ� */

using namespace std;

/* �����峣����/�궨�壬����������ȫ�ֱ��� */
//cdhs��Ӧ5436 
const char Puke_number[13] = { '3','4','5','6','7','8','9','T','J','Q','K','A','2' };
#if (__linux__)             //Linux
const char Puke_color[4] = { 'H','D','C','S' };
#else					    //Win
const char Puke_color[4] = { '\3','\4','\5','\6' };
#endif
//cdhs��Ӧ5436 
//cdhs��Ӧ5436 

/* ��������Լ���Ҫ�ĺ��� */
int get_input_int(int low, int high, int& elem_int, int base)
{
	cout << endl << "��ѡ��һ������[0-2]��" << endl;
	while (1)
	{
		cin >> elem_int;
		if (cin.good() == 0)
		{
			cin.clear();
			cin.ignore(65536, '\n');
			cout << endl << "��ѡ��һ������[0-2]��" << endl;
			continue;
		}
		if (((elem_int < low) || (elem_int > high) || (elem_int % base != 0)) && (cin.good() == 1))
		{
			cout << endl << "��ѡ��һ������[0-2]��" << endl;
			continue;
		}
		if (elem_int >= low && elem_int <= high && elem_int % base == 0)
			break;
	}
	return 1;
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ���ӡĳ����ҵ�������Ϣ������ǵ���������ӱ��
  ���������
  �� �� ֵ��
  ˵    ����
 ***************************************************************************/
int print(const char* prompt, const bool landlord, const unsigned long long player)
{
	/* ֻ�����岻���������������͵ļ򵥱��������ܶ�������������ṹ�塢string�� */
	static int num_times = 1, cnt = 0;
	if (cnt++ % 3 == 0 && num_times <= 17)
		cout << dec << "��" << num_times++ << "�ֽ�����" << endl;


	cout << prompt;
	for (int i = 0; i < 54; i++)
	{
		if (player & ((unsigned long long) 1 << i))      // ��ǰλ������
		{
			if (i <= 51)
				cout << Puke_color[i % 4] << Puke_number[i / 4] << " ";
			else if (i == 52)
				cout << "BJ ";
			else if (i == 53)
				cout << "RJ ";
		}
	}
	if (landlord == true)
		cout << "(����)";
	cout << endl;
	return 0;
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ����ƣ����������������
  ���������
  �� �� ֵ��
  ˵    ����
 ***************************************************************************/
int deal(unsigned long long* player)
{
	/* ֻ�����岻����ʮ���������͵ļ򵥱��������ܶ�������������ṹ�塢string�� */

	srand((unsigned int)(time(0)));								 // ʹ�õ�ǰʱ����Ϊ�������
	static long long Puke=0x003FFFFFFFFFFFFF;					 // ��λ��ֵΪ54λ1
	int landlord = 0;
	for (int i = 0; i < 17; i++)								 // ������17��
	{
		for (int j = 0; j < 3; j++)								 // һ��Ϊ�����˷���
		{
			int index = rand() % 54;                             // ����0-53��Χ�ڵ������
			if (Puke & ((long long) 1 << index))                 // ��ǰλ��û�б�����
			{
				Puke = (Puke & ((long long)(0xFFDFFFFFFFFFFFFF) >> (53 - index)));// ��Puke�Ѿ����Ƶ�λ��0
				player[j]= (player[j] | ((unsigned long long) 1 << index));	      // ��player�����Ƶ�λ��1	
			}
			else                                                 // ��ǰλ���ѱ����� 
				--j;
		}
		print("�׵��ƣ�", 0, player[0]);
		print("�ҵ��ƣ�", 0, player[1]);
		print("�����ƣ�", 0, player[2]);
		//cout << "0x" << setfill('0') << setw(16) << hex << Puke << endl;//���������ֵ
		//cout << "0x" << setfill('0') << setw(16) << hex << player[0] << endl;//���������ֵ
		//cout << "0x" << setfill('0') << setw(16) << hex << player[1] << endl;//���������ֵ
		//cout << "0x" << setfill('0') << setw(16) << hex << player[2] << endl;//���������ֵ
	}
	get_input_int(0, 2, landlord, 1);
	for (int i = 0; i < 54; i++)								// ����ʣ����˿��ƶѣ���ʣ�����ȫ��������
	{
		if (Puke & ((long long)1 << i))                         // ��ǰλ��û�б�����
		{
			Puke = (Puke & ((long long)(0xFFDFFFFFFFFFFFFF) >> (53 - i)));         // ��Puke�Ѿ����Ƶ�λ��0
			player[landlord] = (player[landlord] | ((unsigned long long) 1 << i)); // ��landlord�����Ƶ�λ��1	
		}
	}
	return landlord;											 // �˴��޸�Ϊѡ���ĵ���(0-2)
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����main��������׼�޸�
 ***************************************************************************/
int main()
{
	unsigned long long player[3] = { 0 }; //���������ҵķ�����Ϣ
	int landlord; //����0-2��ʾ�ĸ�����ǵ���

	cout << "���س�����ʼ����";
	while (getchar() != '\n')
		;

	landlord = deal(player);
	print("�׵��ƣ�", (landlord == 0), player[0]);
	print("�ҵ��ƣ�", (landlord == 1), player[1]);
	print("�����ƣ�", (landlord == 2), player[2]);

	return 0;
}
