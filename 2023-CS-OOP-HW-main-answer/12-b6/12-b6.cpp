/*2150792 ¼Æ¿Æ Å£Â»Ñô*/
#include <iostream>
using namespace std;
using fun_return = void (*)(int);
//typedef void (*fun_return)(int);

void f_sub(int x)
{
	cout << "x = " << x << endl;
}

fun_return  fun(const char* p)
{
	cout << "str = " << p << endl;
	return f_sub;
}

int main()
{
	void(*(*f[3])(const char* p))(int x);

	f[0] = fun;
	f[0]("Hello")(2);
	f[0]("Tongji")(7);

	return 0;
}