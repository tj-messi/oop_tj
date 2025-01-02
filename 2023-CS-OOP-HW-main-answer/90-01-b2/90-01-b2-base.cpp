/*2150792 �ƿ� ţ»��*/
#include"../include/cmd_console_tools.h"
#include"../include/common.h"
#include"90-01-b2.h"

//�ڲ�����ʵ�ֵ���������
void fun_1(char choice)
{
	//line����������col������������game_array�е�һ�����У������ڶ������У�����x�����У�y�����У�������Ӧ��ϵ
	int line = 0, col = 0, game_array[9][9] = { 0 }, predict_next_ball[3] = { 0 }, flag_first_appendarray = 0;
	elem_queue back_path[100] = { 0,0 };//���ڲ����ƶ��ɹ���·������ļ�¼
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
	char sta_line, sta_col, des_line, des_col;//�������ڲ����ƶ�����ʼ�����Ŀ������
	int tmp = 0, score = 0;
	elem_queue back_path[100] = { {0,0} };//���ڲ����ƶ��ɹ���·������ļ�¼

	inputdata_linecol(&line, &col);
	append_game_array(choice, game_array, line, col, predict_next_ball, flag_first_appendarray);
	flag_first_appendarray = 1;
	print_game_array(game_array, line, col, choice, predict_next_ball, back_path);
	inputdata_move(line, col, &sta_line, &sta_col, &des_line, &des_col, game_array);
	tmp = search_game_road(choice, game_array, back_path, line, col, sta_line, sta_col, des_line, des_col);
	if (tmp == 0)
		cout << "�޷��ҵ��ƶ�·��" << endl;
	else
	{
		move_game_array(choice, game_array, sta_line, sta_col, des_line, des_col);

		print_game_array(game_array, line, col, '4', predict_next_ball, back_path);//���ҽ������
		print_game_array(game_array, line, col, '5', predict_next_ball, back_path);//�ƶ�·��
	}
	input_end_continue();
}

void fun_3(char choice)
{
	int line = 0, col = 0, game_array[9][9] = { 0 }, predict_next_ball[3] = { 0 }, flag_first_appendarray = 0;
	char sta_line, sta_col, des_line, des_col;//�������ڲ����ƶ�����ʼ�����Ŀ������
	int tmp = 0, score = 0, tmp1 = 0, color_ball = 0;
	elem_queue back_path[100] = { 0,0 }, del_locate[100] = { 0,0 };//���ڲ����ƶ��ɹ���·������ļ�¼

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
			cout << "�޷��ҵ��ƶ�·��" << endl;
			print_game_array(game_array, line, col, '2', predict_next_ball, back_path);
		}
		else
		{   //�ƶ����飬��ӡ���飬�ܼƵ÷֣���������򣬴�ӡ��Ӻ������
			move_game_array(choice, game_array, sta_line, sta_col, des_line, des_col);//���ƶ�����
			print_game_array(game_array, line, col, '3', predict_next_ball, back_path);//��ӡ�ƶ���Ӧ���򣬵���û����������������(��demo����ȫһ�£�������Ϊ���ָ�ֱ�ۣ�
			tmp = check_ball_delete(game_array, line, col, &color_ball, del_locate);
			if (tmp >= 5)
				score += (tmp - 1) * (tmp - 2);
			cout << endl << "���ε÷�: " << ((tmp >= 5) ? (tmp - 1) * (tmp - 2) : 0) << "  �ܵ÷�: " << score << endl;
			if (tmp < 5)
				tmp1 = append_game_array(choice, game_array, line, col, predict_next_ball, flag_first_appendarray);
			else
				tmp1 = 0;
			print_game_array(game_array, line, col, '2', predict_next_ball, back_path);
			tmp = check_ball_delete(game_array, line, col, &color_ball, del_locate);//�����������ٴμ�����޳��������������������ȥ�Ҳ������ܵ÷�
			if (tmp >= 5)
				cout << endl << "������ȥ�������������Ϊ���������ܵ÷�" << endl;
			if (check_game_over(game_array, line, col) == 0)//�����ʱ�����Ѿ�����
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

//�������ܣ���ӡ��Ϸ���ڲ�����    (�������鷽ʽʹ��)
void print_game_array(int a[9][9], int line, int col, char choice, int b[3], elem_queue back_path[100])
{
	int a_1[9][9] = { 0 };
	if (choice == '1')
		cout << endl << "��ʼ����" << endl;
	else if (choice == '2')
		cout << endl << "��ǰ����" << endl;
	else if (choice == '3')
		cout << endl << "�ƶ��������" << endl;
	else if (choice == '4')
		cout << endl << "���ҽ������" << endl;
	else if (choice == '5')
		cout << endl << "�ƶ�·��" << endl;
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
		if (choice == '4')//��Ӧ����2�Ĳ��ҽ������
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
				for (int t = 0; back_path[t].x != -1; t++)//����back__path
				{
					if ((i == back_path[t].y) && (j == back_path[t].x))
					{     //Ϊ������ɫ2��ͼ����������ɫ���ָ����ԣ�����+7;
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
	if (choice == '2')//���ݲ���ѡ���Ƿ�Ԥ���´β����������ֵ
		cout << endl << "��3���������ɫ�ֱ��ǣ�" << b[0] << ' ' << b[1] << ' ' << b[2] << endl;
}

//�������ܣ������ƶ��������ʼ��Ŀ������     (���������鷽ʽ����������)
int inputdata_move(int line, int col, char* sta_line, char* sta_col, char* des_line, char* des_col, int a[9][9])
{
	cout << "������ĸ+������ʽ[����c2]����Ҫ�ƶ���ľ������꣺";
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
					cout << "����Ϊ" << *sta_line << "��" << *sta_col << "��" << endl;
					break;
				}
				else
					flag = 1;
			}
		}
		if (flag == 0)
			cout << "�����������������";
		else
			cout << "��ʼλ��Ϊ�գ�����������";
		int tmp_x = 0, tmp_y = 0;
		cct_getxy(tmp_x, tmp_y);
		cct_showch(49, tmp_y - 1, ' ', COLOR_BLACK, COLOR_WHITE, 20);//�����ղŵ�����
		cct_gotoxy(49, tmp_y - 1);//���ص���Ӧλ��
	}
	cout << "������ĸ+������ʽ[����c2]����Ҫ�ƶ����Ŀ�����꣺";
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
					cout << "����Ϊ" << *des_line << "��" << *des_col << "��" << endl;
					break;
				}
				else
					flag = 1;
			}
		}
		if (flag == 0)
			cout << "�����������������";
		else
			cout << "Ŀ��λ�÷ǿգ�����������";
		int tmp_x = 0, tmp_y = 0;
		cct_getxy(tmp_x, tmp_y);
		cct_showch(49, tmp_y - 1, ' ', COLOR_BLACK, COLOR_WHITE, 20);//�����ղŵ�����
		cct_gotoxy(49, tmp_y - 1);//���ص���Ӧλ��
		continue;
	}
	return 0;
}