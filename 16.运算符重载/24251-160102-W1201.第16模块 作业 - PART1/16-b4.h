/*2351114 �쿡�� ������*/

#pragma once

#include <iostream>
using namespace std;

/* ���������ȫ�ֺ�����Ҫ������д�ڴ˴� */
int  check_year_legal(const int year);
int  check_month_legal(const int month);
int  check_day_legal(const int year, const int month, const int day);
bool is_leapyear(const int year);
/* �������Ҫ�ĺ궨�塢ֻ��ȫ�ֱ����ȣ�д�ڴ˴� */

/* ��ȫDate��Ķ��壬���г�Ա����������ʵ�֣���Ҫ�ڴ˴�����ʵ�� */
class Date {
private:
	int year;
	int month;
	int day;
	/* ������������ݳ�Ա */
public:
	/* ������Ҫ��������ĳ�Ա��������Ԫ������(������������ݳ�Ա) */
	Date();                                      
	Date(const int y, const int m, const int d); 
	Date(int totalday); 

	operator int() const;

	void set(const int y = 2000, const int m = 1, const int d = 1); // set��Ա����
	void get(int& y, int& m, int& d);
	void show();

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
};
