/*2351114 朱俊泽 信15*/
#pragma once


//在graph.cpp中
void print_without_edge(int mp[12][12], int r, int c, int op);
void visual_show_same(int mp[12][12], int r, int c,int op);
int visual_remove(int mp[12][12], int r, int c, int op);
void dfs(int mp[12][12], int vis[12][12], int r, int c, int op);
void visual_replace_by_0(int mp[12][12], int r, int c);
void visual_renew(int mp[12][12], int  r, int c);
void visual_show_potential(int vis[12][12],int mp[12][12], int r, int c);
bool choose_ball(int mp[12][12], int nr, int nc, int pr, int pc);

//在tools.cpp中
void show_score(int now);
bool check_end(int vis[12][12], int r, int c);

//在base.cpp中
void game(int op);
void show_same(int mp[12][12], int r, int c);
bool check_same(int mp[12][12], int r, int c);
void renew(int mp[12][12], int r, int c,int op);
void show_potential(int mp[12][12], int r, int c);