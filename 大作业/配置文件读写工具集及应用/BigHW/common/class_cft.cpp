/*2351114 大数据 朱俊泽*/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <sstream>
#include <algorithm>
/* 添加自己需要的头文件，注意限制 */
#include "../include/class_cft.h"
using namespace std;

/* 给出各种自定义函数的实现（已给出的内容不全） */

bool is_only_spaces(const std::string& str)
{
	return str.find_first_not_of(" \t\n\r") == std::string::npos;
}

void trimLine(string& line, const string& trimType)
{
	if (trimType == "left" || trimType == "all")
		line.erase(0, line.find_first_not_of(" \t\r"));
	if (trimType == "right" || trimType == "all")
		line.erase(line.find_last_not_of(" \t\r") + 1);
}

void cutComment(string& str,const char* const commentChar)
{
	int pos = str.find_first_of(commentChar);
	if (pos != string::npos)
		str.erase(pos);
}

static string to_lower(const std::string& str)
{
	string lower_str = str;
	transform(lower_str.begin(), lower_str.end(), lower_str.begin(), ::tolower);
	return lower_str;
}


static bool str_case_cmp(const string& a, const string& b)
{
	return to_lower(a) == to_lower(b);
}

// 工具函数：查找组
ConfigGroup* config_file_tools::find_group(const std::string& group_name, const bool is_case_sensitive) 
{
	for (std::vector<ConfigGroup>::iterator it = cfg_list.begin(); it != cfg_list.end(); ++it) 
	{
		string temp_name = it->name;
		trimLine(temp_name, "all");
		if ((is_case_sensitive && temp_name == group_name) || (!is_case_sensitive && str_case_cmp(temp_name, group_name)))
		{
			return &(*it);
		}
	}
	return nullptr;
}

// 工具函数：查找项目
ConfigItem* config_file_tools::find_item(ConfigGroup* group, const std::string& item_name, const bool is_case_sensitive)
{
	for (std::vector<ConfigItem>::iterator it = group->items.begin(); it != group->items.end(); ++it) 
	{
		string temp_name = it->name;
		trimLine(temp_name, "all");
		if ((is_case_sensitive && temp_name == item_name) || (!is_case_sensitive && str_case_cmp(temp_name, item_name)))
		{
			return &(*it);
		}
	}
	return nullptr;
}

void config_file_tools::print_config_data() const {
	// 遍历每个组
	for (size_t i = 0; i < cfg_list.size(); ++i) {
		const ConfigGroup& group = cfg_list[i];
		std::cout << "Group: " << group.name << std::endl;

		// 遍历组内的每个配置项
		for (size_t j = 0; j < group.items.size(); ++j) {
			const ConfigItem& item = group.items[j];
			//std::cout << "  Item: " << item.name << " = " << item.value << std::endl;
			cout << item.rawline << endl;
		}
	}
}


/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
config_file_tools::config_file_tools(const char* const _cfgname, const enum BREAK_CTYPE bctype )
{

	ifstream infile(_cfgname);
	if (!infile.is_open())
	{
		cout << "无法打开配置文件: " << _cfgname << endl;
		check_open = false;
		return;
	}
	else
	{
		string rawline;
		check_open = true;
		cfgname = _cfgname;
		string line;
		string nowGroup = "";
		ConfigGroup* current_group = nullptr;
		int count = 0;

		// = 版本的分割
		if(bctype == BREAK_CTYPE::Equal)
		{
			while (getline(infile, line))
			{
				count++;
				check_open = true;
				//cout << count << endl;//判断那一行
				//cout << line << endl;

				if (line.empty())//空行
				{
					continue;
				}
				else
				{
					//先分割特殊注释
					if (line.find("//") != -1 || line.find("#") != -1 || line.find(";") != -1)
					{
						if (line.find("//") != -1)
						{
							line = line.substr(0, line.find("//"));
						}
						if (line.find("#") != -1)
						{
							line = line.substr(0, line.find("#"));
						}
						if (line.find(";") != -1)
						{
							line = line.substr(0, line.find(";"));
						}
					}
					if (is_only_spaces(line) || line == "")
						continue;
					trimLine(line, "all");
					rawline = line;
					if (line[0] == '[' && line[line.size() - 1] == ']') // 组名
					{
						nowGroup = line;
						cfg_list.push_back(ConfigGroup{ nowGroup,{} });
					}
					else
					{
						if (line.find("=") == -1)//没有分割，只能被get item all读取
						{
							current_group = &cfg_list.back();
							current_group->items.push_back(ConfigItem{ "" , "",rawline });
						}
						else // 有 分割
						{
							int delimiter_pos = line.find("=");
							string item_name = line.substr(0, delimiter_pos);
							string item_value = line.substr(delimiter_pos + 1);

							//trimLine(item_name, "all");
							//cutComment(item_name, " \t");
							//trimLine(item_value, "all");
							//cutComment(item_value, " \t");

							if (nowGroup == "")//现在没有组名，混合cfg
							{
								if (cfg_list.size() == 0)
								{
									cfg_list.push_back(ConfigGroup{ "",{} });
								}
								current_group = &cfg_list.back();
								current_group->items.push_back(ConfigItem{ item_name , item_value ,rawline});
							}
							else//有组名
							{
								current_group = &cfg_list.back();
								current_group->items.push_back(ConfigItem{ item_name , item_value,rawline });
							}
						}
					}
				}
			}
		}

		// tab 版本的分割
		if (bctype == BREAK_CTYPE::Space)
		{
			while (getline(infile, line))
			{
				count++;
				check_open = true;
				//cout << count << endl;//判断那一行

				if (line.empty())//空行
				{
					continue;
				}
				else
				{
					//先分割特殊注释
					if (line.find("//") != -1 || line.find("#") != -1 || line.find(";") != -1)
					{
						if (line.find("//") != -1)
						{
							line = line.substr(0, line.find("//"));
						}
						if (line.find("#") != -1)
						{
							line = line.substr(0, line.find("#"));
						}
						if (line.find(";") != -1)
						{
							line = line.substr(0, line.find(";"));
						}
					}
					if (is_only_spaces(line) || line == "")
						continue;
					trimLine(line, "all");
					rawline = line;
					if (line[0] == '[' && line[line.size() - 1] == ']') // 组名
					{
						nowGroup = line;
						cfg_list.push_back(ConfigGroup{ nowGroup,{} });
					}
					else
					{
						if (line.find(" ") == -1)//没有分割，只能被get item all读取
						{
							current_group = &cfg_list.back();
							current_group->items.push_back(ConfigItem{ "" , "",rawline});
						}
						else // 有 分割
						{
							int delimiter_pos = line.find(" ");
							string item_name = line.substr(0, delimiter_pos);
							string item_value = line.substr(delimiter_pos + 1);

							//trimLine(item_name, "all");
							//cutComment(item_name, " \t");
							//trimLine(item_value, "all");
							//cutComment(item_value, " \t");

							if (nowGroup == "")//现在没有组名，混合cfg
							{
								if (cfg_list.size() == 0)
								{
									cfg_list.push_back(ConfigGroup{ "",{} });
								}
								current_group = &cfg_list.back();
								current_group->items.push_back(ConfigItem{ item_name , item_value , rawline});
							}
							else//有组名
							{
								current_group = &cfg_list.back();
								current_group->items.push_back(ConfigItem{ item_name , item_value ,rawline});
							}
						}
					}

				}
			}
		}
		infile.close();
	}

}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
config_file_tools::config_file_tools(const string& _cfgname, const enum BREAK_CTYPE bctype)
{
	ifstream infile(_cfgname.c_str());
	if (!infile.is_open())
	{
		cout << "无法打开配置文件: " << _cfgname << endl;
		check_open = false;
		return;
	}
	else
	{
		string rawline;
		check_open = true;
		cfgname = _cfgname;
		string line;
		string nowGroup = "";
		ConfigGroup* current_group = nullptr;
		int count = 0;

		// = 版本的分割
		if (bctype == BREAK_CTYPE::Equal)
		{
			while (getline(infile, line))
			{
				count++;
				check_open = true;
				//cout << count << endl;//判断那一行
				//cout << line << endl;

				if (line.empty())//空行
				{
					continue;
				}
				else
				{
					//先分割特殊注释
					if (line.find("//") != -1 || line.find("#") != -1 || line.find(";") != -1)
					{
						if (line.find("//") != -1)
						{
							line = line.substr(0, line.find("//"));
						}
						if (line.find("#") != -1)
						{
							line = line.substr(0, line.find("#"));
						}
						if (line.find(";") != -1)
						{
							line = line.substr(0, line.find(";"));
						}
					}
					if (is_only_spaces(line) || line == "")
						continue;
					trimLine(line, "all");
					rawline = line;
					if (line[0] == '[' && line[line.size() - 1] == ']') // 组名
					{
						nowGroup = line;
						cfg_list.push_back(ConfigGroup{ nowGroup,{} });
					}
					else
					{
						if (line.find("=") == -1)//没有分割，只能被get item all读取
						{
							if(cfg_list.size()!=0)
							{
								current_group = &cfg_list.back();
							}
							else
							{
								cfg_list.push_back(ConfigGroup{ "",{} });
								current_group = &cfg_list.back();
							}
							current_group->items.push_back(ConfigItem{ "" , "",rawline });
						}
						else // 有 分割
						{
							int delimiter_pos = line.find("=");
							string item_name = line.substr(0, delimiter_pos);
							string item_value = line.substr(delimiter_pos + 1);

							//trimLine(item_name, "all");
							//cutComment(item_name, " \t");
							//trimLine(item_value, "all");
							//cutComment(item_value, " \t");

							if (nowGroup == "")//现在没有组名，混合cfg
							{
								if (cfg_list.size() == 0)
								{
									cfg_list.push_back(ConfigGroup{ "",{} });
								}
								current_group = &cfg_list.back();
								current_group->items.push_back(ConfigItem{ item_name , item_value ,rawline });
							}
							else//有组名
							{
								current_group = &cfg_list.back();
								current_group->items.push_back(ConfigItem{ item_name , item_value,rawline });
							}
						}
					}
				}
			}
		}

		// tab 版本的分割
		if (bctype == BREAK_CTYPE::Space)
		{
			while (getline(infile, line))
			{
				count++;
				check_open = true;
				//cout << count << endl;//判断那一行

				if (line.empty())//空行
				{
					continue;
				}
				else
				{
					//先分割特殊注释
					if (line.find("//") != -1 || line.find("#") != -1 || line.find(";") != -1)
					{
						if (line.find("//") != -1)
						{
							line = line.substr(0, line.find("//"));
						}
						if (line.find("#") != -1)
						{
							line = line.substr(0, line.find("#"));
						}
						if (line.find(";") != -1)
						{
							line = line.substr(0, line.find(";"));
						}
					}
					if (is_only_spaces(line) || line == "")
						continue;
					trimLine(line, "all");
					rawline = line;
					if (line[0] == '[' && line[line.size() - 1] == ']') // 组名
					{
						nowGroup = line;
						cfg_list.push_back(ConfigGroup{ nowGroup,{} });
					}
					else
					{
						if (line.find(" ") == -1)//没有分割，只能被get item all读取
						{
							if (cfg_list.size() != 0)
							{
								current_group = &cfg_list.back();
							}
							else
							{
								cfg_list.push_back(ConfigGroup{ "",{} });
								current_group = &cfg_list.back();
							}
							current_group->items.push_back(ConfigItem{ "" , "",rawline });
						}
						else // 有 分割
						{
							int delimiter_pos = line.find(" ");
							string item_name = line.substr(0, delimiter_pos);
							string item_value = line.substr(delimiter_pos + 1);

							//trimLine(item_name, "all");
							//cutComment(item_name, " \t");
							//trimLine(item_value, "all");
							//cutComment(item_value, " \t");

							if (nowGroup == "")//现在没有组名，混合cfg
							{
								if (cfg_list.size() == 0)
								{
									cfg_list.push_back(ConfigGroup{ "",{} });
								}
								current_group = &cfg_list.back();
								current_group->items.push_back(ConfigItem{ item_name , item_value , rawline });
							}
							else//有组名
							{
								current_group = &cfg_list.back();
								current_group->items.push_back(ConfigItem{ item_name , item_value ,rawline });
							}
						}
					}

				}
			}
		}
		infile.close();
	}

	/* 按需完成 */
}

/***************************************************************************
  函数名称：析构函数
  功    能：
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
config_file_tools::~config_file_tools()
{
	cfg_list.clear();
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
	//return check_open;
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
	int cnt = 0;
	for (int i = 0; i <(int) cfg_list.size(); i++)
	{
		if (cfg_list[i].name == "")
		{
			//continue;
		}
		ret.push_back(cfg_list[i].name);
		cnt++;
	}
	/* 按需完成，根据需要改变return的值 */
	return ret.size();
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
	
	ConfigGroup* group = find_group(group_name, is_case_sensitive);

	if (!group) return 0;

	for (std::vector<ConfigItem>::const_iterator it = group->items.begin(); it != group->items.end(); ++it)
	{
		
		ret.push_back(it->rawline);
	}
	return ret.size();
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
	get_all_item(group_name.c_str(), ret, is_case_sensitive);
	/* 按需完成，根据需要改变return的值 */
	return ret.size();
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
	ConfigGroup* group = find_group(group_name, group_is_case_sensitive);
	if (!group) return 0;

	ConfigItem* item = find_item(group, item_name, item_is_case_sensitive);
	if (!item) return 0;

	ret = item->value;
	/* 按需完成，根据需要改变return的值 */
	return 1;
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
	ConfigGroup* group = find_group(group_name, group_is_case_sensitive);
	if (!group) return 0;

	ConfigItem* item = find_item(group, item_name, item_is_case_sensitive);
	return (item != nullptr) ? 1 : 0;
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
	ConfigGroup* group = find_group(group_name, group_is_case_sensitive);
	if (!group) return 0;

	ConfigItem* item = find_item(group, item_name, item_is_case_sensitive);
	if (item == nullptr)
		return 0;

	string raw_value = item->value;

	trimLine(raw_value, "all");

	//value = raw_value[0];
	if(raw_value.size()!=1 || is_only_spaces(raw_value))
	{
		if (value == DEFAULT_CHAR_VALUE)
			return 0;
		else
		{
			value = def_value;
			return 1;
		}
	}
	else
	{
		return 1;
	}

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
	string raw_value;
	ConfigGroup* group = find_group(group_name, group_is_case_sensitive);
	if (!group) return 0;

	ConfigItem* item = find_item(group, item_name, item_is_case_sensitive);
	if (item == nullptr)
		return 0;

	if (!item_get_raw(group_name, item_name, raw_value, group_is_case_sensitive, item_is_case_sensitive)) {
		value = def_value;
		return (def_value != DEFAULT_INT_VALUE) ? 1 : 0;
	}

	 raw_value = item->value;

	 trimLine(raw_value, "all");

	 int parsed_value = std::stoi(raw_value);
	 if (parsed_value >= min_value && parsed_value <= max_value) {
		 value = parsed_value;
		 return 1;
	 }
	 else
	 {
		 value = def_value;
		 return (def_value != DEFAULT_INT_VALUE) ? 1 : 0;
	 }

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
	std::string raw_value;

	ConfigGroup* group = find_group(group_name, group_is_case_sensitive);
	if (!group) return 0;

	ConfigItem* item = find_item(group, item_name, item_is_case_sensitive);
	if (item == nullptr)
		return 0;
	if (!item_get_raw(group_name, item_name, raw_value, group_is_case_sensitive, item_is_case_sensitive)) {
		// 如果未找到项，设置为默认值
		value = def_value;
		return (def_value != DEFAULT_DOUBLE_VALUE) ? 1 : 0;
	}

	raw_value = item->value;

	trimLine(raw_value, "all");

	double parsed_value = std::stod(raw_value);
	if (parsed_value >= min_value && parsed_value <= max_value) {
		value = parsed_value;
		return 1; // 成功
	}
	value = def_value;
	return (def_value != DEFAULT_DOUBLE_VALUE) ? 1 : 0;
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
	if (str_maxlen <= 0) {
		// 如果最大长度小于等于0，直接返回空字符串
		if (value) {
			value[0] = '\0';
		}
		return 0;
	}

	std::string raw_value;

	

	if (!item_get_raw(group_name, item_name, raw_value, group_is_case_sensitive, item_is_case_sensitive)) {
		// 如果未找到项，设置为默认值
		if (def_value) {
			strncpy(value, def_value, str_maxlen - 1); // 确保不超过最大长度
			value[str_maxlen - 1] = '\0'; // 确保字符串以 NULL 结尾
		}
		else {
			value[0] = '\0'; // 默认值为空字符串
		}
		return (def_value != nullptr) ? 1 : 0;
	}


	trimLine(raw_value, "all");


	// 如果找到项，将其复制到输出缓冲区
	strncpy(value, raw_value.c_str(), str_maxlen - 1);
	value[str_maxlen - 1] = '\0'; // 确保字符串以 NULL 结尾

	/* 按需完成，根据需要改变return的值 */
	return 1;
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
	std::string raw_value;
	if (!item_get_raw(group_name, item_name, raw_value, group_is_case_sensitive, item_is_case_sensitive)) {
		// 如果未找到项，设置为默认值
		value = def_value;
		return (def_value != DEFAULT_STRING_VALUE) ? 1 : 0;
	}

	// 如果找到项，直接返回其值
	value = raw_value;

	trimLine(value, "all");
	/* 按需完成，根据需要改变return的值 */
	return 1;
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
	const unsigned int& def_value, const bool group_is_case_sensitive, const bool item_is_case_sensitive) {
	// 获取项的原始内容
	std::string raw_value;
	if (!item_get_raw(group_name, item_name, raw_value, group_is_case_sensitive, item_is_case_sensitive)) {
		// 如果未找到项，设置为默认值
		value = def_value;
		return (def_value != DEFAULT_IPADDR_VALUE) ? 1 : 0;
	}

	// 清理原始值中的空格

	trimLine(raw_value, "all");

	raw_value.erase(0, raw_value.find_first_not_of(" \t"));
	raw_value.erase(raw_value.find_last_not_of(" \t") + 1);

	// 解析 IP 地址
	try {
		unsigned int parsed_value = 0;
		unsigned int octets[4] = { 0 };
		size_t pos = 0;

		for (int i = 0; i < 4; i++) {
			size_t next_dot = raw_value.find('.', pos);
			std::string octet = raw_value.substr(pos, next_dot - pos);

			// 验证每个部分是否是合法的数字
			if (octet.empty() || !std::all_of(octet.begin(), octet.end(), ::isdigit)) {
				throw std::invalid_argument("Invalid IP address format");
			}

			// 转换为整数
			octets[i] = std::stoi(octet);
			if (octets[i] > 255) {
				throw std::out_of_range("IP octet out of range");
			}

			pos = (next_dot == std::string::npos) ? std::string::npos : next_dot + 1;
		}

		// 如果没有完全解析四个部分，则报错
		if (pos != std::string::npos) {
			throw std::invalid_argument("Invalid IP address format");
		}

		// 将四个部分合成为 32 位整数
		parsed_value = (octets[0] << 24) | (octets[1] << 16) | (octets[2] << 8) | octets[3];
		value = parsed_value;
		return 1;
	}
	catch (...) {
		// 转换失败，设置默认值
		value = def_value;
		return (def_value != DEFAULT_IPADDR_VALUE) ? 1 : 0;
	}
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
