/* 2351114 朱俊泽 大数据 */
#include <iostream>
#include <iomanip>
#include "17-b2-time.h"
using namespace std;

/* --- 给出Time类的成员函数的体外实现(含友元及其它必要的公共函数)  --- */ 
// 默认构造函数，初始化为 00:00:00
Time::Time() : hour(0), minute(0), second(0) {}

// 使用小时、分钟、秒初始化
Time::Time(int h, int m, int s) {
    if (isrightTime(h, m, s)) {
        hour = h;
        minute = m;
        second = s;
    }
    else {
        hour = 0;
        minute = 0;
        second = 0;
    }
}

// 使用总秒数初始化
Time::Time(int seconds) {
    seconds = (seconds % 86400 + 86400) % 86400; // 环绕处理，一天86400秒
    hour = seconds / 3600;
    minute = (seconds % 3600) / 60;
    second = seconds % 60;
}

// 检查时间是否合法
bool Time::isrightTime(int h, int m, int s) {
    return h >= 0 && h < 24 && m >= 0 && m < 60 && s >= 0 && s < 60;
}

// 设置时间（小时、分钟、秒）
void Time::set(int h, int m, int s) {
    if (isrightTime(h, m, s)) {
        hour = h;
        minute = m;
        second = s;
    }
    else {
        hour = 0;
        minute = 0;
        second = 0;
    }
}

// 设置时间（小时、分钟）
void Time::set(int h, int m) {
    set(h, m, 0);
}

// 设置时间（仅小时）
void Time::set(int h) {
    set(h, 0, 0);
}

// 清空时间，设置为 00:00:00
void Time::set() {
    hour = 0;
    minute = 0;
    second = 0;
}

// 获取时间
void Time::get(int& h, int& m, int& s) {
    h = hour;
    m = minute;
    s = second;
}

// 显示时间
void Time::show() {
    cout << setfill('0') << setw(2) << hour << ":"
        << setw(2) << minute << ":"
        << setw(2) << second;
    //cout << endl;
}

// 类型转换：将时间转换为总秒数
Time::operator int() {
    return hour * 3600 + minute * 60 + second;
}

// 运算符重载：Time + int
Time operator+(const Time& t1, const int seconds) {
    Time t = t1;
    return Time(t .operator int() + seconds);
}

// 运算符重载：int + Time
Time operator+(const int seconds, const Time& t2) {
    Time t = t2;
    return Time(t .operator int() + seconds);
}

// 运算符重载：Time - int
Time operator-(const Time& t1, const int seconds) {
    Time t = t1;
    return Time(t.operator int() - seconds);
}

// 运算符重载：Time - Time（返回相差的秒数）
int operator-(const Time& t1, const Time& t2) {
    Time t11 = t1, t22 = t2;
    return t11.operator int() - t22.operator int();
}

// 前置 ++
Time& Time::operator++() {
    *this = *this + 1;
    return *this;
}

// 后置 ++
Time Time::operator++(int) {
    Time temp = *this;
    *this = *this + 1;
    return temp;
}

// 前置 --
Time& Time::operator--() {
    *this = *this - 1;
    return *this;
}

// 后置 --
Time Time::operator--(int) {
    Time temp = *this;
    *this = *this - 1;
    return temp;
}

// 比较运算符
bool operator==(const Time& t1, const Time& t2) {
    return t1.hour == t2.hour && t1.minute == t2.minute && t1.second == t2.second;
}

bool operator!=(const Time& t1, const Time& t2) {
    return !(t1 == t2);
}

bool operator<(Time& t1, Time& t2) {
    return t1.operator int() < t2.operator int();
}

bool operator<=(Time& t1, Time& t2) {
    return (t1 < t2) || (t1 == t2);
}

bool operator>(Time& t1, Time& t2) {
    return !(t1 <= t2);
}

bool operator>=(Time& t1, Time& t2) {
    return !(t1 < t2);
}

// 输出流运算符
ostream& operator<<(ostream& out, const Time& t) {
    out << setfill('0') << setw(2) << t.hour << ":"
        << setw(2) << t.minute << ":"
        << setw(2) << t.second;
    return out;
}

// 输入流运算符
istream& operator>>(istream& in, Time& t) {
    int h, m, s;
    in >> h >> m  >> s;
    if ( t.isrightTime(h, m, s)) {
        t.set(h, m, s);
    }
    else {
        t.set(0, 0, 0);
    }
    return in;
}

