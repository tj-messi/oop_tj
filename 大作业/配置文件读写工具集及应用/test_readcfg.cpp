#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <conio.h>
#include "../include/class_aat.h"
#include "../include/class_cft.h"
using namespace std;

#define TEST_FOR_FIXED_FILE	1

#if TEST_FOR_FIXED_FILE

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
int readconfig_yzmond_conf(const char *const fname)
{
	config_file_tools sCfg(fname); //�ָ�����=

	if (sCfg.is_read_succeeded() == 0) {
		cout << "�����ļ�[" << fname << "]��ȡ�д�." << endl;
		return -1;
	}

	/* ���屾Ӧ�ó������������Ľṹ�壬ÿ�����ݵľ������͸���ʵ����;���� */
	struct yzmond_cfg {
		unsigned int dbserver_ip;		//���ݿ������IP��ַ
		unsigned short dbserver_port;	//���ݿ�������˿ں�
		unsigned short bind_port;		//�����˿ں�
		bool is_long_tcp;		//�Ƿ�����
		int db_bufsize;			//���ݿ⻺������С
		double memory_toplimit;	//�ڴ�ʹ������
	} mycfg;

	int port;
	sCfg.item_get_int("[��������]", "�����˿ں�", port, 0, 65535, 41109);
	/* ��Ϊû�� item_get_short���ֲ����ڴ���ʱ��shortǿ��ת��Ϊint�����������ʱ����ȥ�����ٸ�ֵ
	   ��Ϊ������0-65535�����ᳬ��u_short�Ľ��� */
	mycfg.bind_port = port;

	char sel;
	sCfg.item_get_char("[��������]", "��������", sel, "YyNn", 'n');
	/* �����ļ��и���ĿԼ��ֻ����дYyNy����˶�����������ת�� */
	mycfg.is_long_tcp = (sel == 'Y' || sel == 'y') ? true : false;

	sCfg.item_get_int("[���ݿ�]", "�������˿ں�", port, 0, 65535, 3306);
	mycfg.dbserver_port = port;

	sCfg.item_get_ipaddr("[���ݿ�]", "������IP��ַ", mycfg.dbserver_ip, 0xC0A850E6); // Ĭ��"192.168.80.230"
	sCfg.item_get_int("[���ݿ�]", "���ݿ⻺����", mycfg.db_bufsize);
	/* �����ļ��еĵ�λ��MB��תΪ�ֽ� */
	mycfg.db_bufsize *= 1024 * 1024;

	sCfg.item_get_double("[ϵͳ����]", "�ڴ�ʹ�ñ���", mycfg.memory_toplimit, 0, 80, 60);

	/* ��ӡ����ֵ */
	cout << "bind_port = " << mycfg.bind_port << endl;
	cout << "dbserver_ip = " << hex << mycfg.dbserver_ip << dec << endl;
	cout << "dbserver_port = " << mycfg.dbserver_port << endl;
	cout << "log_tcp = " << (mycfg.is_long_tcp ? "Yes":"No") << endl;
	cout << "db_bufsize = " << mycfg.db_bufsize << "�ֽ�" << endl;
	cout << "memory_toplimit = " << mycfg.memory_toplimit << "%" << endl;

	/* ��������ִ�У��ں��������л��õ�mycfg�ĸ������� */

	return 0;
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����
 ***************************************************************************/
int readconfig_php_ini(const char* const fname)
{
	config_file_tools sCfg(fname); //�ָ�����=

	if (sCfg.is_read_succeeded() == 0) {
		cout << "�����ļ�[" << fname << "]��ȡ�д�." << endl;
		return -1;
	}

	/* ��ӡ[ODBC]����������ԭʼ��Ϣ */
	const char* const gname = "[ODBC]";
	cout << "ȡ�����ļ��е�" << gname << "�飺" << endl;
	vector <string> item;
	if (sCfg.get_all_item(gname, item) == 0) {
		cout << "δȡ�������ļ� [" << fname << "] �� [" << gname << "] ��." << endl;
		return -1;
	}

	for (auto& it : item)
		cout << '*' << it << '*' << endl; //ǰ���*���ڿ���ո�������ַ�
	cout << endl;

	/* ȡ�������������ظ��У��������ƺ�ֵ��*/
	char value[16];
	sCfg.item_get_cstring("[ODBC]", "odbc.allow_persistent", value, sizeof(value));
	cout << "allow_persistent = " << value << endl;

	int max_links;
	sCfg.item_get_int("[POSTGRESQL]", "pgsql.max_links", max_links);
	cout << "max_links = " << max_links << endl;

	return 0;
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    �����ϸ���˵��httpd.conf����һ�ַ��������ļ���
			��������Directory���ʾ��
				<Directory />
					AllowOverride none
					Require all denied
				</Directory>
			���䵽ĿǰҪ��������ļ���ֻ����Ϊ������ļ������ļ�����ȡ
 ***************************************************************************/
int readconfig_httpd_conf(const char* const fname)
{
	config_file_tools sCfg(fname, BREAK_CTYPE::Space); //�ָ����ǿո�/tab

	if (sCfg.is_read_succeeded() == 0) {
		cout << "�����ļ�[" << fname << "]��ȡ�д�." << endl;
		return -1;
	}

	/* ȡ�������������ظ��У��������ƺ�ֵ��*/
	char value[32];
	sCfg.item_get_cstring("", "serverroot", value, sizeof(value)); //��Ŀ��Сд������
	cout << "ServerRoot = " << value << endl;

	string charset;
	sCfg.item_get_string("", "AddDefaultCharSet", charset);
	cout << "AddDefaultCharSet = " << charset << endl;

	string indexfile;
	sCfg.item_get_raw("", "DirectoryIndex", indexfile);
	cout << "DirectoryIndex = " << indexfile << endl;
	/* �����ٽ��д���ȡ���ո�ֿ��Ķ���ļ������˴��� */

	return 0;
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
int readconfig_homework_conf(const char* const fname)
{
	config_file_tools sCfg(fname); //�ָ�����=

	if (sCfg.is_read_succeeded() == 0) {
		cout << "�����ļ�[" << fname << "]��ȡ�д�." << endl;
		return -1;
	}

	/* ���屾Ӧ�ó������������Ľṹ�壬ÿ�����ݵľ������͸���ʵ����;���� */
	struct hw_cfg {
		string src_rootdir;			//ѧ���ύԴ�ļ��ĸ�Ŀ¼
		int score_deducting_base;	//�����۷�
		int score_deducting_bighw_one_warning; //����ҵwarning��������
		int score_deducting_bighw_max_warnings; //����ҵwarning��������
		int score_deducting_format;
	} mycfg;

	sCfg.item_get_string("[�ļ�Ŀ¼]", "src_rootdir", mycfg.src_rootdir);

	sCfg.item_get_int("[�ɼ�����]", "score_deducting_base", mycfg.score_deducting_base);
	sCfg.item_get_int("[�ɼ�����]", "score_deducting_format", mycfg.score_deducting_format);

	/* ����ҵ����۷ֵĸ�ʽ���ǵ�int����stringȡ�����ٴ��� */
	string bighw_warning_str;
	sCfg.item_get_raw("[�ɼ�����]", "score_deducting_warning_bighw", bighw_warning_str);
	istringstream in(bighw_warning_str);
	in >> mycfg.score_deducting_bighw_one_warning >> mycfg.score_deducting_bighw_max_warnings;
	/* Ӧ���ٶԶ��������ݽ��з�Χ��飬demo�� */

	/* ��ӡ����ֵ */
	cout << "�ύ��ҵ��Ŀ¼    ��" << mycfg.src_rootdir << endl;
	cout << "�������۷�      ��" << mycfg.score_deducting_base << endl;
	cout << "����ҵwarning�۷� ��ÿ��" << mycfg.score_deducting_bighw_one_warning << "�֣�����" << mycfg.score_deducting_bighw_max_warnings << "��" << endl;
	cout << "Դ�����ʽ�۷�    ��" << mycfg.score_deducting_format << endl;

	/* ��������ִ�У��ں��������л��õ�mycfg�ĸ������� */

	/* רҵȫ�ƺͼ�ƵĶ�Ӧ��ϵ��Ȼ�� xxx=yyy��ʽ����xxxδ֪�������רҵȫ��д�����ļ������� get_item_string ȥ������Ƿǳ��޴��ķǹ�����Ϊ!!!����
		��Ҫȫ��ȡ�����������ٵ������� */
	const char *const gname = "[רҵȫ�Ƽ�ƶ���]";
	vector <string> fname_sname_table;
	if (sCfg.get_all_item(gname, fname_sname_table) == 0) {
		cout << "δȡ�������ļ� [" << fname << "] �� [" << gname << "] ��." << endl;
		return -1;
	}

	cout << endl;
	cout << gname << endl;
	for (auto& it : fname_sname_table)
		cout << '*' << it << '*' << endl; //ǰ���*���ڿ���ո�������ַ�
	cout << endl;
	/* �����ٶ� fname_sname_table ���зֽ⣬�˴��� */

	/* ȡ��ѧ�ڵĿκ� */
	vector <string> cno_table;
	if (sCfg.get_all_item("[�κ�]", cno_table) == 0) {
		cout << "δȡ�������ļ� [" << fname << "] �� [�κ�] ��." << endl;
		return -1;
	}

	cout << endl;
	cout << "[�κ�]" << endl;
	for (auto& it : cno_table)
		cout << it << endl; //ǰ���*���ڿ���ո�������ַ�
	cout << endl;

	return 0;
}


#endif

#if !TEST_FOR_FIXED_FILE
enum OPT_ARGS {
	OPT_ARGS_HELP = 0,
	OPT_ARGS_DEBUG,
	OPT_ARGS_CFGFILE,
	OPT_ARGS_GROUP_NAME,
	OPT_ARGS_ITEM_NAME,
	OPT_ARGS_GROUP_NAME_CASE_SENSITIVE,
	OPT_ARGS_ITEM_NAME_CASE_SENSITIVE,
	OPT_ARGS_ITEM_BREAK_CHARACTER,
	OPT_ARGS_ITEM_TYPE
};
#endif

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
int main(int argc, char* argv[])
{
#if TEST_FOR_FIXED_FILE //���Լ����̶��������ļ��Ķ��������������ļ����߼�������ʹ�ó�����

	readconfig_yzmond_conf("yzmond.conf");
	cout << endl;
	wait_for_enter();

	readconfig_php_ini("php-win.ini");
	cout << endl;
	wait_for_enter();

	readconfig_php_ini("php-linux.ini");
	cout << endl;
	wait_for_enter();

	readconfig_httpd_conf("httpd.conf");
	cout << endl;
	wait_for_enter();

	readconfig_homework_conf("homework.conf");
	cout << endl;

#else //�������ɲ��ԣ������������ļ�������������Ŀ�ȣ�������֤��д�ĺ������и���������ȷ�ԣ�

	/* ָ����ȡ�����ݵ����� */
	const string itemtype_set[] = { "raw", "null", "char", "int", "double", "cstring", "string", "ip", "" };	//��β������""
	/* ָ��ÿ�����/ֵ֮��ķָ���
		equal : ���ַ� =
		space : �ո�tab���㣬����ж��������һ���� */
	const string break_character_set[] = { "equal", "space", "" };	//��β������""

	args_analyse_tools args[] = {
		args_analyse_tools("--help",     ST_EXTARGS_TYPE::boolean, 0, false),
		args_analyse_tools("--debug",    ST_EXTARGS_TYPE::boolean, 0, false),
		args_analyse_tools("--cfgfile",  ST_EXTARGS_TYPE::str, 1, string("")),	//�����string()���������䵽args_analyse(const char *arg_name, enum ST_EXTARGS_TYPE type, int ext_num, bool def)
		args_analyse_tools("--group",    ST_EXTARGS_TYPE::str, 1, string("all")),	//����[]��all���ʾȫ��group
		args_analyse_tools("--item",     ST_EXTARGS_TYPE::str, 1, string("all")),	//�����string()���������䵽args_analyse(const char *arg_name, enum ST_EXTARGS_TYPE type, int ext_num, bool def)
		args_analyse_tools("--gcs",      ST_EXTARGS_TYPE::boolean, 0, false),      //�������ִ�Сд��--group_case_sensitive��Ϊ�����뷽������д--gcs��
		args_analyse_tools("--ics",      ST_EXTARGS_TYPE::boolean, 0, false),      //�������ִ�Сд��--item_case_sensitive��Ϊ�����뷽������д--��
		args_analyse_tools("--brkchar",  ST_EXTARGS_TYPE::str_with_set_error, 1, 0, break_character_set),	//����/��ֵ��Ĭ�Ϸָ�����=�������ƶ�����������е�����һ��ƥ�伴��
		args_analyse_tools("--type",     ST_EXTARGS_TYPE::str_with_set_error, 1, 0, itemtype_set),		//����3�����壬����
		args_analyse_tools()  //���һ�������ڽ���
	};

	int cur_argc;

	//���һ������1����ʾ��ѡ������⣬������������
	if ((cur_argc = args_analyse_process(argc, argv, args, 0)) < 0) {
		//������Ϣ�ں������Ѵ�ӡ
		return -1;
	}

	const bool is_help = args[OPT_ARGS_HELP].existed(); //������Ҫ�ã���ȡֵ���������Ч��
	const bool is_debug = args[OPT_ARGS_DEBUG].existed(); //������Ҫ�ã���ȡֵ���������Ч��
	const bool is_group_case_sensitive = args[OPT_ARGS_GROUP_NAME_CASE_SENSITIVE].existed(); //������Ҫ�ã���ȡֵ���������Ч��
	const bool is_item_case_sensitive = args[OPT_ARGS_ITEM_NAME_CASE_SENSITIVE].existed(); //������Ҫ�ã���ȡֵ���������Ч��
	const enum BREAK_CTYPE ctype = (args[OPT_ARGS_ITEM_BREAK_CHARACTER].get_string() == "space") ? BREAK_CTYPE::Space : BREAK_CTYPE::Equal;
	const string item_type = args[OPT_ARGS_ITEM_TYPE].get_string();

	/* ������� --help | --debug ���ӡ���� --help ��ӡ�꼴�˳� */
	if (is_help || is_debug) {
		args_analyse_print(args);
		if (is_help)
			return -1;
	}

	if (args[OPT_ARGS_CFGFILE].existed() == 0) {
		args_analyse_print(args);
		cout << "�����" << args[OPT_ARGS_CFGFILE].get_name() << "����." << endl << endl;
		return -1;
	}

	if (args[OPT_ARGS_GROUP_NAME].existed() == 0 && args[OPT_ARGS_ITEM_NAME].existed() != 0) {
		cout << "ʹ��--itemǰ������ָ��--group(\"\"��ʾgroupΪ��" << endl;
		return -1;
	}

	config_file_tools sCfg(args[OPT_ARGS_CFGFILE].get_string(), ctype);

	if (sCfg.is_read_succeeded() == 0) {
		cout << "�����ļ�[" << args[OPT_ARGS_CFGFILE].get_string() << "]��ȡ���ɹ�" << endl;
		return -1;
	}

	/* �����--group �� --group all�����ӡȫ������ */
	if (args[OPT_ARGS_GROUP_NAME].get_string() == "all") {
		vector <string> groups;
		int group_num = sCfg.get_all_group(groups);
		if (group_num == 0)
			return 0;	//��Ϊ�գ��������õĿ��������򲻴�ӡ

		for (const auto& one_group : groups) {
			/* ȡÿ��������� */
			vector <string> items;
			int items_num = sCfg.get_all_item(one_group, items, is_group_case_sensitive);

			cout << "���� : " << (one_group.empty() ? "<NULL>" : one_group) << " ���� : " << items_num << endl; //�������ļ��Ŀ�������ӡΪ<NULL>
			for (const auto& one_item : items)
				cout << "    �� : " << one_item << endl;

			cout << endl; //ÿ���һ��
		}
	}
	else { //��ӡĳ��group�µ����������ĳ�������[]������--group [test]��
		string group_name_wanted = args[OPT_ARGS_GROUP_NAME].get_string();

		/* ȡ print_group_name ��������ע������ʱ��Ҫ����Ŀ��all�� */
		if (args[OPT_ARGS_ITEM_NAME].get_string() == "all") {
			vector <string> items;
			int items_num = sCfg.get_all_item(group_name_wanted, items, is_group_case_sensitive);

			if (items_num > 0) { //�ҵ�
				cout << "���� : " << group_name_wanted << " ���� : " << items_num << endl;
				for (const auto& one_item : items)
					cout << "    �� : " << one_item << endl;
			}
			else //δ�ҵ�
				cout << "δ�ҵ���" << group_name_wanted << endl;
		}
		else { //ȡ��������� xxx = yyy��ʽ������ȡ������
			string item_name_wanted = args[OPT_ARGS_ITEM_NAME].get_string();

			/* --typeδָ�� �� --type raw����ȡֵ��ԭʼ���ݣ���ָ���ָ�����������ַ�����string��ʽ���֣�*/
			if (item_type == "raw") {
				string item;
				int ret = sCfg.item_get_raw(group_name_wanted, item_name_wanted, item, is_group_case_sensitive, is_item_case_sensitive);
				if (ret)
					cout << "�ҵ���" << group_name_wanted << "/��" << item_name_wanted << "��ԭʼ����Ϊ[" << item << "]." << endl;
				else
					cout << "δ�ҵ���" << group_name_wanted << "/��" << item_name_wanted << "����������/��Ŀ�Ƿ���ȷ." << endl;
			}
			else { //�ƶ��˾����������ͣ�������ʹ��󣬲�����Ĵ�
				/* �ҵ���value�����ַ�����ʽ��ԭʼֵ����ֵȡ����ת��Ϊ��Ӧ�������ݼ���
					ע��Ĭ��ֵ����Χ��Ϊ�˼򻯣�û��ͨ�������ɱ䣬д���� */
				if (item_type == "null") {
					/* �Ȳ������ʹ�ã�������Сд�����С�������Сд������ */
					if (sCfg.item_get_null(group_name_wanted, item_name_wanted, is_group_case_sensitive, is_item_case_sensitive) > 0)
						cout << "�ҵ���\"" << group_name_wanted << "\"/��\"" << item_name_wanted << "\"." << endl;
					else
						cout << "δ�ҵ���\"" << group_name_wanted << "\"/��\"" << item_name_wanted << "\"." << endl;
				}
				else if (item_type == "char") {
					char c_value;

					/* �Ȳ������ʹ�ã���ȱʡֵ���޿�ѡ���ϣ������ַ����Ϸ�����������Сд�����С�������Сд������ */
					if (sCfg.item_get_char(group_name_wanted, item_name_wanted, c_value) > 0)
						cout << "�ҵ���\"" << group_name_wanted << "\"/��\"" << item_name_wanted << "\"��char�͵�ֵΪ[" << c_value << "/" << int(c_value) << "]." << endl; //��intֵ���㿴��
					else
						cout << "δ�ҵ���\"" << group_name_wanted << "\"/��\"" << item_name_wanted << "\"��char��ֵ����������/��Ŀ/���������Ƿ���ȷ." << endl;

					cout << endl;

					/* ��β����п�ѡ���ϡ���ȱʡֵ���������Ϊ��Ҫ--gcs��--ics�����Ĭ��ֵֻ�����ϣ�
					   ��������Ǵ�Сд���У���˾��Ϊ sCfg.item_get_char(group_name_wanted, item_name_wanted, c_value, "YyNn");	 */
					if (sCfg.item_get_char(group_name_wanted, item_name_wanted, c_value, "YyNn", DEFAULT_CHAR_VALUE, is_group_case_sensitive, is_item_case_sensitive) > 0)
						cout << "�ҵ���\"" << group_name_wanted << "\"/��\"" << item_name_wanted << "\"��char�͵�ֵΪ[" << c_value << "/" << int(c_value) << "]." << endl; //��intֵ���㿴��
					else
						cout << "δ�ҵ���\"" << group_name_wanted << "\"/��\"" << item_name_wanted << "\"��char��ֵ����������/��Ŀ/���������Ƿ���ȷ." << endl;

					cout << endl;

					/*  �������п�ѡ������ȱʡֵ�����*/
					if (sCfg.item_get_char(group_name_wanted, item_name_wanted, c_value, "YyNn", 'Y', is_group_case_sensitive, is_item_case_sensitive) > 0)
						cout << "�ҵ���\"" << group_name_wanted << "\"/��\"" << item_name_wanted << "\"��char�͵�ֵΪ[" << c_value << "/" << int(c_value) << "]." << endl; //��intֵ���㿴��
				}
				else if (item_type == "int") {
					int i_value;

					/* �Ȳ������ʹ�ã���ȱʡֵ���޺���Χ��������Сд�����С�������Сд������ */
					if (sCfg.item_get_int(group_name_wanted, item_name_wanted, i_value) > 0)
						cout << "�ҵ���" << group_name_wanted << "/��" << item_name_wanted << "��int�͵�ֵΪ[" << i_value << "]." << endl;
					else
						cout << "δ�ҵ���" << group_name_wanted << "/��" << item_name_wanted << "��int��ֵ����������/��Ŀ/���������Ƿ���ȷ." << endl;

					cout << endl;

					/* ��β����������ޡ���ȱʡֵ���������Ϊ��Ҫ--gcs��--ics�����Ĭ��ֵֻ�����ϣ�
					   ��������Ǵ�Сд���У���˾��Ϊ sCfg.item_get_int(group_name_wanted, item_name_wanted, i_value, -2, 100);	 */
					if (sCfg.item_get_int(group_name_wanted, item_name_wanted, i_value, -2, 100, DEFAULT_INT_VALUE, is_group_case_sensitive, is_item_case_sensitive) > 0)
						cout << "�ҵ���" << group_name_wanted << "/��" << item_name_wanted << "��int�͵�ֵΪ[" << i_value << "]." << endl;
					else
						cout << "δ�ҵ���" << group_name_wanted << "/��" << item_name_wanted << "��int��ֵ����������/��Ŀ/���������Ƿ���ȷ." << endl;

					cout << endl;

					/*  �������������ޡ���ȱʡֵ�����*/
					if (sCfg.item_get_int(group_name_wanted, item_name_wanted, i_value, -2, 100, 10, is_group_case_sensitive, is_item_case_sensitive) > 0)
						cout << "�ҵ���" << group_name_wanted << "/��" << item_name_wanted << "��int�͵�ֵΪ[" << i_value << "]." << endl;
				}
				else if (item_type == "double") {
					double d_value;

					/* �Ȳ������ʹ�ã���ȱʡֵ���޺���Χ��������Сд�����С�������Сд������ */
					if (sCfg.item_get_double(group_name_wanted, item_name_wanted, d_value) > 0)
						cout << "�ҵ���" << group_name_wanted << "/��" << item_name_wanted << "��double�͵�ֵΪ[" << d_value << "]." << endl;
					else
						cout << "δ�ҵ���" << group_name_wanted << "/��" << item_name_wanted << "��double��ֵ����������/��Ŀ/���������Ƿ���ȷ." << endl;

					cout << endl;

					/* ��β����������ޡ���ȱʡֵ���������Ϊ��Ҫ--gcs��--ics�����Ĭ��ֵֻ�����ϣ�
					   ��������Ǵ�Сд���У���˾��Ϊ sCfg.item_get_double(group_name_wanted, item_name_wanted, d_value, -31.1, +75.2);	 */
					if (sCfg.item_get_double(group_name_wanted, item_name_wanted, d_value, -31.1, +75.2, DEFAULT_DOUBLE_VALUE, is_group_case_sensitive, is_item_case_sensitive) > 0)
						cout << "�ҵ���" << group_name_wanted << "/��" << item_name_wanted << "��double�͵�ֵΪ[" << d_value << "]." << endl;
					else
						cout << "δ�ҵ���" << group_name_wanted << "/��" << item_name_wanted << "��double��ֵ����������/��Ŀ/���������Ƿ���ȷ." << endl;

					cout << endl;

					/*  �������������ޡ���ȱʡֵ�����*/
					if (sCfg.item_get_double(group_name_wanted, item_name_wanted, d_value, -31.1, +75.2, 1.2, is_group_case_sensitive, is_item_case_sensitive) > 0)
						cout << "�ҵ���" << group_name_wanted << "/��" << item_name_wanted << "��double�͵�ֵΪ[" << d_value << "]." << endl;
				}
				else if (item_type == "cstring") {
					char s_value[16];

					/* �Ȳ������ʹ�ã�����󳤶ȣ��Զ�ΪMAX_STRLEN������ȱʡֵ��������Сд�����С�������Сд������
					   ע�����ַ�ʽ��ֻҪֵ�����ݳ���15�ֽڣ�����Խ�磬����Խ��������ʲô���ܽ��ܣ�ĳЩ������Ҫ���Ժ����֣�������Ҫע�͵��������� */
					if (sCfg.item_get_cstring(group_name_wanted, item_name_wanted, s_value, MAX_STRLEN) > 0)
						cout << "�ҵ���" << group_name_wanted << "/��" << item_name_wanted << "��cstring�͵�ֵΪ[" << s_value << "]." << endl;
					else
						cout << "δ�ҵ���" << group_name_wanted << "/��" << item_name_wanted << "��cstring��ֵ����������/��Ŀ/���������Ƿ���ȷ." << endl;

					cout << endl;

					/* ��β�������󳤶ȡ���ȱʡֵ���������Ϊ��Ҫ--gcs��--ics�����Ĭ��ֵֻ�����ϣ�
					   ��������Ǵ�Сд���У���˾��Ϊ (sCfg.item_get_cstring(group_name_wanted, item_name_wanted, s_value, sizeof(s_value), "Hello");	 */
					if (sCfg.item_get_cstring(group_name_wanted, item_name_wanted, s_value, sizeof(s_value), DEFAULT_CSTRING_VALUE, is_group_case_sensitive, is_item_case_sensitive) > 0)
						cout << "�ҵ���" << group_name_wanted << "/��" << item_name_wanted << "��cstring�͵�ֵΪ[" << s_value << "]." << endl;
					else
						cout << "δ�ҵ���" << group_name_wanted << "/��" << item_name_wanted << "��cstring��ֵ����������/��Ŀ/���������Ƿ���ȷ." << endl;

					cout << endl;

					/*  ����������󳤶ȡ���ȱʡֵ�����*/
					if (sCfg.item_get_cstring(group_name_wanted, item_name_wanted, s_value, sizeof(s_value), "Hello", is_group_case_sensitive, is_item_case_sensitive) > 0)
						cout << "�ҵ���" << group_name_wanted << "/��" << item_name_wanted << "��cstring�͵�ֵΪ[" << s_value << "]." << endl;
				}
				else if (item_type == "string") {
					string str_value;

					/* �Ȳ������ʹ�ã���ȱʡֵ��������Сд�����С�������Сд������ */
					if (sCfg.item_get_string(group_name_wanted, item_name_wanted, str_value) > 0)
						cout << "�ҵ���" << group_name_wanted << "/��" << item_name_wanted << "��string�͵�ֵΪ[" << str_value << "]." << endl;
					else
						cout << "δ�ҵ���" << group_name_wanted << "/��" << item_name_wanted << "��string��ֵ����������/��Ŀ/���������Ƿ���ȷ." << endl;

					cout << endl;

					/*  �ٲ�����ȱʡֵ�����*/
					if (sCfg.item_get_string(group_name_wanted, item_name_wanted, str_value, "Tongji", is_group_case_sensitive, is_item_case_sensitive) > 0)
						cout << "�ҵ���" << group_name_wanted << "/��" << item_name_wanted << "��string�͵�ֵΪ[" << str_value << "]." << endl;
				}
				else if (item_type == "ip") {
					unsigned int ipaddr_value;

					/* �Ȳ������ʹ�ã���ȱʡֵ��������Сд�����С�������Сд������ */
					if (sCfg.item_get_ipaddr(group_name_wanted, item_name_wanted, ipaddr_value) > 0)
						cout << "�ҵ���" << group_name_wanted << "/��" << item_name_wanted << "��ipaddr�͵�ֵΪ[" << hex << ipaddr_value << dec << "]." << endl;
					else
						cout << "δ�ҵ���" << group_name_wanted << "/��" << item_name_wanted << "��ipaddr��ֵ����������/��Ŀ/���������Ƿ���ȷ." << endl;

					cout << endl;

					/*  �ٲ�����ȱʡֵ�������0xC0A801E6 = 192.168.1.230 */
					if (sCfg.item_get_ipaddr(group_name_wanted, item_name_wanted, ipaddr_value, 0xC0A801E6, is_group_case_sensitive, is_item_case_sensitive) > 0)
						cout << "�ҵ���" << group_name_wanted << "/��" << item_name_wanted << "��ipaddr�͵�ֵΪ[" << hex << ipaddr_value << dec << "]." << endl;
				}
				//���������ʲô��������ֱ���˳�
				cout << endl;
			}
		}
	}
#endif  //���ɲ��Խ���
	return 0;
}

/* �Ƽ������ɲ������(�½�һ��.bat�����������ݸ��ƹ�ȥ���ɣ�ע��Ҫ����ΪASNI�ַ���)

rem --------------------------------
rem	ȡָ�������ļ���������/����������
rem --------------------------------
test_readcfg --cfgfile httpd.conf
pause
test_readcfg --cfgfile httpd.conf --group all
pause
test_readcfg --cfgfile php.ini
pause
test_readcfg --cfgfile php.ini --group all
pause
test_readcfg --cfgfile my.cnf
pause
test_readcfg --cfgfile yzmond.conf
pause

rem --------------------------------------
rem 	ȡָ�������ļ���ָ�������������ԭʼ����
rem --------------------------------------
test_readcfg --cfgfile httpd.conf --group ""
pause
test_readcfg --cfgfile php.ini --group [MSSQL]
pause
test_readcfg --cfgfile php.ini --group [mssql]
pause
test_readcfg --cfgfile php.ini --group [MSSQL] --gcs
rem ��Сд���У������Ҳ���
test_readcfg --cfgfile php.ini --group [mssql] --gcs
pause
test_readcfg --cfgfile my.cnf --group ""
pause
test_readcfg --cfgfile my.cnf --group "[mysqld]"
pause
test_readcfg --cfgfile yzmond.conf --group "[���ݿ�]"
pause

rem ----------------------------------------------------------------------------------------------------------
rem	ȡָ�������ļ���ָ�����е�ָ������ظ���Ŀ��ֵ��ԭʼ���ݣ������� "��Ŀ�� =/�ո�/tab ֵ" ��ʽ��������Ҳ�����
rem ----------------------------------------------------------------------------------------------------------
test_readcfg --cfgfile php.ini --group [MSSQL] --item mssql.max_links
pause
test_readcfg --cfgfile php.ini --group [MSSQL] --gcs --item mssql.max_links
pause
test_readcfg --cfgfile php.ini --group [MSSQL] --gcs --item mssql.max_links --ics
pause
rem ���Ҳ���
test_readcfg --cfgfile php.ini --group [mssql] --gcs --item mssql.max_links
pause
rem ���Ҳ���
test_readcfg --cfgfile php.ini --group [MSSQL] --item mssql.MAX_links --ics
pause
rem ���Ҳ���
test_readcfg --cfgfile php.ini --group [mssql] --gcs --item mssql.max_links --ics
pause

rem httpd.conf �ķָ����ǿո񣬱��Ҳ���
test_readcfg --cfgfile httpd.conf --group "" --item EnableSendfile
pause
rem ָ���ָ���Ϊ�ո�/tab���ҵ�
test_readcfg --cfgfile httpd.conf --group "" --item EnableSendfile --brkchar space
pause
rem ָ���ָ���Ϊ�ո�/tab���ҳ���������ݣ��ⲻ�ǳ��������Ա������ȷ֪�������ļ��ĸ�ʽ��
test_readcfg --cfgfile php.ini --group [MSSQL] --item mssql.max_links --brkchar space
pause

rem --------------------------------------------------------------------------------------------------------------------------
rem	ȡָ�������ļ���ָ�����е�ָ������ظ���Ŀ��ֵ�������� "��Ŀ�� =/�ո�/tab ֵ" ��ʽ�������������Ҫƥ�䣬�����ƥ�䣬���ǳ����
rem		1��null��
rem  ע�����������Ƿ���� --gcs �� --ics
rem --------------------------------------------------------------------------------------------------------------------------
rem ��ȡ��
test_readcfg --cfgfile yzmond.conf --group [��������] --item �������� --type null
pause
rem ��ȡ��
test_readcfg --cfgfile yzmond.conf --group "[��������]" --item "��������" --type null
pause
rem ��ȡ��
test_readcfg --cfgfile php.ini --group [soap] --item soap.wsdl_cache_dir --type null
pause
rem ȡ����������һ�����Ե�item��һ����ĸ��
test_readcfg --cfgfile php.ini --group [soap] --item soap.wsdl_cache_di --type null
pause

rem --------------------------------------------------------------------------------------------------------------------------
rem	ȡָ�������ļ���ָ�����е�ָ������ظ���Ŀ��ֵ�������� "��Ŀ�� =/�ո�/tab ֵ" ��ʽ�������������Ҫƥ�䣬�����ƥ�䣬���ǳ����
rem		2��char��
rem  ע�����������Ƿ���� --gcs �� --ics
rem --------------------------------------------------------------------------------------------------------------------------
rem  ���ַ�ʽ����ȡ��y
test_readcfg --cfgfile yzmond.conf --group [��������] --item �������� --type char
pause
rem ǰ����ȡ������������ȡ��Ĭ��ֵY
test_readcfg --cfgfile php.ini --group [soap] --item soap.wsdl_cache_dir --type char
pause
rem ��һ��ȡ��9����Ϊ�����ַ����Ϸ������ڶ���ȡ��������Ϊ���ںϷ���������û��Ĭ��ֵ��������ȡ��Ĭ��ֵY
test_readcfg --cfgfile yzmond.conf --group [��������] --item �豸������� --type char
pause

rem --------------------------------------------------------------------------------------------------------------------------
rem	ȡָ�������ļ���ָ�����е�ָ������ظ���Ŀ��ֵ�������� "��Ŀ�� =/�ո�/tab ֵ" ��ʽ�������������Ҫƥ�䣬�����ƥ�䣬���ǳ����
rem		3��int��
rem  ע�����������Ƿ���� --gcs �� --ics
rem --------------------------------------------------------------------------------------------------------------------------
rem ���ַ�ʽ����ȡ��30
test_readcfg --cfgfile yzmond.conf --group [ϵͳ����] --item δӦ��ʱ --type int
pause
rem ��һ��ȡ��1000���ڶ���ȡ������������ȡ��Ĭ��ֵ10
test_readcfg --cfgfile yzmond.conf --group [ϵͳ����] --item ������󳤶� --type int
pause
rem �ҵ�������ָ�����󣬰�int�������־�ȡ��60
test_readcfg --cfgfile yzmond.conf --group [ϵͳ����] --item �ڴ�ʹ�ñ��� --type int
pause
rem ǰ����ȡ������������ȡ��Ĭ��ֵ10
test_readcfg --cfgfile php.ini --group [Tidy] --item tidy.clean_output --type int
pause

rem --------------------------------------------------------------------------------------------------------------------------
rem	ȡָ�������ļ���ָ�����е�ָ������ظ���Ŀ��ֵ�������� "��Ŀ�� =/�ո�/tab ֵ" ��ʽ�������������Ҫƥ�䣬�����ƥ�䣬���ǳ����
rem		4��double��
rem  ע�����������Ƿ���� --gcs �� --ics
rem --------------------------------------------------------------------------------------------------------------------------
rem ���ַ�ʽ����ȡ��60.5
test_readcfg --cfgfile yzmond.conf --group [ϵͳ����] --item �ڴ�ʹ�ñ��� --type double
pause
rem ���ַ�ʽ����ȡ��30����double��ʽ��int�Ǽ��ݵģ�
test_readcfg --cfgfile yzmond.conf --group [ϵͳ����] --item δӦ��ʱ --type double
pause
rem ��һ��ȡ��87.35���ڶ���ȡ������������ȡ��Ĭ��ֵ1.2
test_readcfg --cfgfile yzmond.conf --group [ϵͳ����] --item �ڴ���ر��� --type double
pause
rem ǰ����ȡ������������ȡ��Ĭ��ֵ1.2
test_readcfg --cfgfile php.ini --group [Tidy] --item tidy.clean_output --type double
pause
rem ǰ����ȡ������������ȡ��Ĭ��ֵ1.2
test_readcfg --cfgfile php.ini --group [soap] --item soap.wsdl_cache_dir --type double
pause

rem --------------------------------------------------------------------------------------------------------------------------
rem	ȡָ�������ļ���ָ�����е�ָ������ظ���Ŀ��ֵ�������� "��Ŀ�� =/�ո�/tab ֵ" ��ʽ�������������Ҫƥ�䣬�����ƥ�䣬���ǳ����
rem		5��cstring��
rem  ע�����������Ƿ���� --gcs �� --ics
rem --------------------------------------------------------------------------------------------------------------------------
rem ����ԭʼ���ݣ����ո�����У������ں�--type cstring�Ƚ�
test_readcfg --cfgfile httpd.conf --group "" --item DirectoryIndex --brkchar space
pause
rem ����ԭʼ���ݣ����ո�����У������ں�--type cstring�Ƚ�
test_readcfg --cfgfile httpd.conf --group "" --item DirectoryIndex --brkchar space --type raw
pause
rem ���ַ�ʽ����ȡ��index.html����һ���ո�ǰ�����ݣ�
test_readcfg --cfgfile httpd.conf --group "" --item DirectoryIndex --brkchar space --type cstring
pause

rem ���LogFormat��ֻ�ҵ�һ��������ԭʼ���ݣ����ո�����У������ں�--type cstring�Ƚ�
test_readcfg --cfgfile httpd.conf --group "" --item LogFormat --brkchar space
pause
rem ���LogFormat��ֻ�ҵ�һ�������ַ�ʽ����ȡ��"%h��δ��ת�����������ƥ�䣬��ȡ��һ���ո�ǰ�����ݣ�
test_readcfg --cfgfile httpd.conf --group "" --item LogFormat --brkchar space --type cstring
pause

rem ���AddType��ֻ�ҵ�һ��������ԭʼ���ݣ����ո�����У������ں�--type cstring�Ƚ�
test_readcfg --cfgfile httpd.conf --group "" --item AddType --brkchar space --type raw
pause
rem ���AddType��ֻ�ҵ�һ������һ�ַ�ʽ��Խ�磨��ʲô������֣�����һ�ַ�ʽע�ͺ󣬺����ַ�ʽ����ȡ������Ϊ15�Ĵ�
test_readcfg --cfgfile httpd.conf --group "" --item AddType --brkchar space --type cstring
pause

rem ǰ����ȡ������������ȡ��Ĭ��ֵHello
test_readcfg --cfgfile php.ini --group [soap] --item soap.wsdl_cache_dir --type cstring
pause

rem --------------------------------------------------------------------------------------------------------------------------
rem	ȡָ�������ļ���ָ�����е�ָ������ظ���Ŀ��ֵ�������� "��Ŀ�� =/�ո�/tab ֵ" ��ʽ�������������Ҫƥ�䣬�����ƥ�䣬���ǳ����
rem		6��string��
rem  ע�����������Ƿ���� --gcs �� --ics
rem --------------------------------------------------------------------------------------------------------------------------
rem ����ԭʼ���ݣ����ո�����У������ں�--type string�Ƚ�
test_readcfg --cfgfile httpd.conf --group "" --item DirectoryIndex --brkchar space
pause
rem ���ַ�ʽ����ȡ��index.html����һ���ո�ǰ�����ݣ�
test_readcfg --cfgfile httpd.conf --group "" --item DirectoryIndex --brkchar space --type string
pause

rem ���LogFormat��ֻ�ҵ�һ��������ԭʼ���ݣ����ո�����У������ں�--type string�Ƚ�
test_readcfg --cfgfile httpd.conf --group "" --item LogFormat --brkchar space
pause
rem ���LogFormat��ֻ�ҵ�һ�������ַ�ʽ����ȡ��"%h��δ��ת�����������ƥ�䣬��ȡ��һ���ո�ǰ�����ݣ�
test_readcfg --cfgfile httpd.conf --group "" --item LogFormat --brkchar space --type string
pause

rem ���AddType��ֻ�ҵ�һ��������ԭʼ���ݣ����ո�����У������ں�--type string�Ƚ�
test_readcfg --cfgfile httpd.conf --group "" --item AddType --brkchar space --type raw
pause
rem ���AddType��ֻ�ҵ�һ�������ַ�ʽ����ȡ����������application/x-compress
test_readcfg --cfgfile httpd.conf --group "" --item AddType --brkchar space --type string
pause

rem ��һ��ȡ�������ڶ���ȡ��Ĭ��ֵTongji
test_readcfg --cfgfile php.ini --group [soap] --item soap.wsdl_cache_dir --type string
pause

rem --------------------------------------------------------------------------------------------------------------------------
rem	ȡָ�������ļ���ָ�����е�ָ������ظ���Ŀ��ֵ�������� "��Ŀ�� =/�ո�/tab ֵ" ��ʽ�������������Ҫƥ�䣬�����ƥ�䣬���ǳ����
rem		7��IP��ַ
rem  ע�����������Ƿ���� --gcs �� --ics
rem --------------------------------------------------------------------------------------------------------------------------
rem ���ַ�ʽ����ȡ��192.9.200.214����ӡ����hex��c009c8d6��
test_readcfg --cfgfile yzmond.conf --group [���ݲɼ�����] --item ����IP��ַ --type ip
pause
rem ��һ��ȡ�������ڶ���ȡ��Ĭ��ֵ192.168.1.230��c0a801e6��
test_readcfg --cfgfile yzmond.conf --group [���ݿ�] --item ������IP��ַ --type ip
pause
rem ��һ��ȡ�������ڶ���ȡ��Ĭ��ֵ192.168.1.230��c0a801e6��
test_readcfg --cfgfile php.ini --group [soap] --item soap.wsdl_cache_dir --type ip

*/
