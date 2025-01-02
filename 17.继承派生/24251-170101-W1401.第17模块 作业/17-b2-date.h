/* 2351114 朱俊泽 大数据 */
#include <iostream>
using namespace std;

/* 如果有其它全局函数需要声明，写于此处 */

/* Date类的声明 */ 
class Date {
protected:
	/* 除这三个以外，不允许再定义任何数据成员 */ 
	int year;
	int month;
	int day;
public:
	/* 允许需要的成员函数及友元函数的声明 */
     // 构造函数
    Date();
    Date(int y, int m, int d); // 使用指定日期初始化
    Date(int days);            // 使用天数（自1900-01-01起算）初始化

    // 日期设置
    void set(int y, int m, int d);
    void set(int y, int m);
    void set(int y);

    // 日期获取
    void get(int& y, int& m, int& d);

    // 日期显示
    void show();

    // 判断闰年
    bool isleapyear(int y);

    // 获取某年某月的天数
    int getDinM(int y, int m);

    // 检查日期是否合法
    bool isrightDate(int y, int m, int d);

    // 类型转换
    operator int(); // 将日期转换为天数（自1900-01-01起算）

    // 前置和后置 ++ 和 --
    Date& operator++();    // 前置 ++
    Date operator++(int);  // 后置 ++
    Date& operator--();    // 前置 --
    Date operator--(int);  // 后置 --

    // 流运算符
    friend ostream& operator<<(ostream& out, const Date& d);
    friend istream& operator>>(istream& in, Date& d);
	/* 允许加入友元声明（如果有必要） */
     // 比较运算符
    friend bool operator==(const Date& d1, const Date& d2);
    friend bool operator!=(const Date& d1, const Date& d2);
    friend bool operator<(Date& d1, Date& d2);
    friend bool operator<=(Date& d1, Date& d2);
    friend bool operator>(Date& d1, Date& d2);
    friend bool operator>=(Date& d1, Date& d2);

    // 运算符重载
    friend Date operator+(const Date& d1, const int d2);
    friend Date operator+(const int d1,const  Date& d2);
    friend Date operator-(const Date& d1, const int d2);
    friend int operator-(const Date& d1,const Date& d2);
};
