/*2351114 朱俊泽 大数据*/
#pragma once

#include <string>
#include <stdexcept>
#include <iostream>
using namespace std;

enum class week { sun, mon, tue, wed, thu, fri, sat };

/* 允许添加相应的函数声明 */



// 运算符声明
std::ostream& operator<<(std::ostream& os, const week& w);
std::istream& operator>>(std::istream& is, week& w);
week operator++(week& w);         // 前置++
week operator++(week& w, int);    // 后置++
week operator--(week& w);         // 前置--
week operator--(week& w, int);    // 后置--
week operator+(const week& w, int n);
week operator-(const week& w, int n);
week& operator+=(week& w, int n);
week& operator-=(week& w, int n);
