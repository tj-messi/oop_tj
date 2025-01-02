//2150244 ��06 ������
#include <Windows.h>
#include <cmath>
#include "../include/cmd_hdc_tools.h"

#define HAT_COLOR   RGB(255,151,0)		//��ñ����ɫ
#define HAT_RED     RGB(170,14,2)		//��ñ�ϵĺ�ɫ
#define WHITE_COLOR RGB(255,255,255)	//����������Ҫ�õ��İ�ɫ
#define PI          3.1415926			//Բ����

//�Ƕ�ת����
static inline double hdc_inner_deg2rad(const double angle)
{
	return angle * PI / 180;
}

//������������ͷ
static void hdc_cartoon_inner_bone(const int base_x, const int base_y)
{
	const int reg_len = 283;	//x��y����ı仯��
	const int reg_wid = 900;	//ʵ�ʳ���
	const int reg_high = 94;	//ʵ�ʿ��
	const int radius_s = 60;	//��ͷ��Բ�뾶

	//���Ͻǵ����½ǵĹ�ͷ
	hdc_rectangle(base_x - reg_len, base_y - reg_len - (int)(reg_high / sqrt(2)), reg_wid, reg_high, 45, true, 5, WHITE_COLOR);		//��ͷ������
	//��ͨ���ĸ�Բģ��һ�¹�ͷ
	hdc_circle(base_x - reg_len, base_y - reg_len - reg_high/2, radius_s, true, 5, WHITE_COLOR);
	hdc_circle(base_x - reg_len - reg_high/2, base_y - reg_len, radius_s, true, 5, WHITE_COLOR);
	hdc_circle(base_x + reg_len, base_y + reg_len + reg_high / 2, radius_s, true, 5, WHITE_COLOR);
	hdc_circle(base_x + reg_len + reg_high / 2, base_y + reg_len, radius_s, true, 5, WHITE_COLOR);

	//���Ͻǵ����½ǵĹ�ͷ
	hdc_rectangle(base_x + reg_len + (int)(reg_high / sqrt(2)), base_y - reg_len, reg_wid, reg_high, 135, true, 5, WHITE_COLOR);	//��ͷ������
	//��ͨ������Բģ��һ�¹�ͷ
	hdc_circle(base_x - reg_len, base_y + reg_len + reg_high / 2, radius_s, true, 5, WHITE_COLOR);
	hdc_circle(base_x - reg_len - reg_high / 2, base_y + reg_len, radius_s, true, 5, WHITE_COLOR);
	hdc_circle(base_x + reg_len, base_y - reg_len - reg_high / 2, radius_s, true, 5, WHITE_COLOR);
	hdc_circle(base_x + reg_len + reg_high / 2, base_y - reg_len, radius_s, true, 5, WHITE_COLOR);

}

//��·�ɵĲ�ñ
static void hdc_cartoon_inner_hat(const int base_x, const int base_y)
{
	const int hat_a = 330;				//��ñ��Բ�ĳ�����
	const int hat_b = 30;				//��ñ��Բ�Ķ̰���
	const int red_b = 30;				//��ñ��Բ�Ķ̰���
	const int r_head = 250;				//ͷ�Ĵ�С

	hdc_sector (base_x, base_y, r_head, -90, 90, true, 5, HAT_COLOR);				//�ϰ벿��
	hdc_arc    (base_x, base_y, r_head, -90, 90, 10, COLOR_BLACK);					//�ϰ벿������
	hdc_ellipse(base_x, base_y - hat_b, r_head, red_b, 0, true, 5, HAT_RED);		//��ɫ����
	hdc_ellipse(base_x, base_y - hat_b, r_head, red_b, 0, false, 9, COLOR_BLACK);	//��ɫ��������
	hdc_ellipse(base_x, base_y, hat_a, hat_b, 0, true, 5, HAT_COLOR);				//��Բ����
	hdc_ellipse(base_x, base_y, hat_a, hat_b, 0, false, 9, COLOR_BLACK);			//��Բ��������
	hdc_ellipse(base_x, base_y, r_head, hat_b / 2, 0, true, 5, WHITE_COLOR);		//���ಿ�ָֻ���ɫ
	hdc_ellipse(base_x, base_y, r_head, hat_b / 2, 0, false, 9, COLOR_BLACK);		//���ಿ������
	hdc_sector (base_x, base_y, r_head, 90, 270, true, 5, WHITE_COLOR);				//�°벿��
	hdc_arc    (base_x, base_y, r_head, 90, 270, 9, COLOR_BLACK);					//�°벿������
}

//��ͷ��
static void hdc_cartoon_inner_head(const int base_x, const int base_y)
{
	const int r_head  = 250;			//ͷ�Ĵ�С
	const int y_mouth = 280;			//���������ƫ����
	const int r_mouth = 100;			//�첿Բ�Ĵ�С
	const int y_nose  = 167;			//����������ƫ����
	const int r_nose  = 20;				//���Ӱ뾶
	const int x_eyes  = 110;			//�۾�������ƫ����
	const int y_eyes  = 90;				//�۾�������ƫ����
	const int r_eyes  = 80;				//�۾��뾶
	const int d_teeth = 10;				//���������ת�Ƕ�
	const int y1 = 133;					//���ݵ�һ�λ�Բ��ƫ����
	const int r1 = 150;					//���ݵ�һ�λ��뾶
	const int y2 = 200;					//���ݵڶ��λ�Բ��ƫ����
	const int r2 = 130;					//���ݵڶ��λ��뾶
	
	//�Ȼ��첿��Բ���Ⱥ������ǵ�
	hdc_circle(base_x, base_y + y_mouth, r_mouth, true , 5, WHITE_COLOR);	//��Ȧ
	
	//����ñ
	hdc_cartoon_inner_hat(base_x, base_y);

	//�۾�
	hdc_circle(base_x - x_eyes, base_y + y_eyes, r_eyes, true, 9, COLOR_BLACK);
	hdc_circle(base_x + x_eyes, base_y + y_eyes, r_eyes, true, 9, COLOR_BLACK);

	//����
	hdc_circle(base_x, base_y + y_nose, r_nose, true, 9, COLOR_BLACK);

	//�������ϸ��
	hdc_arc(base_x, base_y + y1, r1, 135, 225, 9, COLOR_BLACK);
	hdc_arc(base_x, base_y + y2, r2, 105, 255, 9, COLOR_BLACK);
	hdc_line(base_x, base_y + r_head, base_x, base_y + y2 + r2, 9, COLOR_BLACK);
	hdc_line(base_x - (int)(r_head * sin(hdc_inner_deg2rad(d_teeth))), base_y + (int)(r_head * cos(hdc_inner_deg2rad(d_teeth))), base_x - (int)(r2 * sin(hdc_inner_deg2rad(3 * d_teeth))), base_y + y2 + (int)(r2 * cos(hdc_inner_deg2rad(3 * d_teeth))), 9, COLOR_BLACK);
	hdc_line(base_x + (int)(r_head * sin(hdc_inner_deg2rad(d_teeth))), base_y + (int)(r_head * cos(hdc_inner_deg2rad(d_teeth))), base_x + (int)(r2 * sin(hdc_inner_deg2rad(3 * d_teeth))), base_y + y2 + (int)(r2 * cos(hdc_inner_deg2rad(3 * d_teeth))), 9, COLOR_BLACK);
}

void hdc_draw_cartoon_2150244(const int base_x, const int base_y)
{	
	//���뺯����ִ�еĵ�һ���������� hdc_cls();
	hdc_cls();

	//��ʼ���±�������Ҫ���Ǻ�ɫ����
	hdc_init(0, 7, 800, 800);

	//������������ͷ
	hdc_cartoon_inner_bone(base_x, base_y);

	//ͷ���Ͳ�ñ
	hdc_cartoon_inner_head(base_x, base_y);
}
