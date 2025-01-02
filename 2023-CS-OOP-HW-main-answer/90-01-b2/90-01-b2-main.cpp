/*2150792 计科 牛禄阳*/
#include"../include/cmd_console_tools.h"
#include"../include/common.h"
#include"90-01-b2.h"

/*Read Me
  在完成大作业时，我仔细分析了demo显示的不理想之处，并尝试进行改进。特此将我的作业与demo的不同之处
  在此说明，希望便于老师/助教批改作业时查看。
  1.第三小题中，demo打印的移动后的数组时已经把三个将要新生成的球放进去，或者直接消去相连的球，所以下面的
	当前数组和移动后的数组一模一样。 个人认为这种形式不能直观体现球的移动和消去，所以我显示的移动后的数组
	仅仅是把要移动的球给移动到指定位置，不打印新的球，也不消去，但如果能消去，此时已经计分。然后在当前数组
	的显示中，打印新出现的球，消去相连的球。注意这里会特别判断，是不是因为新出现的三个球恰好和之前的四个球
	相连，然后被消去，这种情况下，会消去，但不会计入得分，这也是demo的一个bug。同样cmd界面移动彩球时也会
	解决这个bug。
  2.cmd图形界面的彩球移动，并没有和demo一样，球从某个框上通过，此框换了一种形状，而是保持原形状。当然，这点
	与1相比是影响更小的改动。
*/

int main()
{
	while (1)
	{
		char choice = 0;
		cct_cls();
		cct_setconsoleborder(120, 30, 120, 9001);//设置菜单窗口大小
		choice = menu(menu_infor_90_01_b2, total_choice_90_01_b2, infor_num_90_01_b2);
		if (choice == '0')
			return 0;
		cct_cls();
		int tmp = 0, score = 0;
		switch (choice)
		{
			case '1':
				fun_1(choice);
				break;
			case '2':
				fun_2(choice);
				break;
			case '3':
				fun_3(choice);
				break;
			case '4':
				fun_4(choice);
				break;
			case '5':
				fun_5(choice);
				break;
			case '6':
				fun_6(choice);
				break;
			case '7':
				fun_7(choice);
				break;
		}
	}
	return 0;
}

