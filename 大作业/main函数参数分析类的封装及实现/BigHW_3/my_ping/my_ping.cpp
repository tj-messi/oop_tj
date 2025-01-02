/* ѧ�� ���� �༶ */
#include <iostream>
//�ɸ�����Ҫ�ټ���������Ҫ��ͷ�ļ�
#include "../include/class_aat.h"
using namespace std;

#define	IPADDR_IS_FIXED_ARGS		1		//1 - IP��ַΪ�̶�������0 - IP��ַΪ�ɱ����

/* enum��˳��Ҫ��args������˳�򱣳�һ��
   ����enum class ֻ�ǲ���ÿ�ζ���ǿ��ת�� */
enum OPT_ARGS {
	ARGS_HELP = 0,
	ARGS_T,
	ARGS_N,
	ARGS_L,
#if	!IPADDR_IS_FIXED_ARGS
	ARGS_IPADDR,
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

	/* ע���ⲿ�ֱ�14-b4��Ҫ��ͣ���Ϊû������������Ӧ */
	cout << endl;
#if IPADDR_IS_FIXED_ARGS
	cout << "Usage: " << procname << " [--help] | [--t] [--n count] [--l size] IPaddress" << endl;
	cout << endl;

	cout << "ѡ��:" << endl;
	cout << "    --help\t\t����������Ϣ" << endl;
	cout << "    --t\t\t\t����Pingָ��������ֱ����Ctrl+Cֹͣ" << endl;
	cout << "    --n count\t\tָ��Ҫ���͵İ�����[1..1024]��Ĭ��4" << endl;
	cout << "    --l size\t\tָ�����ͻ������Ĵ�С[32..64000]��Ĭ��64" << endl;
	cout << endl;
	cout << "ʾ��:" << endl;
	cout << "    " << procname << " --help" << endl;
	cout << "    " << procname << " 192.168.80.230" << endl;
	cout << "    " << procname << " --t 192.168.80.230" << endl;
	cout << "    " << procname << " --l 2000 192.168.80.230" << endl;
	cout << "    " << procname << " --n 200 --l 1000 192.168.80.230" << endl;
	cout << "    " << procname << " --l 1000 --n 200 192.168.80.230" << endl;
	cout << "    " << procname << " --l 1000 --t 192.168.80.230" << endl;
	cout << "    " << procname << " --t --l 1000 --n 20 192.168.80.230" << endl;
	cout << endl;
#else
	cout << "Usage: " << procname << " [--help] | [--t] [--n count] [--l size] IPaddress" << endl;
	cout << endl;

	cout << "ѡ��:" << endl;
	cout << "    --help\t\t����������Ϣ" << endl;
	cout << "    --t\t\t\t����Pingָ��������ֱ����Ctrl+Cֹͣ" << endl;
	cout << "    --n count\t\tָ��Ҫ���͵İ�����[1..1024]��Ĭ��4" << endl;
	cout << "    --l size\t\tָ�����ͻ������Ĵ�С[32..64000]��Ĭ��64" << endl;
	cout << "    --ip x.x.x.x\tָ��IP��ַ(������������)" << endl;
	cout << endl;
	cout << "ʾ��:" << endl;
	cout << "    " << procname << " --help" << endl;
	cout << "    " << procname << " --ip 192.168.80.230" << endl;
	cout << "    " << procname << " --t --ip 192.168.80.230" << endl;
	cout << "    " << procname << " --l 2000 --ip 192.168.80.230" << endl;
	cout << "    " << procname << " --n 200 --l 1000 --ip 192.168.80.230" << endl;
	cout << "    " << procname << " --l 1000 --ip 192.168.80.230 --n 200 " << endl;
	cout << "    " << procname << " --ip 192.168.80.230 --l 1000 --t" << endl;
	cout << "    " << procname << " --t --l 1000 --n 20 --ip 192.168.80.230" << endl;
	cout << endl;
#endif
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ������һ�룬ΪʲôҪ�� static����Ȼֻ��һ��cpp�������ǹ���ϰ�ߣ�
***************************************************************************/
#if IPADDR_IS_FIXED_ARGS
static bool is_ipaddr_valid(const char* const ipstr)
{
	return true; //��������Ҫ����ʵ�֣�����ֵ�����޸�
}
#endif

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

#if IPADDR_IS_FIXED_ARGS //������������Ĵ��룬--t/--n/--l�ǿ�ѡ��������������һ���̶���IP��ַ
	args_analyse_tools args[] = {
		args_analyse_tools("--help", ST_EXTARGS_TYPE::boolean,          0, false), //Ĭ��false
		args_analyse_tools("--t",    ST_EXTARGS_TYPE::boolean,          0, false), //Ĭ��false
		args_analyse_tools("--n",    ST_EXTARGS_TYPE::int_with_default, 1, 4, 1, 1024), //[1..1024]��Ĭ��4
		args_analyse_tools("--l",    ST_EXTARGS_TYPE::int_with_default, 1, 64, 32, 64000), //[32..64000]��Ĭ��64
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
		if (argc - cur_argc > 1) {
			cout << "���ɱ�����⣬��������" << argc - cur_argc << "���̶���������������ֻ��Ҫһ���̶�����" << endl;
			return -1;
		}
	}

	/* ��ӡ���������Ľ�� */
	cout << "�ɱ�����б�:" << endl;
	args_analyse_print(args);

	/* ���IP��ַ�Ƿ��ǵ��ʮ���Ƶĺ�������Ҫʵ�� */
	if (is_ipaddr_valid(argv[cur_argc]) == false) {
		cout << "ָ����IP��ַ [" << argv[cur_argc] << "] ����ȷ." << endl;
		return -1;
	}

	/* ��ӡ������ֵ */
	cout << "�������ͨ��" << endl;
	cout << " --t������" << args[ARGS_L].existed() << endl;
	cout << " --n������" << args[ARGS_N].get_int() << endl;
	cout << " --l������" << args[ARGS_L].get_int() << endl;
	cout << "IP��ַ�ǣ�" << argv[cur_argc] << endl;
#else //������������Ĵ��룬--t/--n/--l/--ip��Ϊ��ѡ�������໥λ�����⣬ͨ���ж�--ip�Ƿ������ǿ��Ҫ��ò����������
	args_analyse_tools args[] = {
		args_analyse_tools("--help", ST_EXTARGS_TYPE::boolean,          0, false), //Ĭ��false
		args_analyse_tools("--t",    ST_EXTARGS_TYPE::boolean,          0, false), //Ĭ��false
		args_analyse_tools("--n",    ST_EXTARGS_TYPE::int_with_default, 1, 4, 1, 1024), //[1..1024]��Ĭ��4
		args_analyse_tools("--l",    ST_EXTARGS_TYPE::int_with_default, 1, 64, 32, 64000), //[32..64000]��Ĭ��64
		args_analyse_tools("--ip",   ST_EXTARGS_TYPE::ipaddr_with_error,1, string("")),
		args_analyse_tools()  //���һ�������ڽ���
};

	/* �����κβ��������⴦����ӡ��ʾ��Ϣ����� */
	if (argc == 1) {
		usage(argv[0]);
		return -1;
	}

	int need_fixed_args = 0;	//����Ҫ�̶�����
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

	/* �ж��Ƿ���--ip���� */
	if (args[ARGS_IPADDR].existed() == false) {
		cout << "����ָ��IP��ַ(--ip����)" << endl;
		usage(argv[0]);
		return -1;
	}

	/* ��ӡ���������Ľ��������Ҫ�ٴμ��IP��ַ�ĺ����ԣ���Ϊ--ipʱ�Ѿ������ˣ� */
	cout << "�ɱ�����б�:" << endl;
	args_analyse_print(args);

	/* ��ӡ������ֵ */
	cout << "�������ͨ��" << endl;
	cout << " --t������" << args[ARGS_L].existed() << endl;
	cout << " --n������" << args[ARGS_N].get_int() << endl;
	cout << " --l������" << args[ARGS_L].get_int() << endl;
	cout << "IP��ַ�ǣ�" << args[ARGS_IPADDR].get_str_ipaddr() << endl;
#endif

	return 0;
}
