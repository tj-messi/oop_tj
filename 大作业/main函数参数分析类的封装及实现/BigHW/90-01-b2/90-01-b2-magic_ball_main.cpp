/*2351114 �쿡�� ��15*/
#include"../include/cmd_console_tools.h"
#include"../include/base_work_fun.h"
#include"../include/90-01-b2 && 90-02-b1.h"
#include"90-01-b2-magic_ball.h"
#include<iostream>
#include<conio.h>
#include<string>
#include<time.h>
#include<stdlib.h>
using namespace std;

int main()
{
	cct_setconsoleborder(120, 40, 120, 9000);
	srand((unsigned)time(NULL));
	while (1)
	{
		cct_setfontsize("������", 16, 8);
		cct_setcolor(0);
		char c[15][100] =
		{
			"1.�ڲ����飬���ɳ�ʼ״̬��Ѱ���Ƿ��г�ʼ��������" ,
			"2.�ڲ����飬������ʼ����������0�����䲢��0���",
			"3.�ڲ����飬������ʼ������������������ʾ",
			"4.n*n�Ŀ��(�޷ָ���),��ʾ��ʼ״̬" ,
			"5.n*n�Ŀ��(�зָ���),��ʾ��ʼ״̬" ,
			"6.n*n�Ŀ��(�зָ���),��ʾ��ʼ״̬����ʼ��������" ,
			"7.n*n�Ŀ��(�зָ���),������ʼ�����������ʾ������ʾ",
			"8.cmdͼ�ν���������(�зָ��ߣ�����ƶ�ʱ��ʾ���꣬�Ҽ��˳�)",
			"9.cmdͼ�ν���������",
		};
		char op = menu(c,9,1,0);
		switch (op)  //������� ��������ֱ���
		{
			case '0':
				cout << endl;
				return 0;
			case '1':
				game(1);
				break;
			case '2':
				game(2);
				break;
			case '3':
				game(3);
				break;
			case '4':
				game(4);
				break;
			case '5':
				game(5);
				break;
			case '6':
				game(6);
				break;
			case '7':
				game(7);
				break;
			case '8':
				game(8);
				break;
			case '9':
				game(9);
				break;
			default:
				break;
		}
		cout << endl << "��С�������������End����..." ;
		char cmd[100];
		gets_s(cmd);
		while (1)
		{
			int x, y;
			cct_getxy(x, y);
			gets_s(cmd);
			if ((cmd[0]=='e'||cmd[0]=='E')&& (cmd[1] == 'n' || cmd[1] == 'N')&& (cmd[2] == 'd' || cmd[2] == 'D'))
			{
				cct_cls();
				break;
			}
			else
			{
				cin.clear();
				cct_gotoxy(0, y + 1);
				cout << "�����������������";
				cct_gotoxy(x, y);
				cout<<"                                                                            ";
			}
			cct_gotoxy(x, y);
		}
	}
	return 0;
}