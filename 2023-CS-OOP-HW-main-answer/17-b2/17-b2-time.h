/* 2150792 计科 牛禄阳 */
#pragma once

#include <iostream>
#include <iomanip>
using namespace std;

/* 如果有其它全局函数需要声明，写于此处 */

int check_minorsec_legal(const int minsec);
int check_hour_legal(const int h);

const int TIMEMAXNUM = 86400;
/* Time类的声明 */ 
class Time {
protected:
	/* 除这三个以外，不允许再定义任何数据成员 */ 
	int hour;
	int minute;
	int second;
public:
	/* 允许需要的成员函数及友元函数的声明 */
	Time();
	Time(int hou, int min, int sec);
	void set(const int hou = 0, const int min = 0, const int sec = 0);
	void get(int& hou, int& min, int& sec);
	void show();
	operator int() const;
	Time(int _secs);
	friend Time operator +(const Time& time, const int sec);
	friend Time operator +(const int sec, const Time& time);
	friend int operator -(const Time& time1, const Time& time2);
	friend Time operator -(const Time& time, const int sec);
	Time& operator ++();
	Time operator ++(int);
	Time& operator --();
	Time operator --(int);
	friend ostream& operator << (ostream& out, const Time& time);
	friend istream& operator >> (istream& in, Time& time);
	friend bool operator <  (const Time& time1, const Time& time2);
	friend bool operator >  (const Time& time1, const Time& time2);
	friend bool operator == (const Time& time1, const Time& time2);
	friend bool operator != (const Time& time1, const Time& time2);
	friend bool operator >= (const Time& time1, const Time& time2);
	friend bool operator <= (const Time& time1, const Time& time2);
};
