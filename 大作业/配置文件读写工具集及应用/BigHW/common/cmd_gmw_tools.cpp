/*2351114 �쿡�� ������*/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <climits>
#include <conio.h>
#include <iomanip>
#include <windows.h>
#include "../include/cmd_console_tools.h"
#include "../include/cmd_gmw_tools.h"
using namespace std;

/* --------------------------------------------------
		�˴����Ը�����Ҫ�ľ�̬ȫ�ֱ������������٣����û�У�����̬ȫ��ֻ������/�궨�壨�������ޣ���
   -------------------------------------------------- */
//���еĿ�ܶ����ó���һ��CGI����������������gmw.h�ļ���

/* --------------------------------------------------
		�˴����Ը�����Ҫ���ڲ��������ߺ���
		1�����������ޣ�����Ϊ gmw_inner_* 
		2����������
		3��������static������ȷ��ֻ�ڱ�Դ�ļ���ʹ��
   -------------------------------------------------- */
//����һ��gmw_inner_renew()��ʵʱ�������в���
void gmw_inner_renew(CONSOLE_GRAPHICS_INFO* const pCGI)
{
	pCGI->start_x = pCGI->extern_left_cols;
	pCGI->start_y = pCGI->extern_up_lines + pCGI->top_status_line;
	//����������
	pCGI->lines = pCGI->extern_up_lines + pCGI->extern_down_lines + pCGI->CFI.bhigh +
		pCGI->SLI.is_top_status_line + pCGI->SLI.is_lower_status_line +
		pCGI->draw_frame_with_col_no + 4;  // 4 �����ڶ����UIԤ�� flag
	pCGI->cols = pCGI->extern_left_cols + pCGI->extern_right_cols + pCGI->CFI.bwidth +
		pCGI->draw_frame_with_row_no * 2 + 1;  // �����������Ҷ�������ͱ߿�

	//����ܸ߿�
	pCGI->CFI.bhigh = pCGI->CFI.block_high * pCGI->row_num +
		pCGI->CFI.separator * (pCGI->row_num - 1) + 2;
	pCGI->CFI.bwidth = pCGI->CFI.block_width * pCGI->col_num +
		pCGI->CFI.separator * 2 * (pCGI->col_num - 1) + 4;
	//���²���״̬��ʼλ��
	pCGI->SLI.top_start_x = pCGI->extern_left_cols;
	pCGI->SLI.top_start_y = pCGI->extern_up_lines;
	pCGI->SLI.lower_start_x = pCGI->extern_left_cols;
	pCGI->SLI.lower_start_y = pCGI->start_y + pCGI->CFI.bhigh + pCGI->draw_frame_with_col_no;
}
/* ----------------------------------------------- 
		ʵ����������ĺ���������������׼����
   ----------------------------------------------- */
/***************************************************************************
  �������ƣ�
  ��    �ܣ�������Ϸ����ܵ�������
  ���������CONSOLE_GRAPHICS_INFO *const pCGI	������ṹָ��
			const int row						������(������Ϊ0���������ޣ���Ϊ��֤��ȷ��)
			const int col						������(������Ϊ0���������ޣ���Ϊ��֤��ȷ��)
  �� �� ֵ��
  ˵    ����1��ָ��������Ϸ�ľ������������ֵ
            2�����еı仯�ᵼ��CONSOLE_GRAPHICS_INFO�ṹ����������Աֵ�ı仯��Ҫ����
***************************************************************************/
int gmw_set_rowcol(CONSOLE_GRAPHICS_INFO *const pCGI, const int row, const int col)
{
	/* ��ֹ��δ���� gmw_init ǰ������������ */
	if (pCGI->inited != CGI_INITED)
		return -1;
	//����
	pCGI->row_num = max(0, row);
	pCGI->col_num = max(0, col);
	//�߿�
	pCGI->CFI.bhigh = pCGI->CFI.block_high * pCGI->row_num + pCGI->row_num  * pCGI->CFI.separator + 2- pCGI->CFI.separator;
	pCGI->CFI.bwidth = pCGI->CFI.block_width * pCGI->col_num + pCGI->col_num  * 2 * pCGI->CFI.separator + 4- pCGI->CFI.separator;
	//��ʾ����
	pCGI->lines = pCGI->extern_up_lines + pCGI->extern_down_lines + pCGI->CFI.bhigh + pCGI->SLI.is_top_status_line + 
		pCGI->SLI.is_lower_status_line + pCGI->draw_frame_with_col_no + 4;
	pCGI->cols = pCGI->extern_left_cols + pCGI->extern_right_cols + pCGI->CFI.bwidth + pCGI->draw_frame_with_row_no * 2 + 1;
	//���
	pCGI->SLI.lower_start_y = pCGI->extern_up_lines + pCGI->draw_frame_with_col_no + pCGI->SLI.is_top_status_line + pCGI->CFI.bhigh;
	return 0; //�˾�ɸ�����Ҫ�޸�
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ������������ڣ�����Ϸ�������������ڵ�����cmd���ڣ�����ɫ
  ���������CONSOLE_GRAPHICS_INFO *const pCGI	������ṹָ��
		   const int bg_color					��ǰ��ɫ��ȱʡCOLOR_BLACK��
		   const int fg_color					������ɫ��ȱʡCOLOR_WHITE��
		   const bool cascade					���Ƿ�����ȱʡΪtrue-������
  �� �� ֵ��
  ˵    ����1��cascade = trueʱ
				ͬ���޸���Ϸ���������ɫ
				ͬ���޸�����״̬���������ı��ı���ɫ��ǰ��ɫ����Ŀ�ı��ı���ɫ��ǰ��ɫ���䣩
			2���������ɫֵ���󼰳�ͻ����Ҫ��Ϊ��֤
				������ɫ��0-15
				    ǰ��ɫ����ɫ��ֵһ�µ����޷���������
					ǰ��ɫ������״̬����Ŀǰ��ɫ�������޷�������Ŀ��ʾ
					...
***************************************************************************/
int gmw_set_color(CONSOLE_GRAPHICS_INFO *const pCGI, const int bgcolor, const int fgcolor, const bool cascade)
{
	/* ��ֹ��δ���� gmw_init ǰ������������ */
	if (pCGI->inited != CGI_INITED)
		return -1;
	if (cascade)
	{
		//��ɫ
		pCGI->area_bgcolor = bgcolor;
		pCGI->area_fgcolor = fgcolor;

		//ͬ���޸���Ϸ���������ɫ
		//ͬ���޸�����״̬���������ı��ı���ɫ��ǰ��ɫ����Ŀ�ı��ı���ɫ��ǰ��ɫ���䣩
		pCGI->CFI.bgcolor = bgcolor;
		pCGI->CFI.fgcolor = fgcolor;

		//������Ŀ
		pCGI->SLI.top_normal_bgcolor = bgcolor;
		pCGI->SLI.top_normal_fgcolor = fgcolor;
		pCGI->SLI.top_catchy_bgcolor = bgcolor;
		pCGI->SLI.lower_normal_bgcolor = bgcolor;
		pCGI->SLI.lower_normal_fgcolor = fgcolor;
		pCGI->SLI.lower_catchy_bgcolor = bgcolor;
	}
	else
	{
		//��ɫ
		pCGI->area_bgcolor = bgcolor;
		pCGI->area_fgcolor = fgcolor;
	}
	
	return 0; //�˾�ɸ�����Ҫ�޸�
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ����ô��ڵ�����
  ���������CONSOLE_GRAPHICS_INFO *const pCGI	������ṹָ��
		   const char *fontname					���������ƣ�ֻ����"Terminal"��"������"���֣������򷵻�-1�����ı����壩
		   const int fs_high					������߶ȣ�ȱʡ������Ϊ16�������������ƣ���Ϊ��֤��
		   const int fs_width					������߶ȣ�ȱʡ������Ϊ8�������������ƣ���Ϊ��֤��
  �� �� ֵ��
  ˵    ����1����cmd_console_tools�е�setfontsize���ƣ�Ŀǰֻ֧�֡��������塱�͡������塱
            2������������������ֱ�ӷ��أ�����ԭ�������ò���
***************************************************************************/
int gmw_set_font(CONSOLE_GRAPHICS_INFO *const pCGI, const char *fontname, const int fs_high, const int fs_width)
{
	/* ��ֹ��δ���� gmw_init ǰ������������ */
	if (pCGI->inited != CGI_INITED)
		return -1;

	//����ߺͿ�
	pCGI->CFT.font_size_high = (fs_high <= 0) ? 16 : fs_high;
	pCGI->CFT.font_size_width = (fs_width <= 0) ? 8 : fs_width;

	if (strcmp(fontname, "Terminal") || strcmp(fontname, "������"))
	{
		strcpy(pCGI->CFT.font_type, fontname);
	}
	else
		return -1;

	return 0; //�˾�ɸ�����Ҫ�޸�
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�������ʱ
  ���������CONSOLE_GRAPHICS_INFO *const pCGI	������ṹָ��
		   const int type						����ʱ�����ͣ�ĿǰΪ3�֣�
		   const int delay_ms					����msΪ��λ����ʱ
			   ���߿����ʱ��0 ~ �������ޣ���Ϊ��֤��ȷ��<0����0��
			   ��ɫ�����ʱ��0 ~ �������ޣ���Ϊ��֤��ȷ��<0����0��
			   ɫ���ƶ�����ʱ��BLOCK_MOVED_DELAY_MS ~ �������ޣ���Ϊ��֤��ȷ�� <BLOCK_MOVED_DELAY_MS ���� BLOCK_MOVED_DELAY_MS��
  �� �� ֵ��
  ˵    ����
***************************************************************************/
int gmw_set_delay(CONSOLE_GRAPHICS_INFO *const pCGI, const int type, const int delay_ms)
{
	/* ��ֹ��δ���� gmw_init ǰ������������ */
	if (pCGI->inited != CGI_INITED)
		return -1;
	/*
	DELAY_OF_DRAW_FRAME		0	//����Ϸ�����ʱ��ʱ
	DELAY_OF_DRAW_BLOCK		1	//��ɫ��ʱ����ʱ
	DELAY_OF_BLOCK_MOVED	2	//ɫ���ƶ�ʱ��ʱ
	*/
	if (type==0)
	{
		pCGI->delay_of_draw_frame = max(0, delay_ms);
	}
	else if (type == 1)
	{
		pCGI->delay_of_draw_block = max(0, delay_ms);
	}
	else
	{
		pCGI->delay_of_block_moved = max(BLOCK_MOVED_DELAY_MS, delay_ms);
	}


	return 0; //�˾�ɸ�����Ҫ�޸�
}

/***************************************************************************
  �������ƣ�
  ���������������Ϸ����ܽṹ֮����Ҫ�����Ķ�������
  ��    �ܣ�CONSOLE_GRAPHICS_INFO *const pCGI	��
		   const int up_lines					���ϲ�������У�ȱʡ������Ϊ0���������ޣ���Ϊ��֤��
		   const int down_lines				���²�������У�ȱʡ������Ϊ0���������ޣ���Ϊ��֤��
		   const int left_cols					����߶�����У�ȱʡ������Ϊ0���������ޣ���Ϊ��֤��
		   const int right_cols				���ұ߶�����У�ȱʡ������Ϊ0���������ޣ���Ϊ��֤��
  �� �� ֵ��
  ˵    �����������еı仯�ᵼ��CONSOLE_GRAPHICS_INFO�ṹ����������Աֵ�ı仯��Ҫ����
***************************************************************************/
int gmw_set_ext_rowcol(CONSOLE_GRAPHICS_INFO *const pCGI, const int up_lines, const int down_lines, const int left_cols, const int right_cols)
{
	/* ��ֹ��δ���� gmw_init ǰ������������ */
	if (pCGI->inited != CGI_INITED)
		return -1;

	//�������Ҷ�����
	pCGI->extern_up_lines = max(0, up_lines);
	pCGI->extern_down_lines = max(0, down_lines);
	pCGI->extern_left_cols = max(0, left_cols);
	pCGI->extern_right_cols = max(0, right_cols);

	pCGI->start_x = pCGI->extern_left_cols;
	pCGI->start_y = pCGI->extern_up_lines + pCGI->top_status_line;
	//����������
	pCGI->lines = pCGI->extern_up_lines + pCGI->extern_down_lines + pCGI->CFI.bhigh +
		pCGI->SLI.is_top_status_line + pCGI->SLI.is_lower_status_line +
		pCGI->draw_frame_with_col_no + 4;  // 4 �����ڶ����UIԤ�� flag
	pCGI->cols = pCGI->extern_left_cols + pCGI->extern_right_cols + pCGI->CFI.bwidth +
		pCGI->draw_frame_with_row_no * 2 + 1;  // �����������Ҷ�������ͱ߿�

	//����ܸ߿�
	pCGI->CFI.bhigh = pCGI->CFI.block_high * pCGI->row_num +
		pCGI->CFI.separator * (pCGI->row_num - 1) + 2;
	pCGI->CFI.bwidth = pCGI->CFI.block_width * pCGI->col_num +
		pCGI->CFI.separator * 2 * (pCGI->col_num - 1) + 4;
	//���²���״̬��ʼλ��
	pCGI->SLI.top_start_x = pCGI->extern_left_cols;
	pCGI->SLI.top_start_y = pCGI->extern_up_lines;
	pCGI->SLI.lower_start_x = pCGI->extern_left_cols;
	pCGI->SLI.lower_start_y = pCGI->start_y + pCGI->CFI.bhigh + pCGI->draw_frame_with_col_no;

	return 0; //�˾�ɸ�����Ҫ�޸�
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ���� CONSOLE_FRAME_TYPE �ṹ�е�11�����ͣ�ȱʡ4�֣�
  ���������CONSOLE_GRAPHICS_INFO *const pCGI	������ṹָ��
			const int type						��1 - ȫ�� 2 - ȫ���� 3 - ��˫���� 4 - �ᵥ��˫
  �� �� ֵ��
  ˵    ����
***************************************************************************/
int gmw_set_frame_default_linetype(CONSOLE_GRAPHICS_INFO *const pCGI, const int type)
{
	/* ��ֹ��δ���� gmw_init ǰ������������ */
	if (pCGI->inited != CGI_INITED)
		return -1;

	bool flag=false;
	if (type == 1)
	{
		strcpy(pCGI->CFI.top_left, "�X");
		strcpy(pCGI->CFI.lower_left, "�^");
		strcpy(pCGI->CFI.top_right, "�[");
		strcpy(pCGI->CFI.lower_right, "�a");
		strcpy(pCGI->CFI.h_normal, "�T");
		strcpy(pCGI->CFI.v_normal, "�U");
		strcpy(pCGI->CFI.h_top_separator, "�j");
		strcpy(pCGI->CFI.h_lower_separator, "�m");
		strcpy(pCGI->CFI.v_left_separator, "�d");
		strcpy(pCGI->CFI.v_right_separator, "�g");
		strcpy(pCGI->CFI.mid_separator, "�p");
		flag = true;
	}
	else if (type == 2)
	{
		strcpy(pCGI->CFI.top_left, "��");
		strcpy(pCGI->CFI.lower_left, "��");
		strcpy(pCGI->CFI.top_right, "��");
		strcpy(pCGI->CFI.lower_right, "��");
		strcpy(pCGI->CFI.h_normal, "��");
		strcpy(pCGI->CFI.v_normal, "��");
		strcpy(pCGI->CFI.h_top_separator, "��");
		strcpy(pCGI->CFI.h_lower_separator, "��");
		strcpy(pCGI->CFI.v_left_separator, "��");
		strcpy(pCGI->CFI.v_right_separator, "��");
		strcpy(pCGI->CFI.mid_separator, "��");
		flag = true;
	}
	else if (type == 3)
	{
		strcpy(pCGI->CFI.top_left, "�V");
		strcpy(pCGI->CFI.lower_left, "�\");
		strcpy(pCGI->CFI.top_right, "�Y");
		strcpy(pCGI->CFI.lower_right, "�_");
		strcpy(pCGI->CFI.h_normal, "�T");
		strcpy(pCGI->CFI.v_normal, "��");
		strcpy(pCGI->CFI.h_top_separator, "�h");
		strcpy(pCGI->CFI.h_lower_separator, "�k");
		strcpy(pCGI->CFI.v_left_separator, "�b");
		strcpy(pCGI->CFI.v_right_separator, "�e");
		strcpy(pCGI->CFI.mid_separator, "�n");
		flag = true;
	}
	else
	{
		strcpy(pCGI->CFI.top_left, "�W");
		strcpy(pCGI->CFI.lower_left, "�]");
		strcpy(pCGI->CFI.top_right, "�Z");
		strcpy(pCGI->CFI.lower_right, "�`");
		strcpy(pCGI->CFI.h_normal, "��");
		strcpy(pCGI->CFI.v_normal, "�U");
		strcpy(pCGI->CFI.h_top_separator, "�i");
		strcpy(pCGI->CFI.h_lower_separator, "�l");
		strcpy(pCGI->CFI.v_left_separator, "�c");
		strcpy(pCGI->CFI.v_right_separator, "�f");
		strcpy(pCGI->CFI.mid_separator, "�o");
		flag = true;
	}
	if (!flag)
	{
		//cpy���ɹ�
		cout << "���ɹ�" << endl;
		//std::sleep(500);
	}


	return 0; //�˾�ɸ�����Ҫ�޸�
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ���� CONSOLE_FRAME_TYPE �ṹ�е�11������
  ���������CONSOLE_GRAPHICS_INFO *const pCGI	������ṹָ��
			const char *...						����11�֣������.h���˴���
  �� �� ֵ��
  ˵    ����Լ��Ϊһ�������Ʊ��������ʹ���������ݣ���Ϊ��֤2�ֽ�
			1������2�ֽ���ֻȡǰ2�ֽ�
			2�������NULL���������ո����
			3�������1�ֽڣ���һ���ո������˶�������ʾ�ң������
***************************************************************************/
int gmw_set_frame_linetype(CONSOLE_GRAPHICS_INFO *const pCGI, const char *top_left, const char *lower_left, const char *top_right,
	const char *lower_right, const char *h_normal, const char *v_normal, const char *h_top_separator,
	const char *h_lower_separator, const char *v_left_separator, const char *v_right_separator, const char *mid_separator)
{
	/* ��ֹ��δ���� gmw_init ǰ������������ */
	if (pCGI->inited != CGI_INITED)
		return -1;

	const char* src[] = {top_left,lower_left, top_right, lower_right , h_normal , v_normal, h_top_separator , h_lower_separator 
						 , v_left_separator, v_right_separator, mid_separator };
	char* dst[] = { pCGI->CFI.top_left,pCGI->CFI.lower_left, pCGI->CFI.top_right, pCGI->CFI.lower_right ,pCGI->CFI.h_normal ,
						 pCGI->CFI.v_normal,pCGI->CFI.h_top_separator ,pCGI->CFI.h_lower_separator
						 , pCGI->CFI.v_left_separator, pCGI->CFI.v_right_separator,pCGI->CFI.mid_separator };

	for (int i = 0; i <= 10; i++)
	{
		if (src[i] == NULL) {
			// ������� NULL���������ո����
			strcpy(dst[i], "  ");
		}
		else {
			int src_len = strlen(src[i]);

			// �����1�ֽ��ַ�����һ���ո�
			if (src_len == 1) {
				dst[i][0] = src[i][0];
				dst[i][1] = ' ';
				dst[i][2] = '\0';
			}
			// ���ǡ����2�ֽڣ�ֱ�Ӹ���
			// // �������2�ֽڣ���ȡǰ2�ֽ�
			else {
				dst[i][0] = src[i][0];
				dst[i][1] = src[i][1];
				dst[i][2] = '\0';
			}
		}
	}

	return 0; //�˾�ɸ�����Ҫ�޸�
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ���� CONSOLE_FRAME_TYPE �ṹ�е�ɫ��������С���Ƿ���Ҫ�ָ��ߵ�
  ������������������CONSOLE_GRAPHICS_INFO *const pCGI	������ṹָ��
			const int block_width						����ȣ�����ȱʡ2����ΪԼ�������Ϊ�����Ʊ�����������������Ҫ+1��
			const int block_high						���߶ȣ�����ȱʡ1��
			const bool separator						���Ƿ���Ҫ�ָ��ߣ�ȱʡΪtrue����Ҫ�ָ��ߣ�
  �� �� ֵ��
  ˵    ������ܴ�С/�Ƿ���Ҫ�ָ��ߵȵı仯�ᵼ��CONSOLE_GRAPHICS_INFO�ṹ����������Աֵ�ı仯��Ҫ����
***************************************************************************/
int gmw_set_frame_style(CONSOLE_GRAPHICS_INFO *const pCGI, const int block_width, const int block_high, const bool separator)
{
	/* ��ֹ��δ���� gmw_init ǰ������������ */
	if (pCGI->inited != CGI_INITED)
		return -1;
	//���
	pCGI->CFI.block_high = max(1, block_high);
	pCGI->CFI.block_width = max(2, block_width);
	if (block_width % 2 == 1)
	{
		pCGI->CFI.block_width++;
	}

	//�Ƿ���Ҫ�ָ�
	pCGI->CFI.separator = separator;

	//����ܸ߿�
	pCGI->CFI.bhigh = pCGI->CFI.block_high * pCGI->row_num + pCGI->CFI.separator * (pCGI->row_num - 1) + 2;
	pCGI->CFI.bwidth = pCGI->CFI.block_width * pCGI->col_num + pCGI->CFI.separator * 2 * (pCGI->col_num - 1) + 4;

	pCGI->lines = pCGI->extern_up_lines + pCGI->extern_down_lines + pCGI->CFI.bhigh
							+ pCGI->draw_frame_with_col_no + pCGI->top_status_line + pCGI->lower_status_line + 4;
	pCGI->cols = pCGI->extern_left_cols + pCGI->extern_right_cols + pCGI->CFI.bwidth
						+ pCGI->draw_frame_with_row_no * 2 + 1;

	pCGI->SLI.lower_start_y = pCGI->start_y + pCGI->CFI.bhigh + pCGI->draw_frame_with_col_no;

	return 0; //�˾�ɸ�����Ҫ�޸�
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ���� CONSOLE_BORDER_TYPE �ṹ�е���ɫ
  ���������CONSOLE_GRAPHICS_INFO *const pCGI	������ṹָ��
			const int bg_color					������ɫ��ȱʡ -1��ʾ�ô��ڱ���ɫ��
			const int fg_color					��ǰ��ɫ��ȱʡ -1��ʾ�ô���ǰ��ɫ��
  �� �� ֵ��
  ˵    �����������ɫֵ���󼰳�ͻ����Ҫ��Ϊ��֤
				������ɫ��0-15��ǰ��ɫ����ɫ��ֵһ�µ����޷��������ݵ�
***************************************************************************/
int gmw_set_frame_color(CONSOLE_GRAPHICS_INFO *const pCGI, const int bgcolor, const int fgcolor)
{
	/* ��ֹ��δ���� gmw_init ǰ������������ */
	if (pCGI->inited != CGI_INITED)
		return -1;

	//ȱʡ -1��ʾ�ô��ڱ���ɫ--�������˼
	pCGI->CFI.bgcolor = bgcolor < 0 ? pCGI->area_bgcolor : bgcolor;
	pCGI->CFI.fgcolor = fgcolor < 0 ? pCGI->area_fgcolor : fgcolor;

	return 0; //�˾�ɸ�����Ҫ�޸�
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ���� CONSOLE_BLOCK_INFO �ṹ�е�6�����ͣ�ȱʡ4�֣�
  ���������CONSOLE_GRAPHICS_INFO *const pCGI	������ṹָ��
			const int type						��1 - ȫ˫�� 2 - ȫ���� 3 - ��˫���� 4 - �ᵥ��˫
  �� �� ֵ��
  ˵    ����
***************************************************************************/
int gmw_set_block_default_linetype(CONSOLE_GRAPHICS_INFO *const pCGI, const int type)
{
	/* ��ֹ��δ���� gmw_init ǰ������������ */
	if (pCGI->inited != CGI_INITED)
		return -1;

	bool flag = false;
	if (type == 1)
	{
		strcpy(pCGI->CBI.top_left, "�X");
		strcpy(pCGI->CBI.lower_left, "�^");
		strcpy(pCGI->CBI.top_right, "�[");
		strcpy(pCGI->CBI.lower_right, "�a");
		strcpy(pCGI->CBI.h_normal, "�T");
		strcpy(pCGI->CBI.v_normal, "�U");
		flag = true;
	}
	else if (type == 2)
	{
		strcpy(pCGI->CBI.top_left, "��");
		strcpy(pCGI->CBI.lower_left, "��");
		strcpy(pCGI->CBI.top_right, "��");
		strcpy(pCGI->CBI.lower_right, "��");
		strcpy(pCGI->CBI.h_normal, "��");
		strcpy(pCGI->CBI.v_normal, "��");
		flag = true;
	}
	else if (type == 3)
	{
		strcpy(pCGI->CBI.top_left, "�V");
		strcpy(pCGI->CBI.lower_left, "�\");
		strcpy(pCGI->CBI.top_right, "�Y");
		strcpy(pCGI->CBI.lower_right, "�_");
		strcpy(pCGI->CBI.h_normal, "�T");
		strcpy(pCGI->CBI.v_normal, "��");
		flag = true;
	}
	else
	{
		strcpy(pCGI->CBI.top_left, "�W");
		strcpy(pCGI->CBI.lower_left, "�]");
		strcpy(pCGI->CBI.top_right, "�Z");
		strcpy(pCGI->CBI.lower_right, "�`");
		strcpy(pCGI->CBI.h_normal, "��");
		strcpy(pCGI->CBI.v_normal, "�U");
		flag = true;
	}
	if (!flag)
	{
		//cpy���ɹ�
		cout << "���ɹ�" << endl;
		//std::sleep(500);
	}

	return 0; //�˾�ɸ�����Ҫ�޸�
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ���� CONSOLE_BLOCK_INFO �ṹ�е�6������
  ���������CONSOLE_GRAPHICS_INFO *const pCGI	������ṹָ��
		   const char *...					����6�֣������.h���˴���
  �� �� ֵ��
  ˵    ����Լ��Ϊһ�������Ʊ��������ʹ���������ݣ���Ϊ��֤2�ֽ�
			1������2�ֽ���ֻȡǰ2�ֽ�
			2�������NULL���������ո����
			3�������1�ֽڣ���һ���ո������˶�������ʾ�ң������
***************************************************************************/
int gmw_set_block_linetype(CONSOLE_GRAPHICS_INFO *const pCGI, const char *top_left, const char *lower_left, const char *top_right, const char *lower_right, const char *h_normal, const char *v_normal)
{
	/* ��ֹ��δ���� gmw_init ǰ������������ */
	if (pCGI->inited != CGI_INITED)
		return -1;

	const char* src[] = { top_left,lower_left, top_right, lower_right , h_normal , v_normal };
	char* dst[] = { pCGI->CFI.top_left,pCGI->CFI.lower_left, pCGI->CFI.top_right, pCGI->CFI.lower_right ,pCGI->CFI.h_normal ,
						 pCGI->CFI.v_normal,pCGI->CFI.h_top_separator ,pCGI->CFI.h_lower_separator
						 , pCGI->CFI.v_left_separator, pCGI->CFI.v_right_separator,pCGI->CFI.mid_separator };

	for (int i = 0; i <= 5; i++)
	{
		if (src[i] == NULL) {
			// ������� NULL���������ո����
			strcpy(dst[i], "  ");
		}
		else {
			int src_len = strlen(src[i]);

			// �����1�ֽ��ַ�����һ���ո�
			if (src_len == 1) {
				dst[i][0] = src[i][0];
				dst[i][1] = ' ';
				dst[i][2] = '\0';
			}
			// ���ǡ����2�ֽڣ�ֱ�Ӹ���
			// // �������2�ֽڣ���ȡǰ2�ֽ�
			else {
				dst[i][0] = src[i][0];
				dst[i][1] = src[i][1];
				dst[i][2] = '\0';
			}
		}
	}

	return 0; //�˾�ɸ�����Ҫ�޸�
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�����ÿ����Ϸɫ��(����)�Ƿ���ҪС�߿�
  ���������CONSOLE_GRAPHICS_INFO *const pCGI	������ṹָ��
		   const bool on_off					��true - ��Ҫ flase - ����Ҫ��ȱʡfalse��
  �� �� ֵ��
  ˵    �����߿�Լ��Ϊ�����Ʊ����˫��
***************************************************************************/
int gmw_set_block_border_switch(CONSOLE_GRAPHICS_INFO *const pCGI, const bool on_off)
{
	/* ��ֹ��δ���� gmw_init ǰ������������ */
	if (pCGI->inited != CGI_INITED)
		return -1;

	pCGI->CBI.block_border = on_off;

	return 0; //�˾�ɸ�����Ҫ�޸�
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ������Ƿ���ʾ����״̬��
  ���������CONSOLE_GRAPHICS_INFO *const pCGI	������ṹָ��
			const int type						��״̬�����ͣ���/�£�
			const bool on_off					��true - ��Ҫ flase - ����Ҫ��ȱʡtrue��
  �� �� ֵ��
  ˵    ����1��״̬�������Լ�����£�
			   1.1����״̬��ֻ��һ�У������������Ϸ�����/�б�����棬Ϊ��������ʼһ�У�����������Ͻ����������״̬�������꣩
			   1.2����״̬��ֻ��һ�У������������·����ߵ�����
			   1.3��״̬���Ŀ��Ϊ�������ȣ������Ϣ������ض�
		   2�����еı仯�ᵼ��CONSOLE_GRAPHICS_INFO�ṹ����������Աֵ�ı仯��Ҫ����
***************************************************************************/
int gmw_set_status_line_switch(CONSOLE_GRAPHICS_INFO *const pCGI, const int type, const bool on_off)
{
	/* ��ֹ��δ���� gmw_init ǰ������������ */
	if (pCGI->inited != CGI_INITED)
		return -1;

	if (type == TOP_STATUS_LINE)
	{
		pCGI->SLI.is_top_status_line = on_off;
		pCGI->top_status_line = on_off;
		/* ������ʼλ�� */
	pCGI->start_y = pCGI->extern_up_lines + (on_off ? 1 : 0);
	pCGI->SLI.top_start_x = pCGI->start_x;
	pCGI->SLI.top_start_y = pCGI->start_y - 1;
	/* �ײ���ʼλ�� */
	pCGI->SLI.lower_start_x = pCGI->start_x;
	pCGI->SLI.lower_start_y = pCGI->start_y + pCGI->CFI.bhigh + pCGI->draw_frame_with_col_no;
	}

	if (type == LOWER_STATUS_LINE)
	{
		pCGI->SLI.is_lower_status_line = on_off;
		pCGI->lower_status_line = on_off;
	}
	

	pCGI->lines = pCGI->extern_up_lines + pCGI->extern_down_lines +
		pCGI->draw_frame_with_col_no + pCGI->CFI.bhigh +
		pCGI->SLI.is_top_status_line + pCGI->SLI.is_lower_status_line + 4;

	pCGI->cols = pCGI->extern_left_cols + pCGI->extern_right_cols +
		pCGI->draw_frame_with_row_no * 2 + pCGI->CFI.bwidth + 1;

	return 0; //�˾�ɸ�����Ҫ�޸�
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ���������״̬������ɫ
  ���������CONSOLE_GRAPHICS_INFO *const pCGI	������ṹָ��
			const int type						��״̬�����ͣ���/�£�
			const int normal_bgcolor			�������ı�����ɫ��ȱʡ -1��ʾʹ�ô��ڱ���ɫ��
			const int normal_fgcolor			�������ı�ǰ��ɫ��ȱʡ -1��ʾʹ�ô���ǰ��ɫ��
			const int catchy_bgcolor			����Ŀ�ı�����ɫ��ȱʡ -1��ʾʹ�ô��ڱ���ɫ��
			const int catchy_fgcolor			����Ŀ�ı�ǰ��ɫ��ȱʡ -1��ʾʹ������ɫ��
  ���������
  �� �� ֵ��
  ˵    �����������ɫֵ���󼰳�ͻ����Ҫ��Ϊ��֤
				������ɫ��0-15��ǰ��ɫ����ɫ��ֵһ�µ����޷��������ݵ�
***************************************************************************/
int gmw_set_status_line_color(CONSOLE_GRAPHICS_INFO *const pCGI, const int type, const int normal_bgcolor, const int normal_fgcolor, const int catchy_bgcolor, const int catchy_fgcolor)
{
	/* ��ֹ��δ���� gmw_init ǰ������������ */
	if (pCGI->inited != CGI_INITED)
		return -1;

	if (type == TOP_STATUS_LINE)
	{
		pCGI->SLI.top_normal_bgcolor = normal_bgcolor < 0 ? pCGI->area_bgcolor : normal_bgcolor;
		pCGI->SLI.top_catchy_bgcolor = catchy_bgcolor < 0 ? pCGI->area_bgcolor : catchy_bgcolor;
		pCGI->SLI.top_normal_fgcolor = normal_fgcolor < 0 ? pCGI->area_fgcolor : normal_fgcolor;
		//��Ŀ�ı�ǰ��ɫ��ȱʡ -1��ʾʹ������ɫ��
		pCGI->SLI.top_catchy_fgcolor = catchy_fgcolor < 0 ? COLOR_HYELLOW : catchy_fgcolor;
	}

	if (type == LOWER_STATUS_LINE)
	{
		pCGI->SLI.lower_normal_bgcolor = normal_bgcolor < 0 ? pCGI->area_bgcolor : normal_bgcolor;
		pCGI->SLI.lower_catchy_bgcolor = catchy_bgcolor < 0 ? pCGI->area_bgcolor : catchy_bgcolor;
		pCGI->SLI.lower_normal_fgcolor = normal_fgcolor < 0 ? pCGI->area_fgcolor : normal_fgcolor;
		//��Ŀ�ı�ǰ��ɫ��ȱʡ -1��ʾʹ������ɫ��
		pCGI->SLI.lower_catchy_fgcolor = catchy_fgcolor < 0 ? COLOR_HYELLOW : catchy_fgcolor;
	}

	return 0; //�˾�ɸ�����Ҫ�޸�
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ������Ƿ���ʾ�к�
  ���������CONSOLE_GRAPHICS_INFO *const pCGI	������ṹָ��
			const bool on_off					��true - ��ʾ flase - ����ʾ��ȱʡfalse��
  �� �� ֵ��
  ˵    ����1���к�Լ��Ϊ��ĸA��ʼ�������У��������26�����a��ʼ������52��ͳһΪ*��ʵ��Ӧ�ò����ܣ�
            2���Ƿ���ʾ�кŵı仯�ᵼ��CONSOLE_GRAPHICS_INFO�ṹ����������Աֵ�ı仯��Ҫ����
***************************************************************************/
int gmw_set_rowno_switch(CONSOLE_GRAPHICS_INFO *const pCGI, const bool on_off)
{
	/* ��ֹ��δ���� gmw_init ǰ������������ */
	if (pCGI->inited != CGI_INITED)
		return -1;

	pCGI->draw_frame_with_row_no = false;
	pCGI->draw_frame_with_row_no = on_off;

	pCGI->lines = pCGI->extern_up_lines + pCGI->extern_down_lines +
		pCGI->draw_frame_with_col_no + pCGI->CFI.bhigh +
		pCGI->top_status_line + pCGI->lower_status_line + 4;

	pCGI->cols = pCGI->extern_left_cols + pCGI->extern_right_cols +
		(pCGI->draw_frame_with_row_no ? 2 : 0) +  /* flag �к���Ҫ�������� flag*/
		pCGI->CFI.bwidth + 1;

	pCGI->SLI.lower_start_y = pCGI->start_y + pCGI->CFI.bhigh + pCGI->draw_frame_with_col_no;

	return 0; //�˾�ɸ�����Ҫ�޸�
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ������Ƿ���ʾ�б�
  ���������CONSOLE_GRAPHICS_INFO *const pCGI	������ṹָ��
			const bool on_off					��true - ��ʾ flase - ����ʾ��ȱʡfalse��
  �� �� ֵ��
  ˵    ����1���б�Լ��Ϊ����0��ʼ�������У�����0-99������99ͳһΪ**��ʵ��Ӧ�ò����ܣ�
            2���Ƿ���ʾ�б�ı仯�ᵼ��CONSOLE_GRAPHICS_INFO�ṹ����������Աֵ�ı仯��Ҫ����
***************************************************************************/
int gmw_set_colno_switch(CONSOLE_GRAPHICS_INFO *const pCGI, const bool on_off)
{
	/* ��ֹ��δ���� gmw_init ǰ������������ */
	if (pCGI->inited != CGI_INITED)
		return -1;
	pCGI->draw_frame_with_col_no = false;
	pCGI->draw_frame_with_col_no = on_off;

	pCGI->lines = pCGI->extern_up_lines + pCGI->extern_down_lines +
		pCGI->CFI.bhigh + pCGI->SLI.is_top_status_line +
		pCGI->SLI.is_lower_status_line +
		(on_off ? 1 : 0) + 4;  /* �б�����1��flag */

	pCGI->cols = pCGI->extern_left_cols + pCGI->extern_right_cols +
		pCGI->draw_frame_with_row_no * 2 + pCGI->CFI.bwidth + 1;

	/* �ײ���ʼλ�� */
	pCGI->SLI.lower_start_y = pCGI->start_y + pCGI->CFI.bhigh + (on_off ? 1 : 0);


	return 0; //�˾�ɸ�����Ҫ�޸�
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ���ӡ CONSOLE_GRAPHICS_INFO �ṹ���еĸ���Աֵ
  ���������
  �� �� ֵ��
  ˵    ����1�����������ã���ӡ��ʽ�Զ���
            2������������������δ���ù������Բ�ʵ��
***************************************************************************/
int gmw_print(const CONSOLE_GRAPHICS_INFO *const pCGI)
{
	/* ��ֹ��δ���� gmw_init ǰ������������ */
	if (pCGI->inited != CGI_INITED)
		return -1;

	cout << "test-gmw-print-list" << endl;
	while (1)
	{
		int cmd = _getch();
		if (cmd == 13)
		{
			break;
		}
	}

	cout << "is_top_status_line  " << pCGI->SLI.is_top_status_line << endl;
	cout << "is_lower_status_line    " << pCGI->SLI.is_lower_status_line << endl;

	cout << "top_start_x       " << pCGI->SLI.top_start_x << endl;
	cout << "top_start_y       " << pCGI->SLI.top_start_y << endl;

	cout << "top_normal_bgcolor     " << pCGI->SLI.top_normal_bgcolor << endl;
	cout << "top_normal_fgcolor      " << pCGI->SLI.top_normal_fgcolor << endl;

	cout << "SLI width         " << pCGI->SLI.width << endl;

	while (1)
	{
		int cmd = _getch();
		if (cmd == 13)
		{
			break;
		}
	}

	cout << "block_width     " << pCGI->CFI.block_width << endl;
	cout << "block_high    " << pCGI->CFI.block_high << endl;

	cout << "separator   " << pCGI->CFI.separator << endl;

	cout << "bwidth     " << pCGI->CFI.bwidth << endl;
	cout << "bhigh      " << pCGI->CFI.bhigh << endl;

	while (1)
	{
		int cmd = _getch();
		if (cmd == 13)
		{
			break;
		}
	}

	cout << "row_num    " << pCGI->row_num << endl;
	cout << "col_num      " << pCGI->col_num << endl;

	cout << "extern_up_lines   " << pCGI->extern_up_lines << endl;
	cout << "extern_down_lines   " << pCGI->extern_down_lines << endl;
	cout << "extern_left_cols  " << pCGI->extern_left_cols << endl;
	cout << "extern_right_cols " << pCGI->extern_right_cols << endl;

	cout << "start_x    " << pCGI->start_x << endl;
	cout << "start_y" << pCGI->start_y << endl;

	cout << "lines    " << pCGI->lines << endl;
	cout << "cols    " << pCGI->cols << endl;

	while (1)
	{
		int cmd = _getch();
		if (cmd == 13)
		{
			break;
		}
	}

	return 0; //�˾�ɸ�����Ҫ�޸�
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ��� CONSOLE_GRAPHICS_INFO �ṹ����ȱʡֵ���г�ʼ��
  ���������CONSOLE_GRAPHICS_INFO *const pCGI������ṹָ��
		   const int row					����Ϸ����ɫ��������ȱʡ10��
		   const int col					����Ϸ����ɫ��������ȱʡ10��
		   const int bgcolor				���������ڱ���ɫ��ȱʡ COLOR_BLACK��
		   const int fgcolor				���������ڱ���ɫ��ȱʡ COLOR_WHITE��
  �� �� ֵ��
  ˵    �������ڱ�����/ǰ���ף�����16*8�����������޶������У�����״̬�����У����к�/�б꣬�������Ϊ˫�ߣ�ɫ����2/�߶�1/��С�߿���ɫ��
***************************************************************************/
int gmw_init(CONSOLE_GRAPHICS_INFO *const pCGI, const int row, const int col, const int bgcolor, const int fgcolor)
{
	/* �����ñ�� */
	pCGI->inited = CGI_INITED;

	//��Ĭ��ֵ�����Ϸ����к�������hͷ�ļ�Ѱ�ҾͿ�����
	gmw_set_rowcol(pCGI, row, col);
	gmw_set_font(pCGI,"������");
	gmw_set_color(pCGI, COLOR_BLACK, COLOR_WHITE);
	gmw_set_delay(pCGI, DELAY_OF_DRAW_FRAME, 0);
	gmw_set_delay(pCGI, DELAY_OF_DRAW_BLOCK, 0);
	gmw_set_delay(pCGI, DELAY_OF_BLOCK_MOVED, BLOCK_MOVED_DELAY_MS);
	gmw_set_ext_rowcol(pCGI);

	gmw_set_frame_default_linetype(pCGI, 1);
	gmw_set_frame_style(pCGI);
	gmw_set_frame_color(pCGI);

	gmw_set_block_default_linetype(pCGI, 1);
	gmw_set_block_border_switch(pCGI);


	gmw_set_status_line_switch(pCGI, TOP_STATUS_LINE);
	gmw_set_status_line_switch(pCGI, LOWER_STATUS_LINE);
	gmw_set_status_line_color(pCGI, TOP_STATUS_LINE);
	gmw_set_status_line_color(pCGI, LOWER_STATUS_LINE);

	gmw_set_rowno_switch(pCGI,false);
	gmw_set_colno_switch(pCGI,false);


	pCGI->SLI.lower_catchy_fgcolor = COLOR_HYELLOW;
	pCGI->SLI.top_catchy_fgcolor = COLOR_HYELLOW;

	cct_setfontsize(pCGI->CFT.font_type, pCGI->CFT.font_size_high);
	cct_setconsoleborder(pCGI->cols, pCGI->lines);
	cct_setcolor(pCGI->area_bgcolor, pCGI->area_fgcolor);

	return 0; //�˾�ɸ�����Ҫ�޸�
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�������Ϸ���
  ���������const CONSOLE_GRAPHICS_INFO *const pCGI	������ṹָ��
  �� �� ֵ��
  ˵    ��������ɲο�demo��Ч��
***************************************************************************/
int gmw_draw_frame(const CONSOLE_GRAPHICS_INFO *const pCGI)
{
	/* ��ֹ��δ���� gmw_init ǰ������������ */
	if (pCGI->inited != CGI_INITED)
		return -1;

	//���ڻ�ȡĿǰ��ϣ���������x��y��ʹ��showstr
	int x, y;

	cct_setfontsize(pCGI->CFT.font_type, pCGI->CFT.font_size_high);
	cct_setconsoleborder(pCGI->cols, pCGI->lines);
	cct_setcolor(pCGI->area_bgcolor, pCGI->area_fgcolor);

	cct_cls();

	//�Ƿ���Ҫ�б�
	if (pCGI->draw_frame_with_col_no)
	{
		cct_gotoxy(pCGI->extern_left_cols + pCGI->draw_frame_with_row_no * 2 + pCGI->CFI.block_width / 2 + 1,
				   pCGI->extern_up_lines + pCGI->SLI.is_top_status_line);//ֱ��+1������
		for (int j = 0; j < pCGI->col_num; j++)
		{
			if (j < 100)
			{
				cout << setw(pCGI->CFI.block_width + 2 * pCGI->CFI.separator) << setiosflags(ios::left) << (j >= 100 ? char('*') : j);//����100���*
			}
			else
			{
				cout << setw(pCGI->CFI.block_width + 2 * pCGI->CFI.separator) << setiosflags(ios::left) << "**";
			}
		}
	}

	//���д�ӡ
	cct_setcolor(pCGI->CFI.bgcolor, pCGI->CFI.fgcolor);
	cct_gotoxy(pCGI->extern_left_cols + pCGI->draw_frame_with_row_no * 2, 
			   pCGI->extern_up_lines + pCGI->draw_frame_with_col_no + pCGI->SLI.is_top_status_line);
	//����
	cct_getxy(x, y);
	cct_showstr(x, y, pCGI->CFI.top_left, pCGI->CFI.bgcolor, pCGI->CFI.fgcolor, 1);
	//���м�
	for (int i = 0; i < pCGI->col_num; i++)
	{
		//����м��
		if (pCGI->CFI.separator)
		{
			for (int j = 0; j < pCGI->CFI.block_width; j++, j++)
			{
				cct_getxy(x, y);
				cct_showstr(x, y, pCGI->CFI.h_normal, pCGI->CFI.bgcolor, pCGI->CFI.fgcolor, 1);
				Sleep(pCGI->delay_of_draw_frame);
			}
			cct_getxy(x, y);
			cct_showstr(x, y, pCGI->CFI.h_top_separator, pCGI->CFI.bgcolor, pCGI->CFI.fgcolor, 1);
			Sleep(pCGI->delay_of_draw_frame);
		}
		else
		{
			for (int j = 0; j < pCGI->CFI.block_width; j++, j++)
			{
				cct_getxy(x, y);
				cct_showstr(x, y, pCGI->CFI.h_normal, pCGI->CFI.bgcolor, pCGI->CFI.fgcolor, 1);
				Sleep(pCGI->delay_of_draw_frame);
			}
		}
	}
	//����
	if (pCGI->CFI.separator)
	{
		cct_getxy(x, y);
		cct_showstr(x - 2, y, pCGI->CFI.top_right, pCGI->CFI.bgcolor, pCGI->CFI.fgcolor, 1);
	}
	else
	{
		cct_getxy(x, y);
		cct_showstr(x, y, pCGI->CFI.top_right, pCGI->CFI.bgcolor, pCGI->CFI.fgcolor, 1);
	}
	//��ʱx,yָ���һ�б߽�����һ����

	//�м��������
	
	for (int i = 0; i < pCGI->row_num; i++)
	{
		for (int ii = 0; ii < pCGI->CFI.block_high; ii++)//ÿһ��block��ÿһ��
		{
			//���ܻ����б�
			if (pCGI->draw_frame_with_row_no)
			{	
				if ((ii == (pCGI->CFI.block_high - 1) / 2))//����Ҫ���б��ʱ��
				{
					cct_setcolor(pCGI->area_bgcolor, pCGI->area_fgcolor);
					cct_gotoxy(pCGI->extern_left_cols, 
					ii + 1 + (i * (pCGI->CFI.separator + pCGI->CFI.block_high)) + pCGI->SLI.is_top_status_line 
					+ pCGI->extern_up_lines + pCGI->draw_frame_with_col_no);
					if (i < 52)
						cout << (i >= 26 ? (char)('a' + i - 26) : (char)('A' + i));
					else
						cout << '*';
					Sleep(pCGI->delay_of_draw_frame);
				}	
			}

			cct_setcolor((*pCGI).CFI.bgcolor, (*pCGI).CFI.fgcolor);
			cct_gotoxy(pCGI->extern_left_cols + pCGI->draw_frame_with_row_no * 2, 
					   ii + 1 + (i * (pCGI->CFI.separator + pCGI->CFI.block_high)) + pCGI->SLI.is_top_status_line 
					   + pCGI->extern_up_lines + pCGI->draw_frame_with_col_no);
			cct_getxy(x, y);//��ʱx��yӦ����ÿһ�еĵ�һ��Ԫ��
			cct_showstr(x, y, pCGI->CFI.v_normal, (*pCGI).CFI.bgcolor,(*pCGI).CFI.fgcolor,1);

			for (int j = 0; j < pCGI->col_num; j++) {
				for (int k = 0; k < pCGI->CFI.block_width; k +=2)
				{
					cout << "  ";//�����ַ�2��һ��
				}
				if (pCGI->CFI.separator)//�����Ҫ��϶���ߵ����ұ߽�
				{
					cct_getxy(x, y);
					cct_showstr(x,y,pCGI->CFI.v_normal, (*pCGI).CFI.bgcolor, (*pCGI).CFI.fgcolor, 1);
					if (j == pCGI->col_num - 1)
					{
						cct_getxy(x, y);
						cct_showstr(x - 2, y, pCGI->CFI.v_normal, (*pCGI).CFI.bgcolor, (*pCGI).CFI.fgcolor, 1);
					}
				}
				else
				{
					if (j == pCGI->col_num - 1)
					{
						cct_getxy(x, y);
						cct_showstr(x, y, pCGI->CFI.v_normal, (*pCGI).CFI.bgcolor, (*pCGI).CFI.fgcolor, 1);
					}
				}
				Sleep(pCGI->delay_of_draw_frame);
			}

			Sleep(pCGI->delay_of_draw_frame);
		}
		
		if (pCGI->CFI.separator)//�м�ָ����
		{
			cct_setcolor((*pCGI).CFI.bgcolor, (*pCGI).CFI.fgcolor);
			cct_gotoxy(pCGI->extern_left_cols + pCGI->draw_frame_with_row_no * 2, 
					   pCGI->SLI.is_top_status_line + pCGI->extern_up_lines + pCGI->draw_frame_with_col_no +
				       1 + (i + 1) * pCGI->CFI.block_high + i * pCGI->CFI.separator);
			cct_getxy(x, y);
			cct_showstr(x, y, pCGI->CFI.v_left_separator, (*pCGI).CFI.bgcolor, (*pCGI).CFI.fgcolor, 1);//��ָ�

			for (int j = 0; j < pCGI->col_num; j++) {
				for (int k = 0; k < pCGI->CFI.block_width; k += 2)
				{
					x += 2;
					cct_showstr(x, y, pCGI->CFI.h_normal, (*pCGI).CFI.bgcolor, (*pCGI).CFI.fgcolor, 1);
				}
				cct_getxy(x, y);
				cct_showstr(x, y, pCGI->CFI.mid_separator, (*pCGI).CFI.bgcolor, (*pCGI).CFI.fgcolor, 1);  // ����м�ָ���
				Sleep(pCGI->delay_of_draw_frame);
			}
			cct_getxy(x, y);
			cct_showstr(x-2, y, pCGI->CFI.v_right_separator, (*pCGI).CFI.bgcolor, (*pCGI).CFI.fgcolor, 1);//�ҷָ�
			//���ڹ��Ӧ������ÿһ�����һ�У���һ����Ҫ���¶�λ
		}

	}

	//���һ��
	cct_gotoxy(pCGI->extern_left_cols + pCGI->draw_frame_with_row_no * 2, 
			   pCGI->extern_up_lines + pCGI->draw_frame_with_col_no + pCGI->SLI.is_top_status_line + pCGI->CFI.bhigh - 1);
	cct_getxy(x, y);
	cct_setcolor((*pCGI).CFI.bgcolor, (*pCGI).CFI.fgcolor);
	cct_showstr(x, y, pCGI->CFI.lower_left, (*pCGI).CFI.bgcolor, (*pCGI).CFI.fgcolor, 1);

	for (int j = 0; j < pCGI->col_num; j++) {
		for (int k = 0; k < pCGI->CFI.block_width; k += 2)
		{
			x += 2;
			cct_showstr(x, y, pCGI->CFI.h_normal, (*pCGI).CFI.bgcolor, (*pCGI).CFI.fgcolor, 1);
		}
		if (pCGI->CFI.separator)
		{
			cct_getxy(x, y);
			cct_showstr(x, y, pCGI->CFI.h_lower_separator, (*pCGI).CFI.bgcolor, (*pCGI).CFI.fgcolor, 1);
		}
	}
	if(pCGI->CFI.separator)
	{
		cct_getxy(x, y);
		cct_showstr(x - 2, y, pCGI->CFI.lower_right, (*pCGI).CFI.bgcolor, (*pCGI).CFI.fgcolor, 1);
	}
	else
	{
		cct_getxy(x, y);
		cct_showstr(x , y, pCGI->CFI.lower_right, (*pCGI).CFI.bgcolor, (*pCGI).CFI.fgcolor, 1);
	}

	return 0; //�˾�ɸ�����Ҫ�޸�
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ���״̬������ʾ��Ϣ
  ���������const CONSOLE_GRAPHICS_INFO *const pCGI	������ṹָ��
		   const int type							��ָ������/��״̬��
		   const char *msg						��������Ϣ
		   const char *catchy_msg					����Ҫ�ر��ע����Ϣ����������Ϣǰ��ʾ��
  �� �� ֵ��
  ˵    ����1���������޶�Ϊ����ܵĿ�ȣ����к��б�λ�ã����������ȥ
            2��������һ���ַ���ĳ���ֵ�ǰ������ᵼ�º������룬Ҫ����
***************************************************************************/
int gmw_status_line(const CONSOLE_GRAPHICS_INFO *const pCGI, const int type, const char *msg, const char *catchy_msg)
{
	/* ��ֹ��δ���� gmw_init ǰ������������ */
	if (pCGI->inited != CGI_INITED)
		return -1;

	int x, y;//���ڼ�¼���λ��x��y
	int restrict_width = 2 * pCGI->draw_frame_with_row_no + pCGI->CFI.bwidth;//���ȵ�����

	char* new_catchy_msg = new(nothrow) char[restrict_width + 1]();
	char* new_msg = new(nothrow) char[restrict_width + 1]();

	const char* src[] = { catchy_msg,msg };
	char* dst[] = { new_catchy_msg, new_msg };

	//���Ƴ��ȣ��������һ������İ����������
	for (int i = 0; i <= 1; i++)
	{
		if (src[i] == NULL)
		{
			strcpy(dst[i], "");
			continue;
		}

		strncpy(dst[i], src[i], restrict_width);
		dst[i][restrict_width] = '\0';

		char* last = dst[i] + strlen(dst[i]) - 1; // ָ�����һ���ַ�
		if ((unsigned char)*last > 127) { // ����Ǻ���
			char* ps = dst[i];
			while (ps < last) {
				if ((unsigned char)*ps > 127)
					ps += 2;
				else
					ps += 1;
			}
			if (ps > last + 1) {
				*last = '\0';
			}
		}
	}

	if (type == TOP_STATUS_LINE)//��״̬��
	{
		if (!pCGI->SLI.is_top_status_line)//��״̬������ʾ
			return 0;
		cct_gotoxy(pCGI->SLI.top_start_x, pCGI->SLI.top_start_y);
		cct_setcolor(pCGI->SLI.top_catchy_bgcolor, pCGI->SLI.top_catchy_fgcolor);
		cct_getxy(x, y);
		cct_showstr(x, y, new_catchy_msg, pCGI->SLI.top_catchy_bgcolor, pCGI->SLI.top_catchy_fgcolor, 1);

		cct_setcolor(pCGI->SLI.top_normal_bgcolor, pCGI->SLI.top_normal_fgcolor);
		cct_getxy(x, y);
		cct_showstr(x, y, new_msg, pCGI->SLI.top_normal_bgcolor, pCGI->SLI.top_normal_fgcolor, 1);
	}
	else//��״̬��
	{
		if (!pCGI->SLI.is_lower_status_line)//��״̬������ʾ
			return 0;
		cct_gotoxy(pCGI->SLI.lower_start_x, pCGI->SLI.lower_start_y);
		cct_setcolor(pCGI->SLI.lower_catchy_bgcolor, pCGI->SLI.lower_catchy_fgcolor);
		cct_getxy(x, y);
		cct_showstr(x, y, new_catchy_msg, pCGI->SLI.lower_catchy_bgcolor, pCGI->SLI.lower_catchy_fgcolor, 1);

		cct_setcolor(pCGI->SLI.lower_normal_bgcolor, pCGI->SLI.lower_normal_fgcolor);
		cct_getxy(x, y);
		cct_showstr(x, y, new_msg, pCGI->SLI.lower_normal_bgcolor, pCGI->SLI.lower_normal_fgcolor, 1);
	}

	return 0; //�˾�ɸ�����Ҫ�޸�
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ���ʾĳһ��ɫ��(����Ϊ�ַ���������Ϊrow/col)
  ���������const CONSOLE_GRAPHICS_INFO *const pCGI	������ṹָ��
		   const int row_no						���кţ���0��ʼ����Ϊ��֤��ȷ�ԣ����򲻼�飩
		   const int col_no						���кţ���0��ʼ����Ϊ��֤��ȷ�ԣ����򲻼�飩
		   const int bdi_value						����Ҫ��ʾ��ֵ
		   const BLOCK_DISPLAY_INFO *const bdi		����Ÿ�ֵ��Ӧ����ʾ��Ϣ�Ľṹ������
  �� �� ֵ��
  ˵    ����1��BLOCK_DISPLAY_INFO �ĺ����ͷ�ļ����÷��ο���������
            2��bdi_valueΪ BDI_VALUE_BLANK ��ʾ�հ׿飬Ҫ���⴦��
***************************************************************************/
int gmw_draw_block(const CONSOLE_GRAPHICS_INFO *const pCGI, const int row_no, const int col_no, const int bdi_value, const BLOCK_DISPLAY_INFO *const bdi)
{
	/* ��ֹ��δ���� gmw_init ǰ������������ */
	if (pCGI->inited != CGI_INITED)
		return -1;

	//bdi��β�����뷴��Ķ���
	/*
	typedef struct _block_display_info_ {
		const int   value;	//Ҫ��ʾ���ڲ�����ֵ
		const int   bgcolor;	//-1��ʾ����Ϸ���򱳾�ɫ
		const int   fgcolor;	//-1��ʾ����Ϸ����ǰ��ɫ
		const char* content;	//�ڲ�����ֵ��Ӧ��ͼ�Σ����ΪNULL����ֱ����ʾ�ڲ������ֵ��
	} BLOCK_DISPLAY_INFO;
	*/

	//����ʹ��showstr
	int x, y;

	const BLOCK_DISPLAY_INFO* pbdi = bdi;
	while (pbdi->value != bdi_value && pbdi->value != BDI_VALUE_END)
		pbdi++;

	// ��ʼ����
	int block_start_x = pCGI->start_x + pCGI->draw_frame_with_row_no * 2 + 2 + col_no * (pCGI->CFI.block_width + pCGI->CFI.separator * 2);
	int block_start_y = pCGI->start_y + pCGI->draw_frame_with_col_no + 1 + row_no * (pCGI->CFI.block_high + pCGI->CFI.separator);

	// ������ɫ
	int block_fg_color;
	int block_bg_color;

	if (pbdi->value == BDI_VALUE_BLANK) {
		block_bg_color = (pbdi->bgcolor == -1) ? pCGI->CFI.bgcolor : pbdi->bgcolor;
		block_fg_color = block_bg_color;
	}
	else {
		block_bg_color = (pbdi->bgcolor == -1) ? pCGI->CFI.bgcolor : pbdi->bgcolor;
		block_fg_color = (pbdi->fgcolor == -1) ? pCGI->CFI.fgcolor : pbdi->fgcolor;
	}
	

	cct_setcolor(block_bg_color, block_fg_color);
	cct_gotoxy(block_start_x, block_start_y);
	if (pCGI->CBI.block_border)//�б߿򣬲�Ȼ����ֻ�������---����
	{
		for (int i = 0; i < pCGI->CFI.block_high; i++)
		{
			cct_gotoxy(block_start_x, block_start_y+i);
			if(i==0)
			{
				for (int j = 0; j < pCGI->CFI.block_width/2; j ++)//����һ������
				{
					cct_getxy(x, y);
					if (j == 0)
					{
						cct_getxy(x, y);
						cct_showstr(x, y, pCGI->CBI.top_left, block_bg_color, block_fg_color, 1);
					}
					else if (j == pCGI->CFI.block_width/2 - 1)
					{
						cct_getxy(x, y);
						cct_showstr(x, y, pCGI->CBI.top_right, block_bg_color, block_fg_color, 1);
					}
					else
					{
						cct_getxy(x, y);
						cct_showstr(x, y, pCGI->CBI.h_normal, block_bg_color, block_fg_color, 1);
					}

				}
			}
			else if (i == pCGI->CFI.block_high - 1)
			{
				for (int j = 0; j < pCGI->CFI.block_width/2; j ++)
				{
					cct_getxy(x, y);
					if (j == 0)
					{
						cct_getxy(x, y);
						cct_showstr(x, y, pCGI->CBI.lower_left, block_bg_color, block_fg_color, 1);
					}
					else if (j == pCGI->CFI.block_width/2 - 1)
					{
						cct_getxy(x, y);
						cct_showstr(x, y, pCGI->CBI.lower_right, block_bg_color, block_fg_color, 1);
					}
					else
					{
						cct_getxy(x, y);
						cct_showstr(x, y, pCGI->CBI.h_normal, block_bg_color, block_fg_color, 1);
					}
				}
			}
			else
			{
				for (int j = 0; j < pCGI->CFI.block_width/2; j ++)
				{
					if (j == 0 || j == pCGI->CFI.block_width / 2 - 1)
					{
						cct_getxy(x, y);
						cct_showstr(x, y, pCGI->CBI.v_normal, block_bg_color, block_fg_color, 1);
					}
					else
						cout << "  ";
				}
			}
		}
	}
	else//�������������λ�ã��õ�ɫ��
	{
		for (int i = 0; i < pCGI->CFI.block_high; i++)
		{
			cct_gotoxy(block_start_x, block_start_y + i);
			if (i == 0)
			{
				for (int j = 0; j < pCGI->CFI.block_width / 2; j++)//����һ������
				{
					cct_getxy(x, y);
					if (j == 0)
					{
						cct_getxy(x, y);
						cct_showstr(x, y, "  ", block_bg_color, block_fg_color, 1);
					}
					else if (j == pCGI->CFI.block_width / 2 - 1)
					{
						cct_getxy(x, y);
						cct_showstr(x, y, "  ", block_bg_color, block_fg_color, 1);
					}
					else
					{
						cct_getxy(x, y);
						cct_showstr(x, y, "  ", block_bg_color, block_fg_color, 1);
					}

				}
			}
			else if (i == pCGI->CFI.block_high - 1)
			{
				for (int j = 0; j < pCGI->CFI.block_width / 2; j++)
				{
					cct_getxy(x, y);
					if (j == 0)
					{
						cct_getxy(x, y);
						cct_showstr(x, y, "  ", block_bg_color, block_fg_color, 1);
					}
					else if (j == pCGI->CFI.block_width / 2 - 1)
					{
						cct_getxy(x, y);
						cct_showstr(x, y, "  ", block_bg_color, block_fg_color, 1);
					}
					else
					{
						cct_getxy(x, y);
						cct_showstr(x, y, "  ", block_bg_color, block_fg_color, 1);
					}
				}
			}
			else
			{
				for (int j = 0; j < pCGI->CFI.block_width / 2; j++)
				{
					if (j == 0 || j == pCGI->CFI.block_width / 2 - 1)
					{
						cct_getxy(x, y);
						cct_showstr(x, y, "  ", block_bg_color, block_fg_color, 1);
					}
					else
						cout << "  ";
				}
			}
		}
	}

	/* ���� */
	int content_x = block_start_x + (pCGI->CFI.block_width - 1) / 2;
	int content_y = block_start_y + (pCGI->CFI.block_high - 1) / 2;

	if (pbdi->content == NULL && pbdi->value != BDI_VALUE_BLANK)
	{
		cct_gotoxy(content_x, content_y);
		//cct_getxy(x, y);
		//cct_showstr(x, y, pbdi->value, block_bg_color, block_fg_color, 1);
		cout << pbdi->value;
	}
	else
	{
		cct_gotoxy(content_x, content_y);
		cct_getxy(x, y);
		cct_showstr(x, y, pbdi->content, block_bg_color, block_fg_color, 1);
		//cout << pbdi->content;
	}

	return 0; //�˾�ɸ�����Ҫ�޸�
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ��ƶ�ĳһ��ɫ��
  ���������const CONSOLE_GRAPHICS_INFO *const pCGI	������ṹָ��
		   const int row_no						���кţ���0��ʼ����Ϊ��֤��ȷ�ԣ����򲻼�飩
		   const int col_no						���кţ���0��ʼ����Ϊ��֤��ȷ�ԣ����򲻼�飩
		   const int bdi_value						����Ҫ��ʾ��ֵ
		   const int blank_bdi_value				���ƶ����������ڶ���Ч����ʾʱ���ڱ�ʾ�հ׵�ֵ��һ��Ϊ0���˴���Ϊ�������룬�ǿ��ǵ����ܳ��ֵ����������
		   const BLOCK_DISPLAY_INFO *const bdi		�������ʾֵ/�հ�ֵ��Ӧ����ʾ��Ϣ�Ľṹ������
		   const int direction						���ƶ�����һ�����֣������cmd_gmw_tools.h
		   const int distance						���ƶ����루��1��ʼ����Ϊ��֤��ȷ�ԣ����򲻼�飩
  �� �� ֵ��
  ˵    ����
***************************************************************************/
int gmw_draw_block_by_a_step(const CONSOLE_GRAPHICS_INFO* const pCGI, const int row_no, const int col_no, const int bdi_value, const BLOCK_DISPLAY_INFO* const bdi,int dx,int dy)
{
	/* ��ֹ��δ���� gmw_init ǰ������������ */
	if (pCGI->inited != CGI_INITED)
		return -1;

	//bdi��β�����뷴��Ķ���
	/*
	typedef struct _block_display_info_ {
		const int   value;	//Ҫ��ʾ���ڲ�����ֵ
		const int   bgcolor;	//-1��ʾ����Ϸ���򱳾�ɫ
		const int   fgcolor;	//-1��ʾ����Ϸ����ǰ��ɫ
		const char* content;	//�ڲ�����ֵ��Ӧ��ͼ�Σ����ΪNULL����ֱ����ʾ�ڲ������ֵ��
	} BLOCK_DISPLAY_INFO;
	*/

	//����ʹ��showstr
	int x, y;

	const BLOCK_DISPLAY_INFO* pbdi = bdi;
	while (pbdi->value != bdi_value && pbdi->value != BDI_VALUE_END)
		pbdi++;

	// ��ʼ����
	int block_start_x = pCGI->start_x + pCGI->draw_frame_with_row_no * 2 + 2 + col_no * (pCGI->CFI.block_width + pCGI->CFI.separator * 2)+dx;//����x��ƫ��
	int block_start_y = pCGI->start_y + pCGI->draw_frame_with_col_no + 1 + row_no * (pCGI->CFI.block_high + pCGI->CFI.separator)+dy;//����y��ƫ��

	// ������ɫ
	int block_fg_color;
	int block_bg_color;

	if (pbdi->value == BDI_VALUE_BLANK) {
		block_bg_color = (pbdi->bgcolor == -1) ? pCGI->CFI.bgcolor : pbdi->bgcolor;
		block_fg_color = block_bg_color;
	}
	else {
		block_bg_color = (pbdi->bgcolor == -1) ? pCGI->CFI.bgcolor : pbdi->bgcolor;
		block_fg_color = (pbdi->fgcolor == -1) ? pCGI->CFI.fgcolor : pbdi->fgcolor;
	}


	cct_setcolor(block_bg_color, block_fg_color);
	cct_gotoxy(block_start_x, block_start_y);
	if (pCGI->CBI.block_border)//�б߿򣬲�Ȼ����ֻ�������---����
	{
		for (int i = 0; i < pCGI->CFI.block_high; i++)
		{
			cct_gotoxy(block_start_x, block_start_y + i);
			if (i == 0)
			{
				for (int j = 0; j < pCGI->CFI.block_width / 2; j++)//����һ������
				{
					cct_getxy(x, y);
					if (j == 0)
					{
						cct_getxy(x, y);
						cct_showstr(x, y, pCGI->CBI.top_left, block_bg_color, block_fg_color, 1);
					}
					else if (j == pCGI->CFI.block_width / 2 - 1)
					{
						cct_getxy(x, y);
						cct_showstr(x, y, pCGI->CBI.top_right, block_bg_color, block_fg_color, 1);
					}
					else
					{
						cct_getxy(x, y);
						cct_showstr(x, y, pCGI->CBI.h_normal, block_bg_color, block_fg_color, 1);
					}

				}
			}
			else if (i == pCGI->CFI.block_high - 1)
			{
				for (int j = 0; j < pCGI->CFI.block_width / 2; j++)
				{
					cct_getxy(x, y);
					if (j == 0)
					{
						cct_getxy(x, y);
						cct_showstr(x, y, pCGI->CBI.lower_left, block_bg_color, block_fg_color, 1);
					}
					else if (j == pCGI->CFI.block_width / 2 - 1)
					{
						cct_getxy(x, y);
						cct_showstr(x, y, pCGI->CBI.lower_right, block_bg_color, block_fg_color, 1);
					}
					else
					{
						cct_getxy(x, y);
						cct_showstr(x, y, pCGI->CBI.h_normal, block_bg_color, block_fg_color, 1);
					}
				}
			}
			else
			{
				for (int j = 0; j < pCGI->CFI.block_width / 2; j++)
				{
					if (j == 0 || j == pCGI->CFI.block_width / 2 - 1)
					{
						cct_getxy(x, y);
						cct_showstr(x, y, pCGI->CBI.v_normal, block_bg_color, block_fg_color, 1);
					}
					else
						cout << "  ";
				}
			}
		}
	}

	/* ���� */
	int content_x = block_start_x + (pCGI->CFI.block_width - 1) / 2;
	int content_y = block_start_y + (pCGI->CFI.block_high - 1) / 2;

	if (pbdi->content == NULL && pbdi->value != BDI_VALUE_BLANK)
	{
		cct_gotoxy(content_x, content_y);
		//cct_getxy(x, y);
		//cct_showstr(x, y, pbdi->value, block_bg_color, block_fg_color, 1);
		cout << pbdi->value;
	}
	else
	{
		cct_gotoxy(content_x, content_y);
		cct_getxy(x, y);
		cct_showstr(x, y, pbdi->content, block_bg_color, block_fg_color, 1);
		//cout << pbdi->content;
	}

	return 0; //�˾�ɸ�����Ҫ�޸�
}
int gmw_move_block(const CONSOLE_GRAPHICS_INFO *const pCGI, const int row_no, const int col_no, const int bdi_value, const int blank_bdi_value, const BLOCK_DISPLAY_INFO *const bdi, const int direction, const int distance)
{
	/* ��ֹ��δ���� gmw_init ǰ������������ */
	if (pCGI->inited != CGI_INITED)
		return -1;

	// ��ʼ����
	int block_start_x = pCGI->start_x + pCGI->draw_frame_with_row_no * 2 + 2 + col_no * (pCGI->CFI.block_width + pCGI->CFI.separator * 2);
	int block_start_y = pCGI->start_y + pCGI->draw_frame_with_col_no + 1 + row_no * (pCGI->CFI.block_high + pCGI->CFI.separator);

	//������ɫ
	int bgcolor = bdi->bgcolor < 0 ? pCGI->CFI.bgcolor : bdi->bgcolor;
	int fgcolor = bdi->fgcolor < 0 ? pCGI->CFI.fgcolor : bdi->fgcolor;

	/*
	 ����ɫ��������ƶ����� 
		define DOWN_TO_UP		0
		define UP_TO_DOWN		1
		define RIGHT_TO_LEFT	2
		define LEFT_TO_RIGHT	3
	*/

	//����ľ��벻�����ص�ľ��룬��Ҫ�¼���
	int true_steps = distance * (pCGI->CFI.block_width / 2 + pCGI->CFI.separator);

	if (direction == DOWN_TO_UP)//����
	{
		for (int i = 0; i <= true_steps; i++)
		{
			gmw_draw_block_by_a_step(pCGI, row_no, col_no, bdi_value, bdi, 0, -i);//dy==i ����һ��λ��
			Sleep(20);//����

			//��ԭ��λ�õ�����
			if (i != true_steps)
			{
				if (((i+1) % (pCGI->CFI.block_high + 1) == 0) && i != 0 && pCGI->CFI.separator)//�зָ���ŵĻ�����Ҫ�ж��Ƿ����
				{
					//test
					cct_showstr(block_start_x, block_start_y - i + (pCGI->CFI.block_high - 1), pCGI->CFI.h_normal, bgcolor, fgcolor, pCGI->CFI.block_width/2);
					//Sleep(1000);
				}
				else
				{
					cct_showstr(block_start_x, block_start_y - i + (pCGI->CFI.block_high - 1), " ", bgcolor, fgcolor, pCGI->CFI.block_width);
				}
			}
		}
	}
	if (direction == UP_TO_DOWN)//����
	{
		for (int i = 0; i <= true_steps; i++)
		{
			gmw_draw_block_by_a_step(pCGI, row_no, col_no, bdi_value, bdi, 0, +i);//dy==i
			Sleep(20);//����

			//��ԭ��λ�õ�����
			if (i != true_steps)
			{
				if (((i + 1) % (pCGI->CFI.block_high + 1) == 0) && i != 0 && pCGI->CFI.separator)//�зָ���ŵĻ�����Ҫ�ж��Ƿ����
				{
					//test
					cct_showstr(block_start_x, block_start_y + i, pCGI->CFI.h_normal, bgcolor, fgcolor, pCGI->CFI.block_width/2);
					//Sleep(1000);
				}
				else
				{
					cct_showstr(block_start_x, block_start_y + i, " ", bgcolor, fgcolor, pCGI->CFI.block_width);
				}
			}
		}
	}
	if (direction == RIGHT_TO_LEFT)//����
	{
		for (int i = 0; i <= 2*true_steps; i+=2)
		{
			gmw_draw_block_by_a_step(pCGI, row_no, col_no, bdi_value, bdi, -i,0 );//dy==i
			Sleep(20);//����

			//��ԭ��λ�õ�����
			if (i != 2 * true_steps)
			{
				for (int j = 0; j < pCGI->CFI.block_high; j++)
				{
					if (((i / 2 + 1) % ((pCGI->CFI.block_width + 2) / 2) == 0) && i != 0 && pCGI->CFI.separator)//�зָ���ŵĻ�����Ҫ�ж��Ƿ����
					{
						//test
						cct_showstr(block_start_x - i+(pCGI->CFI.block_width - 2), block_start_y + j , pCGI->CFI.v_normal, pCGI->CFI.bgcolor, pCGI->CFI.fgcolor, 1);
						//Sleep(100);
					}
					else
					{
						cct_showstr(block_start_x - i + (pCGI->CFI.block_width - 2), block_start_y + j, "  ", pCGI->CFI.bgcolor, pCGI->CFI.fgcolor, 1);
					}
				}
			}
		}
	}
	if (direction == LEFT_TO_RIGHT)//����
	{
		for (int i = 0; i <= 2*true_steps; i+=2)
		{
			gmw_draw_block_by_a_step(pCGI, row_no, col_no, bdi_value, bdi, +i ,0 );//dy==i
			Sleep(20);//����

			//��ԭ��λ�õ�����
			if (i != 2*true_steps)
			{
				for (int j = 0; j < pCGI->CFI.block_high; j++)
				{
					if (((i/2+1) % ((pCGI->CFI.block_width + 2)/2) == 0) && i != 0 && pCGI->CFI.separator)//�зָ���ŵĻ�����Ҫ�ж��Ƿ����
					{
						//test
						cct_showstr(block_start_x + i, block_start_y + j , pCGI->CFI.v_normal, pCGI->CFI.bgcolor, pCGI->CFI.fgcolor, 1);
						//Sleep(100);
					}
					else
					{
						cct_showstr(block_start_x + i, block_start_y + j, "  ", pCGI->CFI.bgcolor, pCGI->CFI.fgcolor, 1);
					}
				}
			}
		}
	}

	return 0; //�˾�ɸ�����Ҫ�޸�
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ������̻����
  ���������const CONSOLE_GRAPHICS_INFO *const pCGI	������ṹָ��
		   int &MAction							��������� CCT_MOUSE_EVENT�����ֵ��Ч��Ϊ MOUSE_ONLY_MOVED/MOUSE_LEFT_BUTTON_CLICK/MOUSE_RIGHT_BUTTON_CLICK ����֮һ
		                                               ������� CCT_KEYBOARD_EVENT�����ֵ��Ч
		   int &MRow								��������� CCT_MOUSE_EVENT �� MAction = MOUSE_ONLY_MOVED/MOUSE_LEFT_BUTTON_CLICK�����ֵ��Ч����ʾ���ѡ�����Ϸ������кţ���0��ʼ��
												  ���������ֵ��Ч�����������Чֵ���´��󣬲��Ǳ������Ĵ�!!!��
		   int &MCol								��������� CCT_MOUSE_EVENT �� MAction = MOUSE_ONLY_MOVED/MOUSE_LEFT_BUTTON_CLICK�����ֵ��Ч����ʾ���ѡ�����Ϸ������кţ���0��ʼ��
												  ���������ֵ��Ч�����������Чֵ���´��󣬲��Ǳ������Ĵ�!!!��
		   int &KeyCode1							��������� CCT_KEYBOARD_EVENT�����ֵ��Ч��Ϊ�����ļ��루���˫���룬��Ϊ��һ����
												  ���������ֵ��Ч�����������Чֵ���´��󣬲��Ǳ������Ĵ�!!!��
		   int &KeyCode2							��������� CCT_KEYBOARD_EVENT�����ֵ��Ч��Ϊ�����ļ��루���˫���룬��Ϊ�ڶ���������ǵ����룬��Ϊ0��
												  ���������ֵ��Ч�����������Чֵ���´��󣬲��Ǳ������Ĵ�!!!��
		   const bool update_lower_status_line		������ƶ�ʱ���Ƿ�Ҫ�ڱ���������ʾ"[��ǰ���] *��*��/λ�÷Ƿ�"����Ϣ��true=��ʾ��false=����ʾ��ȱʡΪtrue��
  �� �� ֵ����������Լ��
		   1�����������ƶ����õ���MRow/MCol�봫�����ͬ(���ָ��΢С���ƶ�)���򲻷��أ�������
							  �õ����зǷ�λ�ã��򲻷��أ����� update_lower_status_line ����������״̬����ʾ"[��ǰ���] λ�÷Ƿ�"
							  �õ���MRow/MCol�봫��Ĳ�ͬ(��������һ���仯)������ update_lower_status_line ����������״̬����ʾ"[��ǰ���] *��*��"���ٷ���MOUSE_ONLY_MOVED����Щ��Ϸ���غ�Ҫ����ɫ��Ĳ�ͬ��ɫ��ʾ��
		   2������ǰ������������ҵ�ǰ���ָ��ͣ��������Ϸ�����*��*���ϣ��򷵻� CCT_MOUSE_EVENT ��MAction Ϊ MOUSE_LEFT_BUTTON_CLICK, MRow Ϊ�кţ�MCol Ϊ�б�
		                          �ҵ�ǰ���ָ��ͣ���ڷǷ����򣨷���Ϸ������Ϸ�����еķָ��ߣ����򲻷��أ����� update_lower_status_line ����������״̬����ʾ"[��ǰ���] λ�÷Ƿ�"
		   3������ǰ�������Ҽ������ж����ָ��ͣ�������Ƿ�Ϸ���ֱ�ӷ��� CCT_MOUSE_EVENT ��MAction Ϊ MOUSE_RIGHT_BUTTON_CLICK, MRow��MColȡ��ǰֵ����Ϊ�������ǵ��Ҽ������Ҫ���꣩
		   4��������¼����ϵ�ĳ������˫���밴��������ֱ�ӷ��� CCT_KEYBOARD_EVENT��KeyCode1/KeyCode2��Ϊ��Ӧ�ļ���ֵ
 ˵    ����ͨ������ cmd_console_tools.cpp �е� read_keyboard_and_mouse ����ʵ��
***************************************************************************/
static int gmw_inner_convert_xy_to_rc(const CONSOLE_GRAPHICS_INFO* const pCGI, int MX, int MY, int& MRow, int& MCol)
{

	int block_start_x0 = pCGI->start_x + 2;
	int block_start_y0 = pCGI->start_y + 1;

	MRow = MCol = -1024; // ��ʼ��Ϊ�Ƿ�λ��

	// ����
	for (int i = 0; i < pCGI->row_num; i++) {
		for (int j = 0; j < pCGI->col_num; j++) {
			int block_start_x = block_start_x0 + j * (pCGI->CFI.block_width + 2 * pCGI->CFI.separator);
			int block_start_y = block_start_y0 + i * (pCGI->CFI.block_high + 1 * pCGI->CFI.separator);

			if (block_start_x <= MX && MX < block_start_x + pCGI->CFI.block_width &&
				block_start_y <= MY && MY < block_start_y + pCGI->CFI.block_high) {
				MRow = i;
				MCol = j;
				return 0;
			}
		}
	}
	return -1;
}

int gmw_read_keyboard_and_mouse(const CONSOLE_GRAPHICS_INFO* const pCGI, int& MAction, int& MRow, int& MCol, int& KeyCode1, int& KeyCode2, const bool update_lower_status_line)
{
	/* ��ֹ��δ���� gmw_init ǰ������������ */
	if (pCGI->inited != CGI_INITED)
		return -1;

	cct_enable_mouse();

	int MX = 0, MY = 0;  //��¼���λ��
	int type;            //�¼�����
	int MRow_new = MRow, MCol_new = MCol;    //������ֵ
	int sign = 0, old_sign = 0;

	while (1) {
		type = cct_read_keyboard_and_mouse(MX, MY, MAction, KeyCode1, KeyCode2);
		if (type == CCT_KEYBOARD_EVENT)
			return type;
		else {
			//�ж��Ҽ�
			if (MAction == MOUSE_RIGHT_BUTTON_CLICK) {
				MRow = MRow_new;
				MCol = MCol_new;
				return CCT_MOUSE_EVENT;
			}
			old_sign = sign;
			//�ж����λ���Ƿ�Ϸ�
			sign = 0;
			if (MX < pCGI->start_x + pCGI->draw_frame_with_row_no * 2 + 2)
				sign = 1;
			if (MX >= pCGI->start_x + pCGI->draw_frame_with_row_no * 2 + pCGI->CFI.bwidth - 2)
				sign = 1;
			if (MY < pCGI->start_y + pCGI->draw_frame_with_col_no + 1)
				sign = 1;
			if (MY >= pCGI->start_y + pCGI->draw_frame_with_col_no + pCGI->CFI.bhigh - 1)
				sign = 1;
			if (pCGI->CFI.separator) {
				if ((MX - pCGI->start_x - pCGI->draw_frame_with_row_no * 2 - 2) % (pCGI->CFI.block_width + 2) >= pCGI->CFI.block_width)
					sign = 1;
				if ((MY - pCGI->start_y - pCGI->draw_frame_with_col_no - 1) % (pCGI->CFI.block_high + 1) >= pCGI->CFI.block_high)
					sign = 1;
			}

			//�ж����
			if (MAction == MOUSE_LEFT_BUTTON_CLICK) {
				if (sign) {
					if (update_lower_status_line && !old_sign) {
						gmw_status_line(pCGI, LOWER_STATUS_LINE, "[��ǰ���] λ�÷Ƿ�                ");
					}
				}
				else {
					return CCT_MOUSE_EVENT;
				}
			}

			//ʣ������ƶ�
			if (sign) {
				if (update_lower_status_line && !old_sign) {
					gmw_status_line(pCGI, LOWER_STATUS_LINE, "[��ǰ���] λ�÷Ƿ�                   ");
				}
			}
			else {
				MCol_new = (MX - pCGI->start_x - pCGI->draw_frame_with_row_no * 2 - 2) / (pCGI->CFI.block_width + pCGI->CFI.separator * 2);
				MRow_new = (MY - pCGI->start_y - pCGI->draw_frame_with_col_no - 1) / (pCGI->CFI.block_high + pCGI->CFI.separator);
				if (MRow_new != MRow || MCol_new != MCol || old_sign) {
					if (update_lower_status_line) {
						char temp[256];
						sprintf(temp, "[��ǰ���] %c��%d��                 ", char('A' + MRow_new), MCol_new);
						gmw_status_line(pCGI, LOWER_STATUS_LINE, temp);
					}
					MRow = MRow_new;
					MCol = MCol_new;
					return CCT_MOUSE_EVENT;
				}
			}
		}
	}

	return CCT_MOUSE_EVENT; //�˾�ɸ�����Ҫ�޸�
}
