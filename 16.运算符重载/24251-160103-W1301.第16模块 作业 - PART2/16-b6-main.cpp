#include <iostream>
#include "16-b6.h"
using namespace std;

#if defined(__linux) || defined(__linux__) //Linux
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

#else //VS+Dev
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
		week w1 = week::wed, w2;
		static week w3;

		cout << "enum class的cout基本输出测试(常/变量):" << endl;
		cout << "======================================" << endl;
		cout << "期望输出 : 星期三 实际输出 : " << w1 << endl;
		cout << "期望输出 : 随机   实际输出 : " << w2 << endl; //本行随机的意思值"星期日/../星期六/错误"都可以接受
		cout << "期望输出 : 星期日 实际输出 : " << w3 << endl;
		cout << "期望输出 : 星期六 实际输出 : " << week::sat << endl;
		cout << "期望输出 : 错误   实际输出 : " << static_cast<week>(9) << endl;
		cout << "期望输出 : 错误   实际输出 : " << week(11) << endl;
		cout << "期望输出 : 错误   实际输出 : " << (week)12 << endl;
		cout << endl;

		wait_for_enter();
	}

	if (1) {
		week w;

		cout << "enum class的cin基本输出测试:" << endl;
		cout << "============================" << endl;
		cout << "请输入mon（区分大小写）" << endl;
		cin >> w;
		cout << "期望输出 : 星期一 实际输出 : " << w << endl;

		cout << "请输入Mon（区分大小写）" << endl;
		cin >> w;
		cout << "期望输出 : 星期一 实际输出 : " << w << endl;

		cout << "请输入mOn（区分大小写）" << endl;
		cin >> w;
		cout << "期望输出 : 星期一 实际输出 : " << w << endl;

		cout << "请输入moN（区分大小写）" << endl;
		cin >> w;
		cout << "期望输出 : 星期一 实际输出 : " << w << endl;

		cout << "请输入MOn（区分大小写）" << endl;
		cin >> w;
		cout << "期望输出 : 星期一 实际输出 : " << w << endl;

		cout << "请输入mON（区分大小写）" << endl;
		cin >> w;
		cout << "期望输出 : 星期一 实际输出 : " << w << endl;

		cout << "请输入MoN（区分大小写）" << endl;
		cin >> w;
		cout << "期望输出 : 星期一 实际输出 : " << w << endl;

		cout << "请输入MON（区分大小写）" << endl;
		cin >> w;
		cout << "期望输出 : 星期一 实际输出 : " << w << endl;

		cout << "循环7次，每次以任意大小写组合依次输入sun / mon / tue / wed / thu / fri / sat" << endl;
		for (int i = 0; i < 7; i++) {
			cin >> w;
			cout << "期望输出 : " << week(i) << " 实际输出 : " << w << endl;
		}

		cout << "循环3次，每次任意输入非sun / mon / tue / wed / thu / fri / sat的内容" << endl;
		for (int i = 0; i < 3; i++) {
		cin >> w;
		cout << "期望输出 : 错误    实际输出 : " << w << endl;
		}

		wait_for_enter();
	}

	if (1) {
		week w1 = week::wed, w2;

		cout << "enum class的++测试:" << endl;
		cout << "===================" << endl;
		w2 = w1++;
		cout << "期望输出 : 星期四 实际输出 : " << w1 << endl;
		cout << "期望输出 : 星期三 实际输出 : " << w2 << endl;
		cout << endl;

		w1 = week::sat;
		w2 = w1++;
		cout << "期望输出 : 星期日 实际输出 : " << w1 << endl;
		cout << "期望输出 : 星期六 实际输出 : " << w2 << endl;
		cout << endl;

		w1 = week::wed;
		w2 = ++w1;
		cout << "期望输出 : 星期四 实际输出 : " << w1 << endl;
		cout << "期望输出 : 星期四 实际输出 : " << w2 << endl;
		cout << endl;

		w1 = week::sat;
		w2 = ++w1;
		cout << "期望输出 : 星期日 实际输出 : " << w1 << endl;
		cout << "期望输出 : 星期日 实际输出 : " << w2 << endl;
		cout << endl;

		wait_for_enter();
	}

	if (1) {
		cout << "enum class的循环前缀++测试:" << endl;
		cout << "===========================" << endl;

		week w1 = week::fri;
		const char chn[] = "六日一二三四五";
		for (int i = 0; i < 7; i++) {
			cout << "期望输出 : 星期" << chn[i * 2] << chn[i * 2 + 1] << " 实际输出 : " << ++w1 << endl;
		}

		wait_for_enter();
	}

	if (1) {
		cout << "enum class的循环后缀++测试:" << endl;
		cout << "===========================" << endl;

		week w1 = week::wed;
		const char chn[] = "三四五六日一二";
		for (int i = 0; i < 7; i++) {
			cout << "期望输出 : 星期" << chn[i * 2] << chn[i * 2 + 1] << " 实际输出 : " << w1++ << endl;
		}

		wait_for_enter();
	}

	if (1) {
		week w1 = week::wed, w2;

		cout << "enum class的--测试:" << endl;
		cout << "===================" << endl;
		w2 = w1--;
		cout << "期望输出 : 星期二 实际输出 : " << w1 << endl;
		cout << "期望输出 : 星期三 实际输出 : " << w2 << endl;
		cout << endl;

		w1 = week::sun;
		w2 = w1--;
		cout << "期望输出 : 星期六 实际输出 : " << w1 << endl;
		cout << "期望输出 : 星期日 实际输出 : " << w2 << endl;
		cout << endl;

		w1 = week::wed;
		w2 = --w1;
		cout << "期望输出 : 星期二 实际输出 : " << w1 << endl;
		cout << "期望输出 : 星期二 实际输出 : " << w2 << endl;
		cout << endl;

		w1 = week::sun;
		w2 = --w1;
		cout << "期望输出 : 星期六 实际输出 : " << w1 << endl;
		cout << "期望输出 : 星期六 实际输出 : " << w2 << endl;
		cout << endl;

		wait_for_enter();
	}

	if (1) {
		cout << "enum class的循环前缀--测试:" << endl;
		cout << "===========================" << endl;

		week w1 = week::fri;
		const char chn[] = "五六日一二三四";
		for (int i = 6; i >=0; i--) {
			cout << "期望输出 : 星期" << chn[i * 2] << chn[i * 2 + 1] << " 实际输出 : " << --w1 << endl;
		}

		wait_for_enter();
	}

	if (1) {
		cout << "enum class的循环后缀--测试:" << endl;
		cout << "===========================" << endl;

		week w1 = week::wed;
		const char chn[] = "四五六日一二三";
		for (int i = 6; i >= 0; i--) {
			cout << "期望输出 : 星期" << chn[i * 2] << chn[i * 2 + 1] << " 实际输出 : " << w1-- << endl;
		}

		wait_for_enter();
	}

	if (1) {
		week w1 = week::wed, w2;

		cout << "enum class的+/-测试1:" << endl;
		cout << "=====================" << endl;
		w2 = w1+2;
		cout << "期望输出 : 星期三 实际输出 : " << w1 << endl;
		cout << "期望输出 : 星期五 实际输出 : " << w2 << endl;
		cout << endl;

		w1 = week::wed;
		w2 = w1+15;
		cout << "期望输出 : 星期三 实际输出 : " << w1 << endl;
		cout << "期望输出 : 星期四 实际输出 : " << w2 << endl;
		cout << endl;

		w1 = week::wed;
		w2 = w1-3;
		cout << "期望输出 : 星期三 实际输出 : " << w1 << endl;
		cout << "期望输出 : 星期日 实际输出 : " << w2 << endl;
		cout << endl;

		w1 = week::wed;
		w2 = w1-7006;
		cout << "期望输出 : 星期三 实际输出 : " << w1 << endl;
		cout << "期望输出 : 星期四 实际输出 : " << w2 << endl;
		cout << endl;

		wait_for_enter();
	}

	if (1) {
		week w1 = week::wed;

		cout << "enum class的+/-测试2:" << endl;
		cout << "=====================" << endl;
		w1 = w1 + 2;
		cout << "期望输出 : 星期五 实际输出 : " << w1 << endl;

		w1 = week::wed;
		w1 = w1 + 15;
		cout << "期望输出 : 星期四 实际输出 : " << w1 << endl;

		w1 = week::wed;
		w1 = w1 - 3;
		cout << "期望输出 : 星期日 实际输出 : " << w1 << endl;

		w1 = week::wed;
		w1 = w1 - 7006;
		cout << "期望输出 : 星期四 实际输出 : " << w1 << endl;

		wait_for_enter();
	}

	if (1) {
		week w1 = week::wed;

		cout << "enum class的+=/-=测试:" << endl;
		cout << "======================" << endl;

		w1 += 2;
		cout << "期望输出 : 星期五 实际输出 : " << w1 << endl;

		w1 = week::wed;
		w1 += 15;
		cout << "期望输出 : 星期四 实际输出 : " << w1 << endl;

		w1 = week::wed;
		w1 -= 3;
		cout << "期望输出 : 星期日 实际输出 : " << w1 << endl;

		w1 = week::wed;
		w1 -= 7006;
		cout << "期望输出 : 星期四 实际输出 : " << w1 << endl;

		cout << endl;
		wait_for_enter();
	}


	return 0;
}
