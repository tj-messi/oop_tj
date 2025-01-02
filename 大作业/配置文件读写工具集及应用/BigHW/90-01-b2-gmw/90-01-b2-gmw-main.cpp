/*2351114 �쿡�� ������*/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <climits>
#include <conio.h>
#include <iomanip>
#include <windows.h>
#include "../include/cmd_console_tools.h"
#include"../include/base_work_fun.h"
#include "../include/cmd_gmw_tools.h"
using namespace std;

void initial_mp(int mp[12][12], int x, int y, int top)
{
	int rd = rand() % top + 1;
	mp[x][y] = rd;
}
bool check_same(int mp[12][12],int remove_mp[12][12], int r, int c)
{
	bool flag = false;
	for (int i = 0; i < r; i++)
	{
		for (int j = 0; j < c - 2; j++)
		{
			if (mp[i][j] == mp[i][j + 1] && mp[i][j + 1] == mp[i][j + 2])
			{
				remove_mp[i][j] = 1;
				remove_mp[i][j+1] = 1;
				remove_mp[i][j+2] = 1;
				flag= true;
			}
		}
	}
	for (int i = 0; i < c; i++)
	{
		for (int j = 0; j < r - 2; j++)
		{
			if (mp[j][i] == mp[j + 1][i] && mp[j + 1][i] == mp[j + 2][i])
			{
				remove_mp[j][i] = 1;
				remove_mp[j+1][i] = 1;
				remove_mp[j+2][i] = 1;
				flag = true;
			}
		}
	}
	return flag;
}
void show_potential(int mp[12][12],int remove_mp[12][12], int vis[12][12], int r, int c)
{
	//��vis��Ϊpotential_remove����ܹ��ƶ�ʵ�ֵ�����
	int dx[5] = { 0,0,1,-1 };
	int dy[5] = { 1,-1,0,0 };
	memset(vis, 0, sizeof vis);
	for (int i = 0; i < r; i++)
	{
		for (int j = 0; j < c; j++)
		{
			for (int k = 0; k < 4; k++)
			{
				int nx = i + dx[k], ny = j + dy[k];
				int temp = mp[i][j];
				if (nx < 0 || nx >= r || ny < 0 || ny >= c)
					continue;
				mp[i][j] = mp[nx][ny];
				mp[nx][ny] = temp;
				if (check_same(mp, remove_mp,r, c))
				{
					for (int ni = 1; ni <= r; ni++)
					{
						for (int nj = 1; nj <= c - 2; nj++)
						{
							if (mp[ni][nj] == mp[ni][nj + 1] && mp[ni][nj + 1] == mp[ni][nj + 2])
							{
								vis[i][j] = 1;
								vis[nx][ny] = 1;
							}
						}
					}
					for (int ni = 1; ni <= c; ni++)
					{
						for (int nj = 1; nj <= r - 2; nj++)
						{
							if (mp[nj][ni] == mp[nj + 1][ni] && mp[nj + 1][ni] == mp[nj + 2][ni])
							{
								vis[i][j] = 1;
								vis[nx][ny] = 1;
							}
						}
					}
				}
				mp[nx][ny] = mp[i][j];
				mp[i][j] = temp;
			}
		}
	}
}
int main()
{
	cct_setconsoleborder(120, 40, 120, 9000);
	cct_setcursor(CURSOR_INVISIBLE);
	srand((unsigned)time(NULL));
	int mp[12][12];
	int remove_mp[12][12];
	int potential_remove[12][12];
	memset(mp, 0, sizeof mp);
	memset(remove_mp, 0, sizeof remove_mp);
	memset(potential_remove, 0, sizeof potential_remove);
	int r, c;
	cct_cls();
	while (1)
	{
		cout << "����������(5-9)��" << endl;
		cin >> r;
		if (!cin.good() || r > 9 || r < 5)
		{
			cin.clear();
			cin.ignore(9999, '\n');
			continue;
		}
		break;
	}
	while (1)
	{
		cout << "����������(5-9)��" << endl;
		cin >> c;
		if (!cin.good() || c > 9 || c < 5)
		{
			cin.clear();
			cin.ignore(9999, '\n');
			continue;
		}
		break;
	}
	CONSOLE_GRAPHICS_INFO MyCGI; //����һ��CGI����
	char temp1[256];
	char temp2[256];
	int score = 0;
	/* ������ʼ�����������������ڴ˻����������޸Ĳ������ã��������Ԥ��ֵ
		��Ϸ��������ܣ�Ϊ10*10�����ָ��ߣ�ÿ��ɫ��Ĵ�СΪ2��*1�У�ɫ�鲻���߿�
		���ڱ���ɫ�ڣ�ǰ��ɫ��
		����Ϊ����8*16
		���߿�ɫ��ʱ����ʱ��ɫ���ƶ�ʱ��ʱ3ms
		�������Ҹ�������ȫ��Ϊ0
		��״̬�����������ı���ɫͬ���ڣ���Ŀ�ı�����ͬ���ڣ�ǰ��Ϊ����
		��״̬�����������ı���ɫͬ���ڣ���Ŀ�ı�����ͬ���ڣ�ǰ��Ϊ����
		����ʾ�к�
		����ʾ�б�
		��Ϸ����Ϊ˫�߿򣬴��ָ��ߣ�ɫ���СΪ2�����2��=1�����֣�*1���߶�1�У�����ɫͬ����
		ɫ��Ϊ˫���ߣ���ɫ��δ�꣩*/		
	gmw_init(&MyCGI);
	gmw_set_rowcol(&MyCGI, r, c);
	gmw_set_font(&MyCGI, "������", 24, 18);
	gmw_set_rowno_switch(&MyCGI, false);					//��ʾ�к�
	gmw_set_colno_switch(&MyCGI, false);					//��ʾ�б�
	gmw_set_frame_style(&MyCGI, 2, 1, true);			//��������С��
	gmw_set_color(&MyCGI,COLOR_BLACK ,COLOR_HWHITE); //�ı���ɫ
	gmw_set_frame_color(&MyCGI, COLOR_HWHITE, COLOR_BLACK);
	gmw_set_frame_default_linetype(&MyCGI, 1);			//�߽����ʲô����



	gmw_set_status_line_switch(&MyCGI, TOP_STATUS_LINE, true);//������״̬������
	gmw_set_status_line_switch(&MyCGI, LOWER_STATUS_LINE, true);//������״̬������

	//test
	gmw_draw_frame(&MyCGI);
	sprintf(temp1, "%d�� %d��", (MyCGI.lines), MyCGI.cols);
	sprintf(temp2, "%s %d", "Ŀǰ�÷֣� ",score);
	gmw_status_line(&MyCGI, TOP_STATUS_LINE,  temp2,temp1);//�ϴ�ӡ

	gmw_status_line(&MyCGI, LOWER_STATUS_LINE, "����End����", "���Խ�����");//�´�ӡ
	

	/* ����1-7�������ú�����ʽ��ʾ�ڽ�����
	   - ע��1���������ý�������+ѡ�С���Ϣ����һ�������еķ���
				1-7��ʾ������11-17��ʾѡ��
			 2��ʵ��ʵ���е�����ֵ��Ҫ����ˣ��˴�������Ϊ��ɫ��Ĳ�ͬ״̬����ʾ
			  3���� test_magic_ball ����������һ�ַ�ʽ��ʾɫ��Ĳ�ͬ״̬�����Զ��� */
	const BLOCK_DISPLAY_INFO bdi[] = {
		{BDI_VALUE_BLANK, -1, -1, "  "},  //0����ʾ���ÿո���伴��
		{1,  COLOR_HBLACK, -1, "��"},	//����״̬����1����Ӧ�Ĳ���
		{2,  COLOR_YELLOW, -1, "��"},
		{3,  COLOR_HGREEN, -1, "��"},
		{4,  COLOR_HCYAN, -1, "��"},
		{5,  COLOR_HRED, -1, "��"},
		{6,  COLOR_HPINK, -1, "��"},
		{7,  COLOR_HYELLOW, -1, "��"},
		{11, COLOR_HBLACK, -1, "��"},//ѡ��״̬����1����Ӧ�Ĳ���ͼ��
		{12, COLOR_YELLOW, -1, "��"},
		{13, COLOR_HGREEN, -1, "��"},
		{14, COLOR_HCYAN, -1, "��"},
		{15, COLOR_HRED, -1, "��"},
		{16, COLOR_HPINK, -1, "��"},
		{17, COLOR_HYELLOW, -1, "��"},
		{21, COLOR_HBLACK, -1, "��"},//������״̬����1����Ӧ�Ĳ���ͼ��
		{22, COLOR_YELLOW, -1, "��"},
		{23, COLOR_HGREEN, -1, "��"},
		{24, COLOR_HCYAN, -1, "��"},
		{25, COLOR_HRED, -1, "��"},
		{26, COLOR_HPINK, -1, "��"},
		{27, COLOR_HYELLOW, -1, "��"},
		{31, COLOR_HBLACK, -1, "��"},//������״̬�����߽ǣ�����1����Ӧ�Ĳ���ͼ��
		{32, COLOR_YELLOW, -1, "��"},
		{33, COLOR_HGREEN, -1, "��"},
		{34, COLOR_HCYAN, -1, "��"},
		{35, COLOR_HRED, -1, "��"},
		{36, COLOR_HPINK, -1, "��"},
		{37, COLOR_HYELLOW, -1, "��"},
		{41, COLOR_HBLACK, 15, "��"},//ѡ��״̬���ҵ������1����Ӧ�Ĳ���ͼ��
		{42, COLOR_YELLOW, 15, "��"},
		{43, COLOR_HGREEN, 15, "��"},
		{44, COLOR_HCYAN, 15, "��"},
		{45, COLOR_HRED, 15, "��"},
		{46, COLOR_HPINK, 15, "��"},
		{47, COLOR_HYELLOW, 15, "��"},
		{BDI_VALUE_END, -1, -1, NULL} //�жϽ�������Ϊ-999
	};
	const int BDI_NORMAL = 0, BDI_SELECTED = 10 ,BDI_REMOVE = 20,BDI_REMOVE_COR =30, BDI_SELECTED_WHITE=40;//һ����û�б�ѡ��Ļ���ֵ��һ���Ǳ�ѡ���˵Ļ�ֵ��һ���Ǳ������Ļ�ֵ

	for (int i = 0; i < r; i++)
	{
		for (int j = 0; j < c; j++)
		{
			initial_mp(mp, i, j, 7);
		}
	}
	for (int i = 0; i < r; i++)
	{
		for (int j = 0; j < c; j++)
		{
			gmw_draw_block(&MyCGI, i, j, BDI_NORMAL + mp[i][j], bdi);
		}
	}

	//��ʼ��Ϸ
	while (1)
	{
		while (check_same(mp,remove_mp, r, c))//�����ڿ�������������
		{
			//�ȱ��
			for (int i = 0; i < r; i++)
			{
				for (int j = 0; j < c; j++)
				{
					if (remove_mp[i][j] == 1)
					{
						score++;
						gmw_draw_block(&MyCGI, i, j, BDI_REMOVE + mp[i][j], bdi);
					}
				}
			}
			//����˸����
			for (int i = 0; i < r; i++)
			{
				for (int j = 0; j < c; j++)
				{
					if (remove_mp[i][j] == 1)
					{
						for (int k = 1; k <= 3; k++)//��˸����
						{
							gmw_draw_block(&MyCGI, i, j, BDI_REMOVE_COR + mp[i][j], bdi);
							Sleep(100);
							gmw_draw_block(&MyCGI, i, j, BDI_REMOVE + mp[i][j], bdi);
							Sleep(100);
						}
						gmw_draw_block(&MyCGI, i, j, BDI_VALUE_BLANK, bdi);
						mp[i][j] = 0;
					}
				}
			}
			memset(remove_mp, 0, sizeof remove_mp);

			sprintf(temp1, "%d�� %d��", (MyCGI.lines), MyCGI.cols);
			sprintf(temp2, "%s %d", "Ŀǰ�÷֣� ", score);
			gmw_status_line(&MyCGI, TOP_STATUS_LINE, temp2, temp1);//�ϴ�ӡ

			for (int i = r - 1; i >= 0; i--)
			{
				for (int j = 0; j < c; j++)
				{
					if (mp[i][j] == 0)
					{
						int dis = 0;
						while (i - dis >= 0 && mp[i - dis][j] == 0)
						{
							dis++;
						}
						if (i - dis < 0)//ͷ��ȫ��0
							continue;
						else//ͷ���з���Ŀ��Խ���
						{
							gmw_move_block(&MyCGI, i - dis, j, mp[i - dis][j], 0, bdi, UP_TO_DOWN, dis);
							mp[i][j] = mp[i - dis][j];
							mp[i - dis][j] = 0;
						}
					}
				}
			}
			for (int i = 0; i < r; i++)
			{
				for (int j = 0; j < c; j++)
				{
					if (mp[i][j] == 0)
					{
						initial_mp(mp, i, j, 7);
						gmw_draw_block(&MyCGI, i, j, BDI_NORMAL + mp[i][j], bdi);
					}
				}
			}

		}//�����ɾ�Ϊֹ
		//�����û�пɽ�����������
		memset(potential_remove, 0, sizeof potential_remove);
		show_potential(mp, remove_mp, potential_remove, r, c);
		bool end_flag = true;
		for (int i = 0; i < r; i++)
		{
			for (int j = 0; j < c; j++)
			{
				if (potential_remove[i][j] == 1)
				{
					gmw_draw_block(&MyCGI, i, j, BDI_SELECTED + mp[i][j], bdi);
					end_flag = false;
				}
				else
				{
					gmw_draw_block(&MyCGI, i, j, BDI_NORMAL + mp[i][j], bdi);
				}
			}
		}

		if (end_flag)
		{
			break;
		}

		int Maction, Mr, Mc, Keycode1, Keycode2;
		bool have_chosen = false;//ǰһ����û��ѡ��
		int before_x=-1, before_y=-1;//��һ��ѡ���
		while(1)//������ȡ������
		{
			gmw_read_keyboard_and_mouse(&MyCGI, Maction, Mr, Mc, Keycode1, Keycode2, true);
			if (Maction == MOUSE_RIGHT_BUTTON_CLICK)
			{
				return 0;
			}
			if (Maction == MOUSE_LEFT_BUTTON_CLICK)
			{
				if (!potential_remove[Mr][Mc])//���Ǻ��ʵĵ�
				{
					sprintf(temp1, "����ѡ��%c��%d��                   ", char('A' + Mr), Mc);
					gmw_status_line(&MyCGI, LOWER_STATUS_LINE, temp1);//�´�ӡ

					if (have_chosen)
					{
						gmw_draw_block(&MyCGI, before_x, before_y, BDI_SELECTED + mp[before_x][before_y], bdi);
						have_chosen = false;
					}
				}
				else//�ǿ���ѡ��ĵ�
				{
					if (have_chosen)//֮ǰѡ�����
					{
						if (before_x == Mr && before_y == Mc)//�ڶ���ѡ����ͬλ�ò���
							continue;
						else if (abs(before_x - Mr) + abs(before_y - Mc) > 1)//����ѡ�񲢲�������
						{
							gmw_draw_block(&MyCGI, before_x, before_y, BDI_NORMAL + mp[before_x][before_y], bdi);
							gmw_draw_block(&MyCGI, Mr, Mc, BDI_SELECTED_WHITE + mp[Mr][Mc], bdi);
							before_x = Mr, before_y = Mc;//����ѡ��ڶ��ν���whileѭ������ϴ�ѡ��
						}
						else//ѡ��������ڵ�
						{
							int useless[12][12];
							int temp = mp[before_x][before_y];
							mp[before_x][before_y] = mp[Mr][Mc];
							mp[Mr][Mc] = temp;
							//�Ƚ������ж��������ǲ��ǿɽ������ݣ�����֮����������
							if (check_same(mp, useless, r, c))
							{
								gmw_draw_block(&MyCGI, Mr, Mc, BDI_NORMAL + mp[Mr][Mc], bdi);
								gmw_draw_block(&MyCGI, before_x, before_y, BDI_NORMAL + mp[before_x][before_y], bdi);
								memset(remove_mp, 0, sizeof remove_mp);
								break;//���������ˣ����½���һ��ѭ��
							}
							else//���������Ҫ��������
							{
								int temp = mp[before_x][before_y];
								mp[before_x][before_y] = mp[Mr][Mc];
								mp[Mr][Mc] = temp;

								sprintf(temp1, "%c��%d��  �� %c��%d�� �޷�������            ", char('A' + Mr), Mc ,char('A'+before_x),before_y);
								gmw_status_line(&MyCGI, LOWER_STATUS_LINE, temp1);//�´�ӡ

								have_chosen = false;

								gmw_draw_block(&MyCGI, Mr, Mc, BDI_SELECTED + mp[Mr][Mc], bdi);
								gmw_draw_block(&MyCGI, before_x, before_y, BDI_SELECTED + mp[before_x][before_y], bdi);

							}

						}
					}
					else
					{
						gmw_draw_block(&MyCGI, Mr, Mc, BDI_SELECTED_WHITE + mp[Mr][Mc], bdi);
						have_chosen = true;//�Ѿ�ѡ��
						before_x = Mr, before_y = Mc;//����ѡ��ڶ��ν���whileѭ������ϴ�ѡ��
					}
				}
			}

		}

	}

}