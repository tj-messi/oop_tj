/* 2150792 �ƿ� ţ»�� */
#pragma once

#include <iostream>
#include <cstring>
using namespace std;

/* ���������ȫ�ֺ�����Ҫ������д�ڴ˴� */
int  check_year_legal(const int year);
int  check_month_legal(const int month);
int  check_day_legal(const int year, const int month, const int day);
bool is_leapyear(const int year);
/* �������Ҫ�ĺ궨�塢ֻ��ȫ�ֱ����ȣ�д�ڴ˴� */
const int MAXDATENUM = 73049;

/* ��ȫDate��Ķ��壬���г�Ա����������ʵ�֣���Ҫ�ڴ˴�����ʵ�� */
class Date {
protected:
	int year;
	int month;
	int day;
	/* ������������ݳ�Ա */
public:
	/* ������Ҫ��������ĳ�Ա��������Ԫ������(������������ݳ�Ա) */
	Date();                                      // Ĭ�Ϲ��캯��
	Date(const int y, const int m, const int d); // ���ι��캯��
	void set(const int y = 2000, const int m = 1, const int d = 1); // set��Ա����
	void get(int& y, int& m, int& d);
	void show();
	Date(int totalday); // ת�����캯����int->Date
	friend Date operator+(const Date& date, const int a);
	friend Date operator+(const int a, const Date& date);
	friend Date operator-(const Date& date, const int a);
	friend int operator-(const Date& date1, const Date& date2);
	Date& operator ++();
	Date operator ++(int);
	Date& operator --();
	Date operator --(int);
	friend ostream& operator << (ostream& out, const Date& date);
	friend istream& operator >> (istream& in, Date& date);
	bool operator <(const Date& date);
	bool operator >(const Date& date);
	bool operator == (const Date& date);
	friend bool operator !=(const Date& date1, const Date& date2);
	friend bool operator >=(const Date& date1, const Date& date2);
	friend bool operator <=(const Date& date1, const Date& date2);
	/* �Զ����Ա���� */
	operator int() const;  // ����ת����������Date����ת��Ϊint���͵�����
};

