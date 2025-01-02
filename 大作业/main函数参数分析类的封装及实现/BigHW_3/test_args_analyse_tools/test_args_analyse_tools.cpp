/* ѧ�� ���� �༶ */
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "../include/class_aat.h"
using namespace std;

enum OPT_ARGS {
	ARGS_HELP,
	ARGS_BOOL,
	ARGS_INT_DEF,
	ARGS_INT_ERR,
	ARGS_INTSET_DEF,
	ARGS_INTSET_ERR,
	ARGS_DOUBLE_DEF,
	ARGS_DOUBLE_ERR,
	ARGS_DOUBLESET_DEF,
	ARGS_DOUBLESET_ERR,
	ARGS_STR1,
	ARGS_STR2,
	ARGS_STRSET_DEF,
	ARGS_STRSET_ERR,
	ARGS_IPADDR_DEF,
	ARGS_IPADDR_ERR
};

/***************************************************************************
  �������ƣ�
  ��    �ܣ���������
  ���������
  �� �� ֵ��
  ˵    ���������и�ʽҪ����--��ʼ�Ŀɱ������˳�����⣬�����ָ���Ĺ̶�����
***************************************************************************/
int main(int argc, char* argv[])
{
	/* ��Ϊ������ lib_common_tools.lib���˴��ȼ���С�Ƿ����Ҫ�� */
	if (sizeof(args_analyse_tools) != 240) {
		cout << "class args_analyse_tools ����240�ֽڣ����ʹ�� lib_common_tools.lib �еĺ�������ܳ���" << endl;
		return -1;
	}

	string hashtype[] = { "md5","sha1","sha224","sha256","sha384","sha512","all", "" };	//��β������""
	int intset[] = { 11, 22, 33, 123, 345, INVALID_INT_VALUE_OF_SET }; 				//��β������INVALID_INT_VALUE_OF_SET
	double doubleset[] = { 1.1, 2.2, 3.3, 12.3, 3.45, INVALID_DOUBLE_VALUE_OF_SET }; 				//��β������INVALID_INT_VALUE_OF_SET

	args_analyse_tools args[] = {
		args_analyse_tools("--help",      ST_EXTARGS_TYPE::boolean, 0, false),
		args_analyse_tools("--bool",      ST_EXTARGS_TYPE::boolean, 0, true),
		args_analyse_tools("--intdef",    ST_EXTARGS_TYPE::int_with_default,        1, 12345, 0, 65535),
		args_analyse_tools("--interr",    ST_EXTARGS_TYPE::int_with_error,          1, 12345, 0, 65535),	//����12345��Ϊ�κ�ֵ��������
		args_analyse_tools("--intsetdef", ST_EXTARGS_TYPE::int_with_set_default,    1, 2, intset),		//����2����defaultΪset�еĵ�[2]��ֵ����33�������ֵ����Χ��ȱʡ0
		args_analyse_tools("--intseterr", ST_EXTARGS_TYPE::int_with_set_error,      1, 2, intset),		//����2�����壬����
		args_analyse_tools("--doubledef",		ST_EXTARGS_TYPE::double_with_default,		1, 1.23, -2.5, 99.9),
		args_analyse_tools("--doubleerr",		ST_EXTARGS_TYPE::double_with_error,		1, 1.23, -2.5, 99.9),	//����12345��Ϊ�κ�ֵ��������
		args_analyse_tools("--doublesetdef",	ST_EXTARGS_TYPE::double_with_set_default,	1, 2, doubleset),		//����2����defaultΪset�еĵ�[2]��ֵ����33�������ֵ����Χ��ȱʡ0
		args_analyse_tools("--doubleseterr",	ST_EXTARGS_TYPE::double_with_set_error,	1, 2, doubleset),		//����2�����壬����
		args_analyse_tools("--str1",      ST_EXTARGS_TYPE::str,                  1, string("")),		//�����string()���������䵽args_analyse(const char *arg_name, enum ST_EXTARGS_TYPE type, int ext_num, bool def)
		args_analyse_tools("--str2",      ST_EXTARGS_TYPE::str,                  1, string("Hello")),	//�����string()���������䵽args_analyse(const char *arg_name, enum ST_EXTARGS_TYPE type, int ext_num, bool def)
		args_analyse_tools("--strsetdef", ST_EXTARGS_TYPE::str_with_set_default, 1, 3, hashtype),		//����3����defaultΪset�еĵ�[3]��ֵ����sha256�������ֵ����Χ��ȱʡ0
		args_analyse_tools("--strseterr", ST_EXTARGS_TYPE::str_with_set_error,   1, 3, hashtype),		//����3�����壬����
		args_analyse_tools("--ipdef",     ST_EXTARGS_TYPE::ipaddr_with_default,     1, string("192.168.80.230")),
		args_analyse_tools("--iperr",     ST_EXTARGS_TYPE::ipaddr_with_error,       1, string("")), //�ձ�ʾ0.0.0.0
		args_analyse_tools()  //���һ�������ڽ���
	};

	int need_fixed_args = 0;	//���Ը�Ϊ1
	int cur_argc;

	/* ���һ��������1 - ��ʾ��ѡ������⣬����Ҫ��������
					  ��1��Windows/Linux�µ�ping���ping IP��ַ��������������ʽ�����⻹�кܶ�-/--��ͷ�Ŀ�ѡ����
						  ping 192.168.80.230
						  ping -t -n 10 192.168.80.230
					 ��2��Linux�µ�c++���c++ Դ�����ļ�����������������ʽ�����⻹�кܶ�-/--��ͷ�Ŀ�ѡ����
						  c++ test.cpp
						  c++ -Wall -o test test.cpp
				  0 - ��ʾ��ѡ������⣬����Ҫ�������� */
	if ((cur_argc = args_analyse_process(argc, argv, args, need_fixed_args)) < 0)
	{
		//������Ϣ�ں������Ѵ�ӡ
		return -1;
	}

	/* ����������ɺ�Ĵ����� */
	if (need_fixed_args) {
		if (cur_argc == argc) {  //˵������û�и���Ҫ�Ĺ̶�����
			cout << "ָ����Ҫ�̶���������δ����" << endl;
			return -1;
		}

		/* �˴�Ӧ�ô���Ҫ��Ĺ̶������������м򵥴�ӡ���� */
		cout << "����" << argc - cur_argc << "���̶�����������ĳ��������Ӧ�Ķ����ɾ�������������������" << endl;
		for (int i = cur_argc; i < argc; i++)
			cout << argv[i] << endl;
	}

	/* ��ӡһЩ��ʾ��Ϣ */
	cout << endl << "������۲��ӡ����У���Ӧ���exist�Ƿ�Ϊ1��ֵ�Ƿ�ΪԤ��" << endl << endl;

	cout << "�鿴default��error����ķ�����" << endl;
	cout << "  ��������ָ����Χ�ڵ�ֵ���ῴ�����" << endl;
	cout << "  ����--intdef 100000" << endl;
	cout << "      --interr 100000" << endl;
	cout << endl;

	/* ��ӡ�����ķ������ */
	args_analyse_print(args);

	/* �����һ���о���Ҫ���Ӧ�ó�����ִ�е��˴�������������ɣ�����ʵ����幦�ܵĽ׶� */

	/* ��ӡ�����в����Ŀ���ֵ */
	const int w1 = 16, w2 = 24, w3 = 20, w4 = 20;
	/* ��ӡ���⼰���� */
	cout << setw(w1 + w2 + w3 + w4) << setfill('=') << '=' << setfill(' ') << endl;
	cout << setw(w1) << "������" << setw(w2) << "�����Ƿ��������������" << setw(w3) << "ֵ1" << setw(w4) << "ֵ2" << endl;
	cout << setw(w1 + w2 + w3 + w4) << setfill('=') << '=' << setfill(' ') << endl;

	/* --------------------------------------------------------------
		ע�⣺����һ��Ҫ���ֿ�ִ���ļ��������еĲ�����ֵ���ܱ�ʹ��
		      ����ò����ֲ�����ֵ����ȡȱʡֵ
		���磺ping�����ʵ�֣������²�����
				args_analyse_tools("--n", ST_EXTARGS_TYPE::int_with_default, 1, 10, 1, 65535),
			  ��ping 10.80.42.230��--n��ֵ��get_int()��ȡ��10����ȱʡֵ
			    ping -n 15 10.80.42.230��--n��ֵ��get_int()��ȡ��15
				ping -n 100000 10.80.42.230��--n��ֵ��get_int()��ȡ��10����ȱʡֵ
	   --------------------------------------------------------------*/

	cout << setw(w1) << args[ARGS_BOOL].get_name() << setw(w2) << args[ARGS_BOOL].existed() << (args[ARGS_BOOL].existed() ? "True" : "False") << endl; //bool�ͣ�ֻҪexisted������Ϊ��true��û�е�����get_bool()����

	cout << setw(w1) << args[ARGS_INT_DEF].get_name() << setw(w2) << args[ARGS_INT_DEF].existed() << setw(w3) << args[ARGS_INT_DEF].get_int() << endl;
	cout << setw(w1) << args[ARGS_INT_ERR].get_name() << setw(w2) << args[ARGS_INT_ERR].existed() << setw(w3) << args[ARGS_INT_ERR].get_int() << endl;
	cout << setw(w1) << args[ARGS_INTSET_DEF].get_name() << setw(w2) << args[ARGS_INTSET_DEF].existed() << setw(w3) << args[ARGS_INTSET_DEF].get_int() << endl;
	cout << setw(w1) << args[ARGS_INTSET_ERR].get_name() << setw(w2) << args[ARGS_INTSET_ERR].existed() << setw(w3) << args[ARGS_INTSET_ERR].get_int() << endl;

	cout << setw(w1) << args[ARGS_DOUBLE_DEF].get_name() << setw(w2) << args[ARGS_DOUBLE_DEF].existed() << setw(w3) << args[ARGS_DOUBLE_DEF].get_double() << endl;
	cout << setw(w1) << args[ARGS_DOUBLE_ERR].get_name() << setw(w2) << args[ARGS_DOUBLE_ERR].existed() << setw(w3) << args[ARGS_DOUBLE_ERR].get_double() << endl;
	cout << setw(w1) << args[ARGS_DOUBLESET_DEF].get_name() << setw(w2) << args[ARGS_DOUBLESET_DEF].existed() << setw(w3) << args[ARGS_DOUBLESET_DEF].get_double() << endl;
	cout << setw(w1) << args[ARGS_DOUBLESET_ERR].get_name() << setw(w2) << args[ARGS_DOUBLESET_ERR].existed() << setw(w3) << args[ARGS_DOUBLESET_ERR].get_double() << endl;

	/* Ĭ��ֵΪ�յ������Ϊ�˿��������ӡ<NULL> */
	cout << setw(w1) << args[ARGS_STR1].get_name() << setw(w2) << args[ARGS_STR1].existed() << setw(w3) << (args[ARGS_STR1].get_string().empty() ? "<NULL>" : args[ARGS_STR1].get_string()) << endl;
	cout << setw(w1) << args[ARGS_STR2].get_name() << setw(w2) << args[ARGS_STR2].existed() << setw(w3) << args[ARGS_STR2].get_string() << endl;

	cout << setw(w1) << args[ARGS_STRSET_DEF].get_name() << setw(w2) << args[ARGS_STRSET_DEF].existed() << setw(w3) << args[ARGS_STRSET_DEF].get_string() << endl;
	cout << setw(w1) << args[ARGS_STRSET_ERR].get_name() << setw(w2) << args[ARGS_STRSET_ERR].existed() << setw(w3) << args[ARGS_STRSET_ERR].get_string() << endl;

	/* u_int��ʽ��IP��ַ����hex��ӡ����ӡ��ɺ���תΪdec */
	cout << setw(w1) << args[ARGS_IPADDR_DEF].get_name() << setw(w2) << args[ARGS_IPADDR_DEF].existed() << setw(w3) << hex << args[ARGS_IPADDR_DEF].get_ipaddr() << dec << setw(w4) << args[ARGS_IPADDR_DEF].get_str_ipaddr() << endl;
	cout << setw(w1) << args[ARGS_IPADDR_ERR].get_name() << setw(w2) << args[ARGS_IPADDR_ERR].existed() << setw(w3) << hex << args[ARGS_IPADDR_ERR].get_ipaddr() << dec << setw(w4) << args[ARGS_IPADDR_ERR].get_str_ipaddr() << endl;

	/* ��ӡ���� */
	cout << setw(w1 + w2 + w3 + w4) << setfill('=') << '=' << setfill(' ') << endl;

	return 0;
}

#if 0
// ��������

test_args_analyse_tools --help

test_args_analyse_tools --bool	//ֵΪtrue

test_args_analyse_tools --intdef 123				//ֵ123
test_args_analyse_tools --intdef 123 --intdef 456	//�����ظ�
test_args_analyse_tools --intdef -12				//Ĭ��ֵ12345
test_args_analyse_tools --intdef 654321				//Ĭ��ֵ12345

test_args_analyse_tools --interr 123				//ֵ123
test_args_analyse_tools --interr 123 --interr 456	//�����ظ�
test_args_analyse_tools --interr -12				//����ֵ�Ƿ�
test_args_analyse_tools --interr 654321				//����ֵ�Ƿ�

test_args_analyse_tools --intsetdef 11					//ֵ11
test_args_analyse_tools --intsetdef 12					//Ĭ��ֵ33
test_args_analyse_tools --intsetdef 11 --intsetdef 22	//�����ظ�

test_args_analyse_tools --intseterr 11					//ֵ11
test_args_analyse_tools --intseterr 12					//����ֵ�Ƿ�
test_args_analyse_tools --intseterr 11 --intseterr 22	//�����ظ�

test_args_analyse_tools --doubledef 2.34					//ֵ2.34
test_args_analyse_tools --doubledef 2.34 --doubledef 4.32	//�����ظ�
test_args_analyse_tools --doubledef -3						//Ĭ��ֵ1.23����ΪVS���Զ�������ʽ�����- 3��ɾ��֮��Ŀո�
test_args_analyse_tools --doubledef 101.234					//Ĭ��ֵ1.23

test_args_analyse_tools --doubleerr 2.34					//ֵ2.34
test_args_analyse_tools --doubleerr 2.34 --doubledef 4.32	//�����ظ�
test_args_analyse_tools --doubleerr -3						//����ֵ�Ƿ�����ΪVS���Զ�������ʽ�����- 3��ɾ��֮��Ŀո�
test_args_analyse_tools --doubleerr 101.234					//����ֵ�Ƿ�

test_args_analyse_tools --doublesetdef 12.3						//ֵ12.3
test_args_analyse_tools --doublesetdef 5.6						//Ĭ��ֵ3.3
test_args_analyse_tools --doublesetdef 1.1 --doublesetdef 2.2	//�����ظ�

test_args_analyse_tools --doubleseterr 12.3						//ֵ12.3
test_args_analyse_tools --doubleseterr 5.6						//����ֵ�Ƿ�
test_args_analyse_tools --doubleseterr 1.1 --doubleseterr 2.2	//�����ظ�

test_args_analyse_tools --str1 hello				//ֵhello
test_args_analyse_tools --str1 hello --str1 horse	//�����ظ�

test_args_analyse_tools --str2 hello				//ֵhello
test_args_analyse_tools --str2 hello --str2 horse	//�����ظ�

test_args_analyse_tools --strsetdef md5						//ֵmd5
test_args_analyse_tools --strsetdef md4						//ֵsha256
test_args_analyse_tools --strsetdef md5 --strsetdef sha1	//����:�ظ�

test_args_analyse_tools --strseterr md5						//ֵmd5
test_args_analyse_tools --strseterr md4						//����ֵ�Ƿ�
test_args_analyse_tools --strseterr md5 --strseterr sha1	//����:�ظ�

test_args_analyse_tools --ipdef 1.1.1.1						//ֵ1.1.1.1
test_args_analyse_tools --ipdef 1.1.1.1234					//ֵ192.168.80.230
test_args_analyse_tools --ipdef 1.1.1.1 --ipdef 2.2.2.2		//�����ظ�

test_args_analyse_tools --iperr 1.1.1.1						//ֵ1.1.1.1
test_args_analyse_tools --iperr 1.1.1.1234					//����ֵ�Ƿ�
test_args_analyse_tools --iperr 1.1.1.1 --iperr 2.2.2.2		//�����ظ�

//������������������ϣ�
#endif
