/*2150792 计科 牛禄阳*/
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

//ON返回1，OFF返回2，输入错误返回0
int input_switch(char &switch_id, char switch_state[maxsize])
{
	cin >> switch_id;							  //读入开关序号
	cin >> switch_state;                          //读入开关状态
	/*小写字母转为大写*/
	if (switch_id >= 'a' && switch_id <= 'z')    
		switch_id -= ('a' - 'A');
	char_upcase(switch_state, maxsize); 
	/*判断输入开关合法性*/
	if ((switch_id >= 'A' && switch_id <= 'J') || switch_id == 'Q')
	{
		if (switch_state[0] == 'O' && switch_state[1] == 'N' && switch_state[2] == '\0')//合法ON
			return 1;
		else if (switch_state[0] == 'O' && switch_state[1] == 'F' && switch_state[2] == 'F' && switch_state[3] == '\0')  //合法OFF
			return 2;
	}
	return 0;										   //非合法状态
}

void print_switch_state(short switch_a, int choice)
{
	if (choice == 0)
		cout << "初始状态：";
	else if (choice == 1)
		cout << "当前状态：";
	cout << "0x" << setfill('0') << setw(4) << hex << switch_a << endl;//输出开关数值
	cout << resetiosflags(ios::right);
	for (int i = 0; i < 9; i++)
		cout << setiosflags(ios::left) << setfill(' ') << setw(4) << char('A' + i);//输出开关序号
	cout << char('J') << endl;   //J特殊判断，为了不输出多余的空格
	for (int i = 0; i < 10; i++)
		cout << setiosflags(ios::left) << setfill(' ') << setw(4) << ((switch_a & (1 << i)) ? "ON" : "OFF");//输出开关状态
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
		cout << "请以(\"A On /J Off\"形式输入，输入\"Q on/off\"退出)" << endl;
		int temp = 0;
		temp = input_switch(switch_id, switch_state);
		if (temp > 0 && switch_id == 'Q')
			break;
		if (temp == 0)
			continue;
		else
		{
			if (temp == 1)     //某位置为1
				switch_a = (switch_a | (0x1 << (switch_id - 'A')));
			else if (temp == 2)//某位置为0
				switch_a = (switch_a & (short(0xFDFF) >> (short)fabs('J' - switch_id)));
		}
		print_switch_state(switch_a, 1);
	}
	return 0;
}
