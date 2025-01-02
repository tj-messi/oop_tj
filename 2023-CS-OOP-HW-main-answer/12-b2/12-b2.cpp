/*2150792 �ƿ� ţ»��*/
#include<iostream>
#include<iomanip>
#include<cmath>
#include<string>
#include<cstring>
using namespace std;

double definite_integration(double (*p)(double),int n,double low,double high)
{
	double delta_x = (high - low) / n;
	double sigma_x = 0;
	for (int i=1;i<=n;i++)
		sigma_x += delta_x * p(low + delta_x * i);
	return sigma_x;
}

int main()
{
	int n;
	double low, high, value;

	cout << "������sinxdx�����ޡ����޼����仮������" << endl;
	cin >> low >> high >> n;
	value = definite_integration(sin,n,low,high);
	cout << "sinxdx[" << low << "~" << high << "/n=" << n << "] : " << value << endl;

	cout << "������cosxdx�����ޡ����޼����仮������" << endl;
	cin >> low >> high >> n;
	value = definite_integration(cos,n, low, high);
	cout << "cosxdx[" << low << "~" << high << "/n=" << n << "] : " << value << endl;

	cout << "������e^xdx�����ޡ����޼����仮������" << endl;
	cin >> low >> high >> n;
	value = definite_integration(exp,n, low, high);
	cout << "e^xdx[" << low << "~" << high << "/n=" << n << "] : " << value << endl;

	return 0;
}