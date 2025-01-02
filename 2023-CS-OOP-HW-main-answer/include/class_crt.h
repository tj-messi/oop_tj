/* 2150792 计科 牛禄阳 */
#pragma once

/* 允许按需加入需要的头文件等 */ 
#include <string>
#include <cstring>
#include <vector>
#include <fstream>
using namespace std;
/* 定义读配置文件类 */
struct item {
	string name;            // 每一项的名称
	string value;           // 此项的值
	string expression;      // 此项对应的表达式
};

class cfgfile_read_tools {
protected:
	string        cfgname; // 配置文件名 

	/* 允许按需加入需要的数据成员及成员函数 */ 
	ifstream in;
	vector<string> all_group;
	vector<vector<item>>   all_item; // 二维数组，每一行是一个组中的全部项
	bool _is_open;
public:
	/* 构造和析构函数 */ 
	cfgfile_read_tools(const char* _cfgname = "");
	cfgfile_read_tools(const string& _cfgname);
	virtual ~cfgfile_read_tools();

	/* 判断配置文件是否打开成功 */
	bool is_open();

	/* 组读取函数，读出所有的组，放在string型的vector中 */
	int get_all_group(vector <string>& ret);

	/* 项读取函数 - 取某个group的所有item，放在string型的vector中 */
	int get_all_item(const char* const group_name, vector <string>& ret, const bool ignore_lower_upper_case = false);	//测试函数中缺省区分大小写
	int get_all_item(const string& group_name, vector <string>& ret, const bool ignore_lower_upper_case = false);

	/* 项读取函数 - 取某个group的所有item，放在string中 */
	int get_one_item(const char* const group_name, const char* const item_name, string &ret, const bool ignore_lower_upper_case = false);
	int get_one_item(const string& group_name, const string& item_name, string &ret, const bool ignore_lower_upper_case = false);

	/* 项读取函数 - 按数据类型读取某个group的某个item，放在对应数据类型的变量中
		数据类型包括：int/double/string/char * /char */
	int item_get_value(const char* const group_name, const char* const item_name, const char* const def_str, char* str, const int str_maxlen, const bool ignore_lower_upper_case = true);
	int item_get_value(const char* const group_name, const char* const item_name, const char* const def_str, string& value, const bool ignore_lower_upper_case = true);
	int item_get_value(const char* const group_name, const char* const item_name, char &ch, const bool ignore_lower_upper_case = true);
	int item_get_value(const char* const group_name, const char* const item_name, const int min_value, const int max_value, const int def_value, int& value, const bool ignore_lower_upper_case = true);
	int item_get_value(const char* const group_name, const char* const item_name, const double min_value, const double max_value, const double def_value, double& value, const bool ignore_lower_upper_case = true);

	/* 允许按需加入需要的友元声明等 */ 
	friend int read_all_cfgfile(cfgfile_read_tools& cf);
};

/* 找到group_name对应的下标 */
int find_group_index(const vector<string>& source, const char* const name, const bool ignore_lower_upper_case);
int find_group_index(const vector<string>& source, const string& name, const bool ignore_lower_upper_case);
int find_item_index(const vector<item>& source, const char* const name, const bool ignore_lower_upper_case);
int find_item_index(const vector<item>& source, const string& name, const bool ignore_lower_upper_case);
