#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <conio.h>
#include "../include/class_aat.h"
#include "../include/class_cft.h"
using namespace std;

#define TEST_FOR_FIXED_FILE	1

#if TEST_FOR_FIXED_FILE

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
void wait_for_enter()
{
	cout << endl << "按回车键继续";
	while (_getch() != '\r')
		;
	cout << endl << endl;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
int readconfig_yzmond_conf(const char *const fname)
{
	config_file_tools sCfg(fname); //分隔符是=

	if (sCfg.is_read_succeeded() == 0) {
		cout << "配置文件[" << fname << "]读取有错." << endl;
		return -1;
	}

	/* 定义本应用程序相关配置项的结构体，每个数据的具体类型根据实际用途决定 */
	struct yzmond_cfg {
		unsigned int dbserver_ip;		//数据库服务器IP地址
		unsigned short dbserver_port;	//数据库服务器端口号
		unsigned short bind_port;		//监听端口号
		bool is_long_tcp;		//是否长连接
		int db_bufsize;			//数据库缓冲区大小
		double memory_toplimit;	//内存使用上限
	} mycfg;

	int port;
	sCfg.item_get_int("[连接设置]", "监听端口号", port, 0, 65535, 41109);
	/* 因为没有 item_get_short，又不能在传入时将short强制转换为int，因此先用临时变量去读，再赋值
	   因为限制了0-65535，不会超过u_short的界限 */
	mycfg.bind_port = port;

	char sel;
	sCfg.item_get_char("[连接设置]", "允许长连接", sel, "YyNn", 'n');
	/* 配置文件中该项目约定只能填写YyNy，因此读出来后按需做转换 */
	mycfg.is_long_tcp = (sel == 'Y' || sel == 'y') ? true : false;

	sCfg.item_get_int("[数据库]", "服务器端口号", port, 0, 65535, 3306);
	mycfg.dbserver_port = port;

	sCfg.item_get_ipaddr("[数据库]", "服务器IP地址", mycfg.dbserver_ip, 0xC0A850E6); // 默认"192.168.80.230"
	sCfg.item_get_int("[数据库]", "数据库缓冲区", mycfg.db_bufsize);
	/* 配置文件中的单位是MB，转为字节 */
	mycfg.db_bufsize *= 1024 * 1024;

	sCfg.item_get_double("[系统设置]", "内存使用比例", mycfg.memory_toplimit, 0, 80, 60);

	/* 打印配置值 */
	cout << "bind_port = " << mycfg.bind_port << endl;
	cout << "dbserver_ip = " << hex << mycfg.dbserver_ip << dec << endl;
	cout << "dbserver_port = " << mycfg.dbserver_port << endl;
	cout << "log_tcp = " << (mycfg.is_long_tcp ? "Yes":"No") << endl;
	cout << "db_bufsize = " << mycfg.db_bufsize << "字节" << endl;
	cout << "memory_toplimit = " << mycfg.memory_toplimit << "%" << endl;

	/* 后续程序执行，在后续程序中会用到mycfg的各项配置 */

	return 0;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
 ***************************************************************************/
int readconfig_php_ini(const char* const fname)
{
	config_file_tools sCfg(fname); //分隔符是=

	if (sCfg.is_read_succeeded() == 0) {
		cout << "配置文件[" << fname << "]读取有错." << endl;
		return -1;
	}

	/* 打印[ODBC]组的所有项的原始信息 */
	const char* const gname = "[ODBC]";
	cout << "取配置文件中的" << gname << "组：" << endl;
	vector <string> item;
	if (sCfg.get_all_item(gname, item) == 0) {
		cout << "未取到配置文件 [" << fname << "] 的 [" << gname << "] 组." << endl;
		return -1;
	}

	for (auto& it : item)
		cout << '*' << it << '*' << endl; //前后加*便于看清空格等隐含字符
	cout << endl;

	/* 取几个具体的项（返回该行，包括名称和值）*/
	char value[16];
	sCfg.item_get_cstring("[ODBC]", "odbc.allow_persistent", value, sizeof(value));
	cout << "allow_persistent = " << value << endl;

	int max_links;
	sCfg.item_get_int("[POSTGRESQL]", "pgsql.max_links", max_links);
	cout << "max_links = " << max_links << endl;

	return 0;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：严格来说，httpd.conf是另一种风格的配置文件，
			例：这是Directory组的示例
				<Directory />
					AllowOverride none
					Require all denied
				</Directory>
			适配到目前要求的配置文件，只能做为不含组的简单配置文件来读取
 ***************************************************************************/
int readconfig_httpd_conf(const char* const fname)
{
	config_file_tools sCfg(fname, BREAK_CTYPE::Space); //分隔符是空格/tab

	if (sCfg.is_read_succeeded() == 0) {
		cout << "配置文件[" << fname << "]读取有错." << endl;
		return -1;
	}

	/* 取几个具体的项（返回该行，包括名称和值）*/
	char value[32];
	sCfg.item_get_cstring("", "serverroot", value, sizeof(value)); //项目大小写不敏感
	cout << "ServerRoot = " << value << endl;

	string charset;
	sCfg.item_get_string("", "AddDefaultCharSet", charset);
	cout << "AddDefaultCharSet = " << charset << endl;

	string indexfile;
	sCfg.item_get_raw("", "DirectoryIndex", indexfile);
	cout << "DirectoryIndex = " << indexfile << endl;
	/* 后续再进行处理，取到空格分开的多个文件名，此处略 */

	return 0;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
int readconfig_homework_conf(const char* const fname)
{
	config_file_tools sCfg(fname); //分隔符是=

	if (sCfg.is_read_succeeded() == 0) {
		cout << "配置文件[" << fname << "]读取有错." << endl;
		return -1;
	}

	/* 定义本应用程序相关配置项的结构体，每个数据的具体类型根据实际用途决定 */
	struct hw_cfg {
		string src_rootdir;			//学生提交源文件的根目录
		int score_deducting_base;	//基本扣分
		int score_deducting_bighw_one_warning; //大作业warning单个分数
		int score_deducting_bighw_max_warnings; //大作业warning单个分数
		int score_deducting_format;
	} mycfg;

	sCfg.item_get_string("[文件目录]", "src_rootdir", mycfg.src_rootdir);

	sCfg.item_get_int("[成绩计算]", "score_deducting_base", mycfg.score_deducting_base);
	sCfg.item_get_int("[成绩计算]", "score_deducting_format", mycfg.score_deducting_format);

	/* 大作业警告扣分的格式不是单int，先string取出来再处理 */
	string bighw_warning_str;
	sCfg.item_get_raw("[成绩计算]", "score_deducting_warning_bighw", bighw_warning_str);
	istringstream in(bighw_warning_str);
	in >> mycfg.score_deducting_bighw_one_warning >> mycfg.score_deducting_bighw_max_warnings;
	/* 应该再对读到的数据进行范围检查，demo略 */

	/* 打印配置值 */
	cout << "提交作业根目录    ：" << mycfg.src_rootdir << endl;
	cout << "基础检查扣分      ：" << mycfg.score_deducting_base << endl;
	cout << "大作业warning扣分 ：每个" << mycfg.score_deducting_bighw_one_warning << "分，上限" << mycfg.score_deducting_bighw_max_warnings << "个" << endl;
	cout << "源代码格式扣分    ：" << mycfg.score_deducting_format << endl;

	/* 后续程序执行，在后续程序中会用到mycfg的各项配置 */

	/* 专业全称和简称的对应关系虽然是 xxx=yyy格式，但xxx未知（如果把专业全称写死在文件中再用 get_item_string 去读简称是非常愚蠢的非工程行为!!!），
		需要全部取出来，后续再单独处理 */
	const char *const gname = "[专业全称简称对照]";
	vector <string> fname_sname_table;
	if (sCfg.get_all_item(gname, fname_sname_table) == 0) {
		cout << "未取到配置文件 [" << fname << "] 的 [" << gname << "] 组." << endl;
		return -1;
	}

	cout << endl;
	cout << gname << endl;
	for (auto& it : fname_sname_table)
		cout << '*' << it << '*' << endl; //前后加*便于看清空格等隐含字符
	cout << endl;
	/* 后续再对 fname_sname_table 进行分解，此处略 */

	/* 取本学期的课号 */
	vector <string> cno_table;
	if (sCfg.get_all_item("[课号]", cno_table) == 0) {
		cout << "未取到配置文件 [" << fname << "] 的 [课号] 组." << endl;
		return -1;
	}

	cout << endl;
	cout << "[课号]" << endl;
	for (auto& it : cno_table)
		cout << it << endl; //前后加*便于看清空格等隐含字符
	cout << endl;

	return 0;
}


#endif

#if !TEST_FOR_FIXED_FILE
enum OPT_ARGS {
	OPT_ARGS_HELP = 0,
	OPT_ARGS_DEBUG,
	OPT_ARGS_CFGFILE,
	OPT_ARGS_GROUP_NAME,
	OPT_ARGS_ITEM_NAME,
	OPT_ARGS_GROUP_NAME_CASE_SENSITIVE,
	OPT_ARGS_ITEM_NAME_CASE_SENSITIVE,
	OPT_ARGS_ITEM_BREAK_CHARACTER,
	OPT_ARGS_ITEM_TYPE
};
#endif

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
int main(int argc, char* argv[])
{
#if TEST_FOR_FIXED_FILE //测试几个固定的配置文件的读法（这是配置文件工具集真正的使用场景）

	readconfig_yzmond_conf("yzmond.conf");
	cout << endl;
	wait_for_enter();

	readconfig_php_ini("php-win.ini");
	cout << endl;
	wait_for_enter();

	readconfig_php_ini("php-linux.ini");
	cout << endl;
	wait_for_enter();

	readconfig_httpd_conf("httpd.conf");
	cout << endl;
	wait_for_enter();

	readconfig_homework_conf("homework.conf");
	cout << endl;

#else //进入自由测试，即键盘输入文件名、组名、项目等（用于验证你写的函数集中各函数的正确性）

	/* 指定读取的数据的类型 */
	const string itemtype_set[] = { "raw", "null", "char", "int", "double", "cstring", "string", "ip", "" };	//结尾必须是""
	/* 指定每项的名/值之间的分隔符
		equal : 单字符 =
		space : 空格、tab都算，如果有多个，按第一个算 */
	const string break_character_set[] = { "equal", "space", "" };	//结尾必须是""

	args_analyse_tools args[] = {
		args_analyse_tools("--help",     ST_EXTARGS_TYPE::boolean, 0, false),
		args_analyse_tools("--debug",    ST_EXTARGS_TYPE::boolean, 0, false),
		args_analyse_tools("--cfgfile",  ST_EXTARGS_TYPE::str, 1, string("")),	//必须加string()，否则被适配到args_analyse(const char *arg_name, enum ST_EXTARGS_TYPE type, int ext_num, bool def)
		args_analyse_tools("--group",    ST_EXTARGS_TYPE::str, 1, string("all")),	//不带[]的all则表示全部group
		args_analyse_tools("--item",     ST_EXTARGS_TYPE::str, 1, string("all")),	//必须加string()，否则被适配到args_analyse(const char *arg_name, enum ST_EXTARGS_TYPE type, int ext_num, bool def)
		args_analyse_tools("--gcs",      ST_EXTARGS_TYPE::boolean, 0, false),      //组名区分大小写（--group_case_sensitive，为了输入方便用缩写--gcs）
		args_analyse_tools("--ics",      ST_EXTARGS_TYPE::boolean, 0, false),      //项名区分大小写（--item_case_sensitive，为了输入方便用缩写--）
		args_analyse_tools("--brkchar",  ST_EXTARGS_TYPE::str_with_set_error, 1, 0, break_character_set),	//项名/项值的默认分隔符是=，可以制定多个，和其中的任意一个匹配即可
		args_analyse_tools("--type",     ST_EXTARGS_TYPE::str_with_set_error, 1, 0, itemtype_set),		//参数3无意义，不用
		args_analyse_tools()  //最后一个，用于结束
	};

	int cur_argc;

	//最后一个参数1，表示除选项参数外，还有其它参数
	if ((cur_argc = args_analyse_process(argc, argv, args, 0)) < 0) {
		//错误信息在函数中已打印
		return -1;
	}

	const bool is_help = args[OPT_ARGS_HELP].existed(); //后面多出要用，先取值出来，提高效率
	const bool is_debug = args[OPT_ARGS_DEBUG].existed(); //后面多出要用，先取值出来，提高效率
	const bool is_group_case_sensitive = args[OPT_ARGS_GROUP_NAME_CASE_SENSITIVE].existed(); //后面多出要用，先取值出来，提高效率
	const bool is_item_case_sensitive = args[OPT_ARGS_ITEM_NAME_CASE_SENSITIVE].existed(); //后面多出要用，先取值出来，提高效率
	const enum BREAK_CTYPE ctype = (args[OPT_ARGS_ITEM_BREAK_CHARACTER].get_string() == "space") ? BREAK_CTYPE::Space : BREAK_CTYPE::Equal;
	const string item_type = args[OPT_ARGS_ITEM_TYPE].get_string();

	/* 如果加了 --help | --debug 则打印，且 --help 打印完即退出 */
	if (is_help || is_debug) {
		args_analyse_print(args);
		if (is_help)
			return -1;
	}

	if (args[OPT_ARGS_CFGFILE].existed() == 0) {
		args_analyse_print(args);
		cout << "必须带" << args[OPT_ARGS_CFGFILE].get_name() << "参数." << endl << endl;
		return -1;
	}

	if (args[OPT_ARGS_GROUP_NAME].existed() == 0 && args[OPT_ARGS_ITEM_NAME].existed() != 0) {
		cout << "使用--item前必须先指定--group(\"\"表示group为空" << endl;
		return -1;
	}

	config_file_tools sCfg(args[OPT_ARGS_CFGFILE].get_string(), ctype);

	if (sCfg.is_read_succeeded() == 0) {
		cout << "配置文件[" << args[OPT_ARGS_CFGFILE].get_string() << "]读取不成功" << endl;
		return -1;
	}

	/* 如果无--group 或 --group all，则打印全部内容 */
	if (args[OPT_ARGS_GROUP_NAME].get_string() == "all") {
		vector <string> groups;
		int group_num = sCfg.get_all_group(groups);
		if (group_num == 0)
			return 0;	//组为空（含简单配置的空组名）则不打印

		for (const auto& one_group : groups) {
			/* 取每组的所有项 */
			vector <string> items;
			int items_num = sCfg.get_all_item(one_group, items, is_group_case_sensitive);

			cout << "组名 : " << (one_group.empty() ? "<NULL>" : one_group) << " 项数 : " << items_num << endl; //简单配置文件的空组名打印为<NULL>
			for (const auto& one_item : items)
				cout << "    项 : " << one_item << endl;

			cout << endl; //每组空一行
		}
	}
	else { //打印某个group下的所有项或者某项（组名带[]，例：--group [test]）
		string group_name_wanted = args[OPT_ARGS_GROUP_NAME].get_string();

		/* 取 print_group_name 组的所有项（注：测试时不要有项目叫all） */
		if (args[OPT_ARGS_ITEM_NAME].get_string() == "all") {
			vector <string> items;
			int items_num = sCfg.get_all_item(group_name_wanted, items, is_group_case_sensitive);

			if (items_num > 0) { //找到
				cout << "组名 : " << group_name_wanted << " 项数 : " << items_num << endl;
				for (const auto& one_item : items)
					cout << "    项 : " << one_item << endl;
			}
			else //未找到
				cout << "未找到组" << group_name_wanted << endl;
		}
		else { //取单项（必须是 xxx = yyy形式，否则取不到）
			string item_name_wanted = args[OPT_ARGS_ITEM_NAME].get_string();

			/* --type未指定 或 --type raw，则取值的原始内容（即指定分隔符后的所有字符，以string形式呈现）*/
			if (item_type == "raw") {
				string item;
				int ret = sCfg.item_get_raw(group_name_wanted, item_name_wanted, item, is_group_case_sensitive, is_item_case_sensitive);
				if (ret)
					cout << "找到组" << group_name_wanted << "/项" << item_name_wanted << "，原始内容为[" << item << "]." << endl;
				else
					cout << "未找到组" << group_name_wanted << "/项" << item_name_wanted << "，请检查组名/项目是否正确." << endl;
			}
			else { //制定了具体数据类型（如果类型错误，不是你的错）
				/* 找到，value中是字符串形式的原始值，将值取出，转换为对应类型数据即可
					注：默认值、范围等为了简化，没有通过参数可变，写死了 */
				if (item_type == "null") {
					/* 先测试最简使用：组名大小写不敏感、项名大小写不敏感 */
					if (sCfg.item_get_null(group_name_wanted, item_name_wanted, is_group_case_sensitive, is_item_case_sensitive) > 0)
						cout << "找到组\"" << group_name_wanted << "\"/项\"" << item_name_wanted << "\"." << endl;
					else
						cout << "未找到组\"" << group_name_wanted << "\"/项\"" << item_name_wanted << "\"." << endl;
				}
				else if (item_type == "char") {
					char c_value;

					/* 先测试最简使用：无缺省值、无可选集合（任意字符均合法）、组名大小写不敏感、项名大小写不敏感 */
					if (sCfg.item_get_char(group_name_wanted, item_name_wanted, c_value) > 0)
						cout << "找到组\"" << group_name_wanted << "\"/项\"" << item_name_wanted << "\"，char型的值为[" << c_value << "/" << int(c_value) << "]." << endl; //加int值方便看清
					else
						cout << "未找到组\"" << group_name_wanted << "\"/项\"" << item_name_wanted << "\"的char型值，请检查组名/项目/数据类型是否正确." << endl;

					cout << endl;

					/* 其次测试有可选集合、无缺省值的情况（因为需要--gcs和--ics，因此默认值只能设上）
					   如果不考虑大小写敏感，则此句简化为 sCfg.item_get_char(group_name_wanted, item_name_wanted, c_value, "YyNn");	 */
					if (sCfg.item_get_char(group_name_wanted, item_name_wanted, c_value, "YyNn", DEFAULT_CHAR_VALUE, is_group_case_sensitive, is_item_case_sensitive) > 0)
						cout << "找到组\"" << group_name_wanted << "\"/项\"" << item_name_wanted << "\"，char型的值为[" << c_value << "/" << int(c_value) << "]." << endl; //加int值方便看清
					else
						cout << "未找到组\"" << group_name_wanted << "\"/项\"" << item_name_wanted << "\"的char型值，请检查组名/项目/数据类型是否正确." << endl;

					cout << endl;

					/*  最后测试有可选集、有缺省值的情况*/
					if (sCfg.item_get_char(group_name_wanted, item_name_wanted, c_value, "YyNn", 'Y', is_group_case_sensitive, is_item_case_sensitive) > 0)
						cout << "找到组\"" << group_name_wanted << "\"/项\"" << item_name_wanted << "\"，char型的值为[" << c_value << "/" << int(c_value) << "]." << endl; //加int值方便看清
				}
				else if (item_type == "int") {
					int i_value;

					/* 先测试最简使用：无缺省值、无合理范围、组名大小写不敏感、项名大小写不敏感 */
					if (sCfg.item_get_int(group_name_wanted, item_name_wanted, i_value) > 0)
						cout << "找到组" << group_name_wanted << "/项" << item_name_wanted << "，int型的值为[" << i_value << "]." << endl;
					else
						cout << "未找到组" << group_name_wanted << "/项" << item_name_wanted << "的int型值，请检查组名/项目/数据类型是否正确." << endl;

					cout << endl;

					/* 其次测试有上下限、无缺省值的情况（因为需要--gcs和--ics，因此默认值只能设上）
					   如果不考虑大小写敏感，则此句简化为 sCfg.item_get_int(group_name_wanted, item_name_wanted, i_value, -2, 100);	 */
					if (sCfg.item_get_int(group_name_wanted, item_name_wanted, i_value, -2, 100, DEFAULT_INT_VALUE, is_group_case_sensitive, is_item_case_sensitive) > 0)
						cout << "找到组" << group_name_wanted << "/项" << item_name_wanted << "，int型的值为[" << i_value << "]." << endl;
					else
						cout << "未找到组" << group_name_wanted << "/项" << item_name_wanted << "的int型值，请检查组名/项目/数据类型是否正确." << endl;

					cout << endl;

					/*  最后测试有上下限、有缺省值的情况*/
					if (sCfg.item_get_int(group_name_wanted, item_name_wanted, i_value, -2, 100, 10, is_group_case_sensitive, is_item_case_sensitive) > 0)
						cout << "找到组" << group_name_wanted << "/项" << item_name_wanted << "，int型的值为[" << i_value << "]." << endl;
				}
				else if (item_type == "double") {
					double d_value;

					/* 先测试最简使用：无缺省值、无合理范围、组名大小写不敏感、项名大小写不敏感 */
					if (sCfg.item_get_double(group_name_wanted, item_name_wanted, d_value) > 0)
						cout << "找到组" << group_name_wanted << "/项" << item_name_wanted << "，double型的值为[" << d_value << "]." << endl;
					else
						cout << "未找到组" << group_name_wanted << "/项" << item_name_wanted << "的double型值，请检查组名/项目/数据类型是否正确." << endl;

					cout << endl;

					/* 其次测试有上下限、无缺省值的情况（因为需要--gcs和--ics，因此默认值只能设上）
					   如果不考虑大小写敏感，则此句简化为 sCfg.item_get_double(group_name_wanted, item_name_wanted, d_value, -31.1, +75.2);	 */
					if (sCfg.item_get_double(group_name_wanted, item_name_wanted, d_value, -31.1, +75.2, DEFAULT_DOUBLE_VALUE, is_group_case_sensitive, is_item_case_sensitive) > 0)
						cout << "找到组" << group_name_wanted << "/项" << item_name_wanted << "，double型的值为[" << d_value << "]." << endl;
					else
						cout << "未找到组" << group_name_wanted << "/项" << item_name_wanted << "的double型值，请检查组名/项目/数据类型是否正确." << endl;

					cout << endl;

					/*  最后测试有上下限、有缺省值的情况*/
					if (sCfg.item_get_double(group_name_wanted, item_name_wanted, d_value, -31.1, +75.2, 1.2, is_group_case_sensitive, is_item_case_sensitive) > 0)
						cout << "找到组" << group_name_wanted << "/项" << item_name_wanted << "，double型的值为[" << d_value << "]." << endl;
				}
				else if (item_type == "cstring") {
					char s_value[16];

					/* 先测试最简使用：无最大长度（自动为MAX_STRLEN）、无缺省值、组名大小写不敏感、项名大小写不敏感
					   注：这种方式，只要值的内容超过15字节，都会越界，至于越界表现则出什么都能接受，某些测试项要测试后两种，可能需要注释掉本测试项 */
					if (sCfg.item_get_cstring(group_name_wanted, item_name_wanted, s_value, MAX_STRLEN) > 0)
						cout << "找到组" << group_name_wanted << "/项" << item_name_wanted << "，cstring型的值为[" << s_value << "]." << endl;
					else
						cout << "未找到组" << group_name_wanted << "/项" << item_name_wanted << "的cstring型值，请检查组名/项目/数据类型是否正确." << endl;

					cout << endl;

					/* 其次测试有最大长度、无缺省值的情况（因为需要--gcs和--ics，因此默认值只能设上）
					   如果不考虑大小写敏感，则此句简化为 (sCfg.item_get_cstring(group_name_wanted, item_name_wanted, s_value, sizeof(s_value), "Hello");	 */
					if (sCfg.item_get_cstring(group_name_wanted, item_name_wanted, s_value, sizeof(s_value), DEFAULT_CSTRING_VALUE, is_group_case_sensitive, is_item_case_sensitive) > 0)
						cout << "找到组" << group_name_wanted << "/项" << item_name_wanted << "，cstring型的值为[" << s_value << "]." << endl;
					else
						cout << "未找到组" << group_name_wanted << "/项" << item_name_wanted << "的cstring型值，请检查组名/项目/数据类型是否正确." << endl;

					cout << endl;

					/*  最后测试有最大长度、有缺省值的情况*/
					if (sCfg.item_get_cstring(group_name_wanted, item_name_wanted, s_value, sizeof(s_value), "Hello", is_group_case_sensitive, is_item_case_sensitive) > 0)
						cout << "找到组" << group_name_wanted << "/项" << item_name_wanted << "，cstring型的值为[" << s_value << "]." << endl;
				}
				else if (item_type == "string") {
					string str_value;

					/* 先测试最简使用：无缺省值、组名大小写不敏感、项名大小写不敏感 */
					if (sCfg.item_get_string(group_name_wanted, item_name_wanted, str_value) > 0)
						cout << "找到组" << group_name_wanted << "/项" << item_name_wanted << "，string型的值为[" << str_value << "]." << endl;
					else
						cout << "未找到组" << group_name_wanted << "/项" << item_name_wanted << "的string型值，请检查组名/项目/数据类型是否正确." << endl;

					cout << endl;

					/*  再测试有缺省值的情况*/
					if (sCfg.item_get_string(group_name_wanted, item_name_wanted, str_value, "Tongji", is_group_case_sensitive, is_item_case_sensitive) > 0)
						cout << "找到组" << group_name_wanted << "/项" << item_name_wanted << "，string型的值为[" << str_value << "]." << endl;
				}
				else if (item_type == "ip") {
					unsigned int ipaddr_value;

					/* 先测试最简使用：无缺省值、组名大小写不敏感、项名大小写不敏感 */
					if (sCfg.item_get_ipaddr(group_name_wanted, item_name_wanted, ipaddr_value) > 0)
						cout << "找到组" << group_name_wanted << "/项" << item_name_wanted << "，ipaddr型的值为[" << hex << ipaddr_value << dec << "]." << endl;
					else
						cout << "未找到组" << group_name_wanted << "/项" << item_name_wanted << "的ipaddr型值，请检查组名/项目/数据类型是否正确." << endl;

					cout << endl;

					/*  再测试有缺省值的情况，0xC0A801E6 = 192.168.1.230 */
					if (sCfg.item_get_ipaddr(group_name_wanted, item_name_wanted, ipaddr_value, 0xC0A801E6, is_group_case_sensitive, is_item_case_sensitive) > 0)
						cout << "找到组" << group_name_wanted << "/项" << item_name_wanted << "，ipaddr型的值为[" << hex << ipaddr_value << dec << "]." << endl;
				}
				//都不相等则什么都不做，直接退出
				cout << endl;
			}
		}
	}
#endif  //自由测试结束
	return 0;
}

/* 推荐的自由测试组合(新建一个.bat，将所有内容复制过去即可，注意要保存为ASNI字符集)

rem --------------------------------
rem	取指定配置文件的所有组/组中所有项
rem --------------------------------
test_readcfg --cfgfile httpd.conf
pause
test_readcfg --cfgfile httpd.conf --group all
pause
test_readcfg --cfgfile php.ini
pause
test_readcfg --cfgfile php.ini --group all
pause
test_readcfg --cfgfile my.cnf
pause
test_readcfg --cfgfile yzmond.conf
pause

rem --------------------------------------
rem 	取指定配置文件的指定组中所有项的原始内容
rem --------------------------------------
test_readcfg --cfgfile httpd.conf --group ""
pause
test_readcfg --cfgfile php.ini --group [MSSQL]
pause
test_readcfg --cfgfile php.ini --group [mssql]
pause
test_readcfg --cfgfile php.ini --group [MSSQL] --gcs
rem 大小写敏感，报组找不到
test_readcfg --cfgfile php.ini --group [mssql] --gcs
pause
test_readcfg --cfgfile my.cnf --group ""
pause
test_readcfg --cfgfile my.cnf --group "[mysqld]"
pause
test_readcfg --cfgfile yzmond.conf --group "[数据库]"
pause

rem ----------------------------------------------------------------------------------------------------------
rem	取指定配置文件的指定组中的指定项，返回该项目的值的原始内容（必须是 "项目名 =/空格/tab 值" 形式的项，否则报找不到）
rem ----------------------------------------------------------------------------------------------------------
test_readcfg --cfgfile php.ini --group [MSSQL] --item mssql.max_links
pause
test_readcfg --cfgfile php.ini --group [MSSQL] --gcs --item mssql.max_links
pause
test_readcfg --cfgfile php.ini --group [MSSQL] --gcs --item mssql.max_links --ics
pause
rem 报找不到
test_readcfg --cfgfile php.ini --group [mssql] --gcs --item mssql.max_links
pause
rem 报找不到
test_readcfg --cfgfile php.ini --group [MSSQL] --item mssql.MAX_links --ics
pause
rem 报找不到
test_readcfg --cfgfile php.ini --group [mssql] --gcs --item mssql.max_links --ics
pause

rem httpd.conf 的分隔符是空格，报找不到
test_readcfg --cfgfile httpd.conf --group "" --item EnableSendfile
pause
rem 指定分隔符为空格/tab，找到
test_readcfg --cfgfile httpd.conf --group "" --item EnableSendfile --brkchar space
pause
rem 指定分隔符为空格/tab，找出来错的内容，这不是程序错（程序员必须明确知道配置文件的格式）
test_readcfg --cfgfile php.ini --group [MSSQL] --item mssql.max_links --brkchar space
pause

rem --------------------------------------------------------------------------------------------------------------------------
rem	取指定配置文件的指定组中的指定项，返回该项目的值（必须是 "项目名 =/空格/tab 值" 形式的项，且数据类型要匹配，如果不匹配，不是程序错）
rem		1、null型
rem  注：自主决定是否添加 --gcs 和 --ics
rem --------------------------------------------------------------------------------------------------------------------------
rem 能取到
test_readcfg --cfgfile yzmond.conf --group [连接设置] --item 允许长连接 --type null
pause
rem 能取到
test_readcfg --cfgfile yzmond.conf --group "[连接设置]" --item "允许长连接" --type null
pause
rem 能取到
test_readcfg --cfgfile php.ini --group [soap] --item soap.wsdl_cache_dir --type null
pause
rem 取不到（比上一个测试的item少一个字母）
test_readcfg --cfgfile php.ini --group [soap] --item soap.wsdl_cache_di --type null
pause

rem --------------------------------------------------------------------------------------------------------------------------
rem	取指定配置文件的指定组中的指定项，返回该项目的值（必须是 "项目名 =/空格/tab 值" 形式的项，且数据类型要匹配，如果不匹配，不是程序错）
rem		2、char型
rem  注：自主决定是否添加 --gcs 和 --ics
rem --------------------------------------------------------------------------------------------------------------------------
rem  三种方式都能取到y
test_readcfg --cfgfile yzmond.conf --group [连接设置] --item 允许长连接 --type char
pause
rem 前两种取不到，第三种取到默认值Y
test_readcfg --cfgfile php.ini --group [soap] --item soap.wsdl_cache_dir --type char
pause
rem 第一种取到9（因为任意字符均合法），第二种取不到，因为不在合法集合中且没有默认值，第三种取到默认值Y
test_readcfg --cfgfile yzmond.conf --group [连接设置] --item 设备采样间隔 --type char
pause

rem --------------------------------------------------------------------------------------------------------------------------
rem	取指定配置文件的指定组中的指定项，返回该项目的值（必须是 "项目名 =/空格/tab 值" 形式的项，且数据类型要匹配，如果不匹配，不是程序错）
rem		3、int型
rem  注：自主决定是否添加 --gcs 和 --ics
rem --------------------------------------------------------------------------------------------------------------------------
rem 三种方式都能取到30
test_readcfg --cfgfile yzmond.conf --group [系统设置] --item 未应答超时 --type int
pause
rem 第一种取到1000，第二种取不到，第三种取到默认值10
test_readcfg --cfgfile yzmond.conf --group [系统设置] --item 队列最大长度 --type int
pause
rem 找到但类型指定错误，按int读，三种均取到60
test_readcfg --cfgfile yzmond.conf --group [系统设置] --item 内存使用比例 --type int
pause
rem 前两种取不到，第三种取到默认值10
test_readcfg --cfgfile php.ini --group [Tidy] --item tidy.clean_output --type int
pause

rem --------------------------------------------------------------------------------------------------------------------------
rem	取指定配置文件的指定组中的指定项，返回该项目的值（必须是 "项目名 =/空格/tab 值" 形式的项，且数据类型要匹配，如果不匹配，不是程序错）
rem		4、double型
rem  注：自主决定是否添加 --gcs 和 --ics
rem --------------------------------------------------------------------------------------------------------------------------
rem 三种方式都能取到60.5
test_readcfg --cfgfile yzmond.conf --group [系统设置] --item 内存使用比例 --type double
pause
rem 三种方式都能取到30（以double方式读int是兼容的）
test_readcfg --cfgfile yzmond.conf --group [系统设置] --item 未应答超时 --type double
pause
rem 第一种取到87.35，第二种取不到，第三种取到默认值1.2
test_readcfg --cfgfile yzmond.conf --group [系统设置] --item 内存空载比例 --type double
pause
rem 前两种取不到，第三种取到默认值1.2
test_readcfg --cfgfile php.ini --group [Tidy] --item tidy.clean_output --type double
pause
rem 前两种取不到，第三种取到默认值1.2
test_readcfg --cfgfile php.ini --group [soap] --item soap.wsdl_cache_dir --type double
pause

rem --------------------------------------------------------------------------------------------------------------------------
rem	取指定配置文件的指定组中的指定项，返回该项目的值（必须是 "项目名 =/空格/tab 值" 形式的项，且数据类型要匹配，如果不匹配，不是程序错）
rem		5、cstring型
rem  注：自主决定是否添加 --gcs 和 --ics
rem --------------------------------------------------------------------------------------------------------------------------
rem 返回原始内容（含空格的所有），用于和--type cstring比较
test_readcfg --cfgfile httpd.conf --group "" --item DirectoryIndex --brkchar space
pause
rem 返回原始内容（含空格的所有），用于和--type cstring比较
test_readcfg --cfgfile httpd.conf --group "" --item DirectoryIndex --brkchar space --type raw
pause
rem 三种方式都能取到index.html（第一个空格前的内容）
test_readcfg --cfgfile httpd.conf --group "" --item DirectoryIndex --brkchar space --type cstring
pause

rem 多个LogFormat，只找第一个，返回原始内容（含空格的所有），用于和--type cstring比较
test_readcfg --cfgfile httpd.conf --group "" --item LogFormat --brkchar space
pause
rem 多个LogFormat，只找第一个，三种方式都能取到"%h（未做转义符处理及引号匹配，仅取第一个空格前的内容）
test_readcfg --cfgfile httpd.conf --group "" --item LogFormat --brkchar space --type cstring
pause

rem 多个AddType，只找第一个，返回原始内容（含空格的所有），用于和--type cstring比较
test_readcfg --cfgfile httpd.conf --group "" --item AddType --brkchar space --type raw
pause
rem 多个AddType，只找第一个，第一种方式已越界（出什么都不奇怪）；第一种方式注释后，后两种方式都能取到长度为15的串
test_readcfg --cfgfile httpd.conf --group "" --item AddType --brkchar space --type cstring
pause

rem 前两种取不到，第三种取到默认值Hello
test_readcfg --cfgfile php.ini --group [soap] --item soap.wsdl_cache_dir --type cstring
pause

rem --------------------------------------------------------------------------------------------------------------------------
rem	取指定配置文件的指定组中的指定项，返回该项目的值（必须是 "项目名 =/空格/tab 值" 形式的项，且数据类型要匹配，如果不匹配，不是程序错）
rem		6、string型
rem  注：自主决定是否添加 --gcs 和 --ics
rem --------------------------------------------------------------------------------------------------------------------------
rem 返回原始内容（含空格的所有），用于和--type string比较
test_readcfg --cfgfile httpd.conf --group "" --item DirectoryIndex --brkchar space
pause
rem 两种方式都能取到index.html（第一个空格前的内容）
test_readcfg --cfgfile httpd.conf --group "" --item DirectoryIndex --brkchar space --type string
pause

rem 多个LogFormat，只找第一个，返回原始内容（含空格的所有），用于和--type string比较
test_readcfg --cfgfile httpd.conf --group "" --item LogFormat --brkchar space
pause
rem 多个LogFormat，只找第一个，三种方式都能取到"%h（未做转义符处理及引号匹配，仅取第一个空格前的内容）
test_readcfg --cfgfile httpd.conf --group "" --item LogFormat --brkchar space --type string
pause

rem 多个AddType，只找第一个，返回原始内容（含空格的所有），用于和--type string比较
test_readcfg --cfgfile httpd.conf --group "" --item AddType --brkchar space --type raw
pause
rem 多个AddType，只找第一个，两种方式都能取到完整内容application/x-compress
test_readcfg --cfgfile httpd.conf --group "" --item AddType --brkchar space --type string
pause

rem 第一种取不到，第二种取到默认值Tongji
test_readcfg --cfgfile php.ini --group [soap] --item soap.wsdl_cache_dir --type string
pause

rem --------------------------------------------------------------------------------------------------------------------------
rem	取指定配置文件的指定组中的指定项，返回该项目的值（必须是 "项目名 =/空格/tab 值" 形式的项，且数据类型要匹配，如果不匹配，不是程序错）
rem		7、IP地址
rem  注：自主决定是否添加 --gcs 和 --ics
rem --------------------------------------------------------------------------------------------------------------------------
rem 两种方式都能取到192.9.200.214，打印的是hex（c009c8d6）
test_readcfg --cfgfile yzmond.conf --group [数据采集设置] --item 调试IP地址 --type ip
pause
rem 第一种取不到，第二种取到默认值192.168.1.230（c0a801e6）
test_readcfg --cfgfile yzmond.conf --group [数据库] --item 服务器IP地址 --type ip
pause
rem 第一种取不到，第二种取到默认值192.168.1.230（c0a801e6）
test_readcfg --cfgfile php.ini --group [soap] --item soap.wsdl_cache_dir --type ip

*/
