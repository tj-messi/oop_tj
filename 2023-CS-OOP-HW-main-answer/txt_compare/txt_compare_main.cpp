/* 2150792 牛禄阳 计科 */
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <sstream>
#include <tchar.h>
#include <string>
#include "../include/class_aat.h"
#include "../include/cmd_console_tools.h"
#include "txt_compare.h"
using namespace std;

/* 截取txt_compare.exe的函数 */
static void intercept_txt_compare(char* procname, const char* const argv0)
{
	int i = strlen(argv0) - 1;
	string des_name = "";
	while (i >= 0) // 参数长度读完也会终止
	{
		if (argv0[i] == '\\' || argv0[i] == '/') // 读到分割符停止
			break;
		else
		{
			des_name += argv0[i];
			--i;
		}
	}
	reverse(des_name.begin(), des_name.end()); // 从后向前读，所以需要反转
	des_name.copy(procname, des_name.length());
	procname[des_name.length()] = '\0';
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
 ***************************************************************************/
static void usage(const char* const argv0)
{
	char procname[256];

	intercept_txt_compare(procname, argv0); // 修改为自己的截取函数
	ostringstream msg;
	const int wkey = 7 + strlen(procname) + 1;
	const int wopt = 7 + strlen(procname) + 4;
	cout << endl;

	msg << procname << " [Ver1.0.1]" << endl;
	msg << endl;

	msg << "Usage: " << procname << " --file1 xxx --file2 xxx [ --trim none/left/rigth/all | --lineskip 0..100 | --lineoffset -100..100 | --ignore_blank | --max_diff 0..100 | --display none/normal/detailed ]" << endl;

	msg << setw(wkey) << ' ' << "必选项：" << endl;
	msg << setw(wopt) << ' ' << "--file1 name1              : 指定要比较的第1个文件名（必选）" << endl;
	msg << setw(wopt) << ' ' << "--file2 name2              : 指定要比较的第2个文件名（必选）" << endl;
	msg << endl;

	msg << setw(wkey) << ' ' << "可选项：" << endl;
	msg << setw(wopt) << ' ' << "--trim none/left/right/all     : 指定每行的空格/tab的忽略方式（无此项则默认为none）" << endl;
	msg << setw(wopt) << ' ' << "\tnone   : 每行均严格匹配" << endl;
	msg << setw(wopt) << ' ' << "\tleft   : 每行均忽略头部空格" << endl;
	msg << setw(wopt) << ' ' << "\tright  : 每行均忽略尾部空格" << endl;
	msg << setw(wopt) << ' ' << "\tall    : 每行均忽略头尾空格" << endl;
	msg << setw(wopt) << ' ' << "--lineskip s                   : 指定文件的前s行不比较（无此项则s为0）" << endl;
	msg << setw(wopt) << ' ' << "\t取值[0..100]，表示同时跳过两个文件的前s行" << endl;
	msg << setw(wopt) << ' ' << "--lineoffset n                 : 指定文件错位的行数（无此项则n为0）" << endl;
	msg << setw(wopt) << ' ' << "\t取值[-100..100]，负数表示忽略file1的前n行，正数表示忽略file2的前n行" << endl;
	msg << setw(wopt) << ' ' << "--ignore_blank                 : 忽略文件中--trim后的所有空行(无此项则不忽略)" << endl;
	msg << setw(wopt) << ' ' << "--CR_CRLF_not_equal            : 不忽略Windows/Linux文件的换行符差异(无此项则忽略差异)" << endl;
	msg << setw(wopt) << ' ' << "--max_diff m                   : 指定文件错位的行数（无此项则m为0）" << endl;
	msg << setw(wopt) << ' ' << "\t取值[0..100]，表示满m个不同行则结束运行，不再进行后续的比较" << endl;
	msg << setw(wopt) << ' ' << "--max_line x                   : 指定文件比较的最大行数（无此项则x为0）" << endl;
	msg << setw(wopt) << ' ' << "\t取值[0..10000]，表示比较x行后则结束运行，不再进行后续的比较" << endl;
	msg << setw(wopt) << ' ' << "--display none/normal/detailed : 指定显示的信息（无此项则默认为none）" << endl;
	msg << setw(wopt) << ' ' << "\tnone     : 仅一行匹配与否的提示" << endl;
	msg << setw(wopt) << ' ' << "\tnormal   : 每个差异行给出差异信息" << endl;
	msg << setw(wopt) << ' ' << "\tdetailed : 每个差异行给出更详细的差异信息" << endl;
	msg << endl;

	msg << "e.g.   " << procname << " --file1 my.txt --file2 std.txt" << endl;
	msg << setw(wopt) << ' ' << " : 比较my.txt和std.txt，全部匹配，仅一行输出" << endl;
	msg << "       " << procname << " --file1 my.txt --file2 std.txt --trim all" << endl;
	msg << setw(wopt) << ' ' << " : 比较my.txt和std.txt，每行均去除头尾空格，仅一行输出" << endl;
	msg << "       " << procname << " --file1 my.txt --file2 std.txt --lineoffset -2" << endl;
	msg << setw(wopt) << ' ' << " : 比较my.txt和std.txt，忽略my.txt的前2行(即my.txt的第3行与std.txt的第1行进行比较，每行严格匹配)，仅一行输出" << endl;
	msg << "       " << procname << " --file1 my.txt --file2 std.txt --trim left --lineoffset 3" << endl;
	msg << setw(wopt) << ' ' << " : 比较my.txt和std.txt，忽略std.txt的前3行(即my.txt的第1行与std.txt的第4行进行比较)，每行去除头部空格，仅一行输出" << endl;
	msg << "       " << procname << " --file1 my.txt --file2 std.txt --ignore_blank" << endl;
	msg << setw(wopt) << ' ' << " : 比较my.txt和std.txt，忽略文件中的所有空行，仅一行输出" << endl;
	msg << "       " << procname << " --file1 my.txt --file2 std.txt --lineskip 1" << endl;
	msg << setw(wopt) << ' ' << " : 比较my.txt和std.txt，第一行不比较" << endl;
	msg << "       " << procname << " --file1 my.txt --file2 std.txt --ignore_blank --trim right" << endl;
	msg << setw(wopt) << ' ' << " : 比较my.txt和std.txt，忽略文件中去除头尾空格后的所有空行，仅一行输出" << endl;
	msg << "       " << procname << " --file1 my.txt --file2 std.txt --max_diff 3" << endl;
	msg << setw(wopt) << ' ' << " : 比较my.txt和std.txt，全部匹配，有3行不匹配后结束运行，仅一行输出" << endl;
	msg << "       " << procname << " --file1 my.txt --file2 std.txt --max_line 7" << endl;
	msg << setw(wopt) << ' ' << " : 比较my.txt和std.txt，全部匹配，仅比较前7行，仅一行输出" << endl;
	msg << "       " << procname << " --file1 my.txt --file2 std.txt --CR_CRLF_not_queal" << endl;
	msg << setw(wopt) << ' ' << " : 比较my.txt和std.txt，全部匹配，不忽略Windows/Linux的文件差异，仅一行输出" << endl;
	msg << "       " << procname << " --file1 my.txt --file2 std.txt --display normal" << endl;
	msg << setw(wopt) << ' ' << " : 比较my.txt和std.txt，全部匹配，不匹配的行显示信息" << endl;
	msg << "       " << procname << " --file1 my.txt --file2 std.txt --display detailed" << endl;
	msg << setw(wopt) << ' ' << " : 比较my.txt和std.txt，全部匹配，不匹配的行显示详细信息" << endl;
	msg << endl;

	/* 一次全部显示出来 */
	cout << msg.str() << endl;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
int main(int argc, char** argv)
{
	/* 指定去除空格的方式 */
	const string TrimType[] = { "none",	"left",	"right",	"all", "" };
	const string DisplayType[] = { "none",	"normal",	"detailed", "" };

	args_analyse_tools args[] = {
		args_analyse_tools("--help",			ST_EXTARGS_TYPE::boolean, 0, false),
		args_analyse_tools("--debug",			ST_EXTARGS_TYPE::boolean, 0, false),
		args_analyse_tools("--file1",			ST_EXTARGS_TYPE::str, 1, string("")),
		args_analyse_tools("--file2",			ST_EXTARGS_TYPE::str, 1, string("")),
		args_analyse_tools("--trim",			ST_EXTARGS_TYPE::str_with_set_error, 1, 0, TrimType),
		args_analyse_tools("--lineskip",		ST_EXTARGS_TYPE::int_with_default,   1, 0, 0, 100),
		args_analyse_tools("--lineoffset",		ST_EXTARGS_TYPE::int_with_default,   1, 0, -100, 100),
		args_analyse_tools("--ignore_blank",	ST_EXTARGS_TYPE::boolean, 0, false),
		args_analyse_tools("--CR_CRLF_not_equal",ST_EXTARGS_TYPE::boolean, 0, false),
		args_analyse_tools("--max_diff",		ST_EXTARGS_TYPE::int_with_default,   1, 0, 0, 100),
		args_analyse_tools("--max_line",		ST_EXTARGS_TYPE::int_with_default,   1, 0, 0, 10000),
		args_analyse_tools("--display",			ST_EXTARGS_TYPE::str_with_set_error, 1, 0, DisplayType),
		args_analyse_tools()  //最后一个，用于结束
	};
	int cur_argc, ret = 0;

	//最后一个参数1，表示除选项参数外，还有其它参数
	if ((cur_argc = args_analyse_process(argc, argv, args, 0)) < 0) {
		//错误信息在函数中已打印
		args_analyse_print(args);
		usage(argv[0]);
		return -1;
	}
	
	/* 对help做特殊处理 */
	if (args[OPT_ARGS_HELP].existed()) {
		//只要有 --help，其它参数都忽略，显示帮助即可
		args_analyse_print(args);
		usage(argv[0]);
		return -1; //执行完成直接退出
	}

	if (args[OPT_ARGS_FILE1].existed() + args[OPT_ARGS_FILE2].existed() != 2) {
		usage(argv[0]);
		cout << "必须指定参数[" << args[OPT_ARGS_FILE1].get_name() << "和" << args[OPT_ARGS_FILE2].get_name() << "]" << endl;
		return -1;
	}

	// txt_cmp_tools txt_cmp; // 在这里声明txt_cmp对象
	txt_cmp_tools* txt_cmp = new(nothrow)txt_cmp_tools;
	if (txt_cmp == NULL)
		exit(-1);

	if (args[OPT_ARGS_TRIM].existed() == 1)
		txt_cmp->trimtype = args[OPT_ARGS_TRIM].get_string(); // 得到trimtype，用于下面判断

	if (args[OPT_ARGS_CR_CRLF_NOT_EQUAL].existed() && (txt_cmp->trimtype == "right" || txt_cmp->trimtype == "all")) {
		usage(argv[0]);
		cout << "参数[" << args[OPT_ARGS_CR_CRLF_NOT_EQUAL].get_name() << "]不能和[" << args[OPT_ARGS_TRIM].get_name() << " right/all]同时存在." << endl;
		return -1;
	}

	if (args[OPT_ARGS_DEBUG].existed())
		args_analyse_print(args);

	/* 进入实际的功能调用，完成相应的功能 */
	string filename1 = args[OPT_ARGS_FILE1].get_string();
	string filename2 = args[OPT_ARGS_FILE2].get_string();

	if (args[OPT_ARGS_DISPLAY].existed() == 1)
		txt_cmp->displaytype = args[OPT_ARGS_DISPLAY].get_string();
	if (args[OPT_ARGS_LINE_SKIP].existed() == 1)
		txt_cmp->lineskip = args[OPT_ARGS_LINE_SKIP].get_int();
	if (args[OPT_ARGS_LINE_OFFSET].existed() == 1)
		txt_cmp->lineoffset = args[OPT_ARGS_LINE_OFFSET].get_int();
	if (args[OPT_ARGS_IGNORE_BLANK].existed() == 1)
		txt_cmp->ignoreblank = true;
	if (args[OPT_ARGS_CR_CRLF_NOT_EQUAL].existed() == 1)
		txt_cmp->CRnotequal = true;
	if (args[OPT_ARGS_MAX_DIFFNUM].existed() == 1)
		txt_cmp->maxdiff = args[OPT_ARGS_MAX_DIFFNUM].get_int();
	if (args[OPT_ARGS_MAX_LINENUM].existed() == 1)
		txt_cmp->maxline = args[OPT_ARGS_MAX_LINENUM].get_int();

	if(txt_cmp->open_cmpfile(filename1, filename2)==false)				    // 打开比较文件
		return -1;								                
	txt_cmp->file_cmp_top();												// 调用cmp的顶层函数
	txt_cmp->close_cmpfile();                                               // 关闭比较文件 
	delete txt_cmp;
	return 0;
}

/*
阅读提示：
1、空行用 xxx 标出
2、文件结束用 xxx 标出
3、两行相同列位置的差异字符用亮色标出
4、每行中的CR/LF/VT/BS/BEL用X标出(方便看清隐含字符)
5、每行尾的多余的字符用亮色标出，CR/LF/VT/BS/BEL用亮色X标出(方便看清隐含字符)
6、每行最后用 xxx 标出(方便看清隐含字符)"
7、中文因为编码问题，差异位置可能报在后半个汉字上，但整个汉字都亮色标出
8、用--display detailed可以得到更详细的信息
*/

#if 0
//分隔行===的宽度计算 
int width = (this->line_maxlen / 10 + 1) * 10 + 8 + 2; //比---的标尺多2个：line_maxlen向上取10倍整数，8是"文件1 : "

/* 如果加了hex输出，则最小宽度为80 */
if (this->display_detailed && width < 80)
	width = 80;
#endif

/* 测试文件准备
	1.txt ：正常文件
	2.txt ：在1.txt的基础上，某些行前面无空格
	3.txt ：在1.txt的基础上，某些行后面无空格
	4.txt ：在1.txt的基础上，最后一行没有回车
	5.txt ：在1.txt的基础上，多一些空行
	6.txt ：在1.txt的基础上，多一些空行，其中某些行有空格和tab
	7.txt ：和1.txt完全相同
	8.txt ：是1.txt的Linux格式版

txt_compare --file1 1.txt --file2 2.txt --trim left
txt_compare --file1 1.txt --file2 2.txt --trim all
txt_compare --file1 2.txt --file2 3.txt --trim all
txt_compare --file1 1.txt --file2 4.txt --trim right --ignore_blank
txt_compare --file1 1.txt --file2 4.txt --trim all --ignore_blank
txt_compare --file1 2.txt --file2 4.txt --trim all --ignore_blank
txt_compare --file1 3.txt --file2 4.txt --trim right --ignore_blank
txt_compare --file1 3.txt --file2 4.txt --trim all --ignore_blank
txt_compare --file1 1.txt --file2 5.txt --trim right --ignore_blank
txt_compare --file1 1.txt --file2 6.txt --ignore_blank --trim right
txt_compare --file1 5.txt --file2 6.txt --ignore_blank --trim all
txt_compare --file1 1.txt --file2 7.txt
txt_compare --file1 1.txt --file2 8.txt

rem 不相同的例子
txt_compare --file1 1.txt --file2 2.txt
txt_compare --file1 1.txt --file2 2.txt --trim right
txt_compare --file1 1.txt --file2 5.txt
txt_compare --file1 1.txt --file2 5.txt --trim right
txt_compare --file1 1.txt --file2 6.txt
txt_compare --file1 1.txt --file2 6.txt --ignore_blank
txt_compare --file1 1.txt --file2 8.txt --CR_CRLF_not_equal

*/
