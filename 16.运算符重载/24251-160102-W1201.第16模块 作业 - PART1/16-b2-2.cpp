/*2351114 朱俊泽 大数据*/
#include <iostream>
#include <string>
#include "16-b2-2.hpp"  //所有需要完成的内容写在本文件中 
using namespace std;

/* ----main函数测试时随意改动，不需要提交，作业检查时会被替换---- */
int main()
{
	if (1) {
		matrix<int, 2, 3> m1, m2, m3;

		/* 不考虑输入错误 */
		cout << "请输入矩阵m1的值(int型，共2行3列，按先行后列的顺序输入)" << endl;
		cin >> m1;
		cout << "请输入矩阵m2的值(int型，共2行3列，按先行后列的顺序输入)" << endl;
		cin >> m2;

		cout << "初始矩阵m1的值：" << endl;
		cout << m1 << endl;
		cout << "初始矩阵m2的值：" << endl;
		cout << m2 << endl;
		cout << "相加后矩阵m3的值：" << endl;
		cout << (m3 = m1 + m2) << endl;
		cout << endl;
	}

	if (1) {
		matrix<double, 3, 2> m1, m2, m3;

		/* 不考虑输入错误 */
		cout << "请输入矩阵m1的值(double型，共3行2列，按先行后列的顺序输入)" << endl;
		cin >> m1;
		cout << "请输入矩阵m2的值(double型，共3行2列，按先行后列的顺序输入)" << endl;
		cin >> m2;

		cout << "初始矩阵m1的值：" << endl;
		cout << m1 << endl;
		cout << "初始矩阵m2的值：" << endl;
		cout << m2 << endl;
		cout << "相加后矩阵m3的值：" << endl;
		cout << (m3 = m1 + m2) << endl;
		cout << endl;
	}

	if (1) {
		matrix<string, 3, 3> m1, m2, m3;

		/* 不考虑输入错误，字符串为大小写字母的组合序列即可，不考虑含空格/tab/单双引号等特殊字符
		   字符串+的规则等价于string的+，即ab+cd的结果是abcd */
		cout << "请输入矩阵m1的值(string型，共3行3列，按先行后列的顺序输入)" << endl;
		cin >> m1;
		cout << "请输入矩阵m2的值(string型，共3行3列，按先行后列的顺序输入)" << endl;
		cin >> m2;

		cout << "初始矩阵m1的值：" << endl;
		cout << m1 << endl;
		cout << "初始矩阵m2的值：" << endl;
		cout << m2 << endl;
		cout << "相加后矩阵m3的值：" << endl;
		cout << (m3 = m1 + m2) << endl;
		cout << endl;
	}

	return 0;
}

