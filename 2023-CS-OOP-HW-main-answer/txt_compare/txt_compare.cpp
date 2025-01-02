/* 2150792 牛禄阳 计科 */
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <tchar.h>
#include <string>
#include "..\include\class_aat.h"
#include "..\include\cmd_console_tools.h"
#include "txt_compare.h"
using namespace std;
txt_cmp_tools::txt_cmp_tools()
{
	issame = true;
	file1eof = false;
	file2eof = false;
	backcolor = false;
	file1curline = 0;
	file2curline = 0;
	file1linelen = 0;
	file2linelen = 0;
	file1linesta = 0;
	file2linesta = 0;
	linemaxlen = 0;
	width = 0;
	difflinenum = 0;
	cmplinenum = 0;
	linerrtype = 0;
	memset(file1line, '\0', sizeof(file1line));
	memset(file2line, '\0', sizeof(file2line));
	memset(linediff, false, sizeof(linediff));
	ignoreblank = false;
	CRnotequal = false;
	lineskip = 0;
	lineoffset = 0;
	maxdiff = 0;
	maxline = 0;
	trimtype = "none";
	displaytype = "none";
}

bool txt_cmp_tools::open_cmpfile(string filename1, string filename2)
{
	file1.open(filename1, ios::in | ios::binary);
	if (file1.is_open() == 0)
	{
		cerr << "第一个文件[" << filename1 << "]无法打开." << endl;
		return false;
	}
	file2.open(filename2, ios::in | ios::binary);
	if (file2.is_open() == 0)
	{
		file1.close(); // 这里要把已经打开的第一个文件关闭
		cerr << "第二个文件[" << filename2 << "]无法打开." << endl;
		return false;
	}
	return true;
}

void txt_cmp_tools::close_cmpfile()
{
	file1.close();
	file2.close();
}

/* 将一行的内容转化为HEX,choice为1是file1,choice为2是file2 */
void txt_cmp_tools::conv_linecont_tohex(const char* source, char* des, int choice)
{ // 只需要统计转换后的十六进制是有多少行，多少列，就能套用之前的方法
	memset(des, '\0', MAXLEN_LINE);
	bool fileeof = (choice == 1) ? file1eof : file2eof;
	int  filelinelen = (choice == 1) ? file1linelen : file2linelen;
	int  filelinesta = (choice == 1) ? file1linesta : file2linesta;
	if (filelinelen == 0)
	{
		if (fileeof == true)
			strcpy(des, "<EOF>\n");
		else
			strcpy(des, "<EMPTY>\n");
		return;
	}
	int line = filelinelen / 16;
	int col = filelinelen % 16;
	int filelineindex = filelinesta;
	stringstream ss;
	unsigned char ch[20];
	for (int k = 0; k < line; k++)
	{
		ss << hex << setw(8) << setfill('0') << 16 * k << " : ";
		for (int t = 0; t < 16; t++)
			ch[t] = source[filelineindex++];
		for (int t = 0; t < 16; t++)
		{
			if (t == 8)
				ss << "- ";
			ss << hex << setw(2) << setfill('0') << int(ch[t]) << " ";
		}
		ss << " ";
		for (int t = 0; t < 16; t++)
		{
			if (ch[t] >= 32 && ch[t] <= 126)
				ss << ch[t];
			else
				ss << ".";
		}
		ss << endl;
	}
	if (col != 0)
	{
		ss << hex << setw(8) << setfill('0') << 16 * line << " : ";
		for (int t = 0; t < col; t++)
			ch[t] = source[filelineindex++];
		for (int t = 0; t < col; t++)
		{
			if (t == 8)
				ss << "- ";
			ss << hex << setw(2) << setfill('0') << int(ch[t]) << " ";
		}
		if (col <= 8)
			ss << setw(51 - 3 * col) << setfill(' ') << " ";
		else
			ss << setw(51 - 3 * col - 2) << setfill(' ') << " ";
		for (int t = 0; t < col; t++)
		{
			if (ch[t] >= 32 && ch[t] <= 126)
				ss << ch[t];
			else
				ss << ".";
		}
		ss << endl;
	}
	sprintf(des, ss.str().c_str());
}

/* 文件不同时的提示信息 */
void txt_cmp_tools::cmp_prompt_infor()
{
	cout << "阅读提示：" << endl;
	cout << "\t1、空行用<EMPTY>标出" << endl;
	cout << "\t2、文件结束用<EOF>标出" << endl;
	cout << "\t3、两行相同列位置的差异字符用亮色标出" << endl;
	cout << "\t4、每行中的CR/LF/VT/BS/BEL用X标出(方便看清隐含字符)" << endl;
	cout << "\t5、每行尾的多余的字符用亮色标出，CR/LF/VT/BS/BEL用亮色X标出(方便看清隐含字符)" << endl;
	cout << "\t6、每行最后用<CR>标出(方便看清隐含字符)" << endl;
	cout << "\t7、中文因为编码问题，差异位置可能报在后半个汉字上，但整个汉字都亮色标出" << endl;
	if (displaytype != "detailed")
		cout << "\t8、用--display detailed可以得到更详细的信息" << endl;
}

/* 在trim中读入一行的数据，无论有没trim，都需要调用此函数 */
void txt_cmp_tools::trim_line_space(ifstream& file)
{
	char byte_data = '\0';
	int  now_index = 0;
	/* 初始化此行读取数据 */
	memset(linedata.buffer, '\0', sizeof(linedata.buffer));
	file.getline(linedata.buffer, 65537, '\n'); // 注意，getline方式将一整行读入，不存在尾部的\n
	int  buffer_len = strlen(linedata.buffer);  // 求出当前读入的数组的长度
	linedata.start_index = 0;
	linedata.end_index = buffer_len - 1; // end_index = -1，代表此行为空
	linedata.eof_flag = false;

	if (trimtype == "left" || trimtype == "all") //处理左侧空格
	{
		while (1)
		{
			if (linedata.buffer[now_index] == '\r' && CRnotequal) // 如果读到\r，且视为不同，则直接结束
			{
				return; // \r会被留在数组里
			}
			else if (linedata.buffer[now_index] == '\r' || linedata.buffer[now_index] == '\t' || linedata.buffer[now_index] == ' ')
			{  // 如果是\r且不视为不同；或者\t；或者空格，则将此内容跳过
				++now_index;
			}
			else
			{
				break; // 读到有效内容，结束trimleft处理
			}
		}
	}
	linedata.start_index = now_index; // 更新buffer开始定位
	now_index = buffer_len - 1; // 将now_index更新到右侧
	if (trimtype == "right" || trimtype == "all") // 处理右侧空格
	{
		while (1)
		{    // \r和CR不能同时出现
			if (linedata.buffer[now_index] == '\r' || linedata.buffer[now_index] == '\t' || linedata.buffer[now_index] == ' ')
			{  // 如果是\r；或者\t；或者空格，则将此内容跳过
				--now_index;
			}
			else
			{
				break; // 读到有效内容，结束trimleft处理
			}
		}
	}
	if (trimtype == "none" || trimtype == "left") // 不进行trim right时，如果忽视差异，则\r需要读出，否则不需要
	{
		if (!CRnotequal && linedata.buffer[now_index] == '\r')
			--now_index;
	}
	if (file.eof()) // 先判断是否已经读到EOF，读到则直接返回
	{
		linedata.eof_flag = true;
		linedata.end_index = now_index; // 更新buffer结束定位
		return;
	}
	if (buffer_len == 0)
	{ // 如果是Linux文件且该行为空，则什么也读不到，直接返回
		linedata.end_index = now_index; // 更新buffer结束定位
		return;
	}
	linedata.end_index = now_index; // 更新buffer结束定位
}

/* 处理忽视空行,choice==1，则为file1；choice==2,则为file2 */
void txt_cmp_tools::ignore_blank(int choice)
{   // 只有此行数据为空时，才会忽视；如果有\r或其他字符，则不会
	while (linedata.end_index == -1 && linedata.eof_flag == false)
	{
		if (choice == 1)
			read_line_file1();
		else if (choice == 2)
			read_line_file2();
	}
}

/* 如果存在line_offset或者line_skip，一定先执行这两个函数，
   再逐行执行trim_line_space和ignore_blank，然后逐行进行比较 */
int txt_cmp_tools::line_offset()
{
	int lineoffcnt = 0;
	if (lineoffset < 0) // 说明是file1偏移
	{
		lineoffcnt = -lineoffset;
		for (int i = 0; i < lineoffcnt; i++) //需要加入未读到EOF的判断
		{
			read_line_file1();
			if (ignoreblank)          
				ignore_blank(1);
			if (file1eof == true)
			{
				if (file2eof == true) // 在offset时两者都读到文件尾，则相同
					issame = true;
				return 1;
			}
		}
	}
	else                // 说明是file2偏移
	{
		lineoffcnt = lineoffset;
		for (int i = 0; i < lineoffcnt; i++) //需要加入未读到EOF的判断
		{
			read_line_file2();
			if (ignoreblank)
				ignore_blank(2);
			if (file2eof == true)
			{
				if (file1eof == true) // 在offset时两者都读到文件尾，则相同
					issame = true;
				return 1;
			}
		}
	}
	return 0;
}

int  txt_cmp_tools::line_skip()
{
	for (int i = 0; i < lineskip; i++)
	{
		read_line_file1();
		if (ignoreblank)
			ignore_blank(1);
		read_line_file2();
		if (ignoreblank)
			ignore_blank(2);
		if (file1eof && file2eof) // 两个文件均在skip中结束
		{
			issame = true;
			return 1;
		}
		else if (file1eof || file2eof) // 仅有一个结束，代表不相同
			return 1;
	}
	return 0;
}

void txt_cmp_tools::file_cmp_top()
{
	bool flag_maxdiff = false;
	int  line_cmp_result = 0;
	if (lineoffset != 0)
		line_offset();
	if (lineskip != 0)
		line_skip();
	get_maxlen_line();
	set_width();
	if (displaytype != "none")
	{
		cout << "比较结果输出：" << endl;
		print_sep_equals();
	}
	/* 开始文件比对 */
	while (file1eof == false || file2eof == false)
	{
		read_line_file1();
		if (ignoreblank)
			ignore_blank(1);
		read_line_file2();
		if (ignoreblank)
			ignore_blank(2);
		line_cmp_result = file_cmp_line();
		++cmplinenum;
		if (cmplinenum >= maxline && maxline > 0) // 比较行数超过maxline
		{
			break;
		}
		if (line_cmp_result == 1) // 继续比较
			continue;
		else if (displaytype == "none" && line_cmp_result == 0) 
		{
			issame = false;
			++difflinenum;
		}
		else 
		{
			issame = false;
			++difflinenum;
			print_line_errmsg(line_cmp_result);  // 打印此行的错误提示信息
		}
		if (difflinenum >= maxdiff && maxdiff > 0) // 必须此行有错才会进行判断，错误行数超过maxdiff
		{
			flag_maxdiff = true;
			break;
		}
		if (file1eof || file2eof)
			break;
	}
	if (issame)
	{
		if (displaytype == "none")
			cout << "文件相同." << endl;
		else
		{
			cout << "在指定检查条件下完全一致." << endl;
			print_sep_equals();
		}
	}
	else // 两文件不同
	{
		if (displaytype == "none")
			cout << "文件不同." << endl;
		else
		{
			print_sep_equals();
			cout << "在指定检查条件下共" << difflinenum << "行有差异";
			if (flag_maxdiff == true)
				cout << "[已到设定的最大差异值]";
			cout << "." << endl;
			cmp_prompt_infor();
			print_sep_equals();
		}
	}
}

/* 进行两个文件逐行的比较
   相同只有一种类型；不同分为五种类型；1代表相同，0代表从某个位置开始差异或者有差异(diaplay none)；
   -1代表文件1结束/文件2未结束；-2代表文件1未结束/文件2结束；-3代表文件1尾部有多余字符；-4代表文件2尾部有多余字符 */
int  txt_cmp_tools::file_cmp_line()
{
	/* 此行的内容已经读到file1line和file2line中 */
	memset(linediff, false, sizeof(linediff));
	int min_filelen = min(file1linelen, file2linelen);
	int cmp_result = 1;
	for (int i = 0; i < min_filelen; i++)
	{
		if (file1line[file1linesta + i] != file2line[file2linesta + i])
		{
			if (displaytype == "none")
			{
				cmp_result = 0;
				break;
			}
			else                    // 需要记录有差异字符的位置
			{
				linediff[i] = true; // 这个对应的是去除空格后的位置
				cmp_result = 0;
			}
		}
	}
	for (int i = min_filelen; i < file1linelen; i++) // 文件1尾部有字符
	{
		if (displaytype == "none")
		{
			cmp_result = 0;
			break;
		}
		linediff[i] = true;
		if (cmp_result != 0)  // 错误0的优先级最高，不允许被其他错误类型修改
			cmp_result = -3;
	}
	for (int i = min_filelen; i < file2linelen; i++) // 文件2尾部有字符
	{
		if (displaytype == "none")
		{
			cmp_result = 0;
			break;
		}
		linediff[i] = true;
		if (cmp_result != 0)
			cmp_result = -4;
	}
	if ((trimtype != "none") && ignoreblank && ((file1eof && !file2eof) || (!file1eof && file2eof)))           // 在忽视换行的情况下，如果有一个文件结束，需要到下一行去比
	{
		if (cmp_result == 1)
			return cmp_result; // 当前错误不能是0、-3、-4，才会对下一行进行比较
	}
	if (file1eof && !file2eof) // 文件1结束，文件2未结束
	{
		if (cmp_result == 1)
			cmp_result = -1;
	}
	if (!file1eof && file2eof) // 文件2结束，文件1未结束
	{
		if (cmp_result == 1)
			cmp_result = -2;
	}
	return cmp_result;
}

void txt_cmp_tools::set_width()
{
	//分隔行===的宽度计算 
	width = (this->linemaxlen / 10 + 1) * 10 + 8 + 2; //比---的标尺多2个：line_maxlen向上取10倍整数，8是"文件1 : "

	/* 如果加了hex输出，则最小宽度为80 */
	if (this->displaytype == "detailed" && width < 80)
		width = 80;
}

void txt_cmp_tools::get_maxlen_line()
{
	string line;
	size_t max_length = 0;
	// 处理 file1 中的每一行
	while (getline(file1, line)) 
	{
		size_t length = line.length();
		if (length > max_length)
			max_length = length;
	}
	// 处理 file2 中的每一行
	while (getline(file2, line)) 
	{
		size_t length = line.length();
		if (length > max_length) 
			max_length = length;
	}
	/* 得到行长度的最大值，并设置宽度 */
	linemaxlen = max_length;
	set_width();
	/* 恢复文件读指针到开头 */
	file1.clear();
	file2.clear();
	file1.seekg(0, ios::beg);
	file2.seekg(0, ios::beg);
}

void txt_cmp_tools::print_sep_equals()
{
	cout << setw(width) << setfill('=') << "=" << endl;
}

void txt_cmp_tools::print_sep_number()
{
	int max_filelen = max(file1linelen, file2linelen); // 求出当前行两个文件的最大行数
	int need_print_len = max_filelen + 10 - max_filelen % 10; // 向上对齐为10的倍数
	cout << setw(8) << setfill(' ') << ' ';
	cout << setw(need_print_len) << setfill('-') << '-' << endl;
	cout << setw(8) << setfill(' ') << ' ';
	for (int i = 0; i < need_print_len / 10; i++)
		cout << setiosflags(ios::left) << setw(10) << i % 10;
	cout << resetiosflags(ios::left) << endl;
	cout << setw(8) << setfill(' ') << ' ';
	for (int i = 0; i < need_print_len / 10; i++)
		cout << "0123456789";
	cout << endl;
	cout << setw(8) << setfill(' ') << ' ';
	cout << setw(need_print_len) << setfill('-') << '-' << endl;
}

/* 如果此行有错误，打印错误信息 */
void txt_cmp_tools::print_line_errmsg(int choice)
{   // 需要判断displaytype
	cout << "第[" << file1curline << " / " << file2curline << "]行 - ";
	if (choice == 0)
		cout << "第[" << get_diff_findex() << "]个字符开始有差异：" << endl;
	else if (choice == -1)
		cout << "文件1已结束/文件2仍有内容：" << endl;
	else if (choice == -2)
		cout << "文件1仍有内容/文件2已结束：" << endl;
	else if (choice == -3)
		cout << "文件1的尾部有多余字符：" << endl;
	else if (choice == -4)
		cout << "文件2的尾部有多余字符：" << endl;
	set_width();
	if (displaytype == "detailed")
	{
		char* file1linehex = new(nothrow) char[MAXLEN_LINE];
		char* file2linehex = new(nothrow) char[MAXLEN_LINE];
		if (file1linehex == NULL || file2linehex == NULL)
			exit(-1);
		print_sep_number();
		print_file1_dec();
		print_file2_dec();
		conv_linecont_tohex(file1line, file1linehex, 1);
		conv_linecont_tohex(file2line, file2linehex, 2);
		cout << "文件1(HEX) : " << endl << file1linehex;
		cout << "文件2(HEX) : " << endl << file2linehex;
		cout << endl;
		delete[]file1linehex;
		delete[]file2linehex;
	}
	else if (displaytype == "normal")
	{
		print_file1_dec();
		print_file2_dec();
	}
}

void txt_cmp_tools::read_line_file1()
{
	trim_line_space(file1);
	file1eof = linedata.eof_flag;
	++file1curline;
	strcpy(file1line, linedata.buffer);
	file1linelen = linedata.end_index - linedata.start_index + 1;
	if (file1linelen < 0)
		file1linelen = 0;
	file1linesta = linedata.start_index;
}

void txt_cmp_tools::read_line_file2()
{
	trim_line_space(file2);
	file2eof = linedata.eof_flag;
	++file2curline;
	strcpy(file2line, linedata.buffer);
	file2linelen = linedata.end_index - linedata.start_index + 1;
	if (file2linelen < 0)
		file2linelen = 0;
	file2linesta = linedata.start_index;
}

void txt_cmp_tools::reset_back_color()
{
	cct_setcolor();
	backcolor = false;
}

void txt_cmp_tools::set_back_color()
{
	cct_setcolor(COLOR_HYELLOW, COLOR_HRED);
	backcolor = true;
}

void txt_cmp_tools::print_file1_dec()
{
	cout << "文件1 : ";
	if (file1eof == false && file1linelen == 0)
	{
		set_back_color();
		cout << "<EMPTY>";
	}
	for (int i = 0; i < file1linelen; i++)
	{
		if (linediff[i] == true) // 如果当前位置不同
			set_back_color();
		else
			reset_back_color();
		if ((file1line[i + file1linesta] >= 32 && file1line[i + file1linesta] <= 126) || (file1line[i + file1linesta] <= -1))
			cout << file1line[i + file1linesta];
		else
			cout << "X";
	}
	reset_back_color();
	if (file1eof == true)
		cout << "<EOF>" << endl;
	else
		cout << "<CR>" << endl;
}

void txt_cmp_tools::print_file2_dec()
{
	cout << "文件2 : ";
	if (file2eof == false && file2linelen == 0)
	{
		set_back_color();
		cout << "<EMPTY>";
	}
	for (int i = 0; i < file2linelen; i++)
	{
		if (linediff[i] == true) // 如果当前位置不同
			set_back_color();
		else
			reset_back_color();
		if ((file2line[i + file2linesta] >= 32 && file2line[i + file2linesta] <= 126) || (file2line[i + file2linesta] <= -1))
			cout << file2line[i + file2linesta];
		else
			cout << "X";
	}
	reset_back_color();
	if (file2eof == true)
		cout << "<EOF>" << endl;
	else
		cout << "<CR>" << endl;
}

int  txt_cmp_tools::get_diff_findex()
{
	int findex = 0;
	while (linediff[findex] == false)
		++findex;
	return findex;
}
