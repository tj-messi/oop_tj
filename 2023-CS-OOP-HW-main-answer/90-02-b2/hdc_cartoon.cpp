/* 2150792 �ƿ� ţ»�� */
#include "../include/cmd_hdc_tools.h"
#include <Windows.h>
#include <cmath>
#define BLACK RGB(0, 0, 2)         //��
#define GRAY RGB(137, 135, 136)    //�ۿ�����
#define WHITE RGB(250, 247, 248)   //��
#define NOSE RGB(94, 61, 2)        //��������
#define FACE_C1 RGB(254, 232, 113)  //�ϰ벿������
#define FACE_C2 RGB(248, 200, 58)  //�ϰ벿�ֻ���
#define FACE_C3 RGB(251, 250, 249) //�°벿�ְ�
#define HEAD_ARC RGB(225, 144, 52)

static void hdc_draw_eyes(const int base_x, const int base_y)
{
	/*======�������ϵİ�ɫ����=======*/
	hdc_ellipse(base_x - 185, base_y - 90, 79, 50, 0, true, 1, FACE_C3);
	hdc_ellipse(base_x + 72, base_y - 90, 92, 50, 0, true, 1, FACE_C3);

	/*======���۵�����ۿ�======*/
	hdc_sector(base_x - 250, base_y - 70, 37, 180, 360, true, 1, WHITE);//���������������ɫ
	hdc_arc(base_x - 250, base_y - 70, 37, 180, 360, 8, GRAY);//�������������ɫ�߿�

	hdc_rectangle(base_x - 250, base_y - 103, 112, 60, 0, true, 8, WHITE);//���۾�������ɫ

	hdc_line(base_x - 251, base_y - 107, base_x - 123, base_y - 107, 8, GRAY);//�������ۿ���
	hdc_line(base_x - 251, base_y - 34, base_x - 120, base_y - 34, 8, GRAY);//�������ۿ���

	hdc_arc(base_x - 121, base_y - 70, 37, 0, 180, 8, GRAY);//�����Ҳ�������ɫ�߿�

	/*======���۵�����ۿ��������Դ��Գ���======*/
	hdc_sector(base_x - 5, base_y - 70, 39, 180, 360, true, 1, WHITE);//���������������ɫ
	hdc_arc(base_x - 5, base_y - 70, 39, 180, 360, 8, GRAY);//�������������ɫ�߿�

	hdc_rectangle(base_x - 2, base_y - 103, 135, 64, 0, true, 8, WHITE);//���۾�������ɫ

	hdc_line(base_x - 5, base_y - 109, base_x + 150, base_y - 109, 8, GRAY);//�������ۿ���
	hdc_line(base_x - 5, base_y - 31, base_x + 150, base_y - 31, 8, GRAY);//�������ۿ���

	hdc_arc(base_x + 144, base_y - 70, 39, 0, 180, 8, GRAY);//�����Ҳ�������ɫ�߿�

	/*======������������======*/
	hdc_circle(base_x - 121, base_y - 70, 33, true, 3, BLACK);//����
	hdc_circle(base_x + 145, base_y - 70, 34, true, 3, BLACK);//����
}

static void hdc_draw_left_ear(const int base_x, const int base_y)
{
	hdc_line(base_x - 174, base_y - 263, base_x - 174, base_y - 254, 5, FACE_C2);//�޲�ȱʧ���ص�
	/*======�������======*/
	hdc_triangle(base_x - 182, base_y - 190, base_x - 82, base_y - 230, base_x - 165, base_y - 315, true, 3, FACE_C2);//�������������ɫ
	hdc_arc(base_x + 220, base_y - 207, 401, 268, 285, 9, HEAD_ARC);
	hdc_point(base_x - 163, base_y - 311, 10, HEAD_ARC);
	hdc_arc(base_x - 401, base_y + 7, 399, 37, 55, 9, HEAD_ARC);
	//hdc_arc(base_x + 125, base_y - 200, 300, 270, 285, 7, RGB(215, 147, 86));//������С���Ȼ���
	//hdc_arc(base_x + 95, base_y - 130, 300, 300, 303, 7, RGB(215, 147, 86));//����Ϸ������Ȼ���
	//hdc_arc(base_x - 399, base_y - 12, 370, 41, 55, 7, RGB(215, 147, 86));//����Ҳ�С���Ȼ���
}

static void hdc_draw_right_ear(const int base_x, const int base_y)
{
	//Ϊ��Ӧ�����Ĺ��߼������е��޲�
	hdc_point(base_x + 224, base_y - 320, 14, FACE_C2);//�ϲ�ȱ���ص�

	/*======���Ҷ����ⲿ======*/
	hdc_triangle(base_x + 92, base_y - 220, base_x + 240, base_y - 150, base_x + 215, base_y - 320, true, 4, FACE_C2);// �Ҷ�������������ɫ
	hdc_line(base_x + 220, base_y - 316, base_x + 235, base_y - 210, 16, FACE_C2);
	hdc_line(base_x + 239, base_y - 220, base_x + 238, base_y - 190, 12, FACE_C2);
	hdc_arc(base_x + 439, base_y + 39, 426, 308, 330, 9, HEAD_ARC);
	hdc_point(base_x + 100, base_y - 226, 10, HEAD_ARC);
	hdc_arc(base_x - 240, base_y - 213, 482, 76, 98, 9, HEAD_ARC);

	/*======���Ҷ����ڲ�======*/
	hdc_triangle(base_x + 140, base_y - 210, base_x + 205, base_y - 172, base_x + 200, base_y - 265, true, 1, RGB(253, 168, 20));
	hdc_line(base_x + 205, base_y - 172, base_x + 200, base_y - 265, 5, RGB(253, 168, 20));
	hdc_line(base_x + 195, base_y - 265, base_x + 135, base_y - 210, 9, RGB(253, 168, 20));
	hdc_line(base_x + 210, base_y - 172, base_x + 205, base_y - 265, 10, RGB(253, 168, 20));
	hdc_arc(base_x + 48, base_y + 29, 252, 20, 40, 7, HEAD_ARC);
	hdc_arc(base_x + 308, base_y - 90, 211, 304, 330, 7, HEAD_ARC);
	hdc_arc(base_x + 25, base_y - 210, 190, 71, 104, 7, HEAD_ARC);
}

static void hdc_draw_nose(const int base_x, const int base_y)
{
	//����������������
	hdc_triangle(base_x - 140, base_y + 2, base_x - 70, base_y + 2, base_x - 110, base_y + 43, true, 2, NOSE);
	//�����������ϱ�
	hdc_line(base_x - 142, base_y, base_x - 68, base_y, 5, NOSE);
	//�������������
	hdc_sector(base_x - 116, base_y + 5, 36, 180, 270, true, 5, NOSE);
	hdc_sector(base_x - 136, base_y + 15, 17, 245, 340, true, 5, NOSE);
	//�����������ұ�
	hdc_sector(base_x - 85, base_y + 11, 18, 50, 120, true, 5, NOSE);
	hdc_sector(base_x - 80, base_y + 17, 20, 18, 145, true, 1, NOSE);
	hdc_sector(base_x - 100, base_y, 45, 120, 170, true, 1, NOSE);
	hdc_ellipse(base_x - 110, base_y + 23, 40, 16, 0, true, 5, NOSE);

	//�����������±�
	hdc_sector(base_x - 125, base_y + 23, 24, 190, 260, true, 1, NOSE);
	hdc_ellipse(base_x - 110, base_y + 30, 30, 18, 0, true, 5, NOSE);
}

static void hdc_draw_mouse(const int base_x, const int base_y)
{
	/*======����ϰ벿��======*/
	hdc_rectangle(base_x - 122, base_y + 25, 20, 70, 0, true, 5, NOSE);

	/*======����°벿��======*/
	//����ұ�
	hdc_arc(base_x - 55, base_y + 55, 65, 179, 246, 22, NOSE);
	hdc_arc(base_x - 48, base_y + 33, 85, 136, 172, 22, NOSE);
	hdc_arc(base_x - 55, base_y + 63, 57, 165, 190, 22, NOSE);
	//������
	hdc_arc(base_x - 163, base_y + 72, 50, 100, 140, 18, NOSE);
	hdc_arc(base_x - 144, base_y + 102, 10, 120, 240, 9, NOSE);
	hdc_arc(base_x - 144, base_y + 102, 17, 120, 240, 12, NOSE);
	hdc_arc(base_x - 120, base_y + 72, 54, 220, 240, 18, NOSE);
	//Ϊ��Ӧ�����Ĺ��߼������е��޲�
	hdc_point(base_x - 167, base_y + 100, 15, NOSE);//���С����
	hdc_point(base_x - 140, base_y + 98, 18, WHITE);
	hdc_line(base_x - 159, base_y + 116, base_x - 172, base_y + 104, 5, NOSE);//���С����
}

static void hdc_draw_head(const int base_x, const int base_y)
{
	/*======���°벿��======*/
	//����Բģ���²�������
	hdc_ellipse(base_x - 15, base_y + 87, 262, 162, 0, true, 1, FACE_C3);
	hdc_ellipse(base_x - 16, base_y + 87, 262, 162, 0, false, 9, HEAD_ARC);
	//С��������²����Ҳ�ȱʧλ��
	hdc_sector(base_x + 35, base_y + 2, 240, 93, 120, true, 1, FACE_C3);
	hdc_arc(base_x + 35, base_y + 2, 240, 93, 121, 9, HEAD_ARC);

	/*======���ϰ벿��======*/
	//�ϲ໡��
	hdc_ellipse(base_x - 55, base_y - 90, 216, 138, 0, false, 7, HEAD_ARC);
	hdc_ellipse(base_x - 26, base_y - 100, 218, 138, 1, false, 7, HEAD_ARC);
	hdc_ellipse(base_x + 35, base_y - 100, 218, 138, 12, false, 7, HEAD_ARC);
	//�ϲ��ɫ���
	hdc_ellipse(base_x - 55, base_y - 90, 213, 134, 0, true, 1, FACE_C2);
	hdc_ellipse(base_x - 26, base_y - 100, 213, 134, 1, true, 1, FACE_C2);
	hdc_ellipse(base_x + 35, base_y - 100, 213, 134, 12, true, 1, FACE_C2);

	//��໡��
	hdc_sector(base_x + 20, base_y + 40, 300, 270, 290, true, 2, FACE_C2);
	hdc_arc(base_x + 18, base_y + 40, 300, 266, 290, 9, HEAD_ARC);
	hdc_arc(base_x + 20, base_y + 40, 300, 263, 266, 12, HEAD_ARC);

	//�Ҳಿ��
	hdc_sector(base_x + 235, base_y - 22, 61, 145, 165, true, 7, FACE_C2);
	hdc_ellipse(base_x + 158, base_y - 3, 107, 45, 15, true, 8, FACE_C2);
	//������
	hdc_sector(base_x + 142, base_y - 7, 135, 87, 103, true, 1, FACE_C2);
	hdc_arc(base_x + 144, base_y - 7, 135, 87, 103, 7, HEAD_ARC);
	//������
	hdc_sector(base_x + 39, base_y - 13, 240, 65, 92, true, 1, FACE_C2);
	hdc_arc(base_x + 39, base_y - 13, 240, 65, 92, 7, HEAD_ARC);
	//������
	hdc_sector(base_x + 92, base_y - 51, 177, 2, 70, true, 1, FACE_C2);
	hdc_arc(base_x + 92, base_y - 51, 177, 2, 70, 7, HEAD_ARC);
	//������
	hdc_sector(base_x + 25, base_y - 60, 178, 1, 19, true, 1, FACE_C2);
	hdc_arc(base_x + 25, base_y - 60, 178, 1, 19, 7, HEAD_ARC);
	//���ȱʧ����
	hdc_arc(base_x + 50, base_y - 54, 183, 7, 17, 5, HEAD_ARC);

	//������������ɫ���
	hdc_ellipse(base_x - 40, base_y - 70, 230, 137, 0, true, 3, FACE_C1);

	/*======���°벿�����ϰ벿�ֵĽ��紦======*/
	hdc_ellipse(base_x - 95, base_y + 45, 180, 36, 0, true, 5, FACE_C3);
	hdc_ellipse(base_x + 38, base_y + 76, 200, 54, 9, true, 7, FACE_C3);
	hdc_rectangle(base_x - 276, base_y + 43, 15, 32, 0, true, 1, FACE_C3);

	/*======�޲�һЩ���ص��ͻ��======*/
	hdc_point(base_x - 270, base_y + 81, 12, FACE_C3);//��໡��ƴ�Ӵ���ɫ���ص�ͻ��

	//Ϊ��Ӧ�����Ĺ��߼������е��޲�
	hdc_line(base_x - 282, base_y + 50, base_x - 279, base_y + 85, 8, HEAD_ARC);//�޲����δƴ��
	hdc_point(base_x - 14, base_y + 249, 10, HEAD_ARC);//�²໡�����ص�ȱʧ

}

void hdc_draw_cartoon_2150792(const int base_x, const int base_y)
{
	//���뺯����ִ�еĵ�һ���������� hdc_cls();
	hdc_cls();
	hdc_init(7, 0, 800, 750);
	//��ʼ������ɫ
	hdc_rectangle(0, 0, 800, 750, 0, true, 1, RGB(237, 237, 237));

	hdc_draw_left_ear(base_x, base_y);
	hdc_draw_head(base_x, base_y);
	hdc_draw_eyes(base_x, base_y);
	hdc_draw_right_ear(base_x, base_y);
	hdc_draw_nose(base_x, base_y);
	hdc_draw_mouse(base_x, base_y);
}