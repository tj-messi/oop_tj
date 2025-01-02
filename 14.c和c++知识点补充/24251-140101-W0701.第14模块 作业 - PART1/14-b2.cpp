/*2351114 �쿡�� ������*/
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <time.h>
/* �������Ҫ���˴��������ͷ�ļ� */

using namespace std;
//cdhs��Ӧ5436
/* �����峣����/�궨�壬����������ȫ�ֱ��� */
//T����10 
const char number[] = { '3','4','5','6','7','8','9','T','J','Q','K','A','2' };
#if (__linux__)             //Linux
const char color[4] = { 'H','D','C','S' };
#else					    //Win
const char color[4] = { '\3','\4','\5','\6' };
//cdhs��Ӧ5436
//cdhs��Ӧ5436
/* ��������Լ���Ҫ�ĺ��� */
#endif

/***************************************************************************
  �������ƣ�
  ��    �ܣ���ӡĳ����ҵ�������Ϣ������ǵ���������ӱ��
  ���������
  �� �� ֵ��
  ˵    ����
 ***************************************************************************/
int print(const char *prompt, const bool landlord, const unsigned long long player)
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
				cout << color[i % 4] << number[i / 4] << " ";
			else if (i == 52)
				cout << "BJ ";
			else if (i == 53)
				cout << "RJ ";
		}
	}
	if (landlord == true)
	{
		cout << "(����)";
	} 
	
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
int deal(unsigned long long *player)
{
	/* ֻ�����岻����ʮ���������͵ļ򵥱��������ܶ�������������ṹ�塢string�� */
	srand((unsigned int)(time(0)));
	
	int cnt = 0;//�����˶����ƣ�/3�����Ѿ���������
	
	unsigned long long card = 0;//0��ʾ��û������
	
	for(int i=1;i<=17;i++)
	{
		for(int j=1;j<=3;j++)
		{
			cnt++;
			int index = rand() % 54 ; //(0)-(53)
			if(((unsigned long long)1<<index)&card)//�Ѿ������� 
			{
				j--;
			}
			else//û�з��� 
			{
				card = (card | ((unsigned long long)1<<index)); 
				player[j%3]=(player[j%3] | ((unsigned long long)1<<index));
			}
			
			
		}
		//��ʱ�����ǵ��� 
		print("�׵��ƣ�", 0, player[0]);
		print("�ҵ��ƣ�", 0, player[1]);
		print("�����ƣ�", 0, player[2]);
	}
	
	int res;
	
	while (1)
	{
		cout << endl<< "��ѡ��һ������[0-2]��" << endl;
		cin >> res;
		if (cin.good() == 0)
		{
			cin.clear();
			cin.ignore(65536, '\n');
			continue;
		}
		if ((res < 0) || (res > 2)  )
		{
			cin.clear();
			cin.ignore(65536, '\n');
			continue;
		}
		break;
	}
	
	for(int i=0;i<54;i++)
	{
		if (card & ((unsigned long long)1 << i))
			continue;
		else
		{
			player[res]=(player[res] | (unsigned long long)1 << i);
			card=card | ((unsigned long long)1 << i);
		} 
	}
	
	return res; //�˴��޸�Ϊѡ���ĵ���(0-2)
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
