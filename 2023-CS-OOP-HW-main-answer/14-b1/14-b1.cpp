/*2150792 �ƿ� ţ»��*/
#include<iostream>
#include<iomanip>
#include<cmath>
#include<string>
#include<cstring>
using namespace std;
const int maxsize = 4;
const short switch_number[10] = {};
int char_upcase(char a[],int size)
{
	for (int i = 0; i < size; i++)
	{
		if (a[i] >= 'a' && a[i] <= 'z')
			a[i] -= ('a' - 'A');
	}
	return 1;
}

//ON����1��OFF����2��������󷵻�0
int input_switch(char &switch_id, char switch_state[maxsize])
{
	cin >> switch_id;							  //���뿪�����
	cin >> switch_state;                          //���뿪��״̬
	/*Сд��ĸתΪ��д*/
	if (switch_id >= 'a' && switch_id <= 'z')    
		switch_id -= ('a' - 'A');
	char_upcase(switch_state, maxsize); 
	/*�ж����뿪�غϷ���*/
	if ((switch_id >= 'A' && switch_id <= 'J') || switch_id == 'Q')
	{
		if (switch_state[0] == 'O' && switch_state[1] == 'N' && switch_state[2] == '\0')//�Ϸ�ON
			return 1;
		else if (switch_state[0] == 'O' && switch_state[1] == 'F' && switch_state[2] == 'F' && switch_state[3] == '\0')  //�Ϸ�OFF
			return 2;
	}
	return 0;										   //�ǺϷ�״̬
}

void print_switch_state(short switch_a, int choice)
{
	if (choice == 0)
		cout << "��ʼ״̬��";
	else if (choice == 1)
		cout << "��ǰ״̬��";
	cout << "0x" << setfill('0') << setw(4) << hex << switch_a << endl;//���������ֵ
	cout << resetiosflags(ios::right);
	for (int i = 0; i < 9; i++)
		cout << setiosflags(ios::left) << setfill(' ') << setw(4) << char('A' + i);//����������
	cout << char('J') << endl;   //J�����жϣ�Ϊ�˲��������Ŀո�
	for (int i = 0; i < 10; i++)
		cout << setiosflags(ios::left) << setfill(' ') << setw(4) << ((switch_a & (1 << i)) ? "ON" : "OFF");//�������״̬
	cout << endl << endl;
	cout << resetiosflags(ios::left);
}

int main()
{
	char switch_id;
	char switch_state[maxsize];
	short switch_a = 0;
	memset(switch_state, '\0', sizeof(switch_state));
	print_switch_state(switch_a, 0);
	while (true)
	{
		cout << "����(\"A On /J Off\"��ʽ���룬����\"Q on/off\"�˳�)" << endl;
		int temp = 0;
		temp = input_switch(switch_id, switch_state);
		if (temp > 0 && switch_id == 'Q')
			break;
		if (temp == 0)
			continue;
		else
		{
			if (temp == 1)     //ĳλ��Ϊ1
				switch_a = (switch_a | (0x1 << (switch_id - 'A')));
			else if (temp == 2)//ĳλ��Ϊ0
				switch_a = (switch_a & (short(0xFDFF) >> (short)fabs('J' - switch_id)));
		}
		print_switch_state(switch_a, 1);
	}
	return 0;
}
