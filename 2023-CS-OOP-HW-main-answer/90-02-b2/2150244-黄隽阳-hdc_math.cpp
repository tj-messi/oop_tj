//2150244 ��06 ������
#include "../include/cmd_hdc_tools.h"
#include <iostream>
#include <cmath>
using namespace std;

//��ʼλ�õĺ�������
static const int point_x = 400;
static const int point_y = 500;

//��ʼ�ͽ����Ƕ�
static const int start_angle = -45;
static const int end_angle = 45;

//��ɫ
static const int color[2][3] = { { 0x00000000 ,0x00000000, 0x00CCCCCC },{ 0x00C0C0C0 ,0x00C0C0C0, 0x00CCCCCC } };

//�ź������
static const int width = 30;
static const int wid_all = 270;

//����������WiFi�ź�
static const int total_num = 3;	

//������Ҫ������������������Ƚ�С��ϣ���ܿ��õ���
void hdc_draw_Mathematical_curve_2150244()
{
	//���뺯����ִ�еĵ�һ���������� hdc_cls();
	hdc_cls();

	//������ʾ
	cout << "WiFi ͼ�꣬������ WiFi �źŸ���������3��������1-3��Ĭ��3�񣩣� ";
	int num;		//ʵ����ʾ�źŸ������ɼ�������
	cin >> num;
	if (cin.fail() || num < 1 || num > total_num)	//�������򳬷�Χֱ��������
		num = total_num;
	cout << "WiFi ͼ�� " << num << " ��";

	//��ͼ����
	for (int i = 0; i < 3 * total_num - 1; i++) {
		if (i / 3 >= (total_num - num))	//���ź�
			hdc_sector(point_x, point_y, wid_all - width * i, start_angle, end_angle, true, 5, color[0][i % 3]);
		else							//���ź�
			hdc_sector(point_x, point_y, wid_all - width * i, start_angle, end_angle, true, 5, color[1][i % 3]);
	}
}