/*2150792 �ƿ� ţ»��*/
#include"../include/cmd_console_tools.h"
#include"../include/common.h"
#include"90-01-b2.h"

//�������ܣ�ʵ������������������   (��Ҫ��cmd������ʵ�ֹ���)
void inputdata_linecol(int* line, int* col)
{
	cout << "����������(7-9)" << endl;
	while (1)
	{
		if (get_input_int(7, 9, *line) == 1)
			break;
	}
	cout << "����������(7-9)" << endl;
	while (1)
	{
		if (get_input_int(7, 9, *col) == 1)
			break;
	}
	cin.ignore(65536, '\n');
}

//�������ܣ����س�������   (��Ҫ��cmd������ʵ�ֹ���)
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

//�����Ϸ�ڲ�����ģ��Ӷ�ʵ��ÿ�����������ĺ�������������������һ�β�������������Լ�����������      (��Ҫ��cmd������ʵ�ֹ���)
int append_game_array(char choice, int a[9][9], int line, int col, int b[], int flag_first)
{
	srand((unsigned int)(time(0)));
	static int tmp_ball_num[9] = { 0 };
	int tmp_line = 0, tmp_col = 0, num_ball = 0;
	if (choice == '2')
		num_ball = line * col * 3 / 5;
	else if (choice == '3' || choice == '1' || choice == '7')
		num_ball = 5;
	if (flag_first == 0)//��һ��ʱִ�У�����Ҫ���ݶ�Ӧ����ѡ��5������60%
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
		for (int i = 0; i < 3;)//����������Ϊÿ������
		{
			if (check_game_over(a, line, col) == 0)//�����ʱ�����Ѿ�����
				return -1;
			tmp_line = rand() % line;
			tmp_col = rand() % col;
			if (a[tmp_line][tmp_col] != 0)
				continue;//�Ѵ������֣��������
			else
			{
				if (choice == '7')
				{
					b[i + 3] = tmp_line;
					b[i + 6] = tmp_col;
					b[i + 9] = tmp_ball_num[i];//����ص�ֵ�������飬�Ӷ�����(���������λ���Ǳ��뱻���̴�ӡ��λ��)
				}
				a[tmp_line][tmp_col] = tmp_ball_num[i];//������ھ�̬�����е���ɫ
				tmp_ball_num[i] = rand() % 7 + 1;
				b[i] = tmp_ball_num[i];//���������ɵ���ɫ����
				++i;
			}
		}
	}
	return 0;
}

//�������ܣ����ڸ�������ʼ�����Ŀ�����꣬�ı���Ϸ�ڲ������ֵ       (��Ҫ��cmd������ʵ�ֹ���)
void move_game_array(char choice, int a[9][9], char sta_line, char sta_col, char des_line, char des_col)
{
	int tmp = 0;
	tmp = a[sta_line - 'A'][sta_col - '1'];
	a[sta_line - 'A'][sta_col - '1'] = 0;
	a[des_line - 'A'][des_col - '1'] = tmp;
}

//�������ܣ�BFS�㷨ʵ��Ѱ�Ҵ�sta��des��·�������ҵ��������get_path����·��������back_path����������1���Ҳ����򷵻�0    (��Ҫ��cmd������ʵ�ֹ���)
int search_game_road(char choice, int a[9][9], elem_queue back_path[100], int line, int col, char sta_line, char sta_col, char des_line, char des_col)
{
	elem_queue first, perelem, search[100], back_elem[9][9];//��һ�����Ԫ�أ�ÿ�����Ԫ�أ���Ѱ���У�����·������
	int flag[9][9] = { 0 };//������ʶ��û���ҹ�
	int beg = 0;//�ýṹ���������ͨ����ģ�����
	first.x = sta_col - '1';//x���꣬���У�����������ڶ���λ��
	first.y = sta_line - 'A';//y���꣬���У�����Ӧ���������һ��λ��
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
				continue;//�ж���һԪ��λ�õĺϷ���
			if ((a[next_y][next_x] != 0) || flag[next_y][next_x] == 1)
				continue;
			perelem.x = next_x;
			perelem.y = next_y;
			flag[perelem.y][perelem.x] = 1;
			search[beg++] = perelem;
			back_elem[perelem.y][perelem.x].x = search[0].x;//��¼�ͽ����е�Ԫ�صĸ��׵�������
			back_elem[perelem.y][perelem.x].y = search[0].y;//��¼�ͽ����е�Ԫ�صĸ��׵�������
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

//�������ܣ�ͨ���ݹ��ҵ�BFS�㷨���ƶ�·�����Ѵ���ʼ�㵽Ŀ�����������������  (һ��ע��x�������꣬y��������)  (��Ҫ��cmd������ʵ�ֹ���)  
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

//�������ܣ����������������   (��Ҫ��cmd������ʵ�ֹ���)
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
			for (k = j; k < col; k++)//���������k<col��ֻҪ��ͬ������һֱ��
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
				break;//��Ϊÿ�����9�����ҵ�5����ͬ����ֱ��break������һ��
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

	for (int i = 0; i <= col - 5; i++)//�������
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
		int tmp1 = i;//�ݴ�i��ֵ
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

	for (int i = 0; i <= line - 5; i++)//����
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

//�������ܣ���������Ƿ�ȫ����ȫ����Ϸ����     (��Ҫ��cmd������ʵ�ֹ���)
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
			return 1;//��ʱ��û�н���
	}
	return 0;//��������
}


