#pragma once
void initial_mp(int mp[12][12], int x, int y,int top);
void show_mp(int mp[12][12], int r, int c, int start_0);
void show_0(int mp[12][12], int r, int c, int same[12][12]);
bool check_full_0(int mp[12][12], int r, int c);
void replace_by_0(int mp[12][12], int r, int c, int flg = 1);