/* -----------------------------------------

     本文件不需要提交、不允许改动

   ----------------------------------------- */
#include <iostream>
#include <iomanip>
#include <ctime>
#include <cmath>
#include <cstdio>
#include <conio.h>
#include <Windows.h>
#include "../BigHW/include/cmd_console_tools.h"
using namespace std;

/***************************************************************************
  函数名称：
  功    能：显示提示信息
  输入参数：
  返 回 值：
  说    明：如果读不懂，暂时放着，等指针和引用学习完成后再阅读
***************************************************************************/
static void to_be_continued(const char *prompt, const int X = 0, const int Y = 22)
{
	cct_setcolor(); //恢复缺省颜色
	cct_gotoxy(X, Y);

	if (prompt)
		cout << prompt << "，按回车键继续...";
	else
		cout << "按回车键继续...";

	/* 忽略除回车键外的所有输入（注意：_getch的回车是\r，而getchar是\n）*/
	while (_getch() != '\r')
		;

	cct_cls();

	return;
}

/***************************************************************************
  函数名称：
  功    能：在指定位置，用指定颜色，显示一个字符若干次
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
int main()
{
	

	/* 四种线型的框架，每种11个元素，每个元素均为一个中文字符（2字节）
		双线框架："╔", "╚", "╗", "╝", "═", "║", "╦", "╩", "╠", "╣", "╬"
		单线框架："┏", "┗", "┓", "┛", "━", "┃", "┳", "┻", "┣", "┫", "╋"
		横双竖单: "╒", "╘", "╕", "╛", "═", "│", "╤", "╧", "╞", "╡", "╪"
		横单竖双："╓", "╙", "╖", "╜", "─", "║", "╥", "╨", "╟", "╢", "╫"

		双线框架使用样例（可自行替换为其它线型）
		   ╔═╦═╗
		   ║  ║  ║
		   ╠═╬═╣
		   ║  ║  ║
		   ╚═╩═╝  */

   /* 设置新宋体，28点阵 */
	cct_setconsoleborder(80, 25);
	cct_setfontsize("新宋体", 28); //Truetype字体只需要给出一个参数高度即可
	cout << "设置字体为新宋体28" << endl << endl;
	const char* str = "〇";
	cout << (int)(str[1]);
	to_be_continued("int值");
//	双线框架："╔", "╚", "╗", "╝", "═", "║", "╦", "╩", "╠", "╣", "╬"
	cct_gotoxy(0, 5);
	cout << "**╔═╦═╗ 中" << endl;
	cout << "中║测║试║**" << endl;
	cout << "**╠═╬═╣**" << endl;
	cout << "中║ab║12║中" << endl;
	cout << "**╚═╩═╝中" << endl;
	to_be_continued("正常输出，旧版控制台不乱，新版乱...");

	cout << "**╔══╦══╗中" << endl;
	cout << "中║测║试║**" << endl;
	cout << "**╠══╬══╣**" << endl;
	cout << "中║ab║12║中" << endl;
	cout << "**╚══╩══╝中" << endl;
	to_be_continued("每个横线符号重复输出两次，新版不乱，但位置不对...");

	cct_gotoxy(0, 5);
	cout << "**╔ ═ ╦ ═ ╗ 中" << endl;
	cout << "中║ 测║ 试║ **" << endl;
	cout << "**╠ ═ ╬ ═ ╣ **" << endl;
	cout << "中║ ab║ 12║ 中" << endl;
	cout << "**╚ ═ ╩ ═ ╝ 中" << endl;
	to_be_continued("每个中文制表符后面加一个空格，旧版控制台乱，新版不乱...");

	cct_showstr(0, 5, "**╔═╦═╗中");
	cct_showstr(0, 6, "中║测║试║**");
	cct_showstr(0, 7, "**╠═╬═╣**");
	cct_showstr(0, 8, "中║ab║12║中");
	cct_showstr(0, 9, "**╚═╩═╝中");
	to_be_continued("期望用cct_showstr做到新版控制台不乱...");

	return 0;
}
