/* 2150792 �ƿ� ţ»�� */
#pragma once

/* �����������Ҫ��ͷ�ļ��� */ 
#include <string>
#include <cstring>
#include <vector>
#include <fstream>
using namespace std;
/* ����������ļ��� */
struct item {
	string name;            // ÿһ�������
	string value;           // �����ֵ
	string expression;      // �����Ӧ�ı��ʽ
};

class cfgfile_read_tools {
protected:
	string        cfgname; // �����ļ��� 

	/* �����������Ҫ�����ݳ�Ա����Ա���� */ 
	ifstream in;
	vector<string> all_group;
	vector<vector<item>>   all_item; // ��ά���飬ÿһ����һ�����е�ȫ����
	bool _is_open;
public:
	/* ������������� */ 
	cfgfile_read_tools(const char* _cfgname = "");
	cfgfile_read_tools(const string& _cfgname);
	virtual ~cfgfile_read_tools();

	/* �ж������ļ��Ƿ�򿪳ɹ� */
	bool is_open();

	/* ���ȡ�������������е��飬����string�͵�vector�� */
	int get_all_group(vector <string>& ret);

	/* ���ȡ���� - ȡĳ��group������item������string�͵�vector�� */
	int get_all_item(const char* const group_name, vector <string>& ret, const bool ignore_lower_upper_case = false);	//���Ժ�����ȱʡ���ִ�Сд
	int get_all_item(const string& group_name, vector <string>& ret, const bool ignore_lower_upper_case = false);

	/* ���ȡ���� - ȡĳ��group������item������string�� */
	int get_one_item(const char* const group_name, const char* const item_name, string &ret, const bool ignore_lower_upper_case = false);
	int get_one_item(const string& group_name, const string& item_name, string &ret, const bool ignore_lower_upper_case = false);

	/* ���ȡ���� - ���������Ͷ�ȡĳ��group��ĳ��item�����ڶ�Ӧ�������͵ı�����
		�������Ͱ�����int/double/string/char * /char */
	int item_get_value(const char* const group_name, const char* const item_name, const char* const def_str, char* str, const int str_maxlen, const bool ignore_lower_upper_case = true);
	int item_get_value(const char* const group_name, const char* const item_name, const char* const def_str, string& value, const bool ignore_lower_upper_case = true);
	int item_get_value(const char* const group_name, const char* const item_name, char &ch, const bool ignore_lower_upper_case = true);
	int item_get_value(const char* const group_name, const char* const item_name, const int min_value, const int max_value, const int def_value, int& value, const bool ignore_lower_upper_case = true);
	int item_get_value(const char* const group_name, const char* const item_name, const double min_value, const double max_value, const double def_value, double& value, const bool ignore_lower_upper_case = true);

	/* �����������Ҫ����Ԫ������ */ 
	friend int read_all_cfgfile(cfgfile_read_tools& cf);
};

/* �ҵ�group_name��Ӧ���±� */
int find_group_index(const vector<string>& source, const char* const name, const bool ignore_lower_upper_case);
int find_group_index(const vector<string>& source, const string& name, const bool ignore_lower_upper_case);
int find_item_index(const vector<item>& source, const char* const name, const bool ignore_lower_upper_case);
int find_item_index(const vector<item>& source, const string& name, const bool ignore_lower_upper_case);
