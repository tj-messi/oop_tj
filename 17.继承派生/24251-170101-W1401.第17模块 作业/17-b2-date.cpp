/* 2351114 �쿡�� ������ */
#include <iostream>
#include <iomanip>
#include "17-b2-date.h"
using namespace std;

/* --- ����Date��ĳ�Ա����������ʵ��(����Ԫ��������Ҫ�Ĺ�������)  --- */ 

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/

// �ж��Ƿ�������
bool Date::isleapyear(int y) {
    return (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0);
}

// ��ȡĳ��ĳ�µ�����
int Date::getDinM(int y, int m) {
    static int daysInMonth[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    if (m == 2 && isleapyear(y)) {
        return 29; // �������
    }
    return daysInMonth[m - 1];
}

// �ж������Ƿ�Ϸ�
bool Date::isrightDate(int y, int m, int d) {
    return y >= 1900 && y <= 2099 && m >= 1 && m <= 12 && d >= 1 && d <= getDinM(y, m);
}

// Ĭ�Ϲ��캯������ʼ��Ϊ 1900-01-01
Date::Date() : year(1900), month(1), day(1) {}

// ʹ��ָ�������ճ�ʼ��
Date::Date(int y, int m, int d) {
    if (isrightDate(y, m, d)) {
        year = y;
        month = m;
        day = d;
    }
    else {
        year = 1900;
        month = 1;
        day = 1;
    }
}

// ʹ��������ʼ������ 1900-01-01 ���㣩
Date::Date(int days) {
    const int TOTAL_DAYS = 73049; // ������ (1900-01-01 �� 2099-12-31)
    days = (days % TOTAL_DAYS + TOTAL_DAYS) % TOTAL_DAYS; // ���ƴ���
    year = 1900;
    month = 1;
    day = 1;

    while (days >= (isleapyear(year) ? 366 : 365)) {
        days -= (isleapyear(year) ? 366 : 365);
        year++;
    }

    while (days >= getDinM(year, month)) {
        days -= getDinM(year, month);
        month++;
    }

    day += days;

    // ��������
    while (day > getDinM(year, month)) {
        day -= getDinM(year, month);
        month++;
        if (month > 12) {
            month = 1;
            year++;
        }
    }
}

// �������ڣ��ꡢ�¡��գ�
void Date::set(int y, int m, int d) {
    if (isrightDate(y, m, d)) {
        year = y;
        month = m;
        day = d;
    }
    else {
        year = 1900;
        month = 1;
        day = 1;
    }
}

// �������ڣ��ꡢ�£�
void Date::set(int y, int m) {
    set(y, m, 1);
}

// �������ڣ����꣩
void Date::set(int y) {
    set(y, 1, 1);
}

// ��ȡ����
void Date::get(int& y, int& m, int& d) {
    y = year;
    m = month;
    d = day;
}

// ��ʾ����
void Date::show() {
    cout << setfill('0') << setw(4) << year << "-"
        << setw(2) << month << "-"
        << setw(2) << day;

    //cout << endl;
}

// ����ת����������ת��Ϊ����
Date::operator int() {
    int totalDays = 0;
    for (int y = 1900; y < year; y++) {
        totalDays += (isleapyear(y) ? 366 : 365);
    }
    for (int m = 1; m < month; m++) {
        totalDays += getDinM(year, m);
    }
    totalDays += day - 1;
    return totalDays;
}

// ��������أ�Date + int
Date operator+(const Date& d1,const int d2) {
    Date d = d1;
    return Date(d.operator int() + d2);
}

// ��������أ�int + Date
Date operator+(const int d1,const Date& d2) {
    return d2 + d1;
}

// ��������أ�Date - int
Date operator-(const Date& d1,const int d2) {
    Date d = d1;
    return Date(d.operator int() - d2);
}

// ��������أ�Date - Date���������������
int operator-(const Date& d1, const Date& d2) {
    Date d11 = d1, d22 = d2;
    return d11.operator int() - d22.operator int();
}

// ǰ�� ++
Date& Date::operator++() {
    *this = *this + 1;
    return *this;
}

// ���� ++
Date Date::operator++(int) {
    Date temp = *this;
    *this = *this + 1;
    return temp;
}

// ǰ�� --
Date& Date::operator--() {
    *this = *this - 1;
    return *this;
}

// ���� --
Date Date::operator--(int) {
    Date temp = *this;
    *this = *this - 1;
    return temp;
}

// �Ƚ������
bool operator==(const Date& d1, const Date& d2) {
    return d1.year == d2.year && d1.month == d2.month && d1.day == d2.day;
}

bool operator!=(const Date& d1, const Date& d2) {
    return !(d1 == d2);
}

bool operator<(Date& d1, Date& d2) {
    return d1.operator int() < d2.operator int();
}

bool operator<=(Date& d1, Date& d2) {
    return (d1 < d2) || (d1 == d2);
}

bool operator>(Date& d1, Date& d2) {
    return !(d1 <= d2);
}

bool operator>=(Date& d1, Date& d2) {
    return !(d1 < d2);
}

// ����������
ostream& operator<<(ostream& out, const Date& d) {
    out << setfill('0') << setw(4) << d.year << "-"
        << setw(2) << d.month << "-"
        << setw(2) << d.day;
    return out;
}

// �����������
istream& operator>>(istream& in, Date& d) {
    int y, m, dd;
    in >> y >>  m  >> dd;
    if (d.isrightDate(y, m, dd)) {
        d.set(y, m, dd);
    }
    else {
        d.set(1900, 1, 1);
    }
    return in;
}


