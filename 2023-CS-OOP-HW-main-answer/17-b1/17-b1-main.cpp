/* 2150792 计科 牛禄阳 */
/* 1850772 张哲源 2152202 戚峻榕 2152988 杨恺铭 2153731 胡语诺 */
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include "17-b1-TString.h"
#include "17-b1-TStringAdv.h"
using namespace std;
#if defined(__linux) || defined(__linux__)
#include <sys/time.h>
/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
void wait_for_enter()
{
	cout << endl << "按回车键继续";
	while (getchar() != '\n')
		;
	cout << endl << endl;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
long get_cur_msec(void)
{
	struct timespec ts;
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &ts);

	return (ts.tv_sec * 1000 + ts.tv_nsec / 1000000);
}

#else
#include <Windows.h>
#include <conio.h>
/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
void wait_for_enter()
{
	cout << endl << "按回车键继续";
	while (_getch() != '\r')
		;
	cout << endl << endl;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
long get_cur_msec(void)
{
	return GetTickCount(); //取当前系统时间，单位毫秒.
}

#endif

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/

int main()
{
	if (1) {
		const TStringAdv s1;                    // s1为NULL
		const TStringAdv s2("teststr2");        // s2为"teststr2"
		const TStringAdv s3 = "teststr3";       // s3为"teststr3"
		const TStringAdv s4 = NULL;             // s4为NULL
		const TStringAdv s5 = "";               // s5为NULL

		cout << "定义对象并初始化测试(NULL及字符串常量初始化)" << endl;

		cout << "s1应该是<NULL>，  实际输出：" << s1 << endl;
		cout << "s2应该是teststr2，实际输出：" << s2 << endl;
		cout << "s3应该是teststr3，实际输出：" << s3 << endl;
		cout << "s4应该是<NULL>，  实际输出：" << s4 << endl;
		cout << "s5应该是<NULL>，  实际输出：" << s5 << endl;

		wait_for_enter();
	}

	if (1) {
		const TStringAdv s0 = "teststr1";
		const char* str1 = "teststr2";
		const char  str2[] = "teststr3";
		const char* str3 = NULL;
		const char  str4[] = "";
		const TStringAdv s1 = s0, s2 = str1, s3 = str2, s4 = str3, s5 = str4;

		cout << "定义对象并初始化测试(TStringAdv对象及字符指针、字符数组)" << endl;

		cout << "s1应该是teststr1，实际输出：" << s1 << endl;
		cout << "s2应该是teststr2，实际输出：" << s2 << endl;
		cout << "s3应该是teststr3，实际输出：" << s3 << endl;
		cout << "s4应该是<NULL>，  实际输出：" << s4 << endl;
		cout << "s5应该是<NULL>，  实际输出：" << s5 << endl;

		wait_for_enter();
	}

	if (1) {
		TStringAdv s1;

		cout << "重载cin测试" << endl;

		cout << "请在键盘上输入Hello" << endl;
		cin >> s1;
		cout << "s1应该是Hello，实际输出：" << s1 << endl;

		cout << "请在键盘上输入Hello 123" << endl;
		cin >> s1;
		cout << "s1应该是Hello，实际输出：" << s1 << endl;

		wait_for_enter();
	}

	if (1) {
		TStringAdv s1("Hello"), s2;

		cout << "赋值操作测试" << endl;

		cout << "s1应该是Hello， 实际输出：" << s1 << endl;

		s2 = s1;
		cout << "s2应该是Hello， 实际输出：" << s2 << endl;

		s1 = "Hi";
		cout << "s1应该是Hi，    实际输出：" << s1 << endl;

		s2 = "";
		cout << "s2应该是<NULL>，实际输出：" << s2 << endl;

		s1 = NULL;
		cout << "s1应该是<NULL>，实际输出：" << s1 << endl;

		s1 = "Hello";
		cout << "s1应该是Hello， 实际输出：" << (s1 = s1) << endl;
		cout << "s1应该是Hello， 实际输出：" << (s1 = s1 = s1 = s1 = s1) << endl;
		cout << "s1应该是Hello， 实际输出：" << (((s1 = s1) = s1) = s1) << endl;

		wait_for_enter();
	}

	if (1) {
		TStringAdv s0, s1("tong"), s2("ji"), s3;

		cout << "连接(+)测试(两个TStringAdv类)" << endl;

		s3 = s1 + s2;
		cout << "s3应为tongji，实际输出：" << s3 << endl;

		s3 = s2 + s1;
		cout << "s3应为jitong，实际输出：" << s3 << endl;

		s3 = s1 + s0;
		cout << "s3应为tong，  实际输出：" << s3 << endl;

		s3 = s0 + s2;
		cout << "s3应为ji，    实际输出：" << s3 << endl;

		wait_for_enter();
	}

	if (1) {
		TStringAdv s1("tong"), s2, s3;

		cout << "连接(+)测试(TStringAdv类和字符串常量)" << endl;

		s3 = s1 + "ji";
		cout << "s3应为tongji，实际输出：" << s3 << endl;

		s3 = "ji" + s1;
		cout << "s3应为jitong，实际输出：" << s3 << endl;

		s3 = s1 + "";
		cout << "s3应为tong，  实际输出：" << s3 << endl;

		s3 = s1 + (char*)NULL;
		cout << "s3应为tong，  实际输出：" << s3 << endl;

		s3 = "" + s1;
		cout << "s3应为tong，  实际输出：" << s3 << endl;

		s3 = (char*)NULL + s1;
		cout << "s3应为tong，  实际输出：" << s3 << endl;

		s3 = s2 + (char*)NULL;
		cout << "s3应为<NULL>，实际输出：" << s3 << endl;

		s3 = (char*)NULL + s2;
		cout << "s3应为<NULL>，实际输出：" << s3 << endl;

		s3 = s2 + "";
		cout << "s3应为<NULL>，实际输出：" << s3 << endl;

		s3 = "" + s2;
		cout << "s3应为<NULL>，实际输出：" << s3 << endl;

		wait_for_enter();
	}

	if (1) {
		TStringAdv s1("tong"), s3;
		const char* str1 = "ji", * str2 = "", * str3 = NULL;

		cout << "连接(+)测试(TStringAdv类和字符指针)" << endl;

		s3 = s1 + str1;
		cout << "s3应为tongji，实际输出：" << s3 << endl;

		s3 = str1 + s1;
		cout << "s3应为jitong，实际输出：" << s3 << endl;

		s3 = s1 + str2;
		cout << "s3应为tong，  实际输出：" << s3 << endl;

		s3 = str2 + s1;
		cout << "s3应为tong，  实际输出：" << s3 << endl;

		s3 = s1 + str3;
		cout << "s3应为tong，  实际输出：" << s3 << endl;

		s3 = str3 + s1;
		cout << "s3应为tong，  实际输出：" << s3 << endl;

		wait_for_enter();
	}

	if (1) {
		TStringAdv s1("tong"), s3;
		char str1[] = "ji", str2[] = "";

		cout << "连接(+)测试(TStringAdv类和字符数组)" << endl;

		s3 = s1 + str1;
		cout << "s3应为tongji，实际输出：" << s3 << endl;

		s3 = str1 + s1;
		cout << "s3应为jitong，实际输出：" << s3 << endl;

		s3 = s1 + str2;
		cout << "s3应为tong，  实际输出：" << s3 << endl;

		s3 = str2 + s1;
		cout << "s3应为tong，  实际输出：" << s3 << endl;

		wait_for_enter();
	}

	if (1) {
		TStringAdv s1("Hello"), s3;
		char c = '!';

		cout << "连接(+)测试(TStringAdv类和字符)" << endl;

		s3 = s1 + c;
		cout << "s3应为Hello!，实际输出：" << s3 << endl;

		s3 = c + s1;
		cout << "s3应为!Hello，实际输出：" << s3 << endl;

		s1 = "ello";
		cout << "s3应为Hello!，实际输出：" << 'H' + s1 + c << endl;

		s1 = "hina";
		cout << "s3应为China!，实际输出：" << (s1 = 'C' + s1 + c) << endl;

		wait_for_enter();
	}

	if (1) {
		const TStringAdv s1("可"), s3 = "清", s5 = "也";
		TStringAdv s;
		const char* str2 = "以", str4[] = "心";
		const char c = '!';

		cout << "连接(+)综合测试(TStringAdv类和TStringAdv类、字符指针、字符数组、字符)" << endl;
		s = s1 + str2 + s3 + str4 + s5 + c;
		cout << "s应该是可以清心也!，实际输出：" << s << endl;

		cout << "s应该是也可以清心!，实际输出：" << (s = s5 + s1 + str2 + s3 + str4[0] + str4[1] + c) << endl;
		cout << "s应该是心也可以清!，实际输出：" << (s = str4 + s5 + s1.c_str() + str2 + s3 + c) << endl;
		cout << "s应该是清心也可以!，实际输出：" << (s = s3 + str4 + s5 + s1 + str2[0] + &str2[1] + c) << endl;
		cout << "s应该是以清心也可!，实际输出：" << (s = str2 + s3 + str4 + s5.c_str() + s1.c_str() + c) << endl;

		wait_for_enter();
	}

	if (1) {
		TStringAdv s1("tong"), s2 = "ji";
		const char* str3 = "tong", str4[] = "ji";

		cout << "自连接(+=)简单测试(TStringAdv类和TStringAdv类、字符指针、字符数组、字符)" << endl;

		s1 += s2;
		cout << "s1应为tongji，实际输出：" << s1 << endl;

		s1 = "tong";
		s2 += s1;
		cout << "s2应为jitong，实际输出：" << s2 << endl;

		s1 = "tong";
		s1 += "ji";
		cout << "s1应为tongji，实际输出：" << s1 << endl;

		s1 = "ji";
		s1 += str3;
		cout << "s1应为jitong，实际输出：" << s1 << endl;

		s1 = "tong";
		s1 += str4;
		cout << "s1应为tongji，实际输出：" << s1 << endl;

		s1 = "tong";
		s1 += 'j';
		s1 += 'i';
		cout << "s1应为tongji，实际输出：" << s1 << endl;

		wait_for_enter();
	}

	if (1) {
		TStringAdv s1("可"), s3 = "清", s5 = "也";
		TStringAdv s;
		const char* str2 = "以", str4[] = "心";
		const char c = '!';

		cout << "自连接(+=)综合测试(TStringAdv类和TStringAdv类、字符指针、字符数组、字符)" << endl;

		s = "1.";
		s += s1 + str2 + s3 + str4 + s5 + c;
		cout << "s应该是1.可以清心也!，实际输出：" << s << endl;

		s = "2.";
		cout << "s应该是2.也可以清心!，实际输出：" << (s += s5 + s1 + str2 + s3 + str4[0] + str4[1] + c) << endl;

		s = NULL;
		cout << "s应该是3.心也可以清!，实际输出：" << ((s = "3.") += str4 + s5 + s1.c_str() + str2 + s3 + c) << endl;

		s = NULL;
		cout << "s应该是4.清心也可以!，实际输出：" << (((s += "4." + s3) += (str4 + s5)) += (((s1 += str2[0]) += &str2[1]) += c)) << endl;

		s = NULL;
		s += '5';
		s += '.';
		s1 = "可";
		cout << "s应该是5.以清心也可!，实际输出：" << ((((((s += str2) += s3) += str4) += s5.c_str()) += s1.c_str()) += c) << endl;

		wait_for_enter();
	}

	if (1) {
		TStringAdv s1("This is a pencil"), s2("is"), s3;

		cout << "删除(-)测试(TStringAdv类和TStringAdv类)" << endl;

		cout << "s1应为Th is a pencil，实际输出：" << (s1 = s1 - s2) << endl;
		s3 = s1 - s2;
		cout << "s3应为Th  a pencil，  实际输出：" << s3 << endl;

		s1 = "This is a pencil";
		cout << "s1应为Th  a pencil，  实际输出：" << s1 - s2 - s2 - s2 - s2 - s2 << endl;

		wait_for_enter();
	}

	if (1) {
		TStringAdv s1("This is a pencil"), s2;
		const char* str1 = "is";
		const char str2[] = "is";

		cout << "删除(-)测试(TStringAdv类和char指针及数组)" << endl;

		cout << "s1应为Th is a pencil，实际输出：" << (s1 = s1 - str1) << endl;
		s2 = s1 - str1;
		cout << "s2应为Th  a pencil，  实际输出：" << s2 << endl;

		s1 = "This is a pencil";
		cout << "s1应为Th is a pencil，实际输出：" << (s1 = s1 - str2) << endl;
		s2 = s1 - str2;
		cout << "s2应为Th  a pencil，  实际输出：" << s2 << endl;

		s1 = "This is a pencil";
		cout << "s1应为Th  a pencil，  实际输出：" << s1 - str1 - str1 - str1 - str1 - str1 << endl;

		s1 = "This is a pencil";
		cout << "s1应为Th  a pencil，  实际输出：" << s1 - str2 - str2 - str2 - str2 - str2 << endl;

		wait_for_enter();
	}

	if (1) {
		TStringAdv s1("This is a pencil"), s2;
		char c1 = 'i';

		cout << "删除(-)测试(TStringAdv类和char字符)" << endl;

		cout << "s1应为Ths is a pencil，实际输出：" << (s1 = s1 - c1) << endl;
		s2 = s1 - c1;
		cout << "s2应为Ths s a pencil， 实际输出：" << s2 << endl;

		s1 = "This is a pencil";
		cout << "s2应为Ths s a pencl，  实际输出：" << (s1 - c1 - c1 - c1 - c1 - c1 - c1 - c1) << endl;

		s1 = "This is a pencil";
		cout << "s1应为Thi is a pencil，实际输出：" << (s1 = s1 - 's') << endl;
		s2 = s1 - 's';
		cout << "s2应为Thi i a pencil， 实际输出：" << s2 << endl;

		s1 = "This is a pencil";
		cout << "s2应为Thi i a pencil， 实际输出：" << (s1 - 's' - 's' - 's' - 's' - 's' - 's') << endl;

		wait_for_enter();
	}

	if (1) {
		TStringAdv s1;
		const TStringAdv s2 = "is";
		const char* str3 = "pen", str4[] = "a";
		const char c = ' ';

		cout << "自删除(-=)简单测试(TStringAdv类和TStringAdv类、字符指针、字符数组、字符)" << endl;

		s1 = "This is a red pencil";
		cout << "s1应为Th is a red pencil， 实际输出：" << (s1 -= s2) << endl;

		s1 = "This is a red pencil";
		cout << "s1应为This is a red cil，  实际输出：" << (s1 -= str3) << endl;

		s1 = "This is a red pencil";
		cout << "s1应为This is  red pencil，实际输出：" << (s1 -= str4) << endl;

		s1 = "This is a red pencil";
		cout << "s1应为Thisis a red pencil，实际输出：" << (s1 -= c) << endl;

		wait_for_enter();
	}

	if (1) {
		TStringAdv s1;
		const TStringAdv s2 = "is";
		const char* str3 = "pen", str4[] = "a";
		const char c = ' ';

		cout << "自删除(-=)综合测试(TStringAdv类和TStringAdv类、字符指针、字符数组、字符)" << endl;

		s1 = "This is a red pencil";
		cout << "s1应为Th  a red pencil，   实际输出：" << ((s1 -= s2) -= s2) << endl;

		s1 = "This is a red pencil";
		cout << "s1应为This is  red cil，   实际输出：" << ((s1 -= str3) -= str4) << endl;

		s1 = "This is a red pencil";
		cout << "s1应为Thisisaredpencil，   实际输出：" << ((((s1 -= c) -= c) -= c) -= c) << endl;

		s1 = "This is a red pencil";
		cout << "s1应为Th，                 实际输出：" << ((((((((((((s1 -= s2) -= s2) -= str3) -= str4) -= c) -= c) -= c) -= c) -= "red") -= 'c') -= 'i') -= 'l') << endl;

		wait_for_enter();
	}

	if (1) {
		TStringAdv s1("Hello"), s2;

		cout << "复制(*)测试(TStringAdv类和int)" << endl;

		s2 = s1 * 2;
		cout << "s2应为HelloHello，     实际输出：" << s2 << endl;
		cout << "s1应为HelloHelloHello，实际输出：" << (s1 = s1 * 3) << endl;

		TStringAdv s3;
		cout << "s3应为<NULL>，         实际输出：" << (s3 * 5) << endl;
		cout << "s3应为<NULL>，         实际输出：" << (s3 = s3 * 5) << endl;

		int i, n = 100;
		s1 = "Hello";
		s2 = s1 * n;
		for (i = 1; i < n; i++)
			s2 = s2 - s1;
		cout << "s2应为Hello，          实际输出：" << s2 << endl;

		s1 = "Hello";
		s2 = s1 * n;
		for (i = 0; i < n; i++)
			s2 = s2 - 'l';
		for (i = 0; i < n; i++)
			s2 = s2 - 'l';
		for (i = 0; i < n; i++)
			s2 = s2 - 'o';
		for (i = 0; i < n; i++)
			s2 = s2 - 'H';
		for (i = 1; i < n; i++)  //注意，只有这个循环是从1开始，少做1次.
			s2 = s2 - 'e';
		cout << "s2应为e，              实际输出：" << s2 << endl;

		wait_for_enter();
	}

	if (1) {
		TStringAdv s1;

		cout << "自复制(*=)测试(TStringAdv类和int)" << endl;

		s1 = "Hello";
		cout << "s1应为HelloHello，                       实际输出：" << (s1 *= 2) << endl;
		s1 += '!';
		cout << "s1应为HelloHello!HelloHello!HelloHello!，实际输出：" << (s1 *= 3) << endl;

		s1 = "Hello";
		cout << "s1应为HelloHello!HelloHello!HelloHello!，实际输出：" << (((s1 *= 2) += '!') *= 3) << endl;

		//特别测试：打开下面这行的注释，期望编译器会报错，如果不报错，说明定义有问题，不符合预期的语义（为什么？仔细想!!!）.
		// cout << "s1应为HelloHello!HelloHello!HelloHello!，实际输出：" << (((s1 *= 2) + '!') *= 3) << endl;

		s1 = NULL;
		cout << "s1应为<NULL>，                           实际输出：" << (s1 *= 100) << endl;

		wait_for_enter();
	}

	if (1) {
		TStringAdv s1;

		cout << "自连接(+=)/自删除(-=)/自复制(*=)综合测试" << endl;

		s1 = "Hello";
		cout << "s1应为Hello!Hello!Hello!，实际输出：" << ((s1 += '!') *= 3) << endl;

		s1 = "Hello";
		cout << "s1应为Heo!Heo!Heo!Heo!，  实际输出：" << (((s1 += '!') -= "ll") *= 4) << endl;

		s1 = "Hello";
		cout << "s1应为HellHello!，        实际输出：" << (((s1 *= 2) -= 'o') += '!') << endl;

		wait_for_enter();
	}

	if (1) {
		TStringAdv s1("This is a pencil");

		cout << "反转(!)测试" << endl;

		cout << " s1应为This is a pencil，实际输出：" << s1 << endl;
		cout << "!s1应为licnep a si sihT，实际输出：" << !s1 << endl;
		cout << " s1仍为This is a pencil，实际输出：" << s1 << endl;

		s1 = NULL;
		cout << " s1应为<NULL>，          实际输出：" << s1 << endl;
		cout << "!s1应为<NULL>，          实际输出：" << !s1 << endl;
		cout << " s1仍为<NULL>，          实际输出：" << s1 << endl;

		wait_for_enter();
	}

	if (1) {
		TStringAdv s1 = "house", s2 = "horse", s3 = "house", s4 = "", s5 = NULL;

		cout << "比较运算测试(两个TStringAdv类)" << endl;

		cout << "串1=" << s1 << " 串2=" << s2 << "  > 结果应为1，实际：" << (s1 > s2) << endl;
		cout << "串1=" << s1 << " 串2=" << s2 << "  >=结果应为1，实际：" << (s1 >= s2) << endl;
		cout << "串1=" << s1 << " 串2=" << s2 << "  < 结果应为0，实际：" << (s1 < s2) << endl;
		cout << "串1=" << s1 << " 串2=" << s2 << "  <=结果应为0，实际：" << (s1 <= s2) << endl;
		cout << "串1=" << s1 << " 串2=" << s2 << "  ==结果应为0，实际：" << (s1 == s2) << endl;
		cout << "串1=" << s1 << " 串2=" << s2 << "  !=结果应为1，实际：" << (s1 != s2) << endl;

		cout << "串1=" << s1 << " 串3=" << s3 << "  > 结果应为0，实际：" << (s1 > s3) << endl;
		cout << "串1=" << s1 << " 串3=" << s3 << "  >=结果应为1，实际：" << (s1 >= s3) << endl;
		cout << "串1=" << s1 << " 串3=" << s3 << "  < 结果应为0，实际：" << (s1 < s3) << endl;
		cout << "串1=" << s1 << " 串3=" << s3 << "  <=结果应为1，实际：" << (s1 <= s3) << endl;
		cout << "串1=" << s1 << " 串3=" << s3 << "  ==结果应为1，实际：" << (s1 == s3) << endl;
		cout << "串1=" << s1 << " 串3=" << s3 << "  !=结果应为0，实际：" << (s1 != s3) << endl;

		cout << "串1=" << s1 << " 串4=" << s4 << " > 结果应为1，实际：" << (s1 > s4) << endl;
		cout << "串1=" << s1 << " 串4=" << s4 << " >=结果应为1，实际：" << (s1 >= s4) << endl;
		cout << "串1=" << s1 << " 串4=" << s4 << " < 结果应为0，实际：" << (s1 < s4) << endl;
		cout << "串1=" << s1 << " 串4=" << s4 << " <=结果应为0，实际：" << (s1 <= s4) << endl;
		cout << "串1=" << s1 << " 串4=" << s4 << " ==结果应为0，实际：" << (s1 == s4) << endl;
		cout << "串1=" << s1 << " 串4=" << s4 << " !=结果应为1，实际：" << (s1 != s4) << endl;

		cout << "串1=" << s1 << " 串5=" << s5 << " > 结果应为1，实际：" << (s1 > s5) << endl;
		cout << "串1=" << s1 << " 串5=" << s5 << " >=结果应为1，实际：" << (s1 >= s5) << endl;
		cout << "串1=" << s1 << " 串5=" << s5 << " < 结果应为0，实际：" << (s1 < s5) << endl;
		cout << "串1=" << s1 << " 串5=" << s5 << " <=结果应为0，实际：" << (s1 <= s5) << endl;
		cout << "串1=" << s1 << " 串5=" << s5 << " ==结果应为0，实际：" << (s1 == s5) << endl;
		cout << "串1=" << s1 << " 串5=" << s5 << " !=结果应为1，实际：" << (s1 != s5) << endl;

		wait_for_enter();
	}

	if (1) {
		TStringAdv s1 = "house";

		cout << "比较运算测试(TStringAdv类和字符串常量)" << endl;

		cout << "串1=" << s1 << " 常量=horse" << "  > 结果应为1，实际：" << (s1 > "horse") << endl;
		cout << "串1=" << s1 << " 常量=horse" << "  >=结果应为1，实际：" << (s1 >= "horse") << endl;
		cout << "串1=" << s1 << " 常量=horse" << "  < 结果应为0，实际：" << (s1 < "horse") << endl;
		cout << "串1=" << s1 << " 常量=horse" << "  <=结果应为0，实际：" << (s1 <= "horse") << endl;
		cout << "串1=" << s1 << " 常量=horse" << "  ==结果应为0，实际：" << (s1 == "horse") << endl;
		cout << "串1=" << s1 << " 常量=horse" << "  !=结果应为1，实际：" << (s1 != "horse") << endl;

		cout << "串1=" << s1 << " 常量=house" << "  > 结果应为0，实际：" << (s1 > "house") << endl;
		cout << "串1=" << s1 << " 常量=house" << "  >=结果应为1，实际：" << (s1 >= "house") << endl;
		cout << "串1=" << s1 << " 常量=house" << "  < 结果应为0，实际：" << (s1 < "house") << endl;
		cout << "串1=" << s1 << " 常量=house" << "  <=结果应为1，实际：" << (s1 <= "house") << endl;
		cout << "串1=" << s1 << " 常量=house" << "  ==结果应为1，实际：" << (s1 == "house") << endl;
		cout << "串1=" << s1 << " 常量=house" << "  !=结果应为0，实际：" << (s1 != "house") << endl;

		cout << "串1=" << s1 << " 常量=" << "       > 结果应为1，实际：" << (s1 > "") << endl;
		cout << "串1=" << s1 << " 常量=" << "       >=结果应为1，实际：" << (s1 >= "") << endl;
		cout << "串1=" << s1 << " 常量=" << "       < 结果应为0，实际：" << (s1 < "") << endl;
		cout << "串1=" << s1 << " 常量=" << "       <=结果应为0，实际：" << (s1 <= "") << endl;
		cout << "串1=" << s1 << " 常量=" << "       ==结果应为0，实际：" << (s1 == "") << endl;
		cout << "串1=" << s1 << " 常量=" << "       !=结果应为1，实际：" << (s1 != "") << endl;

		cout << "串1=" << s1 << " 常量=<NULL>" << " > 结果应为1，实际：" << (s1 > NULL) << endl;
		cout << "串1=" << s1 << " 常量=<NULL>" << " >=结果应为1，实际：" << (s1 >= NULL) << endl;
		cout << "串1=" << s1 << " 常量=<NULL>" << " < 结果应为0，实际：" << (s1 < NULL) << endl;
		cout << "串1=" << s1 << " 常量=<NULL>" << " <=结果应为0，实际：" << (s1 <= NULL) << endl;
		cout << "串1=" << s1 << " 常量=<NULL>" << " ==结果应为0，实际：" << (s1 == NULL) << endl;
		cout << "串1=" << s1 << " 常量=<NULL>" << " !=结果应为1，实际：" << (s1 != NULL) << endl;

		wait_for_enter();
	}

	if (1) {
		TStringAdv s1 = NULL, s2 = "";

		/* 空的TStringAdv和NULL、"" 都认为相等（本质上，NULL是地址，""是串，没有可比性，但是此处做特殊处理） */
		cout << "串1=" << s1 << " 串2=" << s2 << "  > 结果应为0，实际：" << (s1 > s2) << endl;
		cout << "串1=" << s1 << " 串2=" << s2 << "  >=结果应为1，实际：" << (s1 >= s2) << endl;
		cout << "串1=" << s1 << " 串2=" << s2 << "  < 结果应为0，实际：" << (s1 < s2) << endl;
		cout << "串1=" << s1 << " 串2=" << s2 << "  <=结果应为1，实际：" << (s1 <= s2) << endl;
		cout << "串1=" << s1 << " 串2=" << s2 << "  ==结果应为1，实际：" << (s1 == s2) << endl;
		cout << "串1=" << s1 << " 串2=" << s2 << "  !=结果应为0，实际：" << (s1 != s2) << endl;

		cout << "串1=" << s1 << " 常量=" << "       > 结果应为0，实际：" << (s1 > "") << endl;
		cout << "串1=" << s1 << " 常量=" << "       >=结果应为1，实际：" << (s1 >= "") << endl;
		cout << "串1=" << s1 << " 常量=" << "       < 结果应为0，实际：" << (s1 < "") << endl;
		cout << "串1=" << s1 << " 常量=" << "       <=结果应为1，实际：" << (s1 <= "") << endl;
		cout << "串1=" << s1 << " 常量=" << "       ==结果应为1，实际：" << (s1 == "") << endl;
		cout << "串1=" << s1 << " 常量=" << "       !=结果应为0，实际：" << (s1 != "") << endl;

		cout << "串1=" << s1 << " 常量=<NULL>" << " > 结果应为0，实际：" << (s1 > NULL) << endl;
		cout << "串1=" << s1 << " 常量=<NULL>" << " >=结果应为1，实际：" << (s1 >= NULL) << endl;
		cout << "串1=" << s1 << " 常量=<NULL>" << " < 结果应为0，实际：" << (s1 < NULL) << endl;
		cout << "串1=" << s1 << " 常量=<NULL>" << " <=结果应为1，实际：" << (s1 <= NULL) << endl;
		cout << "串1=" << s1 << " 常量=<NULL>" << " ==结果应为1，实际：" << (s1 == NULL) << endl;
		cout << "串1=" << s1 << " 常量=<NULL>" << " !=结果应为0，实际：" << (s1 != NULL) << endl;

		wait_for_enter();
	}

	if (1) {
		TStringAdv s1 = "house";
		const char* str2 = "horse", * str3 = "house", * str4 = "", * str5 = NULL;

		cout << "比较运算测试(TStringAdv类和字符指针)" << endl;

		cout << "串1=" << s1 << " 串2=" << str2 << "  > 结果应为1，实际：" << (s1 > str2) << endl;
		cout << "串1=" << s1 << " 串2=" << str2 << "  >=结果应为1，实际：" << (s1 >= str2) << endl;
		cout << "串1=" << s1 << " 串2=" << str2 << "  < 结果应为0，实际：" << (s1 < str2) << endl;
		cout << "串1=" << s1 << " 串2=" << str2 << "  <=结果应为0，实际：" << (s1 <= str2) << endl;
		cout << "串1=" << s1 << " 串2=" << str2 << "  ==结果应为0，实际：" << (s1 == str2) << endl;
		cout << "串1=" << s1 << " 串2=" << str2 << "  !=结果应为1，实际：" << (s1 != str2) << endl;

		cout << "串1=" << s1 << " 串3=" << str3 << "  > 结果应为0，实际：" << (s1 > str3) << endl;
		cout << "串1=" << s1 << " 串3=" << str3 << "  >=结果应为1，实际：" << (s1 >= str3) << endl;
		cout << "串1=" << s1 << " 串3=" << str3 << "  < 结果应为0，实际：" << (s1 < str3) << endl;
		cout << "串1=" << s1 << " 串3=" << str3 << "  <=结果应为1，实际：" << (s1 <= str3) << endl;
		cout << "串1=" << s1 << " 串3=" << str3 << "  ==结果应为1，实际：" << (s1 == str3) << endl;
		cout << "串1=" << s1 << " 串3=" << str3 << "  !=结果应为0，实际：" << (s1 != str3) << endl;

		cout << "串1=" << s1 << " 串4=" << str4 << "       > 结果应为1，实际：" << (s1 > str4) << endl;
		cout << "串1=" << s1 << " 串4=" << str4 << "       >=结果应为1，实际：" << (s1 >= str4) << endl;
		cout << "串1=" << s1 << " 串4=" << str4 << "       < 结果应为0，实际：" << (s1 < str4) << endl;
		cout << "串1=" << s1 << " 串4=" << str4 << "       <=结果应为0，实际：" << (s1 <= str4) << endl;
		cout << "串1=" << s1 << " 串4=" << str4 << "       ==结果应为0，实际：" << (s1 == str4) << endl;
		cout << "串1=" << s1 << " 串4=" << str4 << "       !=结果应为1，实际：" << (s1 != str4) << endl;

		cout << "串1=" << s1 << " 串5=<NULL>" << " > 结果应为1，实际：" << (s1 > str5) << endl;
		cout << "串1=" << s1 << " 串5=<NULL>" << " >=结果应为1，实际：" << (s1 >= str5) << endl;
		cout << "串1=" << s1 << " 串5=<NULL>" << " < 结果应为0，实际：" << (s1 < str5) << endl;
		cout << "串1=" << s1 << " 串5=<NULL>" << " <=结果应为0，实际：" << (s1 <= str5) << endl;
		cout << "串1=" << s1 << " 串5=<NULL>" << " ==结果应为0，实际：" << (s1 == str5) << endl;
		cout << "串1=" << s1 << " 串5=<NULL>" << " !=结果应为1，实际：" << (s1 != str5) << endl;

		wait_for_enter();
	}

	if (1) {
		TStringAdv s1 = "house";
		char str2[] = "horse", str3[] = "house", str4[] = "";

		cout << "比较运算测试(TStringAdv类和字符指针)" << endl;

		cout << "串1=" << s1 << " 串2=" << str2 << " > 结果应为1，实际：" << (s1 > str2) << endl;
		cout << "串1=" << s1 << " 串2=" << str2 << " >=结果应为1，实际：" << (s1 >= str2) << endl;
		cout << "串1=" << s1 << " 串2=" << str2 << " < 结果应为0，实际：" << (s1 < str2) << endl;
		cout << "串1=" << s1 << " 串2=" << str2 << " <=结果应为0，实际：" << (s1 <= str2) << endl;
		cout << "串1=" << s1 << " 串2=" << str2 << " ==结果应为0，实际：" << (s1 == str2) << endl;
		cout << "串1=" << s1 << " 串2=" << str2 << " !=结果应为1，实际：" << (s1 != str2) << endl;

		cout << "串1=" << s1 << " 串3=" << str3 << " > 结果应为0，实际：" << (s1 > str3) << endl;
		cout << "串1=" << s1 << " 串3=" << str3 << " >=结果应为1，实际：" << (s1 >= str3) << endl;
		cout << "串1=" << s1 << " 串3=" << str3 << " < 结果应为0，实际：" << (s1 < str3) << endl;
		cout << "串1=" << s1 << " 串3=" << str3 << " <=结果应为1，实际：" << (s1 <= str3) << endl;
		cout << "串1=" << s1 << " 串3=" << str3 << " ==结果应为1，实际：" << (s1 == str3) << endl;
		cout << "串1=" << s1 << " 串3=" << str3 << " !=结果应为0，实际：" << (s1 != str3) << endl;

		cout << "串1=" << s1 << " 串4=" << str4 << "      > 结果应为1，实际：" << (s1 > str4) << endl;
		cout << "串1=" << s1 << " 串4=" << str4 << "      >=结果应为1，实际：" << (s1 >= str4) << endl;
		cout << "串1=" << s1 << " 串4=" << str4 << "      < 结果应为0，实际：" << (s1 < str4) << endl;
		cout << "串1=" << s1 << " 串4=" << str4 << "      <=结果应为0，实际：" << (s1 <= str4) << endl;
		cout << "串1=" << s1 << " 串4=" << str4 << "      ==结果应为0，实际：" << (s1 == str4) << endl;
		cout << "串1=" << s1 << " 串4=" << str4 << "      !=结果应为1，实际：" << (s1 != str4) << endl;

		wait_for_enter();
	}

	if (1) {
		TStringAdv s1 = "tong", s2;

		cout << "求长度测试(length()函数)" << endl;

		cout << "s1为tong，  长度应为4，实际：" << s1.length() << endl;
		cout << "s2为<NULL>，长度应为0，实际：" << s2.length() << endl;
		s2 = s1 + "ji";
		cout << "s2为tongji，长度应为6，实际：" << s2.length() << endl;

		wait_for_enter();
	}

	if (1) {
		TStringAdv s1 = "tong", s2;

		cout << "求长度测试(TStringLen()函数)" << endl;

		cout << "s1为tong，  长度应为4，实际：" << TStringLen(s1) << endl;
		cout << "s2为<NULL>，长度应为0，实际：" << TStringLen(s2) << endl;
		cout << "串为tongji，长度应为6，实际：" << TStringLen(s1 + (s2 = "ji")) << endl;
		cout << "串为tongji，长度应为6，实际：" << TStringLen(s1 + "ji") << endl;
		cout << "串为tongji，长度应为6，实际：" << TStringLen(s2 = s1 + "ji") << endl;
		cout << "串为tong，  长度应为4，实际：" << TStringLen(s1 + (char*)NULL) << endl;

		wait_for_enter();
	}

	if (1) {
		TStringAdv s1 = "house";
		TStringAdv s2[4] = { "yangpu", "sipingroad", "tongji", "shanghai" };
		int i, j;
		char ch = 'P';

		cout << "[]运算符测试" << endl;

		cout << "串1是" << s1 << "，依次打印字符的结果是：";
		for (i = 0; i < s1.length(); i++)
			cout << s1[i] << ' ';
		cout << endl << endl;

		cout << "串1是" << s1 << "，依次打印字符int值的结果是（有越界读）：" << endl;
		for (i = -4; i < s1.length() + 4; i++)
			cout << int(s1[i]) << ' ';
		cout << endl << endl;

		s1[0] = s1[0] - 32;
		cout << "串1是" << s1 << "，依次打印字符的结果是：";
		for (i = 0; i < s1.length(); i++)
			cout << s1[i] << ' ';
		cout << endl << endl;

		s1[1] = 'A';
		s1[2] = ch;
		ch += 32;
		s1[3] = ch;
		s1[4] = 'Y';
		cout << "串1是" << s1 << "，依次打印字符的结果是：";
		for (i = 0; i < s1.length(); i++)
			cout << s1[i] << ' ';
		cout << endl << endl;

		cout << "串2数组是4个字符串，依次打印字符的结果是：" << endl;
		for (i = 0; i < 4; i++) {
			cout << setw(16) << s2[i] << " => ";
			for (j = 0; j < s2[i].length(); j++)
				cout << s2[i][j] << ' ';
			cout << endl;
		}
		cout << endl;

		cout << "串2数组是4个字符串，首字母大写后依次打印字符的结果是：" << endl;
		for (i = 0; i < 4; i++) {
			s2[i][0] -= 32;
			cout << setw(16) << s2[i] << " => ";
			for (j = 0; j < s2[i].length(); j++)
				cout << s2[i][j] << ' ';
			cout << endl;
		}
		cout << endl;

		wait_for_enter();
	}

	if (1) {
		TStringAdv s1("Thank"), s2, s3;
		const char* str1 = "you";
		char str2[] = "!!!";
		char c = '*';
		char empty_pos = '\0';

		cout << "append函数测试" << endl;

		s1.append(c);
		cout << "s1应该是Thank*，       实际输出：" << s1 << endl;

		s1.append(empty_pos);
		cout << "s1应该是Thank*，       实际输出：" << s1 << endl;

		s1.append(str1);
		cout << "s1应该是Thank*you，    实际输出：" << s1 << endl;

		s2.append(str2);
		cout << "s2应该是!!!，          实际输出：" << s2 << endl;

		s3.append(s1).append(s2);
		cout << "s3应该是Thank*you!!!， 实际输出：" << s3 << endl;

		wait_for_enter();
	}

	if (1) {
		TStringAdv s1("Hello"), s2, s3;

		cout << "assign函数测试" << endl;

		s1.assign("你好");
		cout << "s1应该是你好，    实际输出：" << s1 << endl;

		s1.assign("Hello");
		cout << "s1应该是Hello，   实际输出：" << s1 << endl;

		s2.assign("Hello");
		cout << "s2应该是Hello，   实际输出：" << s2 << endl;

		s2.assign("");
		cout << "s2应该是<NULL>，  实际输出：" << s2 << endl;

		s1.assign('h');
		cout << "s1应该是h，       实际输出：" << s1 << endl;

		s1.assign('\0');
		cout << "s1应该是<NULL>，  实际输出：" << s1 << endl;

		const char* str = "你好!!!";
		s1.assign("hello").assign(str);
		cout << "s1应该是你好!!!， 实际输出：" << s1 << endl;

		wait_for_enter();
	}

	if (1) {
		TStringAdv s1 = "我这学期满绩了", s2 = "ComputerScence", s3;
		const char* str1 = "们";
		char c = '!';

		cout << "insert函数测试" << endl;

		s1.insert(str1, 3);
		cout << "s1应该是我们这学期满绩了，                   实际输出：" << s1 << endl;

		s1.insert(c, 17);
		cout << "s1应该是我们这学期满绩了!，                  实际输出：" << s1 << endl;

		s2.insert(' ', 9).insert('i', 12);
		cout << "s2应该是Computer Science，                   实际输出：" << s2 << endl;

		s1.insert(s2, 5);
		cout << "s1应该是我们Computer Science这学期满绩了!，  实际输出：" << s1 << endl;

		s3.insert(s1, 1);
		s3.insert("寄了!", 27).insert('\0', 32);
		cout << "s3应该是我们Computer Science这学期寄了!，    实际输出：" << s3 << endl;

		wait_for_enter();
	}

	if (1) {
		TStringAdv s1 = "tong", s2 = "tongji tongji jitong jti", s3 = "tong";
		char  str1[] = "tong";
		const char* str2 = "ji";
		char c = 't', c1 = ' ';

		cout << "erase函数测试" << endl;

		s1.erase(str2);
		cout << "s1为tong，                    实际：" << s1 << endl;

		s1.erase(str1);
		cout << "s1为<NULL>，                  实际：" << s1 << endl;

		s1.erase(c);
		cout << "s1为<NULL>，                  实际：" << s1 << endl;

		s2.erase(s3);
		cout << "s2为ji tongji jitong jti，    实际：" << s2 << endl;

		s2.erase(str1);
		cout << "s2为ji ji jitong jti，        实际：" << s2 << endl;

		s2.erase(str2);
		cout << "s2为 ji jitong jti，          实际：" << s2 << endl;

		s2.erase(str2);
		cout << "s2为  jitong jti，            实际：" << s2 << endl;

		s2.erase(str1);
		cout << "s2为  ji jti，                实际：" << s2 << endl;

		s2.erase(str1);
		cout << "s2为  ji jti，                实际：" << s2 << endl;

		s2.erase(str2);
		cout << "s2为   jti，                  实际：" << s2 << endl;

		s2.erase(str2);
		cout << "s2为   jti，                  实际：" << s2 << endl;

		s2.erase(c1).erase(c1).erase(c1);
		cout << "s2为jti，                     实际：" << s2 << endl;

		s2.erase(str2);
		cout << "s2为jti，                     实际：" << s2 << endl;

		s2.erase(c);
		cout << "s2为ji，                      实际：" << s2 << endl;

		s2.erase(str2);
		cout << "s2为<NULL>，                  实际：" << s2 << endl;

		wait_for_enter();
	}

	if (1) {//           01234567890123456
		TStringAdv s1 = "Computer Science!", s2;

		cout << "substr函数测试" << endl;

		s2 = s1.substr(1);
		cout << "s2为Computer Science!，  实际：" << s2 << endl;

		s2 = s1.substr(0);
		cout << "s2为<NULL>，             实际：" << s2 << endl;

		s2 = s1.substr(10);
		cout << "s2为Science!，           实际：" << s2 << endl;

		s2 = s1.substr(1, 8);
		cout << "s2为Computer，           实际：" << s2 << endl;

		s2 = s1.substr(1, 20);
		cout << "s2为Computer Science!，  实际：" << s2 << endl;

		s2 = s1.substr(1, 0);
		cout << "s2为<NULL>，             实际：" << s2 << endl;

		wait_for_enter();
	}

	if (1) {//           01234567890123456
		TStringAdv s1 = "Computer Science!";
		char c;
		cout << "at函数测试" << endl;
		c = s1.at(0);
		cout << "c为C，实际：" << c << endl;

		c = s1.at(5);
		cout << "c为t，实际：" << c << endl;

		c = s1.at(10);
		cout << "c为c，实际：" << c << endl;

		c = s1.at(16);
		cout << "c为!，实际：" << c << endl;

		s1.at(16) = '?';
		cout << "c为?，实际：" << s1.at(16) << endl;

		wait_for_enter();
	}

#if !(defined(__linux) || defined(__linux__))
	system("pause"); //Linux不需要.
#endif

	return 0;
}
