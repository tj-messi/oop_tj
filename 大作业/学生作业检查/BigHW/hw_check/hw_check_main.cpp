/*2351114 ������ �쿡��*/
#include "hw_check.h"
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
	const char* DEMO_STUNO = "2359999";

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
	const string Action_Name[] = {"base","firstline","secondline",""}; //Ҳ���Ը�����Ҫ������ͷ�ļ����Ա㹲�� 

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

	args_analyse_process(argc, argv, args, 0);

	//��������ֱ��usage��
	if (argc == 1)
	{
		usage(argv[0]);
		return 0;
	}

	//helpֱ��usage��
	if (args[0].existed())
	{
		usage(argv[0]);
		return 0;
	}

	//debug ��������б�--��return
	if (args[1].existed())
	{
		/* ��ӡ�����ķ������ */
		args_analyse_print(args);
		cout << endl;
	}

	//����Ĳ���
	if (!args[2].existed()) {
		usage(argv[0]);
		cout << "����[--action]����ָ��." << endl;
		return 0;
	}

	if (!args[3].existed()) {
		usage(argv[0]);
		cout << "����[--cno]����ָ��." << endl;
		return 0;
	}

	if (!args[4].existed()) {
		usage(argv[0]);
		cout << "����[--stu]����ָ��." << endl;
		return 0;
	}

	if (!args[5].existed()) {
		usage(argv[0]);
		cout << "����[--file]����ָ��." << endl;
		return 0;
	}

	//����[--chapter/--week]���ܳ�����[--file �����ļ���]ʱ.
	if ((args[6].existed()) && args[5].get_string() != "all") {
		usage(argv[0]);
		cout << "����[--chapter/--week]���ܳ�����[--file �����ļ���]ʱ." << endl;
		return 0;
	}

	if ((args[7].existed()) && args[5].get_string() != "all") {
		usage(argv[0]);
		cout << "����[--chapter/--week]���ܳ�����[--file �����ļ���]ʱ." << endl;
		return 0;
	}

	//HW_Check_SecondLine ֻ�����ȫ��ѧ��
	if (args[4].get_string() != "all" && args[2].get_string() == "secondline") {
		cout << "HW_Check_SecondLine ֻ�����ȫ��ѧ��" << endl;
		return 0;
	}

	//HW_Check_SecondLine ֻ����Ե��ļ�
	if (args[5].get_string() == "all" && args[2].get_string() == "secondline") {
		cout << "HW_Check_SecondLine ֻ����Ե��ļ�" << endl;
		return 0;
	}

	//ѧ��ѧ��û����λ
	if (args[4].get_string().length() != 7 && args[4].get_string()!= "all") {
		cout << "[--���ش���--] ��ȡ [--stu] ָ�����ļ�����." << endl;
		return 0;
	}

	//�ȶ�config
	config_file_tools cfg(args[9].get_string());
	//MySQL��������ݿ�
	string db_host, db_port, db_name, db_username,db_passwd,db_currterm;
	cfg.item_get_raw("[���ݿ�]", "db_host", db_host);
	cfg.item_get_raw("[���ݿ�]", "db_port", db_port);
	cfg.item_get_raw("[���ݿ�]", "db_name", db_name);
	cfg.item_get_raw("[���ݿ�]", "db_username", db_username);
	cfg.item_get_raw("[���ݿ�]", "db_passwd", db_passwd);
	cfg.item_get_raw("[���ݿ�]", "db_currterm", db_currterm);

	//cout << db_host << endl;
	//cout << db_port << endl;
	//cout << db_name << endl;
	//cout << db_username << endl;
	//cout << db_passwd << endl;
	//cout << db_currterm << endl;

	trimLine(db_host, "all");
	trimLine(db_port, "all");
	trimLine(db_name, "all");
	trimLine(db_username, "all");
	trimLine(db_passwd, "all");
	trimLine(db_currterm, "all");

	//�����ļ���source·��
	string src_rootdir;
	cfg.item_get_raw("[�ļ�Ŀ¼]", "src_rootdir", src_rootdir);

	trimLine(src_rootdir, "all");

	MYSQL* mysql_stu;
	MYSQL_RES* result_stu;
	MYSQL_ROW  row_stu;//ÿһ�ж���ɸѡ�õ�����
	/* ��ʼ�� mysql ������ʧ�ܷ���NULL */
	if ((mysql_stu = mysql_init(NULL)) == NULL) {
		cout << "mysql_init failed" << endl;
		return -1;
	}
	else {
		//cout << "initial_successfully!" << endl;
	}

	/* �������ݿ⣬ʧ�ܷ���NULL
		1��mysqldû����
		2��û��ָ�����Ƶ����ݿ���� */
	if (mysql_real_connect(mysql_stu, db_host.c_str(), db_username.c_str(), db_passwd.c_str(), db_name.c_str(), 0, NULL, 0) == NULL
		) {
		cout << "mysql_real_connect failed(" << mysql_error(mysql_stu) << ")" << endl;
		return -1;
	}
	else {
		//cout << "connect_successfully!" << endl;
	}

	/* �����ַ���������������ַ����� */
	mysql_set_character_set(mysql_stu, "gbk");

	//��ʼ��ѰѧУ���ݿ�
	string stuNo = args[4].get_string();
	string fileName = args[5].get_string();
	string cno = args[3].get_string();
	string cno2 = "";

	if (cno.find(",") != -1)//����������
	{
		cno2 = cno.substr(cno.find(",")+1);
		trimLine(cno2, "all");
		cno = cno.substr(0, cno.find(",") );
	}
	//cout << cno << " " << cno2 << endl;
	//
	//while (1)
	//{
	//	
	//}

	int max_len_name = 0;
	int cnt_stu = 0;
	//��һ�μ���
	{
		string searchName;
		if (stuNo != "all") {
			searchName = string("select * from view_hwcheck_stulist where stu_cno = ") + cno + (" and stu_no = ") + stuNo;
		}
		else {
			searchName = string("select * from view_hwcheck_stulist where stu_cno = ") + cno;
		}

		if (mysql_query(mysql_stu, searchName.c_str())) {
			cout << "mysql_query failed(" << mysql_error(mysql_stu) << ")" << endl;
			return -1;
		}
		if ((result_stu = mysql_store_result(mysql_stu)) == NULL) {
			cout << "mysql_store_result failed(" << mysql_error(mysql_stu) << ")" << endl;
			return -1;
		}
		while ((row_stu = mysql_fetch_row(result_stu)) != NULL) {
			max_len_name = max(max_len_name, (int)(((string)row_stu[3]).size()));
			string name = (string)row_stu[3];
			if (((string)row_stu[3]).find("��") != -1)
			{
				string sub1 = ((string)row_stu[3]).substr(0, ((string)row_stu[3]).find("��"));
				string sub2 = ((string)row_stu[3]).substr(((string)row_stu[3]).find("��") + 2);
				name = sub1 + '.' + sub2;

				//name[((string)row_stu[3]).find("��")] = '.';
			}

			//max_len_name = max(max_len_name, (int)(name.size()));
			cnt_stu++;
		}
		//mysql_free_result(result_stu);
	}
	//���ܵ����Ͽκ�
	if(cno2 != "")
	{
		string searchName;
		if (stuNo != "all") {
			searchName = string("select * from view_hwcheck_stulist where stu_cno = ") + cno2 + (" and stu_no = ") + stuNo;
		}
		else {
			searchName = string("select * from view_hwcheck_stulist where stu_cno = ") + cno2;
		}

		if (mysql_query(mysql_stu, searchName.c_str())) {
			cout << "mysql_query failed(" << mysql_error(mysql_stu) << ")" << endl;
			return -1;
		}
		if ((result_stu = mysql_store_result(mysql_stu)) == NULL) {
			cout << "mysql_store_result failed(" << mysql_error(mysql_stu) << ")" << endl;
			return -1;
		}
		while ((row_stu = mysql_fetch_row(result_stu)) != NULL) {
			max_len_name = max(max_len_name, (int)(((string)row_stu[3]).size()));
			string name = (string)row_stu[3];
			if (((string)row_stu[3]).find("��") != -1)
			{
				string sub1 = ((string)row_stu[3]).substr(0, ((string)row_stu[3]).find("��"));
				string sub2 = ((string)row_stu[3]).substr(((string)row_stu[3]).find("��") + 2);
				name = sub1 + '.' + sub2;

				//name[((string)row_stu[3]).find("��")] = '.';
			}
			
			cnt_stu++;
		}

		//mysql_free_result(result_stu);
	}


	//����stu-list �� hw-list
	//while ((row = mysql_fetch_row(result)) != NULL) {
	//	cout << setiosflags(ios::left);           //��������
	//	cout << "ke��" << setw(12) << row[0];    //���12λ�������
	//	cout << "nj��" << setw(8) << row[1];     //    8
	//	cout << "xh��" << setw(4) << row[2];     //    4
	//	cout << "xm��" << setw(4) << row[3];     //    4��Ŀǰ���ַ�����ʽ��Ҳ������atoi(row[3])���int�͵�����
	//	cout << "xb��" << setw(4) << row[4];     //    4
	//	cout << "zy��" << setw(4) << row[5];
	//	cout << "zy��" << setw(4) << row[6];
	//	cout << endl;
	//}
	//ke��2024 / 2025 / 1 nj��2023    xh��2351114xm���쿡��xb����  zy�����ݿ�ѧ������ݼ���zy��������
	//ke��99          nj��10108001xh��9902xm��99  xb��12  zy��help.pdfzy��0.0
	int cnt_correct_all = 0;
	int cnt_not_submit_all = 0;
	int cnt_not_GB_all = 0;
	int cnt_not_pdf_all = 0;
	int cnt_not_vs_all = 0;

	int cnt_first_not_define_all = 0;
	int cnt_first_not_3_all = 0;
	int cnt_first_error_all = 0;
	int cnt_first_multierror_all = 0;

	int cnt_second_not_define_all = 0;

	int cnt_file = 0;
	int cnt_stunum = 0;

	if (args[2].get_string() == "base")
	{
		if (fileName != "all")
			cout << "�κ� : " << args[3].get_string() << " ѧ������ : " << cnt_stu << " Դ�ļ��� : " << fileName << endl;
	}
	if (args[2].get_string() == "firstline")
	{
		if (fileName != "all")
			cout << "�κ� : " << args[3].get_string() << " ѧ������ : " << cnt_stu << " Դ�ļ��� : " << fileName << endl;
	}
	if (args[2].get_string() == "secondline")
	{
		if (fileName != "all")
			cout << "�κ� : " << args[3].get_string() << " ѧ������ : " << cnt_stu << " Դ�ļ��� : " << fileName << endl;
	}

	//��һ���༶��ѯ
	{
		string searchName;
		if (stuNo != "all") {
			searchName = string("select * from view_hwcheck_stulist where stu_cno = ") + cno + (" and stu_no = ") + stuNo;
		}
		else {
			searchName = string("select * from view_hwcheck_stulist where stu_cno = ") + cno;
		}

		if (mysql_query(mysql_stu, searchName.c_str())) {
			cout << "mysql_query failed(" << mysql_error(mysql_stu) << ")" << endl;
			return -1;
		}
		if ((result_stu = mysql_store_result(mysql_stu)) == NULL) {
			cout << "mysql_store_result failed(" << mysql_error(mysql_stu) << ")" << endl;
			return -1;
		}




		while ((row_stu = mysql_fetch_row(result_stu)) != NULL) {
			cnt_stunum++;
			//cout << row_stu[2] << endl;//ѧ��row[2]

			//�Ҷ�Ӧ�ļ�
			MYSQL* mysql_hw;
			MYSQL_RES* result_hw;
			MYSQL_ROW  row_hw;//ÿһ�ж���ɸѡ�õ�����
			/* ��ʼ�� mysql ������ʧ�ܷ���NULL */
			if ((mysql_hw = mysql_init(NULL)) == NULL) {
				cout << "mysql_init failed" << endl;
				return -1;
			}
			else {
				//cout << "initial_successfully!" << endl;
			}
			/* �������ݿ⣬ʧ�ܷ���NULL
			1��mysqldû����
			2��û��ָ�����Ƶ����ݿ���� */
			if (mysql_real_connect(mysql_hw, db_host.c_str(), db_username.c_str(), db_passwd.c_str(), db_name.c_str(), 0, NULL, 0) == NULL
				) {
				cout << "mysql_real_connect failed(" << mysql_error(mysql_hw) << ")" << endl;
				return -1;
			}
			else {
				//cout << "connect_successfully!" << endl;
			}

			/* �����ַ���������������ַ����� */
			mysql_set_character_set(mysql_hw, "gbk");

			string hwname;//ɸѡ����Ӧ�κŵ���ҵ�б�
			if (fileName != "all") {
				hwname = string("select * from view_hwcheck_hwlist where hw_cno = ") + cno;
			}
			else {
				hwname = string("select * from view_hwcheck_hwlist where hw_cno = ") + cno;
			}
			if (mysql_query(mysql_hw, hwname.c_str())) {
				cout << "mysql_query failed(" << mysql_error(mysql_hw) << ")" << endl;
				return -1;
			}
			if ((result_hw = mysql_store_result(mysql_hw)) == NULL) {
				cout << "mysql_store_result failed(" << mysql_error(mysql_hw) << ")" << endl;
				return -1;
			}
			int maxline_row_hw = 0;
			int cnt_hw = 0;
			while ((row_hw = mysql_fetch_row(result_hw)) != NULL) {
				//�½ں����ڵ�����
				if (args[6].existed())
				{
					if (to_string(args[6].get_int()) != row_hw[3])
						continue;
				}
				if (args[7].existed())
				{
					if (to_string(args[7].get_int()) != row_hw[4])
						continue;
				}
				if (args[2].get_string() == "firstline")
				{
					//ֻ��鲿���ļ�
					string extension = string(row_hw[5]).substr(string(row_hw[5]).find_last_of('.'));
					if (extension == ".h" || extension == ".hpp" || extension == ".cpp" || extension == ".c")
					{

					}
					else
						continue;
				}
				maxline_row_hw = max(maxline_row_hw, (int)((string)row_hw[5]).size());
				cnt_hw++;
			}
			maxline_row_hw++;
			//cout << maxline_row_hw << endl;

			if (fileName != "all") {
				hwname = string("select * from view_hwcheck_hwlist where hw_cno = ") + cno;
			}
			else {
				hwname = string("select * from view_hwcheck_hwlist where hw_cno = ") + cno;
			}
			if (mysql_query(mysql_hw, hwname.c_str())) {
				cout << "mysql_query failed(" << mysql_error(mysql_hw) << ")" << endl;
				return -1;
			}
			if ((result_hw = mysql_store_result(mysql_hw)) == NULL) {
				cout << "mysql_store_result failed(" << mysql_error(mysql_hw) << ")" << endl;
				return -1;
			}
			//���ÿһ���ļ���
			int cnt_hwnum = 0;
			int cnt_correct = 0;
			int cnt_not_submit = 0;
			int cnt_not_GB = 0;
			int cnt_not_pdf = 0;
			int cnt_not_vs = 0;
			int cnt_first_not_define = 0;
			int cnt_first_not_3 = 0;
			int cnt_first_error = 0;
			int cnt_first_multierror = 0;
			int cnt_second_not_define = 0;
			string name = (string)row_stu[3];
			if (((string)row_stu[3]).find("��") != -1)
			{
				string sub1 = ((string)row_stu[3]).substr(0, ((string)row_stu[3]).find("��"));
				string sub2 = ((string)row_stu[3]).substr(((string)row_stu[3]).find("��") + 2);
				name = sub1 + '.' + sub2;

				//name[((string)row_stu[3]).find("��")] = '.';
			}
			{
				if (args[2].get_string() == "base")
				{
					if (fileName == "all")
						cout << resetiosflags(ios::right) << setiosflags(ios::left) << setw(3) << cnt_stunum << ":" << " ѧ��-" << row_stu[2] << " ����-" << name << " �κ�-" << args[3].get_string() << " �ļ�����-" << cnt_hw << endl;
				}
				if (args[2].get_string() == "firstline")
				{
					if (fileName == "all")
						cout << resetiosflags(ios::right) << setiosflags(ios::left) << setw(3) << cnt_stunum << ":" << " ѧ��-" << row_stu[2] << " ����-" << name << " �κ�-" << args[3].get_string() << " �ļ�����-" << cnt_hw << endl;
				}
			}


			while ((row_hw = mysql_fetch_row(result_hw)) != NULL) {

				//�½ں����ڵ�����
				if (args[6].existed())
				{
					if (to_string(args[6].get_int()) != row_hw[3])
						continue;
				}
				if (args[7].existed())
				{
					if (to_string(args[7].get_int()) != row_hw[4])
						continue;
				}
				if (fileName != "all")
				{
					if (fileName != row_hw[5])
					{
						continue;
					}
				}
				if (args[2].get_string() == "firstline")
				{
					//ֻ��鲿���ļ�
					string extension = string(row_hw[5]).substr(string(row_hw[5]).find_last_of('.'));
					if (extension == ".h" || extension == ".hpp" || extension == ".cpp" || extension == ".c")
					{

					}
					else
						continue;
				}
				cnt_hwnum++;
				cnt_file++;
				string name = (string)row_stu[3];
				if (((string)row_stu[3]).find("��") != -1)
				{
					string sub1 = ((string)row_stu[3]).substr(0, ((string)row_stu[3]).find("��"));
					string sub2 = ((string)row_stu[3]).substr(((string)row_stu[3]).find("��") + 2);
					name = sub1 + '.' + sub2;

					//name[((string)row_stu[3]).find("��")] = '.';
				}
				//�������Ե��ļ�
				if (fileName != "all")
				{
					//base
					if (args[2].get_string() == "base")
					{
						cout << resetiosflags(ios::right) << setiosflags(ios::left) << setw(3) << cnt_file << ": " << row_stu[2] << "/" << resetiosflags(ios::right) << setiosflags(ios::left) << setw(max_len_name) << name << "  : ";
						Check result = checkfilebase(src_rootdir + cno + '-' + row_stu[2] + '/' + row_hw[5]);
						switch (result) {
							case FILE_NOT_FOUND:
								std::cout << "δ�ύ\n";
								cnt_not_submit++;
								cnt_not_submit_all++;
								break;
							case NOT_PDF:
								cnt_not_pdf++;
								 cnt_not_pdf_all++;
								std::cout << "PDF�ļ���ʽ����ȷ\n";
								break;
							case NOT_VS:
								cnt_not_vs++;
								cnt_not_vs_all++;
								std::cout << "Դ�ļ���ʽ����ȷ(VS�޷�ʶ��)\n";
								break;
							case CORRECT:
								std::cout << "��ȷ\n";
								cnt_correct++;
								cnt_correct_all++;
								break;
							case INVALID_ENCODING:
								cnt_not_GB++;
								cnt_not_GB_all++;
								std::cout << "Դ�ļ���ʽ����ȷ(��GB����)\n";
								break;
						}
					}
					//firstline
					if (args[2].get_string() == "firstline")
					{
						cout << resetiosflags(ios::right) << setiosflags(ios::left) << setw(3) << cnt_file << ": " << row_stu[2] << "/" << resetiosflags(ios::right) << setiosflags(ios::left) << setw(max_len_name) << name << "  : ";
						if (!fileExists(src_rootdir + cno + '-' + row_stu[2] + '/' + row_hw[5]))
						{
							std::cout << "δ�ύ\n";
							cnt_not_submit++;
							cnt_not_submit_all++;
							continue;
						}
						if (isUTF8(src_rootdir + cno + '-' + row_stu[2] + '/' + row_hw[5])) {
							cnt_not_GB++;
							cnt_not_GB_all++;
							std::cout << "Դ�ļ���ʽ����ȷ(��GB����)\n";
							continue;
						}
						if (checkvs(src_rootdir + cno + '-' + row_stu[2] + '/' + row_hw[5]))
						{
							cnt_not_vs++;
							cnt_not_vs_all++;
							std::cout << "Դ�ļ���ʽ����ȷ(VS�޷�ʶ��)\n";
							continue;
						}
						ifstream fin(src_rootdir + cno + '-' + row_stu[2] + '/' + row_hw[5]);
						string firstline;
						while (getline(fin, firstline)) {
							trimLine(firstline, "all");
							if (!firstline.empty()) {
								break;
							}
						}
						Check result = checkfilefirst(firstline, row_stu, row_stu[2], row_stu[3]);
						switch (result) {
							case FILE_NOT_FOUND:
								std::cout << "δ�ύ\n";
								cnt_not_submit++;
								cnt_not_submit_all++;
								break;
							case CORRECT:
								std::cout << "��ȷ\n";
								cnt_correct++;
								cnt_correct_all++;
								break;
							case INVALID_ENCODING:
								cnt_not_GB++;
								cnt_not_GB_all++;
								std::cout << "Դ�ļ���ʽ����ȷ(��GB����)\n";
								break;
							case FIRSTLINE_NOT_DEFINE:
								cnt_first_not_define++;
								cnt_first_not_define_all++;
								cout << "���в���ע���� [" << firstline << "]" << endl;
								break;
							case FIRSTLINE_NOT_3_ITEMS:
								cnt_first_not_3++;
								cnt_first_not_3_all++;
								cout << "���в������� [" << firstline << "]" << endl;
								break;
							case FIRSTLINE_ERROR:
								cnt_first_error++;
								cnt_first_error_all++;
								cout << " [" << firstline << "]" << endl;
								break;
							case FIRSTLINE_MULTIERROR:
								cnt_first_multierror++;
								cnt_first_multierror_all++;
								cout << "���в��Ƿ���Ҫ���/* */��ʽ [" << firstline << "]" << endl;
								break;
						}
					}
					//secondline
					if (args[2].get_string() == "secondline")
					{
						cout << resetiosflags(ios::right) << setiosflags(ios::left) << setw(3) << cnt_file << ": " << row_stu[2] << "/" << resetiosflags(ios::right) << setiosflags(ios::left) << setw(max_len_name) << name << " : ";
						if (!fileExists(src_rootdir + cno + '-' + row_stu[2] + '/' + row_hw[5]))
						{
							std::cout << "δ�ύ\n";
							cnt_not_submit++;
							cnt_not_submit_all++;
							continue;
						}
						if (isUTF8(src_rootdir + cno + '-' + row_stu[2] + '/' + row_hw[5])) {
							cnt_not_GB++;
							cnt_not_GB_all++;
							std::cout << "Դ�ļ���ʽ����ȷ(��GB����)\n";
							continue;
						}
						if (checkvs(src_rootdir + cno + '-' + row_stu[2] + '/' + row_hw[5]))
						{
							cnt_not_vs++;
							cnt_not_vs_all++;
							std::cout << "Դ�ļ���ʽ����ȷ(VS�޷�ʶ��)\n";
							continue;
						}
						ifstream fin(src_rootdir + cno + '-' + row_stu[2] + '/' + row_hw[5]);
						string secondline;
						while (getline(fin, secondline)) {
							trimLine(secondline, "all");
							if (!secondline.empty()) {
								break;
							}
						}
						while (getline(fin, secondline)) {
							trimLine(secondline, "all");
							if (!secondline.empty()) {
								break;
							}
						}//�õ��ڶ���
						Check result = checkfilesecond(secondline, row_stu[2]);
						switch (result) {
							case CORRECT:
								std::cout << "��ȷ\n";
								cnt_correct++;
								cnt_correct_all++;
								break;
							case NOT_DOUBLE:
								//std::cout << "��ȷ\n";
								cnt_correct++;
								cnt_correct_all++;
								break;
							case WRITE_SELF:
								cnt_correct++;
								cnt_correct_all++;
								break;
							case STU_NO_ERROR:
								cnt_correct++;
								cnt_correct_all++;
								break;
							case SECONDLINE_NOT_DEFINE:
								std::cout << "���в���ע��\n";
								cnt_second_not_define++;
								cnt_second_not_define_all++;
								break;
						}
					}
				}
				//�����all�ļ���ȫ��ִ��
				else
				{
					//base
					if (args[2].get_string() == "base")
					{
						cout << "  " << resetiosflags(ios::right) << setiosflags(ios::left) << setw(maxline_row_hw) << row_hw[5] << ": ";//�ļ���
						Check result = checkfilebase(src_rootdir + cno + '-' + row_stu[2] + '/' + row_hw[5]);
						//cout << src_rootdir + cno + '-' + stuNo + '/' + row_hw[5] << endl;
						switch (result) {
							case FILE_NOT_FOUND:
								std::cout << "δ�ύ\n";
								cnt_not_submit++;
								cnt_not_submit_all++;
								break;
							case NOT_VS:
								cnt_not_vs++;
								cnt_not_vs_all++;
								std::cout << "Դ�ļ���ʽ����ȷ(VS�޷�ʶ��)\n";
								break;
							case NOT_PDF:
								cnt_not_pdf++;
								cnt_not_pdf_all++;
								std::cout << "PDF�ļ���ʽ����ȷ\n";
								break;
							case CORRECT:
								std::cout << "��ȷ\n";
								cnt_correct++;
								cnt_correct_all++;
								break;
							case INVALID_ENCODING:
								cnt_not_GB++;
								cnt_not_GB_all++;
								std::cout << "Դ�ļ���ʽ����ȷ(��GB����)\n";
								break;
						}
					}
					//firstline
					if (args[2].get_string() == "firstline")
					{
						if (!fileExists(src_rootdir + cno + '-' + row_stu[2] + '/' + row_hw[5]))
						{
							cout << "  " << resetiosflags(ios::right) << setiosflags(ios::left) << setw(maxline_row_hw) << row_hw[5] << ": ";//�ļ���
							std::cout << "δ�ύ\n";
							cnt_not_submit++;
							cnt_not_submit_all++;
							continue;
						}
						if (isUTF8(src_rootdir + cno + '-' + row_stu[2] + '/' + row_hw[5])) {
							cout << "  " << resetiosflags(ios::right) << setiosflags(ios::left) << setw(maxline_row_hw) << row_hw[5] << ": ";//�ļ���
							cnt_not_GB++;
							cnt_not_GB_all++;
							std::cout << "Դ�ļ���ʽ����ȷ(��GB����)\n";
							continue;
						}
						if (checkvs(src_rootdir + cno + '-' + row_stu[2] + '/' + row_hw[5]))
						{
							cout << "  " << resetiosflags(ios::right) << setiosflags(ios::left) << setw(maxline_row_hw) << row_hw[5] << ": ";//�ļ���
							cnt_not_vs++;
							cnt_not_vs_all++;
							std::cout << "Դ�ļ���ʽ����ȷ(VS�޷�ʶ��)\n";
							continue;
						}
						ifstream fin(src_rootdir + cno + '-' + row_stu[2] + '/' + row_hw[5]);
						string firstline;
						while (getline(fin, firstline)) {
							trimLine(firstline, "all");
							if (!firstline.empty()) {
								break;
							}
						}
						cout << "  " << resetiosflags(ios::right) << setiosflags(ios::left) << setw(maxline_row_hw) << row_hw[5] << ": ";//�ļ���
						Check result = checkfilefirst(firstline, row_stu, row_stu[2], row_stu[3]);
						switch (result) {
							case FILE_NOT_FOUND:
								std::cout << "δ�ύ\n";
								cnt_not_submit++;
								cnt_not_submit_all++;
								break;
							case CORRECT:
								std::cout << "��ȷ\n";
								cnt_correct++;
								cnt_correct_all++;
								break;
							case INVALID_ENCODING:
								cnt_not_GB++;
								cnt_not_GB_all++;
								std::cout << "Դ�ļ���ʽ����ȷ(��GB����)\n";
								break;
							case FIRSTLINE_NOT_DEFINE:
								cnt_first_not_define++;
								cnt_first_not_define_all++;
								cout << "���в���ע���� [" << firstline << "]" << endl;
								break;
							case FIRSTLINE_NOT_3_ITEMS:
								cnt_first_not_3++;
								cnt_first_not_3_all++;
								cout << "���в������� [" << firstline << "]" << endl;
								break;
							case FIRSTLINE_ERROR:
								cnt_first_error++;
								cnt_first_error_all++;
								cout << " [" << firstline << "]" << endl;
								break;
							case FIRSTLINE_MULTIERROR:
								cnt_first_multierror++;
								cnt_first_multierror_all++;
								cout << "���в��Ƿ���Ҫ���/* */��ʽ [" << firstline << "]" << endl;
								break;
						}
					}
				}
			}
			if (args[2].get_string() == "base")
			{
				//�����ļ�base
				if (fileName == "all")
				{
					int width = 0;
					if (cnt_correct)
						width = max(width, 16);
					if (cnt_not_GB)
						width = max(38, width);
					if (cnt_not_submit)
						width = max(18,width);
					if (cnt_not_pdf)
						width = max(width, 29);
					if(cnt_not_vs)
						width = max(width, 40);
					if (cnt_correct == cnt_hwnum)
						cout << "ȫ��ͨ��" << cnt_correct << "/" << cnt_hwnum << "���ļ�������ͨ��" << cnt_correct << "��" << endl;
					else
						cout << "���ͨ��" << cnt_correct << "/" << cnt_hwnum << "���ļ�������ͨ��" << cnt_correct << "��" << endl;
					for (int i = 1; i <= width; i++)
						cout << "-";
					cout << endl;
					cout << "ѧ����ϸ��Ϣ" << endl;
					for (int i = 1; i <= width; i++)
						cout << "-";
					cout << endl;
					if (cnt_correct)
						cout << setw(width - 10) << resetiosflags(ios::right) << setiosflags(ios::right) << "��ȷ" << " : " << cnt_correct << endl;
					if (cnt_not_submit)
						cout << setw(width - 10) << resetiosflags(ios::right) << setiosflags(ios::right) << "δ�ύ" << " : " << cnt_not_submit << endl;
					if (cnt_not_pdf)
						cout << setw(width - 10) << resetiosflags(ios::right) << setiosflags(ios::right) << "PDF�ļ���ʽ����ȷ" << " : " << cnt_not_pdf << endl;
					if (cnt_not_vs)
						cout << setw(width - 10) << resetiosflags(ios::right) << setiosflags(ios::right) << "Դ�ļ���ʽ����ȷ(VS�޷�ʶ��)" << " : " << cnt_not_vs << endl;
					if (cnt_not_GB)
						cout << setw(width - 10) << resetiosflags(ios::right) << setiosflags(ios::right) << "Դ�ļ���ʽ����ȷ(��GB����)" << " : " << cnt_not_GB << endl;
					for (int i = 1; i <= width; i++)
						cout << "-";
					cout << endl;
					cout << endl;
				}
				//�����ļ�base
				else
				{

				}
			}
			if (args[2].get_string() == "firstline")
			{
				if (fileName == "all")
				{
					int width = 0;
					if (cnt_correct)
						width = max(width, 16);
					if (cnt_not_GB)
						width = max(38, width);
					if (cnt_first_multierror)
						width = max(34, width);
					if (cnt_not_submit)
						width = max(18, width);
					if (cnt_correct)
						width = max(16, width);
					if (cnt_first_not_define)
						width = max(26, width);
					if (cnt_first_not_3)
						width = max(24, width);
					if (cnt_first_error)
						width = max(24, width);
					if (cnt_not_vs)
						width = max(width, 40);
					if (cnt_correct == cnt_hwnum)
						cout << "ȫ��ͨ��" << cnt_correct << "/" << cnt_hwnum << "���ļ�������ͨ��" << cnt_correct << "��" << endl;
					else
						cout << "���ͨ��" << cnt_correct << "/" << cnt_hwnum << "���ļ�������ͨ��" << cnt_correct << "��" << endl;
					for (int i = 1; i <= width; i++)
						cout << "-";
					cout << endl;
					cout << "ѧ����ϸ��Ϣ" << endl;
					for (int i = 1; i <= width; i++)
						cout << "-";
					cout << endl;
					if (cnt_correct)
						cout << setw(width - 10) << resetiosflags(ios::right) << setiosflags(ios::right) << "��ȷ" << " : " << cnt_correct << endl;
					if (cnt_not_submit)
						cout << setw(width - 10) << resetiosflags(ios::right) << setiosflags(ios::right) << "δ�ύ" << " : " << cnt_not_submit << endl;
					if (cnt_not_vs)
						cout << setw(width - 10) << resetiosflags(ios::right) << setiosflags(ios::right) << "Դ�ļ���ʽ����ȷ(VS�޷�ʶ��)" << " : " << cnt_not_vs << endl;
					if (cnt_not_GB)
						cout << setw(width - 10) << resetiosflags(ios::right) << setiosflags(ios::right) << "Դ�ļ���ʽ����ȷ(��GB����)" << " : " << cnt_not_GB << endl;
					if (cnt_first_multierror)
						cout << setw(width - 10) << resetiosflags(ios::right) << setiosflags(ios::right) << "���ж���ע�͸�ʽ����ȷ" << " : " << cnt_first_multierror << endl;
					if (cnt_first_not_define)
						cout << setw(width - 10) << resetiosflags(ios::right) << setiosflags(ios::right) << "���в���ע����" << " : " << cnt_first_not_define << endl;
					if (cnt_first_not_3)
						cout << setw(width - 10) << resetiosflags(ios::right) << setiosflags(ios::right) << "���в�������" << " : " << cnt_first_not_3 << endl;
					if (cnt_first_error)
						cout << setw(width - 10) << resetiosflags(ios::right) << setiosflags(ios::right) << "���м�����" << " : " << cnt_first_error << endl;
					for (int i = 1; i <= width; i++)
						cout << "-";
					cout << endl;
					cout << endl;
				}
				else
				{

				}
			}
			//cout << endl << cnt_hw << endl;
			/* �ͷ�result������ᶪʧ�ڴ� */
			mysql_free_result(result_hw);
			/* �ر��������� */
			mysql_close(mysql_hw);
		}
		/* �ͷ�result������ᶪʧ�ڴ� */
		mysql_free_result(result_stu);
	}
	//�ڶ������ϰ༶��ѯ
	if (cno2 != "")
	{
		string searchName;
		if (stuNo != "all") {
			searchName = string("select * from view_hwcheck_stulist where stu_cno = ") + cno2 + (" and stu_no = ") + stuNo;
		}
		else {
			searchName = string("select * from view_hwcheck_stulist where stu_cno = ") + cno2;
		}

		if (mysql_query(mysql_stu, searchName.c_str())) {
			cout << "mysql_query failed(" << mysql_error(mysql_stu) << ")" << endl;
			return -1;
		}
		if ((result_stu = mysql_store_result(mysql_stu)) == NULL) {
			cout << "mysql_store_result failed(" << mysql_error(mysql_stu) << ")" << endl;
			return -1;
		}




		while ((row_stu = mysql_fetch_row(result_stu)) != NULL) {
			cnt_stunum++;
			//cout << row_stu[2] << endl;//ѧ��row[2]

			//�Ҷ�Ӧ�ļ�
			MYSQL* mysql_hw;
			MYSQL_RES* result_hw;
			MYSQL_ROW  row_hw;//ÿһ�ж���ɸѡ�õ�����
			/* ��ʼ�� mysql ������ʧ�ܷ���NULL */
			if ((mysql_hw = mysql_init(NULL)) == NULL) {
				cout << "mysql_init failed" << endl;
				return -1;
			}
			else {
				//cout << "initial_successfully!" << endl;
			}
			/* �������ݿ⣬ʧ�ܷ���NULL
			1��mysqldû����
			2��û��ָ�����Ƶ����ݿ���� */
			if (mysql_real_connect(mysql_hw, db_host.c_str(), db_username.c_str(), db_passwd.c_str(), db_name.c_str(), 0, NULL, 0) == NULL
				) {
				cout << "mysql_real_connect failedhw(" << mysql_error(mysql_hw) << ")" << endl;
				return -1;
			}
			else {
				//cout << "connect_successfully!" << endl;
			}

			/* �����ַ���������������ַ����� */
			mysql_set_character_set(mysql_hw, "gbk");

			string hwname;//ɸѡ����Ӧ�κŵ���ҵ�б�
			if (fileName != "all") {
				hwname = string("select * from view_hwcheck_hwlist where hw_cno = ") + cno2;
			}
			else {
				hwname = string("select * from view_hwcheck_hwlist where hw_cno = ") + cno2;
			}
			if (mysql_query(mysql_hw, hwname.c_str())) {
				cout << "mysql_query failed(" << mysql_error(mysql_hw) << ")" << endl;
				return -1;
			}
			if ((result_hw = mysql_store_result(mysql_hw)) == NULL) {
				cout << "mysql_store_result failed(" << mysql_error(mysql_hw) << ")" << endl;
				return -1;
			}
			int maxline_row_hw = 0;
			int cnt_hw = 0;
			while ((row_hw = mysql_fetch_row(result_hw)) != NULL) {
				//�½ں����ڵ�����
				if (args[6].existed())
				{
					if (to_string(args[6].get_int()) != row_hw[3])
						continue;
				}
				if (args[7].existed())
				{
					if (to_string(args[7].get_int()) != row_hw[4])
						continue;
				}
				if (args[2].get_string() == "firstline")
				{
					//ֻ��鲿���ļ�
					string extension = string(row_hw[5]).substr(string(row_hw[5]).find_last_of('.'));
					if (extension == ".h" || extension == ".hpp" || extension == ".cpp" || extension == ".c")
					{

					}
					else
						continue;
				}
				maxline_row_hw = max(maxline_row_hw, (int)((string)row_hw[5]).size());
				cnt_hw++;
			}
			maxline_row_hw++;
			//cout << maxline_row_hw << endl;

			if (fileName != "all") {
				hwname = string("select * from view_hwcheck_hwlist where hw_cno = ") + cno2;
			}
			else {
				hwname = string("select * from view_hwcheck_hwlist where hw_cno = ") + cno2;
			}
			if (mysql_query(mysql_hw, hwname.c_str())) {
				cout << "mysql_query failed(" << mysql_error(mysql_hw) << ")" << endl;
				return -1;
			}
			if ((result_hw = mysql_store_result(mysql_hw)) == NULL) {
				cout << "mysql_store_result failed(" << mysql_error(mysql_hw) << ")" << endl;
				return -1;
			}
			//���ÿһ���ļ���
			int cnt_hwnum = 0;
			int cnt_correct = 0;
			int cnt_not_submit = 0;
			int cnt_not_GB = 0;
			int cnt_not_pdf = 0;
			int cnt_not_vs = 0;
			int cnt_first_not_define = 0;
			int cnt_first_not_3 = 0;
			int cnt_first_error = 0;
			int cnt_first_multierror = 0;

			int cnt_second_not_define = 0;
			string name = (string)row_stu[3];
			if (((string)row_stu[3]).find("��") != -1)
			{
				string sub1 = ((string)row_stu[3]).substr(0, ((string)row_stu[3]).find("��"));
				string sub2 = ((string)row_stu[3]).substr(((string)row_stu[3]).find("��") + 2);
				name = sub1 + '.' + sub2;

				//name[((string)row_stu[3]).find("��")] = '.';
			}
			{
				if (args[2].get_string() == "base")
				{
					if (fileName == "all")
						cout << resetiosflags(ios::right) << setiosflags(ios::left) << setw(3) << cnt_stunum << ":" << " ѧ��-" << row_stu[2] << " ����-" << name << " �κ�-" << args[3].get_string() << " �ļ�����-" << cnt_hw << endl;
				}
				if (args[2].get_string() == "firstline")
				{
					if (fileName == "all")
						cout << resetiosflags(ios::right) << setiosflags(ios::left) << setw(3) << cnt_stunum << ":" << " ѧ��-" << row_stu[2] << " ����-" << name << " �κ�-" << args[3].get_string() << " �ļ�����-" << cnt_hw << endl;
				}
			}


			while ((row_hw = mysql_fetch_row(result_hw)) != NULL) {

				//�½ں����ڵ�����
				if (args[6].existed())
				{
					if (to_string(args[6].get_int()) != row_hw[3])
						continue;
				}
				if (args[7].existed())
				{
					if (to_string(args[7].get_int()) != row_hw[4])
						continue;
				}
				if (fileName != "all")
				{
					if (fileName != row_hw[5])
					{
						continue;
					}
				}
				if (args[2].get_string() == "firstline")
				{
					//ֻ��鲿���ļ�
					string extension = string(row_hw[5]).substr(string(row_hw[5]).find_last_of('.'));
					if (extension == ".h" || extension == ".hpp" || extension == ".cpp" || extension == ".c")
					{

					}
					else
						continue;
				}
				cnt_hwnum++;
				cnt_file++;
				//�������Ե��ļ�
				if (fileName != "all")
				{
					//base
					if (args[2].get_string() == "base")
					{
						cout << resetiosflags(ios::right) << setiosflags(ios::left) << setw(3) << cnt_file << ": " << row_stu[2] << "/" << resetiosflags(ios::right) << setiosflags(ios::left) << setw(max_len_name) << name << "  : ";
						Check result = checkfilebase(src_rootdir + cno2 + '-' + row_stu[2] + '/' + row_hw[5]);
						switch (result) {
							case FILE_NOT_FOUND:
								std::cout << "δ�ύ\n";
								cnt_not_submit++;
								cnt_not_submit_all++;
								break;
							case NOT_VS:
								cnt_not_vs++;
								cnt_not_vs_all++;
								std::cout << "Դ�ļ���ʽ����ȷ(VS�޷�ʶ��)\n";
								break;
							case NOT_PDF:
								cnt_not_pdf++;
								cnt_not_pdf_all++;
								std::cout << "PDF�ļ���ʽ����ȷ\n";
								break;
							case CORRECT:
								std::cout << "��ȷ\n";
								cnt_correct++;
								cnt_correct_all++;
								break;
							case INVALID_ENCODING:
								cnt_not_GB++;
								cnt_not_GB_all++;
								std::cout << "Դ�ļ���ʽ����ȷ(��GB����)\n";
								break;
						}
					}
					//firstline
					if (args[2].get_string() == "firstline")
					{
						cout << resetiosflags(ios::right) << setiosflags(ios::left) << setw(3) << cnt_file << ": " << row_stu[2] << "/" << resetiosflags(ios::right) << setiosflags(ios::left) << setw(max_len_name) << name << "  : ";
						if (!fileExists(src_rootdir + cno2 + '-' + row_stu[2] + '/' + row_hw[5]))
						{
							std::cout << "δ�ύ\n";
							cnt_not_submit++;
							cnt_not_submit_all++;
							continue;
						}
						if (isUTF8(src_rootdir + cno2 + '-' + row_stu[2] + '/' + row_hw[5])) {
							cnt_not_GB++;
							cnt_not_GB_all++;
							std::cout << "Դ�ļ���ʽ����ȷ(��GB����)\n";
							continue;
						}
						if (checkvs(src_rootdir + cno2 + '-' + row_stu[2] + '/' + row_hw[5]))
						{
							cnt_not_vs++;
							cnt_not_vs_all++;
							std::cout << "Դ�ļ���ʽ����ȷ(VS�޷�ʶ��)\n";
							continue;
						}
						ifstream fin(src_rootdir + cno2 + '-' + row_stu[2] + '/' + row_hw[5]);
						string firstline;
						while (getline(fin, firstline)) {
							trimLine(firstline, "all");
							if (!firstline.empty()) {
								break;
							}
						}
						Check result = checkfilefirst(firstline, row_stu, row_stu[2], row_stu[3]);
						switch (result) {
							case FILE_NOT_FOUND:
								std::cout << "δ�ύ\n";
								cnt_not_submit++;
								cnt_not_submit_all++;
								break;
							case CORRECT:
								std::cout << "��ȷ\n";
								cnt_correct++;
								cnt_correct_all++;
								break;
							case INVALID_ENCODING:
								cnt_not_GB++;
								cnt_not_GB_all++;
								std::cout << "Դ�ļ���ʽ����ȷ(��GB����)\n";
								break;
							case FIRSTLINE_NOT_DEFINE:
								cnt_first_not_define++;
								cnt_first_not_define_all++;
								cout << "���в���ע���� [" << firstline << "]" << endl;
								break;
							case FIRSTLINE_NOT_3_ITEMS:
								cnt_first_not_3++;
								cnt_first_not_3_all++;
								cout << "���в������� [" << firstline << "]" << endl;
								break;
							case FIRSTLINE_ERROR:
								cnt_first_error++;
								cnt_first_error_all++;
								cout << " [" << firstline << "]" << endl;
								break;
							case FIRSTLINE_MULTIERROR:
								cnt_first_multierror++;
								cnt_first_multierror_all++;
								cout << "���в��Ƿ���Ҫ���/* */��ʽ [" << firstline << "]" << endl;
								break;
						}
					}
					if (args[2].get_string() == "secondline")
					{
						cout << resetiosflags(ios::right) << setiosflags(ios::left) << setw(3) << cnt_file << ": " << row_stu[2] << "/" << resetiosflags(ios::right) << setiosflags(ios::left) << setw(max_len_name) << name << " : ";
						if (!fileExists(src_rootdir + cno2 + '-' + row_stu[2] + '/' + row_hw[5]))
						{
							std::cout << "δ�ύ\n";
							cnt_not_submit++;
							cnt_not_submit_all++;
							continue;
						}
						if (isUTF8(src_rootdir + cno2 + '-' + row_stu[2] + '/' + row_hw[5])) {
							cnt_not_GB++;
							cnt_not_GB_all++;
							std::cout << "Դ�ļ���ʽ����ȷ(��GB����)\n";
							continue;
						}
						if (checkvs(src_rootdir + cno2 + '-' + row_stu[2] + '/' + row_hw[5]))
						{
							cnt_not_vs++;
							cnt_not_vs_all++;
							std::cout << "Դ�ļ���ʽ����ȷ(VS�޷�ʶ��)\n";
							continue;
						}
						ifstream fin(src_rootdir + cno2 + '-' + row_stu[2] + '/' + row_hw[5]);
						string secondline;
						while (getline(fin, secondline)) {
							trimLine(secondline, "all");
							if (!secondline.empty()) {
								break;
							}
						}
						while (getline(fin, secondline)) {
							trimLine(secondline, "all");
							if (!secondline.empty()) {
								break;
							}
						}//�õ��ڶ���
						Check result = checkfilesecond(secondline, row_stu[2]);
						switch (result) {
							case CORRECT:
								std::cout << "��ȷ\n";
								cnt_correct++;
								cnt_correct_all++;
								break;
							case NOT_DOUBLE:
								//std::cout << "��ȷ\n";
								cnt_correct++;
								cnt_correct_all++;
								break;
							case WRITE_SELF:
								cnt_correct++;
								cnt_correct_all++;
								break;
							case STU_NO_ERROR:
								cnt_correct++;
								cnt_correct_all++;
								break;
							case SECONDLINE_NOT_DEFINE:
								std::cout << "���в���ע��\n";
								cnt_second_not_define++;
								cnt_second_not_define_all++;
								break;
						}
					}
				}
				else//�����all�ļ���ȫ��ִ��
				{
					//base
					if (args[2].get_string() == "base")
					{
						cout << "  " << resetiosflags(ios::right) << setiosflags(ios::left) << setw(maxline_row_hw) << row_hw[5] << ": ";//�ļ���
						Check result = checkfilebase(src_rootdir + cno2 + '-' + row_stu[2] + '/' + row_hw[5]);
						//cout << src_rootdir + cno + '-' + stuNo + '/' + row_hw[5] << endl;
						switch (result) {
							case FILE_NOT_FOUND:
								std::cout << "δ�ύ\n";
								cnt_not_submit++;
								cnt_not_submit_all++;
								break;
							case NOT_VS:
								cnt_not_vs++;
								cnt_not_vs_all++;
								std::cout << "Դ�ļ���ʽ����ȷ(VS�޷�ʶ��)\n";
							case NOT_PDF:
								cnt_not_pdf++;
								cnt_not_pdf_all++;
								std::cout << "PDF�ļ���ʽ����ȷ\n";
								break;
							case CORRECT:
								std::cout << "��ȷ\n";
								cnt_correct++;
								cnt_correct_all++;
								break;
							case INVALID_ENCODING:
								cnt_not_GB++;
								cnt_not_GB_all++;
								std::cout << "Դ�ļ���ʽ����ȷ(��GB����)\n";
								break;
						}
					}
					//firstline
					if (args[2].get_string() == "firstline")
					{
						if (!fileExists(src_rootdir + cno2 + '-' + row_stu[2] + '/' + row_hw[5]))
						{
							cout << "  " << resetiosflags(ios::right) << setiosflags(ios::left) << setw(maxline_row_hw) << row_hw[5] << ": ";//�ļ���
							std::cout << "δ�ύ\n";
							cnt_not_submit++;
							cnt_not_submit_all++;
							continue;
						}
						if (isUTF8(src_rootdir + cno2 + '-' + row_stu[2] + '/' + row_hw[5])) {
							cout << "  " << resetiosflags(ios::right) << setiosflags(ios::left) << setw(maxline_row_hw) << row_hw[5] << ": ";//�ļ���
							cnt_not_GB++;
							cnt_not_GB_all++;
							std::cout << "Դ�ļ���ʽ����ȷ(��GB����)\n";
							continue;
						}
						if (checkvs(src_rootdir + cno2 + '-' + row_stu[2] + '/' + row_hw[5]))
						{
							cnt_not_vs++;
							cnt_not_vs_all++;
							std::cout << "Դ�ļ���ʽ����ȷ(VS�޷�ʶ��)\n";
							continue;
						}
						ifstream fin(src_rootdir + cno2 + '-' + row_stu[2] + '/' + row_hw[5]);
						string firstline;
						while (getline(fin, firstline)) {
							trimLine(firstline, "all");
							if (!firstline.empty()) {
								break;
							}
						}
						cout << "  " << resetiosflags(ios::right) << setiosflags(ios::left) << setw(maxline_row_hw) << row_hw[5] << ": ";//�ļ���
						Check result = checkfilefirst(firstline, row_stu, row_stu[2], row_stu[3]);
						switch (result) {
							case FILE_NOT_FOUND:
								std::cout << "δ�ύ\n";
								cnt_not_submit++;
								cnt_not_submit_all++;
								break;
							case CORRECT:
								std::cout << "��ȷ\n";
								cnt_correct++;
								cnt_correct_all++;
								break;
							case INVALID_ENCODING:
								cnt_not_GB++;
								cnt_not_GB_all++;
								std::cout << "Դ�ļ���ʽ����ȷ(��GB����)\n";
								break;
							case FIRSTLINE_NOT_DEFINE:
								cnt_first_not_define++;
								cnt_first_not_define_all++;
								cout << "���в���ע���� [" << firstline << "]" << endl;
								break;
							case FIRSTLINE_NOT_3_ITEMS:
								cnt_first_not_3++;
								cnt_first_not_3_all++;
								cout << "���в������� [" << firstline << "]" << endl;
								break;
							case FIRSTLINE_ERROR:
								cnt_first_error++;
								cnt_first_error_all++;
								cout << " [" << firstline << "]" << endl;
								break;
							case FIRSTLINE_MULTIERROR:
								cnt_first_multierror++;
								cnt_first_multierror_all++;
								cout << "���в��Ƿ���Ҫ���/* */��ʽ [" << firstline << "]" << endl;
								break;
						}
					}
				}
			}
			if (args[2].get_string() == "base")
			{
				//�����ļ�base
				if (fileName == "all")
				{
					int width = 0;
					if (cnt_correct)
						width = max(width, 16);
					if (cnt_not_GB)
						width = max(38, width);
					if (cnt_not_submit)
						width = max(18, width);
					if (cnt_not_pdf)
						width = max(width, 29);
					if (cnt_not_vs)
						width = max(width, 40);
					if (cnt_correct == cnt_hwnum)
						cout << "ȫ��ͨ��" << cnt_correct << "/" << cnt_hwnum << "���ļ�������ͨ��" << cnt_correct << "��" << endl;
					else
						cout << "���ͨ��" << cnt_correct << "/" << cnt_hwnum << "���ļ�������ͨ��" << cnt_correct << "��" << endl;
					for (int i = 1; i <= width; i++)
						cout << "-";
					cout << endl;
					cout << "ѧ����ϸ��Ϣ" << endl;
					for (int i = 1; i <= width; i++)
						cout << "-";
					cout << endl;
					if (cnt_correct)
						cout << setw(width - 10) << resetiosflags(ios::right) << setiosflags(ios::right) << "��ȷ" << " : " << cnt_correct << endl;
					if (cnt_not_submit)
						cout << setw(width - 10) << resetiosflags(ios::right) << setiosflags(ios::right) << "δ�ύ" << " : " << cnt_not_submit << endl;
					if (cnt_not_pdf)
						cout << setw(width - 10) << resetiosflags(ios::right) << setiosflags(ios::right) << "PDF�ļ���ʽ����ȷ" << " : " << cnt_not_pdf << endl;
					if (cnt_not_vs)
						cout << setw(width - 10) << resetiosflags(ios::right) << setiosflags(ios::right) << "Դ�ļ���ʽ����ȷ(VS�޷�ʶ��)" << " : " << cnt_not_vs << endl;
					if (cnt_not_GB)
						cout << setw(width - 10) << resetiosflags(ios::right) << setiosflags(ios::right) << "Դ�ļ���ʽ����ȷ(��GB����)" << " : " << cnt_not_GB << endl;
					for (int i = 1; i <= width; i++)
						cout << "-";
					cout << endl;
					cout << endl;
				}
				//�����ļ�base
				else
				{

				}
			}
			if (args[2].get_string() == "firstline")
			{
				if (fileName == "all")
				{
					int width = 0;
					if (cnt_correct)
						width = max(width, 16);
					if (cnt_not_GB)
						width = max(38, width);
					if (cnt_first_multierror)
						width = max(34, width);
					if (cnt_not_submit)
						width = max(18, width);
					if (cnt_correct)
						width = max(16, width);
					if (cnt_first_not_define)
						width = max(26, width);
					if (cnt_first_not_3)
						width = max(24, width);
					if (cnt_first_error)
						width = max(24, width);
					if (cnt_not_vs_all)
						width = max(width, 40);
					if(cnt_correct== cnt_hwnum)
						cout << "ȫ��ͨ��" << cnt_correct << "/" << cnt_hwnum << "���ļ�������ͨ��" << cnt_correct << "��" << endl;
					else
						cout << "���ͨ��" << cnt_correct << "/" << cnt_hwnum << "���ļ�������ͨ��" << cnt_correct << "��" << endl;
					for (int i = 1; i <= width; i++)
						cout << "-";
					cout << endl;
					cout << "ѧ����ϸ��Ϣ" << endl;
					for (int i = 1; i <= width; i++)
						cout << "-";
					cout << endl;
					if (cnt_correct)
						cout << setw(width - 10) << resetiosflags(ios::right) << setiosflags(ios::right) << "��ȷ" << " : " << cnt_correct << endl;
					if (cnt_not_submit)
						cout << setw(width - 10) << resetiosflags(ios::right) << setiosflags(ios::right) << "δ�ύ" << " : " << cnt_not_submit << endl;
					if (cnt_not_vs)
						cout << setw(width - 10) << resetiosflags(ios::right) << setiosflags(ios::right) << "Դ�ļ���ʽ����ȷ(VS�޷�ʶ��)" << " : " << cnt_not_vs << endl;
					if (cnt_not_GB)
						cout << setw(width - 10) << resetiosflags(ios::right) << setiosflags(ios::right) << "Դ�ļ���ʽ����ȷ(��GB����)" << " : " << cnt_not_GB << endl;
					if (cnt_first_multierror)
						cout << setw(width - 10) << resetiosflags(ios::right) << setiosflags(ios::right) << "���ж���ע�͸�ʽ����ȷ" << " : " << cnt_first_multierror << endl;
					if (cnt_first_not_define)
						cout << setw(width - 10) << resetiosflags(ios::right) << setiosflags(ios::right) << "���в���ע����" << " : " << cnt_first_not_define << endl;
					if (cnt_first_not_3)
						cout << setw(width - 10) << resetiosflags(ios::right) << setiosflags(ios::right) << "���в�������" << " : " << cnt_first_not_3 << endl;
					if (cnt_first_error)
						cout << setw(width - 10) << resetiosflags(ios::right) << setiosflags(ios::right) << "���м�����" << " : " << cnt_first_error << endl;
					for (int i = 1; i <= width; i++)
						cout << "-";
					cout << endl;
					cout << endl;
				}
				else
				{

				}
			}

			//cout << endl << cnt_hw << endl;
			/* �ͷ�result������ᶪʧ�ڴ� */
			mysql_free_result(result_hw);
			/* �ر��������� */
			mysql_close(mysql_hw);
		}
		/* �ͷ�result������ᶪʧ�ڴ� */
		mysql_free_result(result_stu);
	}


	cout  << endl ;
	if (args[2].get_string() == "base")//���base���ܽ�
	{
		//ÿ���˵�ȫ��base һ���˵�ȫ��bases
		if(fileName == "all") 
		{
			cout << "�����" << cnt_stu << "��ѧ���ļ�飬�ļ�����:" << cnt_file << "��ͨ������:" << cnt_correct_all << "������ͨ��" << cnt_correct_all<<"��" << endl;
			int width = 0;
			if (cnt_correct_all)
				width = max(width, 16);
			if (cnt_not_GB_all)
				width = max(38, width);
			if (cnt_not_submit_all)
				width = max(18, width);
			if (cnt_not_pdf_all)
				width = max(width, 29);
			if (cnt_not_vs_all)
				width = max(width, 40);
			for (int i = 1; i <= width; i++)
				cout << "=";
			cout  << endl;
			cout << "������ϸ��Ϣ" << endl;
			for (int i = 1; i <= width; i++)
				cout << "=";
			cout << endl;
			if (cnt_correct_all)
				cout << setw(width - 10) << resetiosflags(ios::right) << setiosflags(ios::right) << "��ȷ" << " : " << cnt_correct_all << endl;
			if (cnt_not_submit_all)
				cout << setw(width - 10) << resetiosflags(ios::right) << setiosflags(ios::right) << "δ�ύ" << " : " << cnt_not_submit_all << endl;
			if (cnt_not_pdf_all)
				cout << setw(width - 10) << resetiosflags(ios::right) << setiosflags(ios::right) << "PDF�ļ���ʽ����ȷ" << " : " << cnt_not_pdf_all << endl;
			if (cnt_not_vs_all)
				cout << setw(width - 10) << resetiosflags(ios::right) << setiosflags(ios::right) << "Դ�ļ���ʽ����ȷ(VS�޷�ʶ��)" << " : " << cnt_not_vs_all << endl;
			if (cnt_not_GB_all)
				cout << setw(width-10) << resetiosflags(ios::right) << setiosflags(ios::right) << "Դ�ļ���ʽ����ȷ(��GB����)" << " : " << cnt_not_GB_all << endl;
			for (int i = 1; i <= width; i++)
				cout << "=";
			cout << endl;
			cout << endl;
		}
		//�����ļ���base�����Ǽ�������˵��б�͵����˵��б�
		else
		{
			cout << "���ͨ��" << cnt_correct_all << "/" <<cnt_stu << "��ѧ��" "������ͨ��" << cnt_correct_all <<"��"<< endl;
			int width = 0;
			if (cnt_correct_all)
				width = max(width, 16);
			if (cnt_not_GB_all)
				width = max(width, 38);
			else
				width = max(width, 18);
			if (cnt_not_pdf_all)
				width = max(width, 29);
			if (cnt_not_vs_all)
				width = max(width, 40);
			for (int i = 1; i <= width; i++)
				cout << "=";
			cout << endl;
			cout << "��ϸ��Ϣ" << endl;
			for (int i = 1; i <= width; i++)
				cout << "=";
			cout << endl;
			if (cnt_correct_all)
				cout << setw(width - 10) << resetiosflags(ios::right) << setiosflags(ios::right) << "��ȷ" << " : " << cnt_correct_all << endl;
			if (cnt_not_submit_all)
				cout << setw(width - 10) << resetiosflags(ios::right) << setiosflags(ios::right) << "δ�ύ" << " : " << cnt_not_submit_all << endl;
			if (cnt_not_pdf_all)
				cout << setw(width - 10) << resetiosflags(ios::right) << setiosflags(ios::right) << "PDF�ļ���ʽ����ȷ" << " : " << cnt_not_pdf_all << endl;
			if (cnt_not_vs_all)
				cout << setw(width - 10) << resetiosflags(ios::right) << setiosflags(ios::right) << "Դ�ļ���ʽ����ȷ(VS�޷�ʶ��)" << " : " << cnt_not_vs_all << endl;
			if (cnt_not_GB_all)
				cout << setw(width - 10) << resetiosflags(ios::right) << setiosflags(ios::right) << "Դ�ļ���ʽ����ȷ(��GB����)" << " : " << cnt_not_GB_all << endl;
			for (int i = 1; i <= width; i++)
				cout << "=";
			cout << endl;
			cout << endl;
		}
	}
	if (args[2].get_string() == "firstline")
	{
		//all
		if (fileName == "all")
		{
			int width = 0;
			if (cnt_correct_all)
				width = max(width, 16);
			if (cnt_not_GB_all)
				width = max(38, width);
			if (cnt_not_vs_all)
				width = max(40, width);
			if (cnt_first_multierror_all)
				width = max(34, width);
			if (cnt_not_submit_all)
				width = max(18, width);
			if (cnt_correct_all)
				width = max(16, width);
			if (cnt_first_not_define_all)
				width = max(26, width);
			if (cnt_first_not_3_all)
				width = max(24, width);
			if (cnt_first_error_all)
				width = max(24, width);
			cout << "�����" << cnt_stu << "��ѧ���ļ�飬�ļ�����:" << cnt_file << "��ͨ������:" << cnt_correct_all << "������ͨ��" << cnt_correct_all << "��" << endl;
			for (int i = 1; i <= width; i++)
				cout << "=";
			cout << endl;
			cout << "������ϸ��Ϣ" << endl;
			for (int i = 1; i <= width; i++)
				cout << "=";
			cout << endl;
			if (cnt_correct_all)
				cout << setw(width - 10) << resetiosflags(ios::right) << setiosflags(ios::right) << "��ȷ" << " : " << cnt_correct_all << endl;
			if (cnt_not_submit_all)
				cout << setw(width - 10) << resetiosflags(ios::right) << setiosflags(ios::right) << "δ�ύ" << " : " << cnt_not_submit_all << endl;
			if (cnt_not_vs_all)
				cout << setw(width - 10) << resetiosflags(ios::right) << setiosflags(ios::right) << "Դ�ļ���ʽ����ȷ(VS�޷�ʶ��)" << " : " << cnt_not_vs_all << endl;
			if (cnt_not_GB_all)
				cout << setw(width - 10) << resetiosflags(ios::right) << setiosflags(ios::right) << "Դ�ļ���ʽ����ȷ(��GB����)" << " : " << cnt_not_GB_all << endl;
			if (cnt_first_multierror_all)
				cout << setw(width - 10) << resetiosflags(ios::right) << setiosflags(ios::right) << "���ж���ע�͸�ʽ����ȷ" << " : " << cnt_first_multierror_all << endl;
			if (cnt_first_not_define_all)
				cout << setw(width - 10) << resetiosflags(ios::right) << setiosflags(ios::right) << "���в���ע����" << " : " << cnt_first_not_define_all << endl;
			if (cnt_first_not_3_all)
				cout << setw(width - 10) << resetiosflags(ios::right) << setiosflags(ios::right) << "���в�������" << " : " << cnt_first_not_3_all << endl;
			if (cnt_first_error_all)
				cout << setw(width - 10) << resetiosflags(ios::right) << setiosflags(ios::right) << "���м�����" << " : " << cnt_first_error_all << endl;
			for (int i = 1; i <= width; i++)
				cout << "=";
			cout << endl;
			cout << endl;
		}
		//�����ļ�
		else
		{
			cout << "���ͨ��" << cnt_correct_all << "/" << cnt_stu << "��ѧ��" "������ͨ��" << cnt_correct_all << "��" << endl;
			int width = 0;
			if (cnt_correct_all)
				width = max(width, 16);
			if (cnt_not_GB_all)
				width = max(38, width);
			if (cnt_not_vs_all)
				width = max(40, width);
			if (cnt_first_multierror_all)
				width = max(34, width);
			if (cnt_not_submit_all)
				width = max(18, width);
			if (cnt_correct_all)
				width = max(16, width);
			if (cnt_first_not_define_all)
				width = max(26, width);
			if (cnt_first_not_3_all)
				width = max(24, width);
			if (cnt_first_error_all)
				width = max(24, width);
			for (int i = 1; i <= width; i++)
				cout << "=";
			cout << endl;
			cout << "��ϸ��Ϣ" << endl;
			for (int i = 1; i <= width; i++)
				cout << "=";
			cout << endl;
			if (cnt_correct_all)
				cout << setw(width - 10) << resetiosflags(ios::right) << setiosflags(ios::right) << "��ȷ" << " : " << cnt_correct_all << endl;
			if (cnt_not_submit_all)
				cout << setw(width - 10) << resetiosflags(ios::right) << setiosflags(ios::right) << "δ�ύ" << " : " << cnt_not_submit_all << endl;
			if (cnt_not_vs_all)
				cout << setw(width - 10) << resetiosflags(ios::right) << setiosflags(ios::right) << "Դ�ļ���ʽ����ȷ(VS�޷�ʶ��)" << " : " << cnt_not_vs_all << endl;
			if (cnt_not_GB_all)
				cout << setw(width - 10) << resetiosflags(ios::right) << setiosflags(ios::right) << "Դ�ļ���ʽ����ȷ(��GB����)" << " : " << cnt_not_GB_all << endl;
			if (cnt_first_multierror_all)
				cout << setw(width - 10) << resetiosflags(ios::right) << setiosflags(ios::right) << "���ж���ע�͸�ʽ����ȷ" << " : " << cnt_first_multierror_all << endl;
			if (cnt_first_not_define_all)
				cout << setw(width - 10) << resetiosflags(ios::right) << setiosflags(ios::right) << "���в���ע����" << " : " << cnt_first_not_define_all << endl;
			if (cnt_first_not_3_all)
				cout << setw(width - 10) << resetiosflags(ios::right) << setiosflags(ios::right) << "���в�������" << " : " << cnt_first_not_3_all << endl;
			if (cnt_first_error_all)
				cout << setw(width - 10) << resetiosflags(ios::right) << setiosflags(ios::right) << "���м�����" << " : " << cnt_first_error_all << endl;
			for (int i = 1; i <= width; i++)
				cout << "=";
			cout << endl;
			cout << endl;
		}
	}
	if (args[2].get_string() == "secondline")
	{
		cout << "���ͨ��" << cnt_correct_all << "/" << cnt_stu << "��ѧ��" "������ͨ��" << cnt_correct_all << "��" << endl;
		int width = 0;
		if (cnt_correct_all)
			width = max(width, 16);
		if (cnt_not_GB_all)
			width = max(38, width);
		if (cnt_not_vs_all)
			width = max(40, width);
		if (cnt_first_multierror_all)
			width = max(34, width);
		if (cnt_not_submit_all)
			width = max(18, width);
		if (cnt_correct_all)
			width = max(16, width);
		if (cnt_first_not_define_all)
			width = max(26, width);
		if (cnt_first_not_3_all)
			width = max(24, width);
		if (cnt_first_error_all)
			width = max(24, width);
		if(cnt_second_not_define_all)
			width = max(24, width);
		for (int i = 1; i <= width; i++)
			cout << "=";
		cout << endl;
		cout << "��ϸ��Ϣ" << endl;
		for (int i = 1; i <= width; i++)
			cout << "=";
		cout << endl;
		if (cnt_correct_all)
			cout << setw(width - 10) << resetiosflags(ios::right) << setiosflags(ios::right) << "��ȷ" << " : " << cnt_correct_all << endl;
		if (cnt_not_submit_all)
			cout << setw(width - 10) << resetiosflags(ios::right) << setiosflags(ios::right) << "δ�ύ" << " : " << cnt_not_submit_all << endl;
		if (cnt_not_vs_all)
			cout << setw(width - 10) << resetiosflags(ios::right) << setiosflags(ios::right) << "Դ�ļ���ʽ����ȷ(VS�޷�ʶ��)" << " : " << cnt_not_vs_all << endl;
		if (cnt_not_GB_all)
			cout << setw(width - 10) << resetiosflags(ios::right) << setiosflags(ios::right) << "Դ�ļ���ʽ����ȷ(��GB����)" << " : " << cnt_not_GB_all << endl;
		if (cnt_first_multierror_all)
			cout << setw(width - 10) << resetiosflags(ios::right) << setiosflags(ios::right) << "���ж���ע�͸�ʽ����ȷ" << " : " << cnt_first_multierror_all << endl;
		if (cnt_first_not_define_all)
			cout << setw(width - 10) << resetiosflags(ios::right) << setiosflags(ios::right) << "���в���ע����" << " : " << cnt_first_not_define_all << endl;
		if (cnt_first_not_3_all)
			cout << setw(width - 10) << resetiosflags(ios::right) << setiosflags(ios::right) << "���в�������" << " : " << cnt_first_not_3_all << endl;
		if (cnt_first_error_all)
			cout << setw(width - 10) << resetiosflags(ios::right) << setiosflags(ios::right) << "���м�����" << " : " << cnt_first_error_all << endl;
		if (cnt_second_not_define_all)
			cout << setw(width - 10) << resetiosflags(ios::right) << setiosflags(ios::right) << "���в���ע��" << " : " << cnt_second_not_define_all << endl;
		for (int i = 1; i <= width; i++)
			cout << "=";
		cout << endl;
		cout << endl;
	}
	//cout << endl << cnt_stu << endl;
	

	//������֤
	if (args[2].get_string() == "secondline")
	{
		cout << "����������" << endl;
		Cross cross;
		cross.filename = fileName;
		cross.source_root = src_rootdir;
		{
			string searchName;
			if (stuNo != "all") {
				searchName = string("select * from view_hwcheck_stulist where stu_cno = ") + cno + (" and stu_no = ") + stuNo;
			}
			else {
				searchName = string("select * from view_hwcheck_stulist where stu_cno = ") + cno;
			}

			if (mysql_query(mysql_stu, searchName.c_str())) {
				cout << "mysql_query failed(" << mysql_error(mysql_stu) << ")" << endl;
				return -1;
			}
			if ((result_stu = mysql_store_result(mysql_stu)) == NULL) {
				cout << "mysql_store_result failed(" << mysql_error(mysql_stu) << ")" << endl;
				return -1;
			}


			while ((row_stu = mysql_fetch_row(result_stu)) != NULL)
			{
				if (!fileExists(src_rootdir + cno + '-' + row_stu[2] + '/' + fileName))
				{
					cross.stu_list.push_back({ row_stu[2],row_stu[3],cno,""});
					continue;
				}
				if (isUTF8(src_rootdir + cno + '-' + row_stu[2] + '/' + fileName)) {
					cross.stu_list.push_back({ row_stu[2],row_stu[3],cno,""});
					continue;
				}
				ifstream fin(src_rootdir + cno + '-' + row_stu[2] + '/' + fileName);
				string secondline;
				while (getline(fin, secondline)) {
					trimLine(secondline, "all");
					if (!secondline.empty()) {
						break;
					}
				}
				while (getline(fin, secondline)) {
					trimLine(secondline, "all");
					if (!secondline.empty()) {
						break;
					}
				}//�õ��ڶ���
				cross.stu_list.push_back({ row_stu[2],row_stu[3],cno,secondline });
				//cout << row_stu[2] << " " << row_stu[3] << " " << cno << " " << secondline << endl;
			}

			/* �ͷ�result������ᶪʧ�ڴ� */
			mysql_free_result(result_stu);
		}
		if(cno2!="")
		{
			string searchName;
			if (stuNo != "all") {
				searchName = string("select * from view_hwcheck_stulist where stu_cno = ") + cno2 + (" and stu_no = ") + stuNo;
			}
			else {
				searchName = string("select * from view_hwcheck_stulist where stu_cno = ") + cno2;
			}

			if (mysql_query(mysql_stu, searchName.c_str())) {
				cout << "mysql_query failed(" << mysql_error(mysql_stu) << ")" << endl;
				return -1;
			}
			if ((result_stu = mysql_store_result(mysql_stu)) == NULL) {
				cout << "mysql_store_result failed(" << mysql_error(mysql_stu) << ")" << endl;
				return -1;
			}


			while ((row_stu = mysql_fetch_row(result_stu)) != NULL)
			{
				if (!fileExists(src_rootdir + cno2 + '-' + row_stu[2] + '/' + fileName))
				{
					cross.stu_list.push_back({ row_stu[2],row_stu[3],cno2,""});
					continue;
				}
				if (isUTF8(src_rootdir + cno2 + '-' + row_stu[2] + '/' + fileName)) {
					cross.stu_list.push_back({ row_stu[2],row_stu[3],cno2,""});
					continue;
				}
				ifstream fin(src_rootdir + cno2 + '-' + row_stu[2] + '/' + fileName);
				string secondline;
				while (getline(fin, secondline)) {
					trimLine(secondline, "all");
					if (!secondline.empty()) {
						break;
					}
				}
				while (getline(fin, secondline)) {
					trimLine(secondline, "all");
					if (!secondline.empty()) {
						break;
					}
				}//�õ��ڶ���
				cross.stu_list.push_back({ row_stu[2],row_stu[3],cno2,secondline });
				//cout << row_stu[2] << " " << row_stu[3] << " " << cno2 << " " << secondline << endl;
			}

			/* �ͷ�result������ᶪʧ�ڴ� */
			mysql_free_result(result_stu);
		}
		Crosscheck(cross);
		cout << endl;
	}

	return 0;
}

