/* 2150792 ţ»�� �ƿ� */
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
#define ENABLE_LIB_COMMON_TOOLS			 0

#if ENABLE_LIB_COMMON_TOOLS

#include "../include/lib_aat_tools.h"
typedef 	st_args_analyse		args_analyse_tools;				//lib��class��������st_args_analyse

#else

#define INVALID_INT_VALUE_OF_SET	0x7FFFFFFF

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
	null = 0,				//�������޲γ�ʼ��
	boolean,					//����Ҫ����0/1����ʾ�Ƿ���ڣ����磺--help
	int_with_default,		//���Ӳ���Ϊ���ͣ����� min..max֮�䣬��ȱʡֵ�����ó��������ޣ�����ȱʡֵ
	int_with_error,			//���Ӳ���Ϊ���ͣ����� min..max֮�䣬��ȱʡֵ�����ó��������ޣ��򷵻ش���
	int_with_set_default,	//���Ӳ���Ϊ���ͣ�ֻ������һ��������Ԫ�صļ���[11/22/33]����ȱʡֵ����ֵ���ڼ����У�����ȱʡֵ
	int_with_set_error,		//���Ӳ���Ϊ���ͣ�ֻ������һ��������Ԫ�صļ���[11/22/33]����ȱʡֵ����ֵ���ڼ����У��򷵻ش���
	str,						//���Ӳ���Ϊ�ַ���
	str_with_set_default,	//���Ӳ���Ϊ�ַ�����ֻ������һ��������Ԫ�صļ���["11"/"22"/"33"]����ȱʡֵ����ֵ���ڼ����У�����ȱʡֵ
	str_with_set_error,		//���Ӳ���Ϊ�ַ�����ֻ������һ��������Ԫ�صļ���["11"/"22"/"33"]����ȱʡֵ����ֵ���ڼ����У��򷵻ش���
	ipaddr_with_default,		//���Ӳ���ΪIP��ַ����ȱʡֵ������һ��u_int32
	ipaddr_with_error,		//���Ӳ���ΪIP��ַ����ȱʡֵ�����ش���
	tmax					//���ֵ�����Ƴ���
};

/* ---------------------------------------------------------------
	 �������������Ҫ�Ķ���
	 constȫ�ֱ���/staticȫ�ֱ���(����)/define/class/struct/enum/enum class/union��
   ---------------------------------------------------------------- */
//const int INF = 0x3f3f3f3f;
//const int NOT_NUM = 0x7f7f7f7f;
//const int OUT_RANGE = 0x5f5f5f5f;
const int INT_MIN_DEF = -1;
const int INT_MAX_DEF = 1;
const unsigned int IP_DEF_UINT = 3232256230; // 192.168.80.230 ��Ӧ������ֵ
const string type_name[] = { 
	"null",
	"Bool",
	"IntWithDefault",
	"IntWithError",
	"IntSETWithDefault",	
	"IntSETWithError",
	"String",
	"StringSETWithDefault",
	"StringSETWithError",
	"IPAddrWithDefault",
	"IPAddrWithError" ,
	"tmax"
};
const string args_parm_name[] = { 
	"null",
	"bool",
	"int",
	"int",
	"int",			
	"int",
	"string",
	"string",
	"string",				
	"IP��ַ",
	"IP��ַ" 
};
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
	int* extargs_int_set;		//int�Ͷ�������ļ��ϣ���ʾ��ֻ��һ��ָ��Ŷ��

	string  extargs_string_default;	//string�Ͷ��������ȱʡֵ(��ipaddr)
	string* extargs_string_set;		//string�Ͷ�������ļ��ϣ���ʾ��ֻ��һ��ָ��Ŷ��

	unsigned int   extargs_ipaddr_default;		//IP��ַȱʡֵ

	/* ������Щ�Ǳ��� */
	int    args_existed;				//�������Ƿ���ֹ�����ֹ��ͬ���� -n ** -n ** �ظ����֣�
	int    extargs_int_value;			//int�Ͷ������������ֵ
	string extargs_string_value;		//string�Ͷ������������ֵ
	unsigned int extargs_ipaddr_value;	//IP��ַ�������������ֵ��IP��ַ���ڲ��洢Ϊ����ʽ���ַ�����ʽ��Ҫת����

	/* ---------------------------------------------------------------
		 �������������Ҫ�Ķ��壨�ڲ��ã�
		   1��Ϊ����lib���е�class��ͬ���������������68�ֽڳ�Ա
		   2�������Ҫ�Զ������ݳ�Ա������Ӧ�ۼ�pad����Ĵ�С��ά���ܴ�С200�ֽڲ���
	   ---------------------------------------------------------------- */
	/* ˵����ǰ������ʲô���Ӷ����ں���������Ϊbool,intran,intset,str,strset,ip */
	bool is_bool, is_intran, is_intset, is_str, is_strset, is_ip; // �������ֽڶ���
	/* ��ͬ���͵Ĳ��������󷨲�ͳһ�������ڳ�ʼ��ʱ��� */
	int def_len, val_len; 
	char pad[52]; 

public:
	args_analyse_tools();
	args_analyse_tools(const char* arg_name, const ST_EXTARGS_TYPE type, const int ext_num, const bool def);
	args_analyse_tools(const char* arg_name, const ST_EXTARGS_TYPE type, const int ext_num, const int def, const int _min, const int _max);
	args_analyse_tools(const char* arg_name, const ST_EXTARGS_TYPE type, const int ext_num, const int def_of_set_pos, const int* const set);
	args_analyse_tools(const char* arg_name, const ST_EXTARGS_TYPE type, const int ext_num, const string def);
	args_analyse_tools(const char* arg_name, const ST_EXTARGS_TYPE type, const int ext_num, const int def_of_set_pos, const string* const set);

	~args_analyse_tools();

	/* ��ȡ���� */
	const string get_name() const;		//����ĳ����������ƣ����� "--help"��
	const int    existed() const;			//�ж�ĳ�������Ƿ����
	const int    get_int() const;			//����ĳ�������ֵ��int�ͣ�
	const string get_string() const;		//����ĳ�������ֵ��string�ͣ�
	const unsigned int get_ipaddr() const;	//����ĳ�������ֵ��IP��ַ����"127.0.0.1"Ϊ��������u_int32�͵� 0x7f000001��
	const string get_str_ipaddr() const;	//����ĳ�������ֵ��IP��ַ����"127.0.0.1"Ϊ���������ַ�����ʽ��"127.0.0.1"��

    /* �Բ������з���������0/-1 */
	friend int args_analyse_process(const int argc, const char* const *const argv, args_analyse_tools* const args, const int follow_up_args);
	/* ��ӡ������Ľ�� */
	friend int args_analyse_print(const args_analyse_tools*const args);

	/* ---------------------------------------------------------------
		 ���������������Ҫ�Ķ��壨���ⲻ���֣�
	   ---------------------------------------------------------------- */
private:
	int  get_ranset_length() const;
};

int args_analyse_process(const int argc, const char* const *const argv, args_analyse_tools* const args, const int follow_up_args);
int args_analyse_print(const args_analyse_tools* const args);

#endif  // !ENABLE_LIB_COMMON_TOOLS
