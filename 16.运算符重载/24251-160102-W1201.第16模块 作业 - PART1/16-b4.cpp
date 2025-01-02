/*2351114 �쿡�� ������*/
#include <iostream>
#include "16-b4.h"
using namespace std;

/* ���� Date ������г�Ա����������ʵ�� */


// Ĭ�Ϲ��캯��
Date::Date() : year(2000), month(1), day(1) {}

// ���ι��캯��
Date::Date(const int y, const int m, const int d) {
    set(y, m, d);
}

// ת�����캯��
Date::Date(int total_days) {
    if (total_days < 1) total_days = 1;
    if (total_days > 73049) total_days = 73049;

    year = 1900;
    month = 1;
    day = 1;

    int month_day[13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    while (total_days > 365) {
        if (is_leapyear(year)) {
            if (total_days > 366) total_days -= 366;
            else break;
        }
        else {
            total_days -= 365;
        }
        ++year;
    }

    if (is_leapyear(year)) ++month_day[2];
    while (total_days > month_day[month]) {
        total_days -= month_day[month];
        ++month;
    }

    day = total_days;
}

// ��������
void Date::set(const int y, const int m, const int d) {
    if(y)
        year = check_year_legal(y);
    if(m)
        month = check_month_legal(m);
    if(d)
        day = check_day_legal(year, month, d);
    else
    {
        day = check_day_legal(year, month, day);
    }
}

// ��ȡ����
void Date::get(int& y, int& m, int& d) {
    y = year;
    m = month;
    d = day;
}

// ��ʾ����
void Date::show() {
    cout << year << "." << month << "." << day << endl;
}

// ����ת��Ϊ int������ת��Ϊ������
Date::operator int() const {
    int total_days = 0;
    int month_day[13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    for (int y = 1900; y < year; ++y) {
        total_days += is_leapyear(y) ? 366 : 365;
    }

    if (is_leapyear(year)) ++month_day[2];
    for (int m = 1; m < month; ++m) {
        total_days += month_day[m];
    }

    total_days += day;

    return total_days;
}

// ��������� +
Date operator+(const Date& date, const int days) {
    return Date(int(date) + days);
}

Date operator+(const int days, const Date& date) {
    return date + days;
}

// ��������� -
Date operator-(const Date& date, const int days) {
    return Date(int(date) - days);
}

int operator-(const Date& date1, const Date& date2) {
    return int(date1) - int(date2);
}

// ��������� ++
Date& Date::operator++() {
    *this = *this + 1;
    return *this;
}

Date Date::operator++(int) {
    Date temp = *this;
    *this = *this + 1;
    return temp;
}

// ��������� --
Date& Date::operator--() {
    *this = *this - 1;
    return *this;
}

Date Date::operator--(int) {
    Date temp = *this;
    *this = *this - 1;
    return temp;
}

// �Ƚ������
bool Date::operator<(const Date& date) {
    return int(*this) < int(date);
}

bool Date::operator>(const Date& date) {
    return int(*this) > int(date);
}

bool Date::operator==(const Date& date) {
    return int(*this) == int(date);
}

bool operator!=(const Date& date1, const Date& date2) {
    return !(date1 == date2);
}

bool operator<=(const Date& date1, const Date& date2) {
    return !(date1 > date2);
}

bool operator>=(const Date& date1, const Date& date2) {
    return !(date1 < date2);
}

// �������������
ostream& operator<<(ostream& out, const Date& date) {
    out << date.year << "." << date.month << "." << date.day;
    return out;
}

istream& operator>>(istream& in, Date& date) {
    int y, m, d;
    in >> y >> m >> d;
    date.set(y, m, d);
    return in;
}

/* �������Ҫ������ȫ�ֺ�����ʵ�֣�����д�ڴ˴� */
// ��������
bool is_leapyear(const int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

int check_year_legal(const int year) {
    return (year < 1900 || year > 2099) ? 2000 : year;
}

int check_month_legal(const int month) {
    return (month < 1 || month > 12) ? 1 : month;
}

int check_day_legal(const int year, const int month, const int day) {
    int month_day[13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    if (is_leapyear(year)) ++month_day[2];
    return (day < 1 || day > month_day[month]) ? 1 : day;
}