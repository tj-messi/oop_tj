/*2150792 计科 牛禄阳*/
#pragma once
//结构体和常变量的定义
struct elem_queue
{
	int x, y;
};
const int dx[] = { 1,0,-1,0 };
const int dy[] = { 0,1,0,-1 };//定义BFS算法找相邻元素的顺序，即为：右、下、左、上
//90-01-b2的菜单提示信息常变量
const char* const menu_infor_90_01_b2[] = {
	"1.内部数组，随机生成初始5个球",
	"2.内部数组，随机生成60%的球，寻找移动路径",
	"3.内部数组，完整版游戏",
	"4.画出n*n的框架（无分隔线），随机显示5个球",
	"5.画出n*n的框架（有分隔线），随机显示5个球",
	"6.n*n的框架，60%的球，支持鼠标，完成一次移动",
	"7.cmd图形界面完整版游戏",
	"0.退出"
};
const char total_choice_90_01_b2[] = { '1','2','3','4','5','6','7','0' };
const int infor_num_90_01_b2 = 8;

//内部数组方式实现函数

//功能一的执行函数
void fun_1(char choice);
//功能二的执行函数
void fun_2(char choice);
//功能三的执行函数
void fun_3(char choice);
//输入移动的球的起始和目的坐标
int inputdata_move(int line, int col, char* sta_line, char* sta_col, char* des_line, char* des_col, int a[9][9]);
//打印内部数组的彩色版
void print_game_array(int a[9][9], int line, int col, char choice, int b[3], elem_queue back_path[100]);


//cmd界面方式实现函数

//功能四的执行函数
void fun_4(char choice);
//功能五的执行函数
void fun_5(char choice);
//功能六的执行函数
void fun_6(char choice);
//功能七的执行函数
void fun_7(char choice);
//cmd界面相连球的动态消除
void del_ball_dynamic(elem_queue delete_locate[100], int number);
//cmd界面画框框
void print_gird(int line, int col, char choice, int sta_col);
//cmd界面打印一个彩色的球
void print_ball(int color, int des_line, int des_col, char choice);
//cmd界面改变cmd窗口的大小和字体
void change_typeface_cmd(int set_lines, int set_cols, char choice);
//cmd界面彩球的动态移动
int move_ball_dynamic(int line, char sta_line, char sta_col, char des_line, char des_col, elem_queue back_path[100], int a[9][9], char choice);
//cmd界面的鼠标操作
int mouse_operate(int line, int col, char* sta_line, char* sta_col, char* des_line, char* des_col, int a[9][9]);


//被cmd和数组方式共用的函数

//输入行和列
void inputdata_linecol(int* line, int* col);
//输入回车继续
void huiche_conti();
//检查游戏是否结束（数组已满）
int check_game_over(int a[9][9], int line, int col);
//判断彩球能否被消除
int check_ball_delete(int a[9][9], int line, int col, int* color_ball, elem_queue delete_locate[100] = { 0 });
//在内部数组中添加彩球（最开始以及后续每次加三个）
int append_game_array(char choice, int a[9][9], int line, int col, int b[], int flag_first);
//根据彩球移动的起始和目的坐标，改变内部数组的值
void move_game_array(char choice, int a[9][9], char sta_line, char sta_col, char des_line, char des_col);
//寻找移动的最短路径
int search_game_road(char choice, int a[9][9], elem_queue back_path[100], int line, int col, char sta_line, char sta_col, char des_line, char des_col);
//将移动的最短路径记录在数组中
int get_path(int x, int y, elem_queue a[9][9], char sta_col, char sta_line, elem_queue b[100]);
