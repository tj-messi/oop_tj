/*2351114 �쿡�� ������*/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <Windows.h>
#include <conio.h>
using namespace std;
#include "../include/class_aat.h"
#include "15-b8-bmp.h"

/* �Ѷ���ľ�̬ȫ�ֱ��� */
static HWND hWnd;
static HDC hdc = NULL;
static int _BgColor_, _FgColor_, _Width_, _High;

/***************************************************************************
  �������ƣ�
  ��    �ܣ��ͷŻ�ͼ��Դ
  ���������
  �� �� ֵ��
  ˵    ����������
***************************************************************************/
static void hdc_release()
{
	if (hdc) {
		ReleaseDC(hWnd, hdc);
		hdc = NULL;
	}
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ���ʼ��
  ���������const int bgcolor������ɫ
			const int fgcolor��ǰ��ɫ
			const int width  ����Ļ��ȣ�����
			const int high   ����Ļ�߶ȣ�����
  �� �� ֵ��
  ˵    ����
***************************************************************************/
static void hdc_init(const int bgcolor, const int fgcolor, const int width, const int high)
{
	void hdc_release(); //��ǰ����

	/* ���ͷţ���ֹ��release���ٴ�init��hdc_release�����룩 */
	hdc_release();

	/* ����init����һ����̬ȫ������¼������hdc_cls()���õ� */
	_BgColor_ = bgcolor;
	_FgColor_ = fgcolor;
	_Width_ = width;
	_High = high;

	hdc = GetDC(hWnd);
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ����û�����ɫ������RGBֵ
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
static void hdc_set_pencolor_by_RGB(const int RGB_value)
{
	SelectObject(hdc, GetStockObject(DC_PEN));
	SetDCPenColor(hdc, RGB_value);
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ����û�����ɫ������RGB��ɫ��ֵ0-255
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
static void hdc_set_pencolor(const unsigned char red, const unsigned char green, const unsigned char blue)
{
	hdc_set_pencolor_by_RGB(RGB(red, green, blue));
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ������Ļ�����е�ͼ��
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
static void hdc_cls()
{
	/* ����һ��Ҫ��һ����ɫ��ʼ������������ص㣬�ҵ�����㷽����ͬѧ����֪ͨ�� */
	hdc_init(_BgColor_, (_FgColor_ + 1) % 16, _Width_, _High);

	hdc_init(_BgColor_, _FgColor_, _Width_, _High);

	/* ���ֻ���������demoʱ�������hdc_cls()���һ������ȱ�ߵ����������ʱ����
	   ������ֻ������л������⣬���ߴ���ʱֵ */
	Sleep(30);
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ���(x,y)λ�ô���ָ����ɫ����һ�����ص�
  ���������const int x��x���꣬���Ͻ�Ϊ(0,0)
			const int y��y���꣬���Ͻ�Ϊ(0,0)
  �� �� ֵ��
  ˵    ������ɫֱ���õ�ǰ�趨
***************************************************************************/
void hdc_base_point(const int x, const int y, const unsigned char red, const unsigned char green, const unsigned char blue)
{
	/* ���û��ʵ���ɫ���õ����ɫ��*/
	hdc_set_pencolor(red, green, blue);
	/* ���� */
	MoveToEx(hdc, x - 1, y - 1, NULL);
	LineTo(hdc, x, y);
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
static void usage(const char *const procname)
{
	cout << "Usgae : " << procname << " --bmpname bmpͼƬ�ļ��� [ --start_x 0-300 | --start_y 0-300 | --angle 0/90/180/270 | --mirror ]" << endl;
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
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
int main(int argc, char **argv)
{
#if 0
	/* ����һ��hdc_point�������ʾ���򣬿����󣬸�Ϊ#if 0����*/
	hWnd = GetConsoleWindow();
	hdc_init(0, 7, 1920, 1080);
	hdc_cls();

	const double PI = 3.14159;
	const int begin_x = 100, begin_y = 100, radius = 50;
	int x, y;

	/* ��ʱ�뻭Բ����Y�����£��۲��ĸ�����㣨0��ǣ� */
	hdc_base_point(begin_x, begin_y, 0xFF, 0x0, 0x0);  //Բ��
	for (int angle = 0; angle < 360; angle++) {
		x = begin_x + (int)(radius * sin(angle * PI / 180));
		y = begin_y + (int)(radius * cos(angle * PI / 180));
		hdc_base_point(x, y, 0xFF, 0x0, 0x0);  //��ɫ
		Sleep(20); //��ʱ
	}

	hdc_release();

	return 0;
#endif

	int angle_set[] = { 0, 90, 180, 270, INVALID_INT_VALUE_OF_SET }; 		//��β������INVALID_INT_VALUE_OF_SET

	args_analyse_tools args[] = {
		args_analyse_tools("--help",      ST_EXTARGS_TYPE::boolean, 0, false),
		args_analyse_tools("--bmpname",   ST_EXTARGS_TYPE::str, 1, string("")),
		args_analyse_tools("--start_x",   ST_EXTARGS_TYPE::int_with_default, 1, 0, 0, 300),
		args_analyse_tools("--start_y",   ST_EXTARGS_TYPE::int_with_default, 1, 0, 0, 300),
		args_analyse_tools("--angle",     ST_EXTARGS_TYPE::int_with_set_default, 1, 0, angle_set),
		args_analyse_tools("--mirror",    ST_EXTARGS_TYPE::boolean, 0, false),
		args_analyse_tools()  //���һ�������ڽ���
	};

	int cur_argc;
	if ((cur_argc = args_analyse_process(argc, argv, args, 0)) < 0)
	{
		//������Ϣ�ں������Ѵ�ӡ
		return -1;
	}

	/* ��ӡ�����ķ������ */
	if (args[ARGS_HELP].existed()) {
		args_analyse_print(args);
		cout << "����ָ������[" << args[ARGS_BMPNAME].get_name() << "]" << endl;
		return -1;
	}

	if (args[ARGS_BMPNAME].existed()==false) {
		usage(argv[0]);
		cout << "����ָ������[" << args[ARGS_BMPNAME].get_name() << "]" << endl;
		return -1;
	}

	string filename = args[ARGS_BMPNAME].get_string();
	int angle = args[ARGS_ANGLE].get_int();
	int start_x = args[ARGS_START_X].get_int();
	int start_y = args[ARGS_START_Y].get_int();
	bool is_mirror = args[ARGS_MIRROR].existed();

	/* ͨ����һ�εĹ��캯����ʽ����ȡָ��bmp�ĸ�ʽ�����е����ɫ��Ϣ */
	bitmap bmp(filename.c_str()); //Ϊ�˲���15-b8-bmp.h�а���ͷ�ļ����صظĳ�char*��ʽ

	hWnd = GetConsoleWindow();
	hdc_init(0, 7, 1920, 1080);
	hdc_cls();

	/* ���� hdc_base_point ���ڻ��� */
	bmp.show(start_x, start_y, angle, is_mirror, hdc_base_point);

	hdc_release();

#if 1
	/* �ȴ��س������� */
	while (_getch() != '\r')
		;
#endif
	return 0;
}
