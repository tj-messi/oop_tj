#pragma once

//基础a-c
void game(int op,int score);
void check_same(int mp[12][12], int vis[12][12], int r, int c);
void replace0(int mp[12][12], int flag[12][12], int same[12][12], int r, int c, int x, int y);
void getscore(int mp[12][12], int* now_score, int* now_0, int r, int c);
bool check_end(int mp[12][12], int r, int c);
void check_c_full_of_0(int mp[12][12], int r, int c);

//可视化d-g
void visual_print(int mp[12][12], int r, int c, int op);
void visual_chosen(int mp[12][12], int r, int c, int x, int y, int int_c[2], char char_r[2], int col, int plu, int op, int idx);
void visual_get_same(int mp[12][12], int r, int c, int x, int y, int int_c[2], char char_r[2], int op,int col);
void visual_remove(int mp[12][12], int r, int c, int x, int y, int int_c[2], char char_r[2], int col, int plu, int op, int idx);