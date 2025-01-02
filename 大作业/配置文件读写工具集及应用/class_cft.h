/* ѧ�� �༶ ���� */ 
#pragma once

#include <fstream>
#include <string>
#include <vector>
#include <climits>
/* �����������Ҫ��ͷ�ļ��� */ 
using namespace std;

static const int MAX_LINE = 1024;	//ָ�������ļ�һ�е���󳤶ȣ��������������Ϊ�Ƿ��������ļ�
static const int MAX_STRLEN = 128;  //ָ����char���鷽ʽ��ȡʱ����󳤶�
static const char* const SIMPLE_GNAME = ""; //�����õ�����

/* ָ�������������ݵ�ȱʡֵ */
static const char         DEFAULT_CHAR_VALUE = '\0';
static const int          DEFAULT_INT_VALUE = INT_MIN;
static const double       DEFAULT_DOUBLE_VALUE = DBL_MIN;
static const char*        DEFAULT_CSTRING_VALUE = "\0"; //���ǵ�ʵ��������/��̬����ռ䣬����nullptr
static const string       DEFAULT_STRING_VALUE = "";
static const unsigned int  DEFAULT_IPADDR_VALUE = 0;

/* ִ�� ��Ŀ�� = ֵ ��ʽ��������ķָ�����������һ�������֣�=��ո񣨺�tab�����������Ҫ����������˴� */
enum class BREAK_CTYPE {
	Equal,	//�� = ���зָ����� prompt = yes
	Space	//�ÿո�/tab���зָ����� prompt yes
};

enum CFGITEM_TYPE {
	TYPE_INT = 0,	//4�ֽ�����
	TYPE_DOUBLE,	//8�ֽڸ���
	TYPE_STRING,	//��string��ʽ��ŵ��ַ���
	TYPE_CSTRING,	//��char������ʽ��ŵ��ַ������������127���ַ���MAX_STRLEN-1��
	TYPE_CHARACTER,	//ȡ�����ַ�
	TYPE_IPADDR,	//ȡIPv4(x.x.x.x)��ʽ��IP��ַ��תΪ32λ�޷���������ʾ
	TYPE_NULL		//�����ж�enum������ֵ
};

/* �����Զ���������Ҫ������ */

/* ���������������ļ��� */
class config_file_tools {
private:
	string   cfgname;
	enum BREAK_CTYPE item_separate_character_type; //�������������ֺ�ֵ�ķָ����������ָ���"="��xxx=yyy /�ָ���" \t"��xxx yyy��xxx\tyyy���ɣ�

	/* �������������Ҫ�����ݳ�Ա�ͳ�Ա������private���ֽ��������ö������⣩ */

public:
	/* ���캯�������ã���ָ�������ļ��е�������/������벢�洢���Զ���ṹ�У������������get�����ĵ��� */
	config_file_tools(const char* const cfgname, const enum BREAK_CTYPE bctype = BREAK_CTYPE::Equal);
	config_file_tools(const string& cfgname, const enum BREAK_CTYPE bctype = BREAK_CTYPE::Equal);
	/* ����ж�̬�ڴ����룬�����������мǵ��ͷſռ� */
	virtual ~config_file_tools();

	/* �ж϶������ļ��Ƿ�ɹ����Ƿ�����cfg_list�� */
	bool is_read_succeeded() const;

	/* ȡ�����ļ��е������飬������ vector �� */
	int get_all_group(vector <string>& ret);

	/* ȡ�����ļ��е�ĳ������������ԭʼ���ݣ������� vector �У�Ĭ����������Сд������ */
	int get_all_item(const char* const group_name, vector <string>& ret, const bool is_case_sensitive = false);
	int get_all_item(const string& group_name, vector <string>& ret, const bool is_case_sensitive = false);

	/* ȡ�����ļ��е�ĳ�����ĳ���ԭʼ���ݣ�����Ϊstring��ʽ��ԭʼ���ݣ������Ǻ��ָ����������û��ƥ����Ŀ������Ĭ��������/��Ŀ����Сд������*/
	int item_get_raw(const char* const group_name, const char* const item_name, string& ret, const bool group_is_case_sensitive = false, const bool item_is_case_sensitive = false);
	int item_get_raw(const string& group_name, const string& item_name, string& ret, const bool group_is_case_sensitive = false, const bool item_is_case_sensitive = false);

	/* ����������ļ��е�ĳ�����ĳ��������Ƿ���ڣ����ڷ���1�������ڷ���0�������ؾ����ֵ�������Ǻ��ָ����������û��ƥ����Ŀ������Ĭ��������/��Ŀ����Сд������*/
	int item_get_null(const char* const group_name, const char* const item_name, const bool group_is_case_sensitive = false, const bool item_is_case_sensitive = false);
	int item_get_null(const string& group_name, const string& item_name, const bool group_is_case_sensitive = false, const bool item_is_case_sensitive = false);

	/* ���ڶ�ָ�����͵�������ĺ��� - char */
	int item_get_char(const char* const group_name, const char* const item_name, char& value,
		const char* const choice_set = nullptr, const char def_value = DEFAULT_CHAR_VALUE, const bool group_is_case_sensitive = false, const bool item_is_case_sensitive = false);
	int item_get_char(const string& group_name, const string& item_name, char& value,
		const char* const choice_set = nullptr, const char def_value = DEFAULT_CHAR_VALUE, const bool group_is_case_sensitive = false, const bool item_is_case_sensitive = false);

	/* ���ڶ�ָ�����͵�������ĺ��� - int */
	int item_get_int(const char* const group_name, const char* const item_name, int& value,
		const int min_value = INT_MIN, const int max_value = INT_MAX, const int def_value = DEFAULT_INT_VALUE, const bool group_is_case_sensitive = false, const bool item_is_case_sensitive = false);
	int item_get_int(const string& group_name, const string& item_name, int& value,
		const int min_value = INT_MIN, const int max_value = INT_MAX, const int def_value = DEFAULT_INT_VALUE, const bool group_is_case_sensitive = false, const bool item_is_case_sensitive = false);

	/* ���ڶ�ָ�����͵�������ĺ��� - double */
	int item_get_double(const char* const group_name, const char* const item_name, double& value,
		const double min_value = DBL_MIN, const double max_value = DBL_MAX, const double def_value = DEFAULT_DOUBLE_VALUE, const bool group_is_case_sensitive = false, const bool item_is_case_sensitive = false);
	int item_get_double(const string& group_name, const string& item_name, double& value,
		const double min_value = DBL_MIN, const double max_value = DBL_MAX, const double def_value = DEFAULT_DOUBLE_VALUE, const bool group_is_case_sensitive = false, const bool item_is_case_sensitive = false);

	/* ���ڶ�ָ�����͵�������ĺ��� - char* / char[] */
	int item_get_cstring(const char* const group_name, const char* const item_name, char* const value,
		const int str_maxlen, const char* const def_value = DEFAULT_CSTRING_VALUE, const bool group_is_case_sensitive = false, const bool item_is_case_sensitive = false);
	int item_get_cstring(const string& group_name, const string& item_name, char* const value,
		const int str_maxlen, const char* const def_value = DEFAULT_CSTRING_VALUE, const bool group_is_case_sensitive = false, const bool item_is_case_sensitive = false);

	/* ���ڶ�ָ�����͵�������ĺ��� - string */
	int item_get_string(const char* const group_name, const char* const item_name, string& value,
		const string& def_value = DEFAULT_STRING_VALUE, const bool group_is_case_sensitive = false, const bool item_is_case_sensitive = false);
	int item_get_string(const string& group_name, const string& item_name, string& value,
		const string& def_value = DEFAULT_STRING_VALUE, const bool group_is_case_sensitive = false, const bool item_is_case_sensitive = false);

	/* ���ڶ�ָ�����͵�������ĺ��� - IP��ַ */
	int item_get_ipaddr(const char* const group_name, const char* const item_name, unsigned int& value,
		const unsigned int& def_value = DEFAULT_IPADDR_VALUE, const bool group_is_case_sensitive = false, const bool item_is_case_sensitive = false);
	int item_get_ipaddr(const string& group_name, const string& item_name, unsigned int& value,
		const unsigned int& def_value = DEFAULT_IPADDR_VALUE, const bool group_is_case_sensitive = false, const bool item_is_case_sensitive = false);

	/* �����������Ҫ����Ԫ�����ȣ�public�в����������������Ա��������Ϊ�ⲿ�޵�������*/ 
};

