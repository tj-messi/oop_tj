/*2351114 朱俊泽 信15*/
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
		cct_setfontsize("新宋体", 16, 8);
		cct_setcolor(0);
		char c[15][100] =
		{
			"1.内部数组，生成初始状态，寻找是否有初始可消除项" ,
			"2.内部数组，消除初始可消除项后非0项下落并用0填充",
			"3.内部数组，消除初始可消除项后查找消除提示",
			"4.n*n的框架(无分隔线),显示初始状态" ,
			"5.n*n的框架(有分隔线),显示初始状态" ,
			"6.n*n的框架(有分隔线),显示初始状态及初始可消除项" ,
			"7.n*n的框架(有分隔线),消除初始可消除项后显示消除提示",
			"8.cmd图形界面完整版(有分隔线，鼠标移动时显示坐标，右键退出)",
			"9.cmd图形界面完整版",
		};
		char op = menu(c,9,1,0);
		switch (op)  //输入参数 根据输入分别处理
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
		cout << endl << "本小题结束，请输入End继续..." ;
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
				cout << "输入错误请重新输入";
				cct_gotoxy(x, y);
				cout<<"                                                                            ";
			}
			cct_gotoxy(x, y);
		}
	}
	return 0;
}