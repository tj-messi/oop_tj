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
bool check_same(int mp[12][12], int vis[12][12], int r, int c)
{
	bool flag = false;
	int dx[] = { 1,-1,0,0 };
	int dy[] = { 0,0,1,-1 };
	for (int i = 0; i < r; i++)
	{
		for (int j = 0; j < c; j++)
		{
			for (int k = 0; k <= 3; k++)
			{
				if (!(i + dx[k] >= 0 && i + dx[k] < r && j + dy[k] >= 0 && j + dy[k] < c))continue;
				if (mp[i][j] == mp[i + dx[k]][j + dy[k]]&&mp[i][j]!=0)
				{
					vis[i][j] = 1;
					flag = true;
				}
			}
		}
	}
	return flag;
}
void replace0(int mp[12][12], int flag[12][12], int same[12][12], int r, int c, int x, int y)
{
	if (flag[x][y] == 1)return;
	flag[x][y] = 1;
	int dx[] = { 1,-1,0,0 };
	int dy[] = { 0,0,1,-1 };
	for (int i = 0; i <= 3; i++)
	{
		int nx = x + dx[i], ny = y + dy[i];
		if (mp[x][y] == mp[nx][ny] && nx >= 0 && nx < r && ny >= 0 && ny < c)
		{
			replace0(mp, flag, same, r, c, nx, ny);
		}
	}
	same[x][y] = 0;
}

int main()
{
	cct_setconsoleborder(120, 40, 120, 9000);
	cct_setcursor(CURSOR_INVISIBLE);
	srand((unsigned)time(NULL));
	int mp[12][12];//��ͼ
	int vis[12][12];//�ɵ��������������
	int score = 0;
	memset(mp, 0, sizeof mp);
	memset(vis, 0, sizeof vis);
	int r, c;
	cct_cls();
	while (1)
	{
		cout << "����������(8-10)��" << endl;
		cin >> r;
		if (!cin.good() || r > 10 || r < 8)
		{
			cin.clear();
			cin.ignore(9999, '\n');
			continue;
		}
		break;
	}
	while (1)
	{
		cout << "����������(8-10)��" << endl;
		cin >> c;
		if (!cin.good() || c > 10 || c < 8)
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
	gmw_set_font(&MyCGI, "������", 16, 0);
	gmw_set_rowno_switch(&MyCGI, false);					//��ʾ�к�
	gmw_set_colno_switch(&MyCGI, false);					//��ʾ�б�
	gmw_set_frame_style(&MyCGI, 6, 3, true);			//��������С��
	gmw_set_color(&MyCGI, COLOR_BLACK, COLOR_HWHITE); //�ı���ɫ
	gmw_set_frame_color(&MyCGI, COLOR_HWHITE, COLOR_BLACK);
	gmw_set_frame_default_linetype(&MyCGI, 2);			//�߽����ʲô����

	gmw_set_block_border_switch(&MyCGI, true);

	gmw_set_status_line_switch(&MyCGI, TOP_STATUS_LINE, true);//������״̬������
	gmw_set_status_line_switch(&MyCGI, LOWER_STATUS_LINE, true);//������״̬������

	//test
	gmw_draw_frame(&MyCGI);

	sprintf(temp1, "%d�� %d��", (MyCGI.lines), MyCGI.cols);
	sprintf(temp2, "%s %d", "Ŀǰ�÷֣� ", score);
	gmw_status_line(&MyCGI, TOP_STATUS_LINE, temp2, temp1);//�ϴ�ӡ

	/* ����1-5�������ú�����ʽ��ʾ�ڽ����ϣ�����״̬�� */
	const BLOCK_DISPLAY_INFO bdi_normal[] = {
		{0, -1, -1, "  "},  //0����ʾ���ÿո���伴��
		{1, COLOR_HBLUE, COLOR_BLACK, "��"},
		{2, COLOR_HGREEN, COLOR_BLACK, "��"},
		{3, COLOR_HCYAN, COLOR_BLACK, "��"},
		{4, COLOR_HRED, COLOR_BLACK, "��"},
		{5, COLOR_HPINK, COLOR_BLACK, "��"},
		{-999, -1, -1, NULL} //�жϽ�������Ϊ-999
	};
	/* ����1-5�������ú�����ʽ��ʾ�ڽ����ϣ���ǰѡ����״̬+ѡ�к������״̬�� */
	const BLOCK_DISPLAY_INFO bdi_related[] = {
		{BDI_VALUE_BLANK, -1, -1, "  "},  //�հ�
		{1, COLOR_HBLUE, COLOR_WHITE, "��"},
		{2, COLOR_HGREEN, COLOR_WHITE, "��"},
		{3, COLOR_HCYAN, COLOR_WHITE, "��"},
		{4, COLOR_HRED, COLOR_WHITE, "��"},
		{5, COLOR_HPINK, COLOR_WHITE, "��"},
		{BDI_VALUE_END, -1, -1, NULL} //�жϽ�������Ϊ-999
	};
	/* ����1-5�������ú�����ʽ��ʾ�ڽ����ϣ�ѡ��״̬�� */
	const BLOCK_DISPLAY_INFO bdi_selected[] = {
		{BDI_VALUE_BLANK, -1, -1, "  "},  //�հ�
		{1, COLOR_HBLUE, COLOR_HWHITE, "��"},
		{2, COLOR_HGREEN, COLOR_HWHITE, "��"},
		{3, COLOR_HCYAN, COLOR_HWHITE, "��"},
		{4, COLOR_HRED, COLOR_HWHITE, "��"},
		{5, COLOR_HPINK, COLOR_HWHITE, "��"},
		{BDI_VALUE_END, -1, -1, NULL} //�жϽ�������Ϊ-999
	};

	
	while(1)//�ؿ���ѭ��
	{
		int num_0 = 0;

		for (int i = 0; i < r; i++)
		{
			for (int j = 0; j < c; j++)
			{
				initial_mp(mp, i, j, 5);
			}
		}
		for (int i = 0; i < r; i++)
		{
			for (int j = 0; j < c; j++)
			{
				gmw_draw_block(&MyCGI, i, j, mp[i][j], bdi_normal);
			}
		}

		while(1)
		{
			memset(vis, 0, sizeof vis);
			if (!check_same(mp, vis, r, c))//���û�п��������ģ�ֱ��break
			{
				sprintf(temp1, "���ؽ���ʣ��%d�����س���һ��                  ", r* c - num_0);
				score += (max(0, (10 - (r*c-num_0)) * 180));
				gmw_status_line(&MyCGI, LOWER_STATUS_LINE, temp1);//�´�ӡ
				int cmd;
				while (1)
				{
					cmd = _getch();
					if (cmd == 13)
					{
						break;
					}
				}
				break;
			}
			//�������ֱ�ӿ�������
			int Maction, Mr, Mc, Keycode1, Keycode2;
			bool have_chosen = false;//ǰһ����û��ѡ��
			int now_x = 1, now_y = 1;
			int before_x = 1, before_y = 1;//��һ��ѡ���
			bool keyboard = false;
			int now_score=0;
			//while (1)
			{
				while(1)//������ȡ������
				{
					if (!check_same(mp, vis, r, c))//���û�п��������ģ�ֱ��break
					{
						break;
					}
					if (now_score)
					{
						sprintf(temp1, "%d�� %d��", (MyCGI.lines), MyCGI.cols);
						sprintf(temp2, "%s %d %s %d %s", "���ֵ÷֣�",now_score,"Ŀǰ�÷֣�", score,"           ");
						gmw_status_line(&MyCGI, TOP_STATUS_LINE, temp2, temp1);//�ϴ�ӡ
						now_score = 0;
					}
					gmw_read_keyboard_and_mouse(&MyCGI, Maction, Mr, Mc, Keycode1, Keycode2, true);

					if (Keycode1 == 0 && Keycode2 == 0)//����Ѿ�ִ�в���
					{
						keyboard = false;
						now_x = Mr, now_y = Mc;
						if (Maction == MOUSE_RIGHT_BUTTON_CLICK)
						{
							return 0;
						}
						else if (Maction == MOUSE_LEFT_BUTTON_CLICK)//�������
						{
							if (!vis[now_x][now_y]||mp[now_x][now_y]==0)//�����Ǻ����λ��
							{
								if(mp[now_x][now_y]==0)
								{
									sprintf(temp1, "����ѡ��%c��%d��                   ", char('A' + now_x), now_y);
									gmw_status_line(&MyCGI, LOWER_STATUS_LINE, temp1);//�´�ӡ
								}
								else
								{
									sprintf(temp1, "����ѡ��%c��%d�У�����ֵͬ                   ", char('A' + now_x), now_y);
									gmw_status_line(&MyCGI, LOWER_STATUS_LINE, temp1);//�´�ӡ
								}
							}
							else
							{
								if (have_chosen)//�������
								{
									int flag[12][12];
									//int same[12][12];
									memset(flag, 0, sizeof flag);
									replace0(mp, flag, mp, r, c,now_x,now_y);
									int temp0 = 0;
									for (int i = 0; i < r; i++)
									{
										for (int j = 0; j < c; j++)
										{
											if(mp[i][j]==0)
											{
												temp0++;
												gmw_draw_block(&MyCGI, i, j, mp[i][j], bdi_normal);//���������е�
											}
										}
									}
									now_score = ( temp0-num_0 ) * (temp0 - num_0) * 5;
									score += now_score;
									num_0 = temp0;
									have_chosen = false;
								}
								else//��û���
								{
									int flag[12][12];
									int same[12][12];
									memset(same, 1, sizeof same);
									memset(flag, 0, sizeof flag);
									replace0(mp, flag,same, r, c, now_x, now_y);
									for (int i = 0; i < r; i++)
									{
										for (int j = 0; j < c; j++)
										{
											if (same[i][j] == 0)
												gmw_draw_block(&MyCGI, i, j, mp[i][j], bdi_related);//���������е�
										}
									}
									gmw_draw_block(&MyCGI, now_x, now_y, mp[now_x][now_y], bdi_selected);//���ڵĸ���ѡ��
									have_chosen = true;
								}
							}
						}
						else
						{
							//gmw_draw_block(&MyCGI, now_x, now_y, mp[now_x][now_y], bdi_related);//���ڵĴ�ѡ��
						}
					}
					else
					{
						keyboard = true;

						if (Keycode2 == KB_ARROW_DOWN)//��
						{
							now_x = (now_x + 1 < r ? now_x + 1 : now_x);
						}
						else if (Keycode2 == KB_ARROW_UP)//��
						{
							now_x = (now_x - 1 >= 0 ? now_x - 1 : now_x);
						}
						else if (Keycode2 == KB_ARROW_LEFT)//��
						{
							now_y = (now_y - 1 >= 0 ? now_y - 1 : now_y);
						}
						else if (Keycode2 == KB_ARROW_RIGHT)//��
						{
							now_y = (now_y + 1 < c ? now_y + 1 : now_y);
						}
						else if (Keycode1 == 13)//ѡ��
						{
							if (!vis[now_x][now_y] || mp[now_x][now_y] == 0)//�����Ǻ����λ��
							{
								if (mp[now_x][now_y] == 0)
								{
									sprintf(temp1, "����ѡ��%c��%d��                   ", char('A' + now_x), now_y);
									gmw_status_line(&MyCGI, LOWER_STATUS_LINE, temp1);//�´�ӡ
								}
								else
								{
									sprintf(temp1, "����ѡ��%c��%d�У�����ֵͬ                   ", char('A' + now_x), now_y);
									gmw_status_line(&MyCGI, LOWER_STATUS_LINE, temp1);//�´�ӡ
								}
							}
							else
							{
								if (have_chosen)//�������
								{
									int flag[12][12];
									//int same[12][12];
									memset(flag, 0, sizeof flag);
									int temp0 = 0;
									replace0(mp, flag, mp, r, c, now_x, now_y);
									for (int i = 0; i < r; i++)
									{
										for (int j = 0; j < c; j++)
										{
											if (mp[i][j] == 0)
											{
												temp0++;
												gmw_draw_block(&MyCGI, i, j, mp[i][j], bdi_normal);//���������е�
											}
										}
									}
									now_score = (temp0  - num_0) * (temp0 - num_0) * 5;
									score += now_score;
									num_0 = temp0;
									have_chosen = false;
								}
								else//��û���
								{
									int flag[12][12];
									int same[12][12];
									memset(same, 1, sizeof same);
									memset(flag, 0, sizeof flag);
									replace0(mp, flag, same, r, c, now_x, now_y);
									for (int i = 0; i < r; i++)
									{
										for (int j = 0; j < c; j++)
										{
											if (same[i][j] == 0)
												gmw_draw_block(&MyCGI, i, j, mp[i][j], bdi_related);//���������е�
										}
									}
									gmw_draw_block(&MyCGI, now_x, now_y, mp[now_x][now_y], bdi_selected);//���ڵĸ���ѡ��
									have_chosen = true;
								}
							}
						}
					}

					//�������ͻ�������
					{
						//����
						{
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
											gmw_move_block(&MyCGI, i - dis, j, mp[i - dis][j], 0, bdi_normal, UP_TO_DOWN, dis);
											mp[i][j] = mp[i - dis][j];
											mp[i - dis][j] = 0;
										}
									}
								}
							}
						}
						//����
						{
							int flag_no_0 = 0;
							for (int j = c - 1; j >= 0; j--)
							{
								bool full_0 = true;
								for (int i = 0; i< r; i++)
								{
									if (mp[i][j] != 0)
									{
										full_0 = false;
										if (!flag_no_0)
										{
											flag_no_0 = j;
										}
									}
								}
								if (full_0 && flag_no_0>j )//����ȫΪ0�����ұ��з�0��ֵ
								{
									for (int jj = j+1; jj < c ; jj++)//���п�ʼ���ұ���
									{
										for(int ii=0;ii<r;ii++)
										{
											if(mp[ii][jj]!=0)
											{
												gmw_move_block(&MyCGI, ii, jj, mp[ii][jj], 0, bdi_normal, RIGHT_TO_LEFT, 1);
												mp[ii][jj - 1] = mp[ii][jj];
												mp[ii][jj] = 0;
											}
										}
									}
								}
							}
						}
					}

					if (!((before_x == now_x) && (before_y == now_y)))//�ƶ���
					{
						if (have_chosen)//֮ǰѡ����
						{
							have_chosen = false;
							gmw_draw_block(&MyCGI, before_x, before_y, mp[before_x][before_y], bdi_normal);//֮ǰѡ��ı����ͨ
							int flag[12][12];
							int same[12][12];
							memset(same, 1, sizeof same);
							memset(flag, 0, sizeof flag);
							replace0(mp, flag, same, r, c, before_x, before_y);
							for (int i = 0; i < r; i++)
							{
								for (int j = 0; j < c; j++)
								{
									if (same[i][j] == 0)
										gmw_draw_block(&MyCGI, i, j, mp[i][j], bdi_normal);//ԭ����ȫ������ͨ
								}
							}
							gmw_draw_block(&MyCGI, now_x, now_y, mp[now_x][now_y], bdi_related);//���ڵĴ�ѡ��
						}
						else//֮ǰûѡ
						{
							gmw_draw_block(&MyCGI, before_x, before_y, mp[before_x][before_y], bdi_normal);//֮ǰѡ��ı����ͨ
							gmw_draw_block(&MyCGI, now_x, now_y, mp[now_x][now_y], bdi_related);//���ڵĴ�ѡ��
						}

						before_x = now_x;
						before_y = now_y;

					}
					else
					{
						/*before_x = now_x;
						before_y = now_y;*/
					}
				}
				
			}

		}
	
	
	}


}