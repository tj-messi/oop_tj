/*2351114 朱俊泽 大数据*/
#include <iostream>
#include <cmath>
using namespace std;
#define N 128

/* 从此处到标记替换行之间，给出各种类的定义及实现
	1、不允许定义全局变量（不含const和#define）
	2、不允许添加其它系统头文件
*/ 


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

// 定义基类 integral
class integral {
protected:
    double lower; // 积分下限
    double upper; // 积分上限
    int n;        // 划分区间的数量
    char name[N];//积分名字
public:
    integral() : lower(0), upper(0), n(0) {}
    virtual ~integral() {}
    virtual double value() = 0; // 纯虚函数：计算积分值

    // 重载输入运算符，用于输入上下限和划分数
    friend istream& operator>>(istream& in, integral& obj) {
        while (1)
        {
            cout << "请输入" << obj.name << "的下限、上限及区间划分数量" << endl;
            in >> obj.lower >> obj.upper >> obj.n;
            if (in.good() && obj.lower <= obj.upper && obj.n > 0)
                break;
            cout << "数据输入错误，请重新输入" << endl;
            in.clear();
            in.ignore(65536, '\n');
        }
        return in;
    }
};

// 计算 sin(x) 的定积分
class integral_sin : public integral {
public:
    integral_sin()
    {
        myStrcpy(name, "sinxdx");
    }
    double value() override {
        double step = (upper - lower) / n; // 每个小区间的宽度
        double sum = 0;
        for (int i = 1; i <= n; ++i) {
            double x = lower + i * step; // 取区间右端点
            sum += sin(x) * step;       // 矩形面积
        }
        cout << name << "[" << lower << "~" << upper << "/n=" << n << "] : " << sum << endl;
        return sum;
    }
};

// 计算 cos(x) 的定积分
class integral_cos : public integral {
public:
    integral_cos()
    {
        myStrcpy(name, "cosxdx");
    }
    double value() override {
        double step = (upper - lower) / n; // 每个小区间的宽度
        double sum = 0;
        for (int i = 1; i <= n; ++i) {
            double x = lower + i * step; // 取区间右端点
            sum += cos(x) * step;       // 矩形面积
        }
        cout << name << "[" << lower << "~" << upper << "/n=" << n << "] : " << sum << endl;
        return sum;
    }
};

// 计算 exp(x) 的定积分
class integral_exp : public integral {
public:
    integral_exp()
    {
        myStrcpy(name, "e^xdx");
    }
    double value() override {
        double step = (upper - lower) / n; // 每个小区间的宽度
        double sum = 0;
        for (int i = 1; i <= n; ++i) {
            double x = lower + i * step; // 取区间右端点
            sum += exp(x) * step;       // 矩形面积
        }
        cout << name << "[" << lower << "~" << upper << "/n=" << n << "] : " << sum << endl;
        return sum;
    }
};

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

