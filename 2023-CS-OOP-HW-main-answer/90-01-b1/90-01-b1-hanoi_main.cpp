/* ¼Æ¿Æ 2150792 Å£Â»Ñô */
#include "../include/cmd_console_tools.h"
#include"../include/common.h"
#include"90-01-b1-hanoi.h"


int main()
{
	cct_setconsoleborder(120, 40, 120, 9000);
	char choice = 0, huiche = 0, n = 0;
	char src = '\0', tmp = '\0', dst = '\0';
	while (1) {
		choice = menu(menu_infor_90_01_b1, total_choice_90_01_b1,infor_num_90_01_b1);
		switch (choice) {
			case '0':
				cout << endl;
				return 0;
			case '1':
				exe_1(n, src, tmp, dst, choice);
				break;
			case '2':
				exe_2(n, src, tmp, dst, choice);
				break;
			case '3':
				exe_3(n, src, tmp, dst, choice);
				break;
			case '4':
				exe_4(n, src, tmp, dst, choice);
				break;
			case '5':
				exe_5();
				break;
			case '6':
				exe_6(n, src, tmp, dst, choice);
				break;
			case '7':
				exe_7(n, src, tmp, dst, choice);
				break;
			case '8':
				exe_8(n, src, tmp, dst, choice);
				break;
			case '9':
				exe_9(n, src, tmp, dst, choice);
				break;
		}
		cct_setconsoleborder(120, 40, 120, 9000);
	}
	return 0;
}
