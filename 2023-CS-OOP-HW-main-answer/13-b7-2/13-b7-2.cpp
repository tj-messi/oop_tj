/* 2150792 ţ»�� �ƿ� */
#include <iostream>
/* --���ĳ����������Ҫ���˴�������������ĸ�ʽ����ͷ�ļ� --*/

using namespace std;

int main()
{
	char a[80];

#if (__GNUC__) && (WIN32)             //DevC++
	gets(a);
#elif (_MSC_VER)					  //VS2022
	gets_s(a);
#elif (__linux__)					  //Linux
	fgets(a, 80, stdin); //����Ҫ�������Ļس�
#endif

	cout << a << endl;
	return 0;
}
