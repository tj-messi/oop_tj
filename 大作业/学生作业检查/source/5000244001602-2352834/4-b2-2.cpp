/*2352834 ΢���� ������*/
#include<iostream>
using namespace std;
bool leapyear(int year) {
	return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
