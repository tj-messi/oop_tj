/* 2150792 �ƿ� ţ»�� */
#include <iostream>
#include <Windows.h>
#include <conio.h>
using namespace std;

#include "../include/class_aat.h"
#include "../include/class_crt.h"

enum OPT_ARGS { OPT_ARGS_HELP = 0, OPT_ARGS_CFGFILE };

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void wait_for_enter()
{
	cout << endl << "���س�������";
	while (_getch() != '\r')
		;
	cout << endl << endl;
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����
 ***************************************************************************/
int readconfig_php_linux(const char *const cfgfile_name)
{
	cfgfile_read_tools cfg(cfgfile_name);
	if (cfg.is_open() == 0) {
		cout << "�����ļ� [" << cfgfile_name << "] �޷���." << endl;
		return -1;
	}

	if (1) {
		cout << "����01.ȡ�����ļ��е������飺" << endl;

		vector <string> group;
		if (cfg.get_all_group(group) < 0) {
			cout << "ȡ�����ļ� [" << cfgfile_name << "] �����������." << endl;
			return -1;
		}
		for (auto& ig : group)
			cout << ig << endl;
		cout << endl;
		wait_for_enter();

		cout << "����02.ȡ�����ļ��е�������������" << endl;
		vector <string> item;
		for (auto& ig : group) {
			if (cfg.get_all_item(ig, item) < 0) {
				cout << "ȡ�����ļ� [" << cfgfile_name << "] ��" << ig << "�����." << endl;
				return -1;
			}

			cout << ig << endl;
			for (auto& it : item)
				cout << '*' << it << '*' << endl; //ǰ���*���ڿ���ո�������ַ�
			cout << endl;
		}
		wait_for_enter();

		cout << "����03.ȡ�����ļ��е��������ΪNULL�������������ļ���⣩��" << endl;
		item.clear();
		if (cfg.get_all_item(NULL, item) < 0) {
			cout << "ȡ�����ļ� [" << cfgfile_name << "] �����������." << endl;
			return -1;
		}

		for (auto& it : item)
			cout << '*' << it << '*' << endl; //ǰ���*���ڿ���ո�������ַ�
		cout << endl;
		wait_for_enter();
	}

	if (1) {
		/* ��ӡ[ODBC]���������Ŀ�����ִ�Сд�� */
		const char* gname = "[ODBC]";
		cout << "11.ȡ�����ļ��е�" << gname << "��-���ִ�Сд-��ȷ��" << endl;

		vector <string> item;
		if (cfg.get_all_item(gname, item) < 0) {
			cout << "ȡ�����ļ� [" << cfgfile_name << "] ��" << gname << "�����." << endl;
			return -1;
		}
		for (auto& it : item)
			cout << '*' << it << '*' << endl; //ǰ���*���ڿ���ո�������ַ�
		cout << endl;

		/* ��ӡ[odbc]���������Ŀ�����ִ�Сд�� */
		gname = "[odbc]";
		cout << "12.ȡ�����ļ��е�" << gname << "��-���ִ�Сд-����" << endl;

		item.clear();
		if (cfg.get_all_item(gname, item) < 0) {
			cout << "ȡ�����ļ� [" << cfgfile_name << "] ��" << gname << "�����." << endl;
//			return -1;Ӧ�ó��������أ���������ִ��
		}
		cout << endl;

		/* ��ӡ[odbc]���������Ŀ�����ִ�Сд�� */
		cout << "13.ȡ�����ļ��е�" << gname << "��-���ִ�Сд-��ȷ��" << endl;
		if (cfg.get_all_item(gname, item, true) < 0) {
			cout << "ȡ�����ļ� [" << cfgfile_name << "] ��" << gname << "�����." << endl;
			return -1;
		}
		for (auto& it : item)
			cout << '*' << it << '*' << endl; //ǰ���*���ڿ���ո�������ַ�
		cout << endl;

		/* ��ӡ[PostgreSQL]���������Ŀ�����ִ�Сд�� */
		gname = "[POSTGRESQL]";
		cout << "14.ȡ�����ļ��е�" << gname << "��-���ִ�Сд-��ȷ��" << endl;
		item.clear();
		if (cfg.get_all_item(gname, item, true) < 0) {
			cout << "ȡ�����ļ� [" << cfgfile_name << "] ��" << gname << "�����." << endl;
			return -1;
		}
		for (auto& it : item)
			cout << '*' << it << '*' << endl; //ǰ���*���ڿ���ո�������ַ�
		cout << endl;

		wait_for_enter();
	}

	if (1) {
		/* ȡ�������������ظ��У��������ƺ�ֵ��*/
		string str;
		const char* gname = "[ODBC]";
		const char* iname = "odbc.defaultlrl";

		cout << "21.ȡ�����ļ���" << gname << "���[" << iname << "]��-���ִ�Сд-��ȷ��" << endl;
		if (cfg.get_one_item(gname, iname, str) < 0) {
			cout << "ȡ�����ļ� [" << cfgfile_name << "] ��" << gname << "���[" << iname << "]�����." << endl;
			return -1;
		}
		cout << '*' << str << '*' << endl; //ǰ���*���ڿ���ո�������ַ�
		cout << endl;

		gname = "[POSTGRESQL]";
		iname = "PGSQL.max_links";
		cout << "22.ȡ�����ļ���" << gname << "���[" << iname << "]��-���ִ�Сд-����" << endl;
		if (cfg.get_one_item(gname, iname, str) < 0) {
			cout << "ȡ�����ļ� [" << cfgfile_name << "] ��" << gname << "���[" << iname << "]�����." << endl;
			//		return -1;Ӧ�ó��������أ���������ִ��
		}
		cout << endl;

		cout << "23.ȡ�����ļ���" << gname << "���[" << iname << "]��-���ִ�Сд-��ȷ��" << endl;
		if (cfg.get_one_item(gname, iname, str, true) < 0) {
			cout << "ȡ�����ļ� [" << cfgfile_name << "] ��" << gname << "���[" << iname << "]�����." << endl;
			return -1;
		}
		cout << '*' << str << '*' << endl; //ǰ���*���ڿ���ո�������ַ�
		cout << endl;

		wait_for_enter();
	}

	if (1) {
		/* ȡ��������������int��*/
		const char* gname = "[ODBC]";
		const char* iname = "odbc.defaultlrl";
		int ret_value;

		cout << "31.ȡ�����ļ���" << gname << "���[" << iname << "]���ֵ-Ӧ����4096��" << endl;
		/* ָ����Сֵ-100�����ֵ10000��Ĭ��ֵ200����Ϊ�����ļ��е�4096�ں���Χ�ڣ���˷���4096 */
		if (cfg.item_get_value(gname, iname, -100, 10000, 200, ret_value) < 0) {
			cout << "ȡ�����ļ� [" << cfgfile_name << "] ��" << gname << "���[" << iname << "]���ֵ����." << endl;
			return -1;
		}
		cout << '*' << ret_value << '*' << endl; //ǰ���*���ڿ���ո�������ַ�
		cout << endl;

		cout << "32.ȡ�����ļ���" << gname << "���[" << iname << "]���ֵ-Ӧ����1��" << endl;
		/* ָ����Сֵ-1�����ֵ2048��Ĭ��ֵ1����Ϊ�����ļ��е�4096���ں���Χ�ڣ���˷���1 */
		if (cfg.item_get_value(gname, iname, -1, 2048, 1, ret_value) < 0) {
			cout << "ȡ�����ļ� [" << cfgfile_name << "] ��" << gname << "���[" << iname << "]���ֵ����." << endl;
			return -1;
		}
		cout << '*' << ret_value << '*' << endl; //ǰ���*���ڿ���ո�������ַ�
		cout << endl;

		/* ָ����Сֵ0�����ֵ100��Ĭ��ֵ99����Ϊ�����ļ��ж�Ӧ�����ַ���On���������Ͳ�ƥ�䣬��˷���99 */
		gname = "[ODBC]";
		iname = "odbc.allow_persistent";
		cout << "33.ȡ�����ļ���" << gname << "���[" << iname << "]���ֵ-Ӧ����99��" << endl;
		if (cfg.item_get_value(gname, iname, 0, 100, 99, ret_value) < 0) {
			cout << "ȡ�����ļ� [" << cfgfile_name << "] ��" << gname << "���[" << iname << "]���ֵ����." << endl;
			return -1;
		}
		cout << '*' << ret_value << '*' << endl; //ǰ���*���ڿ���ո�������ַ�
		cout << endl;

		/* ָ����Сֵ0�����ֵ1000��Ĭ��ֵ1����Ϊ�����ļ��ж�Ӧ����123.456����int������˷���123 */
		gname = "[Interbase]";
		iname = "ibase.max_persistent";
		cout << "34.ȡ�����ļ���" << gname << "���[" << iname << "]���ֵ-Ӧ����123��" << endl;
		if (cfg.item_get_value(gname, iname, 0, 1000, 1, ret_value) < 0) {
			cout << "ȡ�����ļ� [" << cfgfile_name << "] ��" << gname << "���[" << iname << "]���ֵ����." << endl;
			return -1;
		}
		cout << '*' << ret_value << '*' << endl; //ǰ���*���ڿ���ո�������ַ�
		cout << endl;

		wait_for_enter();
	}

	if (1) {
		/* ȡ��������������double��*/
		const char* gname = "[Interbase]";
		const char* iname = "ibase.max_persistent";
		double ret_value;

		/* �����ļ�����double�����ݣ����ں���Χ�� */
		cout << "41.ȡ�����ļ���" << gname << "���[" << iname << "]���ֵ-Ӧ����123.456��" << endl;
		if (cfg.item_get_value(gname, iname, 0, 1000, 1, ret_value) < 0) {
			cout << "ȡ�����ļ� [" << cfgfile_name << "] ��" << gname << "���[" << iname << "]���ֵ����." << endl;
			return -1;
		}
		cout << '*' << ret_value << '*' << endl; //ǰ���*���ڿ���ո�������ַ�
		cout << endl;

		/* �����ļ�����double�����ݣ������ں���Χ�� */
		cout << "42.ȡ�����ļ���" << gname << "���[" << iname << "]���ֵ-Ӧ����11.22��" << endl;
		if (cfg.item_get_value(gname, iname, 0, 100, 11.22, ret_value) < 0) {
			cout << "ȡ�����ļ� [" << cfgfile_name << "] ��" << gname << "���[" << iname << "]���ֵ����." << endl;
			return -1;
		}
		cout << '*' << ret_value << '*' << endl; //ǰ���*���ڿ���ո�������ַ�
		cout << endl;

		gname = "[ODBC]";
		iname = "odbc.defaultlrl";
		/* �����ļ�����int�����ݣ���doubleȡҲ���� */
		cout << "43.ȡ�����ļ���" << gname << "���[" << iname << "]���ֵ-Ӧ����4096��" << endl;
		if (cfg.item_get_value(gname, iname, 0, 8000, 1, ret_value) < 0) {
			cout << "ȡ�����ļ� [" << cfgfile_name << "] ��" << gname << "���[" << iname << "]���ֵ����." << endl;
			return -1;
		}
		cout << '*' << ret_value << '*' << endl; //ǰ���*���ڿ���ո�������ַ�
		cout << endl;

		gname = "[POSTGRESQL]";
		iname = "pgsql.allow_persistent";
		/* �����ļ�����On�����ݣ���doubleȡ����Ĭ��ֵ */
		cout << "44.ȡ�����ļ���" << gname << "���[" << iname << "]���ֵ-Ӧ����3.2��" << endl;
		if (cfg.item_get_value(gname, iname, 0, 100, 3.2, ret_value) < 0) {
			cout << "ȡ�����ļ� [" << cfgfile_name << "] ��" << gname << "���[" << iname << "]���ֵ����." << endl;
			return -1;
		}
		cout << '*' << ret_value << '*' << endl; //ǰ���*���ڿ���ո�������ַ�
		cout << endl;

		wait_for_enter();
	}

	if (1) {
		const char *gname = "[POSTGRESQL]";
		const char* iname = "pgsql.allow_persistent";
		char s1[80];
		string s2;

		/* ָ�����ַ����鷽ʽȥ������˷���On */
		cout << "51.ȡ�����ļ���" << gname << "���[" << iname << "]���ֵ-Ӧ����On��" << endl;
		if (cfg.item_get_value(gname, iname, "Hello", s1, 80) < 0) {
			cout << "ȡ�����ļ� [" << cfgfile_name << "] ��" << gname << "���[" << iname << "]���ֵ����." << endl;
			return -1;
		}
		cout << '*' << s1 << '*' << endl; //ǰ���*���ڿ���ո�������ַ�
		cout << endl;

		/* ָ����string��ʽȥ������˷���On */
		cout << "52.ȡ�����ļ���" << gname << "���[" << iname << "]���ֵ-Ӧ����On��" << endl;
		if (cfg.item_get_value(gname, iname, "Hello", s2) < 0) {
			cout << "ȡ�����ļ� [" << cfgfile_name << "] ��" << gname << "���[" << iname << "]���ֵ����." << endl;
			return -1;
		}
		cout << '*' << s2 << '*' << endl; //ǰ���*���ڿ���ո�������ַ�
		cout << endl;

		/* ָ�����ַ����鷽ʽȥ����ָ��Ĭ��ֵΪHello����Ϊ odbc.check_persistent = ����û�����ݣ���˷���Hello	*/
		gname = "[ODBC]";
		iname = "odbc.check_persistent";
		cout << "53.ȡ�����ļ���" << gname << "���[" << iname << "]���ֵ-Ӧ����Hello��" << endl;
		if (cfg.item_get_value(gname, iname, "Hello", s1, 80) < 0) {
			cout << "ȡ�����ļ� [" << cfgfile_name << "] ��" << gname << "���[" << iname << "]���ֵ����." << endl;
			return -1;
		}
		cout << '*' << s1 << '*' << endl; //ǰ���*���ڿ���ո�������ַ�
		cout << endl;

		/* ָ�����ַ����鷽ʽȥ�������������ֻ�ܴ��5���ַ�(��β��)��ָ��Ĭ��ֵΪHello����Ϊ odbc.check_persistent = ����û�����ݣ���˷���Hell	*/
		cout << "54.ȡ�����ļ���" << gname << "���[" << iname << "]���ֵ-Ӧ����Hell��" << endl;
		if (cfg.item_get_value(gname, iname, "Hello", s1, 5) < 0) {
			cout << "ȡ�����ļ� [" << cfgfile_name << "] ��" << gname << "���[" << iname << "]���ֵ����." << endl;
			return -1;
		}
		cout << '*' << s1 << '*' << endl; //ǰ���*���ڿ���ո�������ַ�
		cout << endl;

		gname = "[ODBC]";
		iname = "odbc.defaultlrl";
		/* ָ�����ַ����鷽ʽȥ������ʹ��int��Ҳ�ܷ����ַ����͵�4096����˷���4096	*/
		cout << "55.ȡ�����ļ���" << gname << "���[" << iname << "]���ֵ-Ӧ����4096��" << endl;
		if (cfg.item_get_value(gname, iname, "Hello", s1, 80) < 0) {
			cout << "ȡ�����ļ� [" << cfgfile_name << "] ��" << gname << "���[" << iname << "]���ֵ����." << endl;
			return -1;
		}
		cout << '*' << s1 << '*' << endl; //ǰ���*���ڿ���ո�������ַ�
		cout << endl;

		/* ָ�����ַ����鷽ʽȥ�����ӿո���ַ��������ص�һ���ո�ǰ������ */
		gname = "[Interbase]";
		iname = "ibase.timeformat";
		cout << "56.ȡ�����ļ���" << gname << "���[" << iname << "]���ֵ-Ӧ����%Y-%m-%d��" << endl;
		if (cfg.item_get_value(gname, iname, "Hello", s1, 80) < 0) {
			cout << "ȡ�����ļ� [" << cfgfile_name << "] ��" << gname << "���[" << iname << "]���ֵ����." << endl;
			return -1;
		}
		cout << '*' << s1 << '*' << endl; //ǰ���*���ڿ���ո�������ַ�
		cout << endl;

		/* ָ����stringȥ�����ո���ַ��������غ��ո�Ĵ� */
		gname = "[Interbase]";
		iname = "ibase.timeformat";
		cout << "57.ȡ�����ļ���" << gname << "���[" << iname << "]���ֵ-Ӧ����%Y-%m-%d %H:%M:%S��" << endl;
		if (cfg.item_get_value(gname, iname, "Hello", s2) < 0) {
			cout << "ȡ�����ļ� [" << cfgfile_name << "] ��" << gname << "���[" << iname << "]���ֵ����." << endl;
			return -1;
		}
		cout << '*' << s2 << '*' << endl; //ǰ���*���ڿ���ո�������ַ�
		cout << endl;

		wait_for_enter();
	}

	if (1) {
		const char* gname = "[Interbase]";
		const char* iname = "ibase.allow_persistent";
		char ch;

		/* ָ�����ַ�ȥ������˷���Y */
		cout << "61.ȡ�����ļ���" << gname << "���[" << iname << "]���ֵ-Ӧ����Y��" << endl;
		if (cfg.item_get_value(gname, iname, ch) < 0) {
			cout << "ȡ�����ļ� [" << cfgfile_name << "] ��" << gname << "���[" << iname << "]���ֵ����." << endl;
			return -1;
		}
		cout << '*' << ch << '*' << int(ch) << '*' << endl; //ǰ���*���ڿ���ո�������ַ�
		cout << endl;

		gname = "[POSTGRESQL]";
		iname = "pgsql.allow_persistent";
		/* ָ�����ַ�ȥ���ַ���On����˷������ַ�O */
		cout << "62.ȡ�����ļ���" << gname << "���[" << iname << "]���ֵ-Ӧ����O��" << endl;
		if (cfg.item_get_value(gname, iname, ch) < 0) {
			cout << "ȡ�����ļ� [" << cfgfile_name << "] ��" << gname << "���[" << iname << "]���ֵ����." << endl;
			return -1;
		}
		cout << '*' << ch << '*' << int(ch) << '*' << endl; //ǰ���*���ڿ���ո�������ַ�
		cout << endl;

		gname = "[ODBC]";
		iname = "odbc.defaultlrl";
		/* ָ�����ַ�ȥ��4096���������ַ�4 */
		cout << "63.ȡ�����ļ���" << gname << "���[" << iname << "]���ֵ-Ӧ����4��" << endl;
		if (cfg.item_get_value(gname, iname, ch) < 0) {
			cout << "ȡ�����ļ� [" << cfgfile_name << "] ��" << gname << "���[" << iname << "]���ֵ����." << endl;
			return -1;
		}
		cout << '*' << ch << '*' << int(ch) << '*' << endl; //ǰ���*���ڿ���ո�������ַ�
		cout << endl;

		/* ָ�����ַ�ȥ������Ϊ odbc.check_persistent = ����û�����ݣ���˷��ؿո�	*/
		gname = "[ODBC]";
		iname = "odbc.check_persistent";
		cout << "64.ȡ�����ļ���" << gname << "���[" << iname << "]���ֵ-Ӧ���� ��" << endl;
		if (cfg.item_get_value(gname, iname, ch) < 0) {
			cout << "ȡ�����ļ� [" << cfgfile_name << "] ��" << gname << "���[" << iname << "]���ֵ����." << endl;
			return -1;
		}
		cout << '*' << ch << '*' << int(ch) << '*' << endl; //ǰ���*���ڿ���ո�������ַ�
		cout << endl;

		wait_for_enter();
	}

	return 0;
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����
 ***************************************************************************/
static int readconfig(const string& cfgfile_name)
{
	cfgfile_read_tools cfg(cfgfile_name);
	if (cfg.is_open() == 0) {
		cout << "�����ļ� [" << cfgfile_name << "] �޷���." << endl;
		return -1;
	}

	if (1) {
		cout << "����01.ȡ�����ļ��е������飺" << endl;

		vector <string> group;
		if (cfg.get_all_group(group) < 0) {
			cout << "ȡ�����ļ� [" << cfgfile_name << "] �����������." << endl;
			return -1;
		}
		for (auto& ig : group)
			cout << ig << endl;
		cout << endl;
		wait_for_enter();

		cout << "����02.ȡ�����ļ��е�������������" << endl;
		vector <string> item;
		for (auto& ig : group) {
			if (cfg.get_all_item(ig, item) < 0) {
				cout << "ȡ�����ļ� [" << cfgfile_name << "] ��" << ig << "�����." << endl;
				return -1;
			}

			cout << ig << endl;
			for (auto& it : item)
				cout << '*' << it << '*' << endl; //ǰ���*���ڿ���ո�������ַ�
			cout << endl;
		}
		wait_for_enter();

		cout << "����03.ȡ�����ļ��е��������ΪNULL�������������ļ���⣩��" << endl;
		item.clear();
		if (cfg.get_all_item(NULL, item) < 0) {
			cout << "ȡ�����ļ� [" << cfgfile_name << "] �����������." << endl;
			return -1;
		}

		for (auto& it : item)
			cout << '*' << it << '*' << endl; //ǰ���*���ڿ���ո�������ַ�
		cout << endl;
		wait_for_enter();
	}

	/* ����ʵ������Ĳ��� */
	


	return 0;
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����
 ***************************************************************************/
static void usage(const char* full_procname)
{
	/* ��·���ַ��������ơ�D:\\VS-Debug\\test-readcfg.exe��)�в������һ��\\����������ڣ���Ϊȫ�� */
	const char* procname = strrchr(full_procname, '\\');
	if (procname == NULL)
		procname = full_procname;
	else
		procname++; //ָ��\\����һ���ַ�

	cout << "Usage: " << procname << " --cfgfile filename" << endl;
	cout << endl;
	cout << "e.g. : " << endl;
	cout << "       " << procname << " --cfgfile test.conf : ָ�������ļ���Ϊtest.conf" << endl;
	cout << endl;
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ���������
  ���������
  �� �� ֵ��
  ˵    ���������и�ʽҪ����--��ʼ�Ŀɱ������˳�����⣬�����ָ���Ĺ̶�����
***************************************************************************/
int main(int argc, char **argv)
{
	/* ��Ϊ������ lib_aat_tools.lib���˴��ȼ���С�Ƿ����Ҫ�� */
	if (sizeof(args_analyse_tools) != 200) {
		cout << "class args_analyse_tools ����200�ֽڣ����ʹ�� lib_aat_tools.lib �еĺ�������ܳ���" << endl;
		return -1;
	}

	args_analyse_tools args[] = {
		args_analyse_tools("--help",      ST_EXTARGS_TYPE::boolean, 0, false),
		args_analyse_tools("--cfgfile",    ST_EXTARGS_TYPE::str,                  1, string("")),		//�����string()���������䵽args_analyse(const char *arg_name, enum ST_EXTARGS_TYPE type, int ext_num, bool def)
		args_analyse_tools()  //���һ�������ڽ���
	};

	int need_fixed_args = 0;	//���Ը�Ϊ1
	int cur_argc;

	/* ���һ��������1-��ʾ��ѡ������⣬����Ҫ��������
				  0-��ʾ��ѡ������⣬����Ҫ�������� */
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
	}

	/* ��ӡ��ǰ�����ķ������ */
	args_analyse_print(args);

	if (args[OPT_ARGS_CFGFILE].existed() == 0) {
		usage(argv[0]);
		cout << "������������ļ���." << endl;
		return -1;
	}

	/* ���������ο�ʾ�� */

	if (1) {
		cout << "==========================" << endl;
		cout << "php-linux.ini ��ȡ����" << endl;
		cout << "==========================" << endl;
		readconfig_php_linux("php-linux.ini");
	}

	if (1) {
		cout << "==========================" << endl;
		cout << "php-win.ini ��ȡ����" << endl;
		cout << "==========================" << endl;
		readconfig_php_linux("php-win.ini");
	}

	if (1) {
		/* ����ָ���������ļ��Ķ�ȡ���ԣ����˰��裩 */
		string cfgfile_name = args[OPT_ARGS_CFGFILE].get_string();
		cout << "==========================" << endl;
		cout << cfgfile_name << " ��ȡ����" << endl;
		cout << "==========================" << endl;
		readconfig(cfgfile_name);
	}

	return 0;
}
