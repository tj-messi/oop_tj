/* 计科 2150792 牛禄阳 */
#pragma once
//90-01-b1菜单提示信息
const char* const menu_infor_90_01_b1[] = {
	"1.基本解","2.基本解(步数记录)","3.内部数组显示(横向)",
	"4.内部数组显示(纵向+横向)","5.图形解-预备-画三个圆柱","6.图形解-预备-在起始柱上画n个盘子",
	"7.图形解-预备-第一次移动","8.图形解-自动移动版本","9.图形解-游戏版","0.退出" };
const char total_choice_90_01_b1[] = { '1','2','3','4','5','6','7','8','9','0' };
const int infor_num_90_01_b1 = 10;
/*常变量定义*/
const int START_Y = 12;
const int START_X = 9;
const int A_locate_X = 11;
const int B_locate_X = 21;
const int C_locate_X = 31;
const int A_locate_X_color = 13;
const int B_locate_X_color = 46;
const int C_locate_X_color = 79;
//功能函数
//按回车继续的函数
void huiche_conti();
//实现汉诺塔内部数组移动的函数
void move_hanoi(char src, char dst);
//将汉诺塔三个数组初始数据存入数组中的函数
void store_chushi(int n, char src, char dst);
//将汉诺塔三个数组清空的函数
void clear_array();
//将输入的延时转换为对应的Sleep()参数的函数
int change_yanshi_ms();
//最重要的汉诺塔递归函数
void hanoi(int n, char src, char tmp, char dst, char choice);
//层数，起始柱，目标柱，延时的输入函数
void cin_hanoi(char* sta, char* tmp, char* des, int* n, int select);
//对应第九项起始柱和目标柱的输入函数
int cin_exe_9(char* sta, char* des);
//递归函数内根据实现功能调用其他函数的函数
void select_hanoi(int n, char src, char dst, char choice);

//main函数直接调用的对应各功能的执行函数
void exe_1(int n, char src, char tmp, char dst, char choice);
void exe_2(int n, char src, char tmp, char dst, char choice);
void exe_3(int n, char src, char tmp, char dst, char choice);
void exe_4(int n, char src, char tmp, char dst, char choice);
void exe_5();
void exe_6(int n, char src, char tmp, char dst, char choice);
void exe_7(int n, char src, char tmp, char dst, char choice);
void exe_8(int n, char src, char tmp, char dst, char choice);
void exe_9(int n, char src, char tmp, char dst, char choice);

//以下是打印函数
// 
//功能一打印的函数
void print_1(int n, char src, char dst);
//功能二对应的打印函数
void print_2(int n, char src, char dst);
//打印横向输出的函数
void print_3_4_8_hengxiang(int n, char src, char dst, int select_chushi, int locate);
//打印纵向输出的函数
void print_4_8_zongxiang(int n, char src, char dst, int select_chushi, int locate);
//打印三个柱子的函数
void print_5();
//将对应盘子打印在初始柱上的函数
void print_6(int n, char src, char tmp, char dst);
//8，9功能中移动盘子的函数
void move_color(int n, char src, char dst);


/* ------------------------------------------------------------------------------------------------------

	 本文件功能：
	1、为了保证 hanoi_main.cpp/hanoi_menu.cpp/hanoi_multiple_solutions.cpp 能相互访问函数的函数声明
	2、一个以上的cpp中用到的宏定义（#define）或全局只读（const）变量，个数不限
	3、可以参考 cmd_console_tools.h 的写法（认真阅读并体会）
   ------------------------------------------------------------------------------------------------------ */

