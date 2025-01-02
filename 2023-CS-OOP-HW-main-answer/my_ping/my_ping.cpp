/* 2150792 ţ»�� �ƿ� */
#include <iostream>
//�ɸ�����Ҫ�ټ���������Ҫ��ͷ�ļ�
#include "../include/class_aat.h"
using namespace std;

enum OPT_ARGS {
	ARGS_HELP = 0,
	ARGS_T,
	ARGS_N,
	ARGS_L
};

/* ���������������������Ҳ���Խ��Զ��庯����������cpp�� */
static int str_to_int(const char* const str, int start, int end, bool& flag) //���±�[start end)���ַ���ת��Ϊint
{
	int temp = 0;
	int minus_flag = 1;
	int real_end = int(strlen(str)) < end ? int(strlen(str)) : end; //ȡstrlen(str)��end�н�С���Ǹ� 
	if (start == real_end)
	{
		flag = false;
		return INT_MIN;
	}
	for (int i = start; i < real_end; i++)
	{
		if (i == start && str[i] == '-')
		{
			minus_flag = -1;
			continue;
		}
		temp *= 10;
		if (str[i] >= '0' && str[i] <= '9') //�����ּ���
			temp += (str[i] - '0');
		else
		{
			flag = false;
			return INT_MIN;
		}
	}
	return minus_flag * temp;
}

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

	/* ע���ⲿ�ֱ�14-b4��Ҫ��ͣ���Ϊû������������Ӧ */
	cout << endl;
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
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ������һ�룬ΪʲôҪ�� static����Ȼֻ��һ��cpp�������ǹ���ϰ�ߣ�
***************************************************************************/
static bool is_ipaddr_valid(const char* const ipstr)
{
	string temp_str = ipstr;
	int end_index[5] = { -1,0,0,0,int(strlen(ipstr)) };		  // �������Ԫ��-1���ı�
	int j = 1;
	//����ip��ַ���ҵ�'.'���ڵ��±�
	for (int i = 0; i < int(strlen(ipstr)); i++)
	{
		if (ipstr[i] == '.')
		{
			if (j >= 4)                      // '.'�ĸ�������4����
				return false;
			else
				end_index[j++] = i;
		}
	}
	if (j < 4)								// '.'�ĸ���С��3Ҳ����
		return false;
	for (int i = 0; i < 4; i++)
	{
		int temp = 0;
		bool flag = true;
		temp = str_to_int(ipstr, end_index[i] + 1, end_index[i + 1], flag);
		string check_zero = temp_str.substr(end_index[i] + 1, end_index[i + 1] - end_index[i] - 1); // ��ȡ��Ӧ��str�Ӵ�
		if ((check_zero != to_string(temp) || temp < 0 || temp>255))			// �ֱ����ĸ�'.'֮����ĸ����֣���������ǰ��0
			return false;
	}
	return true;//��������Ҫ����ʵ�֣�����ֵ�����޸�
	
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
	if (sizeof(args_analyse_tools) != 200) {
		cout << "class args_analyse_tools ����200�ֽڣ����ʹ�� lib_common_tools.lib �еĺ�������ܳ���" << endl;
		return -1;
	}

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

	/* ���IP��ַ�Ƿ��ǵ��ʮ���Ƶĺ�������Ҫʵ�� */
	if (is_ipaddr_valid(argv[cur_argc]) == false) {
		cout << "ָ����IP��ַ [" << argv[cur_argc] << "] ����ȷ." << endl;
		return -1;
	}

	/* ��ӡ���������Ľ�� */
	cout << "�ɱ�����б�:" << endl;
	args_analyse_print(args);

	/* ��ӡ������ֵ */
	cout << "�������ͨ��" << endl;
	cout << " --t������" << args[ARGS_L].existed() << endl;
	cout << " --n������" << args[ARGS_N].get_int() << endl;
	cout << " --l������" << args[ARGS_L].get_int() << endl;
	cout << "IP��ַ�ǣ�" << argv[cur_argc] << endl;

	return 0;
}
