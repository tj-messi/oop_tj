/*2150792 �ƿ� ţ»��*/
#include<iostream>
#include<iomanip>
#include<cmath>
#include<string>
#include<cstring>
using namespace std;

int main()
{
	int month_th = 0;
	const char* month[] = { "January","February","March","April","May" ,"June" ,"July" ,"August" ,"September" ,"October" ,"November" ,"December" };
	cout << "�������·�(1-12)" << endl;
	cin >> month_th;
	if (month_th < 1 || month_th > 12 || cin.good() == 0)
		cout << "Invalid" << endl;
	else
		cout << *(month + month_th - 1) << endl;
	return 0;
}