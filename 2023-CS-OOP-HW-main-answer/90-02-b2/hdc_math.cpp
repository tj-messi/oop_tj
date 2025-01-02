/* 2150792 �ƿ� ţ»�� */
#include "../include/cmd_hdc_tools.h"
#include <iostream>
#include <Windows.h>
#include <cmath>
using namespace std;

static const double PI = 3.14159;
//�Ƕ�ת����
static double A_To_R(const double angle)
{
	return angle * PI / 180;
}

/*
���ƺ�������
a:���߿�ȣ�b:���߳���
centerX:���ĵ�x���꣬centerY:���ĵ�y����
thickness:���߿�ȣ�RGB_value:������ɫ
*/
static void drawbutterfly(const int a, const int b, const int centerX, const int centerY,const int thickness, const int RGB_value)
{
	int tn = thickness;
	if (tn < 1)
		tn = 1;		//��������
	int oldx = INT_MAX, oldy = INT_MAX;
	for (double angle = 0; angle <= 360; angle += 0.01)
	{
		double temp = (exp(cos(A_To_R(angle))) - 2 * cos(A_To_R(4 * angle)) - pow(sin(A_To_R(angle / 12)), 5));
		int x = centerX + int(a * sin(A_To_R(angle)) * temp);
		int y = centerY - int(b * cos(A_To_R(angle)) * temp);
		if (x != oldx || y != oldy)
		{
			hdc_point(x, y, tn, RGB_value);
			oldy = y;
			oldx = x;
		}
	}
}

void hdc_draw_Mathematical_curve_2150792()
{
	//���뺯����ִ�еĵ�һ���������� hdc_cls();
	hdc_cls();
	hdc_init(7, 0, 800, 800);

	drawbutterfly(100, 100, 400, 450, 12, RGB(64, 0, 128));
	drawbutterfly( 90,  90, 400, 450, 10, RGB(128, 0, 128));
	drawbutterfly( 80,  80, 400, 450,  8, RGB(0, 0, 255));
	drawbutterfly( 70,  70, 400, 450,  6, RGB(0, 128, 192));
	drawbutterfly( 60,  60, 400, 450,  6, RGB(128, 128, 192));
	drawbutterfly( 50,  50, 400, 450,  6, RGB(128, 128, 192));
	drawbutterfly( 40,  40, 400, 450,  6, RGB(255, 128, 255));

	drawbutterfly( 70, 120, 400, 450,  6, RGB(0, 255, 0));
	drawbutterfly(120,  70, 400, 450,  6, RGB(128, 64, 64));
	drawbutterfly(130,  60, 400, 450,  4, RGB(0, 128, 0));
	drawbutterfly( 60, 130, 400, 450,  4, RGB(128, 255, 128));
}
