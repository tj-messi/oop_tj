/* 2351114 朱俊泽 大数据 */
#include <iostream>
#include <iomanip>
#include "17-b2-datetime.h"
using namespace std;

/* --- 给出DateTime类的成员函数的体外实现(含友元及其它必要的公共函数)  --- */ 

// 默认构造函数
DateTime::DateTime() : Date(), Time() {}

// 使用日期和时间初始化
DateTime::DateTime(int y, int m, int d, int h, int min, int s)
    : Date(y, m, d), Time(h, min, s) {
    if (!isrightDate(y, m, d) || !isrightTime(h, min, s)) {
        set(1900, 1, 1, 0, 0, 0);
    }
}

// 使用总秒数初始化
DateTime::DateTime(long long seconds) {
   
    //Date::set(static_cast<int>(seconds / 86400)); // 初始化日期部分
    ////Time::set( second =static_cast<int>(seconds % 86400)); // 初始化时间部分
    //Time(static_cast<int>(seconds % 86400));

    const long long MAX_SECONDS = 6311433599LL; // Total seconds from 1900-01-01 00:00:00 to 2099-12-31 23:59:59
    seconds = (seconds % (MAX_SECONDS + 1) + (MAX_SECONDS + 1)) % (MAX_SECONDS + 1);
    int y, m, d, hou, min, sec;
    Date nowday((int)(seconds / 86400));
    Time nowtime((int)(seconds % 86400));
    nowday.get(y, m, d);
    nowtime.get(hou, min, sec);
    (*this) = DateTime(y, m, d, hou, min, sec);
}

// 设置日期时间
void DateTime::set(int y, int m, int d, int h, int min, int s)
{
    if (isrightDate(y, m, d) && isrightTime(h, min, s)) {
        Date::set(y, m, d);
        Time::set(h, min, s);
    }
    else {
        Date::set(1900, 1, 1);
        Time::set(0, 0, 0);
    }
}

// 使用总秒数初始化
void DateTime::set(long long seconds) 
{
    const long long MAX_SECONDS = 6311433599LL; // Total seconds from 1900-01-01 00:00:00 to 2099-12-31 23:59:59
    seconds = (seconds % (MAX_SECONDS + 1) + (MAX_SECONDS + 1)) % (MAX_SECONDS + 1);
    Date::set(static_cast<int>(seconds / 86400)); // 初始化日期部分
    Time::set(static_cast<int>(seconds % 86400)); // 初始化时间部分
}

// 获取日期时间
void DateTime::get(int& y, int& m, int& d, int& h, int& min, int& s) {
    Date::get(y, m, d);
    Time::get(h, min, s);
}

// 显示日期时间
void DateTime::show() {
    Date::show();
    cout << " ";
    Time::show();
    cout << endl;
}

// 类型转换
DateTime::operator long long() const
{
    long long totalsec = 0;
    totalsec = ((long long)Date(year, month, day) * 86400) + (long long)((int)Time(hour, minute, second));
    return totalsec;
}

DateTime::operator long long() 
{
    long long totalsec = 0;
    totalsec = ((long long)Date(year, month, day) * 86400) + (long long)((int)Time(hour, minute, second));
    return totalsec;
}

// 运算符重载
#if defined(__linux) || defined(__linux__)
DateTime operator + (const DateTime& dt, long int seconds)
{
    const long long MAX_SECONDS = 6311433599LL; // Total seconds from 1900-01-01 00:00:00 to 2099-12-31 23:59:59
    seconds = (seconds % (MAX_SECONDS + 1) + (MAX_SECONDS + 1)) % (MAX_SECONDS + 1);
    long long totalsec = (long long)dt + seconds;
    while (totalsec < 0)
        totalsec += (MAX_SECONDS + 1);
    totalsec %= (MAX_SECONDS + 1);
    DateTime temp(totalsec);
    return temp;
}
DateTime operator + (long int seconds, const DateTime& dt)
{
    return dt + seconds;
}
DateTime operator - (const DateTime& dt, long int seconds)
{
    return dt + (-seconds);
}
#endif
// DateTime + seconds
DateTime operator + (const DateTime& dt, long long seconds)
{
    const long long MAX_SECONDS = 6311433599LL; // Total seconds from 1900-01-01 00:00:00 to 2099-12-31 23:59:59
    seconds = (seconds % (MAX_SECONDS + 1) + (MAX_SECONDS + 1)) % (MAX_SECONDS + 1);
    long long totalsec = (long long)dt + seconds;
    while (totalsec < 0)
        totalsec += (MAX_SECONDS + 1);
    totalsec %= (MAX_SECONDS + 1);
    DateTime temp(totalsec);
    return temp;
}

DateTime operator+(long long seconds, const DateTime& dt)
{
    return dt + seconds;
}

DateTime operator + (int seconds, const DateTime& dt)
{
    const long long MAX_SECONDS = 6311433599LL; // Total seconds from 1900-01-01 00:00:00 to 2099-12-31 23:59:59
    long long s = (long long)seconds;
    s = (long long)(s % (MAX_SECONDS + 1) + (MAX_SECONDS + 1)) % (MAX_SECONDS + 1);
    long long totalsec = (long long)dt + (long long)s;
    while (totalsec < 0)
        totalsec += (MAX_SECONDS + 1);
    totalsec %= (MAX_SECONDS + 1);
    DateTime temp(totalsec);
    return temp;
}

DateTime operator + (const DateTime& dt, int seconds)
{
    return seconds + dt;
}

// DateTime - seconds
DateTime operator-(const DateTime& dt, long long seconds) {
    return dt + (-seconds);
}

DateTime operator - (const DateTime& dt, int seconds)
{
    return dt + (-seconds);
}

// DateTime - DateTime
long long operator-(const DateTime& dt1, const DateTime& dt2) {
    return static_cast<long long>(dt1) - static_cast<long long>(dt2);
}

// 前后缀 ++/--
DateTime& DateTime::operator++() {
    *this = *this + 1;
    return *this;
}
DateTime DateTime::operator++(int) {
    DateTime temp = *this;
    *this = *this + 1;
    return temp;
}
DateTime& DateTime::operator--() {
    *this = *this - 1;
    return *this;
}
DateTime DateTime::operator--(int) {
    DateTime temp = *this;
    *this = *this - 1;
    return temp;
}

// 比较运算符
bool operator==(const  DateTime& dt1, const DateTime& dt2) {
    return static_cast<long long>(dt1) == static_cast<long long>(dt2);
}

bool operator!=(const DateTime& dt1, const DateTime& dt2) {
    return !(dt1 == dt2);
}

bool operator<(const DateTime& dt1,const  DateTime& dt2) {
    return static_cast<long long>(dt1) < static_cast<long long>(dt2);
}

bool operator<=(const DateTime& dt1, const DateTime& dt2) {
    return dt1 < dt2 || dt1 == dt2;
}

bool operator>(const DateTime& dt1, const DateTime& dt2) {
    return !(dt1 <= dt2);
}

bool operator>=(const DateTime& dt1, const DateTime& dt2) {
    return !(dt1 < dt2);
}

// 输出流运算符
ostream& operator<<(ostream& out, const DateTime& dt) {
    out << static_cast<Date>(dt) << " " << static_cast<Time>(dt);
    return out;
}

// 输入流运算符
istream& operator>>(istream& in, DateTime& dt) {
    int y, m, d, h, min, s;
    cin >> y >> m >> d >> h >> min >> s;
    dt.set(y, m, d, h, min, s);
    return in;
}
