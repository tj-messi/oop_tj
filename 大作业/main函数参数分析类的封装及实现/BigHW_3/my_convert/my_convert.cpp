/* 学号 姓名 班级 */
#include <iostream>
//可根据需要再加入其它需要的头文件
#include "../include/class_aat.h"
using namespace std;

#define	SRC_DST_IS_FIXED_ARGS		1		//1-转换前后的文件名是固定参数，0-转换前后的文件名是可变参数

/* enum的顺序要和args的排列顺序保持一致
   不用enum class 只是不想每次都做强制转换 */
enum OPT_ARGS {
	ARGS_HELP = 0,
	ARGS_CONVERT,
#if	!SRC_DST_IS_FIXED_ARGS
	ARGS_SRCFILE,
	ARGS_DSTFILE,
#endif
	ARGS_MAX	//用于控制enum上限的最大值，有类似 if (enum_value < ARGS_MAX) 需求时使用
};

/* 允许自行添加其它函数，也可以将自定义函数放在其它cpp中 */

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：想一想，为什么要加 static（虽然只有一个cpp，但这是工程习惯）
***************************************************************************/
static void usage(const char* const fullpath_procname)
{
	/* 这三行看得懂吗？*/
	const char* procname = strrchr(fullpath_procname, '\\');
	if (procname == NULL)
		procname = fullpath_procname;
	else
		procname++;

	cout << endl;
#if SRC_DST_IS_FIXED_ARGS
	cout << "Usage: " << procname << " [--help] | [--convert wtol | ltow] src_filename dst_filename" << endl;
	cout << endl;

	cout << "选项:" << endl;
	cout << "    --help\t\t给出帮助信息" << endl;
	cout << "    --convert\t\t给出转换方式" << endl;
	cout << "    \twtol : Windows格式转为Linux" << endl;
	cout << "    \tltow : Linux格式转为Windows" << endl;
	cout << endl;
	cout << "示例:" << endl;
	cout << "    " << procname << " --help" << endl;
	cout << "    " << procname << " a.txt b.txt                : 将Windows格式的a.txt转为Linux格式的b.txt" << endl;
	cout << "    " << procname << " --convert wtol a.txt b.txt : 将Windows格式的a.txt转为Linux格式的b.txt" << endl;
	cout << "    " << procname << " --convert ltow c.txt d.txt : 将Linux格式的c.txt转为Windows格式的d.txt" << endl;
	cout << endl;
#else
	cout << "Usage: " << procname << " [--help] | [--convert wtol | ltow] [--srcfile xxx] [--dstfile xxx]" << endl;
	cout << endl;

	cout << "选项:" << endl;
	cout << "    --help\t\t给出帮助信息" << endl;
	cout << "    --convert\t\t给出转换方式" << endl;
	cout << "    \twtol : Windows格式转为Linux" << endl;
	cout << "    \tltow : Linux格式转为Windows" << endl;
	cout << "    --srcfile\t\t给出源文件名" << endl;
	cout << "    --dstfile\t\t给出目标文件名" << endl;
	cout << endl;
	cout << "示例:" << endl;
	cout << "    " << procname << " --help" << endl;
	cout << "    " << procname << " --srcfile a.txt --dstfile b.txt                 : 将Windows格式的a.txt转为Linux格式的b.txt" << endl;
	cout << "    " << procname << " --dstfile b.txt --srcfile a.txt                 : 将Windows格式的a.txt转为Linux格式的b.txt" << endl;
	cout << "    " << procname << " --convert wtol --srcfile a.txt --dstfile b.txt  : 将Windows格式的a.txt转为Linux格式的b.txt" << endl;
	cout << "    " << procname << "  --dstfile b.txt --convert ltow --srcfile a.txt : 将Linux格式的a.txt转为Windows格式的b.txt" << endl;
	cout << endl;
#endif
}

/***************************************************************************
  函数名称：
  功    能：基本测试
  输入参数：
  返 回 值：
  说    明：命令行格式要求：先--开始的可变参数，顺序任意，最后是指定的固定参数
***************************************************************************/
int main(int argc, char* argv[])
{
	/* 因为引入了 lib_common_tools.lib，此处先检查大小是否符合要求 */
	if (sizeof(args_analyse_tools) != 240) {
		cout << "class args_analyse_tools 不是240字节，如果使用 lib_common_tools.lib 中的函数则可能出错" << endl;
		return -1;
	}

	/* 转换方式仅有两种 */
	string convert_type[] = { "wtol","ltow", "" };	//结尾必须是""

#if SRC_DST_IS_FIXED_ARGS //本段条件编译的代码，--convert是可选参数，最后两个必须是源文件名和目标文件名，且顺序不得交换
	args_analyse_tools args[] = {
		args_analyse_tools("--help",    ST_EXTARGS_TYPE::boolean,          0, false), //默认false
		args_analyse_tools("--convert", ST_EXTARGS_TYPE::str_with_set_default, 1, 0, convert_type),	//参数0代表default为set中的第[0]个值，即wtol，缺省0
		args_analyse_tools()  //最后一个，用于结束
	};

	/* 不带任何参数做特殊处理，打印提示信息后结束 */
	if (argc == 1) {
		usage(argv[0]);
		return -1;
	}

	int need_fixed_args = 1;	//需要固定参数
	int cur_argc;

	/* 最后一个参数：1 - 表示除选项参数外，还需要其它参数
					  例1：Windows/Linux下的ping命令，ping IP地址是最基本的命令格式，另外还有很多-/--开头的可选参数
						  ping 192.168.80.230
						  ping -t -n 10 192.168.80.230
					 例2：Linux下的c++命令，c++ 源程序文件名是最基本的命令格式，另外还有很多-/--开头的可选参数
						  c++ test.cpp
						  c++ -Wall -o test test.cpp
				  0 - 表示除选项参数外，不需要其它参数
		函数返回值：-1 - 处理过程有错
					>0 - 可变参数处理完成后，当前停在argv[]的第几个下标位置，如果后面还有argv[]，则表示固定参数
	*/
	if ((cur_argc = args_analyse_process(argc, argv, args, need_fixed_args)) < 0)
	{
		//错误信息在函数中已打印
		return -1;
	}

	/* 带--help参数做特殊处理，打印提示信息后结束 */
	if (args[ARGS_HELP].existed()) {
		usage(argv[0]);
		return -1;
	}

	/* 可变参数分析完成后，看是否还有固定参数，以及固定参数的数量是否符合要求 */
	if (need_fixed_args) {
		if (cur_argc == argc) {  //说明后面没有跟需要的固定参数
			cout << "需要指定IP地址，但未给出" << endl;
			return -1;
		}
		if (argc - cur_argc != 2) {
			cout << "除可变参数外，必须给出转换的源文件名和目标文件名两个固定参数，但现在只给出了" << argc - cur_argc << "个固定参数" << endl;
			return -1;
		}
	}

	/* 打印参数分析的结果 */
	cout << "可变参数列表:" << endl;
	args_analyse_print(args);

	/* 打印参数的值 */
	cout << "参数检查通过" << endl;
	cout << " --convert参数：" << args[ARGS_CONVERT].get_string() << endl;
	cout << " 源文件名是   ：" << argv[cur_argc] << endl;
	cout << " 目标文件名是 ：" << argv[cur_argc+1] << endl;

	/* 此处应给出真正的实现（本题不需要） */

#else //--convert/--srcfile/--dstfile均为可选参数，相互位置任意，通过判断--srcfile/--dstfile是否存在来强制要求这两个参数必须存在
	args_analyse_tools args[] = {
		args_analyse_tools("--help",    ST_EXTARGS_TYPE::boolean,            0, false), //默认false
		args_analyse_tools("--convert", ST_EXTARGS_TYPE::str_with_set_error, 1, 0, convert_type),	//如果不是wtol/ltow则报错
		args_analyse_tools("--srcfile", ST_EXTARGS_TYPE::str,                1, string("")),	
		args_analyse_tools("--dstfile", ST_EXTARGS_TYPE::str,                1, string("")),
		args_analyse_tools()  //最后一个，用于结束
	};

	/* 不带任何参数做特殊处理，打印提示信息后结束 */
	if (argc == 1) {
		usage(argv[0]);
		return -1;
	}

	int need_fixed_args = 0;	//需要固定参数
	int cur_argc;

	/* 最后一个参数：1 - 表示除选项参数外，还需要其它参数
					  例1：Windows/Linux下的ping命令，ping IP地址是最基本的命令格式，另外还有很多-/--开头的可选参数
						  ping 192.168.80.230
						  ping -t -n 10 192.168.80.230
					 例2：Linux下的c++命令，c++ 源程序文件名是最基本的命令格式，另外还有很多-/--开头的可选参数
						  c++ test.cpp
						  c++ -Wall -o test test.cpp
				  0 - 表示除选项参数外，不需要其它参数
		函数返回值：-1 - 处理过程有错
					>0 - 可变参数处理完成后，当前停在argv[]的第几个下标位置，如果后面还有argv[]，则表示固定参数
	*/
	if ((cur_argc = args_analyse_process(argc, argv, args, need_fixed_args)) < 0)
	{
		//错误信息在函数中已打印
		return -1;
	}

	/* 带--help参数做特殊处理，打印提示信息后结束 */
	if (args[ARGS_HELP].existed()) {
		usage(argv[0]);
		return -1;
	}

	/* 必须同时指定 --srcfile 和 --dstfile，否则报错 */
	if (args[ARGS_SRCFILE].existed() + args[ARGS_DSTFILE].existed() != 2) {
		cout << "必须指定源文件名(--srcfile)和目标文件名(--dstfile)，位置及顺序任意" << endl;
		usage(argv[0]);
		return -1;
	}

	/* 打印参数分析的结果 */
	cout << "可变参数列表:" << endl;
	args_analyse_print(args);

	/* 打印参数的值 */
	cout << "参数检查通过" << endl;
	cout << " --convert参数：" << args[ARGS_CONVERT].get_string() << endl;
	cout << " 源文件名是   ：" << args[ARGS_SRCFILE].get_string() << endl;
	cout << " 目标文件名是 ：" << args[ARGS_DSTFILE].get_string() << endl;

	/* 此处应给出真正的实现（本题不需要） */

#endif

	return 0;
}
