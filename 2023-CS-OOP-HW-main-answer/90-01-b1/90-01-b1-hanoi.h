/* �ƿ� 2150792 ţ»�� */
#pragma once
//90-01-b1�˵���ʾ��Ϣ
const char* const menu_infor_90_01_b1[] = {
	"1.������","2.������(������¼)","3.�ڲ�������ʾ(����)",
	"4.�ڲ�������ʾ(����+����)","5.ͼ�ν�-Ԥ��-������Բ��","6.ͼ�ν�-Ԥ��-����ʼ���ϻ�n������",
	"7.ͼ�ν�-Ԥ��-��һ���ƶ�","8.ͼ�ν�-�Զ��ƶ��汾","9.ͼ�ν�-��Ϸ��","0.�˳�" };
const char total_choice_90_01_b1[] = { '1','2','3','4','5','6','7','8','9','0' };
const int infor_num_90_01_b1 = 10;
/*����������*/
const int START_Y = 12;
const int START_X = 9;
const int A_locate_X = 11;
const int B_locate_X = 21;
const int C_locate_X = 31;
const int A_locate_X_color = 13;
const int B_locate_X_color = 46;
const int C_locate_X_color = 79;
//���ܺ���
//���س������ĺ���
void huiche_conti();
//ʵ�ֺ�ŵ���ڲ������ƶ��ĺ���
void move_hanoi(char src, char dst);
//����ŵ�����������ʼ���ݴ��������еĺ���
void store_chushi(int n, char src, char dst);
//����ŵ������������յĺ���
void clear_array();
//���������ʱת��Ϊ��Ӧ��Sleep()�����ĺ���
int change_yanshi_ms();
//����Ҫ�ĺ�ŵ���ݹ麯��
void hanoi(int n, char src, char tmp, char dst, char choice);
//��������ʼ����Ŀ��������ʱ�����뺯��
void cin_hanoi(char* sta, char* tmp, char* des, int* n, int select);
//��Ӧ�ھ�����ʼ����Ŀ���������뺯��
int cin_exe_9(char* sta, char* des);
//�ݹ麯���ڸ���ʵ�ֹ��ܵ������������ĺ���
void select_hanoi(int n, char src, char dst, char choice);

//main����ֱ�ӵ��õĶ�Ӧ�����ܵ�ִ�к���
void exe_1(int n, char src, char tmp, char dst, char choice);
void exe_2(int n, char src, char tmp, char dst, char choice);
void exe_3(int n, char src, char tmp, char dst, char choice);
void exe_4(int n, char src, char tmp, char dst, char choice);
void exe_5();
void exe_6(int n, char src, char tmp, char dst, char choice);
void exe_7(int n, char src, char tmp, char dst, char choice);
void exe_8(int n, char src, char tmp, char dst, char choice);
void exe_9(int n, char src, char tmp, char dst, char choice);

//�����Ǵ�ӡ����
// 
//����һ��ӡ�ĺ���
void print_1(int n, char src, char dst);
//���ܶ���Ӧ�Ĵ�ӡ����
void print_2(int n, char src, char dst);
//��ӡ��������ĺ���
void print_3_4_8_hengxiang(int n, char src, char dst, int select_chushi, int locate);
//��ӡ��������ĺ���
void print_4_8_zongxiang(int n, char src, char dst, int select_chushi, int locate);
//��ӡ�������ӵĺ���
void print_5();
//����Ӧ���Ӵ�ӡ�ڳ�ʼ���ϵĺ���
void print_6(int n, char src, char tmp, char dst);
//8��9�������ƶ����ӵĺ���
void move_color(int n, char src, char dst);


/* ------------------------------------------------------------------------------------------------------

	 ���ļ����ܣ�
	1��Ϊ�˱�֤ hanoi_main.cpp/hanoi_menu.cpp/hanoi_multiple_solutions.cpp ���໥���ʺ����ĺ�������
	2��һ�����ϵ�cpp���õ��ĺ궨�壨#define����ȫ��ֻ����const����������������
	3�����Բο� cmd_console_tools.h ��д���������Ķ�����ᣩ
   ------------------------------------------------------------------------------------------------------ */

