/*2351114 ������ �쿡��*/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <sstream>
#include <algorithm>
/* ����Լ���Ҫ��ͷ�ļ���ע������ */
#include "../include/class_cft.h"
using namespace std;

/* ���������Զ��庯����ʵ�֣��Ѹ��������ݲ�ȫ�� */

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

// ���ߺ�����������
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

// ���ߺ�����������Ŀ
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
	// ����ÿ����
	for (size_t i = 0; i < cfg_list.size(); ++i) {
		const ConfigGroup& group = cfg_list[i];
		std::cout << "Group: " << group.name << std::endl;

		// �������ڵ�ÿ��������
		for (size_t j = 0; j < group.items.size(); ++j) {
			const ConfigItem& item = group.items[j];
			//std::cout << "  Item: " << item.name << " = " << item.value << std::endl;
			cout << item.rawline << endl;
		}
	}
}


/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
config_file_tools::config_file_tools(const char* const _cfgname, const enum BREAK_CTYPE bctype )
{

	ifstream infile(_cfgname);
	if (!infile.is_open())
	{
		cout << "�޷��������ļ�: " << _cfgname << endl;
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

		// = �汾�ķָ�
		if(bctype == BREAK_CTYPE::Equal)
		{
			while (getline(infile, line))
			{
				count++;
				check_open = true;
				//cout << count << endl;//�ж���һ��
				//cout << line << endl;

				if (line.empty())//����
				{
					continue;
				}
				else
				{
					//�ȷָ�����ע��
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
					if (line[0] == '[' && line[line.size() - 1] == ']') // ����
					{
						nowGroup = line;
						cfg_list.push_back(ConfigGroup{ nowGroup,{} });
					}
					else
					{
						if (line.find("=") == -1)//û�зָֻ�ܱ�get item all��ȡ
						{
							current_group = &cfg_list.back();
							current_group->items.push_back(ConfigItem{ "" , "",rawline });
						}
						else // �� �ָ�
						{
							int delimiter_pos = line.find("=");
							string item_name = line.substr(0, delimiter_pos);
							string item_value = line.substr(delimiter_pos + 1);

							//trimLine(item_name, "all");
							//cutComment(item_name, " \t");
							//trimLine(item_value, "all");
							//cutComment(item_value, " \t");

							if (nowGroup == "")//����û�����������cfg
							{
								if (cfg_list.size() == 0)
								{
									cfg_list.push_back(ConfigGroup{ "",{} });
								}
								current_group = &cfg_list.back();
								current_group->items.push_back(ConfigItem{ item_name , item_value ,rawline});
							}
							else//������
							{
								current_group = &cfg_list.back();
								current_group->items.push_back(ConfigItem{ item_name , item_value,rawline });
							}
						}
					}
				}
			}
		}

		// tab �汾�ķָ�
		if (bctype == BREAK_CTYPE::Space)
		{
			while (getline(infile, line))
			{
				count++;
				check_open = true;
				//cout << count << endl;//�ж���һ��

				if (line.empty())//����
				{
					continue;
				}
				else
				{
					//�ȷָ�����ע��
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
					if (line[0] == '[' && line[line.size() - 1] == ']') // ����
					{
						nowGroup = line;
						cfg_list.push_back(ConfigGroup{ nowGroup,{} });
					}
					else
					{
						if (line.find(" ") == -1)//û�зָֻ�ܱ�get item all��ȡ
						{
							current_group = &cfg_list.back();
							current_group->items.push_back(ConfigItem{ "" , "",rawline});
						}
						else // �� �ָ�
						{
							int delimiter_pos = line.find(" ");
							string item_name = line.substr(0, delimiter_pos);
							string item_value = line.substr(delimiter_pos + 1);

							//trimLine(item_name, "all");
							//cutComment(item_name, " \t");
							//trimLine(item_value, "all");
							//cutComment(item_value, " \t");

							if (nowGroup == "")//����û�����������cfg
							{
								if (cfg_list.size() == 0)
								{
									cfg_list.push_back(ConfigGroup{ "",{} });
								}
								current_group = &cfg_list.back();
								current_group->items.push_back(ConfigItem{ item_name , item_value , rawline});
							}
							else//������
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
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
config_file_tools::config_file_tools(const string& _cfgname, const enum BREAK_CTYPE bctype)
{
	ifstream infile(_cfgname.c_str());
	if (!infile.is_open())
	{
		cout << "�޷��������ļ�: " << _cfgname << endl;
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

		// = �汾�ķָ�
		if (bctype == BREAK_CTYPE::Equal)
		{
			while (getline(infile, line))
			{
				count++;
				check_open = true;
				//cout << count << endl;//�ж���һ��
				//cout << line << endl;

				if (line.empty())//����
				{
					continue;
				}
				else
				{
					//�ȷָ�����ע��
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
					if (line[0] == '[' && line[line.size() - 1] == ']') // ����
					{
						nowGroup = line;
						cfg_list.push_back(ConfigGroup{ nowGroup,{} });
					}
					else
					{
						if (line.find("=") == -1)//û�зָֻ�ܱ�get item all��ȡ
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
						else // �� �ָ�
						{
							int delimiter_pos = line.find("=");
							string item_name = line.substr(0, delimiter_pos);
							string item_value = line.substr(delimiter_pos + 1);

							//trimLine(item_name, "all");
							//cutComment(item_name, " \t");
							//trimLine(item_value, "all");
							//cutComment(item_value, " \t");

							if (nowGroup == "")//����û�����������cfg
							{
								if (cfg_list.size() == 0)
								{
									cfg_list.push_back(ConfigGroup{ "",{} });
								}
								current_group = &cfg_list.back();
								current_group->items.push_back(ConfigItem{ item_name , item_value ,rawline });
							}
							else//������
							{
								current_group = &cfg_list.back();
								current_group->items.push_back(ConfigItem{ item_name , item_value,rawline });
							}
						}
					}
				}
			}
		}

		// tab �汾�ķָ�
		if (bctype == BREAK_CTYPE::Space)
		{
			while (getline(infile, line))
			{
				count++;
				check_open = true;
				//cout << count << endl;//�ж���һ��

				if (line.empty())//����
				{
					continue;
				}
				else
				{
					//�ȷָ�����ע��
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
					if (line[0] == '[' && line[line.size() - 1] == ']') // ����
					{
						nowGroup = line;
						cfg_list.push_back(ConfigGroup{ nowGroup,{} });
					}
					else
					{
						if (line.find(" ") == -1)//û�зָֻ�ܱ�get item all��ȡ
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
						else // �� �ָ�
						{
							int delimiter_pos = line.find(" ");
							string item_name = line.substr(0, delimiter_pos);
							string item_value = line.substr(delimiter_pos + 1);

							//trimLine(item_name, "all");
							//cutComment(item_name, " \t");
							//trimLine(item_value, "all");
							//cutComment(item_value, " \t");

							if (nowGroup == "")//����û�����������cfg
							{
								if (cfg_list.size() == 0)
								{
									cfg_list.push_back(ConfigGroup{ "",{} });
								}
								current_group = &cfg_list.back();
								current_group->items.push_back(ConfigItem{ item_name , item_value , rawline });
							}
							else//������
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

	/* ������� */
}

/***************************************************************************
  �������ƣ���������
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
config_file_tools::~config_file_tools()
{
	cfg_list.clear();
	/* ������� */
}


/***************************************************************************
  �������ƣ�
  ��    �ܣ��ж϶������ļ��Ƿ�ɹ�
  ���������
  �� �� ֵ��true - �ɹ����Ѷ������е���/��
		   false - ʧ�ܣ��ļ�ĳ�г���/�ļ�ȫ����ע�����
  ˵    ����
***************************************************************************/
bool config_file_tools::is_read_succeeded() const
{
	//return check_open;
	/* ������ɣ�������Ҫ�ı�return��ֵ */
	return true;
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ����������ļ��е�������
  ���������vector <string>& ret : vector ��ÿ��Ϊһ������
  �� �� ֵ������������������������ļ���������Ϊ1������Ϊ"��
  ˵    ����
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
	/* ������ɣ�������Ҫ�ı�return��ֵ */
	return ret.size();
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�����ָ�����������������ԭʼ����
  ���������const char* const group_name������
		   vector <string>& ret��vector ��ÿ��Ϊһ�����ԭʼ����
		   const bool is_case_sensitive = false : �����Ƿ��Сд���У�true-��Сд���� / Ĭ��false-��Сд������
  �� �� ֵ�����������0��ʾ��
  ˵    ����
***************************************************************************/
int config_file_tools::get_all_item(const char* const group_name, vector <string>& ret, const bool is_case_sensitive)
{
	/* ������ɣ�������Ҫ�ı�return��ֵ */
	
	ConfigGroup* group = find_group(group_name, is_case_sensitive);

	if (!group) return 0;

	for (std::vector<ConfigItem>::const_iterator it = group->items.begin(); it != group->items.end(); ++it)
	{
		
		ret.push_back(it->rawline);
	}
	return ret.size();
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�����/��ĿΪstring��ʽ������ͬ��
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
int config_file_tools::get_all_item(const string& group_name, vector <string>& ret, const bool is_case_sensitive)
{
	get_all_item(group_name.c_str(), ret, is_case_sensitive);
	/* ������ɣ�������Ҫ�ı�return��ֵ */
	return ret.size();
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�ȡĳ���ԭʼ���ݣ�=��������ַ���string��ʽ��
  ���������const char* const group_name
		   const char* const item_name
		   string &ret
		   const bool group_is_case_sensitive = false : �����Ƿ��Сд���У�true-��Сд���� / Ĭ��false-��Сд������
		   const bool item_is_case_sensitive = false  : �����Ƿ��Сд���У�true-��Сд���� / Ĭ��false-��Сд������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
int config_file_tools::item_get_raw(const char* const group_name, const char* const item_name, string& ret, const bool group_is_case_sensitive, const bool item_is_case_sensitive)
{
	ConfigGroup* group = find_group(group_name, group_is_case_sensitive);
	if (!group) return 0;

	ConfigItem* item = find_item(group, item_name, item_is_case_sensitive);
	if (!item) return 0;

	ret = item->value;
	/* ������ɣ�������Ҫ�ı�return��ֵ */
	return 1;
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�����/��ĿΪstring��ʽ������ͬ��
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
int config_file_tools::item_get_raw(const string& group_name, const string& item_name, string& ret, const bool group_is_case_sensitive, const bool item_is_case_sensitive)
{
	/* ��������ʵ�� */
	return this->item_get_raw(group_name.c_str(), item_name.c_str(), ret, group_is_case_sensitive, item_is_case_sensitive);
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�ȡĳ������ݣ���������Ϊchar��
  ���������const char* const group_name               ������
		   const char* const item_name                ������
		   const bool group_is_case_sensitive = false : �����Ƿ��Сд���У�true-��Сд���� / Ĭ��false-��Сд������
		   const bool item_is_case_sensitive = false  : �����Ƿ��Сд���У�true-��Сд���� / Ĭ��false-��Сд������
  �� �� ֵ��1 - �������������
		   0 - ���������������
  ˵    ����
***************************************************************************/
int config_file_tools::item_get_null(const char* const group_name, const char* const item_name, const bool group_is_case_sensitive, const bool item_is_case_sensitive)
{
	ConfigGroup* group = find_group(group_name, group_is_case_sensitive);
	if (!group) return 0;

	ConfigItem* item = find_item(group, item_name, item_is_case_sensitive);
	return (item != nullptr) ? 1 : 0;
	/* ������ɣ�������Ҫ�ı�return��ֵ */
	return 0;
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�����/��ĿΪstring��ʽ������ͬ��
  ���������
  �� �� ֵ��
  ˵    ������Ϊ���ߺ���һ���ڳ����ʼ���׶α����ã������ڳ���ִ���б���Ƶ�ε��ã�
		   �������ֱ���׿ǣ�����΢Ӱ��Ч�ʣ�����Ӱ���������ܣ��Ը�Ƶ�ε��ã��˷������ʺϣ�
***************************************************************************/
int config_file_tools::item_get_null(const string& group_name, const string& item_name, const bool group_is_case_sensitive, const bool item_is_case_sensitive)
{
	/* ��������ʵ�� */
	return this->item_get_null(group_name.c_str(), item_name.c_str(), group_is_case_sensitive, item_is_case_sensitive);
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�ȡĳ������ݣ���������Ϊchar��
  ���������const char* const group_name               ������
		   const char* const item_name                ������
		   char& value                                ��������char��ֵ������1ʱ���ţ�����0�򲻿��ţ�
		   const char* const choice_set = nullptr     ���Ϸ���char�ļ��ϣ����磺"YyNn"��ʾ�Ϸ�����ΪY/N�Ҳ��ִ�Сд���ò�����Ĭ��ֵnullptr����ʾȫ���ַ���������飩
		   const char def_value = DEFAULT_CHAR_VALUE  ��������/�����Ƿ�������µ�Ĭ��ֵ���ò�����Ĭ��ֵDEFAULT_CHAR_VALUE�����������
															��ֵ��   DEFAULT_CHAR_VALUE ʱ������0��ֵ�����ţ�
															��ֵ���� DEFAULT_CHAR_VALUE ʱ����value=def_value������1
		   const bool group_is_case_sensitive = false : �����Ƿ��Сд���У�true-��Сд���� / Ĭ��false-��Сд������
		   const bool item_is_case_sensitive = false  : �����Ƿ��Сд���У�true-��Сд���� / Ĭ��false-��Сд������
  �� �� ֵ��1 - ȡ����ȷֵ
			   δȡ��ֵ/δȡ����ȷֵ��������ȱʡֵ��������Ϊȱʡֵ��
		   0 - δȡ����ֻ��Ϊδָ��Ĭ��ֵ������²Ż᷵��0��
  ˵    ����
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

	/* ������ɣ�������Ҫ�ı�return��ֵ */
	return 0;
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�����/��ĿΪstring��ʽ������ͬ��
  ���������
  �� �� ֵ��
  ˵    ������Ϊ���ߺ���һ���ڳ����ʼ���׶α����ã������ڳ���ִ���б���Ƶ�ε��ã�
		   �������ֱ���׿ǣ�����΢Ӱ��Ч�ʣ�����Ӱ���������ܣ��Ը�Ƶ�ε��ã��˷������ʺϣ�
***************************************************************************/
int config_file_tools::item_get_char(const string& group_name, const string& item_name, char& value,
						const char* const choice_set, const char def_value, const bool group_is_case_sensitive, const bool item_is_case_sensitive)
{
	/* ��������ʵ�� */
	return this->item_get_char(group_name.c_str(), item_name.c_str(), value, choice_set, def_value, group_is_case_sensitive, item_is_case_sensitive);
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�ȡĳ������ݣ���������Ϊint��
  ���������const char* const group_name               ������
		   const char* const item_name                ������
		   int& value                                 ��������int��ֵ������1ʱ���ţ�����0�򲻿��ţ�
		   const int min_value = INT_MIN              : �������ݷ�Χ�����ޣ�Ĭ��ΪINT_MIN
		   const int max_value = INT_MAX              : �������ݷ�Χ�����ޣ�Ĭ��ΪINT_MAX
		   const int def_value = DEFAULT_INT_VALUE    ��������/�����Ƿ�������µ�Ĭ��ֵ���ò�����Ĭ��ֵ DEFAULT_INT_VALUE�����������
															��ֵ��   DEFAULT_INT_VALUE ʱ������0��ֵ�����ţ�
															��ֵ���� DEFAULT_INT_VALUE ʱ����value=def_value������1
		   const bool group_is_case_sensitive = false : �����Ƿ��Сд���У�true-��Сд���� / Ĭ��false-��Сд������
		   const bool item_is_case_sensitive = false  : �����Ƿ��Сд���У�true-��Сд���� / Ĭ��false-��Сд������
  �� �� ֵ��
  ˵    ����
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

	/* ������ɣ�������Ҫ�ı�return��ֵ */
	return 0;
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�����/��ĿΪstring��ʽ������ͬ��
  ���������
  �� �� ֵ��
  ˵    ������Ϊ���ߺ���һ���ڳ����ʼ���׶α����ã������ڳ���ִ���б���Ƶ�ε��ã�
		   �������ֱ���׿ǣ�����΢Ӱ��Ч�ʣ�����Ӱ���������ܣ��Ը�Ƶ�ε��ã��˷������ʺϣ�
***************************************************************************/
int config_file_tools::item_get_int(const string& group_name, const string& item_name, int& value,
						const int min_value, const int max_value, const int def_value, const bool group_is_case_sensitive, const bool item_is_case_sensitive)
{
	/* ��������ʵ�� */
	return this->item_get_int(group_name.c_str(), item_name.c_str(), value, min_value, max_value, def_value, group_is_case_sensitive, item_is_case_sensitive);
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�ȡĳ������ݣ���������Ϊdouble��
  ���������const char* const group_name                  ������
		   const char* const item_name                   ������
		   double& value                                 ��������int��ֵ������1ʱ���ţ�����0�򲻿��ţ�
		   const double min_value = __DBL_MIN__          : �������ݷ�Χ�����ޣ�Ĭ��ΪINT_MIN
		   const double max_value = __DBL_MAX__          : �������ݷ�Χ�����ޣ�Ĭ��ΪINT_MAX
		   const double def_value = DEFAULT_DOUBLE_VALUE ��������/�����Ƿ�������µ�Ĭ��ֵ���ò�����Ĭ��ֵDEFAULT_DOUBLE_VALUE�����������
																��ֵ��   DEFAULT_DOUBLE_VALUE ʱ������0��ֵ�����ţ�
																��ֵ���� DEFAULT_DOUBLE_VALUE ʱ����value=def_value������1
		   const bool group_is_case_sensitive = false     : �����Ƿ��Сд���У�true-��Сд���� / Ĭ��false-��Сд������
		   const bool item_is_case_sensitive = false      : �����Ƿ��Сд���У�true-��Сд���� / Ĭ��false-��Сд������
  �� �� ֵ��
  ˵    ����
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
		// ���δ�ҵ������ΪĬ��ֵ
		value = def_value;
		return (def_value != DEFAULT_DOUBLE_VALUE) ? 1 : 0;
	}

	raw_value = item->value;

	trimLine(raw_value, "all");

	double parsed_value = std::stod(raw_value);
	if (parsed_value >= min_value && parsed_value <= max_value) {
		value = parsed_value;
		return 1; // �ɹ�
	}
	value = def_value;
	return (def_value != DEFAULT_DOUBLE_VALUE) ? 1 : 0;
	/* ������ɣ�������Ҫ�ı�return��ֵ */
	return 0;
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�����/��ĿΪstring��ʽ������ͬ��
  ���������
  �� �� ֵ��
  ˵    ������Ϊ���ߺ���һ���ڳ����ʼ���׶α����ã������ڳ���ִ���б���Ƶ�ε��ã�
		   �������ֱ���׿ǣ�����΢Ӱ��Ч�ʣ�����Ӱ���������ܣ��Ը�Ƶ�ε��ã��˷������ʺϣ�
***************************************************************************/
int config_file_tools::item_get_double(const string& group_name, const string& item_name, double& value,
						const double min_value, const double max_value, const double def_value, const bool group_is_case_sensitive, const bool item_is_case_sensitive)
{
	/* ��������ʵ�� */
	return this->item_get_double(group_name.c_str(), item_name.c_str(), value, min_value, max_value, def_value, group_is_case_sensitive, item_is_case_sensitive);
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�ȡĳ������ݣ���������Ϊchar * / char []��
  ���������const char* const group_name                  ������
		   const char* const item_name                   ������
		   char *const value                             ��������C��ʽ���ַ���������1ʱ���ţ�����0�򲻿��ţ�
		   const int str_maxlen                          ��ָ��Ҫ������󳤶ȣ���β�㣩
																���<1�򷵻ؿմ�(����DEFAULT_CSTRING_VALUE����Ȼ����������ͬ����Ҫ����defaultֵ���ܻ��)
																���>MAX_STRLEN ������ΪMAX_STRLEN
		   const char* const def_str                     ������������µ�Ĭ��ֵ���ò�����Ĭ��ֵDEFAULT_CSTRING_VALUE�����������
																��ֵ��   DEFAULT_CSTRING_VALUE ʱ������0��ֵ�����ţ�
																��ֵ���� DEFAULT_CSTRING_VALUE ʱ����value=def_value������1��ע�⣬����ֱ��=��
		   const bool group_is_case_sensitive = false : �����Ƿ��Сд���У�true-��Сд���� / Ĭ��false-��Сд������
		   const bool item_is_case_sensitive = false  : �����Ƿ��Сд���У�true-��Сд���� / Ĭ��false-��Сд������
  �� �� ֵ��
  ˵    ����1��Ϊ�򻯣�δ��\"����ת�崦��������ͨ�ַ�
		   2����β�����󳤶�Ϊstr_maxlen������ʱҪ��֤���㹻�ռ�
		   3����� str_maxlen ������ϵͳԤ������� MAX_STRLEN���� MAX_STRLEN ȡ
***************************************************************************/
int config_file_tools::item_get_cstring(const char* const group_name, const char* const item_name, char* const value,
						const int str_maxlen, const char* const def_value, const bool group_is_case_sensitive, const bool item_is_case_sensitive)
{
	if (str_maxlen <= 0) {
		// �����󳤶�С�ڵ���0��ֱ�ӷ��ؿ��ַ���
		if (value) {
			value[0] = '\0';
		}
		return 0;
	}

	std::string raw_value;

	

	if (!item_get_raw(group_name, item_name, raw_value, group_is_case_sensitive, item_is_case_sensitive)) {
		// ���δ�ҵ������ΪĬ��ֵ
		if (def_value) {
			strncpy(value, def_value, str_maxlen - 1); // ȷ����������󳤶�
			value[str_maxlen - 1] = '\0'; // ȷ���ַ����� NULL ��β
		}
		else {
			value[0] = '\0'; // Ĭ��ֵΪ���ַ���
		}
		return (def_value != nullptr) ? 1 : 0;
	}


	trimLine(raw_value, "all");


	// ����ҵ�����临�Ƶ����������
	strncpy(value, raw_value.c_str(), str_maxlen - 1);
	value[str_maxlen - 1] = '\0'; // ȷ���ַ����� NULL ��β

	/* ������ɣ�������Ҫ�ı�return��ֵ */
	return 1;
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�����/��ĿΪstring��ʽ������ͬ��
  ���������
  �� �� ֵ��
  ˵    ������Ϊ���ߺ���һ���ڳ����ʼ���׶α����ã������ڳ���ִ���б���Ƶ�ε��ã�
		   �������ֱ���׿ǣ�����΢Ӱ��Ч�ʣ�����Ӱ���������ܣ��Ը�Ƶ�ε��ã��˷������ʺϣ�
***************************************************************************/
int config_file_tools::item_get_cstring(const string& group_name, const string& item_name, char* const value,
						const int str_maxlen, const char* const def_value, const bool group_is_case_sensitive, const bool item_is_case_sensitive)

{
	/* ��������ʵ�� */
	return item_get_cstring(group_name.c_str(), item_name.c_str(), value, str_maxlen, def_value, group_is_case_sensitive, item_is_case_sensitive);
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�ȡĳ������ݣ���������Ϊ string ��
  ���������const char* const group_name               ������
		   const char* const item_name                ������
		   string &value                              ��������string��ʽ���ַ���������1ʱ���ţ�����0�򲻿��ţ�
		   const string &def_value                    ������������µ�Ĭ��ֵ���ò�����Ĭ��ֵDEFAULT_STRING_VALUE�����������
															��ֵ��   DEFAULT_STRING_VALUE ʱ������0��ֵ�����ţ�
															��ֵ���� DEFAULT_STRING_VALUE ʱ����value=def_value������1
		   const bool group_is_case_sensitive = false : �����Ƿ��Сд���У�true-��Сд���� / Ĭ��false-��Сд������
		   const bool item_is_case_sensitive = false  : �����Ƿ��Сд���У�true-��Сд���� / Ĭ��false-��Сд������
  �� �� ֵ��
  ˵    ����Ϊ�򻯣�δ��\"����ת�崦��������ͨ�ַ�
***************************************************************************/
int config_file_tools::item_get_string(const char* const group_name, const char* const item_name, string& value,
						const string& def_value, const bool group_is_case_sensitive, const bool item_is_case_sensitive)
{
	std::string raw_value;
	if (!item_get_raw(group_name, item_name, raw_value, group_is_case_sensitive, item_is_case_sensitive)) {
		// ���δ�ҵ������ΪĬ��ֵ
		value = def_value;
		return (def_value != DEFAULT_STRING_VALUE) ? 1 : 0;
	}

	// ����ҵ��ֱ�ӷ�����ֵ
	value = raw_value;

	trimLine(value, "all");
	/* ������ɣ�������Ҫ�ı�return��ֵ */
	return 1;
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�����/��ĿΪstring��ʽ������ͬ��
  ���������
  �� �� ֵ��
  ˵    ������Ϊ���ߺ���һ���ڳ����ʼ���׶α����ã������ڳ���ִ���б���Ƶ�ε��ã�
		   �������ֱ���׿ǣ�����΢Ӱ��Ч�ʣ�����Ӱ���������ܣ��Ը�Ƶ�ε��ã��˷������ʺϣ�
***************************************************************************/
int config_file_tools::item_get_string(const string& group_name, const string& item_name, string& value,
						const string& def_value, const bool group_is_case_sensitive, const bool item_is_case_sensitive)
{
	/* ��������ʵ�� */
	return this->item_get_string(group_name.c_str(), item_name.c_str(), value, def_value, group_is_case_sensitive, item_is_case_sensitive);
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�ȡĳ������ݣ���������Ϊ IPv4 ��ַ��32bit���ͣ�������
  ���������const char* const group_name               ������
		   const char* const item_name                ������
		   unsigned int &value                        ��������IP��ַ��32λ���ͷ�ʽ������1ʱ���ţ�����0�򲻿��ţ�
		   const unsigned int &def_value              ������������µ�Ĭ��ֵ���ò�����Ĭ��ֵDEFAULT_IPADDR_VALUE�����������
															��ֵ��   DEFAULT_IPADDR_VALUE ʱ������0��ֵ�����ţ�
															��ֵ���� DEFAULT_IPADDR_VALUE ʱ����value=def_value������1
		   const bool group_is_case_sensitive = false : �����Ƿ��Сд���У�true-��Сд���� / Ĭ��false-��Сд������
		   const bool item_is_case_sensitive = false  : �����Ƿ��Сд���У�true-��Сд���� / Ĭ��false-��Сд������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
int config_file_tools::item_get_ipaddr(const char* const group_name, const char* const item_name, unsigned int& value,
	const unsigned int& def_value, const bool group_is_case_sensitive, const bool item_is_case_sensitive) {
	// ��ȡ���ԭʼ����
	std::string raw_value;
	if (!item_get_raw(group_name, item_name, raw_value, group_is_case_sensitive, item_is_case_sensitive)) {
		// ���δ�ҵ������ΪĬ��ֵ
		value = def_value;
		return (def_value != DEFAULT_IPADDR_VALUE) ? 1 : 0;
	}

	// ����ԭʼֵ�еĿո�

	trimLine(raw_value, "all");

	raw_value.erase(0, raw_value.find_first_not_of(" \t"));
	raw_value.erase(raw_value.find_last_not_of(" \t") + 1);

	// ���� IP ��ַ
	try {
		unsigned int parsed_value = 0;
		unsigned int octets[4] = { 0 };
		size_t pos = 0;

		for (int i = 0; i < 4; i++) {
			size_t next_dot = raw_value.find('.', pos);
			std::string octet = raw_value.substr(pos, next_dot - pos);

			// ��֤ÿ�������Ƿ��ǺϷ�������
			if (octet.empty() || !std::all_of(octet.begin(), octet.end(), ::isdigit)) {
				throw std::invalid_argument("Invalid IP address format");
			}

			// ת��Ϊ����
			octets[i] = std::stoi(octet);
			if (octets[i] > 255) {
				throw std::out_of_range("IP octet out of range");
			}

			pos = (next_dot == std::string::npos) ? std::string::npos : next_dot + 1;
		}

		// ���û����ȫ�����ĸ����֣��򱨴�
		if (pos != std::string::npos) {
			throw std::invalid_argument("Invalid IP address format");
		}

		// ���ĸ����ֺϳ�Ϊ 32 λ����
		parsed_value = (octets[0] << 24) | (octets[1] << 16) | (octets[2] << 8) | octets[3];
		value = parsed_value;
		return 1;
	}
	catch (...) {
		// ת��ʧ�ܣ�����Ĭ��ֵ
		value = def_value;
		return (def_value != DEFAULT_IPADDR_VALUE) ? 1 : 0;
	}
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�����/��ĿΪstring��ʽ������ͬ��
  ���������
  �� �� ֵ��
  ˵    ������Ϊ���ߺ���һ���ڳ����ʼ���׶α����ã������ڳ���ִ���б���Ƶ�ε��ã�
		   �������ֱ���׿ǣ�����΢Ӱ��Ч�ʣ�����Ӱ���������ܣ��Ը�Ƶ�ε��ã��˷������ʺϣ�
***************************************************************************/
int config_file_tools::item_get_ipaddr(const string& group_name, const string& item_name, unsigned int& value,
						const unsigned int& def_value, const bool group_is_case_sensitive, const bool item_is_case_sensitive)
{
	/* ��������ʵ�� */
	return this->item_get_ipaddr(group_name.c_str(), item_name.c_str(), value, def_value, group_is_case_sensitive, item_is_case_sensitive);
}
