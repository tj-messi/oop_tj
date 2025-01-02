/* 计科 2150792 牛禄阳 */
#pragma once
/* =====================公共库函数文件及命名空间===================== */
#include<iostream>
#include<iomanip>
#include<cmath>
#include<conio.h>
#include<time.h>
#include<Windows.h>
using namespace std;

/* =====================公共自定义函数===================== */
char menu(const char * const menu_infor[], const char total_choice[],const int infor_num);
int input_end_continue();
int get_input_int(int low, int high, int& elem_int, int base = 1);

