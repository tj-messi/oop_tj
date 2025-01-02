/*2351114 朱俊泽 大数据*/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <Windows.h>
#include <conio.h>
using namespace std;
#include "../include/class_aat.h"
#include "15-b8-bmp.h"

/* 已定义的静态全局变量 */
static HWND hWnd;
static HDC hdc = NULL;
static int _BgColor_, _FgColor_, _Width_, _High;

/***************************************************************************
  函数名称：
  功    能：释放画图资源
  输入参数：
  返 回 值：
  说    明：可重入
***************************************************************************/
static void hdc_release()
{
	if (hdc) {
		ReleaseDC(hWnd, hdc);
		hdc = NULL;
	}
}

/***************************************************************************
  函数名称：
  功    能：初始化
  输入参数：const int bgcolor：背景色
			const int fgcolor：前景色
			const int width  ：屏幕宽度（点阵）
			const int high   ：屏幕高度（点阵）
  返 回 值：
  说    明：
***************************************************************************/
static void hdc_init(const int bgcolor, const int fgcolor, const int width, const int high)
{
	void hdc_release(); //提前声明

	/* 先释放，防止不release而再次init（hdc_release可重入） */
	hdc_release();

	/* 窗口init后，用一个静态全局量记录，后续hdc_cls()会用到 */
	_BgColor_ = bgcolor;
	_FgColor_ = fgcolor;
	_Width_ = width;
	_High = high;

	hdc = GetDC(hWnd);
}

/***************************************************************************
  函数名称：
  功    能：设置画笔颜色，传入RGB值
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
static void hdc_set_pencolor_by_RGB(const int RGB_value)
{
	SelectObject(hdc, GetStockObject(DC_PEN));
	SetDCPenColor(hdc, RGB_value);
}

/***************************************************************************
  函数名称：
  功    能：设置画笔颜色，传入RGB三色，值0-255
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
static void hdc_set_pencolor(const unsigned char red, const unsigned char green, const unsigned char blue)
{
	hdc_set_pencolor_by_RGB(RGB(red, green, blue));
}

/***************************************************************************
  函数名称：
  功    能：清除屏幕上现有的图形
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
static void hdc_cls()
{
	/* 发现一定要换一种颜色初始化才能清除像素点，找到更简便方法的同学可以通知我 */
	hdc_init(_BgColor_, (_FgColor_ + 1) % 16, _Width_, _High);

	hdc_init(_BgColor_, _FgColor_, _Width_, _High);

	/* 部分机器上运行demo时，会出现hdc_cls()后第一根线有缺线的情况，加延时即可
	   如果部分机器运行还有问题，调高此延时值 */
	Sleep(30);
}

/***************************************************************************
  函数名称：
  功    能：在(x,y)位置处用指定颜色画出一个像素点
  输入参数：const int x：x坐标，左上角为(0,0)
			const int y：y坐标，左上角为(0,0)
  返 回 值：
  说    明：颜色直接用当前设定
***************************************************************************/
void hdc_base_point(const int x, const int y, const unsigned char red, const unsigned char green, const unsigned char blue)
{
	/* 设置画笔的颜色（该点的颜色）*/
	hdc_set_pencolor(red, green, blue);
	/* 画点 */
	MoveToEx(hdc, x - 1, y - 1, NULL);
	LineTo(hdc, x, y);
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
static void usage(const char *const procname)
{
	cout << "Usgae : " << procname << " --bmpname bmp图片文件名 [ --start_x 0-300 | --start_y 0-300 | --angle 0/90/180/270 | --mirror ]" << endl;
	cout << "        " << procname << " --bmpname xxxx.bmp" << endl;
	cout << "        " << procname << " --bmpname xxxx.bmp --angle 90" << endl;
	cout << "        " << procname << " --bmpname xxxx.bmp --angle 90 --mirror" << endl;
	cout << "        " << procname << " --bmpname xxxx.bmp --start_x 100 --start_y 200" << endl;
	cout << endl;
}

enum OPT_ARGS {
	ARGS_HELP,
	ARGS_BMPNAME,
	ARGS_START_X,
	ARGS_START_Y,
	ARGS_ANGLE,
	ARGS_MIRROR
};

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
int main(int argc, char **argv)
{
#if 0
	/* 这是一段hdc_point画点的演示程序，看懂后，改为#if 0即可*/
	hWnd = GetConsoleWindow();
	hdc_init(0, 7, 1920, 1080);
	hdc_cls();

	const double PI = 3.14159;
	const int begin_x = 100, begin_y = 100, radius = 50;
	int x, y;

	/* 逆时针画圆弧（Y轴向下，观察哪个是起点（0°角） */
	hdc_base_point(begin_x, begin_y, 0xFF, 0x0, 0x0);  //圆心
	for (int angle = 0; angle < 360; angle++) {
		x = begin_x + (int)(radius * sin(angle * PI / 180));
		y = begin_y + (int)(radius * cos(angle * PI / 180));
		hdc_base_point(x, y, 0xFF, 0x0, 0x0);  //红色
		Sleep(20); //延时
	}

	hdc_release();

	return 0;
#endif

	int angle_set[] = { 0, 90, 180, 270, INVALID_INT_VALUE_OF_SET }; 		//结尾必须是INVALID_INT_VALUE_OF_SET

	args_analyse_tools args[] = {
		args_analyse_tools("--help",      ST_EXTARGS_TYPE::boolean, 0, false),
		args_analyse_tools("--bmpname",   ST_EXTARGS_TYPE::str, 1, string("")),
		args_analyse_tools("--start_x",   ST_EXTARGS_TYPE::int_with_default, 1, 0, 0, 300),
		args_analyse_tools("--start_y",   ST_EXTARGS_TYPE::int_with_default, 1, 0, 0, 300),
		args_analyse_tools("--angle",     ST_EXTARGS_TYPE::int_with_set_default, 1, 0, angle_set),
		args_analyse_tools("--mirror",    ST_EXTARGS_TYPE::boolean, 0, false),
		args_analyse_tools()  //最后一个，用于结束
	};

	int cur_argc;
	if ((cur_argc = args_analyse_process(argc, argv, args, 0)) < 0)
	{
		//错误信息在函数中已打印
		return -1;
	}

	/* 打印参数的分析结果 */
	if (args[ARGS_HELP].existed()) {
		args_analyse_print(args);
		cout << "必须指定参数[" << args[ARGS_BMPNAME].get_name() << "]" << endl;
		return -1;
	}

	if (args[ARGS_BMPNAME].existed()==false) {
		usage(argv[0]);
		cout << "必须指定参数[" << args[ARGS_BMPNAME].get_name() << "]" << endl;
		return -1;
	}

	string filename = args[ARGS_BMPNAME].get_string();
	int angle = args[ARGS_ANGLE].get_int();
	int start_x = args[ARGS_START_X].get_int();
	int start_y = args[ARGS_START_Y].get_int();
	bool is_mirror = args[ARGS_MIRROR].existed();

	/* 通过带一参的构造函数方式，读取指定bmp的格式及所有点的颜色信息 */
	bitmap bmp(filename.c_str()); //为了不让15-b8-bmp.h中包含头文件，特地改成char*形式

	hWnd = GetConsoleWindow();
	hdc_init(0, 7, 1920, 1080);
	hdc_cls();

	/* 传入 hdc_base_point 用于画点 */
	bmp.show(start_x, start_y, angle, is_mirror, hdc_base_point);

	hdc_release();

#if 1
	/* 等待回车键结束 */
	while (_getch() != '\r')
		;
#endif
	return 0;
}
