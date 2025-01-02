/* 2150792 计科 牛禄阳 */
#include <iostream>
#include <iomanip>
#include "17-b2-time.h"
using namespace std;

/* --- 给出Time类的成员函数的体外实现(含友元及其它必要的公共函数)  --- */ 
Time::Time()
{
	hour = 0;
	minute = 0;
	second = 0;
}
Time::Time(int hou, int min, int sec)
{
	this->set(hou, min, sec);
}
Time::Time(int totalsec)
{
	while (totalsec < 0)
		totalsec += TIMEMAXNUM;
	totalsec %= TIMEMAXNUM;
	set(0, 0, 0);
	/* 求得hour */
	while (totalsec >= 3600)
	{
		totalsec -= 3600;
		++hour;
	}
	/* 求得minute */
	while (totalsec >= 60)
	{
		totalsec -= 60;
		++minute;
	}
	/* 求得second */
	second = totalsec;
}
void Time::set(int hou, int min, int sec)
{
	int good = 1;
	good &= check_hour_legal(hou);
	good &= check_minorsec_legal(min);
	good &= check_minorsec_legal(sec);
	if (good == 0)
	{
		hour = 0;
		minute = 0;
		second = 0;
	}
	else
	{
		hour = hou;
		minute = min;
		second = sec;
	}
}
void Time::show()
{
	cout << setfill('0') << setw(2) << hour << ':';
	cout << setfill('0') << setw(2) << minute << ':';
	cout << setfill('0') << setw(2) << second;
	cout << endl;
}
void Time::get(int& hou, int& min, int& sec)
{
	hou = hour;
	min = minute;
	sec = second;
}
/* 类型转换函数，Time -> int */
Time::operator int() const
{
	int totalsec = 0;
	for (int i = 0; i < hour; i++)
		totalsec += 3600;
	for (int i = 0; i < minute; i++)
		totalsec += 60;
	totalsec += second;
	return totalsec;
}
/* 运算符重载 */
Time operator + (const Time& time, const int sec)
{
	int totalsec = (int)time + sec;
	totalsec %= TIMEMAXNUM;
	return Time(totalsec);
}
Time operator +(const int sec, const Time& time)
{
	int totalsec = (int)time + sec;
	totalsec %= TIMEMAXNUM;
	return Time(totalsec);
}
int  operator -(const Time& time1, const Time& time2)
{
	return (int)time1 - (int)time2;
}
Time operator -(const Time& time, const int sec)
{
	int totalsec = (int)time - sec;
	while (totalsec < 0)
		totalsec += TIMEMAXNUM;
	totalsec %= TIMEMAXNUM;
	return Time(totalsec);
}
Time& Time::operator ++ ()
{
	int totalsec = (int)*this;
	totalsec++;
	totalsec %= TIMEMAXNUM;
	*this = Time(totalsec);
	return *this;
}
Time  Time::operator ++ (int)
{
	Time temp(this->hour, this->minute, this->second);
	int totalsec = (int)*this;
	totalsec++;
	totalsec %= TIMEMAXNUM;
	*this = Time(totalsec);
	return temp;
}
Time& Time::operator -- ()
{
	int totalsec = (int)*this;
	totalsec--;
	while (totalsec < 0)
		totalsec += TIMEMAXNUM;
	totalsec %= TIMEMAXNUM;
	*this = Time(totalsec);
	return *this;
}
Time  Time::operator -- (int)
{
	Time temp(this->hour, this->minute, this->second);
	int totalsec = (int)*this;
	totalsec--;
	while (totalsec < 0)
		totalsec += TIMEMAXNUM;
	totalsec %= TIMEMAXNUM;
	*this = Time(totalsec);
	return temp;
}
ostream& operator << (ostream& out, const Time& time)
{
	out << setfill('0') << setw(2) << time.hour << ':';
	out << setfill('0') << setw(2) << time.minute << ':';
	out << setfill('0') << setw(2) << time.second;
	return out;
}
istream& operator >> (istream& in, Time& time)
{
	int y, min, sec;
	in >> y >> min >> sec;
	time.set(y, min, sec);
	return in;
}
bool operator <  (const Time& time1, const Time& time2)
{
	return (int)time1 <  (int)time2;
}
bool operator >  (const Time& time1, const Time& time2)
{
	return (int)time1 >  (int)time2;
}
bool operator == (const Time& time1, const Time& time2)
{
	return (int)time1 == (int)time2;
}
bool operator != (const Time& time1, const Time& time2)
{
	return (int)time1 != (int)time2;
}
bool operator >= (const Time& time1, const Time& time2)
{
	return (int)time1 >= (int)time2;
}
bool operator <= (const Time& time1, const Time& time2)
{
	return (int)time1 <= (int)time2;
}

/* 公共函数的实现 */
int check_hour_legal(const int hou)
{
	if (hou < 0 || hou >= 24)
		return 0;
	else
		return 1;
}
int check_minorsec_legal(const int minsec)
{
	if (minsec < 0 || minsec >= 60)
		return 0;
	else
		return 1;
}
