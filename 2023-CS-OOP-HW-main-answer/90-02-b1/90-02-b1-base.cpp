/*2150792 计科 牛禄阳*/
#include"../include/cmd_console_tools.h"
#include"../include/common.h"
#include"90-02-b1.h"

/*
   功能：打印数组形式的操作信息提示
*/
void print_base_operation_infor(int cmdx,int cmdy)
{
	cct_showstr(BASE_OPER_INFOR_X, cmdy++, "╔═════════════════════════════════╗");
	for (int i = 0; i < 4; i++)
	{
		cct_showstr(BASE_OPER_INFOR_X, cmdy, "║");
		cct_showstr(BASE_OPER_INFOR_X + FRAME_LENGTH, cmdy, game_oper_infor_90_02_b1[i]);
		cct_showstr(BASE_OPER_INFOR_X + LENGTH_BASE_OPER_INFOR - FRAME_LENGTH, cmdy++, "║");
	}
	cct_showstr(BASE_OPER_INFOR_X, cmdy++, "╚═════════════════════════════════╝");
}

/*
   功能：打印数组形式的初始游戏执行提示信息框架
*/
void print_base_game_exec_infor(int cmdx,int cmdy, Gamearea gameboard)
{
	cmdy = BASE_EXEC_INFOR_Y;
	cct_showstr(BASE_OPER_INFOR_X, cmdy++, "╔═══════════════════════════╗");
	for (int i = 0; i < 4; i++)
	{
		cct_showstr(BASE_OPER_INFOR_X, cmdy, "║");
		cct_showstr(BASE_OPER_INFOR_X + FRAME_LENGTH, cmdy, game_exec_infor_90_02_b1[i]);
		switch (i)
		{
			case 0:
				cout << gameboard.nextTetromino.number;
				break;
			case 1:
				cout << gameboard.gamesocre;
				break;
			case 2:
				cout << gameboard.dropspeed<<"秒";
				break;
			case 3:
				cout << gameboard.elimlinenum;
				break;
		}
		cct_showstr(BASE_OPER_INFOR_X + LENGTH_BASE_GAME_INFOR - FRAME_LENGTH, cmdy++, "║");
		cct_showstr(BASE_OPER_INFOR_X, cmdy, "║");
		cct_showstr(BASE_OPER_INFOR_X + LENGTH_BASE_GAME_INFOR - FRAME_LENGTH, cmdy++, "║");
	}
	cct_showstr(BASE_OPER_INFOR_X, cmdy++, "╚═══════════════════════════╝");
}

/*
   功能：根据游戏区域的行数和列数，打印出数组展示形式的初始信息和边框
*/
void print_base_frame(int gamerow, int gamecol, int &cmdx, int &cmdy)
{
	cout << "  当前数字俄罗斯方块游戏为" << gamerow << "行" << gamecol << "列";
	cmdy++;
	cct_showstr(0, cmdy++, "╔════════════════╗");
	cct_showstr(0, cmdy++, "║ 数字俄罗斯方块游戏——数组形式 ║");
	cct_showstr(0, cmdy++, "╚════════════════╝");
	cmdx = (LENGTH_BASE_TITLE - gamecol) / 2;
	//for (int i = cmdx; i < (LENGTH_BASE_TITLE + gamecol) / 2; i++)
	//	cct_showch(i, cmdy, char(i - cmdx + 'A'));                   //验证间距是否正确
	cct_gotoxy(0, cmdy+2);                                           //留出两个空行
	cmdy += 2;
	for (int i = cmdy; i < cmdy + gamerow; i++)
	{
		cct_showstr(cmdx - FRAME_LENGTH, i, "║");
		cct_showstr(cmdx + gamecol, i, "║");
	}
	cct_showstr(cmdx - FRAME_LENGTH, cmdy + gamerow, "╚");
	cct_showstr(cmdx + gamecol, cmdy + gamerow, "╝");
	cct_showstr(cmdx, cmdy + gamerow, "-", 0, 7, gamecol);
}

/*
   功能：根据所给的位置(currnettetromino中的位置结合cmd传来的参数)，打印或擦除出需要显示的数字
         choice==0为打印；choice==1为擦除。
*/
void print_erase_base_number(Gamearea gameboard,int choice)
{
	for (int i = -OFFSET_ROW; i <= OFFSET_ROW; i++)
	{
		for (int j = -OFFSET_COL; j <= OFFSET_COL; j++)
		{
			if (gameboard.currnetTetromino.shape[i + OFFSET_ROW][j + OFFSET_COL] >= 0)//如果是数字
			{
				if (gameboard.currnetTetromino.row + i < 0)
					continue;                                                        //初始时没有露出的部分不打印
				if (choice == 0)
				{
					cct_showint(gameboard.gamex + gameboard.currnetTetromino.col + j,
						gameboard.gamey + gameboard.currnetTetromino.row + i,
						gameboard.currnetTetromino.number);//打印
				}
				else if (choice == 1)
					cct_showch(gameboard.gamex + gameboard.currnetTetromino.col + j,
						gameboard.gamey + gameboard.currnetTetromino.row + i, ' ');//擦除
			}
		}
		cout << endl;
	}
}

int fun1()
{
	Gamearea gameboard;
	int cmdx = 0, cmdy = 0;                                            //cmd界面下光标的实时位置
	cct_setcursor(CURSOR_INVISIBLE);
	input_gamearea(gameboard.gamerow, gameboard.gamecol);              //输入游戏区域行与列
	cct_cls();
	print_base_frame(gameboard.gamerow, gameboard.gamecol, cmdx, cmdy);//打印标题和外方框
	cct_gotoxy(0, cmdy + gameboard.gamerow);                           //将光标移动到末尾处，为了满足input_end_continue的使用条件
	input_end_continue();                                              //输入end结束本小文
	return 0;
}

int fun2()
{
	Gamearea gameboard;
	int cmdx = 0, cmdy = 0;                                            //cmd界面下光标的实时位置
	cct_setcursor(CURSOR_INVISIBLE);
	input_gamearea(gameboard.gamerow, gameboard.gamecol);              //输入游戏区域行与列
	cct_cls();
	print_base_frame(gameboard.gamerow, gameboard.gamecol, cmdx, cmdy);//打印标题和外方框
	gameboard.gamey = cmdy;                                            //初始化游戏区域的cmd界面行列
	gameboard.gamex = cmdx;
	initial_tetromino(gameboard, 1);                                   //初始化currnetTetromino      
	print_erase_base_number(gameboard, 0);                             //打印初始下落数字
	cct_gotoxy(0, cmdy + gameboard.gamerow);                           //将光标移动到末尾处，为了满足input_end_continue的使用条件
	input_end_continue();                                              //输入end结束本小文
	return 0;
}

int fun3()
{
	Gamearea gameboard;
	int cmdx = 0, cmdy = 0;                                            //cmd界面下光标的实时位置
	cct_setcursor(CURSOR_INVISIBLE);
	input_gamearea(gameboard.gamerow, gameboard.gamecol);              //输入游戏区域行与列
	cct_cls();
	print_base_frame(gameboard.gamerow, gameboard.gamecol, cmdx, cmdy);//打印标题和外方框
	gameboard.gamey = cmdy;                                            //初始化游戏区域的cmd界面行列
	gameboard.gamex = cmdx;                                            //一经初始化便始终保持不变!!!
	print_base_operation_infor(BASE_OPER_INFOR_X, BASE_OPER_INFOR_Y);  //打印base的操作信息
	initial_tetromino(gameboard, 0);                                   //初始化currnetTetromino   
	initial_gamearray(gameboard);                                      //初始化gameboard中的其余成员
	print_erase_base_number(gameboard, 0);                             //打印初始下落数字
	cct_setcolor();
	execute_game_process(gameboard, 0);
	cct_setcolor();
	cct_setcursor(CURSOR_VISIBLE_NORMAL);
	cct_gotoxy(0, cmdy + gameboard.gamerow);                           //将光标移动到末尾处，为了满足input_end_continue的使用条件
	input_end_continue();                                              //输入end结束本小文
	return 0;
}

int fun4()
{
	Gamearea gameboard;
	int cmdx = 0, cmdy = 0, cnt = 0;                                   //cmd界面下光标的实时位置
	cct_setcursor(CURSOR_INVISIBLE);
	input_gamearea(gameboard.gamerow, gameboard.gamecol);              //输入游戏区域行与列
	cct_cls();
	print_base_frame(gameboard.gamerow, gameboard.gamecol, cmdx, cmdy);//打印标题和外方框
	gameboard.gamey = cmdy;                                            //初始化游戏区域的cmd界面行列
	gameboard.gamex = cmdx;                                            //一经初始化便始终保持不变!!!
	print_base_operation_infor(BASE_OPER_INFOR_X, BASE_OPER_INFOR_Y);
	initial_tetromino(gameboard, 0);                                   //初始化currnetTetromino   
	initial_gamearray(gameboard);                                      //初始化gameboard中的其余成员
	print_base_game_exec_infor(BASE_OPER_INFOR_X, BASE_EXEC_INFOR_Y, gameboard);
	while (check_gameover(gameboard))
	{
		print_erase_base_number(gameboard, 0);
		cct_setcolor();
		if (execute_game_process(gameboard, 0) == 0)
			break;//此处break是因为按下了Q/q键，结束游戏
		if (gameboard.gameover == true)
			break;//此处break是因为游戏块无法再下落时，游戏块最高位置高于游戏区域
		cct_setcolor();
		process_cannot_move(gameboard, 0);
	}
	cct_setcursor(CURSOR_VISIBLE_NORMAL);
	cct_setcolor();
	cct_gotoxy(0, cmdy + gameboard.gamerow);                           //将光标移动到末尾处，为了满足input_end_continue的使用条件
	input_end_continue();                                              //输入end结束本小文
	return 0;
}
