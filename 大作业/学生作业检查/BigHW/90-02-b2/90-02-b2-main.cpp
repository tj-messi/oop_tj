/*2351114 �쿡�� ������*/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <climits>
#include <conio.h>
#include<ctime>
#include <iomanip>
#include <windows.h>
#include "../include/cmd_console_tools.h"
#include"../include/base_work_fun.h"
#include "../include/cmd_gmw_tools.h"
using namespace std;

void check_show(int x, int y, int r, int c, int mp[35][35],int vis[35][35],int flag[35][35])
{
	//������һ���Ա���������

	if (flag[x][y])
		return;

	flag[x][y] = 1;

	int dx[] = { 0,0,1,1,1,-1,-1,-1 };
	int dy[] = { 1,-1,0,1,-1,0,1,-1 };
	if (mp[x][y]!=0)
	{
		vis[x][y] = 1;
		return;
	}
	else
	{
		for (int i = 0; i < 8; i++)
		{
			int nx = x + dx[i];
			int ny = y + dy[i];
			if (nx < 0 || nx >= r || ny < 0 || ny >= c)
				continue;
			if (!mp[nx][ny])
			{
				vis[nx][ny] = 1;
				check_show(nx, ny, r, c, mp, vis, flag);
			}
			else
			{
				vis[nx][ny] = 1;
			}
		}
	}

}

class Timer {
public:
	Timer() {
		// ��ʼ������������  
		LARGE_INTEGER frequency;
		QueryPerformanceFrequency(&frequency);
		freq = static_cast<double>(frequency.QuadPart);

		// ��ȡ��ʼ������ֵ  
		QueryPerformanceCounter(&startCounter);
	}

	// ֹͣ��ʱ�������ؾ�����ʱ�䣨�룩  
	double stop() {
		// ��ȡ����������ֵ  
		LARGE_INTEGER endCounter;
		QueryPerformanceCounter(&endCounter);

		// ���㾭����ʱ�䣨�룩  
		return static_cast<double>(endCounter.QuadPart - startCounter.QuadPart) / freq;
	}

private:
	LARGE_INTEGER startCounter; // ��ʼ������ֵ  
	double freq; // ��������Ƶ�ʣ�ÿ��ļ���������  
};

int main()
{
	while(1)
	{
		cct_setconsoleborder(120, 40, 120, 9000);
		cct_setcursor(CURSOR_INVISIBLE);
		cct_setcolor(0);
		srand((unsigned)time(NULL));
		int mp[35][35];//��ͼ
		int red[35][35];
		int have_reveal[35][35];//�Ѿ��򿪵����ݲ����ٿ�
		memset(have_reveal, 0, sizeof have_reveal);
		memset(red, 0, sizeof red);
		memset(mp, 0, sizeof mp);
		int r, c;
		int level;
		int mines;
		cct_cls();
		while (1)
		{
			cout << "������ɨ����Ϸ�ĵȼ������֣�������\\�м�\\�߼�(1\\2\\3)��" << endl;
			cin >> level;
			if (!cin.good() || level > 3 || level < 1)
			{
				cin.clear();
				cin.ignore(9999, '\n');
				continue;
			}
			break;
		}
		switch (level)
		{
			case 1:
			{
				r = 9;
				c = 9;
				mines = 10;
				break;
			}
			case 2:
			{
				r = 16;
				c = 16;
				mines = 40;
				break;
			}
			case 3:
			{
				r = 16;
				c = 30;
				mines = 99;
				break;
			}
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
		gmw_set_rowno_switch(&MyCGI, true);					//��ʾ�к�
		gmw_set_colno_switch(&MyCGI, true);					//��ʾ�б�
		gmw_set_frame_style(&MyCGI, 4, 2, true);			//��������С��
		gmw_set_color(&MyCGI, COLOR_BLACK, COLOR_HWHITE);   //�ı���ɫ
		gmw_set_frame_color(&MyCGI, COLOR_HWHITE, COLOR_BLACK);
		gmw_set_frame_default_linetype(&MyCGI, 1);  //�߽����ʲô����

		gmw_set_block_border_switch(&MyCGI, false);
		gmw_set_frame_style(&MyCGI, 4, 2, true);
		//gmw_set_block_linetype(&MyCGI," ","0"," "," "," "," ");

		gmw_set_status_line_switch(&MyCGI, TOP_STATUS_LINE, true);   //������״̬������
		gmw_set_status_line_switch(&MyCGI, 1, true);   //������״̬������

		//test
		gmw_draw_frame(&MyCGI);

		sprintf(temp1, "�ո���ʾʱ�䣬esc�˳�      ");
		sprintf(temp2, "  ");
		gmw_status_line(&MyCGI, TOP_STATUS_LINE, temp1, temp2);//�ϴ�ӡ

		//���ҿ�������
		const BLOCK_DISPLAY_INFO bdi_reveal[] = {
			{BDI_VALUE_BLANK, COLOR_WHITE, COLOR_WHITE, NULL},  //0����ʾ���ÿո���伴��
			{1, COLOR_WHITE, COLOR_BLUE, "1"},
			{2, COLOR_WHITE, COLOR_GREEN, "2"},
			{3, COLOR_WHITE, COLOR_HBLUE, "3"},
			{4, COLOR_WHITE, COLOR_RED, "4"},
			{5, COLOR_WHITE, COLOR_PINK, "5"},
			{6, COLOR_WHITE, COLOR_HGREEN, "6"},
			{7, COLOR_WHITE, COLOR_CYAN, "7"},
			{8, COLOR_WHITE, COLOR_BLACK, "8"},
			{BDI_VALUE_END, -1, -1, NULL} //�жϽ�������Ϊ-999
		};
		//��û���ҿ�������
		const BLOCK_DISPLAY_INFO bdi_hidden[] = { 0,COLOR_YELLOW, COLOR_YELLOW,NULL };
		//��������
		const BLOCK_DISPLAY_INFO bdi_mine[] = { 1,COLOR_WHITE, COLOR_BLACK,"*" };
		//���������
		const BLOCK_DISPLAY_INFO bdi_masked[] = { 1,COLOR_RED, COLOR_WHITE,"#" };
		for (int i = 0; i < r; i++)
		{
			for (int j = 0; j < c; j++)
			{
				gmw_draw_block(&MyCGI, i, j, 0, bdi_hidden);
			}
		}
		/*
		{
			double stoptime = timer.stop();
			sprintf(temp1, "�ո���ʾʱ�䣬esc�˳�     ");
			sprintf(temp2, "ʱ�䣺%lf ", stoptime);
			gmw_status_line(&MyCGI, TOP_STATUS_LINE, temp2, temp1);//�ϴ�ӡ
		}*/
		Timer timer;
		int Maction, Mr, Mc, Keycode1=0, Keycode2=0;
		bool first_chosen = true;//��һ��ѡ�񣺲��ܱ���
		int before_x = -1, before_y = -1;//��һ��ѡ���
		while (1)//������ȡ������
		{
			gmw_read_keyboard_and_mouse(&MyCGI, Maction, Mr, Mc, Keycode1, Keycode2, true);
			//�����̲���
			{
				if (Keycode1 == 32)
				{
					double stoptime = timer.stop();
					sprintf(temp1, "�ո���ʾʱ�䣬esc�˳�     ");
					sprintf(temp2, "ʱ�䣺%lf ", stoptime);
					gmw_status_line(&MyCGI, TOP_STATUS_LINE, temp2, temp1);//�ϴ�ӡ
				}
				if (Keycode1 == 27)
				{
					break;
				}
				if (Maction == MOUSE_RIGHT_BUTTON_CLICK)//�Ҽ�
				{
					if (have_reveal[Mr][Mc])
					{
						//�Ѿ�������
						continue;
					}
					if (red[Mr][Mc] == 0)//�������
					{
						red[Mr][Mc] = 1;//20��Ϊ������ӵĵ�λ
						gmw_draw_block(&MyCGI, Mr, Mc, 1, bdi_masked);
						mines--;
						sprintf(temp1, "�ո���ʾʱ�䣬esc�˳�      ");
						sprintf(temp2, "%s%d","ʣ�����:",max(mines,0));
						gmw_status_line(&MyCGI, TOP_STATUS_LINE, temp2, temp1);//�ϴ�ӡ
					}
					else
					{
						red[Mr][Mc] = 0;
						gmw_draw_block(&MyCGI, Mr, Mc, 0, bdi_hidden);
						mines++;
						sprintf(temp1, "�ո���ʾʱ�䣬esc�˳�      ");
						sprintf(temp2, "%s%d", "ʣ�����:", max(0,mines));
						gmw_status_line(&MyCGI, TOP_STATUS_LINE, temp2, temp1);//�ϴ�ӡ
					}
				}
				if (Maction == MOUSE_LEFT_BUTTON_CLICK)//���
				{
					if (first_chosen)//��һ��ѡ�񣬸����������ʼ��
					{
						first_chosen = false;
						while (1)
						{
							memset(mp, 0, sizeof mp);
							for (int num = 1; num <= mines; num++)
							{
								int x = rand() % r;
								int y = rand() % c;
								if (mp[x][y] == 10 || (x == Mr && y == Mc))//10��������,���߳�ʼ�����˱��ε��λ��
								{
									num--;
									continue;
								}
								else
									mp[x][y] = 10;
							}

							//����map��������
							int dx[] = { 0,0,1,1,1,-1,-1,-1 };
							int dy[] = { 1,-1,0,1,-1,0,1,-1 };
							for (int i = 0; i < r; i++)
							{
								for (int j = 0; j < c; j++)
								{
									if (mp[i][j] == 10)
										continue;
									for (int k = 0; k < 9; k++)
									{
										int nx = i + dx[k], ny = j + dy[k];
										if (nx < 0 || nx >= r || ny < 0 || ny >= c)
											continue;
										if (mp[nx][ny] == 10)
											mp[i][j]++;
									}
								}
							}
							if (mp[Mr][Mc] == 0)
								break;
						}

						/*for (int i = 0; i < r; i++)
						{
							for (int j = 0; j < c; j++)
							{
								if(mp[i][j]==10)
									gmw_draw_block(&MyCGI, i, j, 1, bdi_mine);
								else
									gmw_draw_block(&MyCGI, i, j, mp[i][j], bdi_reveal);
							}
						}*/
						//����һ������������ݣ���Ϊ�ǵ�һ�ε�����Բ�����ֲ��׵�״̬
						if (red[Mr][Mc] == 1)
						{
							first_chosen = true;
							continue;
						}

						int vis[35][35];
						int flag[35][35];
						memset(flag, 0, sizeof flag);
						memset(vis, 0, sizeof vis);
						check_show(Mr, Mc, r, c, mp, vis, flag);

						for (int i = 0; i < r; i++)
						{
							for (int j = 0; j < c; j++)
							{
								if (vis[i][j] && red[i][j] != 1)
								{
									have_reveal[i][j] = 1;
									gmw_draw_block(&MyCGI, i, j, mp[i][j], bdi_reveal);
								}
							}
						}
					}
					else//���ܰ����ף�
					{
						if (red[Mr][Mc] == 1)//��㲻��
						{
							//first_chosen = true;
							continue;
						}

						if (mp[Mr][Mc] == 10)//��������
						{
							gmw_draw_block(&MyCGI, Mr, Mc, 1, bdi_mine);
							sprintf(temp1, "%s ", "ѡ���˵��ף� �����ˣ� ���س�����......");
							gmw_status_line(&MyCGI, LOWER_STATUS_LINE, "    ", temp1);//�´�ӡ

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

						int vis[35][35];
						int flag[35][35];
						memset(flag, 0, sizeof flag);
						memset(vis, 0, sizeof vis);
						check_show(Mr, Mc, r, c, mp, vis, flag);

						for (int i = 0; i < r; i++)
						{
							for (int j = 0; j < c; j++)
							{
								if (vis[i][j] && red[i][j] != 1)
								{
									have_reveal[i][j] = 1;
									gmw_draw_block(&MyCGI, i, j, mp[i][j], bdi_reveal);
								}
							}
						}
					}
				}
			}
			//�жϽ���
			{
				int end_flag = true;
				for (int i = 0; i < r; i++)
				{
					for (int j = 0; j < c; j++)
					{
						if (red[i][j]&&mp[i][j]!=10)
						{
							end_flag = false;
						}
						if (mp[i][j] == 10 && red[i][j] != 1)
						{
							end_flag = false;
						}
						if (mp[i][j] != 10 && have_reveal[i][j] != 1)
						{
							end_flag = false;
						}
					}
				}
				if (first_chosen)
					end_flag = false;
				if (end_flag)
				{
					double stoptime = timer.stop();
					sprintf(temp1, "%s %lf", "��Ϸ�������س����¿�ʼ��ʱ��", stoptime);
					gmw_status_line(&MyCGI, LOWER_STATUS_LINE, " ", temp1);//�´�ӡ
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
			}
		}
	}
}