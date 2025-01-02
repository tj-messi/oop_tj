#pragma once

/* ROW 和 COL 会被替换为其他值 */
const int ROW = 2;
const int COL = 3;

/* 宏定义的值会在0/1之间任意更改 */
#define OPERATOR_IS_MENBER_FUNCTION		1	//运算符的重载用成员函数方式实现（如果值为0，表示用友元方式实现）

/* 为了测试，此处只能用全局变量，为限制权限，使用静态全局 */
static int a[ROW][COL] = { { 1,2,3 },{ 4,5,6 } };
static int b[ROW][COL] = { { 2,4,6 },{ 3,6,9 } };

//本文件不需要提交，自己测试时允许任意改动
