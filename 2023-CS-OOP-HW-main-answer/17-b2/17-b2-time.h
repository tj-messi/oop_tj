/* 2150792 �ƿ� ţ»�� */
#pragma once

#include <iostream>
#include <iomanip>
using namespace std;

/* ���������ȫ�ֺ�����Ҫ������д�ڴ˴� */

int check_minorsec_legal(const int minsec);
int check_hour_legal(const int h);

const int TIMEMAXNUM = 86400;
/* Time������� */ 
class Time {
protected:
	/* �����������⣬�������ٶ����κ����ݳ�Ա */ 
	int hour;
	int minute;
	int second;
public:
	/* ������Ҫ�ĳ�Ա��������Ԫ���������� */
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
