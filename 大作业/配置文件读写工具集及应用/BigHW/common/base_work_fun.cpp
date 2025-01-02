#include  "windows.h"
#include<iostream>
#include"../include/cmd_console_tools.h"
#include<conio.h>
#include <synchapi.h>
using namespace std;


char menu(char c[15][100], int list_num, bool i,bool ch)
{
	cct_setconsoleborder(120, 40, 120, 9000);
	cct_cls();
	cout << "---------------------------------" << endl;

	for (int i = 0; i < list_num; i++)
	{
		cout << c[i] << endl;
	}
	if (i)cout << "0.ÍË³ö" << endl;
	else cout << "Q.ÍË³ö" << endl;
	cout<< "---------------------------------" << endl
		<< "[ÇëÑ¡Ôñ:] ";
	while (1)
	{
		const char num = _getch();
		if (ch && (num == 'q' || num == 'Q'|| (num <= 'a' + list_num - 1 && num >= 'a') || (num <= 'A' + list_num - 1
			&& num>= 'A')) || i && (num <= '0'+list_num && num >= '0'))
		{
			return num;
		}
		cin.clear();
	}
}

void pause(int time)
{
	Sleep(time);
}