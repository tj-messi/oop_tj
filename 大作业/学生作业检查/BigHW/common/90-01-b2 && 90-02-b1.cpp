#include"../include/cmd_console_tools.h"
#include <iostream>
#include <iomanip>
#include <tchar.h>
#include <string.h>
#include <Windows.h>
#include<conio.h>
#include<time.h>
#include<stdlib.h>
using namespace std;

void initial_mp(int mp[12][12], int x, int y,int top)
{
	int rd = rand() % top + 1;
	mp[x][y] = rd;
}
void show_mp(int mp[12][12], int r, int c ,int start_0)
{
	cout << "  |";
	for (int i = 1; i <= c; i++)
		cout << "  " << i - start_0;
	cout << endl << "--+";
	for (int i = 1; i <= c; i++)
		cout << "---";
	cout << endl;
	for (int i = 1; i <= r; i++)
	{
		cout << (char)('A' + (i - 1)) << " |";
		for (int j = 1; j <= c; j++)
		{
			cout << "  " << mp[i][j];
		}
		cout << endl;
	}
}

void show_0(int mp[12][12], int r, int c, int same[12][12])
{

	int x, y;
	cct_getxy(x, y);
	for (int i = 1; i <= r; i++)
	{
		for (int j = 1; j <= c; j++)
		{
			if (same[i][j] == 0)
			{
				cct_showch(2 + 3 * (j), y - r + i - 1, mp[i][j] + '0', 14, 1, 1);
			}
		}
	}
	cct_gotoxy(x, y);
	cct_setcolor(0);
}


bool check_full_0(int mp[12][12], int r, int c)
{
	for (int i = r; i >= 1; i--)
	{
		if (mp[i][c] != 0)
			return false;
	}
	return true;
}
void replace_by_0(int mp[12][12], int r, int c, int flg=1)
{
	int vis[10][10];
	memset(vis, 0, sizeof vis);
	for (int i = 1; i <= r; i++)
	{
		for (int j = 1; j <= c - 2; j++)
		{
			if (mp[i][j] == mp[i][j + 1] && mp[i][j + 1] == mp[i][j + 2])
			{
				vis[i][j] = 1;
				vis[i][j + 1] = 1;
				vis[i][j + 2] = 1;
			}
		}
	}
	for (int i = 1; i <= c; i++)
	{
		for (int j = 1; j <= r - 2; j++)
		{
			if (mp[j][i] == mp[j + 1][i] && mp[j + 1][i] == mp[j + 2][i])
			{
				vis[j][i] = 1;
				vis[j + 1][i] = 1;
				vis[j + 2][i] = 1;
			}
		}
	}
	if (flg == 1)
	{
		for (int i = 1; i <= r; i++)
		{
			for (int j = 1; j <= c; j++)
			{
				if (vis[i][j])
					mp[i][j] = 0;
			}
		}
	}

	for (int i = r; i >= 1; i--)
	{
		for (int j = 1; j <= c; j++)
		{
			while (mp[i][j] == 0 && !check_full_0(mp, i, j))
			{
				for (int k = i; k > 1; k--)
				{
					mp[k][j] = mp[k - 1][j];
				}
				mp[1][j] = 0;
			}
		}
	}
}
