/*2351114 �쿡�� ������*/
#include<iostream>
using namespace std;
int main()
{
	//1
	const char *month[] = {"January",  "February",  "March",  "April",  "May",  "June",  "July",  "August",  "September",  "October",  "November",  "December"};
	cout<<"�������·�(1-12)"<<endl;
	int idx=0;
	cin>>idx;
	if(idx<1||idx>12||cin.good()==0)
		cout<<"Invalid"<<endl;
	else
		cout<<month[idx-1]<<endl;
	return 0;
}
