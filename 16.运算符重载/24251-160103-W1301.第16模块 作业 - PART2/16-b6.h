/*2351114 �쿡�� ������*/
#pragma once

#include <string>
#include <stdexcept>
#include <iostream>
using namespace std;

enum class week { sun, mon, tue, wed, thu, fri, sat };

/* ���������Ӧ�ĺ������� */



// ���������
std::ostream& operator<<(std::ostream& os, const week& w);
std::istream& operator>>(std::istream& is, week& w);
week operator++(week& w);         // ǰ��++
week operator++(week& w, int);    // ����++
week operator--(week& w);         // ǰ��--
week operator--(week& w, int);    // ����--
week operator+(const week& w, int n);
week operator-(const week& w, int n);
week& operator+=(week& w, int n);
week& operator-=(week& w, int n);
