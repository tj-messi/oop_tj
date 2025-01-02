/*2351114 朱俊泽 大数据*/
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
		此处可以给出需要的静态全局变量（尽可能少，最好没有）、静态全局只读变量/宏定义（个数不限）等
   -------------------------------------------------- */
//所有的框架都设置成了一个CGI变量，变量内容在gmw.h文件中

/* --------------------------------------------------
		此处可以给出需要的内部辅助工具函数
		1、函数名不限，建议为 gmw_inner_* 
		2、个数不限
		3、必须是static函数，确保只在本源文件中使用
   -------------------------------------------------- */
//设置一个gmw_inner_renew()来实时更新所有参数
void gmw_inner_renew(CONSOLE_GRAPHICS_INFO* const pCGI)
{
	pCGI->start_x = pCGI->extern_left_cols;
	pCGI->start_y = pCGI->extern_up_lines + pCGI->top_status_line;
	//更新总行列
	pCGI->lines = pCGI->extern_up_lines + pCGI->extern_down_lines + pCGI->CFI.bhigh +
		pCGI->SLI.is_top_status_line + pCGI->SLI.is_lower_status_line +
		pCGI->draw_frame_with_col_no + 4;  // 4 行用于额外的UI预留 flag
	pCGI->cols = pCGI->extern_left_cols + pCGI->extern_right_cols + pCGI->CFI.bwidth +
		pCGI->draw_frame_with_row_no * 2 + 1;  // 列数包含左右额外区域和边框

	//主框架高宽
	pCGI->CFI.bhigh = pCGI->CFI.block_high * pCGI->row_num +
		pCGI->CFI.separator * (pCGI->row_num - 1) + 2;
	pCGI->CFI.bwidth = pCGI->CFI.block_width * pCGI->col_num +
		pCGI->CFI.separator * 2 * (pCGI->col_num - 1) + 4;
	//上下补充状态起始位置
	pCGI->SLI.top_start_x = pCGI->extern_left_cols;
	pCGI->SLI.top_start_y = pCGI->extern_up_lines;
	pCGI->SLI.lower_start_x = pCGI->extern_left_cols;
	pCGI->SLI.lower_start_y = pCGI->start_y + pCGI->CFI.bhigh + pCGI->draw_frame_with_col_no;
}
/* ----------------------------------------------- 
		实现下面给出的函数（函数声明不准动）
   ----------------------------------------------- */
/***************************************************************************
  函数名称：
  功    能：设置游戏主框架的行列数
  输入参数：CONSOLE_GRAPHICS_INFO *const pCGI	：整体结构指针
			const int row						：行数(错误则为0，不设上限，人为保证正确性)
			const int col						：列数(错误则为0，不设上限，人为保证正确性)
  返 回 值：
  说    明：1、指消除类游戏的矩形区域的行列值
            2、行列的变化会导致CONSOLE_GRAPHICS_INFO结构体中其它成员值的变化，要处理
***************************************************************************/
int gmw_set_rowcol(CONSOLE_GRAPHICS_INFO *const pCGI, const int row, const int col)
{
	/* 防止在未调用 gmw_init 前调用其它函数 */
	if (pCGI->inited != CGI_INITED)
		return -1;
	//行列
	pCGI->row_num = max(0, row);
	pCGI->col_num = max(0, col);
	//高宽
	pCGI->CFI.bhigh = pCGI->CFI.block_high * pCGI->row_num + pCGI->row_num  * pCGI->CFI.separator + 2- pCGI->CFI.separator;
	pCGI->CFI.bwidth = pCGI->CFI.block_width * pCGI->col_num + pCGI->col_num  * 2 * pCGI->CFI.separator + 4- pCGI->CFI.separator;
	//显示区域
	pCGI->lines = pCGI->extern_up_lines + pCGI->extern_down_lines + pCGI->CFI.bhigh + pCGI->SLI.is_top_status_line + 
		pCGI->SLI.is_lower_status_line + pCGI->draw_frame_with_col_no + 4;
	pCGI->cols = pCGI->extern_left_cols + pCGI->extern_right_cols + pCGI->CFI.bwidth + pCGI->draw_frame_with_row_no * 2 + 1;
	//起点
	pCGI->SLI.lower_start_y = pCGI->extern_up_lines + pCGI->draw_frame_with_col_no + pCGI->SLI.is_top_status_line + pCGI->CFI.bhigh;
	return 0; //此句可根据需要修改
}

/***************************************************************************
  函数名称：
  功    能：设置整个窗口（含游戏区、附加区在内的整个cmd窗口）的颜色
  输入参数：CONSOLE_GRAPHICS_INFO *const pCGI	：整体结构指针
		   const int bg_color					：前景色（缺省COLOR_BLACK）
		   const int fg_color					：背景色（缺省COLOR_WHITE）
		   const bool cascade					：是否级联（缺省为true-级联）
  返 回 值：
  说    明：1、cascade = true时
				同步修改游戏主区域的颜色
				同步修改上下状态栏的正常文本的背景色和前景色，醒目文本的背景色（前景色不变）
			2、不检查颜色值错误及冲突，需要人为保证
				例：颜色非0-15
				    前景色背景色的值一致导致无法看到内容
					前景色正好是状态栏醒目前景色，导致无法看到醒目提示
					...
***************************************************************************/
int gmw_set_color(CONSOLE_GRAPHICS_INFO *const pCGI, const int bgcolor, const int fgcolor, const bool cascade)
{
	/* 防止在未调用 gmw_init 前调用其它函数 */
	if (pCGI->inited != CGI_INITED)
		return -1;
	if (cascade)
	{
		//颜色
		pCGI->area_bgcolor = bgcolor;
		pCGI->area_fgcolor = fgcolor;

		//同步修改游戏主区域的颜色
		//同步修改上下状态栏的正常文本的背景色和前景色，醒目文本的背景色（前景色不变）
		pCGI->CFI.bgcolor = bgcolor;
		pCGI->CFI.fgcolor = fgcolor;

		//上下栏目
		pCGI->SLI.top_normal_bgcolor = bgcolor;
		pCGI->SLI.top_normal_fgcolor = fgcolor;
		pCGI->SLI.top_catchy_bgcolor = bgcolor;
		pCGI->SLI.lower_normal_bgcolor = bgcolor;
		pCGI->SLI.lower_normal_fgcolor = fgcolor;
		pCGI->SLI.lower_catchy_bgcolor = bgcolor;
	}
	else
	{
		//颜色
		pCGI->area_bgcolor = bgcolor;
		pCGI->area_fgcolor = fgcolor;
	}
	
	return 0; //此句可根据需要修改
}

/***************************************************************************
  函数名称：
  功    能：设置窗口的字体
  输入参数：CONSOLE_GRAPHICS_INFO *const pCGI	：整体结构指针
		   const char *fontname					：字体名称（只能是"Terminal"和"新宋体"两种，错误则返回-1，不改变字体）
		   const int fs_high					：字体高度（缺省及错误为16，不设其它限制，人为保证）
		   const int fs_width					：字体高度（缺省及错误为8，不设其它限制，人为保证）
  返 回 值：
  说    明：1、与cmd_console_tools中的setfontsize相似，目前只支持“点阵字体”和“新宋体”
            2、若设置其它字体则直接返回，保持原字体设置不变
***************************************************************************/
int gmw_set_font(CONSOLE_GRAPHICS_INFO *const pCGI, const char *fontname, const int fs_high, const int fs_width)
{
	/* 防止在未调用 gmw_init 前调用其它函数 */
	if (pCGI->inited != CGI_INITED)
		return -1;

	//字体高和宽
	pCGI->CFT.font_size_high = (fs_high <= 0) ? 16 : fs_high;
	pCGI->CFT.font_size_width = (fs_width <= 0) ? 8 : fs_width;

	if (strcmp(fontname, "Terminal") || strcmp(fontname, "新宋体"))
	{
		strcpy(pCGI->CFT.font_type, fontname);
	}
	else
		return -1;

	return 0; //此句可根据需要修改
}

/***************************************************************************
  函数名称：
  功    能：设置延时
  输入参数：CONSOLE_GRAPHICS_INFO *const pCGI	：整体结构指针
		   const int type						：延时的类型（目前为3种）
		   const int delay_ms					：以ms为单位的延时
			   画边框的延时：0 ~ 不设上限，人为保证正确（<0则置0）
			   画色块的延时：0 ~ 不设上限，人为保证正确（<0则置0）
			   色块移动的延时：BLOCK_MOVED_DELAY_MS ~ 不设上限，人为保证正确（ <BLOCK_MOVED_DELAY_MS 则置 BLOCK_MOVED_DELAY_MS）
  返 回 值：
  说    明：
***************************************************************************/
int gmw_set_delay(CONSOLE_GRAPHICS_INFO *const pCGI, const int type, const int delay_ms)
{
	/* 防止在未调用 gmw_init 前调用其它函数 */
	if (pCGI->inited != CGI_INITED)
		return -1;
	/*
	DELAY_OF_DRAW_FRAME		0	//画游戏主框架时延时
	DELAY_OF_DRAW_BLOCK		1	//画色块时的延时
	DELAY_OF_BLOCK_MOVED	2	//色块移动时延时
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


	return 0; //此句可根据需要修改
}

/***************************************************************************
  函数名称：
  输入参数：设置游戏主框架结构之外需要保留的额外区域
  功    能：CONSOLE_GRAPHICS_INFO *const pCGI	：
		   const int up_lines					：上部额外的行（缺省及错误为0，不设上限，人为保证）
		   const int down_lines				：下部额外的行（缺省及错误为0，不设上限，人为保证）
		   const int left_cols					：左边额外的列（缺省及错误为0，不设上限，人为保证）
		   const int right_cols				：右边额外的列（缺省及错误为0，不设上限，人为保证）
  返 回 值：
  说    明：额外行列的变化会导致CONSOLE_GRAPHICS_INFO结构体中其它成员值的变化，要处理
***************************************************************************/
int gmw_set_ext_rowcol(CONSOLE_GRAPHICS_INFO *const pCGI, const int up_lines, const int down_lines, const int left_cols, const int right_cols)
{
	/* 防止在未调用 gmw_init 前调用其它函数 */
	if (pCGI->inited != CGI_INITED)
		return -1;

	//上下左右额外行
	pCGI->extern_up_lines = max(0, up_lines);
	pCGI->extern_down_lines = max(0, down_lines);
	pCGI->extern_left_cols = max(0, left_cols);
	pCGI->extern_right_cols = max(0, right_cols);

	pCGI->start_x = pCGI->extern_left_cols;
	pCGI->start_y = pCGI->extern_up_lines + pCGI->top_status_line;
	//更新总行列
	pCGI->lines = pCGI->extern_up_lines + pCGI->extern_down_lines + pCGI->CFI.bhigh +
		pCGI->SLI.is_top_status_line + pCGI->SLI.is_lower_status_line +
		pCGI->draw_frame_with_col_no + 4;  // 4 行用于额外的UI预留 flag
	pCGI->cols = pCGI->extern_left_cols + pCGI->extern_right_cols + pCGI->CFI.bwidth +
		pCGI->draw_frame_with_row_no * 2 + 1;  // 列数包含左右额外区域和边框

	//主框架高宽
	pCGI->CFI.bhigh = pCGI->CFI.block_high * pCGI->row_num +
		pCGI->CFI.separator * (pCGI->row_num - 1) + 2;
	pCGI->CFI.bwidth = pCGI->CFI.block_width * pCGI->col_num +
		pCGI->CFI.separator * 2 * (pCGI->col_num - 1) + 4;
	//上下补充状态起始位置
	pCGI->SLI.top_start_x = pCGI->extern_left_cols;
	pCGI->SLI.top_start_y = pCGI->extern_up_lines;
	pCGI->SLI.lower_start_x = pCGI->extern_left_cols;
	pCGI->SLI.lower_start_y = pCGI->start_y + pCGI->CFI.bhigh + pCGI->draw_frame_with_col_no;

	return 0; //此句可根据需要修改
}

/***************************************************************************
  函数名称：
  功    能：填充 CONSOLE_FRAME_TYPE 结构中的11种线型（缺省4种）
  输入参数：CONSOLE_GRAPHICS_INFO *const pCGI	：整体结构指针
			const int type						：1 - 全线 2 - 全单线 3 - 横双竖单 4 - 横单竖双
  返 回 值：
  说    明：
***************************************************************************/
int gmw_set_frame_default_linetype(CONSOLE_GRAPHICS_INFO *const pCGI, const int type)
{
	/* 防止在未调用 gmw_init 前调用其它函数 */
	if (pCGI->inited != CGI_INITED)
		return -1;

	bool flag=false;
	if (type == 1)
	{
		strcpy(pCGI->CFI.top_left, "╔");
		strcpy(pCGI->CFI.lower_left, "╚");
		strcpy(pCGI->CFI.top_right, "╗");
		strcpy(pCGI->CFI.lower_right, "╝");
		strcpy(pCGI->CFI.h_normal, "═");
		strcpy(pCGI->CFI.v_normal, "║");
		strcpy(pCGI->CFI.h_top_separator, "╦");
		strcpy(pCGI->CFI.h_lower_separator, "╩");
		strcpy(pCGI->CFI.v_left_separator, "╠");
		strcpy(pCGI->CFI.v_right_separator, "╣");
		strcpy(pCGI->CFI.mid_separator, "╬");
		flag = true;
	}
	else if (type == 2)
	{
		strcpy(pCGI->CFI.top_left, "┌");
		strcpy(pCGI->CFI.lower_left, "└");
		strcpy(pCGI->CFI.top_right, "┐");
		strcpy(pCGI->CFI.lower_right, "┘");
		strcpy(pCGI->CFI.h_normal, "─");
		strcpy(pCGI->CFI.v_normal, "│");
		strcpy(pCGI->CFI.h_top_separator, "┬");
		strcpy(pCGI->CFI.h_lower_separator, "┴");
		strcpy(pCGI->CFI.v_left_separator, "├");
		strcpy(pCGI->CFI.v_right_separator, "┤");
		strcpy(pCGI->CFI.mid_separator, "┼");
		flag = true;
	}
	else if (type == 3)
	{
		strcpy(pCGI->CFI.top_left, "╒");
		strcpy(pCGI->CFI.lower_left, "╘");
		strcpy(pCGI->CFI.top_right, "╕");
		strcpy(pCGI->CFI.lower_right, "╛");
		strcpy(pCGI->CFI.h_normal, "═");
		strcpy(pCGI->CFI.v_normal, "│");
		strcpy(pCGI->CFI.h_top_separator, "╤");
		strcpy(pCGI->CFI.h_lower_separator, "╧");
		strcpy(pCGI->CFI.v_left_separator, "╞");
		strcpy(pCGI->CFI.v_right_separator, "╡");
		strcpy(pCGI->CFI.mid_separator, "╪");
		flag = true;
	}
	else
	{
		strcpy(pCGI->CFI.top_left, "╓");
		strcpy(pCGI->CFI.lower_left, "╙");
		strcpy(pCGI->CFI.top_right, "╖");
		strcpy(pCGI->CFI.lower_right, "╜");
		strcpy(pCGI->CFI.h_normal, "─");
		strcpy(pCGI->CFI.v_normal, "║");
		strcpy(pCGI->CFI.h_top_separator, "╥");
		strcpy(pCGI->CFI.h_lower_separator, "╨");
		strcpy(pCGI->CFI.v_left_separator, "╟");
		strcpy(pCGI->CFI.v_right_separator, "╢");
		strcpy(pCGI->CFI.mid_separator, "╫");
		flag = true;
	}
	if (!flag)
	{
		//cpy不成功
		cout << "不成功" << endl;
		//std::sleep(500);
	}


	return 0; //此句可根据需要修改
}

/***************************************************************************
  函数名称：
  功    能：填充 CONSOLE_FRAME_TYPE 结构中的11种线型
  输入参数：CONSOLE_GRAPHICS_INFO *const pCGI	：整体结构指针
			const char *...						：共11种，具体见.h，此处略
  返 回 值：
  说    明：约定为一个中文制表符，可以使用其它内容，人为保证2字节
			1、超过2字节则只取前2字节
			2、如果给NULL，用两个空格替代
			3、如果给1字节，则补一个空格，如果因此而导致显示乱，不算错
***************************************************************************/
int gmw_set_frame_linetype(CONSOLE_GRAPHICS_INFO *const pCGI, const char *top_left, const char *lower_left, const char *top_right,
	const char *lower_right, const char *h_normal, const char *v_normal, const char *h_top_separator,
	const char *h_lower_separator, const char *v_left_separator, const char *v_right_separator, const char *mid_separator)
{
	/* 防止在未调用 gmw_init 前调用其它函数 */
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
			// 如果传入 NULL，用两个空格替代
			strcpy(dst[i], "  ");
		}
		else {
			int src_len = strlen(src[i]);

			// 如果是1字节字符，补一个空格
			if (src_len == 1) {
				dst[i][0] = src[i][0];
				dst[i][1] = ' ';
				dst[i][2] = '\0';
			}
			// 如果恰好是2字节，直接复制
			// // 如果超过2字节，截取前2字节
			else {
				dst[i][0] = src[i][0];
				dst[i][1] = src[i][1];
				dst[i][2] = '\0';
			}
		}
	}

	return 0; //此句可根据需要修改
}

/***************************************************************************
  函数名称：
  功    能：填充 CONSOLE_FRAME_TYPE 结构中的色块数量大小、是否需要分隔线等
  输入参数：输入参数：CONSOLE_GRAPHICS_INFO *const pCGI	：整体结构指针
			const int block_width						：宽度（错误及缺省2，因为约定表格线为中文制表符，如果给出奇数，要+1）
			const int block_high						：高度（错误及缺省1）
			const bool separator						：是否需要分隔线（缺省为true，需要分隔线）
  返 回 值：
  说    明：框架大小/是否需要分隔线等的变化会导致CONSOLE_GRAPHICS_INFO结构体中其它成员值的变化，要处理
***************************************************************************/
int gmw_set_frame_style(CONSOLE_GRAPHICS_INFO *const pCGI, const int block_width, const int block_high, const bool separator)
{
	/* 防止在未调用 gmw_init 前调用其它函数 */
	if (pCGI->inited != CGI_INITED)
		return -1;
	//宽高
	pCGI->CFI.block_high = max(1, block_high);
	pCGI->CFI.block_width = max(2, block_width);
	if (block_width % 2 == 1)
	{
		pCGI->CFI.block_width++;
	}

	//是否需要分割
	pCGI->CFI.separator = separator;

	//主框架高宽
	pCGI->CFI.bhigh = pCGI->CFI.block_high * pCGI->row_num + pCGI->CFI.separator * (pCGI->row_num - 1) + 2;
	pCGI->CFI.bwidth = pCGI->CFI.block_width * pCGI->col_num + pCGI->CFI.separator * 2 * (pCGI->col_num - 1) + 4;

	pCGI->lines = pCGI->extern_up_lines + pCGI->extern_down_lines + pCGI->CFI.bhigh
							+ pCGI->draw_frame_with_col_no + pCGI->top_status_line + pCGI->lower_status_line + 4;
	pCGI->cols = pCGI->extern_left_cols + pCGI->extern_right_cols + pCGI->CFI.bwidth
						+ pCGI->draw_frame_with_row_no * 2 + 1;

	pCGI->SLI.lower_start_y = pCGI->start_y + pCGI->CFI.bhigh + pCGI->draw_frame_with_col_no;

	return 0; //此句可根据需要修改
}

/***************************************************************************
  函数名称：
  功    能：填充 CONSOLE_BORDER_TYPE 结构中的颜色
  输入参数：CONSOLE_GRAPHICS_INFO *const pCGI	：整体结构指针
			const int bg_color					：背景色（缺省 -1表示用窗口背景色）
			const int fg_color					：前景色（缺省 -1表示用窗口前景色）
  返 回 值：
  说    明：不检查颜色值错误及冲突，需要人为保证
				例：颜色非0-15，前景色背景色的值一致导致无法看到内容等
***************************************************************************/
int gmw_set_frame_color(CONSOLE_GRAPHICS_INFO *const pCGI, const int bgcolor, const int fgcolor)
{
	/* 防止在未调用 gmw_init 前调用其它函数 */
	if (pCGI->inited != CGI_INITED)
		return -1;

	//缺省 -1表示用窗口背景色--不变的意思
	pCGI->CFI.bgcolor = bgcolor < 0 ? pCGI->area_bgcolor : bgcolor;
	pCGI->CFI.fgcolor = fgcolor < 0 ? pCGI->area_fgcolor : fgcolor;

	return 0; //此句可根据需要修改
}

/***************************************************************************
  函数名称：
  功    能：填充 CONSOLE_BLOCK_INFO 结构中的6种线型（缺省4种）
  输入参数：CONSOLE_GRAPHICS_INFO *const pCGI	：整体结构指针
			const int type						：1 - 全双线 2 - 全单线 3 - 横双竖单 4 - 横单竖双
  返 回 值：
  说    明：
***************************************************************************/
int gmw_set_block_default_linetype(CONSOLE_GRAPHICS_INFO *const pCGI, const int type)
{
	/* 防止在未调用 gmw_init 前调用其它函数 */
	if (pCGI->inited != CGI_INITED)
		return -1;

	bool flag = false;
	if (type == 1)
	{
		strcpy(pCGI->CBI.top_left, "╔");
		strcpy(pCGI->CBI.lower_left, "╚");
		strcpy(pCGI->CBI.top_right, "╗");
		strcpy(pCGI->CBI.lower_right, "╝");
		strcpy(pCGI->CBI.h_normal, "═");
		strcpy(pCGI->CBI.v_normal, "║");
		flag = true;
	}
	else if (type == 2)
	{
		strcpy(pCGI->CBI.top_left, "┏");
		strcpy(pCGI->CBI.lower_left, "┗");
		strcpy(pCGI->CBI.top_right, "┓");
		strcpy(pCGI->CBI.lower_right, "┛");
		strcpy(pCGI->CBI.h_normal, "━");
		strcpy(pCGI->CBI.v_normal, "┃");
		flag = true;
	}
	else if (type == 3)
	{
		strcpy(pCGI->CBI.top_left, "╒");
		strcpy(pCGI->CBI.lower_left, "╘");
		strcpy(pCGI->CBI.top_right, "╕");
		strcpy(pCGI->CBI.lower_right, "╛");
		strcpy(pCGI->CBI.h_normal, "═");
		strcpy(pCGI->CBI.v_normal, "│");
		flag = true;
	}
	else
	{
		strcpy(pCGI->CBI.top_left, "╓");
		strcpy(pCGI->CBI.lower_left, "╙");
		strcpy(pCGI->CBI.top_right, "╖");
		strcpy(pCGI->CBI.lower_right, "╜");
		strcpy(pCGI->CBI.h_normal, "─");
		strcpy(pCGI->CBI.v_normal, "║");
		flag = true;
	}
	if (!flag)
	{
		//cpy不成功
		cout << "不成功" << endl;
		//std::sleep(500);
	}

	return 0; //此句可根据需要修改
}

/***************************************************************************
  函数名称：
  功    能：填充 CONSOLE_BLOCK_INFO 结构中的6种线型
  输入参数：CONSOLE_GRAPHICS_INFO *const pCGI	：整体结构指针
		   const char *...					：共6种，具体见.h，此处略
  返 回 值：
  说    明：约定为一个中文制表符，可以使用其它内容，人为保证2字节
			1、超过2字节则只取前2字节
			2、如果给NULL，用两个空格替代
			3、如果给1字节，则补一个空格，如果因此而导致显示乱，不算错
***************************************************************************/
int gmw_set_block_linetype(CONSOLE_GRAPHICS_INFO *const pCGI, const char *top_left, const char *lower_left, const char *top_right, const char *lower_right, const char *h_normal, const char *v_normal)
{
	/* 防止在未调用 gmw_init 前调用其它函数 */
	if (pCGI->inited != CGI_INITED)
		return -1;

	const char* src[] = { top_left,lower_left, top_right, lower_right , h_normal , v_normal };
	char* dst[] = { pCGI->CFI.top_left,pCGI->CFI.lower_left, pCGI->CFI.top_right, pCGI->CFI.lower_right ,pCGI->CFI.h_normal ,
						 pCGI->CFI.v_normal,pCGI->CFI.h_top_separator ,pCGI->CFI.h_lower_separator
						 , pCGI->CFI.v_left_separator, pCGI->CFI.v_right_separator,pCGI->CFI.mid_separator };

	for (int i = 0; i <= 5; i++)
	{
		if (src[i] == NULL) {
			// 如果传入 NULL，用两个空格替代
			strcpy(dst[i], "  ");
		}
		else {
			int src_len = strlen(src[i]);

			// 如果是1字节字符，补一个空格
			if (src_len == 1) {
				dst[i][0] = src[i][0];
				dst[i][1] = ' ';
				dst[i][2] = '\0';
			}
			// 如果恰好是2字节，直接复制
			// // 如果超过2字节，截取前2字节
			else {
				dst[i][0] = src[i][0];
				dst[i][1] = src[i][1];
				dst[i][2] = '\0';
			}
		}
	}

	return 0; //此句可根据需要修改
}

/***************************************************************************
  函数名称：
  功    能：设置每个游戏色块(彩球)是否需要小边框
  输入参数：CONSOLE_GRAPHICS_INFO *const pCGI	：整体结构指针
		   const bool on_off					：true - 需要 flase - 不需要（缺省false）
  返 回 值：
  说    明：边框约定为中文制表符，双线
***************************************************************************/
int gmw_set_block_border_switch(CONSOLE_GRAPHICS_INFO *const pCGI, const bool on_off)
{
	/* 防止在未调用 gmw_init 前调用其它函数 */
	if (pCGI->inited != CGI_INITED)
		return -1;

	pCGI->CBI.block_border = on_off;

	return 0; //此句可根据需要修改
}

/***************************************************************************
  函数名称：
  功    能：设置是否显示上下状态栏
  输入参数：CONSOLE_GRAPHICS_INFO *const pCGI	：整体结构指针
			const int type						：状态栏类型（上/下）
			const bool on_off					：true - 需要 flase - 不需要（缺省true）
  返 回 值：
  说    明：1、状态栏的相关约定如下：
			   1.1、上状态栏只能一行，在主区域最上方框线/列标的上面，为主区域的最开始一行（主区域的左上角坐标就是上状态栏的坐标）
			   1.2、下状态栏只能一行，在主区域最下方框线的下面
			   1.3、状态栏的宽度为主区域宽度，如果信息过长则截断
		   2、行列的变化会导致CONSOLE_GRAPHICS_INFO结构体中其它成员值的变化，要处理
***************************************************************************/
int gmw_set_status_line_switch(CONSOLE_GRAPHICS_INFO *const pCGI, const int type, const bool on_off)
{
	/* 防止在未调用 gmw_init 前调用其它函数 */
	if (pCGI->inited != CGI_INITED)
		return -1;

	if (type == TOP_STATUS_LINE)
	{
		pCGI->SLI.is_top_status_line = on_off;
		pCGI->top_status_line = on_off;
		/* 顶部起始位置 */
	pCGI->start_y = pCGI->extern_up_lines + (on_off ? 1 : 0);
	pCGI->SLI.top_start_x = pCGI->start_x;
	pCGI->SLI.top_start_y = pCGI->start_y - 1;
	/* 底部起始位置 */
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

	return 0; //此句可根据需要修改
}

/***************************************************************************
  函数名称：
  功    能：设置上下状态栏的颜色
  输入参数：CONSOLE_GRAPHICS_INFO *const pCGI	：整体结构指针
			const int type						：状态栏类型（上/下）
			const int normal_bgcolor			：正常文本背景色（缺省 -1表示使用窗口背景色）
			const int normal_fgcolor			：正常文本前景色（缺省 -1表示使用窗口前景色）
			const int catchy_bgcolor			：醒目文本背景色（缺省 -1表示使用窗口背景色）
			const int catchy_fgcolor			：醒目文本前景色（缺省 -1表示使用亮黄色）
  输入参数：
  返 回 值：
  说    明：不检查颜色值错误及冲突，需要人为保证
				例：颜色非0-15，前景色背景色的值一致导致无法看到内容等
***************************************************************************/
int gmw_set_status_line_color(CONSOLE_GRAPHICS_INFO *const pCGI, const int type, const int normal_bgcolor, const int normal_fgcolor, const int catchy_bgcolor, const int catchy_fgcolor)
{
	/* 防止在未调用 gmw_init 前调用其它函数 */
	if (pCGI->inited != CGI_INITED)
		return -1;

	if (type == TOP_STATUS_LINE)
	{
		pCGI->SLI.top_normal_bgcolor = normal_bgcolor < 0 ? pCGI->area_bgcolor : normal_bgcolor;
		pCGI->SLI.top_catchy_bgcolor = catchy_bgcolor < 0 ? pCGI->area_bgcolor : catchy_bgcolor;
		pCGI->SLI.top_normal_fgcolor = normal_fgcolor < 0 ? pCGI->area_fgcolor : normal_fgcolor;
		//醒目文本前景色（缺省 -1表示使用亮黄色）
		pCGI->SLI.top_catchy_fgcolor = catchy_fgcolor < 0 ? COLOR_HYELLOW : catchy_fgcolor;
	}

	if (type == LOWER_STATUS_LINE)
	{
		pCGI->SLI.lower_normal_bgcolor = normal_bgcolor < 0 ? pCGI->area_bgcolor : normal_bgcolor;
		pCGI->SLI.lower_catchy_bgcolor = catchy_bgcolor < 0 ? pCGI->area_bgcolor : catchy_bgcolor;
		pCGI->SLI.lower_normal_fgcolor = normal_fgcolor < 0 ? pCGI->area_fgcolor : normal_fgcolor;
		//醒目文本前景色（缺省 -1表示使用亮黄色）
		pCGI->SLI.lower_catchy_fgcolor = catchy_fgcolor < 0 ? COLOR_HYELLOW : catchy_fgcolor;
	}

	return 0; //此句可根据需要修改
}

/***************************************************************************
  函数名称：
  功    能：设置是否显示行号
  输入参数：CONSOLE_GRAPHICS_INFO *const pCGI	：整体结构指针
			const bool on_off					：true - 显示 flase - 不显示（缺省false）
  返 回 值：
  说    明：1、行号约定为字母A开始连续排列（如果超过26，则从a开始，超过52的统一为*，实际应用不可能）
            2、是否显示行号的变化会导致CONSOLE_GRAPHICS_INFO结构体中其它成员值的变化，要处理
***************************************************************************/
int gmw_set_rowno_switch(CONSOLE_GRAPHICS_INFO *const pCGI, const bool on_off)
{
	/* 防止在未调用 gmw_init 前调用其它函数 */
	if (pCGI->inited != CGI_INITED)
		return -1;

	pCGI->draw_frame_with_row_no = false;
	pCGI->draw_frame_with_row_no = on_off;

	pCGI->lines = pCGI->extern_up_lines + pCGI->extern_down_lines +
		pCGI->draw_frame_with_col_no + pCGI->CFI.bhigh +
		pCGI->top_status_line + pCGI->lower_status_line + 4;

	pCGI->cols = pCGI->extern_left_cols + pCGI->extern_right_cols +
		(pCGI->draw_frame_with_row_no ? 2 : 0) +  /* flag 行号需要额外两列 flag*/
		pCGI->CFI.bwidth + 1;

	pCGI->SLI.lower_start_y = pCGI->start_y + pCGI->CFI.bhigh + pCGI->draw_frame_with_col_no;

	return 0; //此句可根据需要修改
}

/***************************************************************************
  函数名称：
  功    能：设置是否显示列标
  输入参数：CONSOLE_GRAPHICS_INFO *const pCGI	：整体结构指针
			const bool on_off					：true - 显示 flase - 不显示（缺省false）
  返 回 值：
  说    明：1、列标约定为数字0开始连续排列（数字0-99，超过99统一为**，实际应用不可能）
            2、是否显示列标的变化会导致CONSOLE_GRAPHICS_INFO结构体中其它成员值的变化，要处理
***************************************************************************/
int gmw_set_colno_switch(CONSOLE_GRAPHICS_INFO *const pCGI, const bool on_off)
{
	/* 防止在未调用 gmw_init 前调用其它函数 */
	if (pCGI->inited != CGI_INITED)
		return -1;
	pCGI->draw_frame_with_col_no = false;
	pCGI->draw_frame_with_col_no = on_off;

	pCGI->lines = pCGI->extern_up_lines + pCGI->extern_down_lines +
		pCGI->CFI.bhigh + pCGI->SLI.is_top_status_line +
		pCGI->SLI.is_lower_status_line +
		(on_off ? 1 : 0) + 4;  /* 列标增加1行flag */

	pCGI->cols = pCGI->extern_left_cols + pCGI->extern_right_cols +
		pCGI->draw_frame_with_row_no * 2 + pCGI->CFI.bwidth + 1;

	/* 底部起始位置 */
	pCGI->SLI.lower_start_y = pCGI->start_y + pCGI->CFI.bhigh + (on_off ? 1 : 0);


	return 0; //此句可根据需要修改
}

/***************************************************************************
  函数名称：
  功    能：打印 CONSOLE_GRAPHICS_INFO 结构体中的各成员值
  输入参数：
  返 回 值：
  说    明：1、仅供调试用，打印格式自定义
            2、本函数测试用例中未调用过，可以不实现
***************************************************************************/
int gmw_print(const CONSOLE_GRAPHICS_INFO *const pCGI)
{
	/* 防止在未调用 gmw_init 前调用其它函数 */
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

	return 0; //此句可根据需要修改
}

/***************************************************************************
  函数名称：
  功    能：将 CONSOLE_GRAPHICS_INFO 结构体用缺省值进行初始化
  输入参数：CONSOLE_GRAPHICS_INFO *const pCGI：整体结构指针
		   const int row					：游戏区域色块行数（缺省10）
		   const int col					：游戏区域色块列数（缺省10）
		   const int bgcolor				：整个窗口背景色（缺省 COLOR_BLACK）
		   const int fgcolor				：整个窗口背景色（缺省 COLOR_WHITE）
  返 回 值：
  说    明：窗口背景黑/前景白，点阵16*8，上下左右无额外行列，上下状态栏均有，无行号/列标，框架线型为双线，色块宽度2/高度1/无小边框，颜色略
***************************************************************************/
int gmw_init(CONSOLE_GRAPHICS_INFO *const pCGI, const int row, const int col, const int bgcolor, const int fgcolor)
{
	/* 首先置标记 */
	pCGI->inited = CGI_INITED;

	//用默认值调用上方所有函数，从h头文件寻找就可以了
	gmw_set_rowcol(pCGI, row, col);
	gmw_set_font(pCGI,"新宋体");
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

	return 0; //此句可根据需要修改
}

/***************************************************************************
  函数名称：
  功    能：画主游戏框架
  输入参数：const CONSOLE_GRAPHICS_INFO *const pCGI	：整体结构指针
  返 回 值：
  说    明：具体可参考demo的效果
***************************************************************************/
int gmw_draw_frame(const CONSOLE_GRAPHICS_INFO *const pCGI)
{
	/* 防止在未调用 gmw_init 前调用其它函数 */
	if (pCGI->inited != CGI_INITED)
		return -1;

	//用于获取目前的希望输出坐标x和y来使用showstr
	int x, y;

	cct_setfontsize(pCGI->CFT.font_type, pCGI->CFT.font_size_high);
	cct_setconsoleborder(pCGI->cols, pCGI->lines);
	cct_setcolor(pCGI->area_bgcolor, pCGI->area_fgcolor);

	cct_cls();

	//是否需要列标
	if (pCGI->draw_frame_with_col_no)
	{
		cct_gotoxy(pCGI->extern_left_cols + pCGI->draw_frame_with_row_no * 2 + pCGI->CFI.block_width / 2 + 1,
				   pCGI->extern_up_lines + pCGI->SLI.is_top_status_line);//直接+1行往下
		for (int j = 0; j < pCGI->col_num; j++)
		{
			if (j < 100)
			{
				cout << setw(pCGI->CFI.block_width + 2 * pCGI->CFI.separator) << setiosflags(ios::left) << (j >= 100 ? char('*') : j);//超过100输出*
			}
			else
			{
				cout << setw(pCGI->CFI.block_width + 2 * pCGI->CFI.separator) << setiosflags(ios::left) << "**";
			}
		}
	}

	//首行打印
	cct_setcolor(pCGI->CFI.bgcolor, pCGI->CFI.fgcolor);
	cct_gotoxy(pCGI->extern_left_cols + pCGI->draw_frame_with_row_no * 2, 
			   pCGI->extern_up_lines + pCGI->draw_frame_with_col_no + pCGI->SLI.is_top_status_line);
	//左上
	cct_getxy(x, y);
	cct_showstr(x, y, pCGI->CFI.top_left, pCGI->CFI.bgcolor, pCGI->CFI.fgcolor, 1);
	//上中间
	for (int i = 0; i < pCGI->col_num; i++)
	{
		//如果有间隔
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
	//右上
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
	//此时x,y指向第一行边界的最后一个点

	//中间的所有行
	
	for (int i = 0; i < pCGI->row_num; i++)
	{
		for (int ii = 0; ii < pCGI->CFI.block_high; ii++)//每一个block的每一行
		{
			//可能会有行标
			if (pCGI->draw_frame_with_row_no)
			{	
				if ((ii == (pCGI->CFI.block_high - 1) / 2))//到了要出行标的时候
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
			cct_getxy(x, y);//此时x，y应该是每一行的第一个元素
			cct_showstr(x, y, pCGI->CFI.v_normal, (*pCGI).CFI.bgcolor,(*pCGI).CFI.fgcolor,1);

			for (int j = 0; j < pCGI->col_num; j++) {
				for (int k = 0; k < pCGI->CFI.block_width; k +=2)
				{
					cout << "  ";//中文字符2个一格
				}
				if (pCGI->CFI.separator)//如果需要间隙或者到了右边界
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
		
		if (pCGI->CFI.separator)//中间分割符号
		{
			cct_setcolor((*pCGI).CFI.bgcolor, (*pCGI).CFI.fgcolor);
			cct_gotoxy(pCGI->extern_left_cols + pCGI->draw_frame_with_row_no * 2, 
					   pCGI->SLI.is_top_status_line + pCGI->extern_up_lines + pCGI->draw_frame_with_col_no +
				       1 + (i + 1) * pCGI->CFI.block_high + i * pCGI->CFI.separator);
			cct_getxy(x, y);
			cct_showstr(x, y, pCGI->CFI.v_left_separator, (*pCGI).CFI.bgcolor, (*pCGI).CFI.fgcolor, 1);//左分割

			for (int j = 0; j < pCGI->col_num; j++) {
				for (int k = 0; k < pCGI->CFI.block_width; k += 2)
				{
					x += 2;
					cct_showstr(x, y, pCGI->CFI.h_normal, (*pCGI).CFI.bgcolor, (*pCGI).CFI.fgcolor, 1);
				}
				cct_getxy(x, y);
				cct_showstr(x, y, pCGI->CFI.mid_separator, (*pCGI).CFI.bgcolor, (*pCGI).CFI.fgcolor, 1);  // 输出中间分隔符
				Sleep(pCGI->delay_of_draw_frame);
			}
			cct_getxy(x, y);
			cct_showstr(x-2, y, pCGI->CFI.v_right_separator, (*pCGI).CFI.bgcolor, (*pCGI).CFI.fgcolor, 1);//右分割
			//现在光标应该是在每一行最后一列，下一次需要重新定位
		}

	}

	//最后一行
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

	return 0; //此句可根据需要修改
}

/***************************************************************************
  函数名称：
  功    能：在状态栏上显示信息
  输入参数：const CONSOLE_GRAPHICS_INFO *const pCGI	：整体结构指针
		   const int type							：指定是上/下状态栏
		   const char *msg						：正常信息
		   const char *catchy_msg					：需要特别标注的信息（在正常信息前显示）
  返 回 值：
  说    明：1、输出宽度限定为主框架的宽度（含行号列标位置），超出则截去
            2、如果最后一个字符是某汉字的前半个，会导致后面乱码，要处理
***************************************************************************/
int gmw_status_line(const CONSOLE_GRAPHICS_INFO *const pCGI, const int type, const char *msg, const char *catchy_msg)
{
	/* 防止在未调用 gmw_init 前调用其它函数 */
	if (pCGI->inited != CGI_INITED)
		return -1;

	int x, y;//用于记录光标位置x，y
	int restrict_width = 2 * pCGI->draw_frame_with_row_no + pCGI->CFI.bwidth;//长度的限制

	char* new_catchy_msg = new(nothrow) char[restrict_width + 1]();
	char* new_msg = new(nothrow) char[restrict_width + 1]();

	const char* src[] = { catchy_msg,msg };
	char* dst[] = { new_catchy_msg, new_msg };

	//限制长度，控制最后一个输出的半个汉字问题
	for (int i = 0; i <= 1; i++)
	{
		if (src[i] == NULL)
		{
			strcpy(dst[i], "");
			continue;
		}

		strncpy(dst[i], src[i], restrict_width);
		dst[i][restrict_width] = '\0';

		char* last = dst[i] + strlen(dst[i]) - 1; // 指向最后一个字符
		if ((unsigned char)*last > 127) { // 如果是汉字
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

	if (type == TOP_STATUS_LINE)//上状态栏
	{
		if (!pCGI->SLI.is_top_status_line)//上状态栏不显示
			return 0;
		cct_gotoxy(pCGI->SLI.top_start_x, pCGI->SLI.top_start_y);
		cct_setcolor(pCGI->SLI.top_catchy_bgcolor, pCGI->SLI.top_catchy_fgcolor);
		cct_getxy(x, y);
		cct_showstr(x, y, new_catchy_msg, pCGI->SLI.top_catchy_bgcolor, pCGI->SLI.top_catchy_fgcolor, 1);

		cct_setcolor(pCGI->SLI.top_normal_bgcolor, pCGI->SLI.top_normal_fgcolor);
		cct_getxy(x, y);
		cct_showstr(x, y, new_msg, pCGI->SLI.top_normal_bgcolor, pCGI->SLI.top_normal_fgcolor, 1);
	}
	else//下状态栏
	{
		if (!pCGI->SLI.is_lower_status_line)//下状态栏不显示
			return 0;
		cct_gotoxy(pCGI->SLI.lower_start_x, pCGI->SLI.lower_start_y);
		cct_setcolor(pCGI->SLI.lower_catchy_bgcolor, pCGI->SLI.lower_catchy_fgcolor);
		cct_getxy(x, y);
		cct_showstr(x, y, new_catchy_msg, pCGI->SLI.lower_catchy_bgcolor, pCGI->SLI.lower_catchy_fgcolor, 1);

		cct_setcolor(pCGI->SLI.lower_normal_bgcolor, pCGI->SLI.lower_normal_fgcolor);
		cct_getxy(x, y);
		cct_showstr(x, y, new_msg, pCGI->SLI.lower_normal_bgcolor, pCGI->SLI.lower_normal_fgcolor, 1);
	}

	return 0; //此句可根据需要修改
}

/***************************************************************************
  函数名称：
  功    能：显示某一个色块(内容为字符串，坐标为row/col)
  输入参数：const CONSOLE_GRAPHICS_INFO *const pCGI	：整体结构指针
		   const int row_no						：行号（从0开始，人为保证正确性，程序不检查）
		   const int col_no						：列号（从0开始，人为保证正确性，程序不检查）
		   const int bdi_value						：需要显示的值
		   const BLOCK_DISPLAY_INFO *const bdi		：存放该值对应的显示信息的结构体数组
  返 回 值：
  说    明：1、BLOCK_DISPLAY_INFO 的含义见头文件，用法参考测试样例
            2、bdi_value为 BDI_VALUE_BLANK 表示空白块，要特殊处理
***************************************************************************/
int gmw_draw_block(const CONSOLE_GRAPHICS_INFO *const pCGI, const int row_no, const int col_no, const int bdi_value, const BLOCK_DISPLAY_INFO *const bdi)
{
	/* 防止在未调用 gmw_init 前调用其它函数 */
	if (pCGI->inited != CGI_INITED)
		return -1;

	//bdi从尾部读入反向的读入
	/*
	typedef struct _block_display_info_ {
		const int   value;	//要显示的内部数组值
		const int   bgcolor;	//-1表示用游戏区域背景色
		const int   fgcolor;	//-1表示用游戏区域前景色
		const char* content;	//内部数组值对应的图形（如果为NULL，则直接显示内部数组的值）
	} BLOCK_DISPLAY_INFO;
	*/

	//存贮使用showstr
	int x, y;

	const BLOCK_DISPLAY_INFO* pbdi = bdi;
	while (pbdi->value != bdi_value && pbdi->value != BDI_VALUE_END)
		pbdi++;

	// 起始坐标
	int block_start_x = pCGI->start_x + pCGI->draw_frame_with_row_no * 2 + 2 + col_no * (pCGI->CFI.block_width + pCGI->CFI.separator * 2);
	int block_start_y = pCGI->start_y + pCGI->draw_frame_with_col_no + 1 + row_no * (pCGI->CFI.block_high + pCGI->CFI.separator);

	// 先是颜色
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
	if (pCGI->CBI.block_border)//有边框，不然可以只输出内容---彩球
	{
		for (int i = 0; i < pCGI->CFI.block_high; i++)
		{
			cct_gotoxy(block_start_x, block_start_y+i);
			if(i==0)
			{
				for (int j = 0; j < pCGI->CFI.block_width/2; j ++)//两个一个格子
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
	else//可能是填充所有位置（用底色）
	{
		for (int i = 0; i < pCGI->CFI.block_high; i++)
		{
			cct_gotoxy(block_start_x, block_start_y + i);
			if (i == 0)
			{
				for (int j = 0; j < pCGI->CFI.block_width / 2; j++)//两个一个格子
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

	/* 内容 */
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

	return 0; //此句可根据需要修改
}

/***************************************************************************
  函数名称：
  功    能：移动某一个色块
  输入参数：const CONSOLE_GRAPHICS_INFO *const pCGI	：整体结构指针
		   const int row_no						：行号（从0开始，人为保证正确性，程序不检查）
		   const int col_no						：列号（从0开始，人为保证正确性，程序不检查）
		   const int bdi_value						：需要显示的值
		   const int blank_bdi_value				：移动过程中用于动画效果显示时用于表示空白的值（一般为0，此处做为参数代入，是考虑到可能出现的特殊情况）
		   const BLOCK_DISPLAY_INFO *const bdi		：存放显示值/空白值对应的显示信息的结构体数组
		   const int direction						：移动方向，一共四种，具体见cmd_gmw_tools.h
		   const int distance						：移动距离（从1开始，人为保证正确性，程序不检查）
  返 回 值：
  说    明：
***************************************************************************/
int gmw_draw_block_by_a_step(const CONSOLE_GRAPHICS_INFO* const pCGI, const int row_no, const int col_no, const int bdi_value, const BLOCK_DISPLAY_INFO* const bdi,int dx,int dy)
{
	/* 防止在未调用 gmw_init 前调用其它函数 */
	if (pCGI->inited != CGI_INITED)
		return -1;

	//bdi从尾部读入反向的读入
	/*
	typedef struct _block_display_info_ {
		const int   value;	//要显示的内部数组值
		const int   bgcolor;	//-1表示用游戏区域背景色
		const int   fgcolor;	//-1表示用游戏区域前景色
		const char* content;	//内部数组值对应的图形（如果为NULL，则直接显示内部数组的值）
	} BLOCK_DISPLAY_INFO;
	*/

	//存贮使用showstr
	int x, y;

	const BLOCK_DISPLAY_INFO* pbdi = bdi;
	while (pbdi->value != bdi_value && pbdi->value != BDI_VALUE_END)
		pbdi++;

	// 起始坐标
	int block_start_x = pCGI->start_x + pCGI->draw_frame_with_row_no * 2 + 2 + col_no * (pCGI->CFI.block_width + pCGI->CFI.separator * 2)+dx;//加上x的偏置
	int block_start_y = pCGI->start_y + pCGI->draw_frame_with_col_no + 1 + row_no * (pCGI->CFI.block_high + pCGI->CFI.separator)+dy;//加上y的偏置

	// 先是颜色
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
	if (pCGI->CBI.block_border)//有边框，不然可以只输出内容---彩球
	{
		for (int i = 0; i < pCGI->CFI.block_high; i++)
		{
			cct_gotoxy(block_start_x, block_start_y + i);
			if (i == 0)
			{
				for (int j = 0; j < pCGI->CFI.block_width / 2; j++)//两个一个格子
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

	/* 内容 */
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

	return 0; //此句可根据需要修改
}
int gmw_move_block(const CONSOLE_GRAPHICS_INFO *const pCGI, const int row_no, const int col_no, const int bdi_value, const int blank_bdi_value, const BLOCK_DISPLAY_INFO *const bdi, const int direction, const int distance)
{
	/* 防止在未调用 gmw_init 前调用其它函数 */
	if (pCGI->inited != CGI_INITED)
		return -1;

	// 起始坐标
	int block_start_x = pCGI->start_x + pCGI->draw_frame_with_row_no * 2 + 2 + col_no * (pCGI->CFI.block_width + pCGI->CFI.separator * 2);
	int block_start_y = pCGI->start_y + pCGI->draw_frame_with_col_no + 1 + row_no * (pCGI->CFI.block_high + pCGI->CFI.separator);

	//先是颜色
	int bgcolor = bdi->bgcolor < 0 ? pCGI->CFI.bgcolor : bdi->bgcolor;
	int fgcolor = bdi->fgcolor < 0 ? pCGI->CFI.fgcolor : bdi->fgcolor;

	/*
	 定义色块的四种移动方向 
		define DOWN_TO_UP		0
		define UP_TO_DOWN		1
		define RIGHT_TO_LEFT	2
		define LEFT_TO_RIGHT	3
	*/

	//这里的距离不是像素点的距离，需要新计算
	int true_steps = distance * (pCGI->CFI.block_width / 2 + pCGI->CFI.separator);

	if (direction == DOWN_TO_UP)//向上
	{
		for (int i = 0; i <= true_steps; i++)
		{
			gmw_draw_block_by_a_step(pCGI, row_no, col_no, bdi_value, bdi, 0, -i);//dy==i 上移一个位置
			Sleep(20);//测试

			//补原行位置的内容
			if (i != true_steps)
			{
				if (((i+1) % (pCGI->CFI.block_high + 1) == 0) && i != 0 && pCGI->CFI.separator)//有分割符号的话可能要判断是否输出
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
	if (direction == UP_TO_DOWN)//向下
	{
		for (int i = 0; i <= true_steps; i++)
		{
			gmw_draw_block_by_a_step(pCGI, row_no, col_no, bdi_value, bdi, 0, +i);//dy==i
			Sleep(20);//测试

			//补原行位置的内容
			if (i != true_steps)
			{
				if (((i + 1) % (pCGI->CFI.block_high + 1) == 0) && i != 0 && pCGI->CFI.separator)//有分割符号的话可能要判断是否输出
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
	if (direction == RIGHT_TO_LEFT)//向左
	{
		for (int i = 0; i <= 2*true_steps; i+=2)
		{
			gmw_draw_block_by_a_step(pCGI, row_no, col_no, bdi_value, bdi, -i,0 );//dy==i
			Sleep(20);//测试

			//补原行位置的内容
			if (i != 2 * true_steps)
			{
				for (int j = 0; j < pCGI->CFI.block_high; j++)
				{
					if (((i / 2 + 1) % ((pCGI->CFI.block_width + 2) / 2) == 0) && i != 0 && pCGI->CFI.separator)//有分割符号的话可能要判断是否输出
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
	if (direction == LEFT_TO_RIGHT)//向右
	{
		for (int i = 0; i <= 2*true_steps; i+=2)
		{
			gmw_draw_block_by_a_step(pCGI, row_no, col_no, bdi_value, bdi, +i ,0 );//dy==i
			Sleep(20);//测试

			//补原行位置的内容
			if (i != 2*true_steps)
			{
				for (int j = 0; j < pCGI->CFI.block_high; j++)
				{
					if (((i/2+1) % ((pCGI->CFI.block_width + 2)/2) == 0) && i != 0 && pCGI->CFI.separator)//有分割符号的话可能要判断是否输出
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

	return 0; //此句可根据需要修改
}

/***************************************************************************
  函数名称：
  功    能：读键盘或鼠标
  输入参数：const CONSOLE_GRAPHICS_INFO *const pCGI	：整体结构指针
		   int &MAction							：如果返回 CCT_MOUSE_EVENT，则此值有效，为 MOUSE_ONLY_MOVED/MOUSE_LEFT_BUTTON_CLICK/MOUSE_RIGHT_BUTTON_CLICK 三者之一
		                                               如果返回 CCT_KEYBOARD_EVENT，则此值无效
		   int &MRow								：如果返回 CCT_MOUSE_EVENT 且 MAction = MOUSE_ONLY_MOVED/MOUSE_LEFT_BUTTON_CLICK，则此值有效，表示左键选择的游戏区域的行号（从0开始）
												  其余情况此值无效（如果访问无效值导致错误，不是本函数的错!!!）
		   int &MCol								：如果返回 CCT_MOUSE_EVENT 且 MAction = MOUSE_ONLY_MOVED/MOUSE_LEFT_BUTTON_CLICK，则此值有效，表示左键选择的游戏区域的列号（从0开始）
												  其余情况此值无效（如果访问无效值导致错误，不是本函数的错!!!）
		   int &KeyCode1							：如果返回 CCT_KEYBOARD_EVENT，则此值有效，为读到的键码（如果双键码，则为第一个）
												  其余情况此值无效（如果访问无效值导致错误，不是本函数的错!!!）
		   int &KeyCode2							：如果返回 CCT_KEYBOARD_EVENT，则此值有效，为读到的键码（如果双键码，则为第二个，如果是单键码，则为0）
												  其余情况此值无效（如果访问无效值导致错误，不是本函数的错!!!）
		   const bool update_lower_status_line		：鼠标移动时，是否要在本函数中显示"[当前光标] *行*列/位置非法"的信息（true=显示，false=不显示，缺省为true）
  返 回 值：函数返回约定
		   1、如果是鼠标移动，得到的MRow/MCol与传入的相同(鼠标指针微小的移动)，则不返回，继续读
							  得到行列非法位置，则不返回，根据 update_lower_status_line 的设置在下状态栏显示"[当前光标] 位置非法"
							  得到的MRow/MCol与传入的不同(行列至少一个变化)，根据 update_lower_status_line 的设置在下状态栏显示"[当前光标] *行*列"，再返回MOUSE_ONLY_MOVED（有些游戏返回后要处理色块的不同颜色显示）
		   2、如果是按下鼠标左键，且当前鼠标指针停留在主游戏区域的*行*列上，则返回 CCT_MOUSE_EVENT ，MAction 为 MOUSE_LEFT_BUTTON_CLICK, MRow 为行号，MCol 为列标
		                          且当前鼠标指针停留在非法区域（非游戏区域，游戏区域中的分隔线），则不返回，根据 update_lower_status_line 的设置在下状态栏显示"[当前光标] 位置非法"
		   3、如果是按下鼠标右键，则不判断鼠标指针停留区域是否合法，直接返回 CCT_MOUSE_EVENT ，MAction 为 MOUSE_RIGHT_BUTTON_CLICK, MRow、MCol取当前值（因为消灭星星的右键标记需要坐标）
		   4、如果按下键盘上的某键（含双键码按键），则直接返回 CCT_KEYBOARD_EVENT，KeyCode1/KeyCode2中为对应的键码值
 说    明：通过调用 cmd_console_tools.cpp 中的 read_keyboard_and_mouse 函数实现
***************************************************************************/
static int gmw_inner_convert_xy_to_rc(const CONSOLE_GRAPHICS_INFO* const pCGI, int MX, int MY, int& MRow, int& MCol)
{

	int block_start_x0 = pCGI->start_x + 2;
	int block_start_y0 = pCGI->start_y + 1;

	MRow = MCol = -1024; // 初始化为非法位置

	// 遍历
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
	/* 防止在未调用 gmw_init 前调用其它函数 */
	if (pCGI->inited != CGI_INITED)
		return -1;

	cct_enable_mouse();

	int MX = 0, MY = 0;  //记录鼠标位置
	int type;            //事件类型
	int MRow_new = MRow, MCol_new = MCol;    //行列新值
	int sign = 0, old_sign = 0;

	while (1) {
		type = cct_read_keyboard_and_mouse(MX, MY, MAction, KeyCode1, KeyCode2);
		if (type == CCT_KEYBOARD_EVENT)
			return type;
		else {
			//判断右键
			if (MAction == MOUSE_RIGHT_BUTTON_CLICK) {
				MRow = MRow_new;
				MCol = MCol_new;
				return CCT_MOUSE_EVENT;
			}
			old_sign = sign;
			//判断鼠标位置是否合法
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

			//判断左键
			if (MAction == MOUSE_LEFT_BUTTON_CLICK) {
				if (sign) {
					if (update_lower_status_line && !old_sign) {
						gmw_status_line(pCGI, LOWER_STATUS_LINE, "[当前光标] 位置非法                ");
					}
				}
				else {
					return CCT_MOUSE_EVENT;
				}
			}

			//剩下鼠标移动
			if (sign) {
				if (update_lower_status_line && !old_sign) {
					gmw_status_line(pCGI, LOWER_STATUS_LINE, "[当前光标] 位置非法                   ");
				}
			}
			else {
				MCol_new = (MX - pCGI->start_x - pCGI->draw_frame_with_row_no * 2 - 2) / (pCGI->CFI.block_width + pCGI->CFI.separator * 2);
				MRow_new = (MY - pCGI->start_y - pCGI->draw_frame_with_col_no - 1) / (pCGI->CFI.block_high + pCGI->CFI.separator);
				if (MRow_new != MRow || MCol_new != MCol || old_sign) {
					if (update_lower_status_line) {
						char temp[256];
						sprintf(temp, "[当前光标] %c行%d列                 ", char('A' + MRow_new), MCol_new);
						gmw_status_line(pCGI, LOWER_STATUS_LINE, temp);
					}
					MRow = MRow_new;
					MCol = MCol_new;
					return CCT_MOUSE_EVENT;
				}
			}
		}
	}

	return CCT_MOUSE_EVENT; //此句可根据需要修改
}
