/* 2150792 �ƿ� ţ»�� */
#include <iostream>
#include "16-b4.h"
using namespace std;

/* ���� Date ������г�Ա����������ʵ�� */
/* Ĭ�Ϲ��캯�� */
Date::Date()
{
	year = 2000;
	month = 1;
	day = 1;
}

/* ���ι��캯������Ҫ��ⷶΧ */
Date::Date(const int y, const int m, const int d)
{
	year = check_year_legal(y);
	month = check_month_legal(m);
	day = check_day_legal(year, month, d);
}

/* set��Ա���������ö�������ڣ�Ϊ0�Ĳ������� */
void Date::set(const int y, const int m, const int d)
{
	if (y != 0)
		year = check_year_legal(y);
	if (m != 0)
		month = check_month_legal(m);
	if (d != 0)
		day = check_day_legal(year, month, d); // ��Ҫ�ü����year��month
	else
		day = check_day_legal(year, month, day); // ����month�޸Ĵ�����day����
}

void Date::get(int& y, int& m, int& d)
{
	y = year;
	m = month;
	d = day;
}

void Date::show()
{
	cout << year << "��" << month << "��" << day << "��" << endl;
}

Date::Date(int totalday)
{
	if (totalday <= 1)
		totalday = 1;
	if (totalday >= 73049)
		totalday = 73049;
	set(1900, 1, 1);
	int month_day[13] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };
	/* ������� */
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
	/* ������� */
	if (is_leapyear(year))
		++month_day[2];
	while (totalday > month_day[month])
	{
		totalday -= month_day[month];
		++month;
	}
	/* ������� */
	day = totalday;
}

/* ����+/- */
Date operator + (const Date& date, const int a)
{
	int totalday = (int)date + a; // �ȵ�������ת��������dataת��Ϊint
	return Date(totalday);
}
Date operator+(const int a, const Date& date)
{
	int totalday = (int)date + a; // �ȵ�������ת��������dataת��Ϊint
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

/* ����>>/<< */
ostream& operator << (ostream& out, const Date& date)
{
	out << date.year << "��" << date.month << "��" << date.day << "��";
	return out;
}
istream& operator >> (istream& in, Date& date)
{
	int y, m, d;
	in >> y >> m >> d;
	date.set(y, m, d);
	return in;
}

/* ����ǰ��׺++/-- */
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

/* ���رȽ������ */
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

/* ����ת������ */
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

/* �������Ҫ������ȫ�ֺ�����ʵ�֣�����д�ڴ˴� */
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
/* �ⲿ��֤year��month�ķ�Χ��ȷ */
int check_day_legal(const int year, const int month, const int day)
{
	int month_day[13] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };
	if (is_leapyear(year))
		++month_day[2];
	if (day<1 || day>month_day[month])
		return 1;  // �Ƿ�����ȱʡֵ1����
	else
		return day;
}
/* �ж��Ƿ������� */
bool is_leapyear(const int year) 
{
	if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) 
		return true; // ������
	else 
		return false; // ��������
}
