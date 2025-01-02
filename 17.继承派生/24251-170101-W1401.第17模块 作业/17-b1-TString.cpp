/*2351114 朱俊泽 大数据*/

/* 允许添加需要的头文件、宏定义等 */
#define _CRT_SECURE_NO_WARNINGS
#include "17-b1-TString.h"
#include <algorithm>
using namespace std;
// Private method to allocate and copy
void TString::allocateAndCopy(const char* str)
{
    len = str ? std::strlen(str) : 0;
    content = new char[len + 1];
    if (str) std::strcpy(content, str);
    else content[0] = '\0';
}

// Constructors and Destructor
TString::TString() : content(nullptr), len(0) {}
TString::TString(const char* str) 
{ 
    allocateAndCopy(str); 
}
TString::TString(const TString& other)
{
    allocateAndCopy(other.content);
}
TString::~TString() 
{
    delete[] content; 
}

// Assignment operators
TString& TString::operator=(const TString& other) 
{
    if (this != &other)
    {
        delete[] content;
        allocateAndCopy(other.content);
    }
    return *this;
}
TString& TString::operator=(const char* str) 
{
    delete[] content;
    allocateAndCopy(str);
    return *this;
}
TString& TString::operator=(char c) 
{
    delete[] content;
    len = 1;
    content = new char[2] {c, '\0'};
    return *this;
}

// Concatenation operators
TString TString::operator+(const TString& other) const
{
    int newLen = len + other.len;
    char* newContent = new char[newLen + 1];
    std::strcpy(newContent, content ? content : "");
    std::strcat(newContent, other.content ? other.content : "");
    TString result(newContent);
    delete[] newContent;
    return result;
}
TString TString::operator+(const char* str) const
{
    return *this + TString(str);
}
TString TString::operator+(char c) const 
{
    char temp[2] = { c, '\0' };
    return *this + temp;
}
TString operator+(const char* str, const TString& obj)
{
    return TString(str) + obj;
}
TString& TString::operator+=(const TString& s)
{
    if (s.content == NULL)
        return *this;
    if (content == NULL) {
        *this = s;
        return *this;
    }
    char* tmp = content;
    len += s.len;
    //content = new(nothrow)char[len + 1];
    content = new(nothrow)char[len + 1];
    content[0] = '\0';
    if (content == NULL) {
        cout << "OVERFLOW" << endl;
        return *this;
    }
    strcpy(content, tmp);
    strcat(content, s.content);
    delete[]tmp;
    return (*this);
}
TString& TString::operator+=(const char* str) 
{
    return *this += TString(str);
}
TString& TString::operator += (const char c)
{
    if (c == '\0')
        return *this;
    int oldlen = len;
    len = len + 1;
    char* newstr;
    newstr = new(nothrow) char[len + 1];
    memcpy(newstr, content, oldlen * sizeof(char));
    delete[]content;
    content = newstr;
    content[len - 1] = c;
    content[len] = '\0';
    return *this;
}

// Subtraction operators
TString TString::operator-(const TString& other) const 
{
    TString result(content);
    char* found = std::strstr(result.content, other.content);
    if (found) {
        std::memmove(found, found + other.len, std::strlen(found + other.len) + 1);
    }
    return result;
}
TString TString::operator-(const char* str) const 
{
    return *this - TString(str);
}
TString TString::operator-(char c) const 
{
    char temp[2] = { c, '\0' };
    return *this - temp;
}
TString& TString::operator-=(const TString& other) 
{
    *this = *this - other;
    return *this;
}
TString& TString::operator-=(const char* str)
{
    return *this -= TString(str);
}
TString& TString::operator-=(char c)
{
    return *this -= TString(&c);
}

// Multiplication operators
TString TString::operator*(int n) const 
{
    if (n <= 0 || len == 0 || content == nullptr) 
    {
        return TString(); // 返回空字符串
    }

    int newLen = len * n;
    char* newContent = new char[newLen + 1];
    newContent[0] = '\0'; // 初始化为空串

    for (int i = 0; i < n; ++i) 
    {
        strcat(newContent, content);
    }

    TString result(newContent);
    delete[] newContent;
    return result;
}

TString& TString::operator*=(int n) 
{
    if (n <= 0 || len == 0 || content == nullptr) 
    {
        delete[] content; // 清理旧内容
        content = nullptr;
        len = 0;
        return *this;
    }

    *this = *this * n;
    return *this;
}

// Logical NOT for reversing
TString TString::operator!() const 
{
    TString reversed(content);
    reverse(reversed.content, reversed.content + len);
    return reversed;
}

// Comparison operators
bool TString::operator==(const TString& other) const {
    return std::strcmp(content ? content : "", other.content ? other.content : "") == 0;
}
bool TString::operator!=(const TString& other) const { return !(*this == other); }
bool TString::operator<(const TString& other) const {
    return std::strcmp(content ? content : "", other.content ? other.content : "") < 0;
}
bool TString::operator<=(const TString& other) const { return !(*this > other); }
bool TString::operator>(const TString& other) const { return other < *this; }
bool TString::operator>=(const TString& other) const { return !(*this < other); }

// Access operators
char& TString::operator[](int index) { return content[index]; }
const char& TString::operator[](int index) const { return content[index]; }

// Utility methods
int TString::length() const { return len; }
const char* TString::c_str() const { return content ? content : ""; }
//TString& TString::append(const TString& other)
//{
//    *this += other;
//    return *this;
//}
//TString& TString::append(const char* str)
//{
//    *this += TString(str);
//    return *this;
//}
//TString& TString::append(char c)
//{
//    *this += TString(&c);
//    return *this;
//}
TString operator+(const char c, const TString& obj) {
    char temp[2] = { c, '\0' };
    return TString(temp) + obj;
}

// Stream operators
std::ostream& operator<<(std::ostream& os, const TString& obj) {
    os << (obj.len ? obj.content : "<EMPTY>");
    return os;
}
std::istream& operator>>(std::istream& is, TString& obj) {
    char temp[1024];
    is >> temp;
    obj = temp;
    return is;
}

// Global utility function
int TStringLen(const TString& obj) { return obj.length(); }
