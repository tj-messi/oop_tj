/*2351114 大数据 朱俊泽*/
#include "hw_check.h"
using namespace std;
/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
 ***************************************************************************/
static void usage(const char* const full_procname)
{
	const char *procname = strrchr(full_procname, '\\');
	if (procname == NULL)
		procname = full_procname;

	const int wkey = 7 + strlen(procname) + 1;
	const int wopt = 7 + strlen(procname) + 4;
	cout << endl;

	cout << "Usage: " << procname << " 必选项/可选项" << endl;
	cout << endl;
	cout << setw(wkey) << ' ' << "必选项：指定操作" << endl;
	cout << setw(wopt) << ' ' << "--action opname : 支持的opname如下" << endl;
	cout << setw(wopt) << ' ' << "\t base              : 基础检查(文件是否提交、是否被改动、编码是否正确)" << endl;
	cout << setw(wopt) << ' ' << "\t firstline         : 首行检查（仅源程序文件需要）" << endl;
	cout << setw(wopt) << ' ' << "\t secondline        : 次行检查（仅部分源程序文件需要）" << endl;

	cout << setw(wkey) << ' ' << "必选项：指定课号" << endl;
	cout << setw(wopt) << ' ' << "--cno course_no     : 课号" << endl;

	cout << setw(wkey) << ' ' << "必选项：指定学生" << endl;
	cout << setw(wopt) << ' ' << "--stu no/all        : 指定单个/全部(7位数字为学号,all为全部)" << endl;

	cout << setw(wkey) << ' ' << "必选项：指定文件" << endl;
	cout << setw(wopt) << ' ' << "--file filename/all : 具体文件名/全部(all为全部,其余为具体文件名)" << endl;

	cout << setw(wkey) << ' ' << "可选项：" << endl;
	cout << setw(wopt) << ' ' << "--chapter n         : 在--file的基础上再进行章节的筛选(无/-1则全部章节,可与--week共存)" << endl;
	cout << setw(wopt) << ' ' << "--week n            : 在--file的基础上再进行周次的筛选(无/-1则全部周次,可与--chapter共存)" << endl;
	cout << setw(wopt) << ' ' << "--display xxxxx     : 每位0/1分别表示正常信息/未提交信息/错误信息/汇总信息/严重错误信息" << endl;
	cout << setw(wopt) << ' ' << "--cfgfile filename  : 指定配置文件名(缺省:hw_check.conf)" << endl;
	cout << endl;

	const char* DEMO_CNO = "10108001";
	const char* DEMO_SRC_FNAME = "12-b1.cpp";
	const char* DEMO_STUNO = "2359999";

	cout << "e.g.   " << procname << " --action base --cno " << DEMO_CNO << " --stu all --file all             : 检查" << DEMO_CNO << "所有学生的所有作业的基本信息" << endl;
	cout << "       " << procname << " --action base --cno " << DEMO_CNO << " --stu all --file all --chapter 4 : 检查" << DEMO_CNO << "所有学生的第4章作业的基本信息" << endl;
	cout << "       " << procname << " --action base --cno " << DEMO_CNO << " --stu all --file all --week 6    : 检查" << DEMO_CNO << "所有学生的第6周作业的基本信息" << endl;
	cout << "       " << procname << " --action base --cno " << DEMO_CNO << " --stu " << DEMO_STUNO << " --file all         : 检查" << DEMO_CNO << "的" << DEMO_STUNO << "学生的所有作业的基本信息" << endl;
	cout << "       " << procname << " --action base --cno " << DEMO_CNO << " --stu " << DEMO_STUNO << " --file " << DEMO_SRC_FNAME << "   : 检查" << DEMO_CNO << "的" << DEMO_STUNO << "学生的" << DEMO_SRC_FNAME << "作业的基本信息" << endl;
	cout << endl;

	cout << "       " << procname << " --action firstline --cno " << DEMO_CNO << " --stu all --file all             : 检查" << DEMO_CNO << "所有学生的所有作业的首行信息" << endl;
	cout << "       " << procname << " --action firstline --cno " << DEMO_CNO << " --stu all --file all --chapter 4 : 检查" << DEMO_CNO << "所有学生的第4章作业的首行信息" << endl;
	cout << "       " << procname << " --action firstline --cno " << DEMO_CNO << " --stu all --file all --week 6    : 检查" << DEMO_CNO << "所有学生的第6周作业的首行信息" << endl;
	cout << "       " << procname << " --action firstline --cno " << DEMO_CNO << " --stu " << DEMO_STUNO << " --file all         : 检查" << DEMO_CNO << "的" << DEMO_STUNO << "学生的所有作业的首行信息" << endl;
	cout << "       " << procname << " --action firstline --cno " << DEMO_CNO << " --stu " << DEMO_STUNO << " --file " << DEMO_SRC_FNAME << "   : 检查" << DEMO_CNO << "的" << DEMO_STUNO << "学生的" << DEMO_SRC_FNAME << "作业的首行信息" << endl;
	cout << endl;

	cout << "       " << procname << " --action secondline --cno " << DEMO_CNO << " --stu all --file " << DEMO_SRC_FNAME << " : 检查" << DEMO_CNO << "的所有学生的" << DEMO_SRC_FNAME << "作业的次行信息" << endl;
	cout << endl;

	cout << "       " << procname << " --cfgfile E:\\test\\my.conf --action base --cno " << DEMO_CNO << " --stu all --file all : 检查" << DEMO_CNO << "所有学生的所有作业的基本信息(指定配置文件)" << endl;
	cout << endl;


	cout << endl;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
 ***************************************************************************/
int main(int argc, char** argv)
{
	const string Action_Name[] = {"base","firstline","secondline",""}; //也可以根据需要，放入头文件中以便共享 

	args_analyse_tools args[] = {
		args_analyse_tools("--help",     ST_EXTARGS_TYPE::boolean,            0, false),
		args_analyse_tools("--debug",    ST_EXTARGS_TYPE::boolean,            0, false),
		args_analyse_tools("--action",   ST_EXTARGS_TYPE::str_with_set_error, 1, -1, Action_Name),	//参数-1无意义，表示无默认，必须指定
		args_analyse_tools("--cno",      ST_EXTARGS_TYPE::str,                1, string("")),
		args_analyse_tools("--stu",      ST_EXTARGS_TYPE::str,                1, string("")),
		args_analyse_tools("--file",     ST_EXTARGS_TYPE::str,                1, string("")),
		args_analyse_tools("--chapter",  ST_EXTARGS_TYPE::int_with_error,     1, -1, -1, 99), //参数-1表示不进行章节选择
		args_analyse_tools("--week",     ST_EXTARGS_TYPE::int_with_error,     1, -1, -1, 20), //参数-1表示不进行周次选择
		args_analyse_tools("--display",  ST_EXTARGS_TYPE::str,                1, string("11111")),
		args_analyse_tools("--cfgfile",  ST_EXTARGS_TYPE::str,                1, string("hw_check.conf")),
		args_analyse_tools()  //最后一个，用于结束
	};

	args_analyse_process(argc, argv, args, 0);

	//参数不够直接usage表
	if (argc == 1)
	{
		usage(argv[0]);
		return 0;
	}

	//help直接usage表
	if (args[0].existed())
	{
		usage(argv[0]);
		return 0;
	}

	//debug 输出参数列表--不return
	if (args[1].existed())
	{
		/* 打印参数的分析结果 */
		args_analyse_print(args);
		cout << endl;
	}

	//必须的参数
	if (!args[2].existed()) {
		usage(argv[0]);
		cout << "参数[--action]必须指定." << endl;
		return 0;
	}

	if (!args[3].existed()) {
		usage(argv[0]);
		cout << "参数[--cno]必须指定." << endl;
		return 0;
	}

	if (!args[4].existed()) {
		usage(argv[0]);
		cout << "参数[--stu]必须指定." << endl;
		return 0;
	}

	if (!args[5].existed()) {
		usage(argv[0]);
		cout << "参数[--file]必须指定." << endl;
		return 0;
	}

	//参数[--chapter/--week]不能出现在[--file 单个文件名]时.
	if ((args[6].existed()) && args[5].get_string() != "all") {
		usage(argv[0]);
		cout << "参数[--chapter/--week]不能出现在[--file 单个文件名]时." << endl;
		return 0;
	}

	if ((args[7].existed()) && args[5].get_string() != "all") {
		usage(argv[0]);
		cout << "参数[--chapter/--week]不能出现在[--file 单个文件名]时." << endl;
		return 0;
	}

	//HW_Check_SecondLine 只能针对全体学生
	if (args[4].get_string() != "all" && args[2].get_string() == "secondline") {
		cout << "HW_Check_SecondLine 只能针对全体学生" << endl;
		return 0;
	}

	//HW_Check_SecondLine 只能针对单文件
	if (args[5].get_string() == "all" && args[2].get_string() == "secondline") {
		cout << "HW_Check_SecondLine 只能针对单文件" << endl;
		return 0;
	}

	//学生学号没有七位
	if (args[4].get_string().length() != 7 && args[4].get_string()!= "all") {
		cout << "[--严重错误--] 读取 [--stu] 指定的文件出错." << endl;
		return 0;
	}

	//先读config
	config_file_tools cfg(args[9].get_string());
	//MySQL的相关数据库
	string db_host, db_port, db_name, db_username,db_passwd,db_currterm;
	cfg.item_get_raw("[数据库]", "db_host", db_host);
	cfg.item_get_raw("[数据库]", "db_port", db_port);
	cfg.item_get_raw("[数据库]", "db_name", db_name);
	cfg.item_get_raw("[数据库]", "db_username", db_username);
	cfg.item_get_raw("[数据库]", "db_passwd", db_passwd);
	cfg.item_get_raw("[数据库]", "db_currterm", db_currterm);

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

	//本地文件的source路径
	string src_rootdir;
	cfg.item_get_raw("[文件目录]", "src_rootdir", src_rootdir);

	trimLine(src_rootdir, "all");

	MYSQL* mysql_stu;
	MYSQL_RES* result_stu;
	MYSQL_ROW  row_stu;//每一行都是筛选好的内容
	/* 初始化 mysql 变量，失败返回NULL */
	if ((mysql_stu = mysql_init(NULL)) == NULL) {
		cout << "mysql_init failed" << endl;
		return -1;
	}
	else {
		//cout << "initial_successfully!" << endl;
	}

	/* 连接数据库，失败返回NULL
		1、mysqld没运行
		2、没有指定名称的数据库存在 */
	if (mysql_real_connect(mysql_stu, db_host.c_str(), db_username.c_str(), db_passwd.c_str(), db_name.c_str(), 0, NULL, 0) == NULL
		) {
		cout << "mysql_real_connect failed(" << mysql_error(mysql_stu) << ")" << endl;
		return -1;
	}
	else {
		//cout << "connect_successfully!" << endl;
	}

	/* 设置字符集，否则读出的字符乱码 */
	mysql_set_character_set(mysql_stu, "gbk");

	//开始搜寻学校数据库
	string stuNo = args[4].get_string();
	string fileName = args[5].get_string();
	string cno = args[3].get_string();
	string cno2 = "";

	if (cno.find(",") != -1)//两个班联合
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
	//第一次计数
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
			if (((string)row_stu[3]).find("·") != -1)
			{
				string sub1 = ((string)row_stu[3]).substr(0, ((string)row_stu[3]).find("·"));
				string sub2 = ((string)row_stu[3]).substr(((string)row_stu[3]).find("·") + 2);
				name = sub1 + '.' + sub2;

				//name[((string)row_stu[3]).find("·")] = '.';
			}

			//max_len_name = max(max_len_name, (int)(name.size()));
			cnt_stu++;
		}
		//mysql_free_result(result_stu);
	}
	//可能的联合课号
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
			if (((string)row_stu[3]).find("·") != -1)
			{
				string sub1 = ((string)row_stu[3]).substr(0, ((string)row_stu[3]).find("·"));
				string sub2 = ((string)row_stu[3]).substr(((string)row_stu[3]).find("·") + 2);
				name = sub1 + '.' + sub2;

				//name[((string)row_stu[3]).find("·")] = '.';
			}
			
			cnt_stu++;
		}

		//mysql_free_result(result_stu);
	}


	//测试stu-list 和 hw-list
	//while ((row = mysql_fetch_row(result)) != NULL) {
	//	cout << setiosflags(ios::left);           //输出左对齐
	//	cout << "ke：" << setw(12) << row[0];    //宽度12位，左对齐
	//	cout << "nj：" << setw(8) << row[1];     //    8
	//	cout << "xh：" << setw(4) << row[2];     //    4
	//	cout << "xm：" << setw(4) << row[3];     //    4，目前是字符串形式，也可以用atoi(row[3])输出int型的年龄
	//	cout << "xb：" << setw(4) << row[4];     //    4
	//	cout << "zy：" << setw(4) << row[5];
	//	cout << "zy：" << setw(4) << row[6];
	//	cout << endl;
	//}
	//ke：2024 / 2025 / 1 nj：2023    xh：2351114xm：朱俊泽xb：男  zy：数据科学与大数据技术zy：大数据
	//ke：99          nj：10108001xh：9902xm：99  xb：12  zy：help.pdfzy：0.0
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
			cout << "课号 : " << args[3].get_string() << " 学生数量 : " << cnt_stu << " 源文件名 : " << fileName << endl;
	}
	if (args[2].get_string() == "firstline")
	{
		if (fileName != "all")
			cout << "课号 : " << args[3].get_string() << " 学生数量 : " << cnt_stu << " 源文件名 : " << fileName << endl;
	}
	if (args[2].get_string() == "secondline")
	{
		if (fileName != "all")
			cout << "课号 : " << args[3].get_string() << " 学生数量 : " << cnt_stu << " 源文件名 : " << fileName << endl;
	}

	//第一个班级查询
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
			//cout << row_stu[2] << endl;//学号row[2]

			//找对应文件
			MYSQL* mysql_hw;
			MYSQL_RES* result_hw;
			MYSQL_ROW  row_hw;//每一行都是筛选好的内容
			/* 初始化 mysql 变量，失败返回NULL */
			if ((mysql_hw = mysql_init(NULL)) == NULL) {
				cout << "mysql_init failed" << endl;
				return -1;
			}
			else {
				//cout << "initial_successfully!" << endl;
			}
			/* 连接数据库，失败返回NULL
			1、mysqld没运行
			2、没有指定名称的数据库存在 */
			if (mysql_real_connect(mysql_hw, db_host.c_str(), db_username.c_str(), db_passwd.c_str(), db_name.c_str(), 0, NULL, 0) == NULL
				) {
				cout << "mysql_real_connect failed(" << mysql_error(mysql_hw) << ")" << endl;
				return -1;
			}
			else {
				//cout << "connect_successfully!" << endl;
			}

			/* 设置字符集，否则读出的字符乱码 */
			mysql_set_character_set(mysql_hw, "gbk");

			string hwname;//筛选出对应课号的作业列表
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
				//章节和周期的限制
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
					//只检查部分文件
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
			//针对每一个文件名
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
			if (((string)row_stu[3]).find("·") != -1)
			{
				string sub1 = ((string)row_stu[3]).substr(0, ((string)row_stu[3]).find("·"));
				string sub2 = ((string)row_stu[3]).substr(((string)row_stu[3]).find("·") + 2);
				name = sub1 + '.' + sub2;

				//name[((string)row_stu[3]).find("·")] = '.';
			}
			{
				if (args[2].get_string() == "base")
				{
					if (fileName == "all")
						cout << resetiosflags(ios::right) << setiosflags(ios::left) << setw(3) << cnt_stunum << ":" << " 学号-" << row_stu[2] << " 姓名-" << name << " 课号-" << args[3].get_string() << " 文件数量-" << cnt_hw << endl;
				}
				if (args[2].get_string() == "firstline")
				{
					if (fileName == "all")
						cout << resetiosflags(ios::right) << setiosflags(ios::left) << setw(3) << cnt_stunum << ":" << " 学号-" << row_stu[2] << " 姓名-" << name << " 课号-" << args[3].get_string() << " 文件数量-" << cnt_hw << endl;
				}
			}


			while ((row_hw = mysql_fetch_row(result_hw)) != NULL) {

				//章节和周期的限制
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
					//只检查部分文件
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
				if (((string)row_stu[3]).find("·") != -1)
				{
					string sub1 = ((string)row_stu[3]).substr(0, ((string)row_stu[3]).find("·"));
					string sub2 = ((string)row_stu[3]).substr(((string)row_stu[3]).find("·") + 2);
					name = sub1 + '.' + sub2;

					//name[((string)row_stu[3]).find("·")] = '.';
				}
				//如果是针对单文件
				if (fileName != "all")
				{
					//base
					if (args[2].get_string() == "base")
					{
						cout << resetiosflags(ios::right) << setiosflags(ios::left) << setw(3) << cnt_file << ": " << row_stu[2] << "/" << resetiosflags(ios::right) << setiosflags(ios::left) << setw(max_len_name) << name << "  : ";
						Check result = checkfilebase(src_rootdir + cno + '-' + row_stu[2] + '/' + row_hw[5]);
						switch (result) {
							case FILE_NOT_FOUND:
								std::cout << "未提交\n";
								cnt_not_submit++;
								cnt_not_submit_all++;
								break;
							case NOT_PDF:
								cnt_not_pdf++;
								 cnt_not_pdf_all++;
								std::cout << "PDF文件格式不正确\n";
								break;
							case NOT_VS:
								cnt_not_vs++;
								cnt_not_vs_all++;
								std::cout << "源文件格式不正确(VS无法识别)\n";
								break;
							case CORRECT:
								std::cout << "正确\n";
								cnt_correct++;
								cnt_correct_all++;
								break;
							case INVALID_ENCODING:
								cnt_not_GB++;
								cnt_not_GB_all++;
								std::cout << "源文件格式不正确(非GB编码)\n";
								break;
						}
					}
					//firstline
					if (args[2].get_string() == "firstline")
					{
						cout << resetiosflags(ios::right) << setiosflags(ios::left) << setw(3) << cnt_file << ": " << row_stu[2] << "/" << resetiosflags(ios::right) << setiosflags(ios::left) << setw(max_len_name) << name << "  : ";
						if (!fileExists(src_rootdir + cno + '-' + row_stu[2] + '/' + row_hw[5]))
						{
							std::cout << "未提交\n";
							cnt_not_submit++;
							cnt_not_submit_all++;
							continue;
						}
						if (isUTF8(src_rootdir + cno + '-' + row_stu[2] + '/' + row_hw[5])) {
							cnt_not_GB++;
							cnt_not_GB_all++;
							std::cout << "源文件格式不正确(非GB编码)\n";
							continue;
						}
						if (checkvs(src_rootdir + cno + '-' + row_stu[2] + '/' + row_hw[5]))
						{
							cnt_not_vs++;
							cnt_not_vs_all++;
							std::cout << "源文件格式不正确(VS无法识别)\n";
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
								std::cout << "未提交\n";
								cnt_not_submit++;
								cnt_not_submit_all++;
								break;
							case CORRECT:
								std::cout << "正确\n";
								cnt_correct++;
								cnt_correct_all++;
								break;
							case INVALID_ENCODING:
								cnt_not_GB++;
								cnt_not_GB_all++;
								std::cout << "源文件格式不正确(非GB编码)\n";
								break;
							case FIRSTLINE_NOT_DEFINE:
								cnt_first_not_define++;
								cnt_first_not_define_all++;
								cout << "首行不是注释行 [" << firstline << "]" << endl;
								break;
							case FIRSTLINE_NOT_3_ITEMS:
								cnt_first_not_3++;
								cnt_first_not_3_all++;
								cout << "首行不是三项 [" << firstline << "]" << endl;
								break;
							case FIRSTLINE_ERROR:
								cnt_first_error++;
								cnt_first_error_all++;
								cout << " [" << firstline << "]" << endl;
								break;
							case FIRSTLINE_MULTIERROR:
								cnt_first_multierror++;
								cnt_first_multierror_all++;
								cout << "首行不是符合要求的/* */格式 [" << firstline << "]" << endl;
								break;
						}
					}
					//secondline
					if (args[2].get_string() == "secondline")
					{
						cout << resetiosflags(ios::right) << setiosflags(ios::left) << setw(3) << cnt_file << ": " << row_stu[2] << "/" << resetiosflags(ios::right) << setiosflags(ios::left) << setw(max_len_name) << name << " : ";
						if (!fileExists(src_rootdir + cno + '-' + row_stu[2] + '/' + row_hw[5]))
						{
							std::cout << "未提交\n";
							cnt_not_submit++;
							cnt_not_submit_all++;
							continue;
						}
						if (isUTF8(src_rootdir + cno + '-' + row_stu[2] + '/' + row_hw[5])) {
							cnt_not_GB++;
							cnt_not_GB_all++;
							std::cout << "源文件格式不正确(非GB编码)\n";
							continue;
						}
						if (checkvs(src_rootdir + cno + '-' + row_stu[2] + '/' + row_hw[5]))
						{
							cnt_not_vs++;
							cnt_not_vs_all++;
							std::cout << "源文件格式不正确(VS无法识别)\n";
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
						}//拿到第二行
						Check result = checkfilesecond(secondline, row_stu[2]);
						switch (result) {
							case CORRECT:
								std::cout << "正确\n";
								cnt_correct++;
								cnt_correct_all++;
								break;
							case NOT_DOUBLE:
								//std::cout << "正确\n";
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
								std::cout << "次行不是注释\n";
								cnt_second_not_define++;
								cnt_second_not_define_all++;
								break;
						}
					}
				}
				//如果是all文件则全部执行
				else
				{
					//base
					if (args[2].get_string() == "base")
					{
						cout << "  " << resetiosflags(ios::right) << setiosflags(ios::left) << setw(maxline_row_hw) << row_hw[5] << ": ";//文件名
						Check result = checkfilebase(src_rootdir + cno + '-' + row_stu[2] + '/' + row_hw[5]);
						//cout << src_rootdir + cno + '-' + stuNo + '/' + row_hw[5] << endl;
						switch (result) {
							case FILE_NOT_FOUND:
								std::cout << "未提交\n";
								cnt_not_submit++;
								cnt_not_submit_all++;
								break;
							case NOT_VS:
								cnt_not_vs++;
								cnt_not_vs_all++;
								std::cout << "源文件格式不正确(VS无法识别)\n";
								break;
							case NOT_PDF:
								cnt_not_pdf++;
								cnt_not_pdf_all++;
								std::cout << "PDF文件格式不正确\n";
								break;
							case CORRECT:
								std::cout << "正确\n";
								cnt_correct++;
								cnt_correct_all++;
								break;
							case INVALID_ENCODING:
								cnt_not_GB++;
								cnt_not_GB_all++;
								std::cout << "源文件格式不正确(非GB编码)\n";
								break;
						}
					}
					//firstline
					if (args[2].get_string() == "firstline")
					{
						if (!fileExists(src_rootdir + cno + '-' + row_stu[2] + '/' + row_hw[5]))
						{
							cout << "  " << resetiosflags(ios::right) << setiosflags(ios::left) << setw(maxline_row_hw) << row_hw[5] << ": ";//文件名
							std::cout << "未提交\n";
							cnt_not_submit++;
							cnt_not_submit_all++;
							continue;
						}
						if (isUTF8(src_rootdir + cno + '-' + row_stu[2] + '/' + row_hw[5])) {
							cout << "  " << resetiosflags(ios::right) << setiosflags(ios::left) << setw(maxline_row_hw) << row_hw[5] << ": ";//文件名
							cnt_not_GB++;
							cnt_not_GB_all++;
							std::cout << "源文件格式不正确(非GB编码)\n";
							continue;
						}
						if (checkvs(src_rootdir + cno + '-' + row_stu[2] + '/' + row_hw[5]))
						{
							cout << "  " << resetiosflags(ios::right) << setiosflags(ios::left) << setw(maxline_row_hw) << row_hw[5] << ": ";//文件名
							cnt_not_vs++;
							cnt_not_vs_all++;
							std::cout << "源文件格式不正确(VS无法识别)\n";
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
						cout << "  " << resetiosflags(ios::right) << setiosflags(ios::left) << setw(maxline_row_hw) << row_hw[5] << ": ";//文件名
						Check result = checkfilefirst(firstline, row_stu, row_stu[2], row_stu[3]);
						switch (result) {
							case FILE_NOT_FOUND:
								std::cout << "未提交\n";
								cnt_not_submit++;
								cnt_not_submit_all++;
								break;
							case CORRECT:
								std::cout << "正确\n";
								cnt_correct++;
								cnt_correct_all++;
								break;
							case INVALID_ENCODING:
								cnt_not_GB++;
								cnt_not_GB_all++;
								std::cout << "源文件格式不正确(非GB编码)\n";
								break;
							case FIRSTLINE_NOT_DEFINE:
								cnt_first_not_define++;
								cnt_first_not_define_all++;
								cout << "首行不是注释行 [" << firstline << "]" << endl;
								break;
							case FIRSTLINE_NOT_3_ITEMS:
								cnt_first_not_3++;
								cnt_first_not_3_all++;
								cout << "首行不是三项 [" << firstline << "]" << endl;
								break;
							case FIRSTLINE_ERROR:
								cnt_first_error++;
								cnt_first_error_all++;
								cout << " [" << firstline << "]" << endl;
								break;
							case FIRSTLINE_MULTIERROR:
								cnt_first_multierror++;
								cnt_first_multierror_all++;
								cout << "首行不是符合要求的/* */格式 [" << firstline << "]" << endl;
								break;
						}
					}
				}
			}
			if (args[2].get_string() == "base")
			{
				//所有文件base
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
						cout << "全部通过" << cnt_correct << "/" << cnt_hwnum << "个文件，本次通过" << cnt_correct << "个" << endl;
					else
						cout << "检查通过" << cnt_correct << "/" << cnt_hwnum << "个文件，本次通过" << cnt_correct << "个" << endl;
					for (int i = 1; i <= width; i++)
						cout << "-";
					cout << endl;
					cout << "学生详细信息" << endl;
					for (int i = 1; i <= width; i++)
						cout << "-";
					cout << endl;
					if (cnt_correct)
						cout << setw(width - 10) << resetiosflags(ios::right) << setiosflags(ios::right) << "正确" << " : " << cnt_correct << endl;
					if (cnt_not_submit)
						cout << setw(width - 10) << resetiosflags(ios::right) << setiosflags(ios::right) << "未提交" << " : " << cnt_not_submit << endl;
					if (cnt_not_pdf)
						cout << setw(width - 10) << resetiosflags(ios::right) << setiosflags(ios::right) << "PDF文件格式不正确" << " : " << cnt_not_pdf << endl;
					if (cnt_not_vs)
						cout << setw(width - 10) << resetiosflags(ios::right) << setiosflags(ios::right) << "源文件格式不正确(VS无法识别)" << " : " << cnt_not_vs << endl;
					if (cnt_not_GB)
						cout << setw(width - 10) << resetiosflags(ios::right) << setiosflags(ios::right) << "源文件格式不正确(非GB编码)" << " : " << cnt_not_GB << endl;
					for (int i = 1; i <= width; i++)
						cout << "-";
					cout << endl;
					cout << endl;
				}
				//单独文件base
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
						cout << "全部通过" << cnt_correct << "/" << cnt_hwnum << "个文件，本次通过" << cnt_correct << "个" << endl;
					else
						cout << "检查通过" << cnt_correct << "/" << cnt_hwnum << "个文件，本次通过" << cnt_correct << "个" << endl;
					for (int i = 1; i <= width; i++)
						cout << "-";
					cout << endl;
					cout << "学生详细信息" << endl;
					for (int i = 1; i <= width; i++)
						cout << "-";
					cout << endl;
					if (cnt_correct)
						cout << setw(width - 10) << resetiosflags(ios::right) << setiosflags(ios::right) << "正确" << " : " << cnt_correct << endl;
					if (cnt_not_submit)
						cout << setw(width - 10) << resetiosflags(ios::right) << setiosflags(ios::right) << "未提交" << " : " << cnt_not_submit << endl;
					if (cnt_not_vs)
						cout << setw(width - 10) << resetiosflags(ios::right) << setiosflags(ios::right) << "源文件格式不正确(VS无法识别)" << " : " << cnt_not_vs << endl;
					if (cnt_not_GB)
						cout << setw(width - 10) << resetiosflags(ios::right) << setiosflags(ios::right) << "源文件格式不正确(非GB编码)" << " : " << cnt_not_GB << endl;
					if (cnt_first_multierror)
						cout << setw(width - 10) << resetiosflags(ios::right) << setiosflags(ios::right) << "首行多行注释格式不正确" << " : " << cnt_first_multierror << endl;
					if (cnt_first_not_define)
						cout << setw(width - 10) << resetiosflags(ios::right) << setiosflags(ios::right) << "首行不是注释行" << " : " << cnt_first_not_define << endl;
					if (cnt_first_not_3)
						cout << setw(width - 10) << resetiosflags(ios::right) << setiosflags(ios::right) << "首行不是三项" << " : " << cnt_first_not_3 << endl;
					if (cnt_first_error)
						cout << setw(width - 10) << resetiosflags(ios::right) << setiosflags(ios::right) << "首行检查出错" << " : " << cnt_first_error << endl;
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
			/* 释放result，否则会丢失内存 */
			mysql_free_result(result_hw);
			/* 关闭整个连接 */
			mysql_close(mysql_hw);
		}
		/* 释放result，否则会丢失内存 */
		mysql_free_result(result_stu);
	}
	//第二个联合班级查询
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
			//cout << row_stu[2] << endl;//学号row[2]

			//找对应文件
			MYSQL* mysql_hw;
			MYSQL_RES* result_hw;
			MYSQL_ROW  row_hw;//每一行都是筛选好的内容
			/* 初始化 mysql 变量，失败返回NULL */
			if ((mysql_hw = mysql_init(NULL)) == NULL) {
				cout << "mysql_init failed" << endl;
				return -1;
			}
			else {
				//cout << "initial_successfully!" << endl;
			}
			/* 连接数据库，失败返回NULL
			1、mysqld没运行
			2、没有指定名称的数据库存在 */
			if (mysql_real_connect(mysql_hw, db_host.c_str(), db_username.c_str(), db_passwd.c_str(), db_name.c_str(), 0, NULL, 0) == NULL
				) {
				cout << "mysql_real_connect failedhw(" << mysql_error(mysql_hw) << ")" << endl;
				return -1;
			}
			else {
				//cout << "connect_successfully!" << endl;
			}

			/* 设置字符集，否则读出的字符乱码 */
			mysql_set_character_set(mysql_hw, "gbk");

			string hwname;//筛选出对应课号的作业列表
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
				//章节和周期的限制
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
					//只检查部分文件
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
			//针对每一个文件名
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
			if (((string)row_stu[3]).find("·") != -1)
			{
				string sub1 = ((string)row_stu[3]).substr(0, ((string)row_stu[3]).find("·"));
				string sub2 = ((string)row_stu[3]).substr(((string)row_stu[3]).find("·") + 2);
				name = sub1 + '.' + sub2;

				//name[((string)row_stu[3]).find("·")] = '.';
			}
			{
				if (args[2].get_string() == "base")
				{
					if (fileName == "all")
						cout << resetiosflags(ios::right) << setiosflags(ios::left) << setw(3) << cnt_stunum << ":" << " 学号-" << row_stu[2] << " 姓名-" << name << " 课号-" << args[3].get_string() << " 文件数量-" << cnt_hw << endl;
				}
				if (args[2].get_string() == "firstline")
				{
					if (fileName == "all")
						cout << resetiosflags(ios::right) << setiosflags(ios::left) << setw(3) << cnt_stunum << ":" << " 学号-" << row_stu[2] << " 姓名-" << name << " 课号-" << args[3].get_string() << " 文件数量-" << cnt_hw << endl;
				}
			}


			while ((row_hw = mysql_fetch_row(result_hw)) != NULL) {

				//章节和周期的限制
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
					//只检查部分文件
					string extension = string(row_hw[5]).substr(string(row_hw[5]).find_last_of('.'));
					if (extension == ".h" || extension == ".hpp" || extension == ".cpp" || extension == ".c")
					{

					}
					else
						continue;
				}
				cnt_hwnum++;
				cnt_file++;
				//如果是针对单文件
				if (fileName != "all")
				{
					//base
					if (args[2].get_string() == "base")
					{
						cout << resetiosflags(ios::right) << setiosflags(ios::left) << setw(3) << cnt_file << ": " << row_stu[2] << "/" << resetiosflags(ios::right) << setiosflags(ios::left) << setw(max_len_name) << name << "  : ";
						Check result = checkfilebase(src_rootdir + cno2 + '-' + row_stu[2] + '/' + row_hw[5]);
						switch (result) {
							case FILE_NOT_FOUND:
								std::cout << "未提交\n";
								cnt_not_submit++;
								cnt_not_submit_all++;
								break;
							case NOT_VS:
								cnt_not_vs++;
								cnt_not_vs_all++;
								std::cout << "源文件格式不正确(VS无法识别)\n";
								break;
							case NOT_PDF:
								cnt_not_pdf++;
								cnt_not_pdf_all++;
								std::cout << "PDF文件格式不正确\n";
								break;
							case CORRECT:
								std::cout << "正确\n";
								cnt_correct++;
								cnt_correct_all++;
								break;
							case INVALID_ENCODING:
								cnt_not_GB++;
								cnt_not_GB_all++;
								std::cout << "源文件格式不正确(非GB编码)\n";
								break;
						}
					}
					//firstline
					if (args[2].get_string() == "firstline")
					{
						cout << resetiosflags(ios::right) << setiosflags(ios::left) << setw(3) << cnt_file << ": " << row_stu[2] << "/" << resetiosflags(ios::right) << setiosflags(ios::left) << setw(max_len_name) << name << "  : ";
						if (!fileExists(src_rootdir + cno2 + '-' + row_stu[2] + '/' + row_hw[5]))
						{
							std::cout << "未提交\n";
							cnt_not_submit++;
							cnt_not_submit_all++;
							continue;
						}
						if (isUTF8(src_rootdir + cno2 + '-' + row_stu[2] + '/' + row_hw[5])) {
							cnt_not_GB++;
							cnt_not_GB_all++;
							std::cout << "源文件格式不正确(非GB编码)\n";
							continue;
						}
						if (checkvs(src_rootdir + cno2 + '-' + row_stu[2] + '/' + row_hw[5]))
						{
							cnt_not_vs++;
							cnt_not_vs_all++;
							std::cout << "源文件格式不正确(VS无法识别)\n";
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
								std::cout << "未提交\n";
								cnt_not_submit++;
								cnt_not_submit_all++;
								break;
							case CORRECT:
								std::cout << "正确\n";
								cnt_correct++;
								cnt_correct_all++;
								break;
							case INVALID_ENCODING:
								cnt_not_GB++;
								cnt_not_GB_all++;
								std::cout << "源文件格式不正确(非GB编码)\n";
								break;
							case FIRSTLINE_NOT_DEFINE:
								cnt_first_not_define++;
								cnt_first_not_define_all++;
								cout << "首行不是注释行 [" << firstline << "]" << endl;
								break;
							case FIRSTLINE_NOT_3_ITEMS:
								cnt_first_not_3++;
								cnt_first_not_3_all++;
								cout << "首行不是三项 [" << firstline << "]" << endl;
								break;
							case FIRSTLINE_ERROR:
								cnt_first_error++;
								cnt_first_error_all++;
								cout << " [" << firstline << "]" << endl;
								break;
							case FIRSTLINE_MULTIERROR:
								cnt_first_multierror++;
								cnt_first_multierror_all++;
								cout << "首行不是符合要求的/* */格式 [" << firstline << "]" << endl;
								break;
						}
					}
					if (args[2].get_string() == "secondline")
					{
						cout << resetiosflags(ios::right) << setiosflags(ios::left) << setw(3) << cnt_file << ": " << row_stu[2] << "/" << resetiosflags(ios::right) << setiosflags(ios::left) << setw(max_len_name) << name << " : ";
						if (!fileExists(src_rootdir + cno2 + '-' + row_stu[2] + '/' + row_hw[5]))
						{
							std::cout << "未提交\n";
							cnt_not_submit++;
							cnt_not_submit_all++;
							continue;
						}
						if (isUTF8(src_rootdir + cno2 + '-' + row_stu[2] + '/' + row_hw[5])) {
							cnt_not_GB++;
							cnt_not_GB_all++;
							std::cout << "源文件格式不正确(非GB编码)\n";
							continue;
						}
						if (checkvs(src_rootdir + cno2 + '-' + row_stu[2] + '/' + row_hw[5]))
						{
							cnt_not_vs++;
							cnt_not_vs_all++;
							std::cout << "源文件格式不正确(VS无法识别)\n";
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
						}//拿到第二行
						Check result = checkfilesecond(secondline, row_stu[2]);
						switch (result) {
							case CORRECT:
								std::cout << "正确\n";
								cnt_correct++;
								cnt_correct_all++;
								break;
							case NOT_DOUBLE:
								//std::cout << "正确\n";
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
								std::cout << "次行不是注释\n";
								cnt_second_not_define++;
								cnt_second_not_define_all++;
								break;
						}
					}
				}
				else//如果是all文件则全部执行
				{
					//base
					if (args[2].get_string() == "base")
					{
						cout << "  " << resetiosflags(ios::right) << setiosflags(ios::left) << setw(maxline_row_hw) << row_hw[5] << ": ";//文件名
						Check result = checkfilebase(src_rootdir + cno2 + '-' + row_stu[2] + '/' + row_hw[5]);
						//cout << src_rootdir + cno + '-' + stuNo + '/' + row_hw[5] << endl;
						switch (result) {
							case FILE_NOT_FOUND:
								std::cout << "未提交\n";
								cnt_not_submit++;
								cnt_not_submit_all++;
								break;
							case NOT_VS:
								cnt_not_vs++;
								cnt_not_vs_all++;
								std::cout << "源文件格式不正确(VS无法识别)\n";
							case NOT_PDF:
								cnt_not_pdf++;
								cnt_not_pdf_all++;
								std::cout << "PDF文件格式不正确\n";
								break;
							case CORRECT:
								std::cout << "正确\n";
								cnt_correct++;
								cnt_correct_all++;
								break;
							case INVALID_ENCODING:
								cnt_not_GB++;
								cnt_not_GB_all++;
								std::cout << "源文件格式不正确(非GB编码)\n";
								break;
						}
					}
					//firstline
					if (args[2].get_string() == "firstline")
					{
						if (!fileExists(src_rootdir + cno2 + '-' + row_stu[2] + '/' + row_hw[5]))
						{
							cout << "  " << resetiosflags(ios::right) << setiosflags(ios::left) << setw(maxline_row_hw) << row_hw[5] << ": ";//文件名
							std::cout << "未提交\n";
							cnt_not_submit++;
							cnt_not_submit_all++;
							continue;
						}
						if (isUTF8(src_rootdir + cno2 + '-' + row_stu[2] + '/' + row_hw[5])) {
							cout << "  " << resetiosflags(ios::right) << setiosflags(ios::left) << setw(maxline_row_hw) << row_hw[5] << ": ";//文件名
							cnt_not_GB++;
							cnt_not_GB_all++;
							std::cout << "源文件格式不正确(非GB编码)\n";
							continue;
						}
						if (checkvs(src_rootdir + cno2 + '-' + row_stu[2] + '/' + row_hw[5]))
						{
							cnt_not_vs++;
							cnt_not_vs_all++;
							std::cout << "源文件格式不正确(VS无法识别)\n";
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
						cout << "  " << resetiosflags(ios::right) << setiosflags(ios::left) << setw(maxline_row_hw) << row_hw[5] << ": ";//文件名
						Check result = checkfilefirst(firstline, row_stu, row_stu[2], row_stu[3]);
						switch (result) {
							case FILE_NOT_FOUND:
								std::cout << "未提交\n";
								cnt_not_submit++;
								cnt_not_submit_all++;
								break;
							case CORRECT:
								std::cout << "正确\n";
								cnt_correct++;
								cnt_correct_all++;
								break;
							case INVALID_ENCODING:
								cnt_not_GB++;
								cnt_not_GB_all++;
								std::cout << "源文件格式不正确(非GB编码)\n";
								break;
							case FIRSTLINE_NOT_DEFINE:
								cnt_first_not_define++;
								cnt_first_not_define_all++;
								cout << "首行不是注释行 [" << firstline << "]" << endl;
								break;
							case FIRSTLINE_NOT_3_ITEMS:
								cnt_first_not_3++;
								cnt_first_not_3_all++;
								cout << "首行不是三项 [" << firstline << "]" << endl;
								break;
							case FIRSTLINE_ERROR:
								cnt_first_error++;
								cnt_first_error_all++;
								cout << " [" << firstline << "]" << endl;
								break;
							case FIRSTLINE_MULTIERROR:
								cnt_first_multierror++;
								cnt_first_multierror_all++;
								cout << "首行不是符合要求的/* */格式 [" << firstline << "]" << endl;
								break;
						}
					}
				}
			}
			if (args[2].get_string() == "base")
			{
				//所有文件base
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
						cout << "全部通过" << cnt_correct << "/" << cnt_hwnum << "个文件，本次通过" << cnt_correct << "个" << endl;
					else
						cout << "检查通过" << cnt_correct << "/" << cnt_hwnum << "个文件，本次通过" << cnt_correct << "个" << endl;
					for (int i = 1; i <= width; i++)
						cout << "-";
					cout << endl;
					cout << "学生详细信息" << endl;
					for (int i = 1; i <= width; i++)
						cout << "-";
					cout << endl;
					if (cnt_correct)
						cout << setw(width - 10) << resetiosflags(ios::right) << setiosflags(ios::right) << "正确" << " : " << cnt_correct << endl;
					if (cnt_not_submit)
						cout << setw(width - 10) << resetiosflags(ios::right) << setiosflags(ios::right) << "未提交" << " : " << cnt_not_submit << endl;
					if (cnt_not_pdf)
						cout << setw(width - 10) << resetiosflags(ios::right) << setiosflags(ios::right) << "PDF文件格式不正确" << " : " << cnt_not_pdf << endl;
					if (cnt_not_vs)
						cout << setw(width - 10) << resetiosflags(ios::right) << setiosflags(ios::right) << "源文件格式不正确(VS无法识别)" << " : " << cnt_not_vs << endl;
					if (cnt_not_GB)
						cout << setw(width - 10) << resetiosflags(ios::right) << setiosflags(ios::right) << "源文件格式不正确(非GB编码)" << " : " << cnt_not_GB << endl;
					for (int i = 1; i <= width; i++)
						cout << "-";
					cout << endl;
					cout << endl;
				}
				//单独文件base
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
						cout << "全部通过" << cnt_correct << "/" << cnt_hwnum << "个文件，本次通过" << cnt_correct << "个" << endl;
					else
						cout << "检查通过" << cnt_correct << "/" << cnt_hwnum << "个文件，本次通过" << cnt_correct << "个" << endl;
					for (int i = 1; i <= width; i++)
						cout << "-";
					cout << endl;
					cout << "学生详细信息" << endl;
					for (int i = 1; i <= width; i++)
						cout << "-";
					cout << endl;
					if (cnt_correct)
						cout << setw(width - 10) << resetiosflags(ios::right) << setiosflags(ios::right) << "正确" << " : " << cnt_correct << endl;
					if (cnt_not_submit)
						cout << setw(width - 10) << resetiosflags(ios::right) << setiosflags(ios::right) << "未提交" << " : " << cnt_not_submit << endl;
					if (cnt_not_vs)
						cout << setw(width - 10) << resetiosflags(ios::right) << setiosflags(ios::right) << "源文件格式不正确(VS无法识别)" << " : " << cnt_not_vs << endl;
					if (cnt_not_GB)
						cout << setw(width - 10) << resetiosflags(ios::right) << setiosflags(ios::right) << "源文件格式不正确(非GB编码)" << " : " << cnt_not_GB << endl;
					if (cnt_first_multierror)
						cout << setw(width - 10) << resetiosflags(ios::right) << setiosflags(ios::right) << "首行多行注释格式不正确" << " : " << cnt_first_multierror << endl;
					if (cnt_first_not_define)
						cout << setw(width - 10) << resetiosflags(ios::right) << setiosflags(ios::right) << "首行不是注释行" << " : " << cnt_first_not_define << endl;
					if (cnt_first_not_3)
						cout << setw(width - 10) << resetiosflags(ios::right) << setiosflags(ios::right) << "首行不是三项" << " : " << cnt_first_not_3 << endl;
					if (cnt_first_error)
						cout << setw(width - 10) << resetiosflags(ios::right) << setiosflags(ios::right) << "首行检查出错" << " : " << cnt_first_error << endl;
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
			/* 释放result，否则会丢失内存 */
			mysql_free_result(result_hw);
			/* 关闭整个连接 */
			mysql_close(mysql_hw);
		}
		/* 释放result，否则会丢失内存 */
		mysql_free_result(result_stu);
	}


	cout  << endl ;
	if (args[2].get_string() == "base")//检查base行总结
	{
		//每个人的全部base 一个人的全部bases
		if(fileName == "all") 
		{
			cout << "共完成" << cnt_stu << "个学生的检查，文件总数:" << cnt_file << "，通过总数:" << cnt_correct_all << "，本次通过" << cnt_correct_all<<"个" << endl;
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
			cout << "整体详细信息" << endl;
			for (int i = 1; i <= width; i++)
				cout << "=";
			cout << endl;
			if (cnt_correct_all)
				cout << setw(width - 10) << resetiosflags(ios::right) << setiosflags(ios::right) << "正确" << " : " << cnt_correct_all << endl;
			if (cnt_not_submit_all)
				cout << setw(width - 10) << resetiosflags(ios::right) << setiosflags(ios::right) << "未提交" << " : " << cnt_not_submit_all << endl;
			if (cnt_not_pdf_all)
				cout << setw(width - 10) << resetiosflags(ios::right) << setiosflags(ios::right) << "PDF文件格式不正确" << " : " << cnt_not_pdf_all << endl;
			if (cnt_not_vs_all)
				cout << setw(width - 10) << resetiosflags(ios::right) << setiosflags(ios::right) << "源文件格式不正确(VS无法识别)" << " : " << cnt_not_vs_all << endl;
			if (cnt_not_GB_all)
				cout << setw(width-10) << resetiosflags(ios::right) << setiosflags(ios::right) << "源文件格式不正确(非GB编码)" << " : " << cnt_not_GB_all << endl;
			for (int i = 1; i <= width; i++)
				cout << "=";
			cout << endl;
			cout << endl;
		}
		//单个文件的base，考虑检查所有人的列表和单个人的列表
		else
		{
			cout << "检查通过" << cnt_correct_all << "/" <<cnt_stu << "个学生" "，本次通过" << cnt_correct_all <<"个"<< endl;
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
			cout << "详细信息" << endl;
			for (int i = 1; i <= width; i++)
				cout << "=";
			cout << endl;
			if (cnt_correct_all)
				cout << setw(width - 10) << resetiosflags(ios::right) << setiosflags(ios::right) << "正确" << " : " << cnt_correct_all << endl;
			if (cnt_not_submit_all)
				cout << setw(width - 10) << resetiosflags(ios::right) << setiosflags(ios::right) << "未提交" << " : " << cnt_not_submit_all << endl;
			if (cnt_not_pdf_all)
				cout << setw(width - 10) << resetiosflags(ios::right) << setiosflags(ios::right) << "PDF文件格式不正确" << " : " << cnt_not_pdf_all << endl;
			if (cnt_not_vs_all)
				cout << setw(width - 10) << resetiosflags(ios::right) << setiosflags(ios::right) << "源文件格式不正确(VS无法识别)" << " : " << cnt_not_vs_all << endl;
			if (cnt_not_GB_all)
				cout << setw(width - 10) << resetiosflags(ios::right) << setiosflags(ios::right) << "源文件格式不正确(非GB编码)" << " : " << cnt_not_GB_all << endl;
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
			cout << "共完成" << cnt_stu << "个学生的检查，文件总数:" << cnt_file << "，通过总数:" << cnt_correct_all << "，本次通过" << cnt_correct_all << "个" << endl;
			for (int i = 1; i <= width; i++)
				cout << "=";
			cout << endl;
			cout << "整体详细信息" << endl;
			for (int i = 1; i <= width; i++)
				cout << "=";
			cout << endl;
			if (cnt_correct_all)
				cout << setw(width - 10) << resetiosflags(ios::right) << setiosflags(ios::right) << "正确" << " : " << cnt_correct_all << endl;
			if (cnt_not_submit_all)
				cout << setw(width - 10) << resetiosflags(ios::right) << setiosflags(ios::right) << "未提交" << " : " << cnt_not_submit_all << endl;
			if (cnt_not_vs_all)
				cout << setw(width - 10) << resetiosflags(ios::right) << setiosflags(ios::right) << "源文件格式不正确(VS无法识别)" << " : " << cnt_not_vs_all << endl;
			if (cnt_not_GB_all)
				cout << setw(width - 10) << resetiosflags(ios::right) << setiosflags(ios::right) << "源文件格式不正确(非GB编码)" << " : " << cnt_not_GB_all << endl;
			if (cnt_first_multierror_all)
				cout << setw(width - 10) << resetiosflags(ios::right) << setiosflags(ios::right) << "首行多行注释格式不正确" << " : " << cnt_first_multierror_all << endl;
			if (cnt_first_not_define_all)
				cout << setw(width - 10) << resetiosflags(ios::right) << setiosflags(ios::right) << "首行不是注释行" << " : " << cnt_first_not_define_all << endl;
			if (cnt_first_not_3_all)
				cout << setw(width - 10) << resetiosflags(ios::right) << setiosflags(ios::right) << "首行不是三项" << " : " << cnt_first_not_3_all << endl;
			if (cnt_first_error_all)
				cout << setw(width - 10) << resetiosflags(ios::right) << setiosflags(ios::right) << "首行检查出错" << " : " << cnt_first_error_all << endl;
			for (int i = 1; i <= width; i++)
				cout << "=";
			cout << endl;
			cout << endl;
		}
		//单个文件
		else
		{
			cout << "检查通过" << cnt_correct_all << "/" << cnt_stu << "个学生" "，本次通过" << cnt_correct_all << "个" << endl;
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
			cout << "详细信息" << endl;
			for (int i = 1; i <= width; i++)
				cout << "=";
			cout << endl;
			if (cnt_correct_all)
				cout << setw(width - 10) << resetiosflags(ios::right) << setiosflags(ios::right) << "正确" << " : " << cnt_correct_all << endl;
			if (cnt_not_submit_all)
				cout << setw(width - 10) << resetiosflags(ios::right) << setiosflags(ios::right) << "未提交" << " : " << cnt_not_submit_all << endl;
			if (cnt_not_vs_all)
				cout << setw(width - 10) << resetiosflags(ios::right) << setiosflags(ios::right) << "源文件格式不正确(VS无法识别)" << " : " << cnt_not_vs_all << endl;
			if (cnt_not_GB_all)
				cout << setw(width - 10) << resetiosflags(ios::right) << setiosflags(ios::right) << "源文件格式不正确(非GB编码)" << " : " << cnt_not_GB_all << endl;
			if (cnt_first_multierror_all)
				cout << setw(width - 10) << resetiosflags(ios::right) << setiosflags(ios::right) << "首行多行注释格式不正确" << " : " << cnt_first_multierror_all << endl;
			if (cnt_first_not_define_all)
				cout << setw(width - 10) << resetiosflags(ios::right) << setiosflags(ios::right) << "首行不是注释行" << " : " << cnt_first_not_define_all << endl;
			if (cnt_first_not_3_all)
				cout << setw(width - 10) << resetiosflags(ios::right) << setiosflags(ios::right) << "首行不是三项" << " : " << cnt_first_not_3_all << endl;
			if (cnt_first_error_all)
				cout << setw(width - 10) << resetiosflags(ios::right) << setiosflags(ios::right) << "首行检查出错" << " : " << cnt_first_error_all << endl;
			for (int i = 1; i <= width; i++)
				cout << "=";
			cout << endl;
			cout << endl;
		}
	}
	if (args[2].get_string() == "secondline")
	{
		cout << "检查通过" << cnt_correct_all << "/" << cnt_stu << "个学生" "，本次通过" << cnt_correct_all << "个" << endl;
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
		cout << "详细信息" << endl;
		for (int i = 1; i <= width; i++)
			cout << "=";
		cout << endl;
		if (cnt_correct_all)
			cout << setw(width - 10) << resetiosflags(ios::right) << setiosflags(ios::right) << "正确" << " : " << cnt_correct_all << endl;
		if (cnt_not_submit_all)
			cout << setw(width - 10) << resetiosflags(ios::right) << setiosflags(ios::right) << "未提交" << " : " << cnt_not_submit_all << endl;
		if (cnt_not_vs_all)
			cout << setw(width - 10) << resetiosflags(ios::right) << setiosflags(ios::right) << "源文件格式不正确(VS无法识别)" << " : " << cnt_not_vs_all << endl;
		if (cnt_not_GB_all)
			cout << setw(width - 10) << resetiosflags(ios::right) << setiosflags(ios::right) << "源文件格式不正确(非GB编码)" << " : " << cnt_not_GB_all << endl;
		if (cnt_first_multierror_all)
			cout << setw(width - 10) << resetiosflags(ios::right) << setiosflags(ios::right) << "首行多行注释格式不正确" << " : " << cnt_first_multierror_all << endl;
		if (cnt_first_not_define_all)
			cout << setw(width - 10) << resetiosflags(ios::right) << setiosflags(ios::right) << "首行不是注释行" << " : " << cnt_first_not_define_all << endl;
		if (cnt_first_not_3_all)
			cout << setw(width - 10) << resetiosflags(ios::right) << setiosflags(ios::right) << "首行不是三项" << " : " << cnt_first_not_3_all << endl;
		if (cnt_first_error_all)
			cout << setw(width - 10) << resetiosflags(ios::right) << setiosflags(ios::right) << "首行检查出错" << " : " << cnt_first_error_all << endl;
		if (cnt_second_not_define_all)
			cout << setw(width - 10) << resetiosflags(ios::right) << setiosflags(ios::right) << "次行不是注释" << " : " << cnt_second_not_define_all << endl;
		for (int i = 1; i <= width; i++)
			cout << "=";
		cout << endl;
		cout << endl;
	}
	//cout << endl << cnt_stu << endl;
	

	//交叉验证
	if (args[2].get_string() == "secondline")
	{
		cout << "交叉检查结果：" << endl;
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
				}//拿到第二行
				cross.stu_list.push_back({ row_stu[2],row_stu[3],cno,secondline });
				//cout << row_stu[2] << " " << row_stu[3] << " " << cno << " " << secondline << endl;
			}

			/* 释放result，否则会丢失内存 */
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
				}//拿到第二行
				cross.stu_list.push_back({ row_stu[2],row_stu[3],cno2,secondline });
				//cout << row_stu[2] << " " << row_stu[3] << " " << cno2 << " " << secondline << endl;
			}

			/* 释放result，否则会丢失内存 */
			mysql_free_result(result_stu);
		}
		Crosscheck(cross);
		cout << endl;
	}

	return 0;
}

