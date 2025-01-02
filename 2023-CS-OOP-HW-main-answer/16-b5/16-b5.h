/* 2150792 计科 牛禄阳 */
#define _CRT_SECURE_NO_WARNINGS
#pragma once

#include <iostream>
#include <cstring>
using namespace std;

/* TString 类的定义 */
class TString {
	static const int MAX_BUFFER = 2048;
protected:
	char* content;
	int len;
public:
	/* 1.构造和析构函数 */
	TString();                                                   // 默认构造函数
	~TString();                                                  // 析构函数
	TString(const char* s);                                 // 一参构造函数
	TString(const TString& other);                               // 复制构造函数
	/* 2.输入流重载 */
	friend ostream& operator << (ostream& out, const TString& s);     // 友元方式重载<<
	/* 3.输出流重载 */
	friend istream& operator >> (istream& in, TString& s);              // 友元方式重载>> 
	/* 4.取字符串 */
	char* c_str() const;
	/* 5.赋值运算符(=)重载，成员函数 */
	TString& operator = (const TString& other);
	TString& operator = (const char* s);                                // 可以用转化构造函数+等于号重载代替
	/* 6.连接运算符(+)重载，友元函数 */
	friend const TString operator + (const TString& s1, const TString& s2);
	friend const TString operator + (const TString& s1, const char* s2);
	// const char* 作为参数不需要定义，可以通过转化构造函数转化为TString后再调用TString+TString的重载
	friend const TString operator + (const char c, const TString& s);
	friend const TString operator + (const TString& s, const char c);
	/* 7.自连接运算符(+=)重载，成员函数 */
	TString& operator += (const TString& other);
	TString& operator += (const char* s);
	// const char* 作为参数不需要定义，可以通过转化构造函数转化为TString后再调用TString的成员重载
	TString& operator += (const char c);
	/* 8.自连接运算符的等价操作append()，成员函数 */
	void append(const TString& other);
	void append(const char c);
	/* 9.删除运算符(-)重载，友元函数 */
	friend TString operator - (const TString& s1, const TString& s2);
	friend TString operator - (const TString& s1, const char c);
	/* 10.自删除运算符(-=)重载，成员函数 */
	TString& operator -=(const TString& s);
	TString& operator -=(const char c);
	/* 11.复制运算符(*)重载，友元函数 */
	friend TString operator * (const TString& s, const int n);
	/* 12.自复制操作(*=)重载，成员函数 */
	TString& operator *= (const int n);
	/* 13.反转操作(!)重载，成员函数 */
	TString operator ! ();
	/* 14.比较运算符重载，友元函数 */
	friend int operator < (const TString& s1, const TString& s2);
	friend int operator > (const TString& s1, const TString& s2);
	friend int operator <= (const TString& s1, const TString& s2);
	friend int operator >= (const TString& s1, const TString& s2);
	friend int operator == (const TString& s1, const TString& s2);
	friend int operator != (const TString& s1, const TString& s2);
	/* 15.求串长度 */
	int length();
	friend int TStringLen(const TString& s);
	/* 16.重载[]运算符，成员函数 */
	char& operator [] (const int n);
};

/* 如果有其它全局函数需要声明，写于此处 */
int  KMPSearch(const char* str1, const char* str2);
bool new_char_array(char*& content, int len);
/* 如果有需要的宏定义、只读全局变量等，写于此处 */
