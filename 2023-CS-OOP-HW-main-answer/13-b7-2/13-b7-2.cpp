/* 2150792 牛禄阳 计科 */
#include <iostream>
/* --如果某编译器有需要，此处允许按条件编译的格式加入头文件 --*/

using namespace std;

int main()
{
	char a[80];

#if (__GNUC__) && (WIN32)             //DevC++
	gets(a);
#elif (_MSC_VER)					  //VS2022
	gets_s(a);
#elif (__linux__)					  //Linux
	fgets(a, 80, stdin); //不需要处理最后的回车
#endif

	cout << a << endl;
	return 0;
}
