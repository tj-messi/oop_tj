/*2351114 朱俊泽 大数据*/

#pragma once

#include <iostream>
using namespace std;

/* 如果有其它全局函数需要声明，写于此处 */
int  check_year_legal(const int year);
int  check_month_legal(const int month);
int  check_day_legal(const int year, const int month, const int day);
bool is_leapyear(const int year);
/* 如果有需要的宏定义、只读全局变量等，写于此处 */

/* 补全Date类的定义，所有成员函数均体外实现，不要在此处体内实现 */
class Date {
private:
	int year;
	int month;
	int day;
	/* 不允许添加数据成员 */
public:
	/* 根据需要定义所需的成员函数、友元函数等(不允许添加数据成员) */
	Date();                                      
	Date(const int y, const int m, const int d); 
	Date(int totalday); 

	operator int() const;

	void set(const int y = 2000, const int m = 1, const int d = 1); // set成员函数
	void get(int& y, int& m, int& d);
	void show();

	friend Date operator+(const Date& date, const int a);
	friend Date operator+(const int a, const Date& date);
	friend Date operator-(const Date& date, const int a);
	friend int operator-(const Date& date1, const Date& date2);

	Date& operator ++();
	Date operator ++(int);
	Date& operator --();
	Date operator --(int);

	friend ostream& operator << (ostream& out, const Date& date);
	friend istream& operator >> (istream& in, Date& date);

	bool operator <(const Date& date);
	bool operator >(const Date& date);
	bool operator == (const Date& date);

	friend bool operator !=(const Date& date1, const Date& date2);
	friend bool operator >=(const Date& date1, const Date& date2);
	friend bool operator <=(const Date& date1, const Date& date2);
};
