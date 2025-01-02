/*2352834 微电子 李重毅*/
#include<iostream>
using namespace std;
bool leapyear(int year) {
	return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
