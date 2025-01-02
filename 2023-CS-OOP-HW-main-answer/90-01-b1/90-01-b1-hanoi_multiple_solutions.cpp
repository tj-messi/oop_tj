/* �ƿ� 2150792 ţ»�� */
#include"90-01-b1-hanoi.h"
#include "../include/cmd_console_tools.h"
#include"../include/common.h"

bool flag_1111 = false;
bool fllag = true;
int length = 0;//���ȵļ�¼
int yanshi = 0;//�ƶ���ʱ��ѡ��
int A[10] = { 0 }, B[10] = { 0 }, C[10] = { 0 };//����һά����
int topa = 0, topb = 0, topc = 0;//����ջ��ָ��

/* ----------------------------------------------------------------------------------

	 ���ļ����ܣ�
	1����ű� hanoi_main.cpp �и��ݲ˵�����ֵ���õĸ��˵����Ӧ��ִ�к���

	 ���ļ�Ҫ��
	1�����������ⲿȫ�ֱ�����const��#define�������Ʒ�Χ�ڣ�
	2�������徲̬ȫ�ֱ�����������Ҫ��������Ҫ�����ĵ���ʾ��ȫ�ֱ�����ʹ��׼���ǣ����á����á��ܲ��þ������ã�
	3����̬�ֲ����������������ƣ���ʹ��׼��Ҳ�ǣ����á����á��ܲ��þ�������
	4���������ϵͳͷ�ļ����Զ���ͷ�ļ��������ռ��

   ----------------------------------------------------------------------------------- */
   /***************************************************************************
	 �������ƣ�hanoi
	 ��    �ܣ���ŵ���ƶ��ĵݹ麯��
	 �����������������ʼ�����м�����Ŀ������ѡ��ڼ�������
	 �� �� ֵ��
	 ˵    ����
   ***************************************************************************/
void hanoi(int n, char src, char tmp, char dst, char choice)
{
	if (n != 1) {

		hanoi(n - 1, src, dst, tmp, choice);//�Ȱ�ǰ��n-1������
		select_hanoi(n, src, dst, choice);
		hanoi(n - 1, tmp, src, dst, choice);
	}
	else {
		select_hanoi(n, src, dst, choice);
	}
}



/***************************************************************************
  �������ƣ�move_hanoi
  ��    �ܣ���ŵ���ڲ�������ƶ�
  �����������ʼ����Ŀ����
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void move_hanoi(char src, char dst)
{
	if (src == 'A' && dst == 'B')
	{
		B[topb++] = A[--topa];
		A[topa] = 0;
	}
	else if (src == 'A' && dst == 'C')
	{
		C[topc++] = A[--topa];
		A[topa] = 0;
	}
	else if (src == 'B' && dst == 'A')
	{
		A[topa++] = B[--topb];
		B[topb] = 0;
	}
	else if (src == 'B' && dst == 'C')
	{
		C[topc++] = B[--topb];
		B[topb] = 0;
	}
	else if (src == 'C' && dst == 'A')
	{
		A[topa++] = C[--topc];
		C[topc] = 0;
	}
	else
	{
		B[topb++] = C[--topc];
		C[topc] = 0;
	}
}

/***************************************************************************
  �������ƣ�select_hanoi
  ��    �ܣ��ڵݹ麯�����ٴ�ѡ���Ӧ����ִ�к����Ĳ˵�����
  �����������������ʼ����Ŀ������ѡ��ڼ�������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void select_hanoi(int n, char src, char dst, char choice)
{
	switch (choice)
	{
		case '1':
			print_1(n, src, dst);
			break;
		case '2':
			print_2(n, src, dst);
			break;
		case '3':
			move_hanoi(src, dst);
			for (int i = 0; i < topa - 1; i++)
			{
				if ((A[i] % 2) == (A[i + 1] % 2))
					flag_1111 = true;
			}
			for (int i = 0; i < topb - 1; i++)
			{
				if ((B[i] % 2) == (B[i + 1] % 2))
					flag_1111 = true;

			}
			for (int i = 0; i < topc - 1; i++)
			{
				if ((C[i] % 2) == (C[i + 1] % 2))
					flag_1111 = true;
			}
			print_3_4_8_hengxiang(n, src, dst, 1, 3);
			break;
		case '4':
			move_hanoi(src, dst);
			print_4_8_zongxiang(n, src, dst, 1, 4);
			print_3_4_8_hengxiang(n, src, dst, 1, 4);
			if (yanshi == 0)
				huiche_conti();
			else
				Sleep(change_yanshi_ms());
			break;
		case '7':
			if (++length == 1) {
				move_hanoi(src, dst);
				move_color(n, src, dst);
			}
			break;
		case '8':
			move_hanoi(src, dst);
			print_4_8_zongxiang(n, src, dst, 1, 8);
			print_3_4_8_hengxiang(n, src, dst, 1, 8);
			cct_setcolor();
			move_color(n, src, dst);
			cct_setcolor();
			if (yanshi == 0)
				huiche_conti();
			else
				Sleep(change_yanshi_ms());
			break;
		case '9':
			break;
	}
}

/***************************************************************************
  �������ƣ�cin_hanoi
  ��    �ܣ������������ʼ����Ŀ��������ʱ
  �����������ʼ�����м�����Ŀ������������ѡ���Ƿ�������ʱ�Ĳ���
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void cin_hanoi(char* sta, char* tmp, char* des, int* n, int select)
{
	cout << endl << endl;
	cout << "�����뺺ŵ���Ĳ���(1-10)" << endl;
	while (1)
	{
		if (get_input_int(1, 10, *n) == 1)
			break;
	}
	cin.ignore(65536, '\n');
	while (1)
	{
		cout << "��������ʼ��(A-C)" << endl;
		cin >> *sta;
		if (cin.good() == 0)
		{
			cin.clear();
			cin.ignore(65536, '\n');
			continue;
		}
		if (((*sta < 'A') || (*sta > 'C' && *sta < 'a') || (*sta > 'c')) && (cin.good() == 1))
		{
			cin.ignore(65536, '\n');
			continue;
		}
		if (((*sta >= 'A') && (*sta <= 'C')) || ((*sta >= 'a') && (*sta <= 'c')))
		{
			cin.ignore(65536, '\n');
			break;
		}
	}
	while (1)
	{
		cout << "������Ŀ����(A-C)" << endl;
		cin >> *des;
		if (cin.good() == 0)
		{
			cin.clear();
			cin.ignore(65536, '\n');
			continue;
		}
		if (((*des < 'A') || (*des > 'C' && *des < 'a') || (*des > 'c') || (*des == *sta) || (*des == *sta + 32) || (*des == *sta - 32)) && (cin.good() == 1))
		{
			cin.ignore(65536, '\n');
			if ((*des == *sta) || (*des == *sta + 32) || (*des == *sta - 32))
			{
				if (*des >= 97)
					cout << "Ŀ����(" << char(*des - 32) << ")��������ʼ��(" << char(*des - 32) << ")��ͬ" << endl;
				else
					cout << "Ŀ����(" << *des << ")��������ʼ��(" << *des << ")��ͬ" << endl;
			}
			continue;
		}
		if (((*des >= 'A' && *des <= 'C') || ((*des >= 'a') && (*des <= 'c'))) && ((*des != *sta) && (*des != *sta + 32) && (*des != *sta - 32)))
		{
			cin.ignore(65536, '\n');
			break;
		}
	}
	if (*des >= 97)
		*des = char(*des - 32);
	if (*sta >= 97)
		*sta = char(*sta - 32);

	if (((*sta == 'A') && (*des == 'B')) || ((*sta == 'B') && (*des == 'A')))
		*tmp = 'C';
	else if ((*sta == 'B') && (*des == 'C') || ((*sta == 'C') && (*des == 'B')))
		*tmp = 'A';
	else
		*tmp = 'B';
	if (select)
	{
		while (1)
		{
			cout << "�������ƶ��ٶ�(0-5: 0-���س�������ʾ 1-��ʱ� 5-��ʱ���)" << endl;
			cin >> yanshi;
			if (cin.good() == 0)
			{
				cin.clear();
				cin.ignore(65536, '\n');
				continue;
			}
			if (((yanshi < 0) || (yanshi > 5)) && (cin.good() == 1))
			{
				cin.ignore(65536, '\n');
				continue;
			}
			if (yanshi >= 0 && yanshi <= 5)
			{
				break;
			}
		}
	}
}

/***************************************************************************
  �������ƣ�cin_exe_9
  ��    �ܣ���Ӧ���ܾţ���Ϸ�����е����뺯��
  �����������ʼ����Ŀ����
  �� �� ֵ��
  ˵    ����
***************************************************************************/
int cin_exe_9(char* sta, char* des)
{
	unsigned char getch_9[20] = { 0 };
	while (1)
	{
		int i = 0;
		for (; i < 20;)
		{
			getch_9[i] = _getch();
			if (getch_9[i] == 13)
				break;
			if (getch_9[i] >= 33 && getch_9[i] <= 126)
			{
				putchar(getch_9[i]);
				++i;
			}
			else if (int(getch_9[i]) == 224)
			{
				getch_9[i] = _getch();
				continue;
			}
			else
				getch_9[i] = 0;
		}
		if (i == 20)
		{
			cct_showch(60, START_Y + 20 + 2, ' ', 0, 7, 20);
			cct_gotoxy(60, START_Y + 5 + 15 + 2);
			continue;
		}
		else
		{
			if ((getch_9[0] == 'q' || getch_9[0] == 'Q') && getch_9[1] == 13)
			{
				return -1;
			}
			if (((getch_9[0] >= 'A' && getch_9[0] <= 'C') || (getch_9[0] >= 'a' && getch_9[0] <= 'c'))
				&& ((getch_9[1] >= 'A' && getch_9[1] <= 'C') || (getch_9[1] >= 'a' && getch_9[1] <= 'c'))
				&& ((getch_9[1] != getch_9[0]) && (getch_9[1] != getch_9[0] + 32) && (getch_9[1] != getch_9[0] - 32))
				&& (getch_9[2] == 13))
			{
				if (getch_9[1] >= 97)
					getch_9[1] = char(getch_9[1] - 32);
				if (getch_9[0] >= 97)
					getch_9[0] = char(getch_9[0] - 32);
				*sta = getch_9[0];
				*des = getch_9[1];
				return 0;
			}
			else
			{
				cct_showch(60, START_Y + 20 + 2, ' ', 0, 7, 20);
				cct_gotoxy(60, START_Y + 5 + 15 + 2);
				continue;
			}
		}
	}
	return 0;
}

/***************************************************************************
  �������ƣ�huiche_conti
  ��    �ܣ�����س�������
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
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

/***************************************************************************
  �������ƣ�store_chushi
  ��    �ܣ����������Ĳ�������ʼ����Ŀ��������������
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void store_chushi(int n, char src, char dst)
{
	int temp = n;//�ݴ�n��ֵ
	if (src == 'A')
	{
		for (int i = 0; i < n; i++)
			A[topa++] = temp--;
	}
	else if (src == 'B')
	{
		for (int i = 0; i < n; i++)
			B[topb++] = temp--;
	}
	else
	{
		for (int i = 0; i < n; i++)
			C[topc++] = temp--;
	}
}

/***************************************************************************
  �������ƣ�clear_array
  ��    �ܣ�ĳһ����ִ����Ϻ���������
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void clear_array()
{
	for (int i = 0; i < 10; i++)
	{
		A[i] = 0;
		B[i] = 0;
		C[i] = 0;
	}
	topa = 0, topb = 0, topc = 0;
}

/***************************************************************************
  �������ƣ�change_yanshi_ms
  ��    �ܣ����������ʱת��Ϊ��Ӧ��Sleep����
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
int change_yanshi_ms()
{
	int time_ms = 0;
	switch (yanshi)
	{
		case 1:
			time_ms = 800;
			break;
		case 2:
			time_ms = 200;
			break;
		case 3:
			time_ms = 50;
			break;
		case 4:
			time_ms = 15;
			break;
		case 5:
			time_ms = 0;
			break;
	}
	return time_ms;
}

/***************************************************************************
  �������ƣ�exe_1��exe_9Ϊ��Ӧ�Ĺ���1-9��ִ�к���
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void exe_1(int n, char src, char tmp, char dst, char choice)
{
	cin_hanoi(&src, &tmp, &dst, &n, 0);
	hanoi(n, src, tmp, dst,choice);
	cout << endl;
	cout << "���س�������";
	huiche_conti();
}

void exe_2(int n, char src, char tmp, char dst, char choice)
{
	cin_hanoi(&src, &tmp, &dst, &n, 0);
	length = 0;
	hanoi(n, src, tmp, dst, choice);
	cout << endl;
	cout << "���س�������";
	huiche_conti();
}

void exe_3(int n, char src, char tmp, char dst, char choice)
{
	cin_hanoi(&src, &tmp, &dst, &n, 0);
	length = 0;
	store_chushi(n, src, dst);
	print_3_4_8_hengxiang(n, src, dst, 0, 3);
	hanoi(n, src, tmp, dst, choice);
	clear_array();
	if (flag_1111 == true)
		cout << "�������µ��ƶ�����" << endl;
	else
		cout << "�����µ��ƶ�����" << endl;
	cout << endl << "���س�������";
	huiche_conti();
}

void exe_4(int n, char src, char tmp, char dst, char choice)
{
	cin_hanoi(&src, &tmp, &dst, &n, 1);
	length = 0;
	store_chushi(n, src, dst);
	cct_cls();
	cct_setcursor(CURSOR_INVISIBLE);
	cout << "�� " << src << " �ƶ��� " << dst << "���� " << n << " �㣬��ʱ����Ϊ " << yanshi;
	print_4_8_zongxiang(n, src, dst, 0, 4);
	print_3_4_8_hengxiang(n, src, dst, 0, 4);
	if (yanshi == 0)
		huiche_conti();
	else
		Sleep(change_yanshi_ms());
	hanoi(n, src, tmp, dst, choice);
	clear_array();
	cct_gotoxy(0, 38);
	cout << "���س�������";
	cct_setcursor(CURSOR_VISIBLE_NORMAL);
	huiche_conti();
}

void exe_5()
{
	cct_cls();
	cct_setcursor(CURSOR_INVISIBLE);
	print_5();
	cct_setcursor(CURSOR_VISIBLE_NORMAL);
	cct_setcolor(0, 15);
	cct_gotoxy(0, 38);
	cout << "���س�������";
	huiche_conti();
}

void exe_6(int n, char src, char tmp, char dst, char choice)
{
	cin_hanoi(&src, &tmp, &dst, &n, 0);
	length = 0;
	cct_cls();
	store_chushi(n, src, dst);
	cct_setcursor(CURSOR_INVISIBLE);
	print_6(n, src, tmp, dst);
	clear_array();
	cct_setcolor(0, 15);
	cct_gotoxy(0, 38);
	cct_setcursor(CURSOR_VISIBLE_NORMAL);
	cout << "���س�������";
	huiche_conti();
}

void exe_7(int n, char src, char tmp, char dst, char choice)
{
	cin_hanoi(&src, &tmp, &dst, &n, 0);
	length = 0;
	yanshi = 3;
	cct_cls();
	store_chushi(n, src, dst);
	cout << "�� " << src << " �ƶ��� " << dst << " ���� " << n << " ��";
	cct_setcursor(CURSOR_INVISIBLE);
	print_6(n, src, tmp, dst);
	hanoi(n, src, tmp, dst, choice);
	clear_array();
	yanshi = 0;
	cct_setcolor(0, 15);
	cct_gotoxy(0, 38);
	cct_setcursor(CURSOR_VISIBLE_NORMAL);
	cout << "���س�������";
	huiche_conti();
}

void exe_8(int n, char src, char tmp, char dst, char choice)
{
	cin_hanoi(&src, &tmp, &dst, &n, 1);
	length = 0;
	cct_cls();
	store_chushi(n, src, dst);
	cout << "�� " << src << " �ƶ��� " << dst << "���� " << n << " �㣬��ʱ����Ϊ " << yanshi;
	cct_setcursor(CURSOR_INVISIBLE);
	print_4_8_zongxiang(n, src, dst, 0, 8);
	print_3_4_8_hengxiang(n, src, dst, 0, 8);
	print_6(n, src, tmp, dst);
	if (yanshi == 0)
		huiche_conti();
	else
		Sleep(change_yanshi_ms());
	cct_setcolor();
	hanoi(n, src, tmp, dst, choice);
	clear_array();
	cct_setcolor();
	cct_gotoxy(0, 38);
	cct_setcursor(CURSOR_VISIBLE_NORMAL);
	cout << "���س�������";
	huiche_conti();
}

void exe_9(int n, char src, char tmp, char dst, char choice)
{
	cin_hanoi(&src, &tmp, &dst, &n, 0);
	char Src = src;
	char Dst = dst;
	int flag = 0;
	int test[10] = { 0 };
	int temp = n;//�ݴ�n��ֵ
	for (int i = 0; i < n;)
		test[i++] = temp--;
	length = 0;
	cct_cls();
	store_chushi(n, src, dst);
	cout << "�� " << src << " �ƶ��� " << dst << "���� " << n << " ��";
	cct_setcursor(CURSOR_INVISIBLE);
	print_4_8_zongxiang(n, src, dst, 0, 8);
	print_3_4_8_hengxiang(n, src, dst, 0, 8);//8��9����ͬһ������
	print_6(n, src, tmp, dst);
	cct_setcolor();
	cct_gotoxy(0, START_Y + 5 + 15 + 2);
	cout << "�������ƶ�������(������ʽ��AC=A���˵������ƶ���C��Q=�˳�) ��";
	while (1)
	{
		cct_setcursor(CURSOR_VISIBLE_NORMAL);
		cct_gotoxy(60, START_Y + 5 + 15 + 2);
		cct_showch(60, START_Y + 5 + 15 + 2, ' ', 0, 7, 3);
		cct_gotoxy(60, START_Y + 5 + 15 + 2);
		flag = cin_exe_9(&src, &dst);
		//��ʱ��֤src��dst��ΪA-C����Ҫ�ٶ�������Ϸ���������֤
		if (flag == -1)
		{
			cct_gotoxy(0, START_Y + 5 + 15 + 3);
			cout << "��Ϸ�ѱ�����ֹ������";
			break;
		}
		if (src == 'A')
		{
			if (topa == 0)
			{
				cct_gotoxy(0, START_Y + 5 + 15 + 3);
				cout << "A���Ѿ�Ϊ�գ��޷���A�����ƶ�����";
				Sleep(1000);
				cct_showch(0, START_Y + 5 + 15 + 3, ' ', 0, 7, 50);
				continue;
			}
			if (dst == 'B')
			{
				if (topb && (A[topa - 1] > B[topb - 1]))
				{
					cct_gotoxy(0, START_Y + 5 + 15 + 3);
					cout << "������Ѵ��̷�����С����";
					Sleep(1000);
					cct_showch(0, START_Y + 5 + 15 + 3, ' ', 0, 7, 50);
					continue;
				}
			}
			else
			{
				if (topc && (A[topa - 1] > C[topc - 1]))
				{
					cct_gotoxy(0, START_Y + 5 + 15 + 3);
					cout << "������Ѵ��̷�����С����";
					Sleep(1000);
					cct_showch(0, START_Y + 5 + 15 + 3, ' ', 0, 7, 50);
					continue;
				}
			}
		}
		if (src == 'B')
		{
			if (topb == 0)
			{
				cct_gotoxy(0, START_Y + 5 + 15 + 3);
				cout << "B���Ѿ�Ϊ�գ��޷���B�����ƶ�����";
				Sleep(1000);
				cct_showch(0, START_Y + 5 + 15 + 3, ' ', 0, 7, 50);
				continue;
			}
			if (dst == 'A')
			{
				if (topa && (B[topb - 1] > A[topa - 1]))
				{
					cct_gotoxy(0, START_Y + 5 + 15 + 3);
					cout << "������Ѵ��̷�����С����";
					Sleep(1000);
					cct_showch(0, START_Y + 5 + 15 + 3, ' ', 0, 7, 50);
					continue;
				}
			}
			else
			{
				if (topc && (B[topb - 1] > C[topc - 1]))
				{
					cct_gotoxy(0, START_Y + 5 + 15 + 3);
					cout << "������Ѵ��̷�����С����";
					Sleep(1000);
					cct_showch(0, START_Y + 5 + 15 + 3, ' ', 0, 7, 50);
					continue;
				}
			}
		}
		if (src == 'C')
		{
			if (topc == 0)
			{
				cct_gotoxy(0, START_Y + 5 + 15 + 3);
				cout << "C���Ѿ�Ϊ�գ��޷���C�����ƶ�����";
				Sleep(1000);
				cct_showch(0, START_Y + 5 + 15 + 3, ' ', 0, 7, 50);
				continue;
			}
			if (dst == 'A')
			{
				if (topa && (C[topc - 1] > A[topa - 1]))
				{
					cct_gotoxy(0, START_Y + 5 + 15 + 3);
					cout << "������Ѵ��̷�����С����";
					Sleep(1000);
					cct_showch(0, START_Y + 5 + 15 + 3, ' ', 0, 7, 50);
					continue;
				}
			}
			else
			{
				if (topb && (C[topc - 1] > B[topb - 1]))
				{
					cct_gotoxy(0, START_Y + 5 + 15 + 3);
					cout << "������Ѵ��̷�����С����";
					Sleep(1000);
					cct_showch(0, START_Y + 5 + 15 + 3, ' ', 0, 7, 50);
					continue;
				}
			}
		}
		//��ʱ������Ϸ���򣬿����ƶ�
		cct_setcursor(CURSOR_INVISIBLE);
		move_hanoi(src, dst);
		print_4_8_zongxiang(n, src, dst, 1, 8);
		print_3_4_8_hengxiang(n, src, dst, 1, 8);
		cct_setcolor();
		move_color(n, src, dst);
		cct_setcolor();
		if (Dst == 'A')
		{
			int i = 0;
			for (; i < n; i++)
			{
				if (test[i] != A[i])
					break;
			}
			if (i == n)
			{
				cct_gotoxy(0, START_Y + 5 + 15 + 3);
				cout << "��ϲ�����ƶ��ɹ�����Ϸ����������";
				break;
			}
			else
				continue;
		}
		if (Dst == 'B')
		{
			int i = 0;
			for (; i < n; i++)
			{
				if (test[i] != B[i])
					break;
			}
			if (i == n)
			{
				cct_gotoxy(0, START_Y + 5 + 15 + 3);
				cout << "��ϲ�����ƶ��ɹ�����Ϸ����������";
				break;
			}
		}
		if (Dst == 'C')
		{
			int i = 0;
			for (; i < n; i++)
			{
				if (test[i] != C[i])
					break;
			}
			if (i == n)
			{
				cct_gotoxy(0, START_Y + 5 + 15 + 3);
				cout << "��ϲ�����ƶ��ɹ�����Ϸ����������";
				break;
			}
		}
	}
	clear_array();
	cct_setcolor();
	cct_gotoxy(0, 38);
	cct_setcursor(CURSOR_VISIBLE_NORMAL);
	cout << "���س�������";
	huiche_conti();
}

/***************************************************************************
  �������ƣ�print
  ��    �ܣ�print�����Ƕ�Ӧ���ܵĴ�ӡ����
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void print_1(int n, char src, char dst)
{
	cout << n << "#" << " ";
	cout << src << "---->" << dst << endl;
}

void print_2(int n, char src, char dst)
{
	cout << "��" << setw(4) << ++length << " " << "��" << "(" << setw(2) << n << "#: ";
	cout << src << "-->" << dst << ")" << endl;
}

void print_3_4_8_hengxiang(int n, char src, char dst, int select_chushi, int locate)
{
	if (locate == 4)
		cct_gotoxy(0, START_Y + 5);
	else if (locate == 8)
		cct_gotoxy(0, START_Y + 5 + 15);
	if (select_chushi == 1)
	{
		cout << "��" << setw(4) << ++length << " " << "��" << "(" << setw(2) << n << "#: ";
		cout << src << "-->" << dst << ")  ";
	}
	else {
		cout << "��ʼ:  ";
		if (locate == 3)
			cout << "                ";
	}
	cout << "A:";
	for (int i = 0; i < topa; i++)
	{
		if (A[i] == 10)
		{
			cout << A[i];
			continue;
		}
		if (A[i] != 0)
			cout << " " << A[i];
	}
	cout << setw(21 - 2 * topa) << " ";
	cout << "B:";
	for (int i = 0; i < topb; i++)
	{
		if (B[i] == 10)
		{
			cout << B[i];
			continue;
		}
		if (B[i] != 0)
			cout << " " << B[i];
	}
	cout << setw(21 - 2 * topb) << " ";
	cout << "C:";
	for (int i = 0; i < topc; i++)
	{
		if (C[i] == 10)
		{
			cout << C[i];
			continue;
		}
		if (C[i] != 0)
			cout << " " << C[i];
	}
	if (topc != 10)
		cout << setw(20 - 2 * topc) << " ";

	cout << endl;
}

void print_4_8_zongxiang(int n, char src, char dst, int select_chushi, int locate)
{
	if (select_chushi == 0) {
		if (locate == 4) {
			cct_gotoxy(START_X, START_Y);
			cout << "=========================" << endl;
			cct_gotoxy(START_X + 2, START_Y + 1);
			cout << "A         B         C" << endl;
			for (int i = 0; i < topa; i++)
			{
				cct_gotoxy(A_locate_X - 1, START_Y - 1 - i);
				cout << setw(2) << A[i];
			}
			for (int i = 0; i < topb; i++)
			{
				cct_gotoxy(B_locate_X - 1, START_Y - 1 - i);
				cout << setw(2) << B[i];
			}
			for (int i = 0; i < topc; i++)
			{
				cct_gotoxy(C_locate_X - 1, START_Y - 1 - i);
				cout << setw(2) << C[i];
			}
		}
		else {
			cct_gotoxy(START_X, START_Y + 17);
			cout << "=========================" << endl;
			cct_gotoxy(START_X + 2, START_Y + 18);
			cout << "A         B         C" << endl;
			for (int i = 0; i < topa; i++)
			{
				cct_gotoxy(A_locate_X - 1, START_Y - 1 - i + 17);
				cout << setw(2) << A[i];
			}
			for (int i = 0; i < topb; i++)
			{
				cct_gotoxy(B_locate_X - 1, START_Y - 1 - i + 17);
				cout << setw(2) << B[i];
			}
			for (int i = 0; i < topc; i++)
			{
				cct_gotoxy(C_locate_X - 1, START_Y - 1 - i + 17);
				cout << setw(2) << C[i];
			}
		}
	}
	else
	{
		if (src == 'A') {
			if (locate == 4) {
				cct_gotoxy(A_locate_X - 1, START_Y - topa - 1);
				putchar(' ');
				putchar(' ');
				if (dst == 'B') {
					cct_gotoxy(B_locate_X - 1, START_Y - topb);
					cout << setw(2) << B[topb - 1];
				}
				else {
					cct_gotoxy(C_locate_X - 1, START_Y - topc);
					cout << setw(2) << C[topc - 1];
				}
			}
			else {
				cct_gotoxy(A_locate_X - 1, START_Y - topa - 1 + 17);
				putchar(' ');
				putchar(' ');
				if (dst == 'B') {
					cct_gotoxy(B_locate_X - 1, START_Y - topb + 17);
					cout << setw(2) << B[topb - 1];
				}
				else {
					cct_gotoxy(C_locate_X - 1, START_Y - topc + 17);
					cout << setw(2) << C[topc - 1];
				}
			}
		}
		else if (src == 'B') {
			if (locate == 4) {
				cct_gotoxy(B_locate_X - 1, START_Y - topb - 1);
				putchar(' ');
				putchar(' ');
				if (dst == 'A') {
					cct_gotoxy(A_locate_X - 1, START_Y - topa);
					cout << setw(2) << A[topa - 1];
				}
				else {
					cct_gotoxy(C_locate_X - 1, START_Y - topc);
					cout << setw(2) << C[topc - 1];
				}
			}
			else {
				cct_gotoxy(B_locate_X - 1, START_Y - topb - 1 + 17);
				putchar(' ');
				putchar(' ');
				if (dst == 'A') {
					cct_gotoxy(A_locate_X - 1, START_Y - topa + 17);
					cout << setw(2) << A[topa - 1];
				}
				else {
					cct_gotoxy(C_locate_X - 1, START_Y - topc + 17);
					cout << setw(2) << C[topc - 1];
				}
			}
		}
		else
		{
			if (locate == 4) {
				cct_gotoxy(C_locate_X - 1, START_Y - topc - 1);
				putchar(' ');
				putchar(' ');
				if (dst == 'A') {
					cct_gotoxy(A_locate_X - 1, START_Y - topa);
					cout << setw(2) << A[topa - 1];
				}
				else {
					cct_gotoxy(B_locate_X - 1, START_Y - topb);
					cout << setw(2) << B[topb - 1];
				}
			}
			else {
				cct_gotoxy(C_locate_X - 1, START_Y - topc - 1 + 17);
				putchar(' ');
				putchar(' ');
				if (dst == 'A') {
					cct_gotoxy(A_locate_X - 1, START_Y - topa + 17);
					cout << setw(2) << A[topa - 1];
				}
				else {
					cct_gotoxy(B_locate_X - 1, START_Y - topb + 17);
					cout << setw(2) << B[topb - 1];
				}
			}
		}
	}
}

void print_5()
{
	int x = 0;
	for (x = 0; x < 23; x++)
	{
		cct_showch(x + 2, 17, ' ', 14, 14, 1);
		cct_showch(x + 23 + 2 + 10, 17, ' ', 14, 14, 1);
		cct_showch(x + 46 + 2 + 20, 17, ' ', 14, 14, 1);
	}
	int y = 0;
	for (y = 12; y > 0; y--)
	{
		cct_showch(A_locate_X_color, y + 4, ' ', 14, 15, 1);
		cct_showch(B_locate_X_color, y + 4, ' ', 14, 14, 1);
		cct_showch(C_locate_X_color, y + 4, ' ', 14, 14, 1);
		Sleep(100);
	}
}

void print_6(int n, char src, char tmp, char dst)
{
	print_5();
	int x = 0;
	if (src == 'A')
	{
		for (int i = 0; i < topa; i++)
		{
			cct_showch(A_locate_X_color - A[i], 16 - i, ' ', A[i], A[i], 2 * A[i] + 1);
			Sleep(200);
		}
	}
	else if (src == 'B')
	{
		for (int i = 0; i < topb; i++)
		{
			cct_showch(B_locate_X_color - B[i], 16 - i, ' ', B[i], B[i], 2 * B[i] + 1);
			Sleep(200);
		}
	}
	else
	{
		for (int i = 0; i < topc; i++)
		{
			cct_showch(C_locate_X_color - C[i], 16 - i, ' ', C[i], C[i], 2 * C[i] + 1);
			Sleep(200);
		}
	}

}

/***************************************************************************
  �������ƣ�move_color
  ��    �ܣ�ʵ��Բ���ƶ�����ʾ
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void move_color(int n, char src, char dst)
{
	if (src == 'A' && dst == 'B')
	{
		for (int i = topa; i <= 15; i++)
		{
			cct_showch(A_locate_X_color - B[topb - 1], 16 - i, ' ', B[topb - 1], B[topb - 1], 2 * B[topb - 1] + 1);
			if (yanshi)
				Sleep(change_yanshi_ms());
			else
				Sleep(20);
			if (i <= 15)
			{
				cct_showch(A_locate_X_color - B[topb - 1], 16 - i, ' ', COLOR_BLACK, COLOR_WHITE, 2 * B[topb - 1] + 1);
				if (i < 12)
					cct_showch(A_locate_X_color, 16 - i, ' ', 14, 14, 1);
			}
		}
		for (int i = A_locate_X_color - B[topb - 1]; i <= B_locate_X_color - B[topb - 1]; i++)
		{
			cct_showch(i, 1, ' ', B[topb - 1], B[topb - 1], 2 * B[topb - 1] + 1);
			if (yanshi)
				Sleep(change_yanshi_ms());
			else
				Sleep(20);
			if (i <= B_locate_X_color)
			{
				cct_showch(i, 1, ' ', COLOR_BLACK, COLOR_WHITE, 2 * B[topb - 1] + 1);
			}
		}
		for (int i = 1; i <= 17 - topb; i++)
		{
			cct_showch(B_locate_X_color - B[topb - 1], i, ' ', B[topb - 1], B[topb - 1], 2 * B[topb - 1] + 1);
			if (yanshi)
				Sleep(change_yanshi_ms());
			else
				Sleep(20);
			if (i < 17 - topb)
			{
				cct_showch(B_locate_X_color - B[topb - 1], i, ' ', COLOR_BLACK, COLOR_WHITE, 2 * B[topb - 1] + 1);
				if (i >= 5)
					cct_showch(B_locate_X_color, i, ' ', 14, 14, 1);
			}
		}
	}
	if (src == 'A' && dst == 'C')
	{
		for (int i = topa; i <= 15; i++)
		{
			cct_showch(A_locate_X_color - C[topc - 1], 16 - i, ' ', C[topc - 1], C[topc - 1], 2 * C[topc - 1] + 1);
			if (yanshi)
				Sleep(change_yanshi_ms());
			else
				Sleep(20);
			if (i <= 15)
			{
				cct_showch(A_locate_X_color - C[topc - 1], 16 - i, ' ', COLOR_BLACK, COLOR_WHITE, 2 * C[topc - 1] + 1);
				if (i < 12)
					cct_showch(A_locate_X_color, 16 - i, ' ', 14, 14, 1);
			}
		}
		for (int i = A_locate_X_color - C[topc - 1]; i <= C_locate_X_color - C[topc - 1]; i++)
		{
			cct_showch(i, 1, ' ', C[topc - 1], C[topc - 1], 2 * C[topc - 1] + 1);
			if (yanshi)
				Sleep(change_yanshi_ms());
			else
				Sleep(20);
			if (i <= C_locate_X_color)
			{
				cct_showch(i, 1, ' ', COLOR_BLACK, COLOR_WHITE, 2 * C[topc - 1] + 1);
			}
		}
		for (int i = 1; i <= 17 - topc; i++)
		{
			cct_showch(C_locate_X_color - C[topc - 1], i, ' ', C[topc - 1], C[topc - 1], 2 * C[topc - 1] + 1);
			if (yanshi)
				Sleep(change_yanshi_ms());
			else
				Sleep(20);
			if (i < 17 - topc)
			{
				cct_showch(C_locate_X_color - C[topc - 1], i, ' ', COLOR_BLACK, COLOR_WHITE, 2 * C[topc - 1] + 1);
				if (i >= 5)
					cct_showch(C_locate_X_color, i, ' ', 14, 14, 1);
			}
		}
	}
	if (src == 'B' && dst == 'C')
	{
		for (int i = topb; i <= 15; i++)
		{
			cct_showch(B_locate_X_color - C[topc - 1], 16 - i, ' ', C[topc - 1], C[topc - 1], 2 * C[topc - 1] + 1);
			if (yanshi)
				Sleep(change_yanshi_ms());
			else
				Sleep(20);
			if (i <= 15)
			{
				cct_showch(B_locate_X_color - C[topc - 1], 16 - i, ' ', COLOR_BLACK, COLOR_WHITE, 2 * C[topc - 1] + 1);
				if (i < 12)
					cct_showch(B_locate_X_color, 16 - i, ' ', 14, 14, 1);
			}
		}
		for (int i = B_locate_X_color - C[topc - 1]; i <= C_locate_X_color - C[topc - 1]; i++)
		{
			cct_showch(i, 1, ' ', C[topc - 1], C[topc - 1], 2 * C[topc - 1] + 1);
			if (yanshi)
				Sleep(change_yanshi_ms());
			else
				Sleep(20);
			if (i <= C_locate_X_color)
			{
				cct_showch(i, 1, ' ', COLOR_BLACK, COLOR_WHITE, 2 * C[topc - 1] + 1);
			}
		}
		for (int i = 1; i <= 17 - topc; i++)
		{
			cct_showch(C_locate_X_color - C[topc - 1], i, ' ', C[topc - 1], C[topc - 1], 2 * C[topc - 1] + 1);
			if (yanshi)
				Sleep(change_yanshi_ms());
			else
				Sleep(20);
			if (i < 17 - topc)
			{
				cct_showch(C_locate_X_color - C[topc - 1], i, ' ', COLOR_BLACK, COLOR_WHITE, 2 * C[topc - 1] + 1);
				if (i >= 5)
					cct_showch(C_locate_X_color, i, ' ', 14, 14, 1);
			}
		}
	}
	if (src == 'B' && dst == 'A')
	{
		for (int i = topb; i <= 15; i++)
		{
			cct_showch(B_locate_X_color - A[topa - 1], 16 - i, ' ', A[topa - 1], A[topa - 1], 2 * A[topa - 1] + 1);
			if (yanshi)
				Sleep(change_yanshi_ms());
			else
				Sleep(20);
			if (i <= 15)
			{
				cct_showch(B_locate_X_color - A[topa - 1], 16 - i, ' ', COLOR_BLACK, COLOR_WHITE, 2 * A[topa - 1] + 1);
				if (i < 12)
					cct_showch(B_locate_X_color, 16 - i, ' ', 14, 14, 1);
			}
		}
		for (int i = B_locate_X_color - A[topa - 1]; i >= A_locate_X_color + A[topa - 1]; i--)
		{
			cct_showch(i, 1, ' ', A[topa - 1], A[topa - 1], 2 * A[topa - 1] + 1);
			if (yanshi)
				Sleep(change_yanshi_ms());
			else
				Sleep(20);
			if (i >= A_locate_X_color)
			{
				cct_showch(i, 1, ' ', COLOR_BLACK, COLOR_WHITE, 2 * A[topa - 1] + 1);
			}
		}
		for (int i = 1; i <= 17 - topa; i++)
		{
			cct_showch(A_locate_X_color - A[topa - 1], i, ' ', A[topa - 1], A[topa - 1], 2 * A[topa - 1] + 1);
			if (yanshi)
				Sleep(change_yanshi_ms());
			else
				Sleep(20);
			if (i < 17 - topa)
			{
				cct_showch(A_locate_X_color - A[topa - 1], i, ' ', COLOR_BLACK, COLOR_WHITE, 2 * A[topa - 1] + 1);
				if (i >= 5)
					cct_showch(A_locate_X_color, i, ' ', 14, 14, 1);
			}
		}
	}
	if (src == 'C' && dst == 'A')
	{
		for (int i = topc; i <= 15; i++)
		{
			cct_showch(C_locate_X_color - A[topa - 1], 16 - i, ' ', A[topa - 1], A[topa - 1], 2 * A[topa - 1] + 1);
			if (yanshi)
				Sleep(change_yanshi_ms());
			else
				Sleep(20);
			if (i <= 15)
			{
				cct_showch(C_locate_X_color - A[topa - 1], 16 - i, ' ', COLOR_BLACK, COLOR_WHITE, 2 * A[topa - 1] + 1);
				if (i < 12)
					cct_showch(C_locate_X_color, 16 - i, ' ', 14, 14, 1);
			}
		}
		for (int i = C_locate_X_color - A[topa - 1]; i >= A_locate_X_color + A[topa - 1]; i--)
		{
			cct_showch(i, 1, ' ', A[topa - 1], A[topa - 1], 2 * A[topa - 1] + 1);
			if (yanshi)
				Sleep(change_yanshi_ms());
			else
				Sleep(20);
			if (i >= A_locate_X_color)
			{
				cct_showch(i, 1, ' ', COLOR_BLACK, COLOR_WHITE, 2 * A[topa - 1] + 1);
			}
		}
		for (int i = 1; i <= 17 - topa; i++)
		{
			cct_showch(A_locate_X_color - A[topa - 1], i, ' ', A[topa - 1], A[topa - 1], 2 * A[topa - 1] + 1);
			if (yanshi)
				Sleep(change_yanshi_ms());
			else
				Sleep(20);
			if (i < 17 - topa)
			{
				cct_showch(A_locate_X_color - A[topa - 1], i, ' ', COLOR_BLACK, COLOR_WHITE, 2 * A[topa - 1] + 1);
				if (i >= 5)
					cct_showch(A_locate_X_color, i, ' ', 14, 14, 1);
			}
		}
	}
	if (src == 'C' && dst == 'B')
	{
		for (int i = topc; i <= 15; i++)
		{
			cct_showch(C_locate_X_color - B[topb - 1], 16 - i, ' ', B[topb - 1], B[topb - 1], 2 * B[topb - 1] + 1);
			if (yanshi)
				Sleep(change_yanshi_ms());
			else
				Sleep(20);
			if (i <= 15)
			{
				cct_showch(C_locate_X_color - B[topb - 1], 16 - i, ' ', COLOR_BLACK, COLOR_WHITE, 2 * B[topb - 1] + 1);
				if (i < 12)
					cct_showch(C_locate_X_color, 16 - i, ' ', 14, 14, 1);
			}
		}
		for (int i = C_locate_X_color - B[topb - 1]; i >= B_locate_X_color + B[topb - 1]; i--)
		{
			cct_showch(i, 1, ' ', B[topb - 1], B[topb - 1], 2 * B[topb - 1] + 1);
			if (yanshi)
				Sleep(change_yanshi_ms());
			else
				Sleep(20);
			if (i >= B_locate_X_color)
			{
				cct_showch(i, 1, ' ', COLOR_BLACK, COLOR_WHITE, 2 * B[topb - 1] + 1);
			}
		}
		for (int i = 1; i <= 17 - topb; i++)
		{
			cct_showch(B_locate_X_color - B[topb - 1], i, ' ', B[topb - 1], B[topb - 1], 2 * B[topb - 1] + 1);
			if (yanshi)
				Sleep(change_yanshi_ms());
			else
				Sleep(20);
			if (i < 17 - topb)
			{
				cct_showch(B_locate_X_color - B[topb - 1], i, ' ', COLOR_BLACK, COLOR_WHITE, 2 * B[topb - 1] + 1);
				if (i >= 5)
					cct_showch(B_locate_X_color, i, ' ', 14, 14, 1);
			}
		}
	}
}


