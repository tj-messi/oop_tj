/*2150792 �ƿ� ţ»��*/
#include"../include/cmd_console_tools.h"
#include"../include/common.h"
#include"90-02-b1.h"
/*
��һ����Ϸ�����������߼���
���������һ���������ģ������ǳ�ʼʱ��ȫ�����䣨�д��Ľ��ĵط�!!!��
1.��ʼ���������ݣ�ֻ�е�һ��ʱ���У�
2.��ӡ������������ֿ飬��ӡ�Ҳ����е���ʾ��Ϣ
3.�ж���Ϸ�Ƿ����
4.δ��������ݲ�����������
5.ÿ�β�����������Ҫ�ж��Ƿ�����ײ��û�з�������4����������ת��6
6.������ײ��Ĵ���
	��1���Ƚ�ֵ��¼��gamearray��
	��2��Ȼ���ж������������������л����gameboard��������Ϣ������ӡ�����������
	��3�������´��������ֿ����Ϣ
	��4����ת��2����ִ��
*/

/*
   ���ܣ�������Ϸ�����С
   ������M����������N����������eg:21*26,��Ϊ21�У�26�е���Ϸ����
*/
void input_gamearea(int& M,int& N)
{
	cout << "����������(18-26)" << endl;
	while (1)
	{

		if (get_input_int(18, 26, M) == 1)
			break;
	}
	cout << "����������(12-21),����3�ı���" << endl;
	while (1)
	{
		if (get_input_int(12, 21, N, 3) == 1)
			break;
	}
	cin.ignore(65536, '\n');
}

/*
   ���ܣ�������Χ�����ĵ���ʱ����ת90��
         ��Ҫע����ǣ�����temp_tetromino�еõ���ת������ټ����ת��ĺ�����
		 ������1(������temp_tetromino����)���ı�currnetTetromino����������0
*/
int move_tetromino_ccw90degrees(Gamearea &gameboard, Tetromino &temp_tetromino)
{
    //�����ĵ���ʱ����ת��ʵ��
    for (int i = 0; i < TETROMINO_ROW; ++i)
        for (int j = 0; j < TETROMINO_ROW; ++j)
			temp_tetromino.shape[TETROMINO_ROW - 1 - j][i] = gameboard.currnetTetromino.shape[i][j];
	if (check_gameaction_legality(gameboard, temp_tetromino) == 1)//�ܼ�������
		return 1;
	else                                                          //���ܼ�������
		return 0;
}

/*
   ���ܣ����Tetromino�����ƻ����ơ�����choice=0,����choice=1�����ƶ�����1�����򷵻�0
		 ��������ƻ����ƣ���ı�currnetTetromino��row��col
*/
int move_tetromino_left_right(Gamearea &gameboard,int choice)
{
	Tetromino temp_tetromino = gameboard.currnetTetromino;   //�����ݴ�tetromino
	if (choice == 0)
		--temp_tetromino.col;
	else if (choice == 1)
		++temp_tetromino.col;                            //����temp_tetromino���ĵ��λ��
	if (check_gameaction_legality(gameboard, temp_tetromino) == 1)
	{
		gameboard.currnetTetromino.col = temp_tetromino.col; //����currnetTetromino���ĵ��λ��
		return 1;                                            //�ܼ�������
	}
	else
		return 0;                                            //���ܼ�������
}  

/*
   ���ܣ����Tetromino���������䡣�����䷵��1���������䷵��0�𣬴�ʱ��ϷӦ�ý�������-1
         ע�⣺������ܷ��������䣬�����к����κδ���!!!
*/
int move_tetromino_normaldrop(Gamearea gameboard)
{
	Tetromino temp_tetromino = gameboard.currnetTetromino;        //�����ݴ�tetromino
	++temp_tetromino.row;                                         //����temp_tetromino���ĵ��λ��
	if (check_gameaction_legality(gameboard, temp_tetromino) == 1)//�ܼ�������
		return 1;
	else 
	{
		if (gameboard.currnetTetromino.row <= 1)                  //�������������ʱ�������λ���������ĵڶ������غ�
		{
			for (int j = -OFFSET_COL; j <= OFFSET_COL; j++)
			{
				if (gameboard.currnetTetromino.shape[0][j + OFFSET_COL] >= 0)//ֻ��Ҫ�жϷ���ĵ�һ��
				{
					if (gameboard.gamearray[1][gameboard.currnetTetromino.col + j + OFFSET_GAMEARRAY] >= 0)
						return -1;
				}
			}
		}
		return 0;                                                //���ܼ�������
	}
}

/*
   ���ܣ�ʵ��Tetromino�Ŀ�������
         һ�����¼�ͷ��ֹͣ����һ�м������룬����������ʱ�䣬��������������˺���
   ������1.��ʱ��Ϸ���� 2.ѡ��������ʽ��ӡ����cmd�����ӡ��0Ϊ���飬1Ϊcmd
*/
void move_tetromino_fastdrop(Gamearea &gameboard,int choice)
{
	double temp_dropspeed = gameboard.dropspeed;
	gameboard.dropspeed = 0.1;                                   //�޸������ٶ�
	int ignore_getch = 0;
	while (true)
	{
		int tmp = move_tetromino_normaldrop(gameboard);
		if (tmp == 1)                     //��ʱ��״̬��������
		{
			while (_kbhit())
				ignore_getch = _getch(); // ��ռ������뻺����
			Sleep(DWORD(1000 * gameboard.dropspeed));
			choice ? print_erase_console_number(gameboard, 1) : print_erase_base_number(gameboard, 1); //������תǰ������
			++gameboard.currnetTetromino.row;                    //����currenttetromino״̬
			choice ? print_erase_console_number(gameboard, 0) : print_erase_base_number(gameboard, 0); //��ӡ��ת�������
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
  ���ܣ��������µĿ��(�µ�cur��next���ֿ鶼�Ѿ�����)��ֱ��ִ�д˺������ж���Ϸ�Ƿ����
        ��Ҫע����ǣ��жϷ�Χ���������ֿ�����Ϸ�����ڵĲ���
*/
int check_gameover(Gamearea gameboard)
{
	for (int i = -OFFSET_ROW; i <= OFFSET_ROW; i++)
	{
		for (int j = -OFFSET_COL; j <= OFFSET_COL; j++)
		{
			if (gameboard.currnetTetromino.shape[i + OFFSET_ROW][j + OFFSET_COL] >= 0)//�����������0
			{
				if (gameboard.gamearray[gameboard.currnetTetromino.row + i + OFFSET_GAMEARRAY][gameboard.currnetTetromino.col + j + OFFSET_GAMEARRAY] >= 0
					&& (gameboard.currnetTetromino.row + i + OFFSET_GAMEARRAY) >= OFFSET_GAMEARRAY)//��������Ϸ����ڲŻ��ж�
					return 0;        //��ʼ״̬��shape��gamearray��ͬһλ�õ����־����ڵ���0����Ϸ����,����������Ϸ�����
			}
		}
	}
	return 1;
}

/*
  ���ܣ������һ����ִ�к�ķ������ڵ�λ���Ƿ����
		1.�Ƿ��뷢����ײ����������֮�����ײ���������ƵĿռ䲻������������0
		2.�Ƿ����䵽��                                                  ����-1
		3.������������                                                  ����1
  ������1.��ʱ����Ϸ����2.ִ����һ�β��������ʱ�洢���ֿ�
*/
int check_gameaction_legality(Gamearea gameboard, Tetromino temp_tetromino)
{
	for (int i = -OFFSET_ROW; i <= OFFSET_ROW; i++)
	{
		for (int j = -OFFSET_COL; j <= OFFSET_COL; j++)
		{
			if (temp_tetromino.shape[i + OFFSET_ROW][j + OFFSET_COL] >= 0) 
			{
				//shape��gamearray��ͬһλ�õ����־����ڵ���0��ᷢ����ײ
				if (gameboard.gamearray[temp_tetromino.row + i + OFFSET_GAMEARRAY][temp_tetromino.col + j + OFFSET_GAMEARRAY] >= 0
					&& (temp_tetromino.row + i + OFFSET_GAMEARRAY >= OFFSET_GAMEARRAY
						|| temp_tetromino.col + j + OFFSET_GAMEARRAY < OFFSET_GAMEARRAY
						|| temp_tetromino.col + j + OFFSET_GAMEARRAY > gameboard.gamecol + OFFSET_GAMEARRAY))
					return 0;                                   //����������Ƽ������ĺϷ��ԣ��������
			}
		}
	}
	return 1;
}

/*
   ���ܣ�����һ�����ֿ�ӿ�ʼ���䵽���յĹ���
		 chioice==0Ϊbase��ʽ��choice==1Ϊconsole��ʽ
   ��������0��������Q/q��������Ϸ������1����������ֿ���������������-1Ҳ������Ϸ
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
			if (move_tetromino_ccw90degrees(gameboard, temp_tetromino) == 1)  //��ת�ɹ�
			{
				choice ? print_erase_console_number(gameboard, 1) : print_erase_base_number(gameboard, 1); //����ԭ����
				gameboard.currnetTetromino = temp_tetromino;		   //����ת��Ľ�����ƻ�ԭʼ����
				choice ? print_erase_console_number(gameboard, 0) : print_erase_base_number(gameboard, 0); //��ӡ��ת�������
			}
		}
		else if (movecommand == GameAction::MOVE_LEFT)
		{
			if (move_tetromino_left_right(gameboard, 0) == 1)                  //���Ƴɹ�
			{
				++gameboard.currnetTetromino.col;
				choice ? print_erase_console_number(gameboard, 1) : print_erase_base_number(gameboard, 1); //����ԭ����
				--gameboard.currnetTetromino.col;
				choice ? print_erase_console_number(gameboard, 0) : print_erase_base_number(gameboard, 0); //��ӡ��ת�������
			}
		}
		else if (movecommand == GameAction::MOVE_RIGHT)
		{
			if (move_tetromino_left_right(gameboard, 1) == 1)                  //���Ƴɹ�
			{
				--gameboard.currnetTetromino.col;
				choice ? print_erase_console_number(gameboard, 1) : print_erase_base_number(gameboard, 1); //����ԭ����
				++gameboard.currnetTetromino.col;
				choice ? print_erase_console_number(gameboard, 0) : print_erase_base_number(gameboard, 0); //��ӡ��ת�������
			}
		}
		else if (movecommand == GameAction::DROP_FAST)
		{
			move_tetromino_fastdrop(gameboard, choice);
			break;//Ҫ������䣬��Ϊ������������ֿ�����ͽ�����
		}
		else if (movecommand == GameAction::NONE || movecommand == GameAction::DROP_NORMAL)
		{
			int tmp = move_tetromino_normaldrop(gameboard);
			if (tmp == 1)
			{
				Sleep(DWORD(100 * gameboard.dropspeed));
				++cnt_drop;
				if (movecommand == GameAction::DROP_NORMAL || cnt_drop == 10)                                  //��Ϊ10��Sleep������_kbit������ȡ
				{
					choice ? print_erase_console_number(gameboard, 1) : print_erase_base_number(gameboard, 1); //����ԭ����
					++gameboard.currnetTetromino.row;                //����currenttetromino״̬
					choice ? print_erase_console_number(gameboard, 0) : print_erase_base_number(gameboard, 0); //��ӡ��ת�������
					cnt_drop = 0;
				}
			}
			else if (tmp == -1)
			{
				gameboard.gameover = true;
				return -1;
			}
			else
				break;//Ҫ������䣬��Ϊ�޷�����������ֿ�����ͽ�����
		}
		else       //(movecommand == GameAction::EXIT)
			return 0;
	}
	return 1;
}

/*
   ���ܣ��޷�������ĺ���������
		��1���Ƚ�ֵ��¼��gamearray��
		��2��Ȼ���ж������������������л����gameboard����check_gameaction_legality����Ϣ������ӡ�����������
		 choice==0,��������ʽ�Ĳ����ʹ�ӡ��choice==1,��cmd������ʽ�Ĳ����ʹ�ӡ
		��3�������´��������ֿ����Ϣ
		��4����ת�������µ����ֿ����ִ��
*/
void process_cannot_move(Gamearea& gameboard,int choice)
{
	/* ��currnetTetromino.shape��¼��gameboard.gamearray�� */
	for (int i = -OFFSET_ROW; i <= OFFSET_ROW; i++)
	{
		for (int j = -OFFSET_COL; j <= OFFSET_COL; j++)
		{
			if (gameboard.gamearray[gameboard.currnetTetromino.row + i + OFFSET_GAMEARRAY]
				[gameboard.currnetTetromino.col + j + OFFSET_GAMEARRAY] < 0)//!!!���ܸ���֮ǰ�Ѿ�������gamearray�е���Ȼ��
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
	//}//��ʾ��ʱgamearray�����ֵ�����ڵ���
	///* �ж������������ӡ����������� */
	//system("pause");
	if (elim_gamearea(gameboard) == 1)
	{
		cct_setcolor();
		print_gamearray(gameboard, choice);
		cct_setcolor();
	}
	/* �����´��������ֿ����Ϣ */
	gameboard.currnetTetromino.number = gameboard.nextTetromino.number;//����number
	initial_tetromino(gameboard, 2);                                   //���״����Ϸ�����
	/* ������Ϸ�������Ϸִ����Ϣ */
	if (choice == 0)
		print_base_game_exec_infor(BASE_OPER_INFOR_X, BASE_EXEC_INFOR_Y, gameboard);//base��ʽ
	else
	{
		print_console_next_number_frame(gameboard);
		print_console_game_infor(gameboard);
	}                                                                               //console��ʽ 
}

/*
   ���ܣ���ӡ�������gamearray��ע��������gamearray���飨�����Ż��ĵ㣬��ӡ���������ࡣ
         ��Ϊû��дֻ��ӡһ�����ֻ�һ���������С��ӡ���������ǽ�shape������Ϊ��С��ӡ��λ��
         choice==0��ӡbase��ʽ,choice==1��ӡconsole��ʽ
*/
void print_gamearray(Gamearea& gameboard, int choice)
{
	if (choice == 0)//base��ʽ
	{
		for (int i = 0; i < gameboard.gamerow; i++)
		{
			for (int j = 0; j < gameboard.gamecol; j++)
			{
				if (gameboard.gamearray[i + OFFSET_GAMEARRAY][j + OFFSET_GAMEARRAY] >= 0)//���������
				{
					cct_showint(gameboard.gamex + j, gameboard.gamey + i,
						gameboard.gamearray[i + OFFSET_GAMEARRAY][j + OFFSET_GAMEARRAY]);//��ӡ
				}
				else
					cct_showch(gameboard.gamex + j, gameboard.gamey + i,' ');//�����˴�
			}
			cout << endl;
		}
	}
	else if (choice == 1)//console��ʽ
	{
		for (int i = 0; i < gameboard.gamerow; i++)
		{
			for (int j = 0; j < gameboard.gamecol; j++)
			{
				int temp_number = gameboard.gamearray[i + OFFSET_GAMEARRAY][j + OFFSET_GAMEARRAY];
				if (temp_number == 0)
					temp_number = 10;
				if (gameboard.gamearray[i + OFFSET_GAMEARRAY][j + OFFSET_GAMEARRAY] >= 0)//���������
				{
					cct_showstr(6 * j + gameboard.gamex, 3 * i + gameboard.gamey, "�X�T�[",
						temp_number, 14, 1);
					cct_showstr(6 * j + gameboard.gamex, 3 * i + gameboard.gamey + 1, "�U��U",
						temp_number, 14, 1);
					cct_showstr(6 * j + gameboard.gamex, 3 * i + gameboard.gamey + 2, "�^�T�a",
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
   ���ܣ��ж�����������ÿ��tetromino������������ã���������ܷ��������
		 ���������޸�gameboard��ֵ�����ҷ���1�����������򷵻�0
*/
int elim_gamearea(Gamearea& gameboard)
{
	int i = 0, j = 0, cnt_elimlinenum = 0;
	for (i = gameboard.gamerow - 1; i >= 0; i--)//�����·���ʼ�������Ż���Ϸǰ��Ч�ʣ������ڲ���
	{
		for (j = 0; j < gameboard.gamecol; j++)
		{
			if (gameboard.gamearray[i + OFFSET_GAMEARRAY][j + OFFSET_GAMEARRAY] >= 0)
				continue;//������������ͬһ�е���һλ��
			else
				break;  //��������������в��������������һ��
		}
		if (j == gameboard.gamecol)
		{
			++cnt_elimlinenum;                    
			//�޸�gamearray��Ӧ���ǽ������������Ϸ���gamearray����һ��
			for (int k = i; k > 0; k--)
			{
				for (int u = 0; u < gameboard.gamecol; u++)
				{
					gameboard.gamearray[k + OFFSET_GAMEARRAY][u + OFFSET_GAMEARRAY] =
						gameboard.gamearray[k + OFFSET_GAMEARRAY - 1][u + OFFSET_GAMEARRAY];
				}
			}
			//����Ϸ�����һ������
			for (int k = 0; k < gameboard.gamecol; k++)
				gameboard.gamearray[OFFSET_GAMEARRAY][k + OFFSET_GAMEARRAY] = -1;
		}
	}
	if (cnt_elimlinenum > 0)
	{
		inc_score_speed_elimnum(gameboard, cnt_elimlinenum);
		return 1;//�޸�gameboard�������������÷֡������ٶ�,����1
	}
	else
		return 0;
}

/*
   ���ܣ������������������ӵ÷֣������������������ı������ٶ�
*/
void inc_score_speed_elimnum(Gamearea& gameboard, int cnt_elimlinenum)
{
	/* �����������������ӵ÷� */
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
	/* �ı��������� */
	gameboard.elimlinenum += cnt_elimlinenum;                  //�޸�����������
	/* �ı������ٶ� */
	if (gameboard.gamesocre < 120)
		gameboard.dropspeed = gameboard.dropspeed - 0.1 * (gameboard.gamesocre / 15);
	else
		gameboard.dropspeed = 0.3;
}

/*
	 ���ܣ���new_seed�ж��Ƿ�����µ����ӣ�����0-9֮��������
	 ˵������ͬ�����ӻ������ͬ����������У�����ͬ�����ӽ�������ͬ����������С�
*/
int get_next_num(const bool new_seed, const unsigned int seed)
{
	if (new_seed)
		srand(seed);

	return rand() % 10;
}

/*
   ���ܣ�������̼������룬���������Ҽ�ͷ���ո�Q/qΪ�Ϸ�����
   ������
   ����ֵ������GameActionö�������ж�Ӧ��ֵ
*/
GameAction get_keyboard_in()
{
	bool isPaused = false;//�ж��Ƿ�
	while (true)
	{
		if (_kbhit())
		{
			unsigned char ch = _getch();  //unsigned����Ҫ_getch���Σ���һ��Ϊ224;char��ֻ��Ҫ_getchһ��
			if ((ch == 'A' || ch == 'a')) //A/aת����ͣ״̬
				isPaused = !isPaused;
			else if ((ch == 'Q' || ch == 'q') && isPaused == false)//Q/q������Ϸ����Ҫȷ��isPaused��״̬
				return GameAction::EXIT;
			else if (ch == ' ' && isPaused == false)
				return GameAction::DROP_FAST;
			else if (ch == 224 && isPaused == false)
			{
				ch = _getch();//_getch()����������ַ�����Ҫ�������Σ���һ�η���0��224
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
		if (isPaused == true)                //������ͣ״̬ʱ��ģ����̹���
			for (int i = 0; i < 1000000; ++i);
		else                                 //���ڹ���״̬����û�а�Q/q,�������Ҽ�ͷ����Ϊ��Ȼ����
			return GameAction::NONE; 
	}
	return GameAction::NONE;
}

/*
  ���ܣ���ʼ��Tetromino����Ϣ
  ������choiceѡ���ʼ��currnetTetromino�����ĵ�λ�ü��Ƿ��һ�ε��ã�
        0�������״γ�ʼ�����Ϸ����У�1�����״γ�ʼ���в�����
        2������״����Ϸ����У�3������״����в�����
*/
void initial_tetromino(Gamearea &gameboard,int choice)
{
	/*======��ʼ��currnetTetromino������======*/
	if (choice == 0 || choice == 1)
		gameboard.currnetTetromino.number = get_next_num(true, (unsigned int)time(0));//�õ���ǰ����
	gameboard.nextTetromino.number = get_next_num(false, (unsigned int)time(0));      //�õ���һ����
	/*======��ʼ��currnetTetromino 5X5 ����======*/
	for (int i = 0; i < TETROMINO_ROW; i++)
		for (int j = 0; j < TETROMINO_COL; j++)
			gameboard.currnetTetromino.shape[i][j] = TETROMINONUMBER[gameboard.currnetTetromino.number][i][j];
	/*======��ʼ��nextTetromino 5X5 ����======*/
	for (int i = 0; i < TETROMINO_ROW; i++)
		for (int j = 0; j < TETROMINO_COL; j++)
			gameboard.nextTetromino.shape[i][j] = TETROMINONUMBER[gameboard.nextTetromino.number][i][j];
	/*======��ʼ��currnetTetromino�����ĵ�λ�ú�rotate======*/
	//ע�⣬�Ƕ�����Ϸ��������λ�ã������Ǿ���λ�ã����ں��������б�����Ϸ������������ֿ�����
	if (choice == 1 || choice == 3)
		gameboard.currnetTetromino.row = gameboard.gamerow / 2 - OFFSET_GAMEARRAY;
	else
		gameboard.currnetTetromino.row = 0;                         //��ʼ����ʱ�����������߼�          
	gameboard.currnetTetromino.col = gameboard.gamecol / 2;         //��ʼһ�������е�
}

/*
   ���ܣ���ʼ��gamearray����
         ע�⣡����Ϊ�˲��Ա߽�λ������ת�����Ʋ����Ƿ�Խ������жϣ���gamearray���к��о�����4��
		 ��Ϊ���⿪��ı߽��ڵ�ֵ����ȫ��ʼ��Ϊ1���߽��ڵ�ֵȫ��ʼ��Ϊ-1��
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
	gameboard.gamesocre = 0;                                           //��ʼ��gameboard
}
