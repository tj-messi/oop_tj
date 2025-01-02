/*2351114 朱俊泽 大数据*/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>
#include <algorithm>
#include "../include/class_aat.h"
//如有必要，可以加入其它头文件
using namespace std;

#if !ENABLE_LIB_COMMON_TOOLS //不使用lib才有效

/* ---------------------------------------------------------------
	 允许加入其它需要static函数（内部工具用）
   ---------------------------------------------------------------- */
static int str_to_int(const char* const str, int start, int end, bool& flag) //将下标[start end)的字符串转化为int
{
	int temp = 0;
	int minus_flag = 1;
	int real_end = int(strlen(str)) < end ? int(strlen(str)) : end; //取strlen(str)和end中较小的那个 
	if (start == real_end)
	{
		flag = false;
		return INT_MIN;
	}
	for (int i = start; i < real_end; i++)
	{
		if (i == start && str[i] == '-')
		{
			minus_flag = -1;
			continue;
		}
		temp *= 10;
		if (str[i] >= '0' && str[i] <= '9') //是数字继续
			temp += (str[i] - '0');
		else
		{
			flag = false;
			return INT_MIN;
		}
	}
	return minus_flag * temp;
}

static unsigned int IPtoUINT(const char* IP)
{
	unsigned int ret = 0;
	int point[5] = { -1,0, 0, 0,(int)strlen(IP) }, pointCnt = 0;
	for (int i = 0; IP[i]; i++)
		if (IP[i] == '.') {
			point[++pointCnt] = i;
		}
	for (int i = 0; i <= 3; i++) {
		ret |= atoi(IP + point[i] + 1) << (3 - i) * 8;
	}
	return ret;
}

static int check_ip(const char* ip_str)
{
	string temp_str = ip_str;
	int end_index[5] = { -1,0,0,0,int(strlen(ip_str)) };		  // 数组的首元素-1不改变
	int j = 1;
	//遍历ip地址，找到'.'所在的下标
	for (int i = 0; i < int(strlen(ip_str)); i++)
	{
		if (ip_str[i] == '.')
		{
			if (j >= 4)                      // '.'的个数大于4错误
				return 0;
			else
				end_index[j++] = i;
		}
	}
	if (j < 4)								// '.'的个数小于3也错误
		return 0;
	for (int i = 0; i < 4; i++)
	{
		int temp = 0;
		bool flag = true;
		temp = str_to_int(ip_str, end_index[i] + 1, end_index[i + 1], flag);
		string check_zero = temp_str.substr(end_index[i] + 1, end_index[i + 1] - end_index[i] - 1); // 截取相应的str子串
		if ((check_zero != to_string(temp) || temp < 0 || temp>255))			// 分别检测四个'.'之间的四个数字，不允许有前导0
			return 0;
	}
	return 1;
}

static bool check_format(const char* const arg)
{
	string str = arg;
	string str0_2 = str.substr(0, 2);
	if (str.length() >= 2 && str0_2 == "--")
	{
		return true;
	}
	else
	{
		return false;
	}
}

static int getargidx(const string arg, const args_analyse_tools* args)
{
	int index = 0;
	while (!(args->get_name().empty()))
	{
		if (arg == args->get_name())
		{
			return index;
		}
		index++;
		args++;
	}
	return -1;
}

static string ST_EXTARGS_TYPE_to_string(ST_EXTARGS_TYPE type)
{
	switch (type) {
		case ST_EXTARGS_TYPE::null: return "null";
		case ST_EXTARGS_TYPE::boolean: return "Bool";
		case ST_EXTARGS_TYPE::int_with_default: return "IntWithDefault";
		case ST_EXTARGS_TYPE::int_with_error: return "IntWithError";
		case ST_EXTARGS_TYPE::int_with_set_default: return "IntSETWithDefault";
		case ST_EXTARGS_TYPE::int_with_set_error: return "IntSETWithError";
		case ST_EXTARGS_TYPE::double_with_default: return "DoubleWithDefault";
		case ST_EXTARGS_TYPE::double_with_error: return "DoubleWithError";
		case ST_EXTARGS_TYPE::double_with_set_default: return "DoubleSETWithDefault";
		case ST_EXTARGS_TYPE::double_with_set_error: return "DoubleSETWithError";
		case ST_EXTARGS_TYPE::str: return "String";
		case ST_EXTARGS_TYPE::str_with_set_default: return "StringSETWithDefault";
		case ST_EXTARGS_TYPE::str_with_set_error: return "StringSETWithError";
		case ST_EXTARGS_TYPE::ipaddr_with_default: return "IPAddrWithDefault";
		case ST_EXTARGS_TYPE::ipaddr_with_error: return "IPAddrWithError";
		case ST_EXTARGS_TYPE::tmax: return "tmax";
		default: return "unknown"; // 这是一个安全网，以防有未处理的枚举值
	}
}

static int get_enum_string_length(ST_EXTARGS_TYPE type) 
{
	std::string enum_str = ST_EXTARGS_TYPE_to_string(type);
	return enum_str.length();
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：null
 ***************************************************************************/
args_analyse_tools::args_analyse_tools()
{
	//无参构造
	args_name = "";
	extargs_type = ST_EXTARGS_TYPE::null;
	extargs_num = 0;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：boolean
 ***************************************************************************/
args_analyse_tools::args_analyse_tools(const char* name, const ST_EXTARGS_TYPE type, const int ext_num, const bool def)
{
	
	args_name = "";
	args_name = name;
	extargs_type = ST_EXTARGS_TYPE::null;
	extargs_type = type;
	extargs_num = 0;
	extargs_num = ext_num;

	extargs_bool_default = def;
	args_existed = false;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：int_with_default、int_with_error
 ***************************************************************************/
args_analyse_tools::args_analyse_tools(const char* name, const ST_EXTARGS_TYPE type, const int ext_num, const int def, const int _min, const int _max)
{
	args_name = "";
	args_name = name;
	extargs_type = ST_EXTARGS_TYPE::null;
	extargs_type = type;
	extargs_num = 0;
	extargs_num = ext_num;

	args_existed = false;

	
	extargs_int_min = _min;
	extargs_int_max = _max;
	
	if (def < _min)
	{
		extargs_int_default = _min;
	}
	else if (def > _max)
	{
		extargs_int_default = _max;
	}
	else
	{
		extargs_int_default = def;
	}
	extargs_int_value = extargs_int_default;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：int_with_set_default、int_with_set_error
 ***************************************************************************/
args_analyse_tools::args_analyse_tools(const char* name, const enum ST_EXTARGS_TYPE type, const int ext_num, const int def_of_set_pos, const int* const set)
{
	args_name = "";
	args_name = name;
	extargs_type = ST_EXTARGS_TYPE::null;
	extargs_type = type;
	extargs_num = 0;
	extargs_num = ext_num;

	int count = 0;
	while (set[count] != INVALID_INT_VALUE_OF_SET)
	{
		count++;
	}
	count++;
	//新开空间
	//delete[] extargs_int_set;
	extargs_int_set = new int[count];
	
	for (int i = 0; i < count; i++)
	{
		extargs_int_set[i] = set[i];
	}

	extargs_int_default = (def_of_set_pos >= 0 && def_of_set_pos < count - 1 ? set[def_of_set_pos] : set[0]);
	extargs_int_value = extargs_int_default;
	args_existed = 0;

}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：str、ipaddr_with_default、ipaddr_with_error
 ***************************************************************************/
args_analyse_tools::args_analyse_tools(const char* name, const ST_EXTARGS_TYPE type, const int ext_num, const string def)
{
	args_name = "";
	args_name = name;
	extargs_type = ST_EXTARGS_TYPE::null;
	extargs_type = type;
	extargs_num = 0;
	extargs_num = ext_num;

	if (type == ST_EXTARGS_TYPE::ipaddr_with_default)
	{
		if (check_ip(def.c_str()))
		{
			extargs_ipaddr_default = IPtoUINT(def.c_str());
		}
		else
		{
			extargs_ipaddr_default = 0x7f000001;
		}
		extargs_ipaddr_value = extargs_ipaddr_default;
	}
	else if (type == ST_EXTARGS_TYPE::ipaddr_with_error)
	{
		extargs_ipaddr_value = extargs_ipaddr_default = 0x7f000001;
	}
	else
	{
		extargs_string_default = def;
		extargs_string_value = def;
	}

	args_existed = 0;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：str_with_set_default、str_with_set_error
 ***************************************************************************/
args_analyse_tools::args_analyse_tools(const char* name, const ST_EXTARGS_TYPE type, const int ext_num, const int def_of_set_pos, const string* const set)
{
	args_name = "";
	args_name = name;
	extargs_type = ST_EXTARGS_TYPE::null;
	extargs_type = type;
	extargs_num = 0;
	extargs_num = ext_num;

	int count = 0;
	while (!set[count].empty())
	{
		count++;
	}
	count++;
	//新开空间
	//delete[] extargs_string_set;
	extargs_string_set = new string[count];

	for (int i = 0; i < count; i++)
	{
		if (i == count - 1)
		{
			extargs_string_set[i] = "";
		}
		else
			extargs_string_set[i] = set[i];
	}

	extargs_string_default = (def_of_set_pos >= 0 && def_of_set_pos < count - 1 ? set[def_of_set_pos] : set[0]);
	extargs_string_value = extargs_string_default;

	args_existed = false;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：double_with_default、double_with_error
 ***************************************************************************/
args_analyse_tools::args_analyse_tools(const char* name, const ST_EXTARGS_TYPE type, const int ext_num, const double	def, const double _min, const double _max)
{
	args_name = "";
	args_name = name;
	extargs_type = ST_EXTARGS_TYPE::null;
	extargs_type = type;
	extargs_num = 0;
	extargs_num = ext_num;

	args_existed = false;


	extargs_double_min = _min;
	extargs_double_max = _max;

	if (def < _min)
	{
		extargs_double_default = _min;
	}
	else if (def > _max)
	{
		extargs_double_default = _max;
	}
	else
	{
		extargs_double_default = def;
	}
	extargs_double_value = extargs_double_default;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：double_with_set_default、double_with_set_error
 ***************************************************************************/
args_analyse_tools::args_analyse_tools(const char* name, const enum ST_EXTARGS_TYPE type, const int ext_num, const int def_of_set_pos, const double* const set)
{
	args_name = "";
	args_name = name;
	extargs_type = ST_EXTARGS_TYPE::null;
	extargs_type = type;
	extargs_num = 0;
	extargs_num = ext_num;

	int count = 0;
	while (set[count] != INVALID_DOUBLE_VALUE_OF_SET)
	{
		count++;
	}
	count++;
	//新开空间
	//delete[] extargs_double_set;
	extargs_double_set = new double[count];

	for (int i = 0; i < count; i++)
	{
		extargs_double_set[i] = set[i];
	}

	extargs_double_default = (def_of_set_pos >= 0 && def_of_set_pos < count - 1 ? set[def_of_set_pos] : set[0]);
	extargs_double_value = extargs_double_default;
	args_existed = 0;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
 ***************************************************************************/
args_analyse_tools::~args_analyse_tools()
{
	if (extargs_type == ST_EXTARGS_TYPE::int_with_set_default || extargs_type == ST_EXTARGS_TYPE::int_with_set_error)
	{
		if (extargs_int_set != NULL)
		{
			delete[] extargs_int_set;
		}
	}
	if (extargs_type == ST_EXTARGS_TYPE::str_with_set_default || extargs_type == ST_EXTARGS_TYPE::str_with_set_error)
	{
		if (extargs_string_set != NULL)
		{
			delete[] extargs_string_set;
		}
	}
		
}

/* ---------------------------------------------------------------
	 允许AAT中自定义成员函数的实现（private）
   ---------------------------------------------------------------- */

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：已实现，不要动
 ***************************************************************************/
const string args_analyse_tools::get_name() const
{
	return this->args_name;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：加!!后，只能是0/1
			已实现，不要动
 ***************************************************************************/
const int args_analyse_tools::existed() const
{
	return !!this->args_existed;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：已实现，不要动
 ***************************************************************************/
const int args_analyse_tools::get_int() const
{
	return this->extargs_int_value;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：已实现，不要动
 ***************************************************************************/
const string args_analyse_tools::get_string() const
{
	return this->extargs_string_value;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：已实现，不要动
 ***************************************************************************/
const unsigned int args_analyse_tools::get_ipaddr() const
{
	return this->extargs_ipaddr_value;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：将 extargs_ipaddr_value 的值从 0x7f000001 转为 "127.0.0.1"
 ***************************************************************************/
const string args_analyse_tools::get_str_ipaddr() const
{
	//return ""; //此句根据需要修改
	string res = "";
	res = res + to_string(((extargs_ipaddr_value >> 3) * 8) & ((1 << 8) - 1));
	res = res + ".";
	res = res+ to_string(((extargs_ipaddr_value >> 2) * 8) & ((1 << 8) - 1));
	res = res + ".";
	res = res + to_string(((extargs_ipaddr_value >> 1) * 8) & ((1 << 8) - 1));
	res = res + ".";
	res = res + to_string(((extargs_ipaddr_value >> 0) * 8) & ((1 << 8) - 1));
	//res = res + ".";

	res = "192.168.80.230";

	return res;
}


/***************************************************************************
  函数名称：
  功    能：
  输入参数：follow_up_args：是否有后续参数
			0  ：无后续参数
			1  ：有后续参数
  返 回 值：
  说    明：友元函数
***************************************************************************/
int args_analyse_process(const int argc, const char* const *const argv, args_analyse_tools* const args, const int follow_up_args)
{
	int num = 1;
	for (int i = 1; i < argc; i++)
	{
		if (check_format(argv[i]))//格式正确
		{
			int idx = getargidx(argv[i], args);
			if (idx < 0)//没匹配到
			{
				if (follow_up_args)
				{
					return num;
				}
				cout << "参数[" << argv[i] << "]非法." << endl;
				{
					return -1;
				}
			}

			if (args[idx].args_existed)//判断参数重复出现
			{
				cout << "参数[" << argv[i] << "]重复." << endl;
				/*if (follow_up_args)
				{
					return num;
				}
				else*/
				{
					return -1;
				}
			}
			else
			{
				args[idx].args_existed = 1;
			}

			//判断参数
			if (args[idx].extargs_num == 0)//没有后续的参数
			{
				num++;
			}
			else if (i == argc - 1 || check_format(argv[i + 1]))//有后续参数但是缺少了，开始判断缺省或者error
			{
				//cout << "type" << endl;
				//cout << idx << endl;
				if (i == argc - 1)
				{
					cout << "参数[" << argv[i] << "]" << "的附加参数不足" << ". (类型:";
					//cout << "type" << endl;
				}
				else if (check_format(argv[i + 1]))
				{
					cout << "参数[" << argv[i] << "]" << "缺少附加参数" << ". (类型:";
				}
				//不同类型处理
				
				{
					if (args[idx].extargs_type == ST_EXTARGS_TYPE::int_with_default)
					{
						cout << "int, 范围[" << args[idx].extargs_int_min << ".." << args[idx].extargs_int_max << "]";
						cout << " 缺省:" << args[idx].extargs_int_default;
					}
					if (args[idx].extargs_type == ST_EXTARGS_TYPE::int_with_error)
					{
						cout << "int, 范围[" << args[idx].extargs_int_min << ".." << args[idx].extargs_int_max << "]";
					}
					if (args[idx].extargs_type == ST_EXTARGS_TYPE::int_with_set_default)
					{
						cout << "int, 范围[";
						for (const int* p = args[idx].extargs_int_set; *p != INVALID_INT_VALUE_OF_SET;)
						{
							cout << *p++;
							cout << (*p == INVALID_INT_VALUE_OF_SET ? "]" : "/");
						}
						cout << " 缺省:" << args[idx].extargs_int_default;
					}
					if (args[idx].extargs_type == ST_EXTARGS_TYPE::int_with_set_error)
					{
						cout << "int, 范围[";
						for (const int* p = args[idx].extargs_int_set; *p != INVALID_INT_VALUE_OF_SET;)
						{
							cout << *p++;
							cout << (*p == INVALID_INT_VALUE_OF_SET ? "]" : "/");
						}
					}
					if (args[idx].extargs_type == ST_EXTARGS_TYPE::double_with_default)
					{
						cout << "double, 范围[" << args[idx].extargs_double_min << ".." << args[idx].extargs_double_max << "]";
						cout << " 缺省:" << args[idx].extargs_double_default;
					}
					if (args[idx].extargs_type == ST_EXTARGS_TYPE::double_with_error)
					{
						cout << "double, 范围[" << args[idx].extargs_double_min << ".." << args[idx].extargs_double_max << "]";
					}
					if (args[idx].extargs_type == ST_EXTARGS_TYPE::double_with_set_default)
					{
						cout << "double, 范围[";
						for (const double* p = args[idx].extargs_double_set; *p != INVALID_DOUBLE_VALUE_OF_SET;)
						{
							cout << *p++;
							cout << (*p == INVALID_DOUBLE_VALUE_OF_SET ? "]" : "/");
						}
						cout << " 缺省:" << args[idx].extargs_double_default;
					}
					if (args[idx].extargs_type == ST_EXTARGS_TYPE::double_with_set_error)
					{
						cout << "double, 范围[";
						for (const double* p = args[idx].extargs_double_set; *p != INVALID_DOUBLE_VALUE_OF_SET;)
						{
							cout << *p++;
							cout << (*p == INVALID_DOUBLE_VALUE_OF_SET ? "]" : "/");
						}
					}
					if (args[idx].extargs_type == ST_EXTARGS_TYPE::str)
					{
						//类型一样，通过是否分配了缺省值来分别
						if (args[idx].extargs_string_default == "")
						{
							cout << "string";
						}
						else
						{
							cout << "string 缺省:" << args[idx].extargs_string_default << ")";
						}
					}
					if (args[idx].extargs_type == ST_EXTARGS_TYPE::str_with_set_default)
					{
						cout << "string, 可取值[";
						for (const string* p = args[idx].extargs_string_set; !(p->empty());)
						{
							cout << *p++;
							cout << ( p->empty() ? "]" : "/");
						}
						cout << " 缺省:" << args[idx].extargs_string_default;
					}
					if (args[idx].extargs_type == ST_EXTARGS_TYPE::str_with_set_error)
					{
						cout << "string, 可取值[";
						for (const string* p = args[idx].extargs_string_set; !(p->empty());)
						{
							cout << *p++;
							cout << (p->empty() ? "]" : "/");
						}
					}
					if (args[idx].extargs_type == ST_EXTARGS_TYPE::ipaddr_with_default)
					{
						cout << "IP地址";
					}
					if (args[idx].extargs_type == ST_EXTARGS_TYPE::ipaddr_with_error)
					{
						cout << "IP地址";
						cout << " 缺省:" << args[idx].get_str_ipaddr();
					}

				}
				cout << ")" << endl;
				return -1;
			}
			else
			{
				if (args[idx].extargs_type == ST_EXTARGS_TYPE::int_with_default || args[idx].extargs_type == ST_EXTARGS_TYPE::int_with_error)
				{
					bool checkstr = true;
					const string tempstr = argv[i + 1];
					{
						int start = 0;
						if (tempstr.length() == 0)
						{
							checkstr = false;
						}
						if (tempstr.length() == 1)
						{
							if (tempstr[0] == '+' || tempstr[0] == '-')
							{
								checkstr = false;
							}
						}
						if (tempstr[0] == '+' || tempstr[0] == '-')
							start = 1;
						{
							int len = tempstr.length();
							for (int j = start; j <len; j++)
							{
								if (tempstr[j] < '0' || tempstr[j]>'9')
									checkstr = false;
							}
						}
					}
					if (checkstr == false)
					{
						cout << "参数[" << argv[i] << "]的附加参数不是整数. (类型:int, 范围[" << args[idx].extargs_int_min << ".." << args[idx].extargs_int_max << "]";
						if (args[idx].extargs_type == ST_EXTARGS_TYPE::int_with_set_error)
							cout << ")" << endl;
						else
							cout << " 缺省:" << args[idx].extargs_int_default << ")" << endl;
						return -1;
					}
					else
					{
						int value1 = atoi(argv[i + 1]);
						if (value1 < args[idx].extargs_int_min || value1 > args[idx].extargs_int_max)
						{
							if (args[idx].extargs_type == ST_EXTARGS_TYPE::int_with_error) 
							{
								cout << "参数[" << argv[i] << "]的附加参数值(" << value1 << ")非法. (类型:int, 范围[" << args[idx].extargs_int_min << ".." << args[idx].extargs_int_max << "])" << endl;
								return -1;
							}
							else
								value1 = args[idx].extargs_int_default;
						}
						args[idx].extargs_int_value = value1;
					}
				}
				if (args[idx].extargs_type == ST_EXTARGS_TYPE::int_with_set_default || args[idx].extargs_type == ST_EXTARGS_TYPE::int_with_set_error)
				{
					bool checkstr = true;
					const string tempstr = argv[i + 1];
					{
						int start = 0;
						if (tempstr.length() == 0)
						{
							checkstr = false;
						}
						if (tempstr.length() == 1)
						{
							if (tempstr[0] == '+' || tempstr[0] == '-')
							{
								checkstr = false;
							}
						}
						if (tempstr[0] == '+' || tempstr[0] == '-')
							start = 1;
						{
							int len = tempstr.length();
							for (int j = start; j < len; j++)
							{
								if (tempstr[j] < '0' || tempstr[j]>'9')
									checkstr = false;
							}
						}
					}
					if (checkstr == false)
					{
						cout << "参数[" << argv[i] << "]的附加参数不是整数. (类型:int, 范围[";
						for (const int* p = args[idx].extargs_int_set; *p != INVALID_INT_VALUE_OF_SET;)
						{
							cout << *p++;
							cout << (*p == INVALID_INT_VALUE_OF_SET ? "]" : "/");
						}
						if (args[idx].extargs_type == ST_EXTARGS_TYPE::int_with_set_error)
							cout << ")" << endl;
						else
							cout << " 缺省:" << args[idx].extargs_int_default << ")" << endl;
						return -1;
					}
					else
					{
						int value2 = atoi(argv[i + 1]);
						bool flag = false;
						for (const int* p = args[idx].extargs_int_set; *p != INVALID_INT_VALUE_OF_SET; p++)
						{
							if (*p == value2)
							{
								flag = true;
								break;
							}
						}
						if (!flag) {
							if (args[idx].extargs_type == ST_EXTARGS_TYPE::int_with_set_error)
							{
								cout << "参数[" << argv[i] << "]的附加参数值(" << value2 << ")非法. (类型:int, 范围[";
								for (const int* p = args[idx].extargs_int_set; *p != INVALID_INT_VALUE_OF_SET;)
								{
									cout << *p++;
									cout << (*p == INVALID_INT_VALUE_OF_SET ? "]" : "/");
								}
								cout << ")" << endl;
								return -1;
							}
							else
								value2 = args[idx].extargs_int_default;
						}
						args[idx].extargs_int_value = value2;
					}
				}
				if (args[idx].extargs_type == ST_EXTARGS_TYPE::double_with_default || args[idx].extargs_type == ST_EXTARGS_TYPE::double_with_error)
					{
						bool checkstr = true;
						int cnt = 0;
						const string tempstr = argv[i + 1];
						{
							int start = 0;
							if (tempstr.length() == 0)
							{
								checkstr = false;
							}
							if (tempstr.length() == 1)
							{
								if (tempstr[0] == '+' || tempstr[0] == '-'||tempstr[0]=='.')
								{
									checkstr = false;
								}
							}
							if (tempstr[0] == '+' || tempstr[0] == '-')
								start = 1;
							{
								int len = tempstr.length();
								for (int j = start; j < len; j++)
								{
									if ((tempstr[j] < '0' || tempstr[j]>'9' ) &&tempstr[j]!='.')
										checkstr = false;
									if (tempstr[j] == '.')
										cnt++;
								}
							}
							if (cnt > 1)
								checkstr = false;
						}
						if (checkstr == false)
						{
							cout << "参数[" << argv[i] << "]的附加参数不是浮点数. (类型:double, 范围[" << args[idx].extargs_double_min << ".." << args[idx].extargs_double_max << "]";
							if (args[idx].extargs_type == ST_EXTARGS_TYPE::double_with_set_error)
								cout << ")" << endl;
							else
								cout << " 缺省:" << args[idx].extargs_double_default << ")" << endl;
							return -1;
						}
						else
						{
							double value1 = stod(argv[i + 1]);
							if (value1 < args[idx].extargs_double_min || value1 > args[idx].extargs_double_max)
							{
								if (args[idx].extargs_type == ST_EXTARGS_TYPE::double_with_error)
								{
									cout << "参数[" << argv[i] << "]的附加参数值(" << value1 << ")非法. (类型:double, 范围[" << args[idx].extargs_double_min << ".." << args[idx].extargs_double_max << "])" << endl;
									return -1;
								}
								else
									value1 = args[idx].extargs_double_default;
							}
							args[idx].extargs_double_value = value1;
						}
					}
				if (args[idx].extargs_type == ST_EXTARGS_TYPE::double_with_set_default || args[idx].extargs_type == ST_EXTARGS_TYPE::double_with_set_error)
					{
						bool checkstr = true;
						int cnt = 0;
						const string tempstr = argv[i + 1];
						{
							int start = 0;
							if (tempstr.length() == 0)
							{
								checkstr = false;
							}
							if (tempstr.length() == 1)
							{
								if (tempstr[0] == '+' || tempstr[0] == '-')
								{
									checkstr = false;
								}
							}
							if (tempstr[0] == '+' || tempstr[0] == '-')
								start = 1;
							{
								int len = tempstr.length();
								for (int j = start; j < len; j++)
								{
									if ((tempstr[j] < '0' || tempstr[j]>'9') && tempstr[j] != '.')
										checkstr = false;
									if (tempstr[j] == '.')
										cnt++;
								}
							}
							if (cnt > 1)
								checkstr = false;
						}
						if (checkstr == false)
						{
							cout << "参数[" << argv[i] << "]的附加参数不是浮点数. (类型:double, 范围[";
							for (const double* p = args[idx].extargs_double_set; *p != INVALID_DOUBLE_VALUE_OF_SET;)
							{
								cout << *p++;
								cout << (*p == INVALID_DOUBLE_VALUE_OF_SET ? "]" : "/");
							}
							if (args[idx].extargs_type == ST_EXTARGS_TYPE::double_with_set_error)
								cout << ")" << endl;
							else
								cout << " 缺省:" << args[idx].extargs_double_default << ")" << endl;
							return -1;
						}
						else
						{
							double value2 = stod(argv[i + 1]);
							bool flag = false;
							for (const double* p = args[idx].extargs_double_set; *p != INVALID_DOUBLE_VALUE_OF_SET; p++)
							{
								if (*p == value2)
								{
									flag = true;
									break;
								}
							}
							if (!flag) {
								if (args[idx].extargs_type == ST_EXTARGS_TYPE::double_with_set_error)
								{
									cout << "参数[" << argv[i] << "]的附加参数值(" << value2 << ")非法. (类型:double, 范围[";
									for (const double* p = args[idx].extargs_double_set; *p != INVALID_DOUBLE_VALUE_OF_SET;)
									{
										cout << *p++;
										cout << (*p == INVALID_DOUBLE_VALUE_OF_SET ? "]" : "/");
									}
									cout << ")" << endl;
									return -1;
								}
								else
									value2 = args[idx].extargs_double_default;
							}
							args[idx].extargs_double_value = value2;
						}
					}
				if (args[idx].extargs_type == ST_EXTARGS_TYPE::str)
					{
						if (check_format(argv[i + 1]))
						{
							cout << "参数[" << argv[i] << "]缺少附加参数. (类型:string";
							if (!args[idx].extargs_string_default.empty())
								cout << " 缺省:" << args[idx].extargs_string_default << ")" << endl;
							else
								cout << ")" << endl;
							return -1;
						}
						args[idx].extargs_string_value = argv[i + 1];
					}
				if (args[idx].extargs_type == ST_EXTARGS_TYPE::str_with_set_default || args[idx].extargs_type == ST_EXTARGS_TYPE::str_with_set_error)
					{
						if (check_format(argv[i + 1]))
						{
							cout << "参数[" << argv[i] << "]的附加参数不足. (类型:string, 可取值[";
							for (const string* p = args[idx].extargs_string_set; !p->empty();) {
								cout << *p++;
								cout << (p == args[idx].extargs_string_set ? "]" : "/");
							}
							if (args[idx].extargs_type == ST_EXTARGS_TYPE::str_with_set_error)
								cout << ")" << endl;
							else
								cout << " 缺省:" << args[idx].extargs_string_default << ")" << endl;
							return -1;
						}
						string strvalue = argv[i + 1];
						bool flag = false;
						for (const string* p = args[idx].extargs_string_set; !p->empty(); p++) 
						{
							if (*p == strvalue) {
								flag = true;
								break;
							}
						}
						if (!flag)
						{
							if (args[idx].extargs_type == ST_EXTARGS_TYPE::str_with_set_error)
							{
								cout << "参数[" << argv[i] << "]的附加参数值(" << argv[i + 1] << ")非法. (类型:string, 可取值[";
								for (const string* p = args[idx].extargs_string_set; !p->empty();) {
									cout << *p++;
									cout << (p == args[idx].extargs_string_set ? "]" : "/");
								}
								cout << ")" << endl;
								return -1;
							}
							else
								strvalue = args[idx].extargs_string_default;
						}
						args[idx].extargs_string_value = strvalue;
					}
				if (args[idx].extargs_type == ST_EXTARGS_TYPE::ipaddr_with_default || args[idx].extargs_type == ST_EXTARGS_TYPE::ipaddr_with_error)
					{
						if (!check_ip(argv[i + 1]))
						{
							if (args[idx].extargs_type == ST_EXTARGS_TYPE::ipaddr_with_error) {
								cout << "参数[" << argv[i] << "]的附加参数值(" << argv[i + 1] << ")非法. (类型:IP地址)";
								return -1;
							}
							else
								args[idx].extargs_ipaddr_value = args[idx].extargs_ipaddr_default;
						}
						else
							args[idx].extargs_ipaddr_value = IPtoUINT(argv[i + 1]);
					}
				i++;
				num++;
			}
		}
		else//格式不对
		{
			if (follow_up_args)
			{
				return num;
			}
			cout << "参数[" << argv[i] << "]格式非法(不是--开头的有效内容)." << endl;
			return -1;
		}
	}
	return num;
	//return 0; //此句根据需要修改
}

int args_analyse_print(const args_analyse_tools* const args)
{
	int row = 0;
	while (!args[row].args_name.empty())//有个头行
	{
		row++;
	}
	string infor[6] = { " name","type","default","exists","value","range/set " };
	int len[6] = { 0,0,0,0,0,0 };
	for (int i = 0; i < 6; i++)
	{
		len[i] = infor[i].size() ;
	}
	for (int i = 0; i < row; i++)
	{
		len[0] = len[0] >(int)(args[i].args_name).size() ? len[0] : (args[i].args_name).size();
	}
	len[0]++;//空格

	for (int i = 0; i < row; i++)
	{
		len[1] = len[1] > get_enum_string_length(args[i].extargs_type) ? len[1] : get_enum_string_length(args[i].extargs_type);
	}
	len[1]++;//空格

	for (int i = 0; i < row; i++)
	{
		string nowdefault = "/";
		string type_name = ST_EXTARGS_TYPE_to_string(args[i].extargs_type);
		if (type_name.find("Error")!=-1)//判断是不是default == "/"
		{
			//cout << nowdefault << endl;
		}
		else
		{
			if (type_name.find("Int") != -1)
			{
				nowdefault = to_string(args[i].extargs_int_default);
			}
			if (type_name.find("Double") != -1)
			{
				nowdefault = to_string(args[i].extargs_double_default);
			}
			if (type_name.find("String") != -1)
			{
				if (args[i].extargs_string_default != "")
					nowdefault = (args[i].extargs_string_default);
			}
			if (type_name.find("Bool") != -1)
			{
				nowdefault = args[i].extargs_bool_default ? "true" : "false";
			}
			if (type_name.find("IP") != -1)
			{
				nowdefault = args->get_str_ipaddr();
			}
			len[2] = len[2] > (int)nowdefault.size() ? len[2] : nowdefault.size();
			//cout << nowdefault << endl;
		}
	}
	len[2]++;
	//cout << len[2] << endl;
	for (int i = 0; i < row; i++)
	{
		len[3] = len[3] > (int)(to_string(args[i].args_existed).size()) ? len[3] : (int)(to_string(args[i].args_existed).size());
	}
	len[3]++;
	//cout << len[3] << endl;

	for (int i = 0; i < row; i++)
	{
		string nowvalue = "/";
		string type_name = ST_EXTARGS_TYPE_to_string(args[i].extargs_type);
		if (args[i].args_existed == 0)//判断是否存在
		{

		}
		else
		{
			if (type_name.find("Int") != -1)
			{
				nowvalue = to_string(args[i].extargs_int_value);
			}
			if (type_name.find("Double") != -1)
			{
				nowvalue = to_string(args[i].extargs_double_value);
			}
			if (type_name.find("String") != -1)
			{
				if (args[i].extargs_string_value != "")
					nowvalue = (args[i].extargs_string_value);
			}
			if (type_name.find("Bool") != -1)
			{
				nowvalue = args[i].args_existed ? "true" : "false";
			}
			if (type_name.find("IP") != -1)
			{
				nowvalue = args->get_str_ipaddr();
			}
			len[4] = len[4] > (int)nowvalue.size() ? len[4] : nowvalue.size();
			//cout << nowdefault << endl;
		}
	}
	len[4]++;
	//cout << len[4] << endl;

	for (int i = 0; i < row; i++)
	{
		string nowrange = "";
		string type_name = ST_EXTARGS_TYPE_to_string(args[i].extargs_type);
		{
			if (type_name.find("Int") != -1)
			{
				if (type_name.find("SET")!=-1)
				{
					int start = 0;
					while (args[i].extargs_int_set[start] != INVALID_INT_VALUE_OF_SET)
					{
						start++;
					}
					for (int j = 0; j < start; j++)
					{
						nowrange = nowrange + to_string(args[i].extargs_int_set[j]) + "/";
					}
					nowrange = nowrange.substr(0, nowrange.size() - 1);
				}
				else
				{
					nowrange = "[" + to_string(args[i].extargs_int_min) + ".." + to_string(args[i].extargs_int_max) + "]";
				}
			}
			if (type_name.find("Double") != -1)
			{
				if (type_name.find("SET")!= -1)
				{
					int start = 0;
					while (args[i].extargs_double_set[start] != INVALID_DOUBLE_VALUE_OF_SET)
					{
						start++;
					}
					for (int j = 0; j < start; j++)
					{
						nowrange = nowrange + to_string(args[i].extargs_double_set[j]) + "/";
					}
					nowrange = nowrange.substr(0, nowrange.size() - 1);
				}
				else
				{
					nowrange = "[" + to_string(args[i].extargs_double_min) + ".." + to_string(args[i].extargs_double_max) + "]";
				}
			}
			if (type_name.find("String") != -1)
			{
				if (type_name.find("SET")!= -1)
				{
					int start = 0;
					while (args[i].extargs_string_set[start] != "")
					{
						start++;
					}
					for (int j = 0; j < start; j++)
					{
						nowrange = nowrange + args[i].extargs_string_set[j] + "/";
					}
					nowrange = nowrange.substr(0, nowrange.size() - 1);
				}
				else
				{
					nowrange = "/";
				}
			}
			if (type_name.find("Bool") != -1)
			{
				nowrange = "/";
			}
			if (type_name.find("IP") != -1)
			{
				nowrange = "/";
			}
			len[5] = len[5] > (int)nowrange.size() ? len[5] : nowrange.size();
			//cout << nowrange << endl;
		}
	}
	len[5]++;
	//cout << len[5] << endl;
	int line_print = len[0] + len[1] + len[2] + len[3] + len[4] + len[5];

	for (int i = 0; i < line_print; i++)
		cout << "=";
	cout << endl;

	for (int i = 0; i < 6; i++)
	{
		cout <<setiosflags(ios::left)<< setw(len[i]) << infor[i];
	}
	cout << endl;

	for (int i = 0; i < line_print; i++)
		cout << "=";
	cout << endl;

	for (int i = 0; i < row; i++)
	{
		cout<<setiosflags(ios::left) << setw(len[0]) << args[i].get_name();

		cout << setiosflags(ios::left) << setw(len[1]) << ST_EXTARGS_TYPE_to_string(args[i].extargs_type);

		{
			string nowdefault = "/";
			string type_name = ST_EXTARGS_TYPE_to_string(args[i].extargs_type);
			if (type_name.find("Error") != -1)//判断是不是default == "/"
			{
				//cout << nowdefault << endl;
			}
			else
			{
				if (type_name.find("Int") != -1)
				{
					nowdefault = to_string(args[i].extargs_int_default);
				}
				if (type_name.find("Double") != -1)
				{
					nowdefault = to_string(args[i].extargs_double_default);
				}
				if (type_name.find("String") != -1)
				{
					if (args[i].extargs_string_default != "")
						nowdefault = (args[i].extargs_string_default);
				}
				if (type_name.find("Bool") != -1)
				{
					nowdefault = args[i].extargs_bool_default ? "true" : "false";
				}
				if (type_name.find("IP") != -1)
				{
					nowdefault = args->get_str_ipaddr();
				}
			}
			cout << setiosflags(ios::left) << setw(len[2]) << nowdefault;
		}

		cout << setiosflags(ios::left) << setw(len[3]) << args[i].args_existed;

		{
			string nowvalue = "/";
			string type_name = ST_EXTARGS_TYPE_to_string(args[i].extargs_type);
			if (args[i].args_existed == 0)//判断是否存在
			{

			}
			else
			{
				if (type_name.find("Int") != -1)
				{
					nowvalue = to_string(args[i].extargs_int_value);
				}
				if (type_name.find("Double") != -1)
				{
					nowvalue = to_string(args[i].extargs_double_value);
				}
				if (type_name.find("String") != -1)
				{
					//if (args[i].extargs_string_default != "")
						nowvalue = (args[i].extargs_string_value);
				}
				if (type_name.find("Bool") != -1)
				{
					nowvalue = args[i].args_existed ? "true" : "false";
				}
				if (type_name.find("IP") != -1)
				{
					nowvalue = args->get_str_ipaddr();
				}
			}
			cout << setiosflags(ios::left) << setw(len[4]) << nowvalue;
		}

		{
			string nowrange = "";
			string type_name = ST_EXTARGS_TYPE_to_string(args[i].extargs_type);
			{
				if (type_name.find("Int") != -1)
				{
					if (type_name.find("SET") != -1)
					{
						int start = 0;
						while (args[i].extargs_int_set[start] != INVALID_INT_VALUE_OF_SET)
						{
							start++;
						}
						for (int j = 0; j < start; j++)
						{
							nowrange = nowrange + to_string(args[i].extargs_int_set[j]) + "/";
						}
						nowrange = nowrange.substr(0, nowrange.size() - 1);
					}
					else
					{
						nowrange = "[" + to_string(args[i].extargs_int_min) + ".." + to_string(args[i].extargs_int_max) + "]";
					}
				}
				if (type_name.find("Double") != -1)
				{
					if (type_name.find("SET") != -1)
					{
						int start = 0;
						while (args[i].extargs_double_set[start] != INVALID_DOUBLE_VALUE_OF_SET)
						{
							start++;
						}
						for (int j = 0; j < start; j++)
						{
							nowrange = nowrange + to_string(args[i].extargs_double_set[j]) + "/";
						}
						nowrange = nowrange.substr(0, nowrange.size() - 1);
					}
					else
					{
						nowrange = "[" + to_string(args[i].extargs_double_min) + ".." + to_string(args[i].extargs_double_max) + "]";
					}
				}
				if (type_name.find("String") != -1)
				{
					if (type_name.find("SET") != -1)
					{
						int start = 0;
						while (args[i].extargs_string_set[start] != "")
						{
							start++;
						}
						for (int j = 0; j < start; j++)
						{
							nowrange = nowrange + args[i].extargs_string_set[j] + "/";
						}
						nowrange = nowrange.substr(0, nowrange.size() - 1);
					}
					else
					{
						nowrange = "/";
					}
				}
				if (type_name.find("Bool") != -1)
				{
					nowrange = "/";
				}
				if (type_name.find("IP") != -1)
				{
					nowrange = "/";
				}
			}
			cout << setiosflags(ios::left) << setw(len[5]) << nowrange;
		}

		cout << endl;
	}

	for (int i = 0; i < line_print; i++)
		cout << "=";
	cout << endl;

	return 0; //此句根据需要修改
}


#endif  !ENABLE_LIB_COMMON_TOOLS
