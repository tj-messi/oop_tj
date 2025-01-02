/* 2150792 计科 牛禄阳 */
#pragma once

#include <iostream>
#include <cstring>
using namespace std;

/* 如果有其它全局函数需要声明，写于此处 */
int  check_year_legal(const int year);
int  check_month_legal(const int month);
int  check_day_legal(const int year, const int month, const int day);
bool is_leapyear(const int year);
/* 如果有需要的宏定义、只读全局变量等，写于此处 */
const int MAXDATENUM = 73049;

/* 补全Date类的定义，所有成员函数均体外实现，不要在此处体内实现 */
class Date {
protected:
	int year;
	int month;
	int day;
	/* 不允许添加数据成员 */
public:
	/* 根据需要定义所需的成员函数、友元函数等(不允许添加数据成员) */
	Date();                                      // 默认构造函数
	Date(const int y, const int m, const int d); // 三参构造函数
	void set(const int y = 2000, const int m = 1, const int d = 1); // set成员函数
	void get(int& y, int& m, int& d);
	void show();
	Date(int totalday); // 转换构造函数，int->Date
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
	/* 自定义成员函数 */
	operator int() const;  // 类型转换函数，将Date对象转化为int类型的天数
};

