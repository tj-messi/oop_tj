/*2150792 计科 牛禄阳*/
#include"../include/cmd_console_tools.h"
#include"../include/common.h"
#include"90-02-b1.h"

/*
   功能：根据游戏区域的行数和列数，打印出cmd展示形式的初始信息和边框
*/
void print_console_oper_infor()
{
	cct_setcolor();//重置颜色
	int cmdy = BASE_OPER_INFOR_Y;
	cct_showstr(CONSOLE_OPER_INFOR_X, cmdy++, "╔═════════════════════════════════╗", 11, 0, 1);
	for (int i = 0; i < 4; i++)
		cct_showstr(CONSOLE_OPER_INFOR_X, cmdy + i, " ", 11, 0, 68);
	for (int i = 0; i < 4; i++)
	{
		cct_showstr(CONSOLE_OPER_INFOR_X, cmdy, "║", 11, 0, 1);
		cct_showstr(CONSOLE_OPER_INFOR_X + FRAME_LENGTH, cmdy, game_oper_infor_90_02_b1[i], 11, 0, 1);
		cct_showstr(CONSOLE_OPER_INFOR_X + LENGTH_BASE_OPER_INFOR - FRAME_LENGTH, cmdy++, "║", 11, 0, 1);
	}
	cct_showstr(CONSOLE_OPER_INFOR_X, cmdy++, "╚═════════════════════════════════╝", 11, 0, 1);
	cct_setcolor();//重置颜色
}

/*
   功能：打印console版游戏的相关信息
*/
void print_console_game_infor(Gamearea gameboard)
{
	int cmdy = CONSOLE_GAME_INFOR_Y;
	cct_showstr(CONSOLE_OPER_INFOR_X, cmdy++, "╔═══════════════════════════╗",11, 0, 1);
	for (int i = 0; i < 6; i++)
		cct_showstr(CONSOLE_OPER_INFOR_X, cmdy + i, " ", 11, 0, 56);//连续打印3行
	for (int i = 1; i < 4; i++)
	{
		cct_showstr(CONSOLE_OPER_INFOR_X, cmdy, "║", 11, 0, 1);
		cct_showstr(CONSOLE_OPER_INFOR_X + FRAME_LENGTH, cmdy, game_exec_infor_90_02_b1[i], 11, 0, 1);
		switch (i)
		{
			case 1:
				cout << gameboard.gamesocre;
				break;
			case 2:
				cout << gameboard.dropspeed << "秒";
				break;
			case 3:
				cout << gameboard.elimlinenum;
				break;
		}
		cct_showstr(CONSOLE_OPER_INFOR_X + 58 - FRAME_LENGTH, cmdy++, "║", 11, 0, 1);
		cct_showstr(CONSOLE_OPER_INFOR_X, cmdy, "║", 11, 0, 1);
		cct_showstr(CONSOLE_OPER_INFOR_X + 58 - FRAME_LENGTH, cmdy++, "║", 11, 0, 1);
	}
	cct_showstr(CONSOLE_OPER_INFOR_X, cmdy++, "╚═══════════════════════════╝", 11, 0, 1);
}

/*
   功能：打印console版下一个要显示的数字
*/
void print_console_next_number_frame(Gamearea gameboard)
{
	cct_setcolor();//重置颜色
	int cmdy = BASE_EXEC_INFOR_Y;
	cct_showstr(CONSOLE_OPER_INFOR_X, cmdy++, "╔═══════════════╗", 15, 0, 1);
	for (int i = 0; i < 21; i++)
		cct_showstr(CONSOLE_OPER_INFOR_X, cmdy + i, " ", 15, 0, 32);
	cct_showstr(CONSOLE_OPER_INFOR_X + FRAME_LENGTH, cmdy, game_exec_infor_90_02_b1[0], 15, 0, 1);
	for (int i = 0; i < 21; i++)
	{
		cct_showstr(CONSOLE_OPER_INFOR_X, cmdy, "║", 15, 0, 1);
		cct_showstr(CONSOLE_OPER_INFOR_X + 34 - FRAME_LENGTH, cmdy++, "║", 15, 0, 1);
	}
	cct_showstr(CONSOLE_OPER_INFOR_X, cmdy++, "╚═══════════════╝", 15, 0, 1);
	cct_setcolor();//重置颜色
	print_erase_console_number(gameboard, 2);
	cct_setcolor();//重置颜色
}

/*
   功能：根据游戏区域的行数和列数，打印出cmd展示形式的初始信息和边框
*/
void print_console_frame(int gamerow, int gamecol)
{
	cct_cls();//清空页面
	cct_setcolor();//重置颜色
	cout << "当前数字俄罗斯方块游戏为" << gamerow << "行，" << gamecol << "列" << endl;
	//for (int i = 0; i < 16; i++)
	//	cout << "0123456789";
	cct_showstr(0, 1, "╔", 15, 0, 1);
	cct_showstr(6 * gamecol + FRAME_LENGTH, 1, "╗", 15, 0, 1);
	cct_showstr(0, 3 * gamerow + 2, "╚", 15, 0, 1);
	cct_showstr(6 * gamecol + FRAME_LENGTH, 3 * gamerow + 2, "╝", 15, 0, 1);
	/* 打印上和下边界 */
	for (int j = 0; j < gamecol; j++)
	{
		cct_showstr(6 * j + FRAME_LENGTH, 1, "═", 15, 0, 3);
		cct_showstr(6 * j + FRAME_LENGTH, 3 * gamerow + 2, "═", 15, 0, 3);
	}
	/* 打印左和右边界 */
	for (int i = 0; i < gamerow; i++)
	{
		for (int j = 0 ;j < 3; j++)
		{
			cct_showstr(0, 3 * i + 2 + j, "║", 15, 0, 1);
			cct_showstr(6 * gamecol + FRAME_LENGTH, 3 * i + 2 + j, "║", 15, 0, 1);
		}
	}
	/* 将所有游戏区域打印为空白 */
	for (int i = 2; i < 3 * gamerow + 2; i++)
		for (int j = 0; j < gamecol; j++)
			cct_showch(6 * j + FRAME_LENGTH, i, ' ', 15, 0, 6);
	cct_setcolor();//重置颜色
}

/*
   功能：根据所给的位置(currnettetromino中的位置结合cmd传来的参数)，打印或擦除出需要显示的数字
         choice==0为打印；choice==1为擦除,choice==2为提示信息中的数字打印
		 console界面中gameboard.gamex应该为2
		 数字0的底色不存在，需要特殊判断解决
*/
void print_erase_console_number(Gamearea gameboard, int choice)
{
	int temp_number = gameboard.currnetTetromino.number;
	if (choice == 2)
		temp_number = gameboard.nextTetromino.number;
	if (temp_number == 0)
		temp_number = 10;
	for (int i = -OFFSET_ROW; i <= OFFSET_ROW; i++)
	{
		for (int j = -OFFSET_COL; j <= OFFSET_COL; j++)
		{
			if (choice == 2)
			{
				if (gameboard.nextTetromino.shape[i + OFFSET_ROW][j + OFFSET_COL] >= 0)
				{
					cct_showstr(CONSOLE_OPER_INFOR_X + 14 + 6 * j, BASE_EXEC_INFOR_Y + 10 + 3 * i,
						"╔═╗", temp_number, 14, 1);
					cct_showstr(CONSOLE_OPER_INFOR_X + 14 + 6 * j, BASE_EXEC_INFOR_Y + 11 + 3 * i,
						"║★║", temp_number, 14, 1);
					cct_showstr(CONSOLE_OPER_INFOR_X + 14 + 6 * j, BASE_EXEC_INFOR_Y + 12 + 3 * i,
						"╚═╝", temp_number, 14, 1);
				}
				continue;
			}
			if(gameboard.currnetTetromino.shape[i + OFFSET_ROW][j + OFFSET_COL] >= 0)//当前位置存在数字
			{
				if (3 * (gameboard.currnetTetromino.row + i) + gameboard.gamey < 0)
					continue;
				else if (3 * (gameboard.currnetTetromino.row + i) + gameboard.gamey == 0)
					cct_showstr(6 * (gameboard.currnetTetromino.col + j) + gameboard.gamex,
						3 * (gameboard.currnetTetromino.row + i) + gameboard.gamey, "      ");
				else if (3 * (gameboard.currnetTetromino.row + i) + gameboard.gamey == 1)
					cct_showstr(6 * (gameboard.currnetTetromino.col + j) + gameboard.gamex,
						3 * (gameboard.currnetTetromino.row + i) + gameboard.gamey, "═══", 15, 0);
				if (choice == 0)
				{
					cct_showstr(6 * (gameboard.currnetTetromino.col + j) + gameboard.gamex,
						3 * (gameboard.currnetTetromino.row + i) + gameboard.gamey, "╔═╗",
						temp_number, 14, 1);
					cct_showstr(6 * (gameboard.currnetTetromino.col + j) + gameboard.gamex,
						3 * (gameboard.currnetTetromino.row + i) + gameboard.gamey + 1, "║★║",
						temp_number, 14, 1);
					cct_showstr(6 * (gameboard.currnetTetromino.col + j) + gameboard.gamex,
						3 * (gameboard.currnetTetromino.row + i) + gameboard.gamey + 2, "╚═╝",
						temp_number, 14, 1);
				}
				else if (choice == 1)//擦除
				{
					for (int t = 0; t < 3; t++)
						cct_showch(6 * (gameboard.currnetTetromino.col + j) + gameboard.gamex,
							3 * (gameboard.currnetTetromino.row + i) + t + gameboard.gamey, ' ', 15, 0, 6);
				}
			}
		}
	}
}

int fun5()
{
	Gamearea gameboard;
	input_gamearea(gameboard.gamerow, gameboard.gamecol);              //输入游戏区域行与列
	cct_cls();
	cct_setfontsize("新宋体", 16);
	cct_setconsoleborder(220, 85, 220, 200);                            //设置菜单窗口大小
	cct_setcursor(CURSOR_INVISIBLE);
	gameboard.gamey = FRAME_LENGTH + 2;                                //初始化游戏区域的cmd界面行列
	gameboard.gamex = FRAME_LENGTH;
	cct_setcolor();
	print_console_frame(gameboard.gamerow, gameboard.gamecol);
	cct_gotoxy(0, gameboard.gamerow * 3 + 3);                          //将光标移动到末尾处，为了满足input_end_continue的使用条件
	cct_setcolor();
	cct_setcursor(CURSOR_VISIBLE_NORMAL);
	input_end_continue();                                              //输入end结束本小文
	return 1;
}

int fun6()
{
	Gamearea gameboard;
	input_gamearea(gameboard.gamerow, gameboard.gamecol);              //输入游戏区域行与列
	cct_cls();
	cct_setfontsize("新宋体", 16);
	cct_setconsoleborder(220, 85, 220, 200);                            //设置菜单窗口大小
	cct_setcursor(CURSOR_INVISIBLE);
	gameboard.gamey = FRAME_LENGTH + 2;                                //初始化游戏区域的cmd界面行列
	gameboard.gamex = FRAME_LENGTH;
	print_console_frame(gameboard.gamerow, gameboard.gamecol);
	initial_tetromino(gameboard, 1);                                   //初始化currnetTetromino    
	initial_gamearray(gameboard);                                      //初始化gameboard中的其余成员
	print_erase_console_number(gameboard, 0);
	cct_setcolor();
	cct_gotoxy(0, gameboard.gamerow * 3 + 3);                          //将光标移动到末尾处，为了满足input_end_continue的使用条件
	cct_setcolor();
	cct_setcursor(CURSOR_VISIBLE_NORMAL);
	input_end_continue();                                              //输入end结束本小文
	return 1;
}

int fun7()
{
	Gamearea gameboard;
	input_gamearea(gameboard.gamerow, gameboard.gamecol);              //输入游戏区域行与列
	cct_cls();
	cct_setfontsize("新宋体", 16);
	cct_setconsoleborder(220, 85, 220, 200);                            //设置菜单窗口大小
	cct_setcursor(CURSOR_INVISIBLE);
	gameboard.gamey = FRAME_LENGTH;                                    //初始化游戏区域的cmd界面行列
	gameboard.gamex = FRAME_LENGTH;
	print_console_frame(gameboard.gamerow, gameboard.gamecol);
	initial_tetromino(gameboard, 0);                                   //初始化currnetTetromino    
	initial_gamearray(gameboard);                                      //初始化gameboard中的其余成员
	print_erase_console_number(gameboard, 0);
	print_console_oper_infor();
	print_console_next_number_frame(gameboard);
	execute_game_process(gameboard, 1);
	cct_setcolor();
	cct_setcursor(CURSOR_VISIBLE_NORMAL);
	cct_gotoxy(0, gameboard.gamerow * 3 + 3);                          //将光标移动到末尾处，为了满足input_end_continue的使用条件
	input_end_continue();                                              //输入end结束本小文
	return 1;
}

int fun8()
{
	Gamearea gameboard;
	input_gamearea(gameboard.gamerow, gameboard.gamecol);              //输入游戏区域行与列
	cct_cls();
	cct_setfontsize("新宋体", 16);
	cct_setconsoleborder(220, 85, 220, 200);                            //设置菜单窗口大小
	cct_setcursor(CURSOR_INVISIBLE);
	gameboard.gamey = FRAME_LENGTH;                                    //初始化游戏区域的cmd界面行列
	gameboard.gamex = FRAME_LENGTH;
	print_console_frame(gameboard.gamerow, gameboard.gamecol);
	initial_tetromino(gameboard, 0);                                   //初始化currnetTetromino    
	initial_gamearray(gameboard);                                      //初始化gameboard中的其余成员
	print_console_oper_infor();
	print_console_next_number_frame(gameboard);
	print_console_game_infor(gameboard);
	while (check_gameover(gameboard))
	{
		print_erase_console_number(gameboard, 0);
		cct_setcolor();
		if (execute_game_process(gameboard, 1) == 0)
			break;//此处break是因为按下了Q/q键，结束游戏
		if (gameboard.gameover == true)
			break;//此处break是因为游戏块无法再下落时，游戏块最高位置高于游戏区域
		cct_setcolor();
		process_cannot_move(gameboard, 1);
	}
	cct_setcursor(CURSOR_VISIBLE_NORMAL);
	cct_setcolor();
	cct_gotoxy(0, gameboard.gamerow * 3 + 3);                          //将光标移动到末尾处，为了满足input_end_continue的使用条件
	input_end_continue();                                              //输入end结束本小文
	return 1;
}
