/* 2150792 计科 牛禄阳 */
#define _CRT_SECURE_NO_WARNINGS
#include "17-b1-TStringAdv.h"
#include "17-b1-TString.h"
#include <iostream>
using namespace std;

/* 1.构造函数 */
TStringAdv::TStringAdv() :TString()
{

}
TStringAdv::TStringAdv(const char* s) : TString(s)
{

}
TStringAdv::TStringAdv(const TString& s) : TString(s)
{
	// 调用基类构造函数
}
TStringAdv::TStringAdv(const TStringAdv& s) : TString(s)
{
	// 两个类的数据成员相同，直接使用基类的析构函数
}

/* 2.assign函数 */
TStringAdv& TStringAdv::assign(const TStringAdv& ts2)
{
	if (this != &ts2)
		TString::operator = (ts2);
	return *this;
}
TStringAdv& TStringAdv::assign(const char* s)
{
	TString::operator = (s);
	return *this;
}
TStringAdv& TStringAdv::assign(const char& c)
{
	if (c == '\0')
	{
		delete[]content;
		len = 0;
		if (new_char_array(content, len) == false)
			exit(-1);
		content[0] = '\0';
		return *this;
	}
	char s[2] = "";
	s[0] = c;
	s[1] = '\0';
	TStringAdv temp(s);
	*this = temp;
	return *this;
}

/* 3.append函数 */
TStringAdv& TStringAdv::append(const TStringAdv& ts2)
{
	int oldlen = len;
	len = len + ts2.len;
	char* newstr;
	if (new_char_array(newstr, len) == false)
		exit(-1);
	memcpy(newstr, content, oldlen * sizeof(char));
	delete[]content;
	memcpy(newstr + oldlen, ts2.content, ts2.len * sizeof(char));
	content = newstr;
	content[len] = '\0';
	return *this;
}
TStringAdv& TStringAdv::append(const char* s)
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
TStringAdv& TStringAdv::append(const char& c)
{
	if (c == '\0')
		return *this;
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

/* 4.insert函数 */
TStringAdv& TStringAdv::insert(const TStringAdv& ts2, int pos)
{
	int oldlen = len;
	if (pos < 1 || pos > oldlen + 1)
		return *this;
	len = len + ts2.len;
	char* newstr;
	if (new_char_array(newstr, len) == false)
		exit(-1);
	memcpy(newstr, content, (pos - 1) * sizeof(char));
	memcpy(newstr + (pos - 1), ts2.content, ts2.len * sizeof(char));
	memcpy(newstr + (pos - 1) + ts2.len, content + (pos - 1), (oldlen - pos + 1) * sizeof(char));
	newstr[len] = '\0';
	delete[]content;
	content = newstr;
	return *this;
}
TStringAdv& TStringAdv::insert(const char* s, int pos)
{
	if (s == NULL)
		return *this;
	int slen = strlen(s), oldlen = len;
	if (pos < 1 || pos > oldlen + 1)
		return *this;
	if (slen == 0)
		return *this;
	len = len + slen;
	char* newstr;
	if (new_char_array(newstr, len) == false)
		exit(-1);
	memcpy(newstr, content, (pos - 1) * sizeof(char));
	memcpy(newstr + (pos - 1), s, slen * sizeof(char));
	memcpy(newstr + (pos - 1) + slen, content + (pos - 1), (oldlen - pos + 1) * sizeof(char));
	newstr[len] = '\0';
	delete[]content;
	content = newstr;
	return *this;
}
TStringAdv& TStringAdv::insert(const char& c, int pos)
{
	int oldlen = len;
	if (pos < 1 || pos > oldlen + 1)
		return *this;
	if (c == '\0')
	{
		len = pos - 1;
		char* newstr;
		if (new_char_array(newstr, len) == false)
			exit(-1);
		memcpy(newstr, content, (pos - 1) * sizeof(char));
		newstr[pos - 1] = '\0';
		delete[] content;
		content = newstr;
		return *this;
	}
	len = len + 1;
	char* newstr;
	if (new_char_array(newstr, len) == false)
		exit(-1);
	memcpy(newstr, content, (pos - 1) * sizeof(char));
	newstr[pos - 1] = c;
	memcpy(newstr + (pos - 1) + 1, content + (pos - 1), (oldlen - pos + 1) * sizeof(char));
	newstr[len] = '\0';
	delete[] content;
	content = newstr;
	return *this;
}

/* 5.erase函数 */
TStringAdv& TStringAdv::erase(const TStringAdv& ts2)
{
	int pos = 0;
	pos = KMPSearch(content, ts2.content);
	if (pos == -1)
		return *this;
	len = len - ts2.len;
	char* temp;
	if (new_char_array(temp, len) == false)
		exit(-1);
	for (int i = 0; i < pos; i++)
		temp[i] = content[i];
	for (int i = pos; content[i + ts2.len] != '\0'; i++)
		temp[i] = content[i + ts2.len];
	delete[]content; // 释放原content的空间
	content = temp;  // 将content指向新的空间
	content[len] = '\0';
	return *this;
}
TStringAdv& TStringAdv::erase(const char* s)
{
	if (s == NULL)
		return *this;
	int slen = strlen(s), pos = 0;
	pos = KMPSearch(content, s);
	if (pos == -1)
		return *this;
	len = len - slen;
	char* temp;
	if (new_char_array(temp, len) == false)
		exit(-1);
	for (int i = 0; i < pos; i++)
		temp[i] = content[i];
	for (int i = pos; content[i + slen] != '\0'; i++)
		temp[i] = content[i + slen];
	delete[]content; // 释放原content的空间
	content = temp;  // 将content指向新的空间
	content[len] = '\0';
	return *this;
}
TStringAdv& TStringAdv::erase(const char& c)
{
	if (c == '\0')
		return *this;
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
	delete[]content; // 释放原content的空间
	content = temp;  // 将content指向新的空间
	content[len] = '\0';
	return *this;
}

/* 6.substr函数 */
TStringAdv TStringAdv::substr(const int pos, const int sublen) const
{
	int substrlen = sublen;
	if (pos < 1 || pos > len || sublen <= 0)
		return TStringAdv();

	if (substrlen == SUBSTRMAXNUM || pos + substrlen - 1 > len)
		substrlen = len - pos + 1;
	char* subcontent;
	if (new_char_array(subcontent, substrlen) == false)
		exit(-1);
	strncpy(subcontent, content + pos - 1, substrlen);
	subcontent[substrlen] = '\0';

	TStringAdv subString;
	subString.content = subcontent;
	subString.len = substrlen;
	return subString;
}

/* 7.at函数 */
char& TStringAdv::at(const int n) 
{
	return (*this)[n]; // 通过重载[]运算符实现
}
