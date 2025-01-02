/* 2351114 朱俊泽 大数据 */
#include "17-b2-date.h"
#include "17-b2-time.h"

/* 如果有其它全局函数需要声明，写于此处 */

/* DateTime类的基本要求：
	1、不允许定义任何数据成员
	2、尽量少定义成员函数 
*/

class DateTime:public Date, public Time {
protected:
	/* 不允许再定义任何数据成员 */ 

public:
	/* 不允许再定义任何数据成员，允许需要的成员函数及友元函数的声明 */
    // 默认构造函数
    DateTime();

    // 使用日期和时间初始化
    DateTime(int y, int m, int d, int h = 0, int min = 0, int s = 0);

    // 使用总秒数初始化
    DateTime(long long seconds);

    // 设置日期时间
    void set(const int y = 1900, const int m = 1, const int d = 1, const int h = 0, const int min = 0, const int s = 0);
    void set(long long secconds);
    //void set();

    // 获取日期时间
    void get(int& y, int& m, int& d, int& h, int& min, int& s);

    // 显示日期时间
    void show();

    // 类型转换
    operator long long()const;
    operator long long();

    // 前置和后置 ++ 和 --
    DateTime& operator++();
    DateTime operator++(int);
    DateTime& operator--();
    DateTime operator--(int);

	/* 允许加入友元声明（如果有必要） */

     // 运算符重载
    friend DateTime operator+(const DateTime& dt, long long seconds);
    friend DateTime operator+(long long seconds,const DateTime& dt );
    friend DateTime operator + (const DateTime& dt, int seconds);
    friend DateTime operator + (int seconds, const DateTime& dt);

#if defined(__linux) || defined(__linux__)
    friend DateTime operator + (long int seconds, const DateTime& dt);
    friend DateTime operator + (const DateTime& dt, long int seconds);
    friend DateTime operator - (const DateTime& dt, long int seconds);
#endif

    friend DateTime operator-(const DateTime& dt, long long seconds);
    friend DateTime operator - (const DateTime& dt, int seconds);
    friend long long operator-(const DateTime& dt1, const DateTime& dt2);

    // 比较运算符
    friend bool operator==(const DateTime& dt1, const DateTime& dt2);
    friend bool operator!=(const DateTime& dt1, const DateTime& dt2);
    friend bool operator<(const DateTime& dt1, const DateTime& dt2);
    friend bool operator<=(const DateTime& dt1, const DateTime& dt2);
    friend bool operator>(const DateTime& dt1, const DateTime& dt2);
    friend bool operator>=(const DateTime& dt1, const DateTime& dt2);

    // 流运算符
    friend ostream& operator<<(ostream& out, const DateTime& dt);
    friend istream& operator>>(istream& in, DateTime& dt);
};
