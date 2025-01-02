/*2351114 �쿡�� ������*/
#pragma once
#include <string>
#include <iostream>
using namespace std;

enum week { sun, mon, tue, wed, thu, fri, sat };

/* ���������Ӧ�ĺ������� */

// �������������������
ostream& operator<<(ostream& os, const week& w);
istream& operator>>(istream& is, week& w);

// ����ǰ�úͺ���++������
week& operator++(week& w);   // ǰ��
week operator++(week& w, int); // ����

// ����ǰ�úͺ���--������
week& operator--(week& w);   // ǰ��
week operator--(week& w, int); // ����

// ���ؼӷ�������������
week operator+(const week& w, int n);
week operator-(const week& w, int n);

// ���ؼӵȡ����Ȳ�����
week& operator+=(week& w, int n);
week& operator-=(week& w, int n);
