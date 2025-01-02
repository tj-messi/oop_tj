/* 2351114 朱俊泽 大数据 */
#include <iostream>
#include <iomanip>
#include "17-b2-date.h"
using namespace std;

/* --- 给出Date类的成员函数的体外实现(含友元及其它必要的公共函数)  --- */ 

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/

// 判断是否是闰年
bool Date::isleapyear(int y) {
    return (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0);
}

// 获取某年某月的天数
int Date::getDinM(int y, int m) {
    static int daysInMonth[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    if (m == 2 && isleapyear(y)) {
        return 29; // 闰年二月
    }
    return daysInMonth[m - 1];
}

// 判断日期是否合法
bool Date::isrightDate(int y, int m, int d) {
    return y >= 1900 && y <= 2099 && m >= 1 && m <= 12 && d >= 1 && d <= getDinM(y, m);
}

// 默认构造函数，初始化为 1900-01-01
Date::Date() : year(1900), month(1), day(1) {}

// 使用指定年月日初始化
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

// 使用天数初始化（自 1900-01-01 起算）
Date::Date(int days) {
    const int TOTAL_DAYS = 73049; // 总天数 (1900-01-01 至 2099-12-31)
    days = (days % TOTAL_DAYS + TOTAL_DAYS) % TOTAL_DAYS; // 环绕处理
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

    // 修正日期
    while (day > getDinM(year, month)) {
        day -= getDinM(year, month);
        month++;
        if (month > 12) {
            month = 1;
            year++;
        }
    }
}

// 设置日期（年、月、日）
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

// 设置日期（年、月）
void Date::set(int y, int m) {
    set(y, m, 1);
}

// 设置日期（仅年）
void Date::set(int y) {
    set(y, 1, 1);
}

// 获取日期
void Date::get(int& y, int& m, int& d) {
    y = year;
    m = month;
    d = day;
}

// 显示日期
void Date::show() {
    cout << setfill('0') << setw(4) << year << "-"
        << setw(2) << month << "-"
        << setw(2) << day;

    //cout << endl;
}

// 类型转换：将日期转换为天数
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

// 运算符重载：Date + int
Date operator+(const Date& d1,const int d2) {
    Date d = d1;
    return Date(d.operator int() + d2);
}

// 运算符重载：int + Date
Date operator+(const int d1,const Date& d2) {
    return d2 + d1;
}

// 运算符重载：Date - int
Date operator-(const Date& d1,const int d2) {
    Date d = d1;
    return Date(d.operator int() - d2);
}

// 运算符重载：Date - Date（返回相差天数）
int operator-(const Date& d1, const Date& d2) {
    Date d11 = d1, d22 = d2;
    return d11.operator int() - d22.operator int();
}

// 前置 ++
Date& Date::operator++() {
    *this = *this + 1;
    return *this;
}

// 后置 ++
Date Date::operator++(int) {
    Date temp = *this;
    *this = *this + 1;
    return temp;
}

// 前置 --
Date& Date::operator--() {
    *this = *this - 1;
    return *this;
}

// 后置 --
Date Date::operator--(int) {
    Date temp = *this;
    *this = *this - 1;
    return temp;
}

// 比较运算符
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

// 输出流运算符
ostream& operator<<(ostream& out, const Date& d) {
    out << setfill('0') << setw(4) << d.year << "-"
        << setw(2) << d.month << "-"
        << setw(2) << d.day;
    return out;
}

// 输入流运算符
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


