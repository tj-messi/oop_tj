/* 2150792 ţ»�� �ƿ� */
#pragma once

#include <string>
#include <fstream>
using namespace std;
enum OPT_ARGS {
	OPT_ARGS_HELP = 0,
	OPT_ARGS_DEBUG,
	OPT_ARGS_FILE1,
	OPT_ARGS_FILE2,
	OPT_ARGS_TRIM,
	OPT_ARGS_LINE_SKIP,
	OPT_ARGS_LINE_OFFSET,
	OPT_ARGS_IGNORE_BLANK,
	OPT_ARGS_CR_CRLF_NOT_EQUAL,
	OPT_ARGS_MAX_DIFFNUM,
	OPT_ARGS_MAX_LINENUM,
	OPT_ARGS_DISPLAY
};
const int MAXLEN_LINE = 66000;
const string SPECIAL_TAG[] = { "", "<EMPTY>", "<CR>", "<EOF" };

struct Line_Data {
	bool eof_flag;
	int  start_index;
	int  end_index;
	char buffer[MAXLEN_LINE];
};

class txt_cmp_tools {
private:
	ifstream file1;
	ifstream file2;
	bool issame;                 // file1��file2�Ƿ���ͬ
	bool file1eof;               // file1�ļ�����eof
	bool file2eof;               // file2�ļ�����eof
	bool backcolor;             // �б���ɫ
	int  file1linelen;			 // file1��ǰ����Ч����
	int  file2linelen;           // file2��ǰ����Ч����
	int  file1linesta;           // file1��ǰ����Ч���ݿ�ʼ�±�
	int  file2linesta;           // file2��ǰ����Ч���ݿ�ʼ�±�
	int  file1curline;           // file1�ļ���ǰ�Ƚϵ�����λ��
	int  file2curline;           // file2�ļ���ǰ�Ƚϵ�����λ��
	int  linemaxlen;             // ���������ݵ���󳤶�
	int  width;                  // �����ݵĴ�ӡ���
	int  difflinenum;            // �Ѿ��ȽϵĲ�ͬ�����еĸ���
	int  cmplinenum;             // �Ѿ��Ƚϵ��еĸ���
	int  linerrtype;             // ��ǰ�еĴ�������
	bool linediff[MAXLEN_LINE];  // ��ǰλ���ַ���ͬ����false/true��ʾ
	char file1line[MAXLEN_LINE]; // file1���е�����
	char file2line[MAXLEN_LINE]; // file2���е�����
public:
	txt_cmp_tools();
	bool ignoreblank;
	bool CRnotequal;             // Ϊ1��������Ϊ��ͬ
	int  lineskip;
	int  lineoffset;
	int  maxdiff;
	int  maxline;
	string trimtype;
	string displaytype;
	struct Line_Data linedata; // ��ŵ�ǰ�����е�����
	bool open_cmpfile(string filename1, string filename2);
	void close_cmpfile();
	void conv_linecont_tohex(const char* source, char* des, int choice);
	void cmp_prompt_infor();
	void trim_line_space(ifstream& file);
	void ignore_blank(int choice);
	int  line_offset();
	int  line_skip();
	void file_cmp_top();
	int  file_cmp_line();
	void set_width();
	void get_maxlen_line();
	void print_sep_equals();
	void print_sep_number();
	void print_line_errmsg(int choice);
	void read_line_file1();
	void read_line_file2();
	void reset_back_color();
	void set_back_color();
	void print_file1_dec();
	void print_file2_dec();
	int  get_diff_findex();
};

