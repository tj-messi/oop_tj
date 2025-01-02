/* 2150792 计科 牛禄阳 */
#include <iostream>
#include <iomanip>
#include "17-b2-datetime.h"
using namespace std;

/* --- 给出DateTime类的成员函数的体外实现(含友元及其它必要的公共函数)  ---

	几个重要提示：
	1、6参构造函数能否空函数体，直接激活Date和Time的构造函数？
	2、1参构造函数，能否不用循环，直接借助Date和Time的一参构造来快速实现？ 
	3、DateTime转long long的类型转换函数，能否不用循环，借助赋值兼容规则快速实现（(最短可以做到只有一句return)） 
	4、DateTime土n的操作，需要定义几个类型的运算符重载？ 
*/ 
DateTime::DateTime() : Date(), Time()
{
}
DateTime::DateTime(int y, int m, int d, int hou, int min, int sec)
{	// 需要满足任意一个数据成员错误均设置为默认值，所以无法调用成员的构造函数
	int good = 1;
	good &= check_minorsec_legal(min);
	good &= check_minorsec_legal(sec);
	good &= check_hour_legal(hou);
	good &= check_year_legal(y);
	good &= check_month_legal(m);
	if (good == 0)
	{
		year = 1900;
		month = 1;
		day = 1;
		hour = 0;
		minute = 0;
		second = 0;
		return;
	}
	else
	{
		year = y;
		month = m;
	}
	good &= check_day_legal(year, month, d); // check_day之前需要保证year和month合法
	if (good == 0)
	{
		year = 1900;
		month = 1;
		day = 1;
		hour = 0;
		minute = 0;
		second = 0;
	}
	else
	{
		day = d;
		hour = hou;
		minute = min;
		second = sec;
	}
}
DateTime::DateTime(long long totalsec)
{
	while (totalsec < 0)
		totalsec += DATATIMEMAXNUM;
	totalsec %= DATATIMEMAXNUM;
	int y, m, d, hou, min, sec;
	Date nowday((int)(totalsec / sec_aday));
	Time nowtime((int)(totalsec % sec_aday));
	nowday.get(y, m, d);
	nowtime.get(hou, min, sec);
	(*this) = DateTime(y, m, d, hou, min, sec);
}
void DateTime::set(long long totalsec)
{
	if (totalsec < 0 || totalsec >= DATATIMEMAXNUM)
		(*this) = DateTime();
	else
	{
		int y, m, d, hou, min, sec;
		Date nowday((int)(totalsec / sec_aday));
		Time nowtime((int)(totalsec % sec_aday));
		nowday.get(y, m, d);
		nowtime.get(hou, min, sec);
		(*this) = DateTime(y, m, d, hou, min, sec);
	}
}
void DateTime::set(int y, int m, int d, int hou, int min, int sec)
{
	(*this) = DateTime(y, m, d, hou, min, sec);
}
void DateTime::get(int& y, int& m, int& d, int& hou, int& min, int& sec) const
{
	y = year;
	m = month;
	d = day;
	hou = hour;
	min = minute;
	sec = second;
}
Date DateTime::getDate() const
{
	return Date(year, month, day);
}
Time DateTime::getTime() const
{
	return Time(hour, minute, second);
}
void DateTime::show() const
{
	cout << Date(year, month, day) << " " << Time(hour, minute, second) << endl;
}
DateTime::operator long long() const
{
	long long totalsec = 0;
	totalsec = ((int)Date(year, month, day) * sec_aday) + (long long)((int)Time(hour, minute, second));
	return totalsec;
}
/* 运算符重载 */
DateTime operator + (const DateTime& datetime, long long sec)
{
	long long totalsec = (long long)datetime + sec;
	while (totalsec < 0)
		totalsec += DATATIMEMAXNUM;
	totalsec %= DATATIMEMAXNUM;
	DateTime temp(totalsec);
	return temp;
}
DateTime operator + (long long sec, const DateTime& datetime)
{
	long long totalsec = (long long)datetime + sec;
	while (totalsec < 0)
		totalsec += DATATIMEMAXNUM;
	totalsec %= DATATIMEMAXNUM;
	DateTime temp(totalsec);
	return temp;
}
#if defined(__linux) || defined(__linux__)
DateTime operator + (const DateTime& datetime, long int sec)
{
	long long totalsec = (long long)datetime + sec;
	while (totalsec < 0)
		totalsec += DATATIMEMAXNUM;
	totalsec %= DATATIMEMAXNUM;
	DateTime temp(totalsec);
	return temp;
}
DateTime operator + (long int sec, const DateTime& datetime)
{
	long long totalsec = (long long)datetime + sec;
	while (totalsec < 0)
		totalsec += DATATIMEMAXNUM;
	totalsec %= DATATIMEMAXNUM;
	DateTime temp(totalsec);
	return temp;
}
DateTime operator - (const DateTime& a, long int sec)
{
	long long totalsec = (long long)a - sec;
	while (totalsec < 0)
		totalsec += DATATIMEMAXNUM;
	totalsec %= DATATIMEMAXNUM;
	DateTime temp(totalsec);
	return temp;
}
#endif
DateTime operator + (const DateTime& datetime, int sec)
{
	long long totalsec = (long long)datetime + sec;
	while (totalsec < 0)
		totalsec += DATATIMEMAXNUM;
	totalsec %= DATATIMEMAXNUM;
	DateTime temp(totalsec);
	return temp;
}
DateTime operator + (int sec, const DateTime& datetime)
{
	long long totalsec = (long long)datetime + sec;
	while (totalsec < 0)
		totalsec += DATATIMEMAXNUM;
	totalsec %= DATATIMEMAXNUM;
	DateTime temp(totalsec);
	return temp;
}
long long operator - (const DateTime& a, const DateTime& b)
{
	return (long long)a - (long long)b;
}
DateTime operator - (const DateTime& a, long long sec)
{
	long long totalsec = (long long)a - sec;
	while (totalsec < 0)
		totalsec += DATATIMEMAXNUM;
	totalsec %= DATATIMEMAXNUM;
	DateTime temp(totalsec);
	return temp;
}
DateTime operator - (const DateTime& a, int sec)
{
	long long totalsec = (long long)a - sec;
	while (totalsec < 0)
		totalsec += DATATIMEMAXNUM;
	totalsec %= DATATIMEMAXNUM;
	DateTime temp(totalsec);
	return temp;
}
DateTime& DateTime::operator ++ ()
{
	long long totalsec = (long long)(*this) + 1;
	totalsec %= DATATIMEMAXNUM;
	set(totalsec);
	return *this;
}
DateTime DateTime::operator ++ (int)
{
	DateTime temp = (*this);
	long long totalsec = (long long)(*this) + 1;
	totalsec %= DATATIMEMAXNUM;
	set(totalsec);
	return temp;
}
DateTime& DateTime::operator -- ()
{
	long long totalsec = (long long)(*this) - 1;
	while (totalsec < 0)
		totalsec += DATATIMEMAXNUM;
	totalsec %= DATATIMEMAXNUM;
	set(totalsec);
	return *this;
}
DateTime DateTime::operator -- (int)
{
	DateTime temp = (*this);
	long long totalsec = (long long)(*this) - 1;
	while (totalsec < 0)
		totalsec += DATATIMEMAXNUM;
	totalsec %= DATATIMEMAXNUM;
	set(totalsec);
	return temp;
}
bool operator < (const DateTime& a, const DateTime& b)
{
	if (a.getDate() < b.getDate())
		return true;
	if (a.getDate() > b.getDate())
		return false;
	return a.getTime() < b.getTime() ? true : false;
}
bool operator > (const DateTime& a, const DateTime& b)
{
	if (a.getDate() > b.getDate())
		return true;
	if (a.getDate() < b.getDate())
		return false;
	return a.getTime() > b.getTime() ? true : false;
}
bool operator <= (const DateTime& a, const DateTime& b)
{
	if (a.getDate() > b.getDate())
		return false;
	return a.getTime() <= b.getTime() ? true : false;
}
bool operator >= (const DateTime& a, const DateTime& b)
{
	if (a.getDate() < b.getDate())
		return false;
	return a.getTime() >= b.getTime() ? true : false;
}
bool operator != (const DateTime& a, const DateTime& b)
{
	if (a.getDate() != b.getDate() || a.getTime() != b.getTime())
		return true;
	return false;
}
bool operator == (const DateTime& a, const DateTime& b)
{
	if (a.getDate() == b.getDate() && a.getTime() == b.getTime())
		return true;
	return false;
}
ostream& operator << (ostream& out, const DateTime& a)
{
	out << Date(a.year, a.month, a.day) << " " << Time(a.hour, a.minute, a.second);
	return out;
}
istream& operator >> (istream& in, DateTime& a)
{
	int y, m, d, hou, min, sec;
	in >> y >> m >> d >> hou >> min >> sec;
	a.set(y, m, d, hou, min, sec);
	return in;
}
