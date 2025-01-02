/* 2150792 计科 牛禄阳 */
#include <iostream>
#include "16-b4.h"
using namespace std;

/* 给出 Date 类的所有成员函数的体外实现 */
/* 默认构造函数 */
Date::Date()
{
	year = 2000;
	month = 1;
	day = 1;
}

/* 三参构造函数，需要检测范围 */
Date::Date(const int y, const int m, const int d)
{
	year = check_year_legal(y);
	month = check_month_legal(m);
	day = check_day_legal(year, month, d);
}

/* set成员函数，设置对象的日期，为0的参数不变 */
void Date::set(const int y, const int m, const int d)
{
	if (y != 0)
		year = check_year_legal(y);
	if (m != 0)
		month = check_month_legal(m);
	if (d != 0)
		day = check_day_legal(year, month, d); // 需要用检测后的year和month
	else
		day = check_day_legal(year, month, day); // 避免month修改带来的day错误
}

void Date::get(int& y, int& m, int& d)
{
	y = year;
	m = month;
	d = day;
}

void Date::show()
{
	cout << year << "年" << month << "月" << day << "日" << endl;
}

Date::Date(int totalday)
{
	if (totalday <= 1)
		totalday = 1;
	if (totalday >= 73049)
		totalday = 73049;
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
	return Date(totalday);
}
Date operator+(const int a, const Date& date)
{
	int totalday = (int)date + a; // 先调用类型转换函数将data转化为int
	return Date(totalday);
}
Date operator-(const Date& date, const int a)
{
	int totalday = (int)date - a;
	return Date(totalday);
}
int operator-(const Date& date1, const Date& date2)
{
	return (int)date1 - (int)date2;
}

/* 重载>>/<< */
ostream& operator << (ostream& out, const Date& date)
{
	out << date.year << "年" << date.month << "月" << date.day << "日";
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
	*this = Date(totalday);
	return *this;
}
Date Date::operator ++(int)
{
	Date temp(this->year, this->month, this->day);
	int totalday = (int)*this;
	totalday++;
	*this = Date(totalday);
	return temp;
}
Date& Date::operator --()
{
	int totalday = (int)*this;
	totalday--;
	*this = Date(totalday);
	return *this;
}
Date Date::operator --(int)
{
	Date temp(this->year, this->month, this->day);
	int totalday = (int)*this;
	totalday--;
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
	return totalday;
}

/* 如果有需要的其它全局函数的实现，可以写于此处 */
int check_year_legal(const int year)
{
	if (year < 1900 || year > 2099)
		return 2000;
	else
		return year;
}
int check_month_legal(const int month)
{
	if (month < 1 || month > 12)
		return 1;
	else
		return month;
}
/* 外部保证year和month的范围正确 */
int check_day_legal(const int year, const int month, const int day)
{
	int month_day[13] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };
	if (is_leapyear(year))
		++month_day[2];
	if (day<1 || day>month_day[month])
		return 1;  // 非法，按缺省值1处理
	else
		return day;
}
/* 判断是否是闰年 */
bool is_leapyear(const int year) 
{
	if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) 
		return true; // 是闰年
	else 
		return false; // 不是闰年
}
