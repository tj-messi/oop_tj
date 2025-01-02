/* ѧ�� ���� �༶ */
#pragma once

#include <string>
using namespace std;

/* -----------------------------
	ע�⣺����(ENABLE_LIB_COMMON_TOOLS)����򿪣���1��
				��Դ�ļ������в�����������ʹ�� lib_common_tools.lib ����ʵ�ֵ� st_args_analyse������ʦ��������ʵ�ֺ������ο���
		  ����(ENABLE_LIB_COMMON_TOOLS)����رգ���0��
				��Դ�ļ������в�����������ʹ�� class_aat.cpp ����ʵ�ֵ� args_analyse_tools��ĿǰΪ�գ���Ҫ�Լ�ʵ�֣�

		  ͨ��������л������������ڲο�demo���Լ�ʵ��֮�����л�

	������ɲ�����ҵʱ��һ��Ҫ�������£�
		1������(ENABLE_LIB_COMMON_TOOLS)������0
		2���Ӷ�Ӧ�� lib Ŀ¼��ɾ�� lib_common_tools.lib
----------------------------------------------------------------------------------------------------------------------------------------------------------- */
#define ENABLE_LIB_COMMON_TOOLS			 1

#if ENABLE_LIB_COMMON_TOOLS

#include "../include/lib_aat_tools.h"
typedef 	st_args_analyse		args_analyse_tools;				//lib��class��������st_args_analyse

#else

typedef unsigned int u_int;

#define INVALID_INT_VALUE_OF_SET			0x7FFFFFFF
#define INVALID_DOUBLE_VALUE_OF_SET		1e308
#define DOUBLE_DELTA						1e-6	//Լ��double�͵����Ϊ1e-6

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
	tmax						//���ֵ�����Ƴ���
};

/* ---------------------------------------------------------------
	 �������������Ҫ�Ķ���
	 constȫ�ֱ���/staticȫ�ֱ���(����)/define/class/struct/enum/enum class/union��
   ---------------------------------------------------------------- */



/* ---------------------------------------------------------------
	   class args_analyse_tools�Ķ��壬���в��ֲ�Ҫ��������private����������Ҫ�Ķ���
   ---------------------------------------------------------------- */
class args_analyse_tools {
private:
	/* ��Щ��ʼ����ֵ�Ͳ�Ӧ���ٱ� */
	string				args_name;		//�������ƣ������� "--help��ʽ"
	ST_EXTARGS_TYPE		extargs_type;	//�������Ķ������������
	int					extargs_num;	//��������ĸ�����0-1��������δ����

	bool extargs_bool_default;	//bool�Ͷ��������ȱʡֵ��default��

	int  extargs_int_default;	//int�Ͷ��������ȱʡֵ��default��
	int  extargs_int_min;		//int�Ͷ����������Сֵ��min��
	int  extargs_int_max;		//int�Ͷ�����������ֵ��max��
	int *extargs_int_set;		//int�Ͷ�������ļ��ϣ���ʾ��ֻ��һ��ָ��Ŷ��

	double  extargs_double_default;	//double�Ͷ��������ȱʡֵ��default��
	double  extargs_double_min;		//double�Ͷ����������Сֵ��min��
	double  extargs_double_max;		//double�Ͷ�����������ֵ��max��
	double* extargs_double_set;		//double�Ͷ�������ļ��ϣ���ʾ��ֻ��һ��ָ��Ŷ��

	string  extargs_string_default;	//string�Ͷ��������ȱʡֵ(��ipaddr)
	string *extargs_string_set;		//string�Ͷ�������ļ��ϣ���ʾ��ֻ��һ��ָ��Ŷ��

	u_int   extargs_ipaddr_default;		//IP��ַȱʡֵ

	/* ������Щ�Ǳ��� */
	int    args_existed;			//�������Ƿ���ֹ�����ֹ��ͬ���� -n ** -n ** �ظ����֣�
	int    extargs_int_value;		//int�Ͷ������������ֵ
	double extargs_double_value;		//int�Ͷ������������ֵ
	string extargs_string_value;		//string�Ͷ������������ֵ
	u_int  extargs_ipaddr_value;		//IP��ַ�������������ֵ

	/* ---------------------------------------------------------------
		 �������������Ҫ�Ķ��壨�ڲ��ã�
		   1��Ϊ����lib���е�class��ͬ���������������68�ֽڳ�Ա
		   2�������Ҫ�Զ������ݳ�Ա������Ӧ�ۼ�pad����Ĵ�С��ά���ܴ�С200�ֽڲ���
	   ---------------------------------------------------------------- */
	char pad[68];

public:
	args_analyse_tools();
	args_analyse_tools(const char* arg_name, const enum ST_EXTARGS_TYPE type, const int ext_num, const bool def);
	args_analyse_tools(const char* arg_name, const enum ST_EXTARGS_TYPE type, const int ext_num, const int def, const int _min, const int _max);
	args_analyse_tools(const char* arg_name, const enum ST_EXTARGS_TYPE type, const int ext_num, const int def_of_set_pos, const int* const set);
	args_analyse_tools(const char* arg_name, const enum ST_EXTARGS_TYPE type, const int ext_num, const double def, const double _min, const double _max);
	args_analyse_tools(const char* arg_name, const enum ST_EXTARGS_TYPE type, const int ext_num, const int def_of_set_pos, const double* const set);
	args_analyse_tools(const char* arg_name, const enum ST_EXTARGS_TYPE type, const int ext_num, const string def);
	args_analyse_tools(const char* arg_name, const enum ST_EXTARGS_TYPE type, const int ext_num, const int def_of_set_pos, const string* const set);
	~args_analyse_tools();

	/* ��ȡ���� */
	const string get_name() const;		//����ĳ����������ƣ����� "--help"��
	const int    existed() const;			//�ж�ĳ�������Ƿ����
	const int    get_int() const;			//����ĳ�������ֵ��int�ͣ�
	const double get_double() const;		//����ĳ�������ֵ��double�ͣ�
	const string get_string() const;		//����ĳ�������ֵ��string�ͣ�
	const u_int get_ipaddr() const;	//����ĳ�������ֵ��IP��ַ����"127.0.0.1"Ϊ��������u_int32�͵� 0x7f000001��
	const string get_str_ipaddr() const;	//����ĳ�������ֵ��IP��ַ����"127.0.0.1"Ϊ���������ַ�����ʽ��"127.0.0.1"��

    /* �Բ������з���������0/-1 */
	friend int args_analyse_process(const int argc, const char* const *const argv, args_analyse_tools* const args, const int follow_up_args);
	/* ��ӡ������Ľ�� */
	friend int args_analyse_print(const args_analyse_tools*const args);

	/* ---------------------------------------------------------------
		 ���������������Ҫ�Ķ��壨���ⲻ���֣�
	   ---------------------------------------------------------------- */
};

int args_analyse_process(const int argc, const char* const *const argv, args_analyse_tools* const args, const int follow_up_args);
int args_analyse_print(const args_analyse_tools* const args);

#endif  // !ENABLE_LIB_COMMON_TOOLS
