/*2150792 计科 牛禄阳*/
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

	cout << "请输入sinxdx的下限、上限及区间划分数量" << endl;
	cin >> low >> high >> n;
	value = definite_integration(sin,n,low,high);
	cout << "sinxdx[" << low << "~" << high << "/n=" << n << "] : " << value << endl;

	cout << "请输入cosxdx的下限、上限及区间划分数量" << endl;
	cin >> low >> high >> n;
	value = definite_integration(cos,n, low, high);
	cout << "cosxdx[" << low << "~" << high << "/n=" << n << "] : " << value << endl;

	cout << "请输入e^xdx的下限、上限及区间划分数量" << endl;
	cin >> low >> high >> n;
	value = definite_integration(exp,n, low, high);
	cout << "e^xdx[" << low << "~" << high << "/n=" << n << "] : " << value << endl;

	return 0;
}