/*2150792 计科 牛禄阳*/
#include"../include/cmd_console_tools.h"
#include"../include/common.h"
#include"90-01-b2.h"

//内部数组实现的三个函数
void fun_1(char choice)
{
	//line代表行数，col代表列数，但game_array中第一个是行！！！第二个是列！！！x代表列，y代表行！！！对应关系
	int line = 0, col = 0, game_array[9][9] = { 0 }, predict_next_ball[3] = { 0 }, flag_first_appendarray = 0;
	elem_queue back_path[100] = { 0,0 };//用于彩球移动成功后路径坐标的记录
	int tmp = 0, score = 0;
	inputdata_linecol(&line, &col);
	append_game_array(choice, game_array, line, col, predict_next_ball, flag_first_appendarray);
	flag_first_appendarray = 1;
	print_game_array(game_array, line, col, choice, predict_next_ball, back_path);
	input_end_continue();
}

void fun_2(char choice)
{
	int line = 0, col = 0, game_array[9][9] = { 0 }, predict_next_ball[3] = { 0 }, flag_first_appendarray = 0;
	char sta_line, sta_col, des_line, des_col;//设置用于彩球移动的起始坐标和目的坐标
	int tmp = 0, score = 0;
	elem_queue back_path[100] = { {0,0} };//用于彩球移动成功后路径坐标的记录

	inputdata_linecol(&line, &col);
	append_game_array(choice, game_array, line, col, predict_next_ball, flag_first_appendarray);
	flag_first_appendarray = 1;
	print_game_array(game_array, line, col, choice, predict_next_ball, back_path);
	inputdata_move(line, col, &sta_line, &sta_col, &des_line, &des_col, game_array);
	tmp = search_game_road(choice, game_array, back_path, line, col, sta_line, sta_col, des_line, des_col);
	if (tmp == 0)
		cout << "无法找到移动路径" << endl;
	else
	{
		move_game_array(choice, game_array, sta_line, sta_col, des_line, des_col);

		print_game_array(game_array, line, col, '4', predict_next_ball, back_path);//查找结果数组
		print_game_array(game_array, line, col, '5', predict_next_ball, back_path);//移动路径
	}
	input_end_continue();
}

void fun_3(char choice)
{
	int line = 0, col = 0, game_array[9][9] = { 0 }, predict_next_ball[3] = { 0 }, flag_first_appendarray = 0;
	char sta_line, sta_col, des_line, des_col;//设置用于彩球移动的起始坐标和目的坐标
	int tmp = 0, score = 0, tmp1 = 0, color_ball = 0;
	elem_queue back_path[100] = { 0,0 }, del_locate[100] = { 0,0 };//用于彩球移动成功后路径坐标的记录

	inputdata_linecol(&line, &col);
	append_game_array('3', game_array, line, col, predict_next_ball, flag_first_appendarray);
	flag_first_appendarray = 1;
	print_game_array(game_array, line, col, '2', predict_next_ball, back_path);
	while (1)
	{
		inputdata_move(line, col, &sta_line, &sta_col, &des_line, &des_col, game_array);
		tmp = search_game_road(choice, game_array, back_path, line, col, sta_line, sta_col, des_line, des_col);
		if (tmp == 0)
		{
			cout << "无法找到移动路径" << endl;
			print_game_array(game_array, line, col, '2', predict_next_ball, back_path);
		}
		else
		{   //移动数组，打印数组，总计得分，添加三个球，打印添加后的数组
			move_game_array(choice, game_array, sta_line, sta_col, des_line, des_col);//先移动数组
			print_game_array(game_array, line, col, '3', predict_next_ball, back_path);//打印移动对应彩球，但还没有添加三个球的数组(与demo不完全一致，个人认为此种更直观）
			tmp = check_ball_delete(game_array, line, col, &color_ball, del_locate);
			if (tmp >= 5)
				score += (tmp - 1) * (tmp - 2);
			cout << endl << "本次得分: " << ((tmp >= 5) ? (tmp - 1) * (tmp - 2) : 0) << "  总得分: " << score << endl;
			if (tmp < 5)
				tmp1 = append_game_array(choice, game_array, line, col, predict_next_ball, flag_first_appendarray);
			else
				tmp1 = 0;
			print_game_array(game_array, line, col, '2', predict_next_ball, back_path);
			tmp = check_ball_delete(game_array, line, col, &color_ball, del_locate);//添加三个球后，再次检查有无出现五个相连，出现则消去且不计入总得分
			if (tmp >= 5)
				cout << endl << "本次消去并非玩家自行所为，不计入总得分" << endl;
			if (check_game_over(game_array, line, col) == 0)//如果此时数组已经满了
			{
				cout << endl << "GAME OVER!!!" << endl;
				break;
			}
			if (tmp1 == -1)
			{
				cout << endl << "GAME OVER!!!" << endl;
				break;
			}
		}
	}
	input_end_continue();
}

//函数功能：打印游戏的内部数组    (仅被数组方式使用)
void print_game_array(int a[9][9], int line, int col, char choice, int b[3], elem_queue back_path[100])
{
	int a_1[9][9] = { 0 };
	if (choice == '1')
		cout << endl << "初始数组" << endl;
	else if (choice == '2')
		cout << endl << "当前数组" << endl;
	else if (choice == '3')
		cout << endl << "移动后的数组" << endl;
	else if (choice == '4')
		cout << endl << "查找结果数组" << endl;
	else if (choice == '5')
		cout << endl << "移动路径" << endl;
	cout << "  |";
	for (int i = 1; i <= col; i++)
		cout << "  " << i;
	cout << endl << "--+-";
	for (int i = 1; i <= col; i++)
		cout << "---";
	int tmp_back_path = 0;
	for (int i = 0; i < line; i++)
	{
		cout << endl << char(i + 'A') << " |";
		if (choice == '4')//对应功能2的查找结果数组
		{
			for (int j = 0; j < col; j++)
			{
				int tmp_x = 0, tmp_y = 0, flag = 0;
				cct_getxy(tmp_x, tmp_y);
				for (int t = 0; back_path[t].x != -1; t++)
				{
					if ((i == back_path[t].y) && (j == back_path[t].x))
					{
						cct_showch(tmp_x + 2, tmp_y, '*', 0, 7, 1);
						flag = 1;
						break;
					}
				}
				if (flag == 0)
					cct_showch(tmp_x + 2, tmp_y, '0', 0, 7, 1);
			}
		}
		else if (choice == '5')
		{
			for (int j = 0; j < col; j++)
			{
				int tmp_x = 0, tmp_y = 0, flag = 0, length = 0;
				cct_getxy(tmp_x, tmp_y);
				for (length = 0; back_path[length].x != -1;)
					++length;
				for (int t = 0; back_path[t].x != -1; t++)//遍历back__path
				{
					if ((i == back_path[t].y) && (j == back_path[t].x))
					{     //为了让颜色2的图形与其他颜色区分更明显，将其+7;
						cct_showch(tmp_x + 2, tmp_y, char(a[i][j] + '0'), (a[back_path[length - 1].y][back_path[length - 1].x] == 2 ?
							a[back_path[length - 1].y][back_path[length - 1].x] + 7 : a[back_path[length - 1].y][back_path[length - 1].x]), 7, 1);
						flag = 1;
						break;
					}
				}
				if (flag == 0)
					cct_showch(tmp_x + 2, tmp_y, char(a[i][j] + '0'), 0, 7, 1);
				cct_setcolor();
			}
		}
		else
		{
			for (int j = 0; j < col; j++)
			{
				int tmp_x = 0, tmp_y = 0;
				cct_getxy(tmp_x, tmp_y);
				cct_showch(tmp_x + 2, tmp_y, char(a[i][j] + '0'), (a[i][j] == 2 ? a[i][j] + 7 : a[i][j]), (a[i][j] == 0) ? 7 : 0, 1);
				cct_setcolor();
			}
		}
	}
	cout << endl;
	if (choice == '2')//根据参数选择是否预测下次产生的球的数值
		cout << endl << "下3个彩球的颜色分别是：" << b[0] << ' ' << b[1] << ' ' << b[2] << endl;
}

//函数功能：输入移动的球的起始和目的坐标     (仅用于数组方式的坐标输入)
int inputdata_move(int line, int col, char* sta_line, char* sta_col, char* des_line, char* des_col, int a[9][9])
{
	cout << "请以字母+数字形式[例：c2]输入要移动球的矩阵坐标：";
	char tmp[200] = { '\0' };
	int flag = 0;
	while (1)
	{
		flag = 0;
		gets_s(tmp);
		if ((tmp[0] >= 'A' && (tmp[0] < ('A' + line))) || (tmp[0] >= 'a' && (tmp[0] < ('a' + line))))
		{
			if ((tmp[1] >= '1' && tmp[1] <= '0' + col) && tmp[2] == '\0')
			{
				*sta_line = (tmp[0] < 'a') ? tmp[0] : char(tmp[0] - 32);
				*sta_col = tmp[1];

				if (a[*sta_line - 'A'][*sta_col - '1'] != 0)
				{
					cout << "输入为" << *sta_line << "行" << *sta_col << "列" << endl;
					break;
				}
				else
					flag = 1;
			}
		}
		if (flag == 0)
			cout << "输入错误，请重新输入";
		else
			cout << "起始位置为空，请重新输入";
		int tmp_x = 0, tmp_y = 0;
		cct_getxy(tmp_x, tmp_y);
		cct_showch(49, tmp_y - 1, ' ', COLOR_BLACK, COLOR_WHITE, 20);//擦除刚才的输入
		cct_gotoxy(49, tmp_y - 1);//光标回到相应位置
	}
	cout << "请以字母+数字形式[例：c2]输入要移动球的目的坐标：";
	while (1)
	{
		flag = 0;
		tmp[0] = '\0';
		tmp[1] = '\0';
		gets_s(tmp);
		if ((tmp[0] >= 'A' && (tmp[0] < ('A' + line))) || (tmp[0] >= 'a' && (tmp[0] < ('a' + line))))
		{
			if ((tmp[1] >= '1' && tmp[1] <= '0' + col) && tmp[2] == '\0')
			{
				*des_line = (tmp[0] < 'a') ? tmp[0] : char(tmp[0] - 32);
				*des_col = tmp[1];
				if (a[*des_line - 'A'][*des_col - '1'] == 0)
				{
					cout << "输入为" << *des_line << "行" << *des_col << "列" << endl;
					break;
				}
				else
					flag = 1;
			}
		}
		if (flag == 0)
			cout << "输入错误，请重新输入";
		else
			cout << "目标位置非空，请重新输入";
		int tmp_x = 0, tmp_y = 0;
		cct_getxy(tmp_x, tmp_y);
		cct_showch(49, tmp_y - 1, ' ', COLOR_BLACK, COLOR_WHITE, 20);//擦除刚才的输入
		cct_gotoxy(49, tmp_y - 1);//光标回到相应位置
		continue;
	}
	return 0;
}