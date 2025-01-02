/* 2351114 朱俊泽 大数据 */

#include <iostream>
using namespace std;

/* 如果有其它全局函数需要声明，写于此处 */

/* Time类的声明 */ 
class Time {
protected:
	/* 除这三个以外，不允许再定义任何数据成员 */ 
	int hour;   // 小时
	int minute; // 分钟
	int second; // 秒

public:
	/* 允许需要的成员函数及友元函数的声明 */
    // 构造函数
    Time();                             // 默认构造函数，初始化为 00:00:00
    Time(int h, int m, int s);          // 使用小时、分钟、秒初始化
    Time(int seconds);                  // 使用总秒数初始化

    // 时间设置
    void set(int h, int m, int s);      // 设置小时、分钟、秒
    void set(int h, int m);             // 设置小时、分钟
    void set(int h);                    // 设置小时
    void set();                         // 清空时间，设置为 00:00:00

    // 时间获取
    void get(int& h, int& m, int& s);   // 获取小时、分钟、秒

    // 显示时间
    void show();                        // 以 hh:mm:ss 格式显示时间

    // 检查时间是否合法
    bool isrightTime(int h, int m, int s);

    // 类型转换
    operator int();                     // 将时间转换为总秒数（从 00:00:00 开始计算）

    // 前置和后置 ++ 和 --
    Time& operator++();                 // 前置 ++
    Time operator++(int);               // 后置 ++
    Time& operator--();                 // 前置 --
    Time operator--(int);               // 后置 --

	/* 允许加入友元声明（如果有必要） */
    // 运算符重载
    friend Time operator+(const Time& t1,const int seconds);
    friend Time operator+(const int seconds,const Time& t2);
    friend Time operator-(const Time& t1,const int seconds);
    friend int operator-(const Time& t1,const Time& t2);

    // 比较运算符
    friend bool operator==(const Time& t1, const Time& t2);
    friend bool operator!=(const Time& t1, const Time& t2);
    friend bool operator<(Time& t1, Time& t2);
    friend bool operator<=(Time& t1, Time& t2);
    friend bool operator>(Time& t1, Time& t2);
    friend bool operator>=(Time& t1, Time& t2);

    // 流运算符
    friend ostream& operator<<(ostream& out, const Time& t);
    friend istream& operator>>(istream& in, Time& t);
};
