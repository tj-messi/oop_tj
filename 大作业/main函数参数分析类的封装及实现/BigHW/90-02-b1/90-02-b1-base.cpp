#include  "windows.h"
#include"../include/cmd_console_tools.h"
#include"../include/base_work_fun.h"
#include"../include/90-01-b2 && 90-02-b1.h"
#include<iostream>
#include<conio.h>
#include<string>
#include<time.h>
#include <synchapi.h>
#include<stdlib.h>
#include"90-02-b1.h"
using namespace std;


void check_same(int mp[12][12], int vis[12][12], int r, int c)
{
	int dx[] = { 1,-1,0,0 };
	int dy[] = { 0,0,1,-1 };
	for (int i = 1; i <= r; i++)
	{
		for (int j = 1; j <= c; j++)
		{
			for (int k = 0; k <= 3; k++)
			{
				if (!(i + dx[k] >= 1 && i + dx[k] <= r && j + dy[k] >= 1 && j + dy[k] <= c))continue;
				if (mp[i][j] == mp[i + dx[k]][j + dy[k]] )
				{
					vis[i][j] = 1;
				}
			}
		}
	}
}

void replace0(int mp[12][12],int flag[12][12],int same[12][12], int r, int c, int x, int y)
{
	if (flag[x][y] == 1)return;
	flag[x][y] = 1;
	int dx[] = { 1,-1,0,0 };
	int dy[] = { 0,0,1,-1 };
	for (int i = 0; i <= 3; i++)
	{
		int nx = x + dx[i], ny = y + dy[i];
		if (mp[x][y] == mp[nx][ny]&&nx>=1&&nx<=r&&ny>=1&&ny<=c)
		{
			replace0(mp, flag, same,r, c, nx, ny);
		}
	}			
	same[x][y] = 0;
}

void getscore(int mp[12][12],int * now_score,int * now_0,int r,int c)
{
	cct_setcolor(0);
	int cnt0 = 0;
	for (int i = 1; i <= r; i++)
	{
		for (int j = 1; j <= c; j++)
		{
			if (mp[i][j] == 0)
				cnt0++;
		}
	}

	int plus0 = cnt0 - *now_0;
	cout << endl << "本次得分：" << plus0 * plus0 * 5 << " 总得分：" << *now_score + plus0 * plus0 * 5 <<"               "<< endl;

	*now_0 += plus0;
	*now_score += plus0 * plus0 * 5;
}

bool check_end(int mp[12][12], int r, int c)
{
	int dx[] = { 1,-1,0,0 };
	int dy[] = { 0,0,1,-1 };
	for (int i = 1; i <= r; i++)
	{
		for (int j = 1; j <= c; j++)
		{
			for (int k = 0; k <= 3; k++)
			{
				if (!(i + dx[k] >= 1 && i + dx[k] <= r && j + dy[k] >= 1 && j + dy[k] <= c))continue;
				if (mp[i][j] == mp[i + dx[k]][j + dy[k]] && mp[i][j] != 0)
				{
					return true;
				}
			}
		}
	}
	return false;
}

void visual_print(int mp[12][12], int r, int c, int op)
{
	cct_setcolor(0);
	cct_cls();
	cct_setfontsize("新宋体", 12, 8);
	if (op == 4 || op == 6)
		cct_setconsoleborder(c*6 + 7, (6 + r) * 6, c * 6 + 7, (6 + r) * 6);
	else
		cct_setconsoleborder(c * 8 + 7, (6 + r) *8, c * 8 + 7, (6 + r) * 8);
	int row, column, rrow, rcolumn;
	cct_getconsoleborder(row, column, rrow, rcolumn);
	cout << "屏幕：" << column << "行" << row << "列" <<endl;
	int x, y;
	cct_getxy(x, y);
	x+=2;
	y+=2;
	for (int i = 1; i <= r; i++)
	{
		if (op == 4)
		{
			cct_showch(x-2, y-1+(3*i), i + 'A' - 1, 0, 7, 1);
		}
		else if(op==5)
		{
			cct_showch(x - 2, y - 2 + (4 * i), i + 'A' - 1, 0, 7, 1);
		}
		if (i == 1)
		{
			cct_showstr(x, y, "┏", 15, 0, 1);
			for (int j = 1; j <= c; j++)
			{
				if(op==4)
					cct_showch(x + 6 * j - 2, y - 1, j+'0'-1, 0, 7, 1);
				else if(op==5)
					cct_showch(x + 8 * j - 4, y - 1, j + '0' - 1, 0, 7, 1);
				if (op == 4 || op == 6)
					cct_showstr(x + 6 * j -4, y, "━", 15, 0, 3);
				else
				{
					cct_showstr(x + 8 * j - 6, y, "━", 15, 0, 3);
					if (j != c)
						cct_showstr(x + 8 * j, y, "┳", 15, 0, 1);
				}
			}
			if (op == 4 || op == 6)
				cct_showstr(x + 6 * (c)+2, y, "┓", 15, 0, 1);
			if (op == 5 || op == 7)
				cct_showstr(x + 8 * (c), y, "┓", 15, 0, 1);
		}
		if (op == 4 || op == 6)
		{
			for (int k = 0; k <= 2; k++)
			{
				cct_showstr(x, y + (i-1)*3 + k +1, "┃", 15, 0, 1);
			}
		}
		else if(op==5)
		{
			for (int k = 0; k <= 2; k++)
			{
				cct_showstr(x, y + 4 * i - 3+k, "┃", 15, 0, 1);
			}
		}
	
		for (int j = 1; j <= c; j++)
		{
			if (op == 4 || op == 6)
			{
				//上层
				cct_showstr(x + 6 * j  -4 , y + (i - 1) * 3 + 1, "╔", mp[i][j] + 9, 0, 1);
				cct_showstr(x + 6 * j - 2, y + (i - 1) * 3 + 1, "═", mp[i][j] + 9, 0, 1);
				cct_showstr(x + 6 * j , y + (i - 1) * 3 + 1, "╗", mp[i][j] + 9, 0, 1);
				//中层
				cct_showstr(x + 6 * j - 4, y + (i - 1) * 3 + 2, "║", mp[i][j] + 9, 0, 1);
				cct_showstr(x + 6 * j - 2, y + (i - 1) * 3 + 2, "★", mp[i][j] + 9, 0, 1);
				cct_showstr(x + 6 * j, y + (i - 1) * 3 + 2, "║", mp[i][j] + 9, 0, 1);
				//下层
				cct_showstr(x + 6 * j - 4, y + (i - 1) * 3 + 3, "╚", mp[i][j] + 9, 0, 1);
				cct_showstr(x + 6 * j - 2, y + (i - 1) * 3 + 3, "═", mp[i][j] + 9, 0, 1);
				cct_showstr(x + 6 * j , y + (i - 1) * 3 + 3, "╝", mp[i][j] + 9, 0, 1);
			}	
			else if(op==5)
			{
				//cct_showstr(x + 8 * j - 4, y + 4 * i - 2, "★", mp[i][j] + 4, 0, 1);
				//上层
				cct_showstr(x + 8 * j - 6, y + 4 * i - 3, "╔", mp[i][j] + 9, 0, 1);
				cct_showstr(x + 8 * j - 4, y + 4 * i - 3, "═", mp[i][j] + 9, 0, 1);
				cct_showstr(x + 8 * j - 2, y + 4 * i - 3, "╗", mp[i][j] + 9, 0, 1);
				//中层
				cct_showstr(x + 8 * j - 6, y + 4 * i - 2, "║", mp[i][j] + 9, 0, 1);
				cct_showstr(x + 8 * j - 4, y + 4 * i - 2, "★", mp[i][j] + 9, 0, 1);
				cct_showstr(x + 8 * j - 2, y + 4 * i - 2, "║", mp[i][j] + 9, 0, 1);
				//下层
				cct_showstr(x + 8 * j - 6, y + 4 * i - 1, "╚", mp[i][j] + 9, 0, 1);
				cct_showstr(x + 8 * j - 4, y + 4 * i - 1, "═", mp[i][j] + 9, 0, 1);
				cct_showstr(x + 8 * j - 2, y + 4 * i - 1, "╝", mp[i][j] + 9, 0, 1);

				cct_showstr(x + 8 * j - 6, y + 4 * i, "━", 15, 0, 3);

				for (int k = 0; k <= 2; k++)
				{
					cct_showstr(x + 8 * j , y + 4 * i - 3 + k, "┃", 15, 0, 1);
				}
			}
		}
		if (op == 4 || op == 6)
		{
			for (int k = 0; k <= 2; k++)
			{
				cct_showstr(x + 6 * (c) +2, y + (i - 1) * 3 + k +1, "┃", 15, 0, 1);
			}
		}
		else if (op == 5)
		{
			for (int k = 0; k <= 2; k++)
			{
				cct_showstr(x+8 * (c), y + 4 * i - 3 + k, "┃", 15, 0, 1);
			}
		}
		if (i == r && (op == 4 || op == 6))
		{
			cct_showstr(x, y + 3 * r+1, "┗", 15, 0, 1);
			for (int j = 1; j <= c; j++)
			{
				cct_showstr(x + 6 * j - 4, y + 3 * r+1, "━", 15, 0, 3);
			}
			cct_showstr(x + 6 * (c ) +2, y + 3*r+1, "┛", 15, 0, 1);
		}
		else if (i == r && (op == 5 || op == 7))
		{
			cct_showstr(x, y + 4 * r, "┗", 15, 0, 1);
			for (int j = 1; j <= c; j++)
			{
				cct_showstr(x + 8 * j - 6, y + 4 * r, "━", 15, 0, 3);
				cct_showstr(x + 8 * j, y + 4 * r, "┻", 15, 0, 1);
			}
			cct_showstr(x + 8 * (c), y + 4 * r, "┛", 15, 0, 1);
		}
		if (i != r && (op == 5 || op == 7))
		{
			cct_showstr(x, y + 4 * i, "┣", 15, 0, 1);
			for (int j = 1; j <= c; j++)
			{
				cct_showstr(x + 8 * j - 2, y + 4 * i, "━", 15, 0, 1);
				cct_showstr(x + 8 * j, y + 4 * i, "╋", 15, 0, 1);
			}
			cct_showstr(x + 8 * c, y + 4 * i, "┫", 15, 0, 1);
		}
	}
	cct_setcolor(0);
}

void check_c_full_of_0(int mp[12][12], int r, int c)
{
	int flag = 15;
	for (int j = c; j >= 1; j--)
	{
		bool full_0 = true;
		for (int i = 1; i <= r; i++)
		{
			if (mp[i][j] != 0)
			{
				if(flag==15)
				{
					flag = j;
				}
				full_0 = false;
			}
		}
		if (full_0 && j <= flag-1 && flag != 15) // 本列全是0，本列右边有非0列
		{
			for (int k = j + 1; k <= c; k++)
			{
				for (int l = 1; l <= r; l++)
				{
					mp[l][k - 1] = mp[l][k];
				}
			}
			for (int l = 1; l <= r; l++)
			{
				mp[l][flag] = 0;
			}
			check_c_full_of_0(mp, r, c);
			return;
		}
	}
}

void visual_chosen(int mp[12][12], int r, int c, int x, int y,int int_c [2],char char_r[2],int col,int plu,int op,int idx)
{
	if (mp[char_r[idx] - 'A' + 1][int_c[idx] + 1] == 0)
		return;
	int dx, dy, j, i;
	if(op==4||op==6)
	{
		 dx = 2;
		dy = 3 * r + 2;
		 j = int_c[idx] + 1;
		 i = char_r[idx] - 'A' + 1;
	}
	else if(op==5||op==7)
	{
		dx = 0;
		dy = 4 * r + 1;
		j = int_c[idx] + 1;
		i = char_r[idx] - 'A' + 1;
	}
	//上层
	cct_showstr(x + 2 * plu * j - 4 + dx, y + (i - 1) * plu + 1 - dy, "╔", mp[i][j] + 9, col, 1);
	cct_showstr(x + 2 * plu * j - 2 + dx, y + (i - 1) * plu + 1 - dy, "═", mp[i][j] + 9, col, 1);
	cct_showstr(x + 2 * plu * j + dx, y + (i - 1) * plu + 1 - dy, "╗", mp[i][j] + 9, col, 1);
	//中层
	cct_showstr(x + 2 * plu * j - 4 + dx, y + (i - 1) * plu + 2 - dy, "║", mp[i][j] + 9, col, 1);
	cct_showstr(x + 2 * plu * j - 2 + dx, y + (i - 1) * plu + 2 - dy, "★", mp[i][j] + 9, col, 1);
	cct_showstr(x + 2 * plu * j + dx, y + (i - 1) * plu + 2 - dy, "║", mp[i][j] + 9, col, 1);
	//下层
	cct_showstr(x + 2 * plu * j - 4 + dx, y + (i - 1) * plu + 3 - dy, "╚", mp[i][j] + 9, col, 1);
	cct_showstr(x + 2 * plu * j - 2 + dx, y + (i - 1) * plu + 3 - dy, "═", mp[i][j] + 9, col, 1);
	cct_showstr(x + 2 * plu * j + dx, y + (i - 1) * plu + 3 - dy, "╝", mp[i][j] + 9, col, 1);
}

void visual_get_same(int mp[12][12], int r, int c, int x, int y,int int_c[2],char char_r[2], int op,int col )
{
	if (mp[char_r[1] - 'A' + 1][int_c[1] + 1] == 0)
		return;
	int flag[12][12],same[12][12];
	memset(flag, 0, sizeof flag);
	memset(same, 1, sizeof same);
	replace0(mp, flag, same, r, c, char_r[1] - 'A' + 1, int_c[1] + 1);
	for (int i = 1; i <= r; i++)
	{
		for (int j = 1; j <= c; j++)
		{
			if (same[i][j] == 0)
			{
				if (char_r[1] - 'A' + 1 == i && int_c[1] + 1 == j)
				{

				}
				else
				{
					int now_c[2] = { 0,j - 1 };
					char now_r[2] = { 0,char(i - 1 + 'A') };
					visual_chosen(mp, r, c, x, y,now_c, now_r, col, (op + 1) / 2, op, 1);
				}
			}
		}
	}
}

void visual_remove(int mp[12][12], int r, int c, int x, int y, int int_c[2], char char_r[2], int col, int plu, int op, int idx)
{
	int dx, dy, j, i;
	if (op == 4 || op == 6)
	{
		dx = 2;
		dy = 3 * r + 2;
		j = int_c[idx] + 1;
		i = char_r[idx] - 'A' + 1;
	}
	else if (op == 5 || op == 7)
	{
		dx = 0;
		dy = 4 * r + 1;
		j = int_c[idx] + 1;
		i = char_r[idx] - 'A' + 1;
	}
	//上层
	cct_showstr(x + 2 * plu * j - 4 + dx, y + (i - 1) * plu + 1 - dy, " ", 15, col, 2);
	cct_showstr(x + 2 * plu * j - 2 + dx, y + (i - 1) * plu + 1 - dy, " ", 15, col, 2);
	cct_showstr(x + 2 * plu * j + dx, y + (i - 1) * plu + 1 - dy, " ", 15, col, 2);
	//中层
	cct_showstr(x + 2 * plu * j - 4 + dx, y + (i - 1) * plu + 2 - dy, " ", 15, col, 2);
	cct_showstr(x + 2 * plu * j - 2 + dx, y + (i - 1) * plu + 2 - dy, " ", 15, col, 2);
	cct_showstr(x + 2 * plu * j + dx, y + (i - 1) * plu + 2 - dy, " ", 15, col, 2);
	//下层
	cct_showstr(x + 2 * plu * j - 4 + dx, y + (i - 1) * plu + 3 - dy, " ", 15, col, 2);
	cct_showstr(x + 2 * plu * j - 2 + dx, y + (i - 1) * plu + 3 - dy, " ", 15, col, 2);
	cct_showstr(x + 2 * plu * j + dx, y + (i - 1) * plu + 3 - dy, " ",15, col, 2);
}


void visual_renew_mp(int mp[12][12], int r, int c,int x,int y, int op)
{
	int plu;
	int dx, dy;
	if (op == 4 || op == 6)
	{
		dx = 2;
		dy = 3 * r + 2;
		plu = 3;

	}
	else if (op == 5 || op == 7)
	{
		dx = 0;
		dy = 4 * r + 1;
		plu = 4;
	}
	if(op==6||op==7)
	{
		for (int j = 1; j <= c; j++)
		{
			for (int i = r; i >= 1; i--)
			{
				if (mp[i][j] == 0)
				{
					for (int k = i; k >= 1; k--)
					{
						int cnt = 1;
						if (mp[k][j] != 0)
						{
							while (mp[k + cnt][j] == 0 && (k + cnt <= r))
							{
								cnt++;
							}
							cnt--;
							if (op == 6)
								cnt *= 3;
							else
								cnt *= 4;
							{
								for (int l = 1; l <= cnt; l++)
								{
									{
										//上层
										cct_showstr(x + 2 * plu * j - 4 + dx, y + (k - 1) * plu + l - dy, " ", 15, 15, 2);
										cct_showstr(x + 2 * plu * j - 2 + dx, y + (k - 1) * plu + l - dy, " ", 15, 15, 2);
										cct_showstr(x + 2 * plu * j + dx, y + (k - 1) * plu + l - dy, " ", 15, 15, 2);
										//中层
										cct_showstr(x + 2 * plu * j - 4 + dx, y + (k - 1) * plu + 1 + l - dy, " ", 15, 15, 2);
										cct_showstr(x + 2 * plu * j - 2 + dx, y + (k - 1) * plu + 1 + l - dy, " ", 15, 15, 2);
										cct_showstr(x + 2 * plu * j + dx, y + (k - 1) * plu + 1 + l - dy, " ", 15,15, 2);
										//下层
										cct_showstr(x + 2 * plu * j - 4 + dx, y + (k- 1) * plu + 2+l - dy, " ", 15, 15, 2);
										cct_showstr(x + 2 * plu * j - 2 + dx, y + (k - 1) * plu +  2 + l - dy, " ", 15, 15, 2);
										cct_showstr(x + 2 * plu * j + dx, y + (k- 1) * plu + 2 + l - dy, " ", 15, 15, 2);

										pause(10 );
									}
									if(op==7)
										cct_showstr(x + 2 * plu * j - 4 + dx, y + (k - 1) * plu  + ((l)%plu==0 ? l : 0)-dy, "━", 15, 0, 3);
									{
										//上层
										cct_showstr(x + 2 * plu * j - 4 + dx, y + (k - 1) * plu + 1+l - dy, "╔", mp[k][j] + 9, 0, 1);
										cct_showstr(x + 2 * plu * j - 2 + dx, y + (k - 1) * plu + 1 + l - dy, "═", mp[k][j] + 9, 0, 1);
										cct_showstr(x + 2 * plu * j + dx, y + (k- 1) * plu + 1 + l - dy, "╗", mp[k][j] + 9, 0, 1);
										//中层
										cct_showstr(x + 2 * plu * j - 4 + dx, y + (k - 1) * plu + 2 + l - dy, "║", mp[k][j] + 9, 0, 1);
										cct_showstr(x + 2 * plu * j - 2 + dx, y + (k - 1) * plu + 2 + l - dy, "★", mp[k][j] + 9, 0, 1);
										cct_showstr(x + 2 * plu * j + dx, y + (k - 1) * plu + 2 + l - dy, "║", mp[k][j] + 9, 0, 1);
										//下层
										cct_showstr(x + 2 * plu * j - 4 + dx, y + (k - 1) * plu + 3 + l - dy, "╚", mp[k][j] + 9, 0, 1);
										cct_showstr(x + 2 * plu * j - 2 + dx, y + (k - 1) * plu + 3 + l - dy, "═", mp[k][j] + 9, 0, 1);
										cct_showstr(x + 2 * plu * j + dx, y + (k - 1) * plu + 3 + l - dy, "╝", mp[k][j] + 9, 0, 1);

										pause(10);
									}
								}
							}
							if (op == 6)
								mp[k + cnt / 3][j] = mp[k][j];
							else
								mp[k + cnt / 4][j] = mp[k][j];
							mp[k][j] = 0;
						}

					}

				}
			}
		}
	}
}

void visual_check_c_0(int mp[12][12], int r, int c,int x, int y, int op)
{
	int plu;
	int dx, dy;
	{
		dx = 0;
		dy = 4 * r ;
		plu = 4;
	}
	int flag = 15;
	for (int j = c; j >= 1; j--)
	{
		bool full_0 = true;
		for (int i = 1; i <= r; i++)
		{
			if (mp[i][j] != 0)
			{
				if (flag == 15)
				{
					flag = j;
				}
				full_0 = false;
			}
		}
		if (full_0 && j <= flag - 1 && flag != 15) // 本列全是0，本列右边有非0列
		{
			for (int k = j + 1; k <= c; k++)
			{
				for (int l = 1; l <= r; l++)
				{
					for (int l1 = 2; l1 <= 2*plu; l1+=2)
					{
						if (mp[l][k] == 0)
							continue;
						{
							//上层
							cct_showstr(x + 2 * plu * k - 4 + dx - l1+2, y + (l - 1) * plu  - dy, " ", 15, 15, 2);
							cct_showstr(x + 2 * plu * k - 2 + dx - l1 + 2, y + (l- 1) * plu - dy, " ", 15, 15, 2);
							cct_showstr(x + 2 * plu * k+ dx - l1 + 2, y + (l - 1) * plu  - dy, " ", 15, 15, 2);
							//中层
							cct_showstr(x + 2 * plu * k - 4 + dx - l1 + 2, y + (l - 1) * plu + 1  - dy, " ", 15, 15, 2);
							cct_showstr(x + 2 * plu * k- 2 + dx - l1 + 2, y + (l - 1) * plu + 1  - dy, " ", 15, 15, 2);
							cct_showstr(x + 2 * plu * k + dx - l1 + 2, y + (l - 1) * plu + 1 - dy, " ", 15, 15, 2);
							//下层
							cct_showstr(x + 2 * plu *k - 4 + dx - l1 + 2, y + (l - 1) * plu + 2  - dy, " ", 15, 15, 2);
							cct_showstr(x + 2 * plu * k - 2 + dx - l1 + 2, y + (l- 1) * plu + 2  - dy, " ", 15, 15, 2);
							cct_showstr(x + 2 * plu *k + dx - l1 + 2, y + (l - 1) * plu + 2  - dy, " ", 15, 15, 2);

							pause(10);
						}
						if (op == 7)
						{
							if((l1 / 2) % 4 == 0)
							{
								for (int idx = 0; idx <= 2; idx++)
								{
									cct_showstr(x + 2 * plu * k - 2 + dx - ((l1 / 2) % 4 == 0 ? l1 : 0), y + (l - 1) * plu + 2 - dy - idx, "┃", 15, 0, 3);
								}
							}
						}
						{
							//上层
							cct_showstr(x + 2 * plu * k - 4 + dx - l1, y + (l - 1) * plu   - dy, "╔", mp[l][k] + 9, 0, 1);
							cct_showstr(x + 2 * plu * k - 2 + dx - l1, y + (l - 1) * plu   - dy, "═", mp[l][k] + 9, 0, 1);
							cct_showstr(x + 2 * plu * k + dx - l1, y + (l- 1) * plu  - dy, "╗", mp[l][k] + 9, 0, 1);
							//中层
							cct_showstr(x + 2 * plu * k - 4 + dx - l1, y + (l - 1) * plu + 1  - dy, "║", mp[l][k] + 9, 0, 1);
							cct_showstr(x + 2 * plu * k - 2 + dx - l1, y + (l - 1) * plu + 1 - dy, "★", mp[l][k] + 9, 0, 1);
							cct_showstr(x + 2 * plu * k + dx - l1, y + (l - 1) * plu + 1- dy, "║", mp[l][k] + 9, 0, 1);
							//下层
							cct_showstr(x + 2 * plu * k - 4 + dx - l1, y + (l - 1) * plu + 2  - dy, "╚", mp[l][k] + 9, 0, 1);
							cct_showstr(x + 2 * plu * k - 2 + dx - l1, y + (l - 1) * plu + 2 - dy, "═", mp[l][k] + 9, 0, 1);
							cct_showstr(x + 2 * plu * k + dx - l1, y + (l - 1) * plu + 2 - dy, "╝", mp[l][k] + 9, 0, 1);

							pause(10);
						}
					}
					mp[l][k - 1] = mp[l][k];
				}
			}
			for (int l = 1; l <= r; l++)
			{
				mp[l][flag] = 0;
			}
			//check_c_full_of_0(mp, r, c);
			return;
		}
	}
}

void game(int op,int score)
{
	int mp[12][12];
	int vis[12][12];
	memset(mp, 0, sizeof mp);
	memset(vis, 0, sizeof vis);
	int r, c;
	cct_cls();
	while (1)
	{
		cout << "请输入行数(8-10)：" << endl;
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
		cout << "请输入列数(8-10)：" << endl;
		cin >> c;
		if (!cin.good() || c > 10 || c < 8)
		{
			cin.clear();
			cin.ignore(9999, '\n');
			continue;
		}
		break;
	}	
	for (int i = 1; i <= r; i++)
	{
		for (int j = 1; j <= c; j++)
		{
			initial_mp(mp, i, j, 5);
		}
	}
	int now_0 = 0;
	while (1)
	{
		if (op == 1 || op == 2 || op == 3)
		{

			cout << endl << "当前数组:" << endl;
			show_mp(mp, r, c, 1);
			cout << endl << "请以字母+数字形式[例：c2]输入矩阵坐标:";
			check_same(mp, vis, r, c);
			char cmd[100];
			gets_s(cmd);
			while (1)
			{
				int x, y;
				cct_getxy(x, y);
				cin >> cmd;
				if (cmd == "")
					cct_gotoxy(x, y);
				if (((cmd[0] >= 'a' && cmd[0] <= 'a' + r - 1) || (cmd[0] >= 'A' && cmd[0] <= 'A' + r - 1)) && (cmd[1] >= '0' && cmd[1] <= '0' + c - 1))
				{
					int nx, ny;
					if ((cmd[0] >= 'a' && cmd[0] <= 'a' + r - 1))
					{
						nx = cmd[0] - 'a' + 1; ny = cmd[1] - '0' + 1;
					}
					else
					{
						nx = cmd[0] - 'A' + 1; ny = cmd[1] - '0' + 1;
					}


					if (mp[nx][ny] == 0)
					{
						cout << "目前选择的是 " << cmd[0] << "行" << ny - 1 << "列 ";
						cout << "目标值是0，非法！，请重新输入";
						cct_gotoxy(x, y);
						cout << "                                                                            ";
					}
					else if (vis[nx][ny] == 0)
					{
						cout << "目前选择的是 " << cmd[0] << "行" << ny - 1 << "列 ";
						cout << "输入的矩阵坐标位置处无连续相同值，请重新输入";
						cct_gotoxy(x, y);
						cout << "                                                                            ";
					}
					else
					{
						cout << "目前选择的是 " << cmd[0] << "行" << ny - 1 << "列                                                 ";
						int flag[12][12], same[12][12];
						memset(flag, 0, sizeof flag);
						memset(same, 1, sizeof same);
						replace0(mp, flag, same, r, c, nx, ny);
						cout << endl << "查找结果数组：" << endl;
						cout << "  |";
						for (int i = 1; i <= c; i++)
							cout << "  " << i - 1;
						cout << endl << "--+";
						for (int i = 1; i <= c; i++)
							cout << "---";
						cout << endl;
						for (int i = 1; i <= r; i++)
						{
							cout << (char)('A' + (i - 1)) << " |";
							for (int j = 1; j <= c; j++)
							{
								if (same[i][j] == 0)
									cout << "  " << '*';
								else
									cout << "  " << 0;
							}
							cout << endl;
						}
						int x0, y0;
						cct_getxy(x0, y0);
						cout << endl << "当前数组(不同颜色表示)" << endl;
						show_mp(mp, r, c, 1);
						show_0(mp, r, c, same);
						if (op == 1)
							return;
						if (op == 2 || op == 3)//2的运行部分
						{
							char cmd_char;
							while (1)
							{
								cout << endl << "请确认是否把" << cmd[0] << cmd[1] << "及周围的想通知消除(Y/N/Q)";

								while (1)
								{
									cmd_char = getchar();
									if (cmd_char == 'y' || cmd_char == 'Y' || cmd_char == 'n' || cmd_char == 'N' || cmd_char == 'q' || cmd_char == 'Q')
										break;
								}
								if (cmd_char == 'q' || cmd_char == 'Q')
									return;
								if (cmd_char == 'n' || cmd_char == 'N')
									break;
								else
									break;
							}
							if (cmd_char == 'n' || cmd_char == 'N')
								break;
							cout << endl << "相同值归并后的数组（不同色标识）：" << endl;
							memset(flag, 0, sizeof flag);
							replace0(mp, flag, mp, r, c, nx, ny);
							check_c_full_of_0(mp, r, c);
							show_mp(mp, r, c, 1);
							show_0(mp, r, c, mp);
							getscore(mp, &score, &now_0, r, c);

							cout << endl << "按回车键进行数组下落操作...";
							int cmd;
							while (1)
							{
								cmd = _getch();
								if (cmd == 13)
								{
									break;
								}
							}
							cout << endl << "下落后的数组" << endl;
							replace_by_0(mp, r, c, 0);
							show_mp(mp, r, c, 1);
							show_0(mp, r, c, mp);
							if (op == 2)
								return;
							if (op == 3)
							{
								if (!check_end(mp, r, c))
								{
									cout << endl << "游戏结束，按回车继续下一盘游戏" << endl;
									int cmd;
									while (1)
									{
										cmd = _getch();
										if (cmd == 13)
										{
											break;
										}
									}
									if (r * c - now_0 < 10)
									{
										score += (10 - r * c + now_0) * 180;
									}
									game(3,score);
								}
								cout << endl << "本次消除结束，按回车键继续新一次的消除";
								int cmd;
								while (1)
								{
									cmd = _getch();
									if (cmd == 13)
									{
										break;
									}
								}
							}
						}
					}
					break;
				}
				else
				{
					cin.clear();
					cct_gotoxy(0, y + 1);
					cout << "输入错误,请重新输入                                                            ";
					cct_gotoxy(x, y);
					cout << "                                                                            ";
				}
				cct_gotoxy(x, y);
			}
		}
		if (op == 4 || op == 6)
		{
			cct_setcursor(CURSOR_INVISIBLE);
			visual_print(mp,r,c,4);
			cout << endl;
			int x, y;
			cct_getxy(x, y);
			cct_enable_mouse();
			int m_x[2] = {0,0}, m_y[2] = {0,0}, m_action = 0, k1 = 0, k2 = 0;
			char char_r[2] = { 'A','A' }; int int_c[2] = { 0,0 };
			while(1)
			{
				cct_setcolor(0);
				while (1)
				{
					bool flag = true;
					int res = cct_read_keyboard_and_mouse(m_x[1], m_y[1], m_action, k1, k2);
					if (m_x[0] == m_x[1] && m_y[0] == m_y[1])
					{

					}
					else
					{
						char_r[1] = 'A' + (m_y[1] - 4) / 3;
						int_c[1] = (m_x[1] / 2 + 1) / 3 - 1;
						m_x[0] = m_x[1];
						m_y[0] = m_y[1];

						if (m_y[1] - 4 < 0)
							flag = false;

						//if((m_y[1]))
					}

					cct_gotoxy(x, y);
					if (m_action == MOUSE_RIGHT_BUTTON_CLICK)
						return;
					if (m_action == MOUSE_LEFT_BUTTON_CLICK)
						break;
					if (k1 == 13)
						break;
					if (int_c[1] >= 0 && int_c[1] <= c - 1 && char_r[1] >= 'A' && char_r[1] <= 'A' + r - 1 && flag)
					{
						if (k1 == 0 && k2 == 0)//鼠标执行的操作
							cout << endl << "[当前鼠标]" << char_r[1] << "行 " << int_c[1] << "列                                                             ";
						else//键盘执行的操作
						{
							if (k2 == KB_ARROW_DOWN)
							{
								if (char_r[1] - 'A' + 2 > r)
								{
									char_r[1] = 'A';
								}
								else
									char_r[1] = ((char_r[1] + 1));
							}
							else if (k2 == KB_ARROW_UP)
							{
								if (char_r[1] - 'A' - 1 < 0)
								{
									char_r[1] = char('A' + r - 1);
								}
								else
									char_r[1] = ((char_r[1] - 1));
							}
							else if (k2 == KB_ARROW_LEFT)
							{
								if (int_c[1] - 1 < 0)
								{
									int_c[1] = c;
								}
								else
									int_c[1]--;
							}
							else if (k2 == KB_ARROW_RIGHT)
							{
								if (int_c[1] + 1 >= c)
								{
									int_c[1] = 0;
								}
								else
									int_c[1]++;

							}

							cout << endl << "[当前键盘]" << char_r[1] << "行 " << int_c[1] << "列                                                                  ";
						}
						if ((!(char_r[0] == char_r[1] && int_c[1] == int_c[0])))
						{

							//原来的消失
							{
								visual_chosen(mp, r, c, x, y, int_c, char_r, 0, 3, 4, 0);
							}

							//现在的打印
							{
								visual_chosen(mp, r, c, x, y, int_c, char_r,7, 3, 4, 1);
							}
							char_r[0] = char_r[1];
							int_c[0] = int_c[1];
							cct_setcolor(0);
							cct_gotoxy(x, y);
						}

					}
					else
					{
						cout << endl << "[当前光标]" << "位置非法               ";
					}
				}
				
				if (op == 6)
				{
					cout <<endl<<"选择了" << char_r[1] << "行 " << int_c[1] << "列   鼠标左键或者回车表示消除  移开表示取消选择                             " << endl;
					int vis[12][12];
					memset(vis, 0, sizeof vis);
					check_same(mp, vis, r, c);
					if (vis[char_r[1] - 'A' + 1][int_c[1] + 1] == 0 && mp[char_r[1] - 'A' + 1][int_c[1] + 1] != 0)//无相同值
					{
						visual_chosen(mp, r, c, x, y, int_c, char_r, 7, 3, 4, 1);
						cct_gotoxy(x, y);
						cct_setcolor(0);
						cout << endl<< "周围无相同值                                                      "  << endl;
						while(1)
						{
							int res = cct_read_keyboard_and_mouse(m_x[1], m_y[1], m_action, k1, k2);
							if (m_action == MOUSE_RIGHT_BUTTON_CLICK)
								return;
							if(k1==0&&k2==0)
							{
								if (m_x[0] == m_x[1] && m_y[0] == m_y[1])
								{

								}
								else
								{

									break;//操作不一样会返回
								}
							}
							else if (k2 == KB_ARROW_DOWN)
							{
								if (char_r[1] - 'A' + 2 > r)
								{
									char_r[1] = 'A';
								}
								else
									char_r[1] = ((char_r[1] + 1));
								break;
							}
							else if (k2 == KB_ARROW_UP)
							{
								if (char_r[1] - 'A' - 1 < 0)
								{
									char_r[1] = char('A' + r - 1);
								}
								else
									char_r[1] = ((char_r[1] - 1));
								break;
							}
							else if (k2 == KB_ARROW_LEFT)
							{
								if (int_c[1] - 1 < 0)
								{
									int_c[1] = c;
								}
								else
									int_c[1]--;
								break;
							}
							else if (k2 == KB_ARROW_RIGHT)
							{
								if (int_c[1] + 1 >= c)
								{
									int_c[1] = 0;
								}
								else
									int_c[1]++;
								break;
							}
						}
						if ((!(char_r[0] == char_r[1] && int_c[1] == int_c[0])) &&mp[char_r[1] - 'A' + 1][int_c[1] + 1] != 0)
						{
							//原来的消失
							{
								visual_chosen(mp, r, c, x, y, int_c, char_r, 0, 3, 4, 0);
							}

							//现在的打印
							{
								visual_chosen(mp, r, c, x, y, int_c, char_r, 7, 3, 4, 1);
							}
							char_r[0] = char_r[1];
							int_c[0] = int_c[1];
							cct_setcolor(0);
							cct_gotoxy(x, y);
						}
						continue;
					}
					else
					{
						visual_get_same(mp, r, c, x, y, int_c, char_r, 6, 7);
						while (1)
						{
							if (int_c[1] >= 0 && int_c[1] <= c - 1 && char_r[1] >= 'A' && char_r[1] <= 'A' + r - 1 )
							{
								visual_chosen(mp, r, c, x, y, int_c, char_r, 15, 3, 4, 1);
							}
							cct_gotoxy(x, y);
							cct_setcolor(0);
							int res = cct_read_keyboard_and_mouse(m_x[1], m_y[1], m_action, k1, k2);
							if (m_action == MOUSE_RIGHT_BUTTON_CLICK)
								return;

							if (m_action == MOUSE_LEFT_BUTTON_CLICK || k1 == 13)
							{
								int flag[12][12];
								memset(flag, 0, sizeof flag);
								replace0(mp, flag, mp, r, c, char_r[1] - 'A' + 1, int_c[1] + 1);
								for (int i = 1; i <= r; i++)
								{
									for (int j = 1; j <= c; j++)
									{
										if (mp[i][j] == 0)
										{
											int now_c[2] = { 0,j - 1 };
											char now_r[2] = { 0,char(i - 1 + 'A') };
											visual_remove(mp, r, c, x, y, now_c, now_r, 15, 3, 6, 1);
										}
									}
								}
								cct_gotoxy(20, 0);
								getscore(mp,&score, &now_0,r,c);
								visual_renew_mp(mp, r, c, x, y, 6);
								cct_setcolor(0);
								cct_gotoxy(x, y);
								return;
								
							}

							if (k1 == 0 && k2 == 0)
							{
								if (m_x[0] == m_x[1] && m_y[0] == m_y[1])
								{
									continue;
								}
								else
								{
									char nowr = 'A' + (m_y[1] - 4) / 3;
									int nowc = (m_x[1] / 2 + 1) / 3 - 1;
									if ((char_r[0] == nowr && int_c[1] == nowc))
									{
										continue;
									}
									visual_get_same(mp, r, c, x, y, int_c, char_r, 6, 0);
									break;//操作不一样会返回
								}
							}
							else if (k2 == KB_ARROW_DOWN)
							{
								visual_get_same(mp, r, c, x, y, int_c, char_r, 6, 0);
								if (char_r[1] - 'A' + 2 > r)
								{
									char_r[1] = 'A';
								}
								else
									char_r[1] = ((char_r[1] + 1));
								break;//操作不一样会返回
							}
							else if (k2 == KB_ARROW_UP)
							{
								visual_get_same(mp, r, c, x, y, int_c, char_r, 6, 0);
								if (char_r[1] - 'A' - 1 < 0)
								{
									char_r[1] = char('A' + r - 1);
								}
								else
									char_r[1] = ((char_r[1] - 1));
								break;//操作不一样会返回
							}
							else if (k2 == KB_ARROW_LEFT)
							{
								visual_get_same(mp, r, c, x, y, int_c, char_r, 6, 0);
								if (int_c[1] - 1 < 0)
								{
									int_c[1] = c;
								}
								else
									int_c[1]--;
								break;//操作不一样会返回
							}
							else if (k2 == KB_ARROW_RIGHT)
							{
								visual_get_same(mp, r, c, x, y, int_c, char_r, 6, 0);
								if (int_c[1] + 1 >= c)
								{
									int_c[1] = 0;
								}
								else
									int_c[1]++;
								break;//操作不一样会返回
							}
							break;
						}
						if ((!(char_r[0] == char_r[1] && int_c[1] == int_c[0]))&&mp[char_r[1]-'A'+1][int_c[1]+1]!=0)
						{
							//原来的消失
							{
								visual_chosen(mp, r, c, x, y, int_c, char_r, 0, 3, 4, 0);
								visual_get_same(mp, r, c, x, y, int_c, char_r, 6, 0);
							}

							//现在的打印
							{
								visual_chosen(mp, r, c, x, y, int_c, char_r, 7, 3, 4, 1);
							}
							char_r[0] = char_r[1];
							int_c[0] = int_c[1];
							cct_setcolor(0);
							cct_gotoxy(x, y);
						}
						
					}
				}
				
				if (op == 4)
				{
					
					visual_chosen(mp, r, c, x, y, int_c, char_r, 15, 3, 4, 1);
					cct_gotoxy(x, y);
					cct_setcolor(0);
					cout << endl<<"选择了" << char_r[1] << "行 " << int_c[1] << "列                " << endl;
					return;
				}
			}


			
		}
		if (op == 5||op==7)
		{
			cct_setcursor(CURSOR_INVISIBLE);
			visual_print(mp, r, c, 5);

			

			cout << endl;
			int x, y;
			cct_getxy(x, y);
			cct_enable_mouse();
			int m_x[2] = { 0,0 }, m_y[2] = { 0,0 }, m_action = 0, k1 = 0, k2 = 0;
			char char_r[2] = { 'A','A' }; int int_c[2] = { 0,0 };
			while(1)
			{
				cct_setcolor(0);
				while (1)
				{
					bool flag = true;
					int res = cct_read_keyboard_and_mouse(m_x[1], m_y[1], m_action, k1, k2);
					if (m_x[0] == m_x[1] && m_y[0] == m_y[1])
					{

					}
					else
					{
						char_r[1] = 'A' + (m_y[1] - 4) / 4;
						int_c[1] = (m_x[1] / 2 - 2) / 4;
						m_x[0] = m_x[1];
						m_y[0] = m_y[1];

						if (m_y[1] - 3 < 0)
							flag = false;
						if ((m_x[1] / 2 - 1) % 4 == 0)
							flag = false;
						if ((m_y[1] - 3) % 4 == 0)
							flag = false;
					}

					cct_gotoxy(x, y);
					if (m_action == MOUSE_RIGHT_BUTTON_CLICK)
						return;
					if (m_action == MOUSE_LEFT_BUTTON_CLICK)
						break;
					if (k1 == 13)
						break;
					if (int_c[1] >= 0 && int_c[1] <= c - 1 && char_r[1] >= 'A' && char_r[1] <= 'A' + r - 1 && flag && mp[char_r[1]-'A'+1][int_c[1] + 1] != 0)
					{
						if (k1 == 0 && k2 == 0)//鼠标执行的操作
							cout << endl << "[当前鼠标]" << char_r[1] << "行 " << int_c[1] << "列                                                                  ";
						else//键盘执行的操作
						{
							if (k2 == KB_ARROW_DOWN)
							{
								if (char_r[1] - 'A' + 2 > r)
								{
									char_r[1] = 'A';
								}
								else
									char_r[1] = ((char_r[1] + 1));
							}
							else if (k2 == KB_ARROW_UP)
							{
								if (char_r[1] - 'A' - 1 < 0)
								{
									char_r[1] = char('A' + r - 1);
								}
								else
									char_r[1] = ((char_r[1] - 1));
							}
							else if (k2 == KB_ARROW_LEFT)
							{
								if (int_c[1] - 1 < 0)
								{
									int_c[1] = c;
								}
								else
									int_c[1]--;
							}
							else if (k2 == KB_ARROW_RIGHT)
							{
								if (int_c[1] + 1 >= c)
								{
									int_c[1] = 0;
								}
								else
									int_c[1]++;
							}

							cout << endl << "[当前键盘]" << char_r[1] << "行 " << int_c[1] << "列																		  ";
						}

						if (!(char_r[0] == char_r[1] && int_c[1] == int_c[0]))
						{
							//原来的消失
							{
								visual_chosen(mp, r, c, x, y, int_c, char_r, 0, 4, 5, 0);
							}

							//现在的打印
							{
								visual_chosen(mp, r, c, x, y, int_c, char_r, 7, 4, 5, 1);
							}
						}

						char_r[0] = char_r[1];
						int_c[0] = int_c[1];
						cct_setcolor(0);
						cct_gotoxy(x, y);
					}
					else
					{
						cout << endl << "[当前光标]" << "位置非法													";
					}
				}
				if (op == 5)
				{
					cct_gotoxy(x, y);
					cct_setcolor(0);
					cout << endl << "选择了" << char_r[1] << "行 " << int_c[1] << "列													" << endl;
					return;
				}
				if (op == 7)
				{
					cout << endl << "选择了" << char_r[1] << "行 " << int_c[1] << "列   鼠标左键或者回车表示消除  移开表示取消选择                             " << endl;
					int vis[12][12];
					memset(vis, 0, sizeof vis);
					check_same(mp, vis, r, c);
					if (vis[char_r[1] - 'A' + 1][int_c[1] + 1] == 0 && mp[char_r[1] - 'A' + 1][int_c[1] + 1] != 0)//无相同值
					{
						visual_chosen(mp, r, c, x, y, int_c, char_r, 7, 4, 7, 1);
						cct_gotoxy(x, y);
						cct_setcolor(0);
						cout << endl << "周围无相同值                                                      " << endl;
						while (1)
						{
							int res = cct_read_keyboard_and_mouse(m_x[1], m_y[1], m_action, k1, k2);
							if (m_action == MOUSE_RIGHT_BUTTON_CLICK)
								return;
							if (k1 == 0 && k2 == 0)
							{
								if (m_x[0] == m_x[1] && m_y[0] == m_y[1])
								{

								}
								else
								{

									break;//操作不一样会返回
								}
							}
							else if (k2 == KB_ARROW_DOWN)
							{
								if (char_r[1] - 'A' + 2 > r)
								{
									char_r[1] = 'A';
								}
								else
									char_r[1] = ((char_r[1] + 1));
								break;
							}
							else if (k2 == KB_ARROW_UP)
							{
								if (char_r[1] - 'A' - 1 < 0)
								{
									char_r[1] = char('A' + r - 1);
								}
								else
									char_r[1] = ((char_r[1] - 1));
								break;
							}
							else if (k2 == KB_ARROW_LEFT)
							{
								if (int_c[1] - 1 < 0)
								{
									int_c[1] = c;
								}
								else
									int_c[1]--;
								break;
							}
							else if (k2 == KB_ARROW_RIGHT)
							{
								if (int_c[1] + 1 >= c)
								{
									int_c[1] = 0;
								}
								else
									int_c[1]++;
								break;
							}
						}
						if ((!(char_r[0] == char_r[1] && int_c[1] == int_c[0])) && mp[char_r[1] - 'A' + 1][int_c[1] + 1] != 0)
						{
							//原来的消失
							{
								visual_chosen(mp, r, c, x, y, int_c, char_r, 0, 4, 7, 0);
							}

							//现在的打印
							{
								visual_chosen(mp, r, c, x, y, int_c, char_r, 7, 4, 7, 1);
							}
							char_r[0] = char_r[1];
							int_c[0] = int_c[1];
							cct_setcolor(0);
							cct_gotoxy(x, y);
						}
						continue;
					}
					else
					{
						visual_get_same(mp, r, c, x, y, int_c, char_r, 7, 7);
						while (1)
						{
							if (int_c[1] >= 0 && int_c[1] <= c - 1 && char_r[1] >= 'A' && char_r[1] <= 'A' + r - 1)
							{
								visual_chosen(mp, r, c, x, y, int_c, char_r, 15, 4, 7, 1);
							}
							cct_gotoxy(x, y);
							cct_setcolor(0);
							int res = cct_read_keyboard_and_mouse(m_x[1], m_y[1], m_action, k1, k2);
							if (m_action == MOUSE_RIGHT_BUTTON_CLICK)
								return;

							if (m_action == MOUSE_LEFT_BUTTON_CLICK || k1 == 13)
							{
								int flag[12][12];
								memset(flag, 0, sizeof flag);
								replace0(mp, flag, mp, r, c, char_r[1] - 'A' + 1, int_c[1] + 1);
								for (int i = 1; i <= r; i++)
								{
									for (int j = 1; j <= c; j++)
									{
										if (mp[i][j] == 0)
										{
											int now_c[2] = { 0,j - 1 };
											char now_r[2] = { 0,char(i - 1 + 'A') };
											visual_remove(mp, r, c, x, y, now_c, now_r, 15, 4, 7, 1);
										}
									}
								}
								cct_gotoxy(20, 0);
								getscore(mp, &score, &now_0, r, c);
								visual_renew_mp(mp, r, c, x, y, 7);
								cct_setcolor(0);
								cct_gotoxy(x, y);
								continue;
							}

							if (k1 == 0 && k2 == 0)
							{
								if (m_x[0] == m_x[1] && m_y[0] == m_y[1])
								{
									continue;
								}
								else
								{
									char nowr = 'A' + (m_y[1] - 4) / 4;
									int nowc = (m_x[1] / 2 -2) /4;
									if ((char_r[0] == nowr && int_c[1] == nowc))
									{
										continue;
									}
									visual_get_same(mp, r, c, x, y, int_c, char_r, 7, 0);
									break;//操作不一样会返回
								}
							}
							else if (k2 == KB_ARROW_DOWN)
							{
								visual_get_same(mp, r, c, x, y, int_c, char_r, 7, 0);
								if (char_r[1] - 'A' + 2 > r)
								{
									char_r[1] = 'A';
								}
								else
									char_r[1] = ((char_r[1] + 1));
								break;//操作不一样会返回
							}
							else if (k2 == KB_ARROW_UP)
							{
								visual_get_same(mp, r, c, x, y, int_c, char_r, 7, 0);
								if (char_r[1] - 'A' - 1 < 0)
								{
									char_r[1] = char('A' + r - 1);
								}
								else
									char_r[1] = ((char_r[1] - 1));
								break;//操作不一样会返回
							}
							else if (k2 == KB_ARROW_LEFT)
							{
								visual_get_same(mp, r, c, x, y, int_c, char_r, 7, 0);
								if (int_c[1] - 1 < 0)
								{
									int_c[1] = c;
								}
								else
									int_c[1]--;
								break;//操作不一样会返回
							}
							else if (k2 == KB_ARROW_RIGHT)
							{
								visual_get_same(mp, r, c, x, y, int_c, char_r, 7, 0);
								if (int_c[1] + 1 >= c)
								{
									int_c[1] = 0;
								}
								else
									int_c[1]++;
								break;//操作不一样会返回
							}
							break;
						}
						if ((!(char_r[0] == char_r[1] && int_c[1] == int_c[0])) && mp[char_r[1] - 'A' + 1][int_c[1] + 1] != 0)
						{
							//原来的消失
							{
								visual_chosen(mp, r, c, x, y, int_c, char_r, 0, 4, 7, 0);
								visual_get_same(mp, r, c, x, y, int_c, char_r, 7, 0);
							}

							//现在的打印
							{
								visual_chosen(mp, r, c, x, y, int_c, char_r, 7, 3, 7, 1);
							}
							char_r[0] = char_r[1];
							int_c[0] = int_c[1];
							cct_setcolor(0);
							cct_gotoxy(x, y);
						}
						visual_check_c_0(mp, r, c, x, y, op);


						cct_setcolor(0);

						if (!check_end(mp, r, c))
						{
							cct_gotoxy(x, y);
							cct_setcolor(0);
							cout << "剩余" << r*c-now_0<<"个星星，无可消除项，本关结束！回车继续下一关                                         ";
							int cmd;
							while (1)
							{
								cmd = _getch();
								if (cmd == 13)
								{
									break;
								}
							}
							if (r * c - now_0 < 10)
							{
								score += (10 - r * c + now_0) * 180;
							}
							game(7, score);
						}

					}
				}
			}
			
		}
	}
}