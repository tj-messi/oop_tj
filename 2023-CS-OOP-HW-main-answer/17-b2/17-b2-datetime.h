/* 2150792 �ƿ� ţ»�� */
#pragma once
#include "17-b2-date.h"
#include "17-b2-time.h"
using namespace std;
/* ���������ȫ�ֺ�����Ҫ������д�ڴ˴� */

/* DateTime��Ļ���Ҫ��
	1�����������κ����ݳ�Ա
	2�������ٶ����Ա���� 
*/
const long long DATATIMEMAXNUM = 6311433600;
const long long sec_aday = 86400;

class DateTime : public Date, public Time {
protected:
	/* �����������⣬�������ٶ����κ����ݳ�Ա */

public:
	/* ������Ҫ�ĳ�Ա��������Ԫ���������� */
	DateTime();
	DateTime(int ye, int mon, int d, int hou, int min, int sec);
	DateTime(long long totalsec);
	void set(long long totalsec);
	void set(const int y = 1900, const int m = 1, const int d = 1, const int hou = 0, const int min = 0, const int sec = 0);
	void get(int& y, int& m, int& d, int& hou, int& min, int& sec) const;
	Date getDate() const;
	Time getTime() const;
	void show() const;
	operator long long() const;
	/* ��������� */
	friend DateTime operator + (const DateTime& datetime, long long sec);
	friend DateTime operator + (long long sec, const DateTime& datetime);
#if defined(__linux) || defined(__linux__)
	friend DateTime operator + (long int sec, const DateTime& datetime);
	friend DateTime operator + (const DateTime& datetime, long int sec);
	friend DateTime operator - (const DateTime& a, long int sec);
#endif
	friend DateTime operator + (const DateTime& datetime, int sec);
	friend DateTime operator + (int sec, const DateTime& datetime);
	friend long long operator - (const DateTime& a, const DateTime& b);
	friend DateTime operator - (const DateTime& a, long long sec);
	friend DateTime operator - (const DateTime& a, int sec);
	DateTime& operator ++();
	DateTime operator ++(int);
	DateTime& operator --();
	DateTime operator --(int);
	friend bool operator < (const DateTime& a, const DateTime& b);
	friend bool operator > (const DateTime& a, const DateTime& b);
	friend bool operator <= (const DateTime& a, const DateTime& b);
	friend bool operator >= (const DateTime& a, const DateTime& b);
	friend bool operator != (const DateTime& a, const DateTime& b);
	friend bool operator == (const DateTime& a, const DateTime& b);
	friend ostream& operator << (ostream& out, const DateTime& a);
	friend istream& operator >> (istream& in, DateTime& a);	
};
