/* 2150792 �ƿ� ţ»�� */
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "16-b5.h"
using namespace std;
/*  
1.strlen/strcpy������Դ������ΪNULL
2.���ݶ����len==0�ж��Ƿ�Ϊ�մ�����Ҫ����content
*/

/* ���� TString ������г�Ա����������ʵ�� */
/* 1.���캯������������ */
TString::TString()
{
	len = 0;
	if (new_char_array(content, len) == false)
		exit(-1);
	content[0] = '\0'; // �� NULL ��Ϊ���ַ���
}
TString::TString(const char* s)
{
	len = (s == NULL) ? 0 : strlen(s);
	if (new_char_array(content, len) == false)
		exit(-1);
	if (s == NULL)
		content[0] = '\0'; // �� NULL ��Ϊ���ַ���
	else
		strcpy(content, s);
}
TString::TString(const TString& other)
{
	len = other.len;
	if (new_char_array(content, len) == false)
		exit(-1);
	strcpy(content, other.content);
}
TString::~TString()
{
	len = 0;
	delete[]content;
}

/* 2.������������� */
ostream& operator << (ostream & out, const TString & s)
{
	if (s.len == 0)
		out << "<NULL>";
	else
		out << s.content;
	return out;
}

/* 3.������������ */
istream& operator >> (istream& in, TString& s)
{
	char temp[TString::MAX_BUFFER] = { '\0' };
	in >> temp;
	s.len = strlen(temp);
	if (s.content != NULL)
		delete[]s.content;
	if (new_char_array(s.content, s.len) == false)
		exit(-1);
	strcpy(s.content, temp);
	return in;
}

/* 4.ȡ�ַ��� */
char* TString::c_str() const
{
	return content;
}

/* 5.��ֵ�����(=)���� */
TString& TString::operator = (const TString& other)
{
	if (this != &other)
	{
		delete[]content;
		len = other.len;
		if (new_char_array(content, len) == false)
			exit(-1);
		strcpy(content, other.content);
	}
	return *this;
}
TString& TString::operator = (const char* s)
{
	delete[]content;
	len = (s == NULL) ? 0 : strlen(s);
	if (new_char_array(content, len) == false)
		exit(-1);
	if (s == NULL)
		content[0] = '\0'; // �� NULL ��Ϊ���ַ���
	else
		strcpy(content, s);
	return *this;
}

/* 6.���������(+)���� */
const TString operator + (const TString& s1, const TString& s2)
{
	TString temp;
	temp.len = s1.len + s2.len;
	if (new_char_array(temp.content, temp.len) == false)
		exit(-1);
	memcpy(temp.content, s1.content, s1.len * sizeof(char));
	memcpy(temp.content + s1.len, s2.content, s2.len * sizeof(char)); // memcpy���Ը���ȫ��ʵ���ڴ��ƶ�
	temp.content[temp.len] = '\0';
	return temp;
}
const TString operator + (const TString& s1, const char* s2)
{
	TString temp;
	int s2len = 0;
	if (s2 != NULL)
		s2len = strlen(s2);
	temp.len = s1.len + s2len;
	if (new_char_array(temp.content, temp.len) == false)
		exit(-1);
	memcpy(temp.content, s1.content, s1.len * sizeof(char));
	memcpy(temp.content + s1.len, s2, s2len * sizeof(char)); // memcpy���Ը���ȫ��ʵ���ڴ��ƶ�
	temp.content[temp.len] = '\0';
	return temp;
}
const TString operator + (const char c, const TString& s)
{
	TString temp;
	temp.len = s.len + 1;
	if (new_char_array(temp.content, temp.len) == false)
		exit(-1);
	temp.content[0] = c;
	memcpy(temp.content + 1, s.content, s.len * sizeof(char));
	temp.content[temp.len] = '\0';
	return temp;
}
const TString operator + (const TString& s, const char c)
{
	TString temp;
	temp.len = s.len + 1;
	if (new_char_array(temp.content, temp.len) == false)
		exit(-1);
	memcpy(temp.content, s.content, s.len * sizeof(char));
	temp.content[temp.len - 1] = c;
	temp.content[temp.len] = '\0';
	return temp;
}

/* 7.�����������(+=)���� */
TString& TString::operator += (const TString& other)
{
	int oldlen = len;
	len = len + other.len;
	char* newstr;
	if (new_char_array(newstr, len) == false)
		exit(-1);
	memcpy(newstr, content, oldlen * sizeof(char));
	delete[]content;
	memcpy(newstr + oldlen, other.content, other.len * sizeof(char));
	content = newstr;
	content[len] = '\0';
	return *this;
}
TString& TString::operator += (const char* s)
{
	int oldlen = len, slen = 0;
	if (s != NULL)
		slen = strlen(s);
	len = len + slen;
	char* newstr;
	if (new_char_array(newstr, len) == false)
		exit(-1);
	memcpy(newstr, content, oldlen * sizeof(char));
	delete[]content;
	memcpy(newstr + oldlen, s, slen * sizeof(char));
	content = newstr;
	content[len] = '\0';
	return *this;
}
TString& TString::operator += (const char c)
{
	int oldlen = len;
	len = len + 1;
	char* newstr;
	if (new_char_array(newstr, len) == false)
		exit(-1);
	memcpy(newstr, content, oldlen * sizeof(char));
	delete[]content;
	content = newstr;
	content[len - 1] = c;
	content[len] = '\0';
	return *this;
}

/* 8.������������ĵȼ۲���append() */
void TString::append(const TString& other)
{
	*this += other;
}
void TString::append(const char c)
{
	*this += c;
}

/* 9.ɾ�������(-)���� */
TString operator - (const TString& s1, const TString& s2)
{
	int pos = 0;
	pos = KMPSearch(s1.content, s2.content);
	if (pos == -1)
		return s1;
	TString temp;
	temp.len = s1.len - s2.len;
	if (new_char_array(temp.content, temp.len) == false)
		exit(-1);
	for (int i = 0; i < pos; i++)
		temp.content[i] = s1.content[i];
	for (int i = pos; s1.content[i + s2.len] != '\0'; i++)
		temp.content[i] = s1.content[i + s2.len];
	temp.content[temp.len] = '\0';
	return temp;
}
TString operator - (const TString& s1, const char c)
{
	char str2[2] = { c,'\0' };
	int pos = 0;
	pos = KMPSearch(s1.content, str2);
	if (pos == -1)
		return s1;
	TString temp;
	temp.len = s1.len - 1;
	if (new_char_array(temp.content, temp.len) == false)
		exit(-1);
	for (int i = 0; i < pos; i++)
		temp.content[i] = s1.content[i];
	for (int i = pos; s1.content[i + 1] != '\0'; i++)
		temp.content[i] = s1.content[i + 1];
	temp.content[temp.len] = '\0';
	return temp;
}

/* 10.��ɾ�������(-=)���� */
TString& TString::operator -=(const TString& s)
{
	int pos = 0;
	pos = KMPSearch(content, s.content);
	if (pos == -1)
		return *this;
	len = len - s.len;
	char* temp;
	if (new_char_array(temp, len) == false)
		exit(-1);
	for (int i = 0; i < pos; i++)
		temp[i] = content[i];
	for (int i = pos; content[i + s.len] != '\0'; i++)
		temp[i] = content[i + s.len];
	delete[]content; // �ͷ�ԭcontent�Ŀռ�
	content = temp;  // ��contentָ���µĿռ�
	content[len] = '\0';
	return *this;
}
TString& TString::operator -=(const char c)
{
	char str2[2] = { c,'\0' };
	int pos = 0;
	pos = KMPSearch(content, str2);
	if (pos == -1)
		return *this;
	len = len - 1;
	char* temp;
	if (new_char_array(temp, len) == false)
		exit(-1);
	for (int i = 0; i < pos; i++)
		temp[i] = content[i];
	for (int i = pos; content[i + 1] != '\0'; i++)
		temp[i] = content[i + 1];
	delete[]content; // �ͷ�ԭcontent�Ŀռ�
	content = temp;  // ��contentָ���µĿռ�
	content[len] = '\0';
	return *this;
}

/* 11.���Ʋ���(*)���� */
TString operator * (const TString& s, const int n)
{
	TString temp;
	for (int i = 0; i < n; i++)
		temp += s;
	return temp;
}

/* 12.�Ը��Ʋ���(*=)���� */
TString& TString::operator *= (const int n)
{
	TString temp = *this;
	for (int i = 1; i < n; i++)
		*this += temp;
	return  *this;
}

/* 13.��ת����(!)���� */
TString TString::operator ! () // �Լ�������ת�����Է�����ʱ����
{
	TString temp = *this;
	for (int i = 0; i < len; i++)
		temp.content[i] = content[len - i - 1];
	temp.content[len] = '\0';
	return temp;
}

/* 14.�Ƚ���������� */
int operator < (const TString& s1, const TString& s2)
{
	if (s2.len == 0)                // s2��0����һ��������С��
		return 0;
	if (s1.len == 0)				// s1��0��s2����0 
		return 1; 
	return (strcmp(s1.content, s2.content) < 0) ? 1 : 0;
}
int operator > (const TString& s1, const TString& s2)
{
	if (s1.len == 0)                // s1��0���򲻿��ܴ���
		return 0;
	if (s2.len == 0)                // s1����0������£�s2��0����һ������
		return 1;
	return (strcmp(s1.content, s2.content) > 0) ? 1 : 0;
}
int operator <= (const TString& s1, const TString& s2)
{
	if (s1.len == 0)
		return 1;
	if (s2.len == 0)
		return 0;
	return (strcmp(s1.content, s2.content) <= 0) ? 1 : 0;
}
int operator >= (const TString& s1, const TString& s2)
{
	if (s2.len == 0)                // s2��0����һ�����ڵ���
		return 1;
	if (s1.len == 0)                // s1��0��s2����0����һ�������ܴ��ڵ���
		return 0;
	return (strcmp(s1.content, s2.content) >= 0) ? 1 : 0;
}
int operator == (const TString& s1, const TString& s2)
{
	if (s1.len == 0 && s2.len == 0)
		return 1;
	if (s1.len == 0 || s2.len == 0)
		return 0;
	return (!strcmp(s1.content, s2.content)) ? 1 : 0;
}
int operator != (const TString& s1, const TString& s2)
{
	if (s1.len == 0 && s2.len == 0)
		return 0;
	if (s1.len == 0 || s2.len == 0)
		return 1;
	return (strcmp(s1.content, s2.content)) ? 1 : 0;
}

/* 15.�󴮳��� */
int TString::length()
{
	return len;
}
int TStringLen(const TString& s)
{
	return s.len;
}

/* 16.����[]����� */
char& TString::operator [] (const int n)
{
	return content[n];
}

/* �������Ҫ������ȫ�ֺ�����ʵ�֣�����д�ڴ˴� */
int  KMPSearch(const char* str1, const char* str2)
{
	int len1 = strlen(str1), len2 = strlen(str2);
	int* lps = new (nothrow) int[len2];
	if (lps == NULL)
		exit(-1);
	for (int i = 0; i < len2; i++)
		lps[i] = 0;
	/* ����str2��lps���� */
	int i = 1, j = 0; // j��ʾ��ƥ���ǰ׺�ͺ�׺�ĳ���
	while (i < len2)
	{
		if (str2[i] == str2[j])
			lps[i++] = ++j;
		else
		{
			if (j != 0)
				j = lps[j - 1];
			else
				lps[i++] = 0;
		}
	}
	if (len1 < len2)
		return -1;
	i = 0, j = 0;
	while (i < len1) 
	{
		if (str1[i] == str2[j]) 
		{
			++i;
			++j;
		}
		if (j == len2) 
			return i - j; // �ҵ���ȫ��ͬ���Ӵ�����������ʼλ��
		else if (i < len1 && str1[i] != str2[j]) 
		{
			if (j != 0) 
				j = lps[j - 1];
			else 
				++i;
		}
	}
	delete[]lps;
	return -1;
}
bool new_char_array(char*& content, int len)
{
	content = new(nothrow) char[len + 1];
	if (content == NULL)
	{
		cout << "��̬����ռ�ʧ��" << endl;
		return false;
	}
	return true;
}
