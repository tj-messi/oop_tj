/*2150792 �ƿ� ţ»��*/
#include"../include/cmd_console_tools.h"
#include"../include/common.h"
#include"90-02-b1.h"

/*
   ���ܣ�������Ϸ�������������������ӡ��cmdչʾ��ʽ�ĳ�ʼ��Ϣ�ͱ߿�
*/
void print_console_oper_infor()
{
	cct_setcolor();//������ɫ
	int cmdy = BASE_OPER_INFOR_Y;
	cct_showstr(CONSOLE_OPER_INFOR_X, cmdy++, "�X�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�[", 11, 0, 1);
	for (int i = 0; i < 4; i++)
		cct_showstr(CONSOLE_OPER_INFOR_X, cmdy + i, " ", 11, 0, 68);
	for (int i = 0; i < 4; i++)
	{
		cct_showstr(CONSOLE_OPER_INFOR_X, cmdy, "�U", 11, 0, 1);
		cct_showstr(CONSOLE_OPER_INFOR_X + FRAME_LENGTH, cmdy, game_oper_infor_90_02_b1[i], 11, 0, 1);
		cct_showstr(CONSOLE_OPER_INFOR_X + LENGTH_BASE_OPER_INFOR - FRAME_LENGTH, cmdy++, "�U", 11, 0, 1);
	}
	cct_showstr(CONSOLE_OPER_INFOR_X, cmdy++, "�^�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�a", 11, 0, 1);
	cct_setcolor();//������ɫ
}

/*
   ���ܣ���ӡconsole����Ϸ�������Ϣ
*/
void print_console_game_infor(Gamearea gameboard)
{
	int cmdy = CONSOLE_GAME_INFOR_Y;
	cct_showstr(CONSOLE_OPER_INFOR_X, cmdy++, "�X�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�[",11, 0, 1);
	for (int i = 0; i < 6; i++)
		cct_showstr(CONSOLE_OPER_INFOR_X, cmdy + i, " ", 11, 0, 56);//������ӡ3��
	for (int i = 1; i < 4; i++)
	{
		cct_showstr(CONSOLE_OPER_INFOR_X, cmdy, "�U", 11, 0, 1);
		cct_showstr(CONSOLE_OPER_INFOR_X + FRAME_LENGTH, cmdy, game_exec_infor_90_02_b1[i], 11, 0, 1);
		switch (i)
		{
			case 1:
				cout << gameboard.gamesocre;
				break;
			case 2:
				cout << gameboard.dropspeed << "��";
				break;
			case 3:
				cout << gameboard.elimlinenum;
				break;
		}
		cct_showstr(CONSOLE_OPER_INFOR_X + 58 - FRAME_LENGTH, cmdy++, "�U", 11, 0, 1);
		cct_showstr(CONSOLE_OPER_INFOR_X, cmdy, "�U", 11, 0, 1);
		cct_showstr(CONSOLE_OPER_INFOR_X + 58 - FRAME_LENGTH, cmdy++, "�U", 11, 0, 1);
	}
	cct_showstr(CONSOLE_OPER_INFOR_X, cmdy++, "�^�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�a", 11, 0, 1);
}

/*
   ���ܣ���ӡconsole����һ��Ҫ��ʾ������
*/
void print_console_next_number_frame(Gamearea gameboard)
{
	cct_setcolor();//������ɫ
	int cmdy = BASE_EXEC_INFOR_Y;
	cct_showstr(CONSOLE_OPER_INFOR_X, cmdy++, "�X�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�[", 15, 0, 1);
	for (int i = 0; i < 21; i++)
		cct_showstr(CONSOLE_OPER_INFOR_X, cmdy + i, " ", 15, 0, 32);
	cct_showstr(CONSOLE_OPER_INFOR_X + FRAME_LENGTH, cmdy, game_exec_infor_90_02_b1[0], 15, 0, 1);
	for (int i = 0; i < 21; i++)
	{
		cct_showstr(CONSOLE_OPER_INFOR_X, cmdy, "�U", 15, 0, 1);
		cct_showstr(CONSOLE_OPER_INFOR_X + 34 - FRAME_LENGTH, cmdy++, "�U", 15, 0, 1);
	}
	cct_showstr(CONSOLE_OPER_INFOR_X, cmdy++, "�^�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�a", 15, 0, 1);
	cct_setcolor();//������ɫ
	print_erase_console_number(gameboard, 2);
	cct_setcolor();//������ɫ
}

/*
   ���ܣ�������Ϸ�������������������ӡ��cmdչʾ��ʽ�ĳ�ʼ��Ϣ�ͱ߿�
*/
void print_console_frame(int gamerow, int gamecol)
{
	cct_cls();//���ҳ��
	cct_setcolor();//������ɫ
	cout << "��ǰ���ֶ���˹������ϷΪ" << gamerow << "�У�" << gamecol << "��" << endl;
	//for (int i = 0; i < 16; i++)
	//	cout << "0123456789";
	cct_showstr(0, 1, "�X", 15, 0, 1);
	cct_showstr(6 * gamecol + FRAME_LENGTH, 1, "�[", 15, 0, 1);
	cct_showstr(0, 3 * gamerow + 2, "�^", 15, 0, 1);
	cct_showstr(6 * gamecol + FRAME_LENGTH, 3 * gamerow + 2, "�a", 15, 0, 1);
	/* ��ӡ�Ϻ��±߽� */
	for (int j = 0; j < gamecol; j++)
	{
		cct_showstr(6 * j + FRAME_LENGTH, 1, "�T", 15, 0, 3);
		cct_showstr(6 * j + FRAME_LENGTH, 3 * gamerow + 2, "�T", 15, 0, 3);
	}
	/* ��ӡ����ұ߽� */
	for (int i = 0; i < gamerow; i++)
	{
		for (int j = 0 ;j < 3; j++)
		{
			cct_showstr(0, 3 * i + 2 + j, "�U", 15, 0, 1);
			cct_showstr(6 * gamecol + FRAME_LENGTH, 3 * i + 2 + j, "�U", 15, 0, 1);
		}
	}
	/* ��������Ϸ�����ӡΪ�հ� */
	for (int i = 2; i < 3 * gamerow + 2; i++)
		for (int j = 0; j < gamecol; j++)
			cct_showch(6 * j + FRAME_LENGTH, i, ' ', 15, 0, 6);
	cct_setcolor();//������ɫ
}

/*
   ���ܣ�����������λ��(currnettetromino�е�λ�ý��cmd�����Ĳ���)����ӡ���������Ҫ��ʾ������
         choice==0Ϊ��ӡ��choice==1Ϊ����,choice==2Ϊ��ʾ��Ϣ�е����ִ�ӡ
		 console������gameboard.gamexӦ��Ϊ2
		 ����0�ĵ�ɫ�����ڣ���Ҫ�����жϽ��
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
						"�X�T�[", temp_number, 14, 1);
					cct_showstr(CONSOLE_OPER_INFOR_X + 14 + 6 * j, BASE_EXEC_INFOR_Y + 11 + 3 * i,
						"�U��U", temp_number, 14, 1);
					cct_showstr(CONSOLE_OPER_INFOR_X + 14 + 6 * j, BASE_EXEC_INFOR_Y + 12 + 3 * i,
						"�^�T�a", temp_number, 14, 1);
				}
				continue;
			}
			if(gameboard.currnetTetromino.shape[i + OFFSET_ROW][j + OFFSET_COL] >= 0)//��ǰλ�ô�������
			{
				if (3 * (gameboard.currnetTetromino.row + i) + gameboard.gamey < 0)
					continue;
				else if (3 * (gameboard.currnetTetromino.row + i) + gameboard.gamey == 0)
					cct_showstr(6 * (gameboard.currnetTetromino.col + j) + gameboard.gamex,
						3 * (gameboard.currnetTetromino.row + i) + gameboard.gamey, "      ");
				else if (3 * (gameboard.currnetTetromino.row + i) + gameboard.gamey == 1)
					cct_showstr(6 * (gameboard.currnetTetromino.col + j) + gameboard.gamex,
						3 * (gameboard.currnetTetromino.row + i) + gameboard.gamey, "�T�T�T", 15, 0);
				if (choice == 0)
				{
					cct_showstr(6 * (gameboard.currnetTetromino.col + j) + gameboard.gamex,
						3 * (gameboard.currnetTetromino.row + i) + gameboard.gamey, "�X�T�[",
						temp_number, 14, 1);
					cct_showstr(6 * (gameboard.currnetTetromino.col + j) + gameboard.gamex,
						3 * (gameboard.currnetTetromino.row + i) + gameboard.gamey + 1, "�U��U",
						temp_number, 14, 1);
					cct_showstr(6 * (gameboard.currnetTetromino.col + j) + gameboard.gamex,
						3 * (gameboard.currnetTetromino.row + i) + gameboard.gamey + 2, "�^�T�a",
						temp_number, 14, 1);
				}
				else if (choice == 1)//����
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
	input_gamearea(gameboard.gamerow, gameboard.gamecol);              //������Ϸ����������
	cct_cls();
	cct_setfontsize("������", 16);
	cct_setconsoleborder(220, 85, 220, 200);                            //���ò˵����ڴ�С
	cct_setcursor(CURSOR_INVISIBLE);
	gameboard.gamey = FRAME_LENGTH + 2;                                //��ʼ����Ϸ�����cmd��������
	gameboard.gamex = FRAME_LENGTH;
	cct_setcolor();
	print_console_frame(gameboard.gamerow, gameboard.gamecol);
	cct_gotoxy(0, gameboard.gamerow * 3 + 3);                          //������ƶ���ĩβ����Ϊ������input_end_continue��ʹ������
	cct_setcolor();
	cct_setcursor(CURSOR_VISIBLE_NORMAL);
	input_end_continue();                                              //����end������С��
	return 1;
}

int fun6()
{
	Gamearea gameboard;
	input_gamearea(gameboard.gamerow, gameboard.gamecol);              //������Ϸ����������
	cct_cls();
	cct_setfontsize("������", 16);
	cct_setconsoleborder(220, 85, 220, 200);                            //���ò˵����ڴ�С
	cct_setcursor(CURSOR_INVISIBLE);
	gameboard.gamey = FRAME_LENGTH + 2;                                //��ʼ����Ϸ�����cmd��������
	gameboard.gamex = FRAME_LENGTH;
	print_console_frame(gameboard.gamerow, gameboard.gamecol);
	initial_tetromino(gameboard, 1);                                   //��ʼ��currnetTetromino    
	initial_gamearray(gameboard);                                      //��ʼ��gameboard�е������Ա
	print_erase_console_number(gameboard, 0);
	cct_setcolor();
	cct_gotoxy(0, gameboard.gamerow * 3 + 3);                          //������ƶ���ĩβ����Ϊ������input_end_continue��ʹ������
	cct_setcolor();
	cct_setcursor(CURSOR_VISIBLE_NORMAL);
	input_end_continue();                                              //����end������С��
	return 1;
}

int fun7()
{
	Gamearea gameboard;
	input_gamearea(gameboard.gamerow, gameboard.gamecol);              //������Ϸ����������
	cct_cls();
	cct_setfontsize("������", 16);
	cct_setconsoleborder(220, 85, 220, 200);                            //���ò˵����ڴ�С
	cct_setcursor(CURSOR_INVISIBLE);
	gameboard.gamey = FRAME_LENGTH;                                    //��ʼ����Ϸ�����cmd��������
	gameboard.gamex = FRAME_LENGTH;
	print_console_frame(gameboard.gamerow, gameboard.gamecol);
	initial_tetromino(gameboard, 0);                                   //��ʼ��currnetTetromino    
	initial_gamearray(gameboard);                                      //��ʼ��gameboard�е������Ա
	print_erase_console_number(gameboard, 0);
	print_console_oper_infor();
	print_console_next_number_frame(gameboard);
	execute_game_process(gameboard, 1);
	cct_setcolor();
	cct_setcursor(CURSOR_VISIBLE_NORMAL);
	cct_gotoxy(0, gameboard.gamerow * 3 + 3);                          //������ƶ���ĩβ����Ϊ������input_end_continue��ʹ������
	input_end_continue();                                              //����end������С��
	return 1;
}

int fun8()
{
	Gamearea gameboard;
	input_gamearea(gameboard.gamerow, gameboard.gamecol);              //������Ϸ����������
	cct_cls();
	cct_setfontsize("������", 16);
	cct_setconsoleborder(220, 85, 220, 200);                            //���ò˵����ڴ�С
	cct_setcursor(CURSOR_INVISIBLE);
	gameboard.gamey = FRAME_LENGTH;                                    //��ʼ����Ϸ�����cmd��������
	gameboard.gamex = FRAME_LENGTH;
	print_console_frame(gameboard.gamerow, gameboard.gamecol);
	initial_tetromino(gameboard, 0);                                   //��ʼ��currnetTetromino    
	initial_gamearray(gameboard);                                      //��ʼ��gameboard�е������Ա
	print_console_oper_infor();
	print_console_next_number_frame(gameboard);
	print_console_game_infor(gameboard);
	while (check_gameover(gameboard))
	{
		print_erase_console_number(gameboard, 0);
		cct_setcolor();
		if (execute_game_process(gameboard, 1) == 0)
			break;//�˴�break����Ϊ������Q/q����������Ϸ
		if (gameboard.gameover == true)
			break;//�˴�break����Ϊ��Ϸ���޷�������ʱ����Ϸ�����λ�ø�����Ϸ����
		cct_setcolor();
		process_cannot_move(gameboard, 1);
	}
	cct_setcursor(CURSOR_VISIBLE_NORMAL);
	cct_setcolor();
	cct_gotoxy(0, gameboard.gamerow * 3 + 3);                          //������ƶ���ĩβ����Ϊ������input_end_continue��ʹ������
	input_end_continue();                                              //����end������С��
	return 1;
}
