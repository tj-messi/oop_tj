/* 2150792 �ƿ� ţ»�� */
#define _CRT_SECURE_NO_WARNINGS
#include "hw_check.h"
#include "../include/class_aat.h"

using namespace std;

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����
 ***************************************************************************/
static void usage(const char* const full_procname)
{
	const char *procname = strrchr(full_procname, '\\');
	if (procname == NULL)
		procname = full_procname;

	const int wkey = 7 + strlen(procname) + 1;
	const int wopt = 7 + strlen(procname) + 4;
	cout << endl;

	cout << "Usage: " << procname << " ��ѡ��/��ѡ��" << endl;
	cout << endl;
	cout << setw(wkey) << ' ' << "��ѡ�ָ������" << endl;
	cout << setw(wopt) << ' ' << "--action opname : ֧�ֵ�opname����" << endl;
	cout << setw(wopt) << ' ' << "\t base              : �������(�ļ��Ƿ��ύ���Ƿ񱻸Ķ��������Ƿ���ȷ)" << endl;
	cout << setw(wopt) << ' ' << "\t firstline         : ���м�飨��Դ�����ļ���Ҫ��" << endl;
	cout << setw(wopt) << ' ' << "\t secondline        : ���м�飨������Դ�����ļ���Ҫ��" << endl;

	cout << setw(wkey) << ' ' << "��ѡ�ָ���κ�" << endl;
	cout << setw(wopt) << ' ' << "--cno course_no     : �κ�" << endl;

	cout << setw(wkey) << ' ' << "��ѡ�ָ��ѧ��" << endl;
	cout << setw(wopt) << ' ' << "--stu no/all        : ָ������/ȫ��(7λ����Ϊѧ��,allΪȫ��)" << endl;

	cout << setw(wkey) << ' ' << "��ѡ�ָ���ļ�" << endl;
	cout << setw(wopt) << ' ' << "--file filename/all : �����ļ���/ȫ��(allΪȫ��,����Ϊ�����ļ���)" << endl;

	cout << setw(wkey) << ' ' << "��ѡ�" << endl;
	cout << setw(wopt) << ' ' << "--chapter n         : ��--file�Ļ������ٽ����½ڵ�ɸѡ(��/-1��ȫ���½�,����--week����)" << endl;
	cout << setw(wopt) << ' ' << "--week n            : ��--file�Ļ������ٽ����ܴε�ɸѡ(��/-1��ȫ���ܴ�,����--chapter����)" << endl;
	cout << setw(wopt) << ' ' << "--display xxxxx     : ÿλ0/1�ֱ��ʾ������Ϣ/δ�ύ��Ϣ/������Ϣ/������Ϣ/���ش�����Ϣ" << endl;
	cout << setw(wopt) << ' ' << "--cfgfile filename  : ָ�������ļ���(ȱʡ:hw_check.conf)" << endl;
	cout << endl;

	const char* DEMO_CNO = "10108001";
	const char* DEMO_SRC_FNAME = "12-b1.cpp";
	const char* DEMO_STUNO = "2259999";

	cout << "e.g.   " << procname << " --action base --cno " << DEMO_CNO << " --stu all --file all             : ���" << DEMO_CNO << "����ѧ����������ҵ�Ļ�����Ϣ" << endl;
	cout << "       " << procname << " --action base --cno " << DEMO_CNO << " --stu all --file all --chapter 4 : ���" << DEMO_CNO << "����ѧ���ĵ�4����ҵ�Ļ�����Ϣ" << endl;
	cout << "       " << procname << " --action base --cno " << DEMO_CNO << " --stu all --file all --week 6    : ���" << DEMO_CNO << "����ѧ���ĵ�6����ҵ�Ļ�����Ϣ" << endl;
	cout << "       " << procname << " --action base --cno " << DEMO_CNO << " --stu " << DEMO_STUNO << " --file all         : ���" << DEMO_CNO << "��" << DEMO_STUNO << "ѧ����������ҵ�Ļ�����Ϣ" << endl;
	cout << "       " << procname << " --action base --cno " << DEMO_CNO << " --stu " << DEMO_STUNO << " --file " << DEMO_SRC_FNAME << "   : ���" << DEMO_CNO << "��" << DEMO_STUNO << "ѧ����" << DEMO_SRC_FNAME << "��ҵ�Ļ�����Ϣ" << endl;
	cout << endl;

	cout << "       " << procname << " --action firstline --cno " << DEMO_CNO << " --stu all --file all             : ���" << DEMO_CNO << "����ѧ����������ҵ��������Ϣ" << endl;
	cout << "       " << procname << " --action firstline --cno " << DEMO_CNO << " --stu all --file all --chapter 4 : ���" << DEMO_CNO << "����ѧ���ĵ�4����ҵ��������Ϣ" << endl;
	cout << "       " << procname << " --action firstline --cno " << DEMO_CNO << " --stu all --file all --week 6    : ���" << DEMO_CNO << "����ѧ���ĵ�6����ҵ��������Ϣ" << endl;
	cout << "       " << procname << " --action firstline --cno " << DEMO_CNO << " --stu " << DEMO_STUNO << " --file all         : ���" << DEMO_CNO << "��" << DEMO_STUNO << "ѧ����������ҵ��������Ϣ" << endl;
	cout << "       " << procname << " --action firstline --cno " << DEMO_CNO << " --stu " << DEMO_STUNO << " --file " << DEMO_SRC_FNAME << "   : ���" << DEMO_CNO << "��" << DEMO_STUNO << "ѧ����" << DEMO_SRC_FNAME << "��ҵ��������Ϣ" << endl;
	cout << endl;

	cout << "       " << procname << " --action secondline --cno " << DEMO_CNO << " --stu all --file " << DEMO_SRC_FNAME << " : ���" << DEMO_CNO << "������ѧ����" << DEMO_SRC_FNAME << "��ҵ�Ĵ�����Ϣ" << endl;
	cout << endl;

	cout << "       " << procname << " --cfgfile E:\\test\\my.conf --action base --cno " << DEMO_CNO << " --stu all --file all : ���" << DEMO_CNO << "����ѧ����������ҵ�Ļ�����Ϣ(ָ�������ļ�)" << endl;
	cout << endl;


	cout << endl;
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����
 ***************************************************************************/
int main(int argc, char** argv)
{
	const string Action_Name[] = { "base","firstline","secondline","" }; //Ҳ���Ը�����Ҫ������ͷ�ļ����Ա㹲�� 

	args_analyse_tools args[] = {
		args_analyse_tools("--help",     ST_EXTARGS_TYPE::boolean,            0, false),
		args_analyse_tools("--debug",    ST_EXTARGS_TYPE::boolean,            0, false),
		args_analyse_tools("--action",   ST_EXTARGS_TYPE::str_with_set_error, 1, -1, Action_Name),	//����-1�����壬��ʾ��Ĭ�ϣ�����ָ��
		args_analyse_tools("--cno",      ST_EXTARGS_TYPE::str,                1, string("")),
		args_analyse_tools("--stu",      ST_EXTARGS_TYPE::str,                1, string("")),
		args_analyse_tools("--file",     ST_EXTARGS_TYPE::str,                1, string("")),
		args_analyse_tools("--chapter",  ST_EXTARGS_TYPE::int_with_error,     1, -1, -1, 99), //����-1��ʾ�������½�ѡ��
		args_analyse_tools("--week",     ST_EXTARGS_TYPE::int_with_error,     1, -1, -1, 20), //����-1��ʾ�������ܴ�ѡ��
		args_analyse_tools("--display",  ST_EXTARGS_TYPE::str,                1, string("11111")),
		args_analyse_tools("--cfgfile",  ST_EXTARGS_TYPE::str,                1, string("hw_check.conf")),
		args_analyse_tools()  //���һ�������ڽ���
	};

	int need_fixed_args = 0;	//���Ը�Ϊ1
	int cur_argc;
	
	if (argc == 1) {
		usage(argv[0]);
		return -1;
	}
	if ((cur_argc = args_analyse_process(argc, argv, args, need_fixed_args)) <= 0)
	{
		//������Ϣ�ں������Ѵ�ӡ
		return -1;
	}
	/* ��ӡ���������Ľ�� */
	
	/* ��--help���������⴦����ӡ��ʾ��Ϣ����� */
	if (args[OPT_ARGS_HELP].existed())
	{
		usage(argv[0]);
		return -1;
	}

	/* �жϱ�ѡ�� */
	if (!args[OPT_ARGS_ACTION].existed())
	{
		usage(argv[0]);
		cout << "����[" << args[OPT_ARGS_ACTION].get_name() << "]����ָ��." << endl;
		return -1;
	}
	if (!args[OPT_ARGS_CNO].existed())
	{
		usage(argv[0]);
		cout << "����[" << args[OPT_ARGS_CNO].get_name() << "]����ָ��." << endl;
		return -1;
	}
	if (!args[OPT_ARGS_STU].existed())
	{
		usage(argv[0]);
		cout << "����[" << args[OPT_ARGS_STU].get_name() << "]����ָ��." << endl;
		return -1;
	}
	if (!args[OPT_ARGS_FILE].existed())
	{
		usage(argv[0]);
		cout << "����[" << args[OPT_ARGS_FILE].get_name() << "]����ָ��." << endl;
		return -1;
	}
	/* secondline���� --file����all��--stu������all */
	if (args[OPT_ARGS_ACTION].get_string() == "secondline")
	{
		if (args[OPT_ARGS_FILE].get_string() == "all") 
		{
			cerr << "HW_Check_SecondLine ֻ����Ե��ļ�" << endl;
			return -1;
		}
		if (args[OPT_ARGS_STU].get_string() != "all") 
		{
			cerr << "HW_Check_SecondLine ֻ�����ȫ��ѧ��" << endl;
			return -1;
		}
	}
	if (args[OPT_ARGS_CHAPTER].existed() || args[OPT_ARGS_WEEK].existed()) 
	{
		if (args[OPT_ARGS_FILE].get_string() != "all") 
		{
			cerr << "����[--chapter/--week]���ܳ�����[--file �����ļ���]ʱ." << endl;
			return -1;
		}
	}
	hw_check hwcheck;
	/* ���cmd����������д��hwcheck�� */
	if (hwcheck.read_hwcheck_cmdpara(args) <= 0)
		return -1;
	/* ��ȡ�����ļ���Ϣ */
	if (!hwcheck.read_db_config(hwcheck.cfgfile))
		return -1;
	/* ��ȡ���ݿ���Ϣ */
	if (!hwcheck.read_db_content())
		return -1;
	/* ����base/firstline/secondline��� */
	hwcheck.hw_check_threeinone();
	
	return 0;
}

