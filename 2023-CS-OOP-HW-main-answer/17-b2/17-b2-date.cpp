/* 2150792 计科 牛禄阳 */
#include <iostream>
#include <iomanip>
#include "17-b2-date.h"
using namespace std;

/* --- 给出Date类的成员函数的体外实现(含友元及其它必要的公共函数)  --- */ 
/* 默认构造函数 */
Date::Date()
{
	year = 1900;
	month = 1;
	day = 1;
}

/* 三参构造函数，需要检测范围 */
Date::Date(const int y, const int m, const int d)
{
	int good = 1;
	good &= check_year_legal(y);
	good &= check_month_legal(m);
	if (!good)  // 需要在检测day之前确保year和month范围正确
	{
		year = 1900;
		month = 1;
		day = 1;
		return;
	}
	else
	{
		year = y;
		month = m;
		good &= check_day_legal(year, month, d);
	}
	if (!good)
	{
		year = 1900;
		month = 1;
		day = 1;
	}
	else
		day = d;
}

/* set成员函数，设置对象的日期，为0的设置为默认值 */
void Date::set(const int y, const int m, const int d)
{
	int good = 1;
	good &= check_year_legal(y);
	good &= check_month_legal(m);
	if (!good)  // 需要在检测day之前确保year和month范围正确
	{
		year = 1900;
		month = 1;
		day = 1;
		return;
	}
	else
	{
		year = y;
		month = m;
		good &= check_day_legal(year, month, d);
	}
	if (!good)
	{
		year = 1900;
		month = 1;
		day = 1;
	}
	else
		day = d;
}

void Date::get(int& y, int& m, int& d)
{
	y = year;
	m = month;
	d = day;
}

void Date::show()
{
	cout << year << '-';
	cout << setfill('0') << setw(2) << month << '-';
	cout << setfill('0') << setw(2) << day;
	cout << endl;
}

Date::Date(int totalday)
{
	while (totalday < 0)
		totalday += MAXDATENUM;
	totalday %= MAXDATENUM;
	totalday++; // 需要自增1从而满足新的要求
	set(1900, 1, 1);
	int month_day[13] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };
	/* 求得年数 */
	while (totalday > 365) // while(totalday>365+is_leapyear(year))
	{
		if (is_leapyear(year))
		{
			if (totalday > 366)
				totalday -= 366;
			else
				break;
		}
		else
			totalday -= 365;
		++year;
	}
	/* 求得月数 */
	if (is_leapyear(year))
		++month_day[2];
	while (totalday > month_day[month])
	{
		totalday -= month_day[month];
		++month;
	}
	/* 求得天数 */
	day = totalday;
}

/* 重载+/- */
Date operator + (const Date& date, const int a)
{
	int totalday = (int)date + a; // 先调用类型转换函数将data转化为int
	totalday %= MAXDATENUM;
	return Date(totalday);
}
Date operator + (const int a, const Date& date)
{
	int totalday = (int)date + a; // 先调用类型转换函数将data转化为int
	totalday %= MAXDATENUM;
	return Date(totalday);
}
Date operator - (const Date& date, const int a)
{
	int totalday = (int)date - a;
	while (totalday < 0)
		totalday += MAXDATENUM;
	totalday %= MAXDATENUM;
	return Date(totalday);
}
int  operator - (const Date& date1, const Date& date2)
{
	return (int)date1 - (int)date2;
}

/* 重载>>/<< */
ostream& operator << (ostream& out, const Date& date)
{
	out << date.year << '-';
	out << setfill('0') << setw(2) << date.month << '-';
	out << setfill('0') << setw(2) << date.day;
	return out;
}
istream& operator >> (istream& in, Date& date)
{
	int y, m, d;
	in >> y >> m >> d;
	date.set(y, m, d);
	return in;
}

/* 重载前后缀++/-- */
Date& Date::operator ++()
{
	int totalday = (int)*this;
	totalday++;
	totalday %= MAXDATENUM;
	*this = Date(totalday);
	return *this;
}
Date Date::operator ++(int)
{
	Date temp(this->year, this->month, this->day);
	int totalday = (int)*this;
	totalday++;
	totalday %= MAXDATENUM;
	*this = Date(totalday);
	return temp;
}
Date& Date::operator --()
{
	int totalday = (int)*this;
	totalday--;
	while (totalday < 0)
		totalday += MAXDATENUM;
	totalday %= MAXDATENUM;
	*this = Date(totalday);
	return *this;
}
Date Date::operator --(int)
{
	Date temp(this->year, this->month, this->day);
	int totalday = (int)*this;
	totalday--;
	while (totalday < 0)
		totalday += MAXDATENUM;
	totalday %= MAXDATENUM;
	*this = Date(totalday);
	return temp;
}

/* 重载比较运算符 */
bool Date::operator <(const Date& date)
{
	return (int)(*this) < (int)date;
}
bool Date::operator >(const Date& date)
{
	return (int)(*this) > (int)date;
}
bool Date::operator == (const Date& date)
{
	return (int)(*this) == (int)date;
}
bool operator !=(const Date& date1, const Date& date2)
{
	return (int)date1 != (int)date2;
}
bool operator >=(const Date& date1, const Date& date2)
{
	return (int)date1 >= (int)date2;
}
bool operator <=(const Date& date1, const Date& date2)
{
	return (int)date1 <= (int)date2;
}

/* 类型转换函数 */
Date::operator int() const
{
	int totalday = 0;
	int month_day[13] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };
	for (int i = 1900; i < year; i++)
	{
		if (is_leapyear(i))
			totalday += 366;
		else
			totalday += 365;
	}
	if (is_leapyear(year))
		++month_day[2];
	for (int i = 1; i < month; i++)
	{
		totalday += month_day[i];
	}
	totalday += day;
	totalday--; // 满足本题要求
	return totalday;
}

/* 如果有需要的其它全局函数的实现，可以写于此处 */
int check_year_legal(const int year)
{
	if (year < 1900 || year > 2099)
		return 0;
	else
		return 1;
}
int check_month_legal(const int month)
{
	if (month < 1 || month > 12)
		return 0;
	else
		return 1;
}
/* 外部保证year和month的范围正确 */
int check_day_legal(const int year, const int month, const int day)
{
	int month_day[13] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };
	if (is_leapyear(year))
		++month_day[2];
	if (day<1 || day>month_day[month])
		return 0;  // 非法，返回0
	else
		return 1;
}
/* 判断是否是闰年 */
bool is_leapyear(const int year)
{
	if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
		return true; // 是闰年
	else
		return false; // 不是闰年
}
