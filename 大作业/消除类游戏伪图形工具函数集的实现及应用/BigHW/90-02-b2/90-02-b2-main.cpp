/*2351114 朱俊泽 大数据*/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <climits>
#include <conio.h>
#include<ctime>
#include <iomanip>
#include <windows.h>
#include "../include/cmd_console_tools.h"
#include"../include/base_work_fun.h"
#include "../include/cmd_gmw_tools.h"
using namespace std;

void check_show(int x, int y, int r, int c, int mp[35][35],int vis[35][35],int flag[35][35])
{
	//检查可以一次性爆出的内容

	if (flag[x][y])
		return;

	flag[x][y] = 1;

	int dx[] = { 0,0,1,1,1,-1,-1,-1 };
	int dy[] = { 1,-1,0,1,-1,0,1,-1 };
	if (mp[x][y]!=0)
	{
		vis[x][y] = 1;
		return;
	}
	else
	{
		for (int i = 0; i < 8; i++)
		{
			int nx = x + dx[i];
			int ny = y + dy[i];
			if (nx < 0 || nx >= r || ny < 0 || ny >= c)
				continue;
			if (!mp[nx][ny])
			{
				vis[nx][ny] = 1;
				check_show(nx, ny, r, c, mp, vis, flag);
			}
			else
			{
				vis[nx][ny] = 1;
			}
		}
	}

}

class Timer {
public:
	Timer() {
		// 初始化计数器变量  
		LARGE_INTEGER frequency;
		QueryPerformanceFrequency(&frequency);
		freq = static_cast<double>(frequency.QuadPart);

		// 获取初始计数器值  
		QueryPerformanceCounter(&startCounter);
	}

	// 停止计时器并返回经过的时间（秒）  
	double stop() {
		// 获取结束计数器值  
		LARGE_INTEGER endCounter;
		QueryPerformanceCounter(&endCounter);

		// 计算经过的时间（秒）  
		return static_cast<double>(endCounter.QuadPart - startCounter.QuadPart) / freq;
	}

private:
	LARGE_INTEGER startCounter; // 开始计数器值  
	double freq; // 计数器的频率（每秒的计数次数）  
};

int main()
{
	while(1)
	{
		cct_setconsoleborder(120, 40, 120, 9000);
		cct_setcursor(CURSOR_INVISIBLE);
		cct_setcolor(0);
		srand((unsigned)time(NULL));
		int mp[35][35];//地图
		int red[35][35];
		int have_reveal[35][35];//已经打开的内容不能再开
		memset(have_reveal, 0, sizeof have_reveal);
		memset(red, 0, sizeof red);
		memset(mp, 0, sizeof mp);
		int r, c;
		int level;
		int mines;
		cct_cls();
		while (1)
		{
			cout << "请输入扫雷游戏的等级（数字），初级\\中级\\高级(1\\2\\3)：" << endl;
			cin >> level;
			if (!cin.good() || level > 3 || level < 1)
			{
				cin.clear();
				cin.ignore(9999, '\n');
				continue;
			}
			break;
		}
		switch (level)
		{
			case 1:
			{
				r = 9;
				c = 9;
				mines = 10;
				break;
			}
			case 2:
			{
				r = 16;
				c = 16;
				mines = 40;
				break;
			}
			case 3:
			{
				r = 16;
				c = 30;
				mines = 99;
				break;
			}
		}
		CONSOLE_GRAPHICS_INFO MyCGI; //声明一个CGI变量
		char temp1[256];
		char temp2[256];
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
		gmw_set_font(&MyCGI, "新宋体", 16, 0);
		gmw_set_rowno_switch(&MyCGI, true);					//显示行号
		gmw_set_colno_switch(&MyCGI, true);					//显示列标
		gmw_set_frame_style(&MyCGI, 4, 2, true);			//设置内容小框
		gmw_set_color(&MyCGI, COLOR_BLACK, COLOR_HWHITE);   //改变颜色
		gmw_set_frame_color(&MyCGI, COLOR_HWHITE, COLOR_BLACK);
		gmw_set_frame_default_linetype(&MyCGI, 1);  //边界框用什么类型

		gmw_set_block_border_switch(&MyCGI, false);
		gmw_set_frame_style(&MyCGI, 4, 2, true);
		//gmw_set_block_linetype(&MyCGI," ","0"," "," "," "," ");

		gmw_set_status_line_switch(&MyCGI, TOP_STATUS_LINE, true);   //设置上状态栏存在
		gmw_set_status_line_switch(&MyCGI, 1, true);   //设置下状态栏存在

		//test
		gmw_draw_frame(&MyCGI);

		sprintf(temp1, "空格显示时间，esc退出      ");
		sprintf(temp2, "  ");
		gmw_status_line(&MyCGI, TOP_STATUS_LINE, temp1, temp2);//上打印

		//被揭开的内容
		const BLOCK_DISPLAY_INFO bdi_reveal[] = {
			{BDI_VALUE_BLANK, COLOR_WHITE, COLOR_WHITE, NULL},  //0不显示，用空格填充即可
			{1, COLOR_WHITE, COLOR_BLUE, "1"},
			{2, COLOR_WHITE, COLOR_GREEN, "2"},
			{3, COLOR_WHITE, COLOR_HBLUE, "3"},
			{4, COLOR_WHITE, COLOR_RED, "4"},
			{5, COLOR_WHITE, COLOR_PINK, "5"},
			{6, COLOR_WHITE, COLOR_HGREEN, "6"},
			{7, COLOR_WHITE, COLOR_CYAN, "7"},
			{8, COLOR_WHITE, COLOR_BLACK, "8"},
			{BDI_VALUE_END, -1, -1, NULL} //判断结束条件为-999
		};
		//还没被揭开的内容
		const BLOCK_DISPLAY_INFO bdi_hidden[] = { 0,COLOR_YELLOW, COLOR_YELLOW,NULL };
		//抽中雷了
		const BLOCK_DISPLAY_INFO bdi_mine[] = { 1,COLOR_WHITE, COLOR_BLACK,"*" };
		//标记旗子了
		const BLOCK_DISPLAY_INFO bdi_masked[] = { 1,COLOR_RED, COLOR_WHITE,"#" };
		for (int i = 0; i < r; i++)
		{
			for (int j = 0; j < c; j++)
			{
				gmw_draw_block(&MyCGI, i, j, 0, bdi_hidden);
			}
		}
		/*
		{
			double stoptime = timer.stop();
			sprintf(temp1, "空格显示时间，esc退出     ");
			sprintf(temp2, "时间：%lf ", stoptime);
			gmw_status_line(&MyCGI, TOP_STATUS_LINE, temp2, temp1);//上打印
		}*/
		Timer timer;
		int Maction, Mr, Mc, Keycode1=0, Keycode2=0;
		bool first_chosen = true;//第一次选择：不能暴雷
		int before_x = -1, before_y = -1;//上一次选择的
		while (1)//反复读取键鼠功能
		{
			gmw_read_keyboard_and_mouse(&MyCGI, Maction, Mr, Mc, Keycode1, Keycode2, true);
			//鼠标键盘操作
			{
				if (Keycode1 == 32)
				{
					double stoptime = timer.stop();
					sprintf(temp1, "空格显示时间，esc退出     ");
					sprintf(temp2, "时间：%lf ", stoptime);
					gmw_status_line(&MyCGI, TOP_STATUS_LINE, temp2, temp1);//上打印
				}
				if (Keycode1 == 27)
				{
					break;
				}
				if (Maction == MOUSE_RIGHT_BUTTON_CLICK)//右键
				{
					if (have_reveal[Mr][Mc])
					{
						//已经被打开了
						continue;
					}
					if (red[Mr][Mc] == 0)//标记旗子
					{
						red[Mr][Mc] = 1;//20作为标记旗子的点位
						gmw_draw_block(&MyCGI, Mr, Mc, 1, bdi_masked);
						mines--;
						sprintf(temp1, "空格显示时间，esc退出      ");
						sprintf(temp2, "%s%d","剩余地雷:",max(mines,0));
						gmw_status_line(&MyCGI, TOP_STATUS_LINE, temp2, temp1);//上打印
					}
					else
					{
						red[Mr][Mc] = 0;
						gmw_draw_block(&MyCGI, Mr, Mc, 0, bdi_hidden);
						mines++;
						sprintf(temp1, "空格显示时间，esc退出      ");
						sprintf(temp2, "%s%d", "剩余地雷:", max(0,mines));
						gmw_status_line(&MyCGI, TOP_STATUS_LINE, temp2, temp1);//上打印
					}
				}
				if (Maction == MOUSE_LEFT_BUTTON_CLICK)//左键
				{
					if (first_chosen)//第一次选择，给整个数组初始化
					{
						first_chosen = false;
						while (1)
						{
							memset(mp, 0, sizeof mp);
							for (int num = 1; num <= mines; num++)
							{
								int x = rand() % r;
								int y = rand() % c;
								if (mp[x][y] == 10 || (x == Mr && y == Mc))//10代表是雷,或者初始化到了本次点击位置
								{
									num--;
									continue;
								}
								else
									mp[x][y] = 10;
							}

							//更新map具体内容
							int dx[] = { 0,0,1,1,1,-1,-1,-1 };
							int dy[] = { 1,-1,0,1,-1,0,1,-1 };
							for (int i = 0; i < r; i++)
							{
								for (int j = 0; j < c; j++)
								{
									if (mp[i][j] == 10)
										continue;
									for (int k = 0; k < 9; k++)
									{
										int nx = i + dx[k], ny = j + dy[k];
										if (nx < 0 || nx >= r || ny < 0 || ny >= c)
											continue;
										if (mp[nx][ny] == 10)
											mp[i][j]++;
									}
								}
							}
							if (mp[Mr][Mc] == 0)
								break;
						}

						/*for (int i = 0; i < r; i++)
						{
							for (int j = 0; j < c; j++)
							{
								if(mp[i][j]==10)
									gmw_draw_block(&MyCGI, i, j, 1, bdi_mine);
								else
									gmw_draw_block(&MyCGI, i, j, mp[i][j], bdi_reveal);
							}
						}*/
						//处理一次性输出的内容，因为是第一次点击所以不会出现踩雷的状态
						if (red[Mr][Mc] == 1)
						{
							first_chosen = true;
							continue;
						}

						int vis[35][35];
						int flag[35][35];
						memset(flag, 0, sizeof flag);
						memset(vis, 0, sizeof vis);
						check_show(Mr, Mc, r, c, mp, vis, flag);

						for (int i = 0; i < r; i++)
						{
							for (int j = 0; j < c; j++)
							{
								if (vis[i][j] && red[i][j] != 1)
								{
									have_reveal[i][j] = 1;
									gmw_draw_block(&MyCGI, i, j, mp[i][j], bdi_reveal);
								}
							}
						}
					}
					else//可能按到雷！
					{
						if (red[Mr][Mc] == 1)//红点不按
						{
							//first_chosen = true;
							continue;
						}

						if (mp[Mr][Mc] == 10)//按到雷了
						{
							gmw_draw_block(&MyCGI, Mr, Mc, 1, bdi_mine);
							sprintf(temp1, "%s ", "选择到了地雷！ 你输了！ 按回车继续......");
							gmw_status_line(&MyCGI, LOWER_STATUS_LINE, "    ", temp1);//下打印

							int cmd;
							while (1)
							{
								cmd = _getch();
								if (cmd == 13)
								{
									break;
								}
							}
							break;
						}

						int vis[35][35];
						int flag[35][35];
						memset(flag, 0, sizeof flag);
						memset(vis, 0, sizeof vis);
						check_show(Mr, Mc, r, c, mp, vis, flag);

						for (int i = 0; i < r; i++)
						{
							for (int j = 0; j < c; j++)
							{
								if (vis[i][j] && red[i][j] != 1)
								{
									have_reveal[i][j] = 1;
									gmw_draw_block(&MyCGI, i, j, mp[i][j], bdi_reveal);
								}
							}
						}
					}
				}
			}
			//判断结束
			{
				int end_flag = true;
				for (int i = 0; i < r; i++)
				{
					for (int j = 0; j < c; j++)
					{
						if (red[i][j]&&mp[i][j]!=10)
						{
							end_flag = false;
						}
						if (mp[i][j] == 10 && red[i][j] != 1)
						{
							end_flag = false;
						}
						if (mp[i][j] != 10 && have_reveal[i][j] != 1)
						{
							end_flag = false;
						}
					}
				}
				if (first_chosen)
					end_flag = false;
				if (end_flag)
				{
					double stoptime = timer.stop();
					sprintf(temp1, "%s %lf", "游戏结束！回车重新开始用时：", stoptime);
					gmw_status_line(&MyCGI, LOWER_STATUS_LINE, " ", temp1);//下打印
					int cmd;
					while (1)
					{
						cmd = _getch();
						if (cmd == 13)
						{
							break;
						}
					}
					break;
				}
			}
		}
	}
}