/*2150792 �ƿ� ţ»��*/
#include"../include/cmd_console_tools.h"
#include"../include/common.h"
#include"90-02-b1.h"

/*
   ���ܣ���ӡ������ʽ�Ĳ�����Ϣ��ʾ
*/
void print_base_operation_infor(int cmdx,int cmdy)
{
	cct_showstr(BASE_OPER_INFOR_X, cmdy++, "�X�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�[");
	for (int i = 0; i < 4; i++)
	{
		cct_showstr(BASE_OPER_INFOR_X, cmdy, "�U");
		cct_showstr(BASE_OPER_INFOR_X + FRAME_LENGTH, cmdy, game_oper_infor_90_02_b1[i]);
		cct_showstr(BASE_OPER_INFOR_X + LENGTH_BASE_OPER_INFOR - FRAME_LENGTH, cmdy++, "�U");
	}
	cct_showstr(BASE_OPER_INFOR_X, cmdy++, "�^�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�a");
}

/*
   ���ܣ���ӡ������ʽ�ĳ�ʼ��Ϸִ����ʾ��Ϣ���
*/
void print_base_game_exec_infor(int cmdx,int cmdy, Gamearea gameboard)
{
	cmdy = BASE_EXEC_INFOR_Y;
	cct_showstr(BASE_OPER_INFOR_X, cmdy++, "�X�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�[");
	for (int i = 0; i < 4; i++)
	{
		cct_showstr(BASE_OPER_INFOR_X, cmdy, "�U");
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
				cout << gameboard.dropspeed<<"��";
				break;
			case 3:
				cout << gameboard.elimlinenum;
				break;
		}
		cct_showstr(BASE_OPER_INFOR_X + LENGTH_BASE_GAME_INFOR - FRAME_LENGTH, cmdy++, "�U");
		cct_showstr(BASE_OPER_INFOR_X, cmdy, "�U");
		cct_showstr(BASE_OPER_INFOR_X + LENGTH_BASE_GAME_INFOR - FRAME_LENGTH, cmdy++, "�U");
	}
	cct_showstr(BASE_OPER_INFOR_X, cmdy++, "�^�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�a");
}

/*
   ���ܣ�������Ϸ�������������������ӡ������չʾ��ʽ�ĳ�ʼ��Ϣ�ͱ߿�
*/
void print_base_frame(int gamerow, int gamecol, int &cmdx, int &cmdy)
{
	cout << "  ��ǰ���ֶ���˹������ϷΪ" << gamerow << "��" << gamecol << "��";
	cmdy++;
	cct_showstr(0, cmdy++, "�X�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�[");
	cct_showstr(0, cmdy++, "�U ���ֶ���˹������Ϸ����������ʽ �U");
	cct_showstr(0, cmdy++, "�^�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�a");
	cmdx = (LENGTH_BASE_TITLE - gamecol) / 2;
	//for (int i = cmdx; i < (LENGTH_BASE_TITLE + gamecol) / 2; i++)
	//	cct_showch(i, cmdy, char(i - cmdx + 'A'));                   //��֤����Ƿ���ȷ
	cct_gotoxy(0, cmdy+2);                                           //������������
	cmdy += 2;
	for (int i = cmdy; i < cmdy + gamerow; i++)
	{
		cct_showstr(cmdx - FRAME_LENGTH, i, "�U");
		cct_showstr(cmdx + gamecol, i, "�U");
	}
	cct_showstr(cmdx - FRAME_LENGTH, cmdy + gamerow, "�^");
	cct_showstr(cmdx + gamecol, cmdy + gamerow, "�a");
	cct_showstr(cmdx, cmdy + gamerow, "-", 0, 7, gamecol);
}

/*
   ���ܣ�����������λ��(currnettetromino�е�λ�ý��cmd�����Ĳ���)����ӡ���������Ҫ��ʾ������
         choice==0Ϊ��ӡ��choice==1Ϊ������
*/
void print_erase_base_number(Gamearea gameboard,int choice)
{
	for (int i = -OFFSET_ROW; i <= OFFSET_ROW; i++)
	{
		for (int j = -OFFSET_COL; j <= OFFSET_COL; j++)
		{
			if (gameboard.currnetTetromino.shape[i + OFFSET_ROW][j + OFFSET_COL] >= 0)//���������
			{
				if (gameboard.currnetTetromino.row + i < 0)
					continue;                                                        //��ʼʱû��¶���Ĳ��ֲ���ӡ
				if (choice == 0)
				{
					cct_showint(gameboard.gamex + gameboard.currnetTetromino.col + j,
						gameboard.gamey + gameboard.currnetTetromino.row + i,
						gameboard.currnetTetromino.number);//��ӡ
				}
				else if (choice == 1)
					cct_showch(gameboard.gamex + gameboard.currnetTetromino.col + j,
						gameboard.gamey + gameboard.currnetTetromino.row + i, ' ');//����
			}
		}
		cout << endl;
	}
}

int fun1()
{
	Gamearea gameboard;
	int cmdx = 0, cmdy = 0;                                            //cmd�����¹���ʵʱλ��
	cct_setcursor(CURSOR_INVISIBLE);
	input_gamearea(gameboard.gamerow, gameboard.gamecol);              //������Ϸ����������
	cct_cls();
	print_base_frame(gameboard.gamerow, gameboard.gamecol, cmdx, cmdy);//��ӡ������ⷽ��
	cct_gotoxy(0, cmdy + gameboard.gamerow);                           //������ƶ���ĩβ����Ϊ������input_end_continue��ʹ������
	input_end_continue();                                              //����end������С��
	return 0;
}

int fun2()
{
	Gamearea gameboard;
	int cmdx = 0, cmdy = 0;                                            //cmd�����¹���ʵʱλ��
	cct_setcursor(CURSOR_INVISIBLE);
	input_gamearea(gameboard.gamerow, gameboard.gamecol);              //������Ϸ����������
	cct_cls();
	print_base_frame(gameboard.gamerow, gameboard.gamecol, cmdx, cmdy);//��ӡ������ⷽ��
	gameboard.gamey = cmdy;                                            //��ʼ����Ϸ�����cmd��������
	gameboard.gamex = cmdx;
	initial_tetromino(gameboard, 1);                                   //��ʼ��currnetTetromino      
	print_erase_base_number(gameboard, 0);                             //��ӡ��ʼ��������
	cct_gotoxy(0, cmdy + gameboard.gamerow);                           //������ƶ���ĩβ����Ϊ������input_end_continue��ʹ������
	input_end_continue();                                              //����end������С��
	return 0;
}

int fun3()
{
	Gamearea gameboard;
	int cmdx = 0, cmdy = 0;                                            //cmd�����¹���ʵʱλ��
	cct_setcursor(CURSOR_INVISIBLE);
	input_gamearea(gameboard.gamerow, gameboard.gamecol);              //������Ϸ����������
	cct_cls();
	print_base_frame(gameboard.gamerow, gameboard.gamecol, cmdx, cmdy);//��ӡ������ⷽ��
	gameboard.gamey = cmdy;                                            //��ʼ����Ϸ�����cmd��������
	gameboard.gamex = cmdx;                                            //һ����ʼ����ʼ�ձ��ֲ���!!!
	print_base_operation_infor(BASE_OPER_INFOR_X, BASE_OPER_INFOR_Y);  //��ӡbase�Ĳ�����Ϣ
	initial_tetromino(gameboard, 0);                                   //��ʼ��currnetTetromino   
	initial_gamearray(gameboard);                                      //��ʼ��gameboard�е������Ա
	print_erase_base_number(gameboard, 0);                             //��ӡ��ʼ��������
	cct_setcolor();
	execute_game_process(gameboard, 0);
	cct_setcolor();
	cct_setcursor(CURSOR_VISIBLE_NORMAL);
	cct_gotoxy(0, cmdy + gameboard.gamerow);                           //������ƶ���ĩβ����Ϊ������input_end_continue��ʹ������
	input_end_continue();                                              //����end������С��
	return 0;
}

int fun4()
{
	Gamearea gameboard;
	int cmdx = 0, cmdy = 0, cnt = 0;                                   //cmd�����¹���ʵʱλ��
	cct_setcursor(CURSOR_INVISIBLE);
	input_gamearea(gameboard.gamerow, gameboard.gamecol);              //������Ϸ����������
	cct_cls();
	print_base_frame(gameboard.gamerow, gameboard.gamecol, cmdx, cmdy);//��ӡ������ⷽ��
	gameboard.gamey = cmdy;                                            //��ʼ����Ϸ�����cmd��������
	gameboard.gamex = cmdx;                                            //һ����ʼ����ʼ�ձ��ֲ���!!!
	print_base_operation_infor(BASE_OPER_INFOR_X, BASE_OPER_INFOR_Y);
	initial_tetromino(gameboard, 0);                                   //��ʼ��currnetTetromino   
	initial_gamearray(gameboard);                                      //��ʼ��gameboard�е������Ա
	print_base_game_exec_infor(BASE_OPER_INFOR_X, BASE_EXEC_INFOR_Y, gameboard);
	while (check_gameover(gameboard))
	{
		print_erase_base_number(gameboard, 0);
		cct_setcolor();
		if (execute_game_process(gameboard, 0) == 0)
			break;//�˴�break����Ϊ������Q/q����������Ϸ
		if (gameboard.gameover == true)
			break;//�˴�break����Ϊ��Ϸ���޷�������ʱ����Ϸ�����λ�ø�����Ϸ����
		cct_setcolor();
		process_cannot_move(gameboard, 0);
	}
	cct_setcursor(CURSOR_VISIBLE_NORMAL);
	cct_setcolor();
	cct_gotoxy(0, cmdy + gameboard.gamerow);                           //������ƶ���ĩβ����Ϊ������input_end_continue��ʹ������
	input_end_continue();                                              //����end������С��
	return 0;
}
