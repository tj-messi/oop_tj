/*2351114 Öì¿¡Ôó ´óÊý¾Ý*/

#pragma once
#include <iostream>
#include <cstring>
#include <cstdlib>

class TString {
private:
    char* content;
    int len;

    void allocateAndCopy(const char* str);

public:
    // Constructors and Destructor
    TString();
    TString(const char* str);
    TString(const TString& other);
    ~TString();

    // Assignment operators
    TString& operator=(const TString& other);
    TString& operator=(const char* str);
    TString& operator=(char c);

    // Concatenation operators
    TString operator+(const TString& other) const;
    TString operator+(const char* str) const;
    TString operator+(char c) const;
    friend TString operator+(const char* str, const TString& obj);

    TString& operator+=(const TString& s);
    TString& operator+=(const char* str);
    TString& operator+=(char c);

    // Subtraction operators
    TString operator-(const TString& other) const;
    TString operator-(const char* str) const;
    TString operator-(char c) const;
    TString& operator-=(const TString& other);
    TString& operator-=(const char* str);
    TString& operator-=(char c);

    // Multiplication operators
    TString operator*(int n) const;
    TString& operator*=(int n);

    // Logical NOT for reversing
    TString operator!() const;

    // Comparison operators
    bool operator==(const TString& other) const;
    bool operator!=(const TString& other) const;
    bool operator<(const TString& other) const;
    bool operator<=(const TString& other) const;
    bool operator>(const TString& other) const;
    bool operator>=(const TString& other) const;

    // Access operators
    char& operator[](int index);
    const char& operator[](int index) const;

    // Utility methods
    int length() const;
    const char* c_str() const;
    TString& append(const TString& other);
    TString& append(const char* str);
    TString& append(char c);

    // Friends for stream I/O
    friend std::ostream& operator<<(std::ostream& os, const TString& obj);
    friend std::istream& operator>>(std::istream& is, TString& obj);

    friend TString operator+(const char c, const TString& obj);

};

// Global utility function
int TStringLen(const TString& obj);
