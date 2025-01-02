/* 2150792 计科 牛禄阳 */
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cmath>
using namespace std;

/* 从此处到标记替换行之间，给出各种类的定义及实现
	1、不允许定义全局变量（不含const和#define）
	2、不允许添加其它系统头文件
*/
// 自定义的strcpy函数
void myStrcpy(char* dest, const char* src) 
{
	if (dest == NULL || src == NULL) 
		return; // 检查空指针
	// 复制src到dest，直到遇到null字符
	while (*src != '\0') 
	{
		*dest = *src;
		dest++;
		src++;
	}
	*dest = '\0'; // 在目标字符串的末尾添加null字符
}

const int MAXBUF = 128;
class integral {
protected:
	double low, high;
	int    num;
	char   name[MAXBUF];
public:
	virtual double value()
	{
		return 0;
	}
	friend istream& operator >>(istream& in, integral& inter);
};
istream& operator >>(istream& in, integral& inter)
{
	while (1)
	{
		cout << "请输入" << inter.name << "的下限、上限及区间划分数量" << endl;
		in >> inter.low >> inter.high >> inter.num;
		if (in.good() && inter.low <= inter.high && inter.num > 0)
			break;
		cout << "数据输入错误，请重新输入" << endl;
		in.clear();
		in.ignore(65536, '\n');
	}
	return in;
}

class integral_sin : public integral {
protected:

public:
	integral_sin();
	virtual double value();
};
integral_sin::integral_sin()
{
	myStrcpy(name, "sinxdx");
}
double integral_sin::value()
{
	double result = 0;
	double wid = (high - low) / num;
	for (int i = 1; i <= num; i++)
		result += sin(low + i * wid) * wid;
	cout << name << "[" << low << "~" << high << "/n=" << num << "] : " << result << endl;
	return result;
}

class integral_cos : public integral {
protected:

public:
	integral_cos();
	virtual double value();
};
integral_cos::integral_cos()
{
	myStrcpy(name, "cosxdx");
}
double integral_cos::value()
{
	double result = 0;
	double wid = (high - low) / num;
	for (int i = 1; i <= num; i++)
		result += cos(low + i * wid) * wid;
	cout << name << "[" << low << "~" << high << "/n=" << num << "] : " << result << endl;
	return result;
}

class integral_exp : public integral {
protected:

public:
	integral_exp();
	virtual double value();
};
integral_exp::integral_exp()
{
	myStrcpy(name, "e^xdx");
}
double integral_exp::value()
{
	double result = 0;
	double wid = (high - low) / num;
	for (int i = 1; i <= num; i++)
		result += exp(low + i * wid) * wid;
	cout << name << "[" << low << "~" << high << "/n=" << num << "] : " << result << endl;
	return result;
}
/* -- 替换标记行 -- 本行不要做任何改动 -- 本行不要删除 -- 在本行的下面不要加入任何自己的语句，作业提交后从本行开始会被替换 -- 替换标记行 -- */

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：fun_integral不准动，思考一下，integral应如何定义
***************************************************************************/
void fun_integral(integral& fRef)
{
	cin >> fRef;	//输入上下限、划分数
	cout << fRef.value() << endl;
	return;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：main函数不准动
***************************************************************************/
int main()
{
	integral_sin s1;
	integral_cos s2;
	integral_exp s3;

	fun_integral(s1); //计算sinxdx的值
	fun_integral(s2); //计算cosxdx的值
	fun_integral(s3); //计算expxdx的值

	return 0;
}

//注：矩形计算取右值，输出为正常double格式

