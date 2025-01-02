#ifndef _ST_TOOLS_ARGS_ANALYSE_H_
#define _ST_TOOLS_ARGS_ANALYSE_H_

#include <string>
using namespace std;

typedef unsigned int u_int;	//��unsigned int����Ϊu_int

#define INVALID_INT_VALUE_OF_SET	0x7FFFFFFF
#define INVALID_DOUBLE_VALUE_OF_SET		1e308
#define DOUBLE_DELTA						1e-6	//Լ��double�͵����Ϊ1e-6

/*  args    extargs_num extargs_type  extargs_fun             extargs_defvalue;
	--help  0           NULL          NULL                    NULL
	--limit 1           INT           char * ת int ����      min/max/def
	--limit 1           INT           char * ת int ����      min/max/��default�����ش�
	--limit 1           INT           char * ת int ����      12/23/35�����е�һ�������ش�
	--user  1           string        char * ת string ����   def
	--user  1           string        char * ת string ����   "abc"/"def"/"xyz"�����е�һ��
	--ip    1           IPADDR        char * ת ipaddr ����   NULL
*/

/* ������ֲ������� */
enum class ST_EXTARGS_TYPE {
	null = 0,					//�������޲γ�ʼ��
	boolean,					//����Ҫ����0/1����ʾ�Ƿ���ڣ����磺--help
	int_with_default,			//���Ӳ���Ϊ���ͣ����� min..max֮�䣬��ȱʡֵ�����ó��������ޣ�����ȱʡֵ
	int_with_error,				//���Ӳ���Ϊ���ͣ����� min..max֮�䣬��ȱʡֵ�����ó��������ޣ��򷵻ش���
	int_with_set_default,		//���Ӳ���Ϊ���ͣ�ֻ������һ��������Ԫ�صļ���[11/22/33]����ȱʡֵ����ֵ���ڼ����У�����ȱʡֵ
	int_with_set_error,			//���Ӳ���Ϊ���ͣ�ֻ������һ��������Ԫ�صļ���[11/22/33]����ȱʡֵ����ֵ���ڼ����У��򷵻ش���
	double_with_default,		//���Ӳ���Ϊʵ�ͣ����� min..max֮�䣬��ȱʡֵ�����ó��������ޣ�����ȱʡֵ
	double_with_error,			//���Ӳ���Ϊʵ�ͣ����� min..max֮�䣬��ȱʡֵ�����ó��������ޣ��򷵻ش���
	double_with_set_default,	//���Ӳ���Ϊʵ�ͣ�ֻ������һ��������Ԫ�صļ���[11/22/33]����ȱʡֵ����ֵ���ڼ����У�����ȱʡֵ
	double_with_set_error,		//���Ӳ���Ϊʵ�ͣ�ֻ������һ��������Ԫ�صļ���[11/22/33]����ȱʡֵ����ֵ���ڼ����У��򷵻ش���
	str,						//���Ӳ���Ϊ�ַ���
	str_with_set_default,		//���Ӳ���Ϊ�ַ�����ֻ������һ��������Ԫ�صļ���["11"/"22"/"33"]����ȱʡֵ����ֵ���ڼ����У�����ȱʡֵ
	str_with_set_error,			//���Ӳ���Ϊ�ַ�����ֻ������һ��������Ԫ�صļ���["11"/"22"/"33"]����ȱʡֵ����ֵ���ڼ����У��򷵻ش���
	ipaddr_with_default,		//���Ӳ���ΪIP��ַ����ȱʡֵ������һ��u_int32
	ipaddr_with_error,			//���Ӳ���ΪIP��ַ����ȱʡֵ�����ش���
	tmax				//���ֵ�����Ƴ���
};

class st_args_analyse {
protected:
	/* ��Щ��ʼ����ֵ�Ͳ�Ӧ���ٱ� */
	string               args_name;		//�������ƣ������� "--help��ʽ"
	ST_EXTARGS_TYPE extargs_type;	//�������Ķ������������
	int                  extargs_num;	//��������ĸ�����0-1��������δ����

	bool extargs_bool_default;		//bool�Ͷ��������ȱʡֵ��default��

	int  extargs_int_default;		//int�Ͷ��������ȱʡֵ��default��
	int  extargs_int_min;			//int�Ͷ����������Сֵ��min��
	int  extargs_int_max;			//int�Ͷ�����������ֵ��max��
	int *extargs_int_set;			//int�Ͷ�������ļ��ϣ���ʾ��ֻ��һ��ָ��Ŷ��

	double  extargs_double_default;	//double�Ͷ��������ȱʡֵ��default��
	double  extargs_double_min;		//double�Ͷ����������Сֵ��min��
	double  extargs_double_max;		//double�Ͷ�����������ֵ��max��
	double* extargs_double_set;		//double�Ͷ�������ļ��ϣ���ʾ��ֻ��һ��ָ��Ŷ��

	string  extargs_string_default;		//string�Ͷ��������ȱʡֵ(��ipaddr)
	string *extargs_string_set;		//string�Ͷ�������ļ��ϣ���ʾ��ֻ��һ��ָ��Ŷ��

	u_int   extargs_ipaddr_default;		//IP��ַȱʡֵ

	/* ������Щ�Ǳ��� */
	int    args_existed;			//�������Ƿ���ֹ�����ֹ��ͬ���� -n ** -n ** �ظ����֣�
	int    extargs_int_value;		//int�Ͷ������������ֵ
	double extargs_double_value;		//int�Ͷ������������ֵ
	string extargs_string_value;		//string�Ͷ������������ֵ
	u_int  extargs_ipaddr_value;		//IP��ַ�������������ֵ

	/* Ϊ�˷��������ú͸�ѧ���ļ��л���ǿ��Լ��class���ܴ�СΪ200�ֽ� */
	char pad[68];

	const char* get_extargs_type_str() const;
	int print(const int width_args_name, const int width_default, const int width_value) const;
	const string get_parameter() const;

public:
	st_args_analyse();
	st_args_analyse(const char *arg_name, const enum ST_EXTARGS_TYPE type, const int ext_num, const bool def);
        /* ע�������⼸�����캯���������һ��Ĭ�ϲ�������ʾ����Ŀ������--ip 1.1.1.1 --ip 2.2.2.2������ʱ����Ҫʵ�� */
	st_args_analyse(const char *arg_name, const enum ST_EXTARGS_TYPE type, const int ext_num, const int def, const int _min, const int _max, const bool mutli_args = false);
	st_args_analyse(const char *arg_name, const enum ST_EXTARGS_TYPE type, const int ext_num, const int def_of_set_pos, const int *const set, const bool mutli_args = false);
	st_args_analyse(const char *arg_name, const enum ST_EXTARGS_TYPE type, const int ext_num, const double def, const double _min, const double _max, const bool mutli_args = false);
	st_args_analyse(const char *arg_name, const enum ST_EXTARGS_TYPE type, const int ext_num, const int def_of_set_pos, const double* const set, const bool mutli_args = false);
	st_args_analyse(const char *arg_name, const enum ST_EXTARGS_TYPE type, const int ext_num, const string def, const bool mutli_args = false);
	st_args_analyse(const char *arg_name, const enum ST_EXTARGS_TYPE type, const int ext_num, const int def_of_set_pos, const string *const set, const bool mutli_args = false);
	~st_args_analyse();

	/* ��ȡ���� */
	const string get_name() const;			//����ĳ����������ƣ����� "--help"��
	const int    existed() const;			//�ж�ĳ�������Ƿ����
	const int    get_int() const;			//����ĳ�������ֵ��int�ͣ�
	const double get_double() const;		//����ĳ�������ֵ��double�ͣ�
	const string get_string() const;		//����ĳ�������ֵ��string�ͣ�
	const u_int get_ipaddr() const;	//����ĳ�������ֵ��IP��ַ����"127.0.0.1"Ϊ��������u_int32�͵� 0x7f000001��
	const string get_str_ipaddr() const;	//����ĳ�������ֵ��IP��ַ����"127.0.0.1"Ϊ���������ַ�����ʽ��"127.0.0.1"��

    /* �Բ������з���������0/-1 */
	friend int args_analyse_process(const int argc, const char* const* const argv, st_args_analyse* const args, const int follow_up_args);
	/* ��ӡ������Ľ�� */
	friend int args_analyse_print(const st_args_analyse* const args);
};

int args_analyse_process(const int argc, const char* const* const argv, st_args_analyse* const args, const int follow_up_args);
int args_analyse_print(const st_args_analyse* const args);

#endif
