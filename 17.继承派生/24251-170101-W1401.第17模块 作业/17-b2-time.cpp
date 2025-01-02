/* 2351114 �쿡�� ������ */
#include <iostream>
#include <iomanip>
#include "17-b2-time.h"
using namespace std;

/* --- ����Time��ĳ�Ա����������ʵ��(����Ԫ��������Ҫ�Ĺ�������)  --- */ 
// Ĭ�Ϲ��캯������ʼ��Ϊ 00:00:00
Time::Time() : hour(0), minute(0), second(0) {}

// ʹ��Сʱ�����ӡ����ʼ��
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

// ʹ����������ʼ��
Time::Time(int seconds) {
    seconds = (seconds % 86400 + 86400) % 86400; // ���ƴ���һ��86400��
    hour = seconds / 3600;
    minute = (seconds % 3600) / 60;
    second = seconds % 60;
}

// ���ʱ���Ƿ�Ϸ�
bool Time::isrightTime(int h, int m, int s) {
    return h >= 0 && h < 24 && m >= 0 && m < 60 && s >= 0 && s < 60;
}

// ����ʱ�䣨Сʱ�����ӡ��룩
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

// ����ʱ�䣨Сʱ�����ӣ�
void Time::set(int h, int m) {
    set(h, m, 0);
}

// ����ʱ�䣨��Сʱ��
void Time::set(int h) {
    set(h, 0, 0);
}

// ���ʱ�䣬����Ϊ 00:00:00
void Time::set() {
    hour = 0;
    minute = 0;
    second = 0;
}

// ��ȡʱ��
void Time::get(int& h, int& m, int& s) {
    h = hour;
    m = minute;
    s = second;
}

// ��ʾʱ��
void Time::show() {
    cout << setfill('0') << setw(2) << hour << ":"
        << setw(2) << minute << ":"
        << setw(2) << second;
    //cout << endl;
}

// ����ת������ʱ��ת��Ϊ������
Time::operator int() {
    return hour * 3600 + minute * 60 + second;
}

// ��������أ�Time + int
Time operator+(const Time& t1, const int seconds) {
    Time t = t1;
    return Time(t .operator int() + seconds);
}

// ��������أ�int + Time
Time operator+(const int seconds, const Time& t2) {
    Time t = t2;
    return Time(t .operator int() + seconds);
}

// ��������أ�Time - int
Time operator-(const Time& t1, const int seconds) {
    Time t = t1;
    return Time(t.operator int() - seconds);
}

// ��������أ�Time - Time����������������
int operator-(const Time& t1, const Time& t2) {
    Time t11 = t1, t22 = t2;
    return t11.operator int() - t22.operator int();
}

// ǰ�� ++
Time& Time::operator++() {
    *this = *this + 1;
    return *this;
}

// ���� ++
Time Time::operator++(int) {
    Time temp = *this;
    *this = *this + 1;
    return temp;
}

// ǰ�� --
Time& Time::operator--() {
    *this = *this - 1;
    return *this;
}

// ���� --
Time Time::operator--(int) {
    Time temp = *this;
    *this = *this - 1;
    return temp;
}

// �Ƚ������
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

// ����������
ostream& operator<<(ostream& out, const Time& t) {
    out << setfill('0') << setw(2) << t.hour << ":"
        << setw(2) << t.minute << ":"
        << setw(2) << t.second;
    return out;
}

// �����������
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

