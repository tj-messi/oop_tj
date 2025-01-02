/* 2150792 计科 牛禄阳 */
#pragma once
#include "17-b2-date.h"
#include "17-b2-time.h"
using namespace std;
/* 如果有其它全局函数需要声明，写于此处 */

/* DateTime类的基本要求：
	1、不允许定义任何数据成员
	2、尽量少定义成员函数 
*/
const long long DATATIMEMAXNUM = 6311433600;
const long long sec_aday = 86400;

class DateTime : public Date, public Time {
protected:
	/* 除这三个以外，不允许再定义任何数据成员 */

public:
	/* 允许需要的成员函数及友元函数的声明 */
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
	/* 运算符重载 */
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
