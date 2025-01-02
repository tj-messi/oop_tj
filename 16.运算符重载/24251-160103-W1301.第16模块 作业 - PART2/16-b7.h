/*2351114 朱俊泽 大数据*/
#pragma once
#include <string>
#include <iostream>
using namespace std;

enum week { sun, mon, tue, wed, thu, fri, sat };

/* 允许添加相应的函数声明 */

// 重载输入输出流操作符
ostream& operator<<(ostream& os, const week& w);
istream& operator>>(istream& is, week& w);

// 重载前置和后置++操作符
week& operator++(week& w);   // 前置
week operator++(week& w, int); // 后置

// 重载前置和后置--操作符
week& operator--(week& w);   // 前置
week operator--(week& w, int); // 后置

// 重载加法、减法操作符
week operator+(const week& w, int n);
week operator-(const week& w, int n);

// 重载加等、减等操作符
week& operator+=(week& w, int n);
week& operator-=(week& w, int n);
