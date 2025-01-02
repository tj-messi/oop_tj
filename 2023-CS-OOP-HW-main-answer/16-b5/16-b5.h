/* 2150792 �ƿ� ţ»�� */
#define _CRT_SECURE_NO_WARNINGS
#pragma once

#include <iostream>
#include <cstring>
using namespace std;

/* TString ��Ķ��� */
class TString {
	static const int MAX_BUFFER = 2048;
protected:
	char* content;
	int len;
public:
	/* 1.������������� */
	TString();                                                   // Ĭ�Ϲ��캯��
	~TString();                                                  // ��������
	TString(const char* s);                                 // һ�ι��캯��
	TString(const TString& other);                               // ���ƹ��캯��
	/* 2.���������� */
	friend ostream& operator << (ostream& out, const TString& s);     // ��Ԫ��ʽ����<<
	/* 3.��������� */
	friend istream& operator >> (istream& in, TString& s);              // ��Ԫ��ʽ����>> 
	/* 4.ȡ�ַ��� */
	char* c_str() const;
	/* 5.��ֵ�����(=)���أ���Ա���� */
	TString& operator = (const TString& other);
	TString& operator = (const char* s);                                // ������ת�����캯��+���ں����ش���
	/* 6.���������(+)���أ���Ԫ���� */
	friend const TString operator + (const TString& s1, const TString& s2);
	friend const TString operator + (const TString& s1, const char* s2);
	// const char* ��Ϊ��������Ҫ���壬����ͨ��ת�����캯��ת��ΪTString���ٵ���TString+TString������
	friend const TString operator + (const char c, const TString& s);
	friend const TString operator + (const TString& s, const char c);
	/* 7.�����������(+=)���أ���Ա���� */
	TString& operator += (const TString& other);
	TString& operator += (const char* s);
	// const char* ��Ϊ��������Ҫ���壬����ͨ��ת�����캯��ת��ΪTString���ٵ���TString�ĳ�Ա����
	TString& operator += (const char c);
	/* 8.������������ĵȼ۲���append()����Ա���� */
	void append(const TString& other);
	void append(const char c);
	/* 9.ɾ�������(-)���أ���Ԫ���� */
	friend TString operator - (const TString& s1, const TString& s2);
	friend TString operator - (const TString& s1, const char c);
	/* 10.��ɾ�������(-=)���أ���Ա���� */
	TString& operator -=(const TString& s);
	TString& operator -=(const char c);
	/* 11.���������(*)���أ���Ԫ���� */
	friend TString operator * (const TString& s, const int n);
	/* 12.�Ը��Ʋ���(*=)���أ���Ա���� */
	TString& operator *= (const int n);
	/* 13.��ת����(!)���أ���Ա���� */
	TString operator ! ();
	/* 14.�Ƚ���������أ���Ԫ���� */
	friend int operator < (const TString& s1, const TString& s2);
	friend int operator > (const TString& s1, const TString& s2);
	friend int operator <= (const TString& s1, const TString& s2);
	friend int operator >= (const TString& s1, const TString& s2);
	friend int operator == (const TString& s1, const TString& s2);
	friend int operator != (const TString& s1, const TString& s2);
	/* 15.�󴮳��� */
	int length();
	friend int TStringLen(const TString& s);
	/* 16.����[]���������Ա���� */
	char& operator [] (const int n);
};

/* ���������ȫ�ֺ�����Ҫ������д�ڴ˴� */
int  KMPSearch(const char* str1, const char* str2);
bool new_char_array(char*& content, int len);
/* �������Ҫ�ĺ궨�塢ֻ��ȫ�ֱ����ȣ�д�ڴ˴� */
