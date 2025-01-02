/*2150792 计科 牛禄阳*/
#include"../include/cmd_console_tools.h"
#include"../include/common.h"
#include"90-02-b1.h"
using namespace std;

int main()
{
	while (1)
	{
		char choice = 0;
		cct_cls();
		cct_setconsoleborder(130, 40, 13, 9001);//设置菜单窗口大小
		cct_setfontsize("新宋体", 32);
		choice = menu(menu_infor_90_02_b1, total_choice_90_02_b1, infor_num_90_02_b1);
		if (choice == '0')
			return 0;
		cct_cls();
		if (choice == total_choice_90_02_b1[0])
			fun1();
		else if (choice == total_choice_90_02_b1[1])
			fun2();
		else if (choice == total_choice_90_02_b1[2])
			fun3();
		else if (choice == total_choice_90_02_b1[3])
			fun4();
		else if (choice == total_choice_90_02_b1[4])
			fun5();
		else if (choice == total_choice_90_02_b1[5])
			fun6();
		else if (choice == total_choice_90_02_b1[6])
			fun7();
		else if (choice == total_choice_90_02_b1[7])
			fun8();
	}
	return 0;
}
