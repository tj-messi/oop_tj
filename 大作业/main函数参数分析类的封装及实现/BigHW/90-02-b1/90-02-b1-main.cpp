#include  "windows.h"
#include"../include/cmd_console_tools.h"
#include"../include/base_work_fun.h"
#include"../include/90-01-b2 && 90-02-b1.h"
#include<iostream>
#include<conio.h>
#include<string>
#include<time.h>
#include<stdlib.h>
#include"90-02-b1.h"
using namespace std;


int main()
{
	cct_setconsoleborder(120, 40, 120, 9000);
	srand((unsigned)time(NULL));
	while (1)
	{
		cct_setfontsize("新宋体", 16, 8);
		cct_setcolor(0);
		char c[15][100] =
		{
			"A.命令行找出可消除项并标识",
			"B.命令行完成一次消除（分步骤显示）",
			"C.命令行完成一关（分步骤显示）",
			"D.伪图形界面下用鼠标选择一个色块（无分隔线）",
			"E.伪图形界面下用鼠标选择一个色块（有分隔线）",
			"F.伪图形界面完成一次消除（分步骤）",
			"G.伪图形界面完整版",
		};
		char op = menu(c, 7 ,0 ,1);
		if (op >= 'a' && op <= 'z')
		{
			op += 'A' - 'a';
		}
		switch (op)  //输入参数 根据输入分别处理
		{
			case 'Q':
				cout << endl;
				return 0;
			case 'A':
				game(1,0);
				break;
			case 'B':
				game(2, 0);
				break;
			case 'C':
				game(3, 0);
				break;
			case 'D':
				game(4, 0);
				break;
			case 'E':
				game(5, 0);
				break;
			case 'F':
				game(6, 0);
				break;
			case 'G':
				game(7, 0);
				break;
			default:
				break;
		}
		cout << endl << "本小题结束，请输入End继续...                                   ";
		char cmd[100];
		gets_s(cmd);
		while (1)
		{
			int x, y;
			cct_getxy(x, y);
			cin >> cmd;
			if ((cmd[0] == 'e' || cmd[0] == 'E') && (cmd[1] == 'n' || cmd[1] == 'N') && (cmd[2] == 'd' || cmd[2] == 'D'))
			{
				cct_cls();
				break;
			}
			else
			{
				cin.clear();
				cct_gotoxy(0, y + 1);
				cout << "输入错误请重新输入";
				cct_gotoxy(x, y);
				cout << "                                                                            ";
			}
			cct_gotoxy(x, y);
		}
	}
	return 0;
}