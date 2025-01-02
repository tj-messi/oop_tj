/* 2150792 计科 牛禄阳 */
#include <iostream>
#include <cstring>
using namespace std;

const int ROW = 2;
const int COL = 3;

#define OPERATOR_IS_MENBER_FUNCTION		1	//运算符的重载用成员函数方式实现（如果值为0，表示用友元方式实现）
/* !@#$%^&*() 替换分隔线，本行及之前行的内容均会被替换，除了第8行的修改0/1之外，不要加自己的内容 )(*&^%$#@! */

class matrix {
private:
	int value[ROW][COL];
	//除此之外不允许再添加数据成员
public:
	matrix(const int(*p)[COL]);	//构造函数-1参，用数组初始化矩阵
	matrix();					//构造函数-0参
#if OPERATOR_IS_MENBER_FUNCTION
	//给出+的成员函数实现方式的声明
	matrix operator+(const matrix& b);
#else
	//给出+的友元函数实现方式的声明
	friend matrix operator+(const matrix& a, const matrix& b);
#endif
	/* ----根据需要添加其它成员函数的定义和友元函数的声明，数量不限---- */
	friend ostream& operator<<(ostream& out, const matrix& mat);  // 重载<<
	friend istream& operator>>(istream& in, matrix& mat);         // 重载>>
};

/* ---- 给出成员函数的体外实现/友元函数的实现，其中+的实现有成员和友元两种形式，要求放在下面的预编译中 ---- */
/* 构造函数-0参，初始化矩阵 */
matrix::matrix()
{
	memset(value, 0, sizeof(value));	
}

/* 构造函数-1参，初始化矩阵 */
matrix::matrix(const int(*p)[COL])
{
	for (int i = 0; i < ROW; i++)
		for (int j = 0; j < COL; j++)
			value[i][j] = p[i][j];
}

ostream& operator<<(ostream& out, const matrix& mat)
{
	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COL; j++)
			out << mat.value[i][j] << " ";
		out << endl;
	}
	return out;
}

istream& operator>>(istream& in, matrix& mat)
{
	for (int i = 0; i < ROW; i++)
		for (int j = 0; j < COL; j++)
			in >> mat.value[i][j];
	return in;
}

#if OPERATOR_IS_MENBER_FUNCTION
//给出+的成员函数方式的体外实现
matrix matrix::operator+(const matrix& b)
{
	matrix res;
	for (int i = 0; i < ROW; i++)
		for (int j = 0; j < COL; j++)
			res.value[i][j] = value[i][j] + b.value[i][j];
	return res;
}

#else
//给出+的友元函数方式的体外实现
matrix operator+(const matrix& a, const matrix& b)
{
	matrix res;
	for (int i = 0; i < ROW; i++)
		for (int j = 0; j < COL; j++)
			res.value[i][j] = a.value[i][j] + b.value[i][j];
	return res;
}
#endif

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：main函数不准动
***************************************************************************/
int main()
{
	int a[ROW][COL] = { { 1,2,3 },{ 4,5,6 } };
	int b[ROW][COL] = { { 2,4,6 },{ 3,6,9 } };
	matrix m1(a), m2(b), m3; //m3的初值为全0

	/* 下面为定值测试 */
	cout << "初始矩阵m1的值" << endl;
	cout << m1 << endl;
	cout << "初始矩阵m2的值" << endl;
	cout << m2 << endl;

	m3 = m1 + m2;
	cout << "相加后矩阵m3的值" << endl;
	cout << m3 << endl;

	cout << "------------------" << endl;

	/* 下面为键盘输入测试 */
	cout << "请输入初始矩阵m1" << endl;
	cin >> m1;
	cout << "请输入初始矩阵m2" << endl;
	cin >> m2;

	cout << "初始矩阵m1的值" << endl;
	cout << m1 << endl;
	cout << "初始矩阵m2的值" << endl;
	cout << m2 << endl;
	cout << "相加后矩阵m3的值" << endl;
	cout << (m3 = m1 + m2) << endl;

	return 0;
}
