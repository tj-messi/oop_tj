/* 2150792 牛禄阳 计科 */
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
	bool issame;                 // file1和file2是否相同
	bool file1eof;               // file1文件到达eof
	bool file2eof;               // file2文件到达eof
	bool backcolor;             // 有背景色
	int  file1linelen;			 // file1当前行有效长度
	int  file2linelen;           // file2当前行有效长度
	int  file1linesta;           // file1当前行有效内容开始下标
	int  file2linesta;           // file2当前行有效内容开始下标
	int  file1curline;           // file1文件当前比较的行数位置
	int  file2curline;           // file2文件当前比较的行数位置
	int  linemaxlen;             // 所有行内容的最大长度
	int  width;                  // 行内容的打印宽度
	int  difflinenum;            // 已经比较的不同内容行的个数
	int  cmplinenum;             // 已经比较的行的个数
	int  linerrtype;             // 当前行的错误种类
	bool linediff[MAXLEN_LINE];  // 当前位置字符不同，用false/true表示
	char file1line[MAXLEN_LINE]; // file1此行的数据
	char file2line[MAXLEN_LINE]; // file2此行的数据
public:
	txt_cmp_tools();
	bool ignoreblank;
	bool CRnotequal;             // 为1将两者视为不同
	int  lineskip;
	int  lineoffset;
	int  maxdiff;
	int  maxline;
	string trimtype;
	string displaytype;
	struct Line_Data linedata; // 存放当前读入行的内容
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

