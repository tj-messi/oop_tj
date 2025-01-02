/* 2150792 计科 牛禄阳 */
#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include "17-b1-TString.h"
using namespace std;

const int SUBSTRMAXNUM = 2147483600;

/* TStringAdv 类的定义 */
class TStringAdv : public TString {
protected:

public:
	/* 1.构造函数 */
	TStringAdv();
	TStringAdv(const char* s);
	TStringAdv(const TString& s);
	TStringAdv(const TStringAdv& s);
	/* 2.assign函数 */
	TStringAdv& assign(const TStringAdv& ts2);
	TStringAdv& assign(const char* s);
	TStringAdv& assign(const char& c);
	/* 3.append函数 */
	TStringAdv& append(const TStringAdv& ts2);
	TStringAdv& append(const char* s);
	TStringAdv& append(const char& c);
	/* 4.insert函数 */
	TStringAdv& insert(const TStringAdv& ts2, int pos);
	TStringAdv& insert(const char* s, int pos);
	TStringAdv& insert(const char& c, int pos);
	/* 5.erase函数 */
	TStringAdv& erase(const TStringAdv& ts2);
	TStringAdv& erase(const char* s);
	TStringAdv& erase(const char& c);
	/* 6.substr函数 */
	TStringAdv substr(const int pos, const int sublen = SUBSTRMAXNUM) const;
	/* 7.at函数 */
	char& at(const int n);
};
