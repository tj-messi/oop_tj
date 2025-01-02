/* 学号 班级 姓名 */ 
#include <iostream>
/* 添加自己需要的头文件，注意限制 */
#include "../include/class_cft.h"
using namespace std;

/* 给出各种自定义函数的实现（已给出的内容不全） */

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
config_file_tools::config_file_tools(const char* const _cfgname, const enum BREAK_CTYPE _ctype)
{
	/* 按需完成 */
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
config_file_tools::config_file_tools(const string& _cfgname, const enum BREAK_CTYPE _ctype)
{
	/* 按需完成 */
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
config_file_tools::~config_file_tools()
{
	/* 按需完成 */
}


/***************************************************************************
  函数名称：
  功    能：判断读配置文件是否成功
  输入参数：
  返 回 值：true - 成功，已读入所有的组/项
		   false - 失败，文件某行超长/文件全部是注释语句
  说    明：
***************************************************************************/
bool config_file_tools::is_read_succeeded() const
{
	/* 按需完成，根据需要改变return的值 */
	return true;
}

/***************************************************************************
  函数名称：
  功    能：返回配置文件中的所有组
  输入参数：vector <string>& ret : vector 中每项为一个组名
  返 回 值：读到的组的数量（简单配置文件的组数量为1，组名为"）
  说    明：
***************************************************************************/
int config_file_tools::get_all_group(vector <string>& ret)
{
	/* 按需完成，根据需要改变return的值 */
	return 0;
}

/***************************************************************************
  函数名称：
  功    能：查找指定组的所有项并返回项的原始内容
  输入参数：const char* const group_name：组名
		   vector <string>& ret：vector 中每项为一个项的原始内容
		   const bool is_case_sensitive = false : 组名是否大小写敏感，true-大小写敏感 / 默认false-大小写不敏感
  返 回 值：项的数量，0表示空
  说    明：
***************************************************************************/
int config_file_tools::get_all_item(const char* const group_name, vector <string>& ret, const bool is_case_sensitive)
{
	/* 按需完成，根据需要改变return的值 */
	return 0;
}

/***************************************************************************
  函数名称：
  功    能：组名/项目为string方式，其余同上
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
int config_file_tools::get_all_item(const string& group_name, vector <string>& ret, const bool is_case_sensitive)
{
	/* 按需完成，根据需要改变return的值 */
	return 0;
}

/***************************************************************************
  函数名称：
  功    能：取某项的原始内容（=后的所有字符，string方式）
  输入参数：const char* const group_name
		   const char* const item_name
		   string &ret
		   const bool group_is_case_sensitive = false : 组名是否大小写敏感，true-大小写敏感 / 默认false-大小写不敏感
		   const bool item_is_case_sensitive = false  : 项名是否大小写敏感，true-大小写敏感 / 默认false-大小写不敏感
  返 回 值：
  说    明：
***************************************************************************/
int config_file_tools::item_get_raw(const char* const group_name, const char* const item_name, string& ret, const bool group_is_case_sensitive, const bool item_is_case_sensitive)
{
	/* 按需完成，根据需要改变return的值 */
	return 0;
}

/***************************************************************************
  函数名称：
  功    能：组名/项目为string方式，其余同上
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
int config_file_tools::item_get_raw(const string& group_name, const string& item_name, string& ret, const bool group_is_case_sensitive, const bool item_is_case_sensitive)
{
	/* 本函数已实现 */
	return this->item_get_raw(group_name.c_str(), item_name.c_str(), ret, group_is_case_sensitive, item_is_case_sensitive);
}

/***************************************************************************
  函数名称：
  功    能：取某项的内容，返回类型为char型
  输入参数：const char* const group_name               ：组名
		   const char* const item_name                ：项名
		   const bool group_is_case_sensitive = false : 组名是否大小写敏感，true-大小写敏感 / 默认false-大小写不敏感
		   const bool item_is_case_sensitive = false  : 项名是否大小写敏感，true-大小写敏感 / 默认false-大小写不敏感
  返 回 值：1 - 该项的项名存在
		   0 - 该项的项名不存在
  说    明：
***************************************************************************/
int config_file_tools::item_get_null(const char* const group_name, const char* const item_name, const bool group_is_case_sensitive, const bool item_is_case_sensitive)
{
	/* 按需完成，根据需要改变return的值 */
	return 0;
}

/***************************************************************************
  函数名称：
  功    能：组名/项目为string方式，其余同上
  输入参数：
  返 回 值：
  说    明：因为工具函数一般在程序初始化阶段被调用，不会在程序执行中被高频次调用，
		   因此这里直接套壳，会略微影响效率，但不影响整体性能（对高频次调用，此方法不适合）
***************************************************************************/
int config_file_tools::item_get_null(const string& group_name, const string& item_name, const bool group_is_case_sensitive, const bool item_is_case_sensitive)
{
	/* 本函数已实现 */
	return this->item_get_null(group_name.c_str(), item_name.c_str(), group_is_case_sensitive, item_is_case_sensitive);
}

/***************************************************************************
  函数名称：
  功    能：取某项的内容，返回类型为char型
  输入参数：const char* const group_name               ：组名
		   const char* const item_name                ：项名
		   char& value                                ：读到的char的值（返回1时可信，返回0则不可信）
		   const char* const choice_set = nullptr     ：合法的char的集合（例如："YyNn"表示合法输入为Y/N且不分大小写，该参数有默认值nullptr，表示全部字符，即不检查）
		   const char def_value = DEFAULT_CHAR_VALUE  ：读不到/读到非法的情况下的默认值，该参数有默认值DEFAULT_CHAR_VALUE，分两种情况
															当值是   DEFAULT_CHAR_VALUE 时，返回0（值不可信）
															当值不是 DEFAULT_CHAR_VALUE 时，令value=def_value并返回1
		   const bool group_is_case_sensitive = false : 组名是否大小写敏感，true-大小写敏感 / 默认false-大小写不敏感
		   const bool item_is_case_sensitive = false  : 项名是否大小写敏感，true-大小写敏感 / 默认false-大小写不敏感
  返 回 值：1 - 取到正确值
			   未取到值/未取到正确值，设置了缺省值（包括设为缺省值）
		   0 - 未取到（只有为未指定默认值的情况下才会返回0）
  说    明：
***************************************************************************/
int config_file_tools::item_get_char(const char* const group_name, const char* const item_name, char& value,
						const char* const choice_set, const char def_value, const bool group_is_case_sensitive, const bool item_is_case_sensitive)
{
	/* 按需完成，根据需要改变return的值 */
	return 0;
}

/***************************************************************************
  函数名称：
  功    能：组名/项目为string方式，其余同上
  输入参数：
  返 回 值：
  说    明：因为工具函数一般在程序初始化阶段被调用，不会在程序执行中被高频次调用，
		   因此这里直接套壳，会略微影响效率，但不影响整体性能（对高频次调用，此方法不适合）
***************************************************************************/
int config_file_tools::item_get_char(const string& group_name, const string& item_name, char& value,
						const char* const choice_set, const char def_value, const bool group_is_case_sensitive, const bool item_is_case_sensitive)
{
	/* 本函数已实现 */
	return this->item_get_char(group_name.c_str(), item_name.c_str(), value, choice_set, def_value, group_is_case_sensitive, item_is_case_sensitive);
}

/***************************************************************************
  函数名称：
  功    能：取某项的内容，返回类型为int型
  输入参数：const char* const group_name               ：组名
		   const char* const item_name                ：项名
		   int& value                                 ：读到的int的值（返回1时可信，返回0则不可信）
		   const int min_value = INT_MIN              : 期望数据范围的下限，默认为INT_MIN
		   const int max_value = INT_MAX              : 期望数据范围的上限，默认为INT_MAX
		   const int def_value = DEFAULT_INT_VALUE    ：读不到/读到非法的情况下的默认值，该参数有默认值 DEFAULT_INT_VALUE，分两种情况
															当值是   DEFAULT_INT_VALUE 时，返回0（值不可信）
															当值不是 DEFAULT_INT_VALUE 时，令value=def_value并返回1
		   const bool group_is_case_sensitive = false : 组名是否大小写敏感，true-大小写敏感 / 默认false-大小写不敏感
		   const bool item_is_case_sensitive = false  : 项名是否大小写敏感，true-大小写敏感 / 默认false-大小写不敏感
  返 回 值：
  说    明：
***************************************************************************/
int config_file_tools::item_get_int(const char* const group_name, const char* const item_name, int& value,
						const int min_value, const int max_value, const int def_value, const bool group_is_case_sensitive, const bool item_is_case_sensitive)
{
	/* 按需完成，根据需要改变return的值 */
	return 0;
}

/***************************************************************************
  函数名称：
  功    能：组名/项目为string方式，其余同上
  输入参数：
  返 回 值：
  说    明：因为工具函数一般在程序初始化阶段被调用，不会在程序执行中被高频次调用，
		   因此这里直接套壳，会略微影响效率，但不影响整体性能（对高频次调用，此方法不适合）
***************************************************************************/
int config_file_tools::item_get_int(const string& group_name, const string& item_name, int& value,
						const int min_value, const int max_value, const int def_value, const bool group_is_case_sensitive, const bool item_is_case_sensitive)
{
	/* 本函数已实现 */
	return this->item_get_int(group_name.c_str(), item_name.c_str(), value, min_value, max_value, def_value, group_is_case_sensitive, item_is_case_sensitive);
}

/***************************************************************************
  函数名称：
  功    能：取某项的内容，返回类型为double型
  输入参数：const char* const group_name                  ：组名
		   const char* const item_name                   ：项名
		   double& value                                 ：读到的int的值（返回1时可信，返回0则不可信）
		   const double min_value = __DBL_MIN__          : 期望数据范围的下限，默认为INT_MIN
		   const double max_value = __DBL_MAX__          : 期望数据范围的上限，默认为INT_MAX
		   const double def_value = DEFAULT_DOUBLE_VALUE ：读不到/读到非法的情况下的默认值，该参数有默认值DEFAULT_DOUBLE_VALUE，分两种情况
																当值是   DEFAULT_DOUBLE_VALUE 时，返回0（值不可信）
																当值不是 DEFAULT_DOUBLE_VALUE 时，令value=def_value并返回1
		   const bool group_is_case_sensitive = false     : 组名是否大小写敏感，true-大小写敏感 / 默认false-大小写不敏感
		   const bool item_is_case_sensitive = false      : 项名是否大小写敏感，true-大小写敏感 / 默认false-大小写不敏感
  返 回 值：
  说    明：
***************************************************************************/
int config_file_tools::item_get_double(const char* const group_name, const char* const item_name, double& value,
						const double min_value, const double max_value, const double def_value, const bool group_is_case_sensitive, const bool item_is_case_sensitive)
{
	/* 按需完成，根据需要改变return的值 */
	return 0;
}

/***************************************************************************
  函数名称：
  功    能：组名/项目为string方式，其余同上
  输入参数：
  返 回 值：
  说    明：因为工具函数一般在程序初始化阶段被调用，不会在程序执行中被高频次调用，
		   因此这里直接套壳，会略微影响效率，但不影响整体性能（对高频次调用，此方法不适合）
***************************************************************************/
int config_file_tools::item_get_double(const string& group_name, const string& item_name, double& value,
						const double min_value, const double max_value, const double def_value, const bool group_is_case_sensitive, const bool item_is_case_sensitive)
{
	/* 本函数已实现 */
	return this->item_get_double(group_name.c_str(), item_name.c_str(), value, min_value, max_value, def_value, group_is_case_sensitive, item_is_case_sensitive);
}

/***************************************************************************
  函数名称：
  功    能：取某项的内容，返回类型为char * / char []型
  输入参数：const char* const group_name                  ：组名
		   const char* const item_name                   ：项名
		   char *const value                             ：读到的C方式的字符串（返回1时可信，返回0则不可信）
		   const int str_maxlen                          ：指定要读的最大长度（含尾零）
																如果<1则返回空串(不是DEFAULT_CSTRING_VALUE，虽然现在两者相同，但要考虑default值可能会改)
																如果>MAX_STRLEN 则上限为MAX_STRLEN
		   const char* const def_str                     ：读不到情况下的默认值，该参数有默认值DEFAULT_CSTRING_VALUE，分两种情况
																当值是   DEFAULT_CSTRING_VALUE 时，返回0（值不可信）
																当值不是 DEFAULT_CSTRING_VALUE 时，令value=def_value并返回1（注意，不是直接=）
		   const bool group_is_case_sensitive = false : 组名是否大小写敏感，true-大小写敏感 / 默认false-大小写不敏感
		   const bool item_is_case_sensitive = false  : 项名是否大小写敏感，true-大小写敏感 / 默认false-大小写不敏感
  返 回 值：
  说    明：1、为简化，未对\"等做转义处理，均按普通字符
		   2、含尾零的最大长度为str_maxlen，调用时要保证有足够空间
		   3、如果 str_maxlen 超过了系统预设的上限 MAX_STRLEN，则按 MAX_STRLEN 取
***************************************************************************/
int config_file_tools::item_get_cstring(const char* const group_name, const char* const item_name, char* const value,
						const int str_maxlen, const char* const def_value, const bool group_is_case_sensitive, const bool item_is_case_sensitive)
{
	/* 按需完成，根据需要改变return的值 */
	return 0;
}

/***************************************************************************
  函数名称：
  功    能：组名/项目为string方式，其余同上
  输入参数：
  返 回 值：
  说    明：因为工具函数一般在程序初始化阶段被调用，不会在程序执行中被高频次调用，
		   因此这里直接套壳，会略微影响效率，但不影响整体性能（对高频次调用，此方法不适合）
***************************************************************************/
int config_file_tools::item_get_cstring(const string& group_name, const string& item_name, char* const value,
						const int str_maxlen, const char* const def_value, const bool group_is_case_sensitive, const bool item_is_case_sensitive)

{
	/* 本函数已实现 */
	return item_get_cstring(group_name.c_str(), item_name.c_str(), value, str_maxlen, def_value, group_is_case_sensitive, item_is_case_sensitive);
}

/***************************************************************************
  函数名称：
  功    能：取某项的内容，返回类型为 string 型
  输入参数：const char* const group_name               ：组名
		   const char* const item_name                ：项名
		   string &value                              ：读到的string方式的字符串（返回1时可信，返回0则不可信）
		   const string &def_value                    ：读不到情况下的默认值，该参数有默认值DEFAULT_STRING_VALUE，分两种情况
															当值是   DEFAULT_STRING_VALUE 时，返回0（值不可信）
															当值不是 DEFAULT_STRING_VALUE 时，令value=def_value并返回1
		   const bool group_is_case_sensitive = false : 组名是否大小写敏感，true-大小写敏感 / 默认false-大小写不敏感
		   const bool item_is_case_sensitive = false  : 项名是否大小写敏感，true-大小写敏感 / 默认false-大小写不敏感
  返 回 值：
  说    明：为简化，未对\"等做转义处理，均按普通字符
***************************************************************************/
int config_file_tools::item_get_string(const char* const group_name, const char* const item_name, string& value,
						const string& def_value, const bool group_is_case_sensitive, const bool item_is_case_sensitive)
{
	/* 按需完成，根据需要改变return的值 */
	return 0;
}

/***************************************************************************
  函数名称：
  功    能：组名/项目为string方式，其余同上
  输入参数：
  返 回 值：
  说    明：因为工具函数一般在程序初始化阶段被调用，不会在程序执行中被高频次调用，
		   因此这里直接套壳，会略微影响效率，但不影响整体性能（对高频次调用，此方法不适合）
***************************************************************************/
int config_file_tools::item_get_string(const string& group_name, const string& item_name, string& value,
						const string& def_value, const bool group_is_case_sensitive, const bool item_is_case_sensitive)
{
	/* 本函数已实现 */
	return this->item_get_string(group_name.c_str(), item_name.c_str(), value, def_value, group_is_case_sensitive, item_is_case_sensitive);
}

/***************************************************************************
  函数名称：
  功    能：取某项的内容，返回类型为 IPv4 地址的32bit整型（主机序）
  输入参数：const char* const group_name               ：组名
		   const char* const item_name                ：项名
		   unsigned int &value                        ：读到的IP地址，32位整型方式（返回1时可信，返回0则不可信）
		   const unsigned int &def_value              ：读不到情况下的默认值，该参数有默认值DEFAULT_IPADDR_VALUE，分两种情况
															当值是   DEFAULT_IPADDR_VALUE 时，返回0（值不可信）
															当值不是 DEFAULT_IPADDR_VALUE 时，令value=def_value并返回1
		   const bool group_is_case_sensitive = false : 组名是否大小写敏感，true-大小写敏感 / 默认false-大小写不敏感
		   const bool item_is_case_sensitive = false  : 项名是否大小写敏感，true-大小写敏感 / 默认false-大小写不敏感
  返 回 值：
  说    明：
***************************************************************************/
int config_file_tools::item_get_ipaddr(const char* const group_name, const char* const item_name, unsigned int& value,
						const unsigned int& def_value, const bool group_is_case_sensitive, const bool item_is_case_sensitive)
{
	/* 按需完成，根据需要改变return的值 */
	return 0;
}

/***************************************************************************
  函数名称：
  功    能：组名/项目为string方式，其余同上
  输入参数：
  返 回 值：
  说    明：因为工具函数一般在程序初始化阶段被调用，不会在程序执行中被高频次调用，
		   因此这里直接套壳，会略微影响效率，但不影响整体性能（对高频次调用，此方法不适合）
***************************************************************************/
int config_file_tools::item_get_ipaddr(const string& group_name, const string& item_name, unsigned int& value,
						const unsigned int& def_value, const bool group_is_case_sensitive, const bool item_is_case_sensitive)
{
	/* 本函数已实现 */
	return this->item_get_ipaddr(group_name.c_str(), item_name.c_str(), value, def_value, group_is_case_sensitive, item_is_case_sensitive);
}
