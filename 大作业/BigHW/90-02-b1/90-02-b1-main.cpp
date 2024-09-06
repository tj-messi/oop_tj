/* Ñ§ºÅ °à¼¶ ÐÕÃû */
#include <iostream>
#include "../include/cmd_console_tools.h"
using namespace std;

int main()
{
	cct_cls();
	cct_showstr(10, 10, "Hello, world!", COLOR_HYELLOW, COLOR_HBLUE);
	cct_setcolor();
	cct_gotoxy(0, 24);
	return 0;
}
