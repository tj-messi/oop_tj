/*2150792 计科 牛禄阳*/
#include"../include/cmd_console_tools.h"
#include"../include/common.h"
#include"90-02-b1.h"
/*
捋一下游戏的总体下落逻辑：
设置下落点一定是正中心，并且是初始时就全部下落（有待改进的地方!!!）
1.初始化各种数据（只有第一次时进行）
2.打印即将下落的数字块，打印右侧框架中的提示信息
3.判断游戏是否结束
4.未结束则根据操作进行下落
5.每次操作结束后需要判断是否发生碰撞，没有发生继续4，发生后跳转到6
6.发生碰撞后的处理，
	（1）先将值记录到gamearray中
	（2）然后判断消除情况【这个函数中会更新gameboard中其他信息】，打印消除后的数组
	（3）更新下次下落数字块的信息
	（4）跳转到2继续执行
*/

/*
   功能：输入游戏区域大小
   参数：M代表行数，N代表列数，eg:21*26,即为21行，26列的游戏区域
*/
void input_gamearea(int& M,int& N)
{
	cout << "请输入行数(18-26)" << endl;
	while (1)
	{

		if (get_input_int(18, 26, M) == 1)
			break;
	}
	cout << "请输入列数(12-21),且是3的倍数" << endl;
	while (1)
	{
		if (get_input_int(12, 21, N, 3) == 1)
			break;
	}
	cin.ignore(65536, '\n');
}

/*
   功能：将矩阵围绕中心点逆时针旋转90度
         需要注意的是，现在temp_tetromino中得到旋转结果，再检测旋转后的合理性
		 合理返回1(并传出temp_tetromino数组)不改变currnetTetromino，不合理返回0
*/
int move_tetromino_ccw90degrees(Gamearea &gameboard, Tetromino &temp_tetromino)
{
    //绕中心点逆时针旋转的实现
    for (int i = 0; i < TETROMINO_ROW; ++i)
        for (int j = 0; j < TETROMINO_ROW; ++j)
			temp_tetromino.shape[TETROMINO_ROW - 1 - j][i] = gameboard.currnetTetromino.shape[i][j];
	if (check_gameaction_legality(gameboard, temp_tetromino) == 1)//能继续下落
		return 1;
	else                                                          //不能继续下落
		return 0;
}

/*
   功能：检测Tetromino的左移或右移。左移choice=0,右移choice=1。能移动返回1，否则返回0
		 如果能左移或右移，会改变currnetTetromino的row或col
*/
int move_tetromino_left_right(Gamearea &gameboard,int choice)
{
	Tetromino temp_tetromino = gameboard.currnetTetromino;   //定义暂存tetromino
	if (choice == 0)
		--temp_tetromino.col;
	else if (choice == 1)
		++temp_tetromino.col;                            //更新temp_tetromino中心点的位置
	if (check_gameaction_legality(gameboard, temp_tetromino) == 1)
	{
		gameboard.currnetTetromino.col = temp_tetromino.col; //更新currnetTetromino中心点的位置
		return 1;                                            //能继续下落
	}
	else
		return 0;                                            //不能继续下落
}  

/*
   功能：检测Tetromino的自由下落。能下落返回1，不能下落返回0吗，此时游戏应该结束返回-1
         注意：仅检测能否自由下落，不进行后续任何处理!!!
*/
int move_tetromino_normaldrop(Gamearea gameboard)
{
	Tetromino temp_tetromino = gameboard.currnetTetromino;        //定义暂存tetromino
	++temp_tetromino.row;                                         //更新temp_tetromino中心点的位置
	if (check_gameaction_legality(gameboard, temp_tetromino) == 1)//能继续下落
		return 1;
	else 
	{
		if (gameboard.currnetTetromino.row <= 1)                  //如果不能再下落时，方块的位置与大数组的第二行有重合
		{
			for (int j = -OFFSET_COL; j <= OFFSET_COL; j++)
			{
				if (gameboard.currnetTetromino.shape[0][j + OFFSET_COL] >= 0)//只需要判断方块的第一行
				{
					if (gameboard.gamearray[1][gameboard.currnetTetromino.col + j + OFFSET_GAMEARRAY] >= 0)
						return -1;
				}
			}
		}
		return 0;                                                //不能继续下落
	}
}

/*
   功能：实现Tetromino的快速下落
         一旦按下箭头，停止接受一切键盘输入，并缩短下落时间，完成下落后才跳出此函数
   参数：1.此时游戏区域 2.选择数组形式打印还是cmd界面打印，0为数组，1为cmd
*/
void move_tetromino_fastdrop(Gamearea &gameboard,int choice)
{
	double temp_dropspeed = gameboard.dropspeed;
	gameboard.dropspeed = 0.1;                                   //修改下落速度
	int ignore_getch = 0;
	while (true)
	{
		int tmp = move_tetromino_normaldrop(gameboard);
		if (tmp == 1)                     //此时的状态还能下落
		{
			while (_kbhit())
				ignore_getch = _getch(); // 清空键盘输入缓冲区
			Sleep(DWORD(1000 * gameboard.dropspeed));
			choice ? print_erase_console_number(gameboard, 1) : print_erase_base_number(gameboard, 1); //擦护旋转前的数字
			++gameboard.currnetTetromino.row;                    //更新currenttetromino状态
			choice ? print_erase_console_number(gameboard, 0) : print_erase_base_number(gameboard, 0); //打印旋转后的数字
		}
		else if (tmp == -1)
		{
			gameboard.gameover = true;
			break;
		}
		else
			break;
	}
	gameboard.dropspeed = temp_dropspeed;                       
}

/*
  功能：在生成新的块后(新的cur和next数字块都已经生成)，直接执行此函数，判断游戏是否结束
        需要注意的是，判断范围必须是数字块在游戏区域内的部分
*/
int check_gameover(Gamearea gameboard)
{
	for (int i = -OFFSET_ROW; i <= OFFSET_ROW; i++)
	{
		for (int j = -OFFSET_COL; j <= OFFSET_COL; j++)
		{
			if (gameboard.currnetTetromino.shape[i + OFFSET_ROW][j + OFFSET_COL] >= 0)//现在这个大于0
			{
				if (gameboard.gamearray[gameboard.currnetTetromino.row + i + OFFSET_GAMEARRAY][gameboard.currnetTetromino.col + j + OFFSET_GAMEARRAY] >= 0
					&& (gameboard.currnetTetromino.row + i + OFFSET_GAMEARRAY) >= OFFSET_GAMEARRAY)//必须在游戏面板内才会判断
					return 0;        //初始状态下shape和gamearray在同一位置的数字均大于等于0则游戏结束,并且是在游戏面板内
			}
		}
	}
	return 1;
}

/*
  功能：检测下一操作执行后的方块所在的位置是否合理，
		1.是否与发生碰撞（与其他块之间的碰撞，或者左移的空间不足等情况）返回0
		2.是否下落到底                                                  返回-1
		3.可能正常下落                                                  返回1
  参数：1.此时的游戏区域；2.执行完一次操作后的暂时存储数字块
*/
int check_gameaction_legality(Gamearea gameboard, Tetromino temp_tetromino)
{
	for (int i = -OFFSET_ROW; i <= OFFSET_ROW; i++)
	{
		for (int j = -OFFSET_COL; j <= OFFSET_COL; j++)
		{
			if (temp_tetromino.shape[i + OFFSET_ROW][j + OFFSET_COL] >= 0) 
			{
				//shape和gamearray在同一位置的数字均大于等于0则会发生碰撞
				if (gameboard.gamearray[temp_tetromino.row + i + OFFSET_GAMEARRAY][temp_tetromino.col + j + OFFSET_GAMEARRAY] >= 0
					&& (temp_tetromino.row + i + OFFSET_GAMEARRAY >= OFFSET_GAMEARRAY
						|| temp_tetromino.col + j + OFFSET_GAMEARRAY < OFFSET_GAMEARRAY
						|| temp_tetromino.col + j + OFFSET_GAMEARRAY > gameboard.gamecol + OFFSET_GAMEARRAY))
					return 0;                                   //多个条件限制检查区域的合法性，必须添加
			}
		}
	}
	return 1;
}

/*
   功能：控制一个数字块从开始下落到最终的过程
		 chioice==0为base形式，choice==1为console形式
   函数返回0代表输入Q/q，结束游戏；返回1代表仅此数字块的下落结束，返回-1也结束游戏
*/
int execute_game_process(Gamearea& gameboard,int choice)
{
	int cnt_drop = 0;
	while (1)
	{
		GameAction movecommand;
		movecommand = get_keyboard_in();
		if (movecommand == GameAction::ROTATE)
		{
			Tetromino temp_tetromino = gameboard.currnetTetromino;
			if (move_tetromino_ccw90degrees(gameboard, temp_tetromino) == 1)  //旋转成功
			{
				choice ? print_erase_console_number(gameboard, 1) : print_erase_base_number(gameboard, 1); //擦除原数字
				gameboard.currnetTetromino = temp_tetromino;		   //将旋转后的结果复制回原始矩阵
				choice ? print_erase_console_number(gameboard, 0) : print_erase_base_number(gameboard, 0); //打印旋转后的数字
			}
		}
		else if (movecommand == GameAction::MOVE_LEFT)
		{
			if (move_tetromino_left_right(gameboard, 0) == 1)                  //左移成功
			{
				++gameboard.currnetTetromino.col;
				choice ? print_erase_console_number(gameboard, 1) : print_erase_base_number(gameboard, 1); //擦除原数字
				--gameboard.currnetTetromino.col;
				choice ? print_erase_console_number(gameboard, 0) : print_erase_base_number(gameboard, 0); //打印旋转后的数字
			}
		}
		else if (movecommand == GameAction::MOVE_RIGHT)
		{
			if (move_tetromino_left_right(gameboard, 1) == 1)                  //右移成功
			{
				--gameboard.currnetTetromino.col;
				choice ? print_erase_console_number(gameboard, 1) : print_erase_base_number(gameboard, 1); //擦除原数字
				++gameboard.currnetTetromino.col;
				choice ? print_erase_console_number(gameboard, 0) : print_erase_base_number(gameboard, 0); //打印旋转后的数字
			}
		}
		else if (movecommand == GameAction::DROP_FAST)
		{
			move_tetromino_fastdrop(gameboard, choice);
			break;//要加入这句，因为快速下落后本数字块操作就结束了
		}
		else if (movecommand == GameAction::NONE || movecommand == GameAction::DROP_NORMAL)
		{
			int tmp = move_tetromino_normaldrop(gameboard);
			if (tmp == 1)
			{
				Sleep(DWORD(100 * gameboard.dropspeed));
				++cnt_drop;
				if (movecommand == GameAction::DROP_NORMAL || cnt_drop == 10)                                  //分为10次Sleep，方便_kbit函数读取
				{
					choice ? print_erase_console_number(gameboard, 1) : print_erase_base_number(gameboard, 1); //擦除原数字
					++gameboard.currnetTetromino.row;                //更新currenttetromino状态
					choice ? print_erase_console_number(gameboard, 0) : print_erase_base_number(gameboard, 0); //打印旋转后的数字
					cnt_drop = 0;
				}
			}
			else if (tmp == -1)
			{
				gameboard.gameover = true;
				return -1;
			}
			else
				break;//要加入这句，因为无法再下落后本数字块操作就结束了
		}
		else       //(movecommand == GameAction::EXIT)
			return 0;
	}
	return 1;
}

/*
   功能：无法再下落的后续处理函数
		（1）先将值记录到gamearray中
		（2）然后判断消除情况【这个函数中会更新gameboard中其check_gameaction_legality他信息】，打印消除后的数组
		 choice==0,用数组形式的擦除和打印；choice==1,用cmd界面形式的擦除和打印
		（3）更新下次下落数字块的信息
		（4）跳转到产生新的数字块继续执行
*/
void process_cannot_move(Gamearea& gameboard,int choice)
{
	/* 将currnetTetromino.shape记录到gameboard.gamearray中 */
	for (int i = -OFFSET_ROW; i <= OFFSET_ROW; i++)
	{
		for (int j = -OFFSET_COL; j <= OFFSET_COL; j++)
		{
			if (gameboard.gamearray[gameboard.currnetTetromino.row + i + OFFSET_GAMEARRAY]
				[gameboard.currnetTetromino.col + j + OFFSET_GAMEARRAY] < 0)//!!!不能覆盖之前已经存在于gamearray中的自然数
				gameboard.gamearray[gameboard.currnetTetromino.row + i + OFFSET_GAMEARRAY]
				[gameboard.currnetTetromino.col + j + OFFSET_GAMEARRAY] =
				gameboard.currnetTetromino.shape[i + OFFSET_ROW][j + OFFSET_COL];
		}
	}
	//cct_gotoxy(0, 70);
	//cct_setcolor();
	//for (int i = 0; i < gameboard.gamerow + OFFSET_GAMEARRAY; i++)
	//{
	//	for (int j = 0; j < gameboard.gamecol + OFFSET_GAMEARRAY; j++)
	//		cout << setw(2) << gameboard.gamearray[i][j];
	//	cout << endl;
	//}//显示此时gamearray数组的值，便于调试
	///* 判断消除情况，打印消除后的数组 */
	//system("pause");
	if (elim_gamearea(gameboard) == 1)
	{
		cct_setcolor();
		print_gamearray(gameboard, choice);
		cct_setcolor();
	}
	/* 更新下次下落数字块的信息 */
	gameboard.currnetTetromino.number = gameboard.nextTetromino.number;//更新number
	initial_tetromino(gameboard, 2);                                   //非首次且上方居中
	/* 更新游戏界面的游戏执行信息 */
	if (choice == 0)
		print_base_game_exec_infor(BASE_OPER_INFOR_X, BASE_EXEC_INFOR_Y, gameboard);//base形式
	else
	{
		print_console_next_number_frame(gameboard);
		print_console_game_infor(gameboard);
	}                                                                               //console形式 
}

/*
   功能：打印消除后的gamearray，注意是整个gamearray数组（可以优化的点，打印函数有冗余。
         因为没有写只打印一个数字或一个方块的最小打印函数，而是将shape数组作为最小打印单位）
         choice==0打印base形式,choice==1打印console形式
*/
void print_gamearray(Gamearea& gameboard, int choice)
{
	if (choice == 0)//base形式
	{
		for (int i = 0; i < gameboard.gamerow; i++)
		{
			for (int j = 0; j < gameboard.gamecol; j++)
			{
				if (gameboard.gamearray[i + OFFSET_GAMEARRAY][j + OFFSET_GAMEARRAY] >= 0)//如果是数字
				{
					cct_showint(gameboard.gamex + j, gameboard.gamey + i,
						gameboard.gamearray[i + OFFSET_GAMEARRAY][j + OFFSET_GAMEARRAY]);//打印
				}
				else
					cct_showch(gameboard.gamex + j, gameboard.gamey + i,' ');//擦除此处
			}
			cout << endl;
		}
	}
	else if (choice == 1)//console形式
	{
		for (int i = 0; i < gameboard.gamerow; i++)
		{
			for (int j = 0; j < gameboard.gamecol; j++)
			{
				int temp_number = gameboard.gamearray[i + OFFSET_GAMEARRAY][j + OFFSET_GAMEARRAY];
				if (temp_number == 0)
					temp_number = 10;
				if (gameboard.gamearray[i + OFFSET_GAMEARRAY][j + OFFSET_GAMEARRAY] >= 0)//如果是数字
				{
					cct_showstr(6 * j + gameboard.gamex, 3 * i + gameboard.gamey, "╔═╗",
						temp_number, 14, 1);
					cct_showstr(6 * j + gameboard.gamex, 3 * i + gameboard.gamey + 1, "║★║",
						temp_number, 14, 1);
					cct_showstr(6 * j + gameboard.gamex, 3 * i + gameboard.gamey + 2, "╚═╝",
						temp_number, 14, 1);
				}
				else
					for (int t = 0; t < 3; t++)
						cct_showch(6 * j + gameboard.gamex, 3 * i + t + gameboard.gamey, ' ', 15, 0, 6);
			}
			cout << endl;
		}
	}
}

/*
   功能：判断消除函数，每次tetromino操作结束后调用，用来检测能否进行消除
		 能消除则修改gameboard的值，并且返回1，不能消除则返回0
*/
int elim_gamearea(Gamearea& gameboard)
{
	int i = 0, j = 0, cnt_elimlinenum = 0;
	for (i = gameboard.gamerow - 1; i >= 0; i--)//从最下方开始检测可以优化游戏前期效率，但后期不会
	{
		for (j = 0; j < gameboard.gamecol; j++)
		{
			if (gameboard.gamearray[i + OFFSET_GAMEARRAY][j + OFFSET_GAMEARRAY] >= 0)
				continue;//存在数字则检测同一行的下一位置
			else
				break;  //不存在数字则此行不能消除，检测下一行
		}
		if (j == gameboard.gamecol)
		{
			++cnt_elimlinenum;                    
			//修改gamearray。应该是将所有消除行上方的gamearray下移一行
			for (int k = i; k > 0; k--)
			{
				for (int u = 0; u < gameboard.gamecol; u++)
				{
					gameboard.gamearray[k + OFFSET_GAMEARRAY][u + OFFSET_GAMEARRAY] =
						gameboard.gamearray[k + OFFSET_GAMEARRAY - 1][u + OFFSET_GAMEARRAY];
				}
			}
			//将游戏区域第一行清零
			for (int k = 0; k < gameboard.gamecol; k++)
				gameboard.gamearray[OFFSET_GAMEARRAY][k + OFFSET_GAMEARRAY] = -1;
		}
	}
	if (cnt_elimlinenum > 0)
	{
		inc_score_speed_elimnum(gameboard, cnt_elimlinenum);
		return 1;//修改gameboard的消除行数、得分、下落速度,返回1
	}
	else
		return 0;
}

/*
   功能：根据消除的行数增加得分，增加消除行数，并改变下落速度
*/
void inc_score_speed_elimnum(Gamearea& gameboard, int cnt_elimlinenum)
{
	/* 根据消除的行数增加得分 */
	switch (cnt_elimlinenum)                            
	{
		case 1:
			gameboard.gamesocre += 1;
			break;
		case 2:
			gameboard.gamesocre += 3;
			break;
		case 3:
			gameboard.gamesocre += 6;
			break;
		case 4:
			gameboard.gamesocre += 10;
			break;
		case 5:
			gameboard.gamesocre += 15;
			break;
	}
	/* 改变消除行数 */
	gameboard.elimlinenum += cnt_elimlinenum;                  //修改消除的行数
	/* 改变下落速度 */
	if (gameboard.gamesocre < 120)
		gameboard.dropspeed = gameboard.dropspeed - 0.1 * (gameboard.gamesocre / 15);
	else
		gameboard.dropspeed = 0.3;
}

/*
	 功能：用new_seed判断是否产生新的种子，返回0-9之间的随机数
	 说明：不同的种子会产生不同的随机数序列，但相同的种子将产生相同的随机数序列。
*/
int get_next_num(const bool new_seed, const unsigned int seed)
{
	if (new_seed)
		srand(seed);

	return rand() % 10;
}

/*
   功能：读入键盘键盘输入，仅上下左右箭头、空格、Q/q为合法输入
   参数：
   返回值：返回GameAction枚举类型中对应的值
*/
GameAction get_keyboard_in()
{
	bool isPaused = false;//判断是否
	while (true)
	{
		if (_kbhit())
		{
			unsigned char ch = _getch();  //unsigned，需要_getch两次，第一次为224;char，只需要_getch一次
			if ((ch == 'A' || ch == 'a')) //A/a转换暂停状态
				isPaused = !isPaused;
			else if ((ch == 'Q' || ch == 'q') && isPaused == false)//Q/q结束游戏，需要确认isPaused的状态
				return GameAction::EXIT;
			else if (ch == ' ' && isPaused == false)
				return GameAction::DROP_FAST;
			else if (ch == 224 && isPaused == false)
			{
				ch = _getch();//_getch()函数读入非字符键需要调用两次，第一次返回0或224
				if (ch == KB_ARROW_UP)
					return GameAction::ROTATE;
				else if (ch == KB_ARROW_DOWN)
					return GameAction::DROP_NORMAL;
				else if (ch == KB_ARROW_LEFT)
					return GameAction::MOVE_LEFT;
				else if (ch == KB_ARROW_RIGHT)
					return GameAction::MOVE_RIGHT;
			}
		}
		if (isPaused == true)                //处于暂停状态时，模拟进程工作
			for (int i = 0; i < 1000000; ++i);
		else                                 //处于工作状态，且没有按Q/q,上下左右箭头，即为自然下落
			return GameAction::NONE; 
	}
	return GameAction::NONE;
}

/*
  功能：初始化Tetromino的信息
  参数：choice选择初始化currnetTetromino的中心点位置及是否第一次调用，
        0代表在首次初始化且上方居中，1代表首次初始化中部居中
        2代表非首次且上方居中，3代表非首次且中部居中
*/
void initial_tetromino(Gamearea &gameboard,int choice)
{
	/*======初始化currnetTetromino的数字======*/
	if (choice == 0 || choice == 1)
		gameboard.currnetTetromino.number = get_next_num(true, (unsigned int)time(0));//得到当前数字
	gameboard.nextTetromino.number = get_next_num(false, (unsigned int)time(0));      //得到下一数字
	/*======初始化currnetTetromino 5X5 数组======*/
	for (int i = 0; i < TETROMINO_ROW; i++)
		for (int j = 0; j < TETROMINO_COL; j++)
			gameboard.currnetTetromino.shape[i][j] = TETROMINONUMBER[gameboard.currnetTetromino.number][i][j];
	/*======初始化nextTetromino 5X5 数组======*/
	for (int i = 0; i < TETROMINO_ROW; i++)
		for (int j = 0; j < TETROMINO_COL; j++)
			gameboard.nextTetromino.shape[i][j] = TETROMINONUMBER[gameboard.nextTetromino.number][i][j];
	/*======初始化currnetTetromino的中心点位置和rotate======*/
	//注意，是对于游戏区域的相对位置，而不是绝对位置，便于后续操作中遍历游戏区域数组和数字块数组
	if (choice == 1 || choice == 3)
		gameboard.currnetTetromino.row = gameboard.gamerow / 2 - OFFSET_GAMEARRAY;
	else
		gameboard.currnetTetromino.row = 0;                         //初始下落时不到顶符合逻辑          
	gameboard.currnetTetromino.col = gameboard.gamecol / 2;         //初始一定是三列的
}

/*
   功能：初始化gamearray数组
         注意！！！为了不对边界位置上旋转和左移操作是否越界进行判断，将gamearray的行和列均开大4个
		 因为，这开大的边界内的值必须全初始化为1，边界内的值全初始化为-1。
*/
void initial_gamearray(Gamearea& gameboard)
{
	for (int i = 0; i < MAX_GAMEAREA_ROW; i++)
		for (int j = 0; j < MAX_GAMEAREA_COL; j++)
			gameboard.gamearray[i][j] = 1;
	for (int i = 0; i < gameboard.gamerow; i++)
		for (int j = 0; j < gameboard.gamecol; j++)
			gameboard.gamearray[i + OFFSET_GAMEARRAY][j + OFFSET_GAMEARRAY] = -1;
	gameboard.dropspeed = 1.0;
	gameboard.elimlinenum = 0;
	gameboard.gameover = false;
	gameboard.gamesocre = 0;                                           //初始化gameboard
}
