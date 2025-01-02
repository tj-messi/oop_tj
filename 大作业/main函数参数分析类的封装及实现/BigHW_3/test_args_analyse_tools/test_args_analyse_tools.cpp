/* 学号 姓名 班级 */
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "../include/class_aat.h"
using namespace std;

enum OPT_ARGS {
	ARGS_HELP,
	ARGS_BOOL,
	ARGS_INT_DEF,
	ARGS_INT_ERR,
	ARGS_INTSET_DEF,
	ARGS_INTSET_ERR,
	ARGS_DOUBLE_DEF,
	ARGS_DOUBLE_ERR,
	ARGS_DOUBLESET_DEF,
	ARGS_DOUBLESET_ERR,
	ARGS_STR1,
	ARGS_STR2,
	ARGS_STRSET_DEF,
	ARGS_STRSET_ERR,
	ARGS_IPADDR_DEF,
	ARGS_IPADDR_ERR
};

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

	string hashtype[] = { "md5","sha1","sha224","sha256","sha384","sha512","all", "" };	//结尾必须是""
	int intset[] = { 11, 22, 33, 123, 345, INVALID_INT_VALUE_OF_SET }; 				//结尾必须是INVALID_INT_VALUE_OF_SET
	double doubleset[] = { 1.1, 2.2, 3.3, 12.3, 3.45, INVALID_DOUBLE_VALUE_OF_SET }; 				//结尾必须是INVALID_INT_VALUE_OF_SET

	args_analyse_tools args[] = {
		args_analyse_tools("--help",      ST_EXTARGS_TYPE::boolean, 0, false),
		args_analyse_tools("--bool",      ST_EXTARGS_TYPE::boolean, 0, true),
		args_analyse_tools("--intdef",    ST_EXTARGS_TYPE::int_with_default,        1, 12345, 0, 65535),
		args_analyse_tools("--interr",    ST_EXTARGS_TYPE::int_with_error,          1, 12345, 0, 65535),	//参数12345可为任何值，无意义
		args_analyse_tools("--intsetdef", ST_EXTARGS_TYPE::int_with_set_default,    1, 2, intset),		//参数2代表default为set中的第[2]个值，即33，如果此值超范围，缺省0
		args_analyse_tools("--intseterr", ST_EXTARGS_TYPE::int_with_set_error,      1, 2, intset),		//参数2无意义，不用
		args_analyse_tools("--doubledef",		ST_EXTARGS_TYPE::double_with_default,		1, 1.23, -2.5, 99.9),
		args_analyse_tools("--doubleerr",		ST_EXTARGS_TYPE::double_with_error,		1, 1.23, -2.5, 99.9),	//参数12345可为任何值，无意义
		args_analyse_tools("--doublesetdef",	ST_EXTARGS_TYPE::double_with_set_default,	1, 2, doubleset),		//参数2代表default为set中的第[2]个值，即33，如果此值超范围，缺省0
		args_analyse_tools("--doubleseterr",	ST_EXTARGS_TYPE::double_with_set_error,	1, 2, doubleset),		//参数2无意义，不用
		args_analyse_tools("--str1",      ST_EXTARGS_TYPE::str,                  1, string("")),		//必须加string()，否则被适配到args_analyse(const char *arg_name, enum ST_EXTARGS_TYPE type, int ext_num, bool def)
		args_analyse_tools("--str2",      ST_EXTARGS_TYPE::str,                  1, string("Hello")),	//必须加string()，否则被适配到args_analyse(const char *arg_name, enum ST_EXTARGS_TYPE type, int ext_num, bool def)
		args_analyse_tools("--strsetdef", ST_EXTARGS_TYPE::str_with_set_default, 1, 3, hashtype),		//参数3代表default为set中的第[3]个值，即sha256，如果此值超范围，缺省0
		args_analyse_tools("--strseterr", ST_EXTARGS_TYPE::str_with_set_error,   1, 3, hashtype),		//参数3无意义，不用
		args_analyse_tools("--ipdef",     ST_EXTARGS_TYPE::ipaddr_with_default,     1, string("192.168.80.230")),
		args_analyse_tools("--iperr",     ST_EXTARGS_TYPE::ipaddr_with_error,       1, string("")), //空表示0.0.0.0
		args_analyse_tools()  //最后一个，用于结束
	};

	int need_fixed_args = 0;	//试试改为1
	int cur_argc;

	/* 最后一个参数：1 - 表示除选项参数外，还需要其它参数
					  例1：Windows/Linux下的ping命令，ping IP地址是最基本的命令格式，另外还有很多-/--开头的可选参数
						  ping 192.168.80.230
						  ping -t -n 10 192.168.80.230
					 例2：Linux下的c++命令，c++ 源程序文件名是最基本的命令格式，另外还有很多-/--开头的可选参数
						  c++ test.cpp
						  c++ -Wall -o test test.cpp
				  0 - 表示除选项参数外，不需要其它参数 */
	if ((cur_argc = args_analyse_process(argc, argv, args, need_fixed_args)) < 0)
	{
		//错误信息在函数中已打印
		return -1;
	}

	/* 参数分析完成后的错误处理 */
	if (need_fixed_args) {
		if (cur_argc == argc) {  //说明后面没有跟需要的固定参数
			cout << "指定需要固定参数，但未给出" << endl;
			return -1;
		}

		/* 此处应该处理要求的固定参数，本例中简单打印即可 */
		cout << "还有" << argc - cur_argc << "个固定参数，具体某个参数对应的动作由具体程序决定，本处忽略" << endl;
		for (int i = cur_argc; i < argc; i++)
			cout << argv[i] << endl;
	}

	/* 打印一些提示信息 */
	cout << endl << "请认真观察打印输出中，对应项的exist是否为1，值是否为预期" << endl << endl;

	cout << "查看default与error区别的方法：" << endl;
	cout << "  给出不在指定范围内的值，会看出差别" << endl;
	cout << "  例：--intdef 100000" << endl;
	cout << "      --interr 100000" << endl;
	cout << endl;

	/* 打印参数的分析结果 */
	args_analyse_print(args);

	/* 如果是一个有具体要求的应用程序，则执行到此处，参数分析完成，进入实验具体功能的阶段 */

	/* 打印出所有参数的可用值 */
	const int w1 = 16, w2 = 24, w3 = 20, w4 = 20;
	/* 打印标题及横线 */
	cout << setw(w1 + w2 + w3 + w4) << setfill('=') << '=' << setfill(' ') << endl;
	cout << setw(w1) << "参数名" << setw(w2) << "参数是否出现在命令行中" << setw(w3) << "值1" << setw(w4) << "值2" << endl;
	cout << setw(w1 + w2 + w3 + w4) << setfill('=') << '=' << setfill(' ') << endl;

	/* --------------------------------------------------------------
		注意：不是一定要出现可执行文件命令行中的参数的值才能被使用
		      如果用不出现参数的值，则取缺省值
		例如：ping命令的实现，有以下参数：
				args_analyse_tools("--n", ST_EXTARGS_TYPE::int_with_default, 1, 10, 1, 65535),
			  则ping 10.80.42.230，--n的值用get_int()能取到10，即缺省值
			    ping -n 15 10.80.42.230，--n的值用get_int()能取到15
				ping -n 100000 10.80.42.230，--n的值用get_int()能取到10，即缺省值
	   --------------------------------------------------------------*/

	cout << setw(w1) << args[ARGS_BOOL].get_name() << setw(w2) << args[ARGS_BOOL].existed() << (args[ARGS_BOOL].existed() ? "True" : "False") << endl; //bool型，只要existed，就认为是true，没有单独的get_bool()函数

	cout << setw(w1) << args[ARGS_INT_DEF].get_name() << setw(w2) << args[ARGS_INT_DEF].existed() << setw(w3) << args[ARGS_INT_DEF].get_int() << endl;
	cout << setw(w1) << args[ARGS_INT_ERR].get_name() << setw(w2) << args[ARGS_INT_ERR].existed() << setw(w3) << args[ARGS_INT_ERR].get_int() << endl;
	cout << setw(w1) << args[ARGS_INTSET_DEF].get_name() << setw(w2) << args[ARGS_INTSET_DEF].existed() << setw(w3) << args[ARGS_INTSET_DEF].get_int() << endl;
	cout << setw(w1) << args[ARGS_INTSET_ERR].get_name() << setw(w2) << args[ARGS_INTSET_ERR].existed() << setw(w3) << args[ARGS_INTSET_ERR].get_int() << endl;

	cout << setw(w1) << args[ARGS_DOUBLE_DEF].get_name() << setw(w2) << args[ARGS_DOUBLE_DEF].existed() << setw(w3) << args[ARGS_DOUBLE_DEF].get_double() << endl;
	cout << setw(w1) << args[ARGS_DOUBLE_ERR].get_name() << setw(w2) << args[ARGS_DOUBLE_ERR].existed() << setw(w3) << args[ARGS_DOUBLE_ERR].get_double() << endl;
	cout << setw(w1) << args[ARGS_DOUBLESET_DEF].get_name() << setw(w2) << args[ARGS_DOUBLESET_DEF].existed() << setw(w3) << args[ARGS_DOUBLESET_DEF].get_double() << endl;
	cout << setw(w1) << args[ARGS_DOUBLESET_ERR].get_name() << setw(w2) << args[ARGS_DOUBLESET_ERR].existed() << setw(w3) << args[ARGS_DOUBLESET_ERR].get_double() << endl;

	/* 默认值为空的情况，为了看清楚，打印<NULL> */
	cout << setw(w1) << args[ARGS_STR1].get_name() << setw(w2) << args[ARGS_STR1].existed() << setw(w3) << (args[ARGS_STR1].get_string().empty() ? "<NULL>" : args[ARGS_STR1].get_string()) << endl;
	cout << setw(w1) << args[ARGS_STR2].get_name() << setw(w2) << args[ARGS_STR2].existed() << setw(w3) << args[ARGS_STR2].get_string() << endl;

	cout << setw(w1) << args[ARGS_STRSET_DEF].get_name() << setw(w2) << args[ARGS_STRSET_DEF].existed() << setw(w3) << args[ARGS_STRSET_DEF].get_string() << endl;
	cout << setw(w1) << args[ARGS_STRSET_ERR].get_name() << setw(w2) << args[ARGS_STRSET_ERR].existed() << setw(w3) << args[ARGS_STRSET_ERR].get_string() << endl;

	/* u_int形式的IP地址，用hex打印，打印完成后再转为dec */
	cout << setw(w1) << args[ARGS_IPADDR_DEF].get_name() << setw(w2) << args[ARGS_IPADDR_DEF].existed() << setw(w3) << hex << args[ARGS_IPADDR_DEF].get_ipaddr() << dec << setw(w4) << args[ARGS_IPADDR_DEF].get_str_ipaddr() << endl;
	cout << setw(w1) << args[ARGS_IPADDR_ERR].get_name() << setw(w2) << args[ARGS_IPADDR_ERR].existed() << setw(w3) << hex << args[ARGS_IPADDR_ERR].get_ipaddr() << dec << setw(w4) << args[ARGS_IPADDR_ERR].get_str_ipaddr() << endl;

	/* 打印横线 */
	cout << setw(w1 + w2 + w3 + w4) << setfill('=') << '=' << setfill(' ') << endl;

	return 0;
}

#if 0
// 测试用例

test_args_analyse_tools --help

test_args_analyse_tools --bool	//值为true

test_args_analyse_tools --intdef 123				//值123
test_args_analyse_tools --intdef 123 --intdef 456	//报错：重复
test_args_analyse_tools --intdef -12				//默认值12345
test_args_analyse_tools --intdef 654321				//默认值12345

test_args_analyse_tools --interr 123				//值123
test_args_analyse_tools --interr 123 --interr 456	//报错：重复
test_args_analyse_tools --interr -12				//报错：值非法
test_args_analyse_tools --interr 654321				//报错：值非法

test_args_analyse_tools --intsetdef 11					//值11
test_args_analyse_tools --intsetdef 12					//默认值33
test_args_analyse_tools --intsetdef 11 --intsetdef 22	//报错：重复

test_args_analyse_tools --intseterr 11					//值11
test_args_analyse_tools --intseterr 12					//报错：值非法
test_args_analyse_tools --intseterr 11 --intseterr 22	//报错：重复

test_args_analyse_tools --doubledef 2.34					//值2.34
test_args_analyse_tools --doubledef 2.34 --doubledef 4.32	//报错：重复
test_args_analyse_tools --doubledef -3						//默认值1.23（因为VS会自动调整格式，如果- 3，删除之间的空格）
test_args_analyse_tools --doubledef 101.234					//默认值1.23

test_args_analyse_tools --doubleerr 2.34					//值2.34
test_args_analyse_tools --doubleerr 2.34 --doubledef 4.32	//报错：重复
test_args_analyse_tools --doubleerr -3						//报错：值非法（因为VS会自动调整格式，如果- 3，删除之间的空格）
test_args_analyse_tools --doubleerr 101.234					//报错：值非法

test_args_analyse_tools --doublesetdef 12.3						//值12.3
test_args_analyse_tools --doublesetdef 5.6						//默认值3.3
test_args_analyse_tools --doublesetdef 1.1 --doublesetdef 2.2	//报错：重复

test_args_analyse_tools --doubleseterr 12.3						//值12.3
test_args_analyse_tools --doubleseterr 5.6						//报错：值非法
test_args_analyse_tools --doubleseterr 1.1 --doubleseterr 2.2	//报错：重复

test_args_analyse_tools --str1 hello				//值hello
test_args_analyse_tools --str1 hello --str1 horse	//报错：重复

test_args_analyse_tools --str2 hello				//值hello
test_args_analyse_tools --str2 hello --str2 horse	//报错：重复

test_args_analyse_tools --strsetdef md5						//值md5
test_args_analyse_tools --strsetdef md4						//值sha256
test_args_analyse_tools --strsetdef md5 --strsetdef sha1	//报错:重复

test_args_analyse_tools --strseterr md5						//值md5
test_args_analyse_tools --strseterr md4						//报错：值非法
test_args_analyse_tools --strseterr md5 --strseterr sha1	//报错:重复

test_args_analyse_tools --ipdef 1.1.1.1						//值1.1.1.1
test_args_analyse_tools --ipdef 1.1.1.1234					//值192.168.80.230
test_args_analyse_tools --ipdef 1.1.1.1 --ipdef 2.2.2.2		//报错：重复

test_args_analyse_tools --iperr 1.1.1.1						//值1.1.1.1
test_args_analyse_tools --iperr 1.1.1.1234					//报错：值非法
test_args_analyse_tools --iperr 1.1.1.1 --iperr 2.2.2.2		//报错：重复

//上面各测试项的任意组合：
#endif
