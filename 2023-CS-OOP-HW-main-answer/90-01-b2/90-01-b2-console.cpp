/*2150792 �ƿ� ţ»��*/
#include"../include/cmd_console_tools.h"
#include"../include/common.h"
#include"90-01-b2.h"

//�����жϣ�fun_7,��̬ȫ��
//cmd���������ʵ�ֵĺ���
void fun_4(char choice)
{
	//line����������col������������game_array�е�һ�����У������ڶ������У�����x�����У�y�����У�������Ӧ��ϵ
	int line = 0, col = 0, game_array[9][9] = { 0 }, predict_next_ball[3] = { 0 }, flag_first_appendarray = 0;
	elem_queue back_path[100] = { 0,0 };//���ڲ����ƶ��ɹ���·������ļ�¼

	inputdata_linecol(&line, &col);
	append_game_array('3', game_array, line, col, predict_next_ball, flag_first_appendarray);
	flag_first_appendarray = 1;
	print_game_array(game_array, line, col, '1', predict_next_ball, back_path);
	cout << endl << "���س�����ʾͼ��..." << endl;
	huiche_conti();
	cct_cls();
	change_typeface_cmd(line, col, '4');
	cct_enable_mouse();//����ʹ����꣬�������������д��ڴ�С��
	print_gird(line, col, choice, 0);//������
	for (int i = 0; i < line; i++)
		for (int j = 0; j < col; j++)
			if (game_array[i][j] != 0)
				print_ball(game_array[i][j], i, j, choice);
	cct_gotoxy(0, line + 2);
	input_end_continue();
}

void fun_5(char choice)
{
	//line����������col������������game_array�е�һ�����У������ڶ������У�����x�����У�y�����У�������Ӧ��ϵ
	int line = 0, col = 0, game_array[9][9] = { 0 }, predict_next_ball[3] = { 0 }, flag_first_appendarray = 0;
	elem_queue back_path[100] = { 0,0 };//���ڲ����ƶ��ɹ���·������ļ�¼

	inputdata_linecol(&line, &col);
	append_game_array('3', game_array, line, col, predict_next_ball, flag_first_appendarray);
	flag_first_appendarray = 1;
	print_game_array(game_array, line, col, '1', predict_next_ball, back_path);
	cout << endl << "���س�����ʾͼ��..." << endl;
	huiche_conti();
	cct_cls();
	change_typeface_cmd(line, col, '5');
	cct_enable_mouse();//����ʹ����꣬�������������д��ڴ�С��
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
	//line����������col������������game_array�е�һ�����У������ڶ������У�����x�����У�y�����У�������Ӧ��ϵ
	int line = 0, col = 0, game_array[9][9] = { 0 }, predict_next_ball[3] = { 0 }, flag_first_appendarray = 0;
	char sta_line, sta_col, des_line, des_col;//�������ڲ����ƶ�����ʼ�����Ŀ������
	elem_queue back_path[100] = { 0,0 }, del_locate[100] = { 0,0 };//���ڲ����ƶ��ɹ���·������ļ�¼
	int tmp = 0, color_ball = 0;
	inputdata_linecol(&line, &col);
	append_game_array('2', game_array, line, col, predict_next_ball, flag_first_appendarray);
	flag_first_appendarray = 1;
	cct_cls();
	change_typeface_cmd(line, col, '6');//�ı�cmd��С������
	cct_enable_mouse();//����ʹ����꣬�������������д��ڴ�С��
	print_gird(line, col, '5', 0);
	for (int i = 0; i < line; i++)//���ݴ�ʱ�ڲ������ֵ�ڸ����ڻ�С��
		for (int j = 0; j < col; j++)
			if (game_array[i][j] != 0)
				print_ball(game_array[i][j], i, j, '5');
	//��λ����Ҫ����������ز����ĺ������ҹ�����ѭ����ֻ���Ҽ������˳�ѭ��
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
				cout << "���� �޷���[" << sta_line << sta_col << "]�ƶ���" << des_line << des_col << endl;
				Sleep(1000);
				cct_showch(0, 2 * line + 3, ' ', 0, 7, 40);
			}
			else
			{   //�ƶ����飬��ӡͼ�ε��ƶ����̣��ܼƵ÷֣���������򣬴�ӡ��Ӻ������
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
	//line����������col������������game_array�е�һ�����У������ڶ������У�����x�����У�y�����У�������Ӧ��ϵ
	int line = 0, col = 0, game_array[9][9] = { 0 }, predict_next_ball[12] = { 0 }, flag_first_appendarray = 0;
	char sta_line, sta_col, des_line, des_col;//�������ڲ����ƶ�����ʼ�����Ŀ������
	elem_queue back_path[100] = { 0,0 }, locate_del_ball[100] = { {0,0} };//���ڲ����ƶ��ɹ���·������ļ�¼
	int tmp = 0, tmp1 = 0, score = 0, num_toa_ball = 0, color_ball = 0, num_percl_ball[7] = { 0 }, num_del_ball[7] = { 0 };
	inputdata_linecol(&line, &col);
	append_game_array('7', game_array, line, col, predict_next_ball, flag_first_appendarray);
	flag_first_appendarray = 1;
	cct_cls();
	change_typeface_cmd(line, col, '7');//�ı�cmd��С������
	cct_enable_mouse();//����ʹ����꣬�������������д��ڴ�С��
	cct_gotoxy(0, 1);
	print_gird(line, col, '5', 0);//��ӡ���򷽿�
	cct_gotoxy(40, 1);
	print_gird(1, 5, '4', 40);//��ӡ�÷ַ���
	cct_gotoxy(40, 5);
	print_gird(1, 3, '5', 40);//��ӡԤ����򷽿�
	cct_gotoxy(40, 9);
	print_gird(8, 12, '4', 40);//��ӡ��������
	for (int i = 0; i < line; i++)//���ݴ�ʱ�ڲ������ֵ�ڸ����ڻ�С��
		for (int j = 0; j < col; j++)
			if (game_array[i][j] != 0)
				print_ball(game_array[i][j], i, j, '5');
	while (1)
	{
		int flag_end = 0;
		cct_showstr(42, 2, "�÷�: ", 15, 0, 1);
		cct_showint(48, 2, score, 15, 0, 1);
		for (int i = 0; i < 3; i++)
			print_ball(predict_next_ball[i], 6, 42 + 4 * i, '8');//���ҿ��ڴ�ӡ�´�����С�����ɫ

		for (int i = 0; i < 7; i++)
			num_percl_ball[i] = 0;//�������
		for (int i = 0; i < line; i++)//ͳ��ÿ����ɫ���������
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
		cout << "  :" << setfill('0') << setw(2) << line * col - num_toa_ball << "/(" << setfill(' ') << setw(5) << setiosflags(ios::fixed) << setprecision(2) << (line * col - num_toa_ball) * 100.0 / (line * col) << "%)  ����-" << tmp1;
		for (int i = 0; i < 7; i++)
		{
			print_ball(i + 1, 11 + i, 42, '8');
			cct_setcolor(15, 0);
			cout << ":" << setfill('0') << setw(2) << num_percl_ball[i] << "/(" << setfill(' ') << setw(5)
				<< setiosflags(ios::fixed) << setprecision(2) << num_percl_ball[i] * 100.0 / (line * col) << "%)  ����-" << num_del_ball[i];
		}
		flag_end = mouse_operate(line, col, &sta_line, &sta_col, &des_line, &des_col, game_array);
		if (flag_end)//���Ҽ�
			break;
		else
		{
			//�ƶ����飬��ӡͼ�ε��ƶ����̣��ܼƵ÷֣���������򣬴�ӡ��Ӻ������
			tmp = search_game_road(choice, game_array, back_path, line, col, sta_line, sta_col, des_line, des_col);
			if (tmp == 0)
			{
				cct_gotoxy(0, 2 * line + 3);
				cout << "���� �޷���[" << sta_line << sta_col << "]�ƶ���" << des_line << des_col << endl;
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
				if (check_game_over(game_array, line, col) == 0)//�����ʱ�����Ѿ�����
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
				tmp = check_ball_delete(game_array, line, col, &color_ball, locate_del_ball);//�����������ٴμ�����޳��������������������ȥ�Ҳ������ܵ÷�
				if (tmp >= 5)
				{
					del_ball_dynamic(locate_del_ball, tmp);
					cct_gotoxy(0, 2 * line + 3);
					cct_setcolor();
					cout << "������ȥ�������������Ϊ���������ܵ÷�";
					Sleep(1000);
					cct_showch(0, 2 * line + 3, ' ', 0, 1, 40);
				}
			}
		}
	}
	cct_gotoxy(0, 2 * line + 1);
	input_end_continue();
}

//�ı�cmd���ڵĴ�С�����塢�ֺ�
void change_typeface_cmd(int set_lines, int set_cols, char choice)
{
	cct_setcolor();
	if (choice == '4')
	{
		cct_setconsoleborder(35, set_lines + 6);
		cct_setfontsize("������", 36);
		cout << "��Ļ��" << set_lines + 6 << "��" << 35 << "��" << endl;
	}
	else if (choice == '5' || choice == '6')
	{
		cct_setconsoleborder(2 * set_cols + 21, 2 * set_lines + 5);
		cct_setfontsize("������", 32);
		cout << "��Ļ��" << 2 * set_lines + 5 << "��" << 2 * set_cols + 21 << "��";
		if (choice == '6')
			cout << "(�ڲ����ϰ��Ҽ��˳�)";
		cout << endl;
	}
	else if (choice == '7')
	{
		cct_setconsoleborder(70, 23);
		cct_setfontsize("������", 24);
		cout << "��Ļ��" << 23 << "��" << 70 << "��" << "(���򷽸����Ҽ��˳�)" << endl;
	}
}

//�����ӵĺ��������ݲ���ѡ���Ƿ񻭷ָ���
void print_gird(int line, int col, char choice, int sta_col)
{
	int tmp_x = 1, tmp_y = 1, flag = 0;//flag=0����ӡ"�U"��flag=1����ӡ"�d�T"
	cct_getxy(tmp_x, tmp_y);
	cct_showstr(tmp_x, tmp_y, "�X�T", 15, 0, 1);
	for (int i = 1; i < col; i++)//ѭ�������ƴ���
	{
		cct_getxy(tmp_x, tmp_y);
		if (choice == '4')
			cct_showstr(tmp_x, tmp_y, "�T", 15, 0, 1);
		else if (choice == '5')
			cct_showstr(tmp_x, tmp_y, "�j�T", 15, 0, 1);//ͨ���������ƴ�ӡ���ݵĲ�ͬ
	}
	cct_getxy(tmp_x, tmp_y);
	if (choice == '4')
		cct_showstr(tmp_x, tmp_y, "�[", 15, 0, 1);
	else if (choice == '5')
		cct_showstr(tmp_x, tmp_y, "�[", 15, 0, 1);//��ӡ��һ����

	if (choice == '4')
	{
		for (int i = 0; i < line; i++)
		{
			cct_showstr(sta_col, tmp_y + 1, "�U", 15, 0, 1);
			cct_getxy(tmp_x, tmp_y);
			for (int j = 0; j < 2 * col; j++)
				cct_showch(tmp_x++, tmp_y, ' ', 15, 0, 1);//��ӡ�м�Ŀհײ���
			cct_showstr(2 * col + 2 + sta_col, tmp_y, "�U", 15, 0, 1);
		}
	}
	else if (choice == '5')
	{
		for (int i = 0; i < 2 * line - 1; i++)
		{
			if (flag == 0)
			{
				cct_showstr(sta_col, tmp_y + 1, "�U  ", 15, 0, 1);
				cct_getxy(tmp_x, tmp_y);
				for (int j = 0; j < col - 1; j++) {
					cct_getxy(tmp_x, tmp_y);
					cct_showstr(tmp_x, tmp_y, "�U  ", 15, 0, 1);
				}
				cct_showstr(4 * col + sta_col, tmp_y, "�U", 15, 0, 1);
				flag = 1;
			}
			else
			{
				cct_showstr(sta_col, tmp_y + 1, "�d�T", 15, 0, 1);
				cct_getxy(tmp_x, tmp_y);
				for (int j = 0; j < col - 1; j++) {
					cct_getxy(tmp_x, tmp_y);
					cct_showstr(tmp_x, tmp_y, "�p�T", 15, 0, 1);
				}
				cct_showstr(4 * col + sta_col, tmp_y, "�g", 15, 0, 1);
				flag = 0;
			}
		}
	}//��ӡ�м�line��
	cct_getxy(tmp_x, tmp_y);
	cct_showstr(sta_col, tmp_y + 1, "�^�T", 15, 0, 1);
	for (int i = 1; i < col; i++)
	{
		cct_getxy(tmp_x, tmp_y);
		if (choice == '4')
			cct_showstr(tmp_x, tmp_y, "�T", 15, 0, 1);
		else if (choice == '5')
			cct_showstr(tmp_x, tmp_y, "�m�T", 15, 0, 1);
	}
	cct_getxy(tmp_x, tmp_y);
	cct_showstr(tmp_x, tmp_y, "�a", 15, 0, 1);//��ӡ���һ����
	cct_setcolor();//�ָ���ɫ
}

//�ڸ��ӵ�ָ��λ�ô�ӡһ����
void print_ball(int color, int des_line, int des_col, char choice)
{//��������һ�¼��㣺1.����һ��Բ�����ƺô�С��ǰ��ɫ(white),2.����Ӧλ�õĸ��ӵı���ɫ����Ϊ��Ӧ��ɫ
	if (color == 2)
		color += 7;
	if (choice == '4')
		cct_showstr(2 * des_col + 2, 2 + des_line, "��", color, 14, 1);//��Բ
	else if (choice == '5')
		cct_showstr(4 * des_col + 2, 2 * des_line + 2, "��", color, 14, 1);
	else if (choice == '6')
		cct_showstr(4 * des_col + 2, 2 * des_line + 2, "��", color, 14, 1);
	else if (choice == '7')
		cct_showstr(des_col, des_line, "��", color, 14, 1);
	else if (choice == '8')
		cct_showstr(des_col, des_line, "��", color, 14, 1);
	cct_setcolor();//�ָ���ɫ
}

/*������������1.��Ҫ�ܸ�֪����λ�ã�����Ҫ������Ӧ��ֵ����Ϊ�������ʼ�������ֹ���꣩
				 ���Ծ�Ҫ׼ȷ���ָ�֪��������Щ���򷵻ص��������Ƕ��١�
				2. ����ѡ�к��˳������ѡ�У�ѡ�к���Ҫ���Ĵ�λ�õ�ͼ����ʾ
				�Ҽ��˳����˳�ʱ������ָ���Ŀ��ڰ������з���������λ����Ч��
				ϸ�ڣ��������ں��������⣬���ٸ�Ӧ��λ�ã�
���ϣ���������������Ҫ���ܾ��Ǹ�֪λ�ã������˳�������һ��ѡ�У���ʱ������꺯�������ض�Ӧ����
�ƶ��������ٴλص���꺯������һ����꺯������Ϊ�Ҽ�������ȫ�˳���ͨ����꺯������ֵ�жϣ�*/

int mouse_operate(int line, int col, char* sta_line, char* sta_col, char* des_line, char* des_col, int a[9][9])
{
	int X = 0, Y = 0, ret, maction, keycode1, keycode2, loop = 1;
	int tmp_move = 0;
	elem_queue b[100] = { 0,0 };
	static int flag_ball = 0;//flag����ָʾ����ĵ����
	static int last_i = -1, last_j = -1;//��¼�ϴ���������λ��
	cct_enable_mouse();
	cct_setcursor(CURSOR_INVISIBLE);	//�رչ��
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
						cout << "[��ǰ���λ��] " << char(i + 'A') << "��" << j + 1 << "��" << endl;
						switch (maction)//�����갴��
						{
							case MOUSE_LEFT_BUTTON_CLICK:			//�������,������Ϊѡ�к��ƶ���
								if ((i != last_i) || (j != last_j))    //��ΰ��µ�����λ�����ϴβ�ͬ
								{   //ѡ�������㣬���λ�����ϴ��ݴ��ѡ�е�λ�ò�ͬ�������λ�ñ�������
									if (a[i][j] != 0)//��ӡ"��"��λ�ñ����в���
									{
										print_ball(a[i][j], i, j, '6');//��ӡ�����ѡ��ͼ��
										if (flag_ball == 1 && a[last_i][last_j] != 0)//�ϸ�λ�ô�ʱ��Ϊ��
											print_ball(a[last_i][last_j], last_i, last_j, '5');//�ָ��ϸ�λ�ñ�ѡ�еĲ���
										last_i = i;
										last_j = j;//��¼����
										flag_ball = 1;//˵���Ѿ�ѡ�й�����
									}
									else if (flag_ball)//��������겻��������֮ǰ�Ѿ�ѡ���򣬿����ƶ�������������
									{

										*sta_line = char(last_i + 'A');
										*sta_col = char(last_j + '1');
										*des_line = char(i + 'A');
										*des_col = char(j + '1');//����������¼
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
								else if ((i == last_i) && (j == last_j))//���ΰ��µ�������ͬ
								{
									if (a[i][j] != 0 && flag_ball == 1)//���µĵط��в���
									{
										print_ball(a[i][j], i, j, '5');
										flag_ball = 0;//���в����λ�����������Σ�ȡ��ѡ�У�����
									}
									else if (a[i][j] != 0 && flag_ball == 0)
									{
										print_ball(a[i][j], i, j, '6');
										flag_ball = 1;
									}
								}
								break;
							case MOUSE_RIGHT_BUTTON_CLICK:			//�����Ҽ�
								return 1;
						} //end of switch(maction)
					}//end of if
				}
			}//�����ص�X/Y����Ӧ��λ�ù�ϵ���ٴ�ӡλ��en
		}
		else if (ret == CCT_KEYBOARD_EVENT)
			continue;	//end of swicth(keycode1)
	}
	return 0;
}

/*�������ܣ���̬��ʾ������ƶ�
  back_path�д���Ǵ���ʼλ�õ���ֹλ�õ��ƶ�·�������꣬������ֱ��cct_show��
  ��Ϊ����˲�ƣ����Ա������ж��ƶ������پ�����������һ����ƶ�,����ÿ���ƶ�ֻ�ƶ���������䣬��������һ��ѭ��*/
int move_ball_dynamic(int line, char sta_line, char sta_col, char des_line, char des_col, elem_queue back_path[100], int a[9][9], char choice)
{     //x���У�������y���У�����
	 //i=0,���ң�i=1,���£�i=2������i=3�����ϣ�
	int tmp_x = 0, tmp_y = 0;
	int path_length = 0;
	if (choice == '7')
	{
		cct_showch(0, 2 * line + 2, ' ', 0, 7, 30);
		cct_setcolor(0, 7);
		cct_gotoxy(0, 2 * line + 2);
		cout << "[��ʾ]  " << "���Դ�[" << sta_line << sta_col << "]�ƶ���[" << des_line << des_col << "]";
	}
	while ((back_path[path_length].x != (des_col - '1')) || (back_path[path_length].y != (des_line - 'A')))
	{
		for (int i = 0; i < 4; i++)
		{
			cct_setcolor();
			//���ж�back_path��ǰһ������һ��λ��Ӧ�ó��ĸ������ƶ�,�������ƶ��ĴΣ������ƶ�����
			if ((back_path[path_length + 1].x == back_path[path_length].x + dx[i])
				&& (back_path[path_length + 1].y == back_path[path_length].y + dy[i]))
			{
				tmp_x = 4 * back_path[path_length].x + 2;
				tmp_y = 2 * back_path[path_length].y + 2;//ȡ��ǰ��x,y����,ע������cmd���ڵ�����
				if (i == 0)
				{
					for (int j = 0; j < 4; j++)
					{
						print_ball(a[sta_line - 'A'][sta_col - '1'], tmp_y, ++tmp_x, '7');
						cct_showch(tmp_x - 1, tmp_y, ' ', 15, 0, 1);//��������
						if (j == 3)
							cct_showstr(tmp_x - 2, tmp_y, "�U", 15, 0, 1);
						Sleep(100);
					}
				}
				else if (i == 2)
				{
					for (int j = 0; j < 4; j++)
					{
						print_ball(a[sta_line - 'A'][sta_col - '1'], tmp_y, --tmp_x, '7');
						cct_showch(tmp_x + 2, tmp_y, ' ', 15, 0, 1);//��������
						if (j == 3)
							cct_showstr(tmp_x + 2, tmp_y, "�U", 15, 0, 1);
						Sleep(100);
					}
				}
				else if (i == 1)
				{
					for (int j = 0; j < 2; j++)
					{
						print_ball(a[sta_line - 'A'][sta_col - '1'], ++tmp_y, tmp_x, '7');
						cct_showch(tmp_x, tmp_y - 1, ' ', 15, 0, 2);//��������
						if (j == 1)
							cct_showstr(tmp_x, tmp_y - 1, "�T", 15, 0, 1);
						Sleep(100);
					}
				}
				else if (i == 3)
				{
					for (int j = 0; j < 2; j++)
					{
						print_ball(a[sta_line - 'A'][sta_col - '1'], --tmp_y, tmp_x, '7');
						cct_showch(tmp_x, tmp_y + 1, ' ', 15, 0, 2);//��������
						if (j == 1)
							cct_showstr(tmp_x, tmp_y + 1, "�T", 15, 0, 1);
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

//�������ܣ�ʵ��cmd������������
void del_ball_dynamic(elem_queue delete_locate[100], int number)
{
	for (int i = 0; i < number; i++)
		cct_showstr(4 * delete_locate[i].x + 2, 2 * delete_locate[i].y + 2, "  ", 15, 0, 1);
	Sleep(100);
}

