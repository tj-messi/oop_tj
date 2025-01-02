/* ѧ�� ���� �༶ */
#include <iostream>
//�ɸ�����Ҫ�ټ���������Ҫ��ͷ�ļ�
#include "../include/class_aat.h"
using namespace std;

#define	SRC_DST_IS_FIXED_ARGS		1		//1-ת��ǰ����ļ����ǹ̶�������0-ת��ǰ����ļ����ǿɱ����

/* enum��˳��Ҫ��args������˳�򱣳�һ��
   ����enum class ֻ�ǲ���ÿ�ζ���ǿ��ת�� */
enum OPT_ARGS {
	ARGS_HELP = 0,
	ARGS_CONVERT,
#if	!SRC_DST_IS_FIXED_ARGS
	ARGS_SRCFILE,
	ARGS_DSTFILE,
#endif
	ARGS_MAX	//���ڿ���enum���޵����ֵ�������� if (enum_value < ARGS_MAX) ����ʱʹ��
};

/* ���������������������Ҳ���Խ��Զ��庯����������cpp�� */

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ������һ�룬ΪʲôҪ�� static����Ȼֻ��һ��cpp�������ǹ���ϰ�ߣ�
***************************************************************************/
static void usage(const char* const fullpath_procname)
{
	/* �����п��ö���*/
	const char* procname = strrchr(fullpath_procname, '\\');
	if (procname == NULL)
		procname = fullpath_procname;
	else
		procname++;

	cout << endl;
#if SRC_DST_IS_FIXED_ARGS
	cout << "Usage: " << procname << " [--help] | [--convert wtol | ltow] src_filename dst_filename" << endl;
	cout << endl;

	cout << "ѡ��:" << endl;
	cout << "    --help\t\t����������Ϣ" << endl;
	cout << "    --convert\t\t����ת����ʽ" << endl;
	cout << "    \twtol : Windows��ʽתΪLinux" << endl;
	cout << "    \tltow : Linux��ʽתΪWindows" << endl;
	cout << endl;
	cout << "ʾ��:" << endl;
	cout << "    " << procname << " --help" << endl;
	cout << "    " << procname << " a.txt b.txt                : ��Windows��ʽ��a.txtתΪLinux��ʽ��b.txt" << endl;
	cout << "    " << procname << " --convert wtol a.txt b.txt : ��Windows��ʽ��a.txtתΪLinux��ʽ��b.txt" << endl;
	cout << "    " << procname << " --convert ltow c.txt d.txt : ��Linux��ʽ��c.txtתΪWindows��ʽ��d.txt" << endl;
	cout << endl;
#else
	cout << "Usage: " << procname << " [--help] | [--convert wtol | ltow] [--srcfile xxx] [--dstfile xxx]" << endl;
	cout << endl;

	cout << "ѡ��:" << endl;
	cout << "    --help\t\t����������Ϣ" << endl;
	cout << "    --convert\t\t����ת����ʽ" << endl;
	cout << "    \twtol : Windows��ʽתΪLinux" << endl;
	cout << "    \tltow : Linux��ʽתΪWindows" << endl;
	cout << "    --srcfile\t\t����Դ�ļ���" << endl;
	cout << "    --dstfile\t\t����Ŀ���ļ���" << endl;
	cout << endl;
	cout << "ʾ��:" << endl;
	cout << "    " << procname << " --help" << endl;
	cout << "    " << procname << " --srcfile a.txt --dstfile b.txt                 : ��Windows��ʽ��a.txtתΪLinux��ʽ��b.txt" << endl;
	cout << "    " << procname << " --dstfile b.txt --srcfile a.txt                 : ��Windows��ʽ��a.txtתΪLinux��ʽ��b.txt" << endl;
	cout << "    " << procname << " --convert wtol --srcfile a.txt --dstfile b.txt  : ��Windows��ʽ��a.txtתΪLinux��ʽ��b.txt" << endl;
	cout << "    " << procname << "  --dstfile b.txt --convert ltow --srcfile a.txt : ��Linux��ʽ��a.txtתΪWindows��ʽ��b.txt" << endl;
	cout << endl;
#endif
}

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

	/* ת����ʽ�������� */
	string convert_type[] = { "wtol","ltow", "" };	//��β������""

#if SRC_DST_IS_FIXED_ARGS //������������Ĵ��룬--convert�ǿ�ѡ�������������������Դ�ļ�����Ŀ���ļ�������˳�򲻵ý���
	args_analyse_tools args[] = {
		args_analyse_tools("--help",    ST_EXTARGS_TYPE::boolean,          0, false), //Ĭ��false
		args_analyse_tools("--convert", ST_EXTARGS_TYPE::str_with_set_default, 1, 0, convert_type),	//����0����defaultΪset�еĵ�[0]��ֵ����wtol��ȱʡ0
		args_analyse_tools()  //���һ�������ڽ���
	};

	/* �����κβ��������⴦����ӡ��ʾ��Ϣ����� */
	if (argc == 1) {
		usage(argv[0]);
		return -1;
	}

	int need_fixed_args = 1;	//��Ҫ�̶�����
	int cur_argc;

	/* ���һ��������1 - ��ʾ��ѡ������⣬����Ҫ��������
					  ��1��Windows/Linux�µ�ping���ping IP��ַ��������������ʽ�����⻹�кܶ�-/--��ͷ�Ŀ�ѡ����
						  ping 192.168.80.230
						  ping -t -n 10 192.168.80.230
					 ��2��Linux�µ�c++���c++ Դ�����ļ�����������������ʽ�����⻹�кܶ�-/--��ͷ�Ŀ�ѡ����
						  c++ test.cpp
						  c++ -Wall -o test test.cpp
				  0 - ��ʾ��ѡ������⣬����Ҫ��������
		��������ֵ��-1 - ��������д�
					>0 - �ɱ����������ɺ󣬵�ǰͣ��argv[]�ĵڼ����±�λ�ã�������滹��argv[]�����ʾ�̶�����
	*/
	if ((cur_argc = args_analyse_process(argc, argv, args, need_fixed_args)) < 0)
	{
		//������Ϣ�ں������Ѵ�ӡ
		return -1;
	}

	/* ��--help���������⴦����ӡ��ʾ��Ϣ����� */
	if (args[ARGS_HELP].existed()) {
		usage(argv[0]);
		return -1;
	}

	/* �ɱ����������ɺ󣬿��Ƿ��й̶��������Լ��̶������������Ƿ����Ҫ�� */
	if (need_fixed_args) {
		if (cur_argc == argc) {  //˵������û�и���Ҫ�Ĺ̶�����
			cout << "��Ҫָ��IP��ַ����δ����" << endl;
			return -1;
		}
		if (argc - cur_argc != 2) {
			cout << "���ɱ�����⣬�������ת����Դ�ļ�����Ŀ���ļ��������̶�������������ֻ������" << argc - cur_argc << "���̶�����" << endl;
			return -1;
		}
	}

	/* ��ӡ���������Ľ�� */
	cout << "�ɱ�����б�:" << endl;
	args_analyse_print(args);

	/* ��ӡ������ֵ */
	cout << "�������ͨ��" << endl;
	cout << " --convert������" << args[ARGS_CONVERT].get_string() << endl;
	cout << " Դ�ļ�����   ��" << argv[cur_argc] << endl;
	cout << " Ŀ���ļ����� ��" << argv[cur_argc+1] << endl;

	/* �˴�Ӧ����������ʵ�֣����ⲻ��Ҫ�� */

#else //--convert/--srcfile/--dstfile��Ϊ��ѡ�������໥λ�����⣬ͨ���ж�--srcfile/--dstfile�Ƿ������ǿ��Ҫ�������������������
	args_analyse_tools args[] = {
		args_analyse_tools("--help",    ST_EXTARGS_TYPE::boolean,            0, false), //Ĭ��false
		args_analyse_tools("--convert", ST_EXTARGS_TYPE::str_with_set_error, 1, 0, convert_type),	//�������wtol/ltow�򱨴�
		args_analyse_tools("--srcfile", ST_EXTARGS_TYPE::str,                1, string("")),	
		args_analyse_tools("--dstfile", ST_EXTARGS_TYPE::str,                1, string("")),
		args_analyse_tools()  //���һ�������ڽ���
	};

	/* �����κβ��������⴦����ӡ��ʾ��Ϣ����� */
	if (argc == 1) {
		usage(argv[0]);
		return -1;
	}

	int need_fixed_args = 0;	//��Ҫ�̶�����
	int cur_argc;

	/* ���һ��������1 - ��ʾ��ѡ������⣬����Ҫ��������
					  ��1��Windows/Linux�µ�ping���ping IP��ַ��������������ʽ�����⻹�кܶ�-/--��ͷ�Ŀ�ѡ����
						  ping 192.168.80.230
						  ping -t -n 10 192.168.80.230
					 ��2��Linux�µ�c++���c++ Դ�����ļ�����������������ʽ�����⻹�кܶ�-/--��ͷ�Ŀ�ѡ����
						  c++ test.cpp
						  c++ -Wall -o test test.cpp
				  0 - ��ʾ��ѡ������⣬����Ҫ��������
		��������ֵ��-1 - ��������д�
					>0 - �ɱ����������ɺ󣬵�ǰͣ��argv[]�ĵڼ����±�λ�ã�������滹��argv[]�����ʾ�̶�����
	*/
	if ((cur_argc = args_analyse_process(argc, argv, args, need_fixed_args)) < 0)
	{
		//������Ϣ�ں������Ѵ�ӡ
		return -1;
	}

	/* ��--help���������⴦����ӡ��ʾ��Ϣ����� */
	if (args[ARGS_HELP].existed()) {
		usage(argv[0]);
		return -1;
	}

	/* ����ͬʱָ�� --srcfile �� --dstfile�����򱨴� */
	if (args[ARGS_SRCFILE].existed() + args[ARGS_DSTFILE].existed() != 2) {
		cout << "����ָ��Դ�ļ���(--srcfile)��Ŀ���ļ���(--dstfile)��λ�ü�˳������" << endl;
		usage(argv[0]);
		return -1;
	}

	/* ��ӡ���������Ľ�� */
	cout << "�ɱ�����б�:" << endl;
	args_analyse_print(args);

	/* ��ӡ������ֵ */
	cout << "�������ͨ��" << endl;
	cout << " --convert������" << args[ARGS_CONVERT].get_string() << endl;
	cout << " Դ�ļ�����   ��" << args[ARGS_SRCFILE].get_string() << endl;
	cout << " Ŀ���ļ����� ��" << args[ARGS_DSTFILE].get_string() << endl;

	/* �˴�Ӧ����������ʵ�֣����ⲻ��Ҫ�� */

#endif

	return 0;
}
