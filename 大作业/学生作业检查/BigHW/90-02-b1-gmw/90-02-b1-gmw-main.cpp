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
bool check_same(int mp[12][12], int vis[12][12], int r, int c)
{
	bool flag = false;
	int dx[] = { 1,-1,0,0 };
	int dy[] = { 0,0,1,-1 };
	for (int i = 0; i < r; i++)
	{
		for (int j = 0; j < c; j++)
		{
			for (int k = 0; k <= 3; k++)
			{
				if (!(i + dx[k] >= 0 && i + dx[k] < r && j + dy[k] >= 0 && j + dy[k] < c))continue;
				if (mp[i][j] == mp[i + dx[k]][j + dy[k]]&&mp[i][j]!=0)
				{
					vis[i][j] = 1;
					flag = true;
				}
			}
		}
	}
	return flag;
}
void replace0(int mp[12][12], int flag[12][12], int same[12][12], int r, int c, int x, int y)
{
	if (flag[x][y] == 1)return;
	flag[x][y] = 1;
	int dx[] = { 1,-1,0,0 };
	int dy[] = { 0,0,1,-1 };
	for (int i = 0; i <= 3; i++)
	{
		int nx = x + dx[i], ny = y + dy[i];
		if (mp[x][y] == mp[nx][ny] && nx >= 0 && nx < r && ny >= 0 && ny < c)
		{
			replace0(mp, flag, same, r, c, nx, ny);
		}
	}
	same[x][y] = 0;
}

int main()
{
	cct_setconsoleborder(120, 40, 120, 9000);
	cct_setcursor(CURSOR_INVISIBLE);
	srand((unsigned)time(NULL));
	int mp[12][12];//地图
	int vis[12][12];//可点击引发消除内容
	int score = 0;
	memset(mp, 0, sizeof mp);
	memset(vis, 0, sizeof vis);
	int r, c;
	cct_cls();
	while (1)
	{
		cout << "请输入行数(8-10)：" << endl;
		cin >> r;
		if (!cin.good() || r > 10 || r < 8)
		{
			cin.clear();
			cin.ignore(9999, '\n');
			continue;
		}
		break;
	}
	while (1)
	{
		cout << "请输入列数(8-10)：" << endl;
		cin >> c;
		if (!cin.good() || c > 10 || c < 8)
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
	gmw_set_rowno_switch(&MyCGI, false);					//显示行号
	gmw_set_colno_switch(&MyCGI, false);					//显示列标
	gmw_set_frame_style(&MyCGI, 6, 3, true);			//设置内容小框
	gmw_set_color(&MyCGI, COLOR_BLACK, COLOR_HWHITE); //改变颜色
	gmw_set_frame_color(&MyCGI, COLOR_HWHITE, COLOR_BLACK);
	gmw_set_frame_default_linetype(&MyCGI, 2);			//边界框用什么类型

	gmw_set_block_border_switch(&MyCGI, true);

	gmw_set_status_line_switch(&MyCGI, TOP_STATUS_LINE, true);//设置上状态栏存在
	gmw_set_status_line_switch(&MyCGI, LOWER_STATUS_LINE, true);//设置下状态栏存在

	//test
	gmw_draw_frame(&MyCGI);

	sprintf(temp1, "%d行 %d列", (MyCGI.lines), MyCGI.cols);
	sprintf(temp2, "%s %d", "目前得分： ", score);
	gmw_status_line(&MyCGI, TOP_STATUS_LINE, temp2, temp1);//上打印

	/* 定义1-5的数字用何种形式显示在界面上（正常状态） */
	const BLOCK_DISPLAY_INFO bdi_normal[] = {
		{0, -1, -1, "  "},  //0不显示，用空格填充即可
		{1, COLOR_HBLUE, COLOR_BLACK, "★"},
		{2, COLOR_HGREEN, COLOR_BLACK, "★"},
		{3, COLOR_HCYAN, COLOR_BLACK, "★"},
		{4, COLOR_HRED, COLOR_BLACK, "★"},
		{5, COLOR_HPINK, COLOR_BLACK, "★"},
		{-999, -1, -1, NULL} //判断结束条件为-999
	};
	/* 定义1-5的数字用何种形式显示在界面上（当前选择项状态+选中后关联项状态） */
	const BLOCK_DISPLAY_INFO bdi_related[] = {
		{BDI_VALUE_BLANK, -1, -1, "  "},  //空白
		{1, COLOR_HBLUE, COLOR_WHITE, "★"},
		{2, COLOR_HGREEN, COLOR_WHITE, "★"},
		{3, COLOR_HCYAN, COLOR_WHITE, "★"},
		{4, COLOR_HRED, COLOR_WHITE, "★"},
		{5, COLOR_HPINK, COLOR_WHITE, "★"},
		{BDI_VALUE_END, -1, -1, NULL} //判断结束条件为-999
	};
	/* 定义1-5的数字用何种形式显示在界面上（选中状态） */
	const BLOCK_DISPLAY_INFO bdi_selected[] = {
		{BDI_VALUE_BLANK, -1, -1, "  "},  //空白
		{1, COLOR_HBLUE, COLOR_HWHITE, "★"},
		{2, COLOR_HGREEN, COLOR_HWHITE, "★"},
		{3, COLOR_HCYAN, COLOR_HWHITE, "★"},
		{4, COLOR_HRED, COLOR_HWHITE, "★"},
		{5, COLOR_HPINK, COLOR_HWHITE, "★"},
		{BDI_VALUE_END, -1, -1, NULL} //判断结束条件为-999
	};

	
	while(1)//关卡的循环
	{
		int num_0 = 0;

		for (int i = 0; i < r; i++)
		{
			for (int j = 0; j < c; j++)
			{
				initial_mp(mp, i, j, 5);
			}
		}
		for (int i = 0; i < r; i++)
		{
			for (int j = 0; j < c; j++)
			{
				gmw_draw_block(&MyCGI, i, j, mp[i][j], bdi_normal);
			}
		}

		while(1)
		{
			memset(vis, 0, sizeof vis);
			if (!check_same(mp, vis, r, c))//如果没有可以消除的，直接break
			{
				sprintf(temp1, "本关结束剩余%d个，回车下一关                  ", r* c - num_0);
				score += (max(0, (10 - (r*c-num_0)) * 180));
				gmw_status_line(&MyCGI, LOWER_STATUS_LINE, temp1);//下打印
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
			//否则可以直接开读键鼠
			int Maction, Mr, Mc, Keycode1, Keycode2;
			bool have_chosen = false;//前一个有没有选择
			int now_x = 1, now_y = 1;
			int before_x = 1, before_y = 1;//上一次选择的
			bool keyboard = false;
			int now_score=0;
			//while (1)
			{
				while(1)//反复读取键鼠功能
				{
					if (!check_same(mp, vis, r, c))//如果没有可以消除的，直接break
					{
						break;
					}
					if (now_score)
					{
						sprintf(temp1, "%d行 %d列", (MyCGI.lines), MyCGI.cols);
						sprintf(temp2, "%s %d %s %d %s", "本轮得分：",now_score,"目前得分：", score,"           ");
						gmw_status_line(&MyCGI, TOP_STATUS_LINE, temp2, temp1);//上打印
						now_score = 0;
					}
					gmw_read_keyboard_and_mouse(&MyCGI, Maction, Mr, Mc, Keycode1, Keycode2, true);

					if (Keycode1 == 0 && Keycode2 == 0)//鼠标已经执行操作
					{
						keyboard = false;
						now_x = Mr, now_y = Mc;
						if (Maction == MOUSE_RIGHT_BUTTON_CLICK)
						{
							return 0;
						}
						else if (Maction == MOUSE_LEFT_BUTTON_CLICK)//左键点了
						{
							if (!vis[now_x][now_y]||mp[now_x][now_y]==0)//都不是合理的位置
							{
								if(mp[now_x][now_y]==0)
								{
									sprintf(temp1, "不能选择%c行%d列                   ", char('A' + now_x), now_y);
									gmw_status_line(&MyCGI, LOWER_STATUS_LINE, temp1);//下打印
								}
								else
								{
									sprintf(temp1, "不能选择%c行%d列：无相同值                   ", char('A' + now_x), now_y);
									gmw_status_line(&MyCGI, LOWER_STATUS_LINE, temp1);//下打印
								}
							}
							else
							{
								if (have_chosen)//点击过了
								{
									int flag[12][12];
									//int same[12][12];
									memset(flag, 0, sizeof flag);
									replace0(mp, flag, mp, r, c,now_x,now_y);
									int temp0 = 0;
									for (int i = 0; i < r; i++)
									{
										for (int j = 0; j < c; j++)
										{
											if(mp[i][j]==0)
											{
												temp0++;
												gmw_draw_block(&MyCGI, i, j, mp[i][j], bdi_normal);//消除掉所有的
											}
										}
									}
									now_score = ( temp0-num_0 ) * (temp0 - num_0) * 5;
									score += now_score;
									num_0 = temp0;
									have_chosen = false;
								}
								else//还没点过
								{
									int flag[12][12];
									int same[12][12];
									memset(same, 1, sizeof same);
									memset(flag, 0, sizeof flag);
									replace0(mp, flag,same, r, c, now_x, now_y);
									for (int i = 0; i < r; i++)
									{
										for (int j = 0; j < c; j++)
										{
											if (same[i][j] == 0)
												gmw_draw_block(&MyCGI, i, j, mp[i][j], bdi_related);//消除掉所有的
										}
									}
									gmw_draw_block(&MyCGI, now_x, now_y, mp[now_x][now_y], bdi_selected);//现在的高亮选择
									have_chosen = true;
								}
							}
						}
						else
						{
							//gmw_draw_block(&MyCGI, now_x, now_y, mp[now_x][now_y], bdi_related);//现在的待选择
						}
					}
					else
					{
						keyboard = true;

						if (Keycode2 == KB_ARROW_DOWN)//下
						{
							now_x = (now_x + 1 < r ? now_x + 1 : now_x);
						}
						else if (Keycode2 == KB_ARROW_UP)//上
						{
							now_x = (now_x - 1 >= 0 ? now_x - 1 : now_x);
						}
						else if (Keycode2 == KB_ARROW_LEFT)//左
						{
							now_y = (now_y - 1 >= 0 ? now_y - 1 : now_y);
						}
						else if (Keycode2 == KB_ARROW_RIGHT)//右
						{
							now_y = (now_y + 1 < c ? now_y + 1 : now_y);
						}
						else if (Keycode1 == 13)//选择
						{
							if (!vis[now_x][now_y] || mp[now_x][now_y] == 0)//都不是合理的位置
							{
								if (mp[now_x][now_y] == 0)
								{
									sprintf(temp1, "不能选择%c行%d列                   ", char('A' + now_x), now_y);
									gmw_status_line(&MyCGI, LOWER_STATUS_LINE, temp1);//下打印
								}
								else
								{
									sprintf(temp1, "不能选择%c行%d列：无相同值                   ", char('A' + now_x), now_y);
									gmw_status_line(&MyCGI, LOWER_STATUS_LINE, temp1);//下打印
								}
							}
							else
							{
								if (have_chosen)//点击过了
								{
									int flag[12][12];
									//int same[12][12];
									memset(flag, 0, sizeof flag);
									int temp0 = 0;
									replace0(mp, flag, mp, r, c, now_x, now_y);
									for (int i = 0; i < r; i++)
									{
										for (int j = 0; j < c; j++)
										{
											if (mp[i][j] == 0)
											{
												temp0++;
												gmw_draw_block(&MyCGI, i, j, mp[i][j], bdi_normal);//消除掉所有的
											}
										}
									}
									now_score = (temp0  - num_0) * (temp0 - num_0) * 5;
									score += now_score;
									num_0 = temp0;
									have_chosen = false;
								}
								else//还没点过
								{
									int flag[12][12];
									int same[12][12];
									memset(same, 1, sizeof same);
									memset(flag, 0, sizeof flag);
									replace0(mp, flag, same, r, c, now_x, now_y);
									for (int i = 0; i < r; i++)
									{
										for (int j = 0; j < c; j++)
										{
											if (same[i][j] == 0)
												gmw_draw_block(&MyCGI, i, j, mp[i][j], bdi_related);//消除掉所有的
										}
									}
									gmw_draw_block(&MyCGI, now_x, now_y, mp[now_x][now_y], bdi_selected);//现在的高亮选择
									have_chosen = true;
								}
							}
						}
					}

					//检查下落和回行问题
					{
						//下落
						{
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
											gmw_move_block(&MyCGI, i - dis, j, mp[i - dis][j], 0, bdi_normal, UP_TO_DOWN, dis);
											mp[i][j] = mp[i - dis][j];
											mp[i - dis][j] = 0;
										}
									}
								}
							}
						}
						//空列
						{
							int flag_no_0 = 0;
							for (int j = c - 1; j >= 0; j--)
							{
								bool full_0 = true;
								for (int i = 0; i< r; i++)
								{
									if (mp[i][j] != 0)
									{
										full_0 = false;
										if (!flag_no_0)
										{
											flag_no_0 = j;
										}
									}
								}
								if (full_0 && flag_no_0>j )//本列全为0并且右边有非0的值
								{
									for (int jj = j+1; jj < c ; jj++)//本列开始向右遍历
									{
										for(int ii=0;ii<r;ii++)
										{
											if(mp[ii][jj]!=0)
											{
												gmw_move_block(&MyCGI, ii, jj, mp[ii][jj], 0, bdi_normal, RIGHT_TO_LEFT, 1);
												mp[ii][jj - 1] = mp[ii][jj];
												mp[ii][jj] = 0;
											}
										}
									}
								}
							}
						}
					}

					if (!((before_x == now_x) && (before_y == now_y)))//移动了
					{
						if (have_chosen)//之前选好了
						{
							have_chosen = false;
							gmw_draw_block(&MyCGI, before_x, before_y, mp[before_x][before_y], bdi_normal);//之前选择的变成普通
							int flag[12][12];
							int same[12][12];
							memset(same, 1, sizeof same);
							memset(flag, 0, sizeof flag);
							replace0(mp, flag, same, r, c, before_x, before_y);
							for (int i = 0; i < r; i++)
							{
								for (int j = 0; j < c; j++)
								{
									if (same[i][j] == 0)
										gmw_draw_block(&MyCGI, i, j, mp[i][j], bdi_normal);//原来的全部变普通
								}
							}
							gmw_draw_block(&MyCGI, now_x, now_y, mp[now_x][now_y], bdi_related);//现在的待选择
						}
						else//之前没选
						{
							gmw_draw_block(&MyCGI, before_x, before_y, mp[before_x][before_y], bdi_normal);//之前选择的变成普通
							gmw_draw_block(&MyCGI, now_x, now_y, mp[now_x][now_y], bdi_related);//现在的待选择
						}

						before_x = now_x;
						before_y = now_y;

					}
					else
					{
						/*before_x = now_x;
						before_y = now_y;*/
					}
				}
				
			}

		}
	
	
	}


}