/*2150792 计科 牛禄阳*/
#include"../include/cmd_console_tools.h"
#include"../include/common.h"
#include"90-01-b2.h"

//函数功能：实现行数和列数的输入   (需要被cmd和数组实现共用)
void inputdata_linecol(int* line, int* col)
{
	cout << "请输入行数(7-9)" << endl;
	while (1)
	{
		if (get_input_int(7, 9, *line) == 1)
			break;
	}
	cout << "请输入列数(7-9)" << endl;
	while (1)
	{
		if (get_input_int(7, 9, *col) == 1)
			break;
	}
	cin.ignore(65536, '\n');
}

//函数功能：按回车键继续   (需要被cmd和数组实现共用)
void huiche_conti()
{
	char huiche = '\0';
	while (1)
	{
		huiche = _getch();
		if (huiche == 13)
			break;
	}
}

//添加游戏内部数组的，从而实现每次添加三个球的函数，其根据输入决定第一次产生的球的数量以及后续的数量      (需要被cmd和数组实现共用)
int append_game_array(char choice, int a[9][9], int line, int col, int b[], int flag_first)
{
	srand((unsigned int)(time(0)));
	static int tmp_ball_num[9] = { 0 };
	int tmp_line = 0, tmp_col = 0, num_ball = 0;
	if (choice == '2')
		num_ball = line * col * 3 / 5;
	else if (choice == '3' || choice == '1' || choice == '7')
		num_ball = 5;
	if (flag_first == 0)//第一次时执行，则需要根据对应功能选择5个或者60%
	{
		for (int i = 0; i < num_ball;)
		{
			tmp_line = rand() % line;
			tmp_col = rand() % col;
			tmp_ball_num[0] = rand() % 7 + 1;
			if (a[tmp_line][tmp_col] != 0)
				continue;
			else
			{
				a[tmp_line][tmp_col] = tmp_ball_num[0];
				++i;
			}
		}
		for (int i = 0; i < 3; )
		{
			tmp_ball_num[i] = rand() % 7 + 1;
			b[i] = tmp_ball_num[i];
			++i;
		}
	}
	else
	{
		for (int i = 0; i < 3;)//后续添加球均为每次三个
		{
			if (check_game_over(a, line, col) == 0)//如果此时数组已经满了
				return -1;
			tmp_line = rand() % line;
			tmp_col = rand() % col;
			if (a[tmp_line][tmp_col] != 0)
				continue;//已存在数字，不能添加
			else
			{
				if (choice == '7')
				{
					b[i + 3] = tmp_line;
					b[i + 6] = tmp_col;
					b[i + 9] = tmp_ball_num[i];//将相关的值存入数组，从而传出(这个传出的位置是必须被立刻打印的位置)
				}
				a[tmp_line][tmp_col] = tmp_ball_num[i];//添加已在静态数组中的颜色
				tmp_ball_num[i] = rand() % 7 + 1;
				b[i] = tmp_ball_num[i];//把重新生成的颜色传出
				++i;
			}
		}
	}
	return 0;
}

//函数功能：对于给定的起始坐标和目的坐标，改变游戏内部数组的值       (需要被cmd和数组实现共用)
void move_game_array(char choice, int a[9][9], char sta_line, char sta_col, char des_line, char des_col)
{
	int tmp = 0;
	tmp = a[sta_line - 'A'][sta_col - '1'];
	a[sta_line - 'A'][sta_col - '1'] = 0;
	a[des_line - 'A'][des_col - '1'] = tmp;
}

//函数功能：BFS算法实现寻找从sta到des的路径，能找到，则调用get_path返回路径给数组back_path，函数返回1；找不到则返回0    (需要被cmd和数组实现共用)
int search_game_road(char choice, int a[9][9], elem_queue back_path[100], int line, int col, char sta_line, char sta_col, char des_line, char des_col)
{
	elem_queue first, perelem, search[100], back_elem[9][9];//第一个入队元素，每次入队元素，搜寻队列，回溯路径数组
	int flag[9][9] = { 0 };//用来标识有没有找过
	int beg = 0;//用结构体数组和普通变量模拟队列
	first.x = sta_col - '1';//x坐标，是列！！！在数组第二个位置
	first.y = sta_line - 'A';//y坐标，是行！！！应该在数组第一个位置
	perelem.x = -1;
	perelem.y = -1;
	flag[first.y][first.x] = 1;
	search[beg++] = first;
	while (beg != 0)
	{
		for (int i = 0; i < 4; i++)
		{
			int next_x = search[0].x + dx[i];
			int next_y = search[0].y + dy[i];
			if (!(next_x >= 0 && next_x < col && next_y >= 0 && next_y < line))
				continue;//判断下一元素位置的合法性
			if ((a[next_y][next_x] != 0) || flag[next_y][next_x] == 1)
				continue;
			perelem.x = next_x;
			perelem.y = next_y;
			flag[perelem.y][perelem.x] = 1;
			search[beg++] = perelem;
			back_elem[perelem.y][perelem.x].x = search[0].x;//记录送进队列的元素的父亲的列坐标
			back_elem[perelem.y][perelem.x].y = search[0].y;//记录送进队列的元素的父亲的行坐标
			if ((perelem.x == (des_col - '1')) && (perelem.y == (des_line - 'A')))
				break;
		}
		if ((perelem.x == (des_col - '1')) && (perelem.y == (des_line - 'A')))
			break;
		for (int i = 0; i < beg - 1; i++)
			search[i] = search[i + 1];
		search[beg - 1].x = 0;
		search[beg - 1].y = 0;
		--beg;
	}
	if (beg)
	{
		int length = 0;
		length = get_path(perelem.x, perelem.y, back_elem, sta_col, sta_line, back_path);
		back_path[0].x = first.x;
		back_path[0].y = first.y;
		back_path[length].x = -1;
		back_path[length].y = -1;
		return 1;
	}
	else
		return 0;
}

//函数功能：通过递归找到BFS算法的移动路径，把从起始点到目标点的坐标存在数组中  (一定注意x是列坐标，y是行坐标)  (需要被cmd和数组实现共用)  
int get_path(int x, int y, elem_queue a[9][9], char sta_col, char sta_line, elem_queue b[100])
{
	static int length = 1;
	if ((x == (sta_col - '1')) && (y == (sta_line - 'A')))
	{
		length = 1;
		return 0;
	}
	get_path(a[y][x].x, a[y][x].y, a, sta_col, sta_line, b);
	b[length].x = x;
	b[length].y = y;
	++length;
	return length;
}

//函数功能：对连续彩球的消除   (需要被cmd和数组实现共用)
int check_ball_delete(int a[9][9], int line, int col, int* color_ball, elem_queue delete_locate[100])
{
	int number = 0;
	int flag = 0;
	for (int i = 0; i < line; i++)
	{
		for (int j = 0; j <= col - 5; j++)
		{
			flag = a[i][j];
			int k = 0;
			for (k = j; k < col; k++)//这个条件是k<col，只要相同，可以一直找
			{
				if (flag == a[i][k] && flag != 0)
					continue;
				else
					break;
			}
			if ((k - j) >= 5)
			{
				int tmp = k;
				for (int t = 0; t < k - j; t++)
				{
					delete_locate[number].x = --tmp;
					delete_locate[number].y = i;
					number++;
				}
				break;//因为每行最多9个，找到5个相同可以直接break，找下一行
			}
		}
	}

	for (int i = 0; i < col; i++)
	{
		for (int j = 0; j <= line - 5; j++)
		{
			int k = 0;
			flag = a[j][i];
			for (k = j; k < line; k++)
			{
				if (flag == a[k][i] && flag != 0)
					continue;
				else
					break;
			}
			if ((k - j) >= 5)
			{
				int tmp = k;
				for (int t = 0; t < k - j; t++)
				{
					delete_locate[number].x = i;
					delete_locate[number].y = --tmp;
					number++;
				}
				break;
			}
		}
	}

	for (int i = 0; i <= col - 5; i++)//完成左上
	{
		int tmp1 = i;
		for (int j = 0; j <= ((col < line) ? col : line) - 5; j++)
		{
			int k = 0;
			flag = a[j][tmp1];
			int tmp2 = tmp1;
			tmp1++;
			for (k = j; k < line && tmp2 < col;)
			{
				if ((a[k][tmp2]) == flag && flag != 0)
				{
					++tmp2;
					++k;
				}
				else
					break;
			}
			if (k - j >= 5)
			{
				int tmp3 = k;
				for (int t = 0; t < k - j; t++)
				{
					delete_locate[number].x = --tmp2;
					delete_locate[number].y = --tmp3;
					number++;
				}
				break;
			}
		}
	}

	for (int i = 1; i <= line - 5; i++)
	{
		int tmp1 = i;//暂存i的值
		for (int j = 0; j <= ((col < line) ? col : line) - 5; j++, tmp1++)
		{
			int k = 0;
			flag = a[tmp1][j];
			int tmp2 = tmp1;
			for (k = j; k < line && tmp2 < col;)
			{
				if ((a[tmp2][k]) == flag && flag != 0)
				{
					++tmp2;
					++k;
				}
				else
					break;
			}
			if (k - j >= 5)
			{
				int tmp3 = k;
				for (int t = 0; t < k - j; t++)
				{
					delete_locate[number].x = --tmp3;
					delete_locate[number].y = --tmp2;
					number++;
				}
				break;
			}
		}
	}

	for (int i = 0; i <= line - 5; i++)//右下
	{
		int tmp1 = i;
		for (int j = col - 1; j >= col - 1 - i; j--)
		{
			int k = 0;
			flag = a[tmp1][j];
			int tmp2 = tmp1;
			tmp1++;
			for (k = j; k >= 0 && tmp2 < line;)
			{
				if ((a[tmp2][k]) == flag && flag != 0)
				{
					++tmp2;
					--k;
				}
				else
					break;
			}
			if (j - k >= 5)
			{
				int tmp3 = k;
				for (int t = 0; t < j - k; t++)
				{
					delete_locate[number].x = ++tmp3;
					delete_locate[number].y = --tmp2;
					number++;
				}
				break;
			}
		}
	}

	for (int i = col - 2; i >= 4; i--)
	{
		int tmp1 = i;
		for (int j = 0; j <= col - 1 - i; j++)
		{
			int k = 0;
			flag = a[j][tmp1];
			int tmp2 = tmp1;
			tmp1--;
			for (k = j; tmp2 >= 0 && k < line;)
			{
				if ((a[k][tmp2]) == flag && flag != 0)
				{
					--tmp2;
					++k;
				}
				else
					break;
			}
			if (k - j >= 5)
			{
				int tmp3 = k;
				for (int t = 0; t < k - j; t++)
				{
					delete_locate[number].x = --tmp3;
					delete_locate[number].y = ++tmp2;
					number++;
				}
				break;
			}
		}
	}

	*color_ball = a[delete_locate[0].y][delete_locate[0].x];
	for (int t = 0; t < number; t++)
		a[delete_locate[t].y][delete_locate[t].x] = 0;
	return number;
}

//函数功能：检查数组是否全满，全满游戏结束     (需要被cmd和数组实现共用)
int check_game_over(int a[9][9], int line, int col)
{
	int i = 0, j = 0;
	for (i = 0; i < line; i++)
	{
		for (j = 0; j < col; j++)
		{
			if (a[i][j] == 0)
				break;
		}
		if (j != col)
			return 1;//此时还没有结束
	}
	return 0;//数组已满
}


