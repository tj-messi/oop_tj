/* 2150792 ţ»�� �ƿ� */
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
		cerr << "��һ���ļ�[" << filename1 << "]�޷���." << endl;
		return false;
	}
	file2.open(filename2, ios::in | ios::binary);
	if (file2.is_open() == 0)
	{
		file1.close(); // ����Ҫ���Ѿ��򿪵ĵ�һ���ļ��ر�
		cerr << "�ڶ����ļ�[" << filename2 << "]�޷���." << endl;
		return false;
	}
	return true;
}

void txt_cmp_tools::close_cmpfile()
{
	file1.close();
	file2.close();
}

/* ��һ�е�����ת��ΪHEX,choiceΪ1��file1,choiceΪ2��file2 */
void txt_cmp_tools::conv_linecont_tohex(const char* source, char* des, int choice)
{ // ֻ��Ҫͳ��ת�����ʮ���������ж����У������У���������֮ǰ�ķ���
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

/* �ļ���ͬʱ����ʾ��Ϣ */
void txt_cmp_tools::cmp_prompt_infor()
{
	cout << "�Ķ���ʾ��" << endl;
	cout << "\t1��������<EMPTY>���" << endl;
	cout << "\t2���ļ�������<EOF>���" << endl;
	cout << "\t3��������ͬ��λ�õĲ����ַ�����ɫ���" << endl;
	cout << "\t4��ÿ���е�CR/LF/VT/BS/BEL��X���(���㿴�������ַ�)" << endl;
	cout << "\t5��ÿ��β�Ķ�����ַ�����ɫ�����CR/LF/VT/BS/BEL����ɫX���(���㿴�������ַ�)" << endl;
	cout << "\t6��ÿ�������<CR>���(���㿴�������ַ�)" << endl;
	cout << "\t7��������Ϊ�������⣬����λ�ÿ��ܱ��ں��������ϣ����������ֶ���ɫ���" << endl;
	if (displaytype != "detailed")
		cout << "\t8����--display detailed���Եõ�����ϸ����Ϣ" << endl;
}

/* ��trim�ж���һ�е����ݣ�������ûtrim������Ҫ���ô˺��� */
void txt_cmp_tools::trim_line_space(ifstream& file)
{
	char byte_data = '\0';
	int  now_index = 0;
	/* ��ʼ�����ж�ȡ���� */
	memset(linedata.buffer, '\0', sizeof(linedata.buffer));
	file.getline(linedata.buffer, 65537, '\n'); // ע�⣬getline��ʽ��һ���ж��룬������β����\n
	int  buffer_len = strlen(linedata.buffer);  // �����ǰ���������ĳ���
	linedata.start_index = 0;
	linedata.end_index = buffer_len - 1; // end_index = -1���������Ϊ��
	linedata.eof_flag = false;

	if (trimtype == "left" || trimtype == "all") //�������ո�
	{
		while (1)
		{
			if (linedata.buffer[now_index] == '\r' && CRnotequal) // �������\r������Ϊ��ͬ����ֱ�ӽ���
			{
				return; // \r�ᱻ����������
			}
			else if (linedata.buffer[now_index] == '\r' || linedata.buffer[now_index] == '\t' || linedata.buffer[now_index] == ' ')
			{  // �����\r�Ҳ���Ϊ��ͬ������\t�����߿ո��򽫴���������
				++now_index;
			}
			else
			{
				break; // ������Ч���ݣ�����trimleft����
			}
		}
	}
	linedata.start_index = now_index; // ����buffer��ʼ��λ
	now_index = buffer_len - 1; // ��now_index���µ��Ҳ�
	if (trimtype == "right" || trimtype == "all") // �����Ҳ�ո�
	{
		while (1)
		{    // \r��CR����ͬʱ����
			if (linedata.buffer[now_index] == '\r' || linedata.buffer[now_index] == '\t' || linedata.buffer[now_index] == ' ')
			{  // �����\r������\t�����߿ո��򽫴���������
				--now_index;
			}
			else
			{
				break; // ������Ч���ݣ�����trimleft����
			}
		}
	}
	if (trimtype == "none" || trimtype == "left") // ������trim rightʱ��������Ӳ��죬��\r��Ҫ������������Ҫ
	{
		if (!CRnotequal && linedata.buffer[now_index] == '\r')
			--now_index;
	}
	if (file.eof()) // ���ж��Ƿ��Ѿ�����EOF��������ֱ�ӷ���
	{
		linedata.eof_flag = true;
		linedata.end_index = now_index; // ����buffer������λ
		return;
	}
	if (buffer_len == 0)
	{ // �����Linux�ļ��Ҹ���Ϊ�գ���ʲôҲ��������ֱ�ӷ���
		linedata.end_index = now_index; // ����buffer������λ
		return;
	}
	linedata.end_index = now_index; // ����buffer������λ
}

/* ������ӿ���,choice==1����Ϊfile1��choice==2,��Ϊfile2 */
void txt_cmp_tools::ignore_blank(int choice)
{   // ֻ�д�������Ϊ��ʱ���Ż���ӣ������\r�������ַ����򲻻�
	while (linedata.end_index == -1 && linedata.eof_flag == false)
	{
		if (choice == 1)
			read_line_file1();
		else if (choice == 2)
			read_line_file2();
	}
}

/* �������line_offset����line_skip��һ����ִ��������������
   ������ִ��trim_line_space��ignore_blank��Ȼ�����н��бȽ� */
int txt_cmp_tools::line_offset()
{
	int lineoffcnt = 0;
	if (lineoffset < 0) // ˵����file1ƫ��
	{
		lineoffcnt = -lineoffset;
		for (int i = 0; i < lineoffcnt; i++) //��Ҫ����δ����EOF���ж�
		{
			read_line_file1();
			if (ignoreblank)          
				ignore_blank(1);
			if (file1eof == true)
			{
				if (file2eof == true) // ��offsetʱ���߶������ļ�β������ͬ
					issame = true;
				return 1;
			}
		}
	}
	else                // ˵����file2ƫ��
	{
		lineoffcnt = lineoffset;
		for (int i = 0; i < lineoffcnt; i++) //��Ҫ����δ����EOF���ж�
		{
			read_line_file2();
			if (ignoreblank)
				ignore_blank(2);
			if (file2eof == true)
			{
				if (file1eof == true) // ��offsetʱ���߶������ļ�β������ͬ
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
		if (file1eof && file2eof) // �����ļ�����skip�н���
		{
			issame = true;
			return 1;
		}
		else if (file1eof || file2eof) // ����һ��������������ͬ
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
		cout << "�ȽϽ�������" << endl;
		print_sep_equals();
	}
	/* ��ʼ�ļ��ȶ� */
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
		if (cmplinenum >= maxline && maxline > 0) // �Ƚ���������maxline
		{
			break;
		}
		if (line_cmp_result == 1) // �����Ƚ�
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
			print_line_errmsg(line_cmp_result);  // ��ӡ���еĴ�����ʾ��Ϣ
		}
		if (difflinenum >= maxdiff && maxdiff > 0) // ��������д�Ż�����жϣ�������������maxdiff
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
			cout << "�ļ���ͬ." << endl;
		else
		{
			cout << "��ָ�������������ȫһ��." << endl;
			print_sep_equals();
		}
	}
	else // ���ļ���ͬ
	{
		if (displaytype == "none")
			cout << "�ļ���ͬ." << endl;
		else
		{
			print_sep_equals();
			cout << "��ָ����������¹�" << difflinenum << "���в���";
			if (flag_maxdiff == true)
				cout << "[�ѵ��趨��������ֵ]";
			cout << "." << endl;
			cmp_prompt_infor();
			print_sep_equals();
		}
	}
}

/* ���������ļ����еıȽ�
   ��ֻͬ��һ�����ͣ���ͬ��Ϊ�������ͣ�1������ͬ��0�����ĳ��λ�ÿ�ʼ��������в���(diaplay none)��
   -1�����ļ�1����/�ļ�2δ������-2�����ļ�1δ����/�ļ�2������-3�����ļ�1β���ж����ַ���-4�����ļ�2β���ж����ַ� */
int  txt_cmp_tools::file_cmp_line()
{
	/* ���е������Ѿ�����file1line��file2line�� */
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
			else                    // ��Ҫ��¼�в����ַ���λ��
			{
				linediff[i] = true; // �����Ӧ����ȥ���ո���λ��
				cmp_result = 0;
			}
		}
	}
	for (int i = min_filelen; i < file1linelen; i++) // �ļ�1β�����ַ�
	{
		if (displaytype == "none")
		{
			cmp_result = 0;
			break;
		}
		linediff[i] = true;
		if (cmp_result != 0)  // ����0�����ȼ���ߣ��������������������޸�
			cmp_result = -3;
	}
	for (int i = min_filelen; i < file2linelen; i++) // �ļ�2β�����ַ�
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
	if ((trimtype != "none") && ignoreblank && ((file1eof && !file2eof) || (!file1eof && file2eof)))           // �ں��ӻ��е�����£������һ���ļ���������Ҫ����һ��ȥ��
	{
		if (cmp_result == 1)
			return cmp_result; // ��ǰ��������0��-3��-4���Ż����һ�н��бȽ�
	}
	if (file1eof && !file2eof) // �ļ�1�������ļ�2δ����
	{
		if (cmp_result == 1)
			cmp_result = -1;
	}
	if (!file1eof && file2eof) // �ļ�2�������ļ�1δ����
	{
		if (cmp_result == 1)
			cmp_result = -2;
	}
	return cmp_result;
}

void txt_cmp_tools::set_width()
{
	//�ָ���===�Ŀ�ȼ��� 
	width = (this->linemaxlen / 10 + 1) * 10 + 8 + 2; //��---�ı�߶�2����line_maxlen����ȡ10��������8��"�ļ�1 : "

	/* �������hex���������С���Ϊ80 */
	if (this->displaytype == "detailed" && width < 80)
		width = 80;
}

void txt_cmp_tools::get_maxlen_line()
{
	string line;
	size_t max_length = 0;
	// ���� file1 �е�ÿһ��
	while (getline(file1, line)) 
	{
		size_t length = line.length();
		if (length > max_length)
			max_length = length;
	}
	// ���� file2 �е�ÿһ��
	while (getline(file2, line)) 
	{
		size_t length = line.length();
		if (length > max_length) 
			max_length = length;
	}
	/* �õ��г��ȵ����ֵ�������ÿ�� */
	linemaxlen = max_length;
	set_width();
	/* �ָ��ļ���ָ�뵽��ͷ */
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
	int max_filelen = max(file1linelen, file2linelen); // �����ǰ�������ļ����������
	int need_print_len = max_filelen + 10 - max_filelen % 10; // ���϶���Ϊ10�ı���
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

/* ��������д��󣬴�ӡ������Ϣ */
void txt_cmp_tools::print_line_errmsg(int choice)
{   // ��Ҫ�ж�displaytype
	cout << "��[" << file1curline << " / " << file2curline << "]�� - ";
	if (choice == 0)
		cout << "��[" << get_diff_findex() << "]���ַ���ʼ�в��죺" << endl;
	else if (choice == -1)
		cout << "�ļ�1�ѽ���/�ļ�2�������ݣ�" << endl;
	else if (choice == -2)
		cout << "�ļ�1��������/�ļ�2�ѽ�����" << endl;
	else if (choice == -3)
		cout << "�ļ�1��β���ж����ַ���" << endl;
	else if (choice == -4)
		cout << "�ļ�2��β���ж����ַ���" << endl;
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
		cout << "�ļ�1(HEX) : " << endl << file1linehex;
		cout << "�ļ�2(HEX) : " << endl << file2linehex;
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
	cout << "�ļ�1 : ";
	if (file1eof == false && file1linelen == 0)
	{
		set_back_color();
		cout << "<EMPTY>";
	}
	for (int i = 0; i < file1linelen; i++)
	{
		if (linediff[i] == true) // �����ǰλ�ò�ͬ
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
	cout << "�ļ�2 : ";
	if (file2eof == false && file2linelen == 0)
	{
		set_back_color();
		cout << "<EMPTY>";
	}
	for (int i = 0; i < file2linelen; i++)
	{
		if (linediff[i] == true) // �����ǰλ�ò�ͬ
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
