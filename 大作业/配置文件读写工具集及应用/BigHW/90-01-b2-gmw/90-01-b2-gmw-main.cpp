/*2351114 朱俊泽 大数据*/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <climits>
#include <conio.h>
#include <iomanip>
#include <windows.h>
#include "../include/cmd_console_tools.h"
#include"../include/base_work_fun.h"
#include "../include/cmd_gmw_tools.h"
using namespace std;

void initial_mp(int mp[12][12], int x, int y, int top)
{
	int rd = rand() % top + 1;
	mp[x][y] = rd;
}
bool check_same(int mp[12][12],int remove_mp[12][12], int r, int c)
{
	bool flag = false;
	for (int i = 0; i < r; i++)
	{
		for (int j = 0; j < c - 2; j++)
		{
			if (mp[i][j] == mp[i][j + 1] && mp[i][j + 1] == mp[i][j + 2])
			{
				remove_mp[i][j] = 1;
				remove_mp[i][j+1] = 1;
				remove_mp[i][j+2] = 1;
				flag= true;
			}
		}
	}
	for (int i = 0; i < c; i++)
	{
		for (int j = 0; j < r - 2; j++)
		{
			if (mp[j][i] == mp[j + 1][i] && mp[j + 1][i] == mp[j + 2][i])
			{
				remove_mp[j][i] = 1;
				remove_mp[j+1][i] = 1;
				remove_mp[j+2][i] = 1;
				flag = true;
			}
		}
	}
	return flag;
}
void show_potential(int mp[12][12],int remove_mp[12][12], int vis[12][12], int r, int c)
{
	//把vis作为potential_remove标记能够移动实现的内容
	int dx[5] = { 0,0,1,-1 };
	int dy[5] = { 1,-1,0,0 };
	memset(vis, 0, sizeof vis);
	for (int i = 0; i < r; i++)
	{
		for (int j = 0; j < c; j++)
		{
			for (int k = 0; k < 4; k++)
			{
				int nx = i + dx[k], ny = j + dy[k];
				int temp = mp[i][j];
				if (nx < 0 || nx >= r || ny < 0 || ny >= c)
					continue;
				mp[i][j] = mp[nx][ny];
				mp[nx][ny] = temp;
				if (check_same(mp, remove_mp,r, c))
				{
					for (int ni = 1; ni <= r; ni++)
					{
						for (int nj = 1; nj <= c - 2; nj++)
						{
							if (mp[ni][nj] == mp[ni][nj + 1] && mp[ni][nj + 1] == mp[ni][nj + 2])
							{
								vis[i][j] = 1;
								vis[nx][ny] = 1;
							}
						}
					}
					for (int ni = 1; ni <= c; ni++)
					{
						for (int nj = 1; nj <= r - 2; nj++)
						{
							if (mp[nj][ni] == mp[nj + 1][ni] && mp[nj + 1][ni] == mp[nj + 2][ni])
							{
								vis[i][j] = 1;
								vis[nx][ny] = 1;
							}
						}
					}
				}
				mp[nx][ny] = mp[i][j];
				mp[i][j] = temp;
			}
		}
	}
}
int main()
{
	cct_setconsoleborder(120, 40, 120, 9000);
	cct_setcursor(CURSOR_INVISIBLE);
	srand((unsigned)time(NULL));
	int mp[12][12];
	int remove_mp[12][12];
	int potential_remove[12][12];
	memset(mp, 0, sizeof mp);
	memset(remove_mp, 0, sizeof remove_mp);
	memset(potential_remove, 0, sizeof potential_remove);
	int r, c;
	cct_cls();
	while (1)
	{
		cout << "请输入行数(5-9)：" << endl;
		cin >> r;
		if (!cin.good() || r > 9 || r < 5)
		{
			cin.clear();
			cin.ignore(9999, '\n');
			continue;
		}
		break;
	}
	while (1)
	{
		cout << "请输入列数(5-9)：" << endl;
		cin >> c;
		if (!cin.good() || c > 9 || c < 5)
		{
			cin.clear();
			cin.ignore(9999, '\n');
			continue;
		}
		break;
	}
	CONSOLE_GRAPHICS_INFO MyCGI; //声明一个CGI变量
	char temp1[256];
	char temp2[256];
	int score = 0;
	/* 先做初始化，这样后续可以在此基础上任意修改部分设置，其余采用预设值
		游戏区域（主框架）为10*10，带分隔线，每个色块的大小为2列*1行，色块不带边框
		窗口背景色黑，前景色白
		字体为点阵，8*16
		画边框及色块时无延时，色块移动时延时3ms
		上下左右辅助区域全部为0
		上状态栏开，正常文本颜色同窗口，醒目文本背景同窗口，前景为亮黄
		下状态栏开，正常文本颜色同窗口，醒目文本背景同窗口，前景为亮黄
		不显示行号
		不显示列标
		游戏区域为双线框，带分隔线，色块大小为2（宽度2列=1个汉字）*1（高度1行），颜色同窗口
		色块为双框线，颜色（未完）*/		
	gmw_init(&MyCGI);
	gmw_set_rowcol(&MyCGI, r, c);
	gmw_set_font(&MyCGI, "新宋体", 24, 18);
	gmw_set_rowno_switch(&MyCGI, false);					//显示行号
	gmw_set_colno_switch(&MyCGI, false);					//显示列标
	gmw_set_frame_style(&MyCGI, 2, 1, true);			//设置内容小框
	gmw_set_color(&MyCGI,COLOR_BLACK ,COLOR_HWHITE); //改变颜色
	gmw_set_frame_color(&MyCGI, COLOR_HWHITE, COLOR_BLACK);
	gmw_set_frame_default_linetype(&MyCGI, 1);			//边界框用什么类型



	gmw_set_status_line_switch(&MyCGI, TOP_STATUS_LINE, true);//设置上状态栏存在
	gmw_set_status_line_switch(&MyCGI, LOWER_STATUS_LINE, true);//设置下状态栏存在

	//test
	gmw_draw_frame(&MyCGI);
	sprintf(temp1, "%d行 %d列", (MyCGI.lines), MyCGI.cols);
	sprintf(temp2, "%s %d", "目前得分： ",score);
	gmw_status_line(&MyCGI, TOP_STATUS_LINE,  temp2,temp1);//上打印

	gmw_status_line(&MyCGI, LOWER_STATUS_LINE, "输入End返回", "测试结束，");//下打印
	

	/* 定义1-7的数字用何种形式显示在界面上
	   - 注：1、本例采用将“正常+选中”信息放在一个数组中的方法
				1-7表示正常，11-17表示选中
			 2、实际实现中的数组值不要求如此，此处仅仅是为了色块的不同状态的显示
			  3、在 test_magic_ball 中用了另外一种方式表示色块的不同状态，可以对照 */
	const BLOCK_DISPLAY_INFO bdi[] = {
		{BDI_VALUE_BLANK, -1, -1, "  "},  //0不显示，用空格填充即可
		{1,  COLOR_HBLACK, -1, "〇"},	//正常状态数字1所对应的彩球
		{2,  COLOR_YELLOW, -1, "〇"},
		{3,  COLOR_HGREEN, -1, "〇"},
		{4,  COLOR_HCYAN, -1, "〇"},
		{5,  COLOR_HRED, -1, "〇"},
		{6,  COLOR_HPINK, -1, "〇"},
		{7,  COLOR_HYELLOW, -1, "〇"},
		{11, COLOR_HBLACK, -1, "◎"},//选中状态数字1所对应的彩球图案
		{12, COLOR_YELLOW, -1, "◎"},
		{13, COLOR_HGREEN, -1, "◎"},
		{14, COLOR_HCYAN, -1, "◎"},
		{15, COLOR_HRED, -1, "◎"},
		{16, COLOR_HPINK, -1, "◎"},
		{17, COLOR_HYELLOW, -1, "◎"},
		{21, COLOR_HBLACK, -1, "●"},//被消除状态数字1所对应的彩球图案
		{22, COLOR_YELLOW, -1, "●"},
		{23, COLOR_HGREEN, -1, "●"},
		{24, COLOR_HCYAN, -1, "●"},
		{25, COLOR_HRED, -1, "●"},
		{26, COLOR_HPINK, -1, "●"},
		{27, COLOR_HYELLOW, -1, "●"},
		{31, COLOR_HBLACK, -1, "¤"},//被消除状态（带边角）数字1所对应的彩球图案
		{32, COLOR_YELLOW, -1, "¤"},
		{33, COLOR_HGREEN, -1, "¤"},
		{34, COLOR_HCYAN, -1, "¤"},
		{35, COLOR_HRED, -1, "¤"},
		{36, COLOR_HPINK, -1, "¤"},
		{37, COLOR_HYELLOW, -1, "¤"},
		{41, COLOR_HBLACK, 15, "◎"},//选中状态并且点击数字1所对应的彩球图案
		{42, COLOR_YELLOW, 15, "◎"},
		{43, COLOR_HGREEN, 15, "◎"},
		{44, COLOR_HCYAN, 15, "◎"},
		{45, COLOR_HRED, 15, "◎"},
		{46, COLOR_HPINK, 15, "◎"},
		{47, COLOR_HYELLOW, 15, "◎"},
		{BDI_VALUE_END, -1, -1, NULL} //判断结束条件为-999
	};
	const int BDI_NORMAL = 0, BDI_SELECTED = 10 ,BDI_REMOVE = 20,BDI_REMOVE_COR =30, BDI_SELECTED_WHITE=40;//一个是没有被选择的基础值，一个是被选择了的基值，一个是被消除的基值

	for (int i = 0; i < r; i++)
	{
		for (int j = 0; j < c; j++)
		{
			initial_mp(mp, i, j, 7);
		}
	}
	for (int i = 0; i < r; i++)
	{
		for (int j = 0; j < c; j++)
		{
			gmw_draw_block(&MyCGI, i, j, BDI_NORMAL + mp[i][j], bdi);
		}
	}

	//开始游戏
	while (1)
	{
		while (check_same(mp,remove_mp, r, c))//有现在可以消除的内容
		{
			//先标黑
			for (int i = 0; i < r; i++)
			{
				for (int j = 0; j < c; j++)
				{
					if (remove_mp[i][j] == 1)
					{
						score++;
						gmw_draw_block(&MyCGI, i, j, BDI_REMOVE + mp[i][j], bdi);
					}
				}
			}
			//再闪烁消除
			for (int i = 0; i < r; i++)
			{
				for (int j = 0; j < c; j++)
				{
					if (remove_mp[i][j] == 1)
					{
						for (int k = 1; k <= 3; k++)//闪烁消除
						{
							gmw_draw_block(&MyCGI, i, j, BDI_REMOVE_COR + mp[i][j], bdi);
							Sleep(100);
							gmw_draw_block(&MyCGI, i, j, BDI_REMOVE + mp[i][j], bdi);
							Sleep(100);
						}
						gmw_draw_block(&MyCGI, i, j, BDI_VALUE_BLANK, bdi);
						mp[i][j] = 0;
					}
				}
			}
			memset(remove_mp, 0, sizeof remove_mp);

			sprintf(temp1, "%d行 %d列", (MyCGI.lines), MyCGI.cols);
			sprintf(temp2, "%s %d", "目前得分： ", score);
			gmw_status_line(&MyCGI, TOP_STATUS_LINE, temp2, temp1);//上打印

			for (int i = r - 1; i >= 0; i--)
			{
				for (int j = 0; j < c; j++)
				{
					if (mp[i][j] == 0)
					{
						int dis = 0;
						while (i - dis >= 0 && mp[i - dis][j] == 0)
						{
							dis++;
						}
						if (i - dis < 0)//头上全是0
							continue;
						else//头上有非零的可以交换
						{
							gmw_move_block(&MyCGI, i - dis, j, mp[i - dis][j], 0, bdi, UP_TO_DOWN, dis);
							mp[i][j] = mp[i - dis][j];
							mp[i - dis][j] = 0;
						}
					}
				}
			}
			for (int i = 0; i < r; i++)
			{
				for (int j = 0; j < c; j++)
				{
					if (mp[i][j] == 0)
					{
						initial_mp(mp, i, j, 7);
						gmw_draw_block(&MyCGI, i, j, BDI_NORMAL + mp[i][j], bdi);
					}
				}
			}

		}//消除干净为止
		//检测有没有可交换消除的量
		memset(potential_remove, 0, sizeof potential_remove);
		show_potential(mp, remove_mp, potential_remove, r, c);
		bool end_flag = true;
		for (int i = 0; i < r; i++)
		{
			for (int j = 0; j < c; j++)
			{
				if (potential_remove[i][j] == 1)
				{
					gmw_draw_block(&MyCGI, i, j, BDI_SELECTED + mp[i][j], bdi);
					end_flag = false;
				}
				else
				{
					gmw_draw_block(&MyCGI, i, j, BDI_NORMAL + mp[i][j], bdi);
				}
			}
		}

		if (end_flag)
		{
			break;
		}

		int Maction, Mr, Mc, Keycode1, Keycode2;
		bool have_chosen = false;//前一个有没有选择
		int before_x=-1, before_y=-1;//上一次选择的
		while(1)//反复读取键鼠功能
		{
			gmw_read_keyboard_and_mouse(&MyCGI, Maction, Mr, Mc, Keycode1, Keycode2, true);
			if (Maction == MOUSE_RIGHT_BUTTON_CLICK)
			{
				return 0;
			}
			if (Maction == MOUSE_LEFT_BUTTON_CLICK)
			{
				if (!potential_remove[Mr][Mc])//不是合适的点
				{
					sprintf(temp1, "不能选择%c行%d列                   ", char('A' + Mr), Mc);
					gmw_status_line(&MyCGI, LOWER_STATUS_LINE, temp1);//下打印

					if (have_chosen)
					{
						gmw_draw_block(&MyCGI, before_x, before_y, BDI_SELECTED + mp[before_x][before_y], bdi);
						have_chosen = false;
					}
				}
				else//是可以选择的点
				{
					if (have_chosen)//之前选择过了
					{
						if (before_x == Mr && before_y == Mc)//第二次选择相同位置不变
							continue;
						else if (abs(before_x - Mr) + abs(before_y - Mc) > 1)//两次选择并不是相邻
						{
							gmw_draw_block(&MyCGI, before_x, before_y, BDI_NORMAL + mp[before_x][before_y], bdi);
							gmw_draw_block(&MyCGI, Mr, Mc, BDI_SELECTED_WHITE + mp[Mr][Mc], bdi);
							before_x = Mr, before_y = Mc;//本次选择第二次进入while循环变成上次选择
						}
						else//选择的是相邻的
						{
							int useless[12][12];
							int temp = mp[before_x][before_y];
							mp[before_x][before_y] = mp[Mr][Mc];
							mp[Mr][Mc] = temp;
							//先交换，判断这两个是不是可交换内容（交换之后有消除）
							if (check_same(mp, useless, r, c))
							{
								gmw_draw_block(&MyCGI, Mr, Mc, BDI_NORMAL + mp[Mr][Mc], bdi);
								gmw_draw_block(&MyCGI, before_x, before_y, BDI_NORMAL + mp[before_x][before_y], bdi);
								memset(remove_mp, 0, sizeof remove_mp);
								break;//可以跳出了，重新进入一次循环
							}
							else//如果不是需要换回来！
							{
								int temp = mp[before_x][before_y];
								mp[before_x][before_y] = mp[Mr][Mc];
								mp[Mr][Mc] = temp;

								sprintf(temp1, "%c行%d列  和 %c行%d列 无法交换！            ", char('A' + Mr), Mc ,char('A'+before_x),before_y);
								gmw_status_line(&MyCGI, LOWER_STATUS_LINE, temp1);//下打印

								have_chosen = false;

								gmw_draw_block(&MyCGI, Mr, Mc, BDI_SELECTED + mp[Mr][Mc], bdi);
								gmw_draw_block(&MyCGI, before_x, before_y, BDI_SELECTED + mp[before_x][before_y], bdi);

							}

						}
					}
					else
					{
						gmw_draw_block(&MyCGI, Mr, Mc, BDI_SELECTED_WHITE + mp[Mr][Mc], bdi);
						have_chosen = true;//已经选择
						before_x = Mr, before_y = Mc;//本次选择第二次进入while循环变成上次选择
					}
				}
			}

		}

	}

}