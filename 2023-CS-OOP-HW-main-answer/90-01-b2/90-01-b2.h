/*2150792 �ƿ� ţ»��*/
#pragma once
//�ṹ��ͳ������Ķ���
struct elem_queue
{
	int x, y;
};
const int dx[] = { 1,0,-1,0 };
const int dy[] = { 0,1,0,-1 };//����BFS�㷨������Ԫ�ص�˳�򣬼�Ϊ���ҡ��¡�����
//90-01-b2�Ĳ˵���ʾ��Ϣ������
const char* const menu_infor_90_01_b2[] = {
	"1.�ڲ����飬������ɳ�ʼ5����",
	"2.�ڲ����飬�������60%����Ѱ���ƶ�·��",
	"3.�ڲ����飬��������Ϸ",
	"4.����n*n�Ŀ�ܣ��޷ָ��ߣ��������ʾ5����",
	"5.����n*n�Ŀ�ܣ��зָ��ߣ��������ʾ5����",
	"6.n*n�Ŀ�ܣ�60%����֧����꣬���һ���ƶ�",
	"7.cmdͼ�ν�����������Ϸ",
	"0.�˳�"
};
const char total_choice_90_01_b2[] = { '1','2','3','4','5','6','7','0' };
const int infor_num_90_01_b2 = 8;

//�ڲ����鷽ʽʵ�ֺ���

//����һ��ִ�к���
void fun_1(char choice);
//���ܶ���ִ�к���
void fun_2(char choice);
//��������ִ�к���
void fun_3(char choice);
//�����ƶ��������ʼ��Ŀ������
int inputdata_move(int line, int col, char* sta_line, char* sta_col, char* des_line, char* des_col, int a[9][9]);
//��ӡ�ڲ�����Ĳ�ɫ��
void print_game_array(int a[9][9], int line, int col, char choice, int b[3], elem_queue back_path[100]);


//cmd���淽ʽʵ�ֺ���

//�����ĵ�ִ�к���
void fun_4(char choice);
//�������ִ�к���
void fun_5(char choice);
//��������ִ�к���
void fun_6(char choice);
//�����ߵ�ִ�к���
void fun_7(char choice);
//cmd����������Ķ�̬����
void del_ball_dynamic(elem_queue delete_locate[100], int number);
//cmd���滭���
void print_gird(int line, int col, char choice, int sta_col);
//cmd�����ӡһ����ɫ����
void print_ball(int color, int des_line, int des_col, char choice);
//cmd����ı�cmd���ڵĴ�С������
void change_typeface_cmd(int set_lines, int set_cols, char choice);
//cmd�������Ķ�̬�ƶ�
int move_ball_dynamic(int line, char sta_line, char sta_col, char des_line, char des_col, elem_queue back_path[100], int a[9][9], char choice);
//cmd�����������
int mouse_operate(int line, int col, char* sta_line, char* sta_col, char* des_line, char* des_col, int a[9][9]);


//��cmd�����鷽ʽ���õĺ���

//�����к���
void inputdata_linecol(int* line, int* col);
//����س�����
void huiche_conti();
//�����Ϸ�Ƿ����������������
int check_game_over(int a[9][9], int line, int col);
//�жϲ����ܷ�����
int check_ball_delete(int a[9][9], int line, int col, int* color_ball, elem_queue delete_locate[100] = { 0 });
//���ڲ���������Ӳ����ʼ�Լ�����ÿ�μ�������
int append_game_array(char choice, int a[9][9], int line, int col, int b[], int flag_first);
//���ݲ����ƶ�����ʼ��Ŀ�����꣬�ı��ڲ������ֵ
void move_game_array(char choice, int a[9][9], char sta_line, char sta_col, char des_line, char des_col);
//Ѱ���ƶ������·��
int search_game_road(char choice, int a[9][9], elem_queue back_path[100], int line, int col, char sta_line, char sta_col, char des_line, char des_col);
//���ƶ������·����¼��������
int get_path(int x, int y, elem_queue a[9][9], char sta_col, char sta_line, elem_queue b[100]);
