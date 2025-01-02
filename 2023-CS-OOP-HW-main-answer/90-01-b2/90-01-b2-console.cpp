/*2150792 计科 牛禄阳*/
#include"../include/cmd_console_tools.h"
#include"../include/common.h"
#include"90-01-b2.h"

//消除判断，fun_7,静态全局
//cmd界面各功能实现的函数
void fun_4(char choice)
{
	//line代表行数，col代表列数，但game_array中第一个是行！！！第二个是列！！！x代表列，y代表行！！！对应关系
	int line = 0, col = 0, game_array[9][9] = { 0 }, predict_next_ball[3] = { 0 }, flag_first_appendarray = 0;
	elem_queue back_path[100] = { 0,0 };//用于彩球移动成功后路径坐标的记录

	inputdata_linecol(&line, &col);
	append_game_array('3', game_array, line, col, predict_next_ball, flag_first_appendarray);
	flag_first_appendarray = 1;
	print_game_array(game_array, line, col, '1', predict_next_ball, back_path);
	cout << endl << "按回车键显示图形..." << endl;
	huiche_conti();
	cct_cls();
	change_typeface_cmd(line, col, '4');
	cct_enable_mouse();//允许使用鼠标，放在设置命令行窗口大小后
	print_gird(line, col, choice, 0);//画格子
	for (int i = 0; i < line; i++)
		for (int j = 0; j < col; j++)
			if (game_array[i][j] != 0)
				print_ball(game_array[i][j], i, j, choice);
	cct_gotoxy(0, line + 2);
	input_end_continue();
}

void fun_5(char choice)
{
	//line代表行数，col代表列数，但game_array中第一个是行！！！第二个是列！！！x代表列，y代表行！！！对应关系
	int line = 0, col = 0, game_array[9][9] = { 0 }, predict_next_ball[3] = { 0 }, flag_first_appendarray = 0;
	elem_queue back_path[100] = { 0,0 };//用于彩球移动成功后路径坐标的记录

	inputdata_linecol(&line, &col);
	append_game_array('3', game_array, line, col, predict_next_ball, flag_first_appendarray);
	flag_first_appendarray = 1;
	print_game_array(game_array, line, col, '1', predict_next_ball, back_path);
	cout << endl << "按回车键显示图形..." << endl;
	huiche_conti();
	cct_cls();
	change_typeface_cmd(line, col, '5');
	cct_enable_mouse();//允许使用鼠标，放在设置命令行窗口大小后
	print_gird(line, col, choice, 0);
	for (int i = 0; i < line; i++)
		for (int j = 0; j < col; j++)
			if (game_array[i][j] != 0)
				print_ball(game_array[i][j], i, j, choice);
	cct_gotoxy(0, 2 * line + 1);
	input_end_continue();
}

void fun_6(char choice)
{
	//line代表行数，col代表列数，但game_array中第一个是行！！！第二个是列！！！x代表列，y代表行！！！对应关系
	int line = 0, col = 0, game_array[9][9] = { 0 }, predict_next_ball[3] = { 0 }, flag_first_appendarray = 0;
	char sta_line, sta_col, des_line, des_col;//设置用于彩球移动的起始坐标和目的坐标
	elem_queue back_path[100] = { 0,0 }, del_locate[100] = { 0,0 };//用于彩球移动成功后路径坐标的记录
	int tmp = 0, color_ball = 0;
	inputdata_linecol(&line, &col);
	append_game_array('2', game_array, line, col, predict_next_ball, flag_first_appendarray);
	flag_first_appendarray = 1;
	cct_cls();
	change_typeface_cmd(line, col, '6');//改变cmd大小和字体
	cct_enable_mouse();//允许使用鼠标，放在设置命令行窗口大小后
	print_gird(line, col, '5', 0);
	for (int i = 0; i < line; i++)//根据此时内部数组的值在格子内画小球
		for (int j = 0; j < col; j++)
			if (game_array[i][j] != 0)
				print_ball(game_array[i][j], i, j, '5');
	//此位置需要放置鼠标等相关操作的函数，且构成死循环，只有右键才能退出循环
	while (1)
	{
		int flag_end = 0;
		flag_end = mouse_operate(line, col, &sta_line, &sta_col, &des_line, &des_col, game_array);
		if (flag_end)
			break;
		else
		{
			tmp = search_game_road(choice, game_array, back_path, line, col, sta_line, sta_col, des_line, des_col);
			if (tmp == 0)
			{
				cct_gotoxy(0, 2 * line + 3);
				cout << "错误 无法从[" << sta_line << sta_col << "]移动到" << des_line << des_col << endl;
				Sleep(1000);
				cct_showch(0, 2 * line + 3, ' ', 0, 7, 40);
			}
			else
			{   //移动数组，打印图形的移动过程，总计得分，添加三个球，打印添加后的数组
				move_ball_dynamic(line, sta_line, sta_col, des_line, des_col, back_path, game_array, choice);
				move_game_array(choice, game_array, sta_line, sta_col, des_line, des_col);
				tmp = check_ball_delete(game_array, line, col, &color_ball, del_locate);
				break;
			}
		}
	}
	cct_gotoxy(0, 2 * line + 1);
	input_end_continue();
}

void fun_7(char choice)
{
	//line代表行数，col代表列数，但game_array中第一个是行！！！第二个是列！！！x代表列，y代表行！！！对应关系
	int line = 0, col = 0, game_array[9][9] = { 0 }, predict_next_ball[12] = { 0 }, flag_first_appendarray = 0;
	char sta_line, sta_col, des_line, des_col;//设置用于彩球移动的起始坐标和目的坐标
	elem_queue back_path[100] = { 0,0 }, locate_del_ball[100] = { {0,0} };//用于彩球移动成功后路径坐标的记录
	int tmp = 0, tmp1 = 0, score = 0, num_toa_ball = 0, color_ball = 0, num_percl_ball[7] = { 0 }, num_del_ball[7] = { 0 };
	inputdata_linecol(&line, &col);
	append_game_array('7', game_array, line, col, predict_next_ball, flag_first_appendarray);
	flag_first_appendarray = 1;
	cct_cls();
	change_typeface_cmd(line, col, '7');//改变cmd大小和字体
	cct_enable_mouse();//允许使用鼠标，放在设置命令行窗口大小后
	cct_gotoxy(0, 1);
	print_gird(line, col, '5', 0);//打印彩球方框
	cct_gotoxy(40, 1);
	print_gird(1, 5, '4', 40);//打印得分方框
	cct_gotoxy(40, 5);
	print_gird(1, 3, '5', 40);//打印预测彩球方框
	cct_gotoxy(40, 9);
	print_gird(8, 12, '4', 40);//打印消除方框
	for (int i = 0; i < line; i++)//根据此时内部数组的值在格子内画小球
		for (int j = 0; j < col; j++)
			if (game_array[i][j] != 0)
				print_ball(game_array[i][j], i, j, '5');
	while (1)
	{
		int flag_end = 0;
		cct_showstr(42, 2, "得分: ", 15, 0, 1);
		cct_showint(48, 2, score, 15, 0, 1);
		for (int i = 0; i < 3; i++)
			print_ball(predict_next_ball[i], 6, 42 + 4 * i, '8');//在右框内打印下次三个小球的颜色

		for (int i = 0; i < 7; i++)
			num_percl_ball[i] = 0;//数量清空
		for (int i = 0; i < line; i++)//统计每种颜色的球的数量
			for (int j = 0; j < col; j++)
			{
				if (game_array[i][j])
					++num_percl_ball[game_array[i][j] - 1];
			}

		cct_gotoxy(42, 10);
		num_toa_ball = 0;
		for (int i = 0; i < 7; i++)
			num_toa_ball += num_percl_ball[i];
		cct_setcolor(15, 0);
		cout << "  :" << setfill('0') << setw(2) << line * col - num_toa_ball << "/(" << setfill(' ') << setw(5) << setiosflags(ios::fixed) << setprecision(2) << (line * col - num_toa_ball) * 100.0 / (line * col) << "%)  消除-" << tmp1;
		for (int i = 0; i < 7; i++)
		{
			print_ball(i + 1, 11 + i, 42, '8');
			cct_setcolor(15, 0);
			cout << ":" << setfill('0') << setw(2) << num_percl_ball[i] << "/(" << setfill(' ') << setw(5)
				<< setiosflags(ios::fixed) << setprecision(2) << num_percl_ball[i] * 100.0 / (line * col) << "%)  消除-" << num_del_ball[i];
		}
		flag_end = mouse_operate(line, col, &sta_line, &sta_col, &des_line, &des_col, game_array);
		if (flag_end)//按右键
			break;
		else
		{
			//移动数组，打印图形的移动过程，总计得分，添加三个球，打印添加后的数组
			tmp = search_game_road(choice, game_array, back_path, line, col, sta_line, sta_col, des_line, des_col);
			if (tmp == 0)
			{
				cct_gotoxy(0, 2 * line + 3);
				cout << "错误 无法从[" << sta_line << sta_col << "]移动到" << des_line << des_col << endl;
				Sleep(1000);
				cct_showch(0, 2 * line + 3, ' ', 0, 7, 40);
			}
			else
			{
				move_ball_dynamic(line, sta_line, sta_col, des_line, des_col, back_path, game_array, choice);
				move_game_array(choice, game_array, sta_line, sta_col, des_line, des_col);
				tmp = check_ball_delete(game_array, line, col, &color_ball, locate_del_ball);
				if (tmp >= 5)
				{
					score += (tmp - 1) * (tmp - 2);
					num_del_ball[color_ball - 1] += tmp;
					del_ball_dynamic(locate_del_ball, tmp);
				}
				if (tmp < 5)
				{
					tmp = append_game_array(choice, game_array, line, col, predict_next_ball, flag_first_appendarray);
					for (int i = 0; i < 3; i++)
						print_ball(predict_next_ball[i + 9], predict_next_ball[i + 3], predict_next_ball[i + 6], '5');
				}
				if (check_game_over(game_array, line, col) == 0)//如果此时数组已经满了
				{
					cct_gotoxy(0, 2 * line + 3);
					cct_setcolor();
					cout << endl << "GAME OVER!!!" << endl;
					break;
				}
				if (tmp == -1)
				{
					cct_gotoxy(0, 2 * line + 3);
					cct_setcolor();
					cout << endl << "GAME OVER!!!" << endl;
					break;
				}
				tmp = check_ball_delete(game_array, line, col, &color_ball, locate_del_ball);//添加三个球后，再次检查有无出现五个相连，出现则消去且不计入总得分
				if (tmp >= 5)
				{
					del_ball_dynamic(locate_del_ball, tmp);
					cct_gotoxy(0, 2 * line + 3);
					cct_setcolor();
					cout << "本次消去并非玩家自行所为，不计入总得分";
					Sleep(1000);
					cct_showch(0, 2 * line + 3, ' ', 0, 1, 40);
				}
			}
		}
	}
	cct_gotoxy(0, 2 * line + 1);
	input_end_continue();
}

//改变cmd窗口的大小和字体、字号
void change_typeface_cmd(int set_lines, int set_cols, char choice)
{
	cct_setcolor();
	if (choice == '4')
	{
		cct_setconsoleborder(35, set_lines + 6);
		cct_setfontsize("新宋体", 36);
		cout << "屏幕：" << set_lines + 6 << "行" << 35 << "列" << endl;
	}
	else if (choice == '5' || choice == '6')
	{
		cct_setconsoleborder(2 * set_cols + 21, 2 * set_lines + 5);
		cct_setfontsize("新宋体", 32);
		cout << "屏幕：" << 2 * set_lines + 5 << "行" << 2 * set_cols + 21 << "列";
		if (choice == '6')
			cout << "(在彩球上按右键退出)";
		cout << endl;
	}
	else if (choice == '7')
	{
		cct_setconsoleborder(70, 23);
		cct_setfontsize("新宋体", 24);
		cout << "屏幕：" << 23 << "行" << 70 << "列" << "(彩球方格内右键退出)" << endl;
	}
}

//画格子的函数，根据参数选择是否画分割线
void print_gird(int line, int col, char choice, int sta_col)
{
	int tmp_x = 1, tmp_y = 1, flag = 0;//flag=0，打印"║"，flag=1，打印"╠═"
	cct_getxy(tmp_x, tmp_y);
	cct_showstr(tmp_x, tmp_y, "╔═", 15, 0, 1);
	for (int i = 1; i < col; i++)//循环仅控制次数
	{
		cct_getxy(tmp_x, tmp_y);
		if (choice == '4')
			cct_showstr(tmp_x, tmp_y, "═", 15, 0, 1);
		else if (choice == '5')
			cct_showstr(tmp_x, tmp_y, "╦═", 15, 0, 1);//通过参数控制打印内容的不同
	}
	cct_getxy(tmp_x, tmp_y);
	if (choice == '4')
		cct_showstr(tmp_x, tmp_y, "╗", 15, 0, 1);
	else if (choice == '5')
		cct_showstr(tmp_x, tmp_y, "╗", 15, 0, 1);//打印第一横行

	if (choice == '4')
	{
		for (int i = 0; i < line; i++)
		{
			cct_showstr(sta_col, tmp_y + 1, "║", 15, 0, 1);
			cct_getxy(tmp_x, tmp_y);
			for (int j = 0; j < 2 * col; j++)
				cct_showch(tmp_x++, tmp_y, ' ', 15, 0, 1);//打印中间的空白部分
			cct_showstr(2 * col + 2 + sta_col, tmp_y, "║", 15, 0, 1);
		}
	}
	else if (choice == '5')
	{
		for (int i = 0; i < 2 * line - 1; i++)
		{
			if (flag == 0)
			{
				cct_showstr(sta_col, tmp_y + 1, "║  ", 15, 0, 1);
				cct_getxy(tmp_x, tmp_y);
				for (int j = 0; j < col - 1; j++) {
					cct_getxy(tmp_x, tmp_y);
					cct_showstr(tmp_x, tmp_y, "║  ", 15, 0, 1);
				}
				cct_showstr(4 * col + sta_col, tmp_y, "║", 15, 0, 1);
				flag = 1;
			}
			else
			{
				cct_showstr(sta_col, tmp_y + 1, "╠═", 15, 0, 1);
				cct_getxy(tmp_x, tmp_y);
				for (int j = 0; j < col - 1; j++) {
					cct_getxy(tmp_x, tmp_y);
					cct_showstr(tmp_x, tmp_y, "╬═", 15, 0, 1);
				}
				cct_showstr(4 * col + sta_col, tmp_y, "╣", 15, 0, 1);
				flag = 0;
			}
		}
	}//打印中间line行
	cct_getxy(tmp_x, tmp_y);
	cct_showstr(sta_col, tmp_y + 1, "╚═", 15, 0, 1);
	for (int i = 1; i < col; i++)
	{
		cct_getxy(tmp_x, tmp_y);
		if (choice == '4')
			cct_showstr(tmp_x, tmp_y, "═", 15, 0, 1);
		else if (choice == '5')
			cct_showstr(tmp_x, tmp_y, "╩═", 15, 0, 1);
	}
	cct_getxy(tmp_x, tmp_y);
	cct_showstr(tmp_x, tmp_y, "╝", 15, 0, 1);//打印最后一横行
	cct_setcolor();//恢复颜色
}

//在格子的指定位置打印一个球
void print_ball(int color, int des_line, int des_col, char choice)
{//画格子有一下几点：1.画出一个圆，控制好大小和前景色(white),2.将对应位置的格子的背景色更改为相应颜色
	if (color == 2)
		color += 7;
	if (choice == '4')
		cct_showstr(2 * des_col + 2, 2 + des_line, "○", color, 14, 1);//画圆
	else if (choice == '5')
		cct_showstr(4 * des_col + 2, 2 * des_line + 2, "○", color, 14, 1);
	else if (choice == '6')
		cct_showstr(4 * des_col + 2, 2 * des_line + 2, "◎", color, 14, 1);
	else if (choice == '7')
		cct_showstr(des_col, des_line, "◎", color, 14, 1);
	else if (choice == '8')
		cct_showstr(des_col, des_line, "○", color, 14, 1);
	cct_setcolor();//恢复颜色
}

/*鼠标操作函数：1.需要能感知鼠标的位置，并且要返回相应的值（作为彩球的起始坐标和终止坐标）
				 所以就要准确划分感知的区域，哪些区域返回的行列数是多少。
				2. 能有选中和退出。左键选中，选中后需要更改此位置的图形显示
				右键退出，退出时必须在指定的框内按键才有反馈，其余位置无效。
				细节：鼠标放置在合理区域外，不再感应其位置；
综上：鼠标操作函数的主要功能就是感知位置，控制退出条件，一旦选中，暂时结束鼠标函数，返回对应坐标
移动结束后，再次回到鼠标函数。但一旦鼠标函数按键为右键，则完全退出（通过鼠标函数返回值判断）*/

int mouse_operate(int line, int col, char* sta_line, char* sta_col, char* des_line, char* des_col, int a[9][9])
{
	int X = 0, Y = 0, ret, maction, keycode1, keycode2, loop = 1;
	int tmp_move = 0;
	elem_queue b[100] = { 0,0 };
	static int flag_ball = 0;//flag用来指示左键的的情况
	static int last_i = -1, last_j = -1;//记录上次左键点击的位置
	cct_enable_mouse();
	cct_setcursor(CURSOR_INVISIBLE);	//关闭光标
	while (1)
	{
		ret = cct_read_keyboard_and_mouse(X, Y, maction, keycode1, keycode2);
		if (ret == CCT_MOUSE_EVENT)
		{
			for (int i = 0; i < line; i++)
			{
				for (int j = 0; j < col; j++)
				{
					if (((X == (4 * j + 2)) || (X == (4 * j + 3))) && (Y == (2 * i + 2)))
					{
						cct_showch(0, 2 * line + 2, ' ', 0, 7, 30);
						cct_gotoxy(0, 2 * line + 2);
						cct_setcolor();
						cout << "[当前鼠标位置] " << char(i + 'A') << "行" << j + 1 << "列" << endl;
						switch (maction)//监测鼠标按键
						{
							case MOUSE_LEFT_BUTTON_CLICK:			//按下左键,操作分为选中和移动。
								if ((i != last_i) || (j != last_j))    //这次按下的坐标位置与上次不同
								{   //选中需满足，这次位置与上次暂存的选中的位置不同，且这个位置必须有球
									if (a[i][j] != 0)//打印"◎"的位置必须有彩球
									{
										print_ball(a[i][j], i, j, '6');//打印彩球的选中图形
										if (flag_ball == 1 && a[last_i][last_j] != 0)//上个位置此时不为空
											print_ball(a[last_i][last_j], last_i, last_j, '5');//恢复上个位置被选中的彩球
										last_i = i;
										last_j = j;//记录坐标
										flag_ball = 1;//说明已经选中过球了
									}
									else if (flag_ball)//点击的坐标不存在球，且之前已经选中球，可以移动，将参数传出
									{

										*sta_line = char(last_i + 'A');
										*sta_col = char(last_j + '1');
										*des_line = char(i + 'A');
										*des_col = char(j + '1');//将相关坐标记录
										tmp_move = search_game_road('1', a, b, line, col, *sta_line, *sta_col, *des_line, *des_col);
										if (tmp_move == 0)
											;
										else
										{
											last_i = i;
											last_j = j;
										}
										return 0;
									}
								}
								else if ((i == last_i) && (j == last_j))//两次按下的坐标相同
								{
									if (a[i][j] != 0 && flag_ball == 1)//按下的地方有彩球
									{
										print_ball(a[i][j], i, j, '5');
										flag_ball = 0;//在有彩球的位置连续按两次，取消选中！！！
									}
									else if (a[i][j] != 0 && flag_ball == 0)
									{
										print_ball(a[i][j], i, j, '6');
										flag_ball = 1;
									}
								}
								break;
							case MOUSE_RIGHT_BUTTON_CLICK:			//按下右键
								return 1;
						} //end of switch(maction)
					}//end of if
				}
			}//读返回的X/Y，对应好位置关系后再打印位置en
		}
		else if (ret == CCT_KEYBOARD_EVENT)
			continue;	//end of swicth(keycode1)
	}
	return 0;
}

/*函数功能：动态显示彩球的移动
  back_path中存的是从起始位置到终止位置的移动路径的坐标，但不能直接cct_show，
  因为不能瞬移，所以必须先判断移动方向，再决定上下左右一点点移动,而且每次移动只移动两个坐标间，外面再套一个循环*/
int move_ball_dynamic(int line, char sta_line, char sta_col, char des_line, char des_col, elem_queue back_path[100], int a[9][9], char choice)
{     //x是列！！！，y是行！！！
	 //i=0,向右；i=1,向下；i=2，向左；i=3，向上；
	int tmp_x = 0, tmp_y = 0;
	int path_length = 0;
	if (choice == '7')
	{
		cct_showch(0, 2 * line + 2, ' ', 0, 7, 30);
		cct_setcolor(0, 7);
		cct_gotoxy(0, 2 * line + 2);
		cout << "[提示]  " << "可以从[" << sta_line << sta_col << "]移动到[" << des_line << des_col << "]";
	}
	while ((back_path[path_length].x != (des_col - '1')) || (back_path[path_length].y != (des_line - 'A')))
	{
		for (int i = 0; i < 4; i++)
		{
			cct_setcolor();
			//先判定back_path的前一个到下一个位置应该朝哪个方向移动,且左右移动四次，上下移动两次
			if ((back_path[path_length + 1].x == back_path[path_length].x + dx[i])
				&& (back_path[path_length + 1].y == back_path[path_length].y + dy[i]))
			{
				tmp_x = 4 * back_path[path_length].x + 2;
				tmp_y = 2 * back_path[path_length].y + 2;//取当前的x,y坐标,注意这是cmd窗口的坐标
				if (i == 0)
				{
					for (int j = 0; j < 4; j++)
					{
						print_ball(a[sta_line - 'A'][sta_col - '1'], tmp_y, ++tmp_x, '7');
						cct_showch(tmp_x - 1, tmp_y, ' ', 15, 0, 1);//消除残留
						if (j == 3)
							cct_showstr(tmp_x - 2, tmp_y, "║", 15, 0, 1);
						Sleep(100);
					}
				}
				else if (i == 2)
				{
					for (int j = 0; j < 4; j++)
					{
						print_ball(a[sta_line - 'A'][sta_col - '1'], tmp_y, --tmp_x, '7');
						cct_showch(tmp_x + 2, tmp_y, ' ', 15, 0, 1);//消除残留
						if (j == 3)
							cct_showstr(tmp_x + 2, tmp_y, "║", 15, 0, 1);
						Sleep(100);
					}
				}
				else if (i == 1)
				{
					for (int j = 0; j < 2; j++)
					{
						print_ball(a[sta_line - 'A'][sta_col - '1'], ++tmp_y, tmp_x, '7');
						cct_showch(tmp_x, tmp_y - 1, ' ', 15, 0, 2);//消除残留
						if (j == 1)
							cct_showstr(tmp_x, tmp_y - 1, "═", 15, 0, 1);
						Sleep(100);
					}
				}
				else if (i == 3)
				{
					for (int j = 0; j < 2; j++)
					{
						print_ball(a[sta_line - 'A'][sta_col - '1'], --tmp_y, tmp_x, '7');
						cct_showch(tmp_x, tmp_y + 1, ' ', 15, 0, 2);//消除残留
						if (j == 1)
							cct_showstr(tmp_x, tmp_y + 1, "═", 15, 0, 1);
						Sleep(100);
					}
				}
			}
		}
		cct_setcolor();
		++path_length;
	}
	cct_showch(0, 20, ' ', 0, 7, 30);
	return 0;
}

//函数功能：实现cmd界面彩球的消除
void del_ball_dynamic(elem_queue delete_locate[100], int number)
{
	for (int i = 0; i < number; i++)
		cct_showstr(4 * delete_locate[i].x + 2, 2 * delete_locate[i].y + 2, "  ", 15, 0, 1);
	Sleep(100);
}

