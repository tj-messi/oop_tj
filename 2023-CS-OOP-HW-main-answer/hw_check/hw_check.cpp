/* 2150792 计科 牛禄阳 */
#define _CRT_SECURE_NO_WARNINGS
#include "hw_check.h"
#include "../include/class_aat.h"
#include "../include/class_crt.h"
#include "../include_mariadb_x86/mysql/mysql.h"
const char* CONFGROUPNAME = "[文件目录]";
const char* CONFITEMNAME = "src_rootdir";
const char* DEFSRCROOTDIR = "D:\\oop_hw_cpp\\BigHW\\hw_check\\23241-source\\";
/* 数据库相关常变量 */
const char* DBGROUPNAME = "[数据库]";
const char* DBITEM_HOST = "db_host";
const char* DBITEM_PORT = "db_port";
const char* DBITEM_NAME = "db_name";
const char* DBITEM_USERNAME = "db_username";
const char* DBITEM_PASSWD = "db_passwd";
const char* DBITEM_CURRTERM = "db_currterm";
const char* DEFDB_HOST = "10.80.42.244";
const int   DEFDB_PORT = 3306;
const char* DEFDB_NAME = "homework";
const char* DEFDB_USERNAME = "hwcheck";
const char* DEFDB_PASSWD = "hw_CheCk-For23241*oOP";
const char* DEFDB_CURRTERM = "2023/2024/1";

/* 通用函数，暂时放在类外 */
/* 1.检查cmd输入的参数stu是否合法 */
int  is_stuno_valid(const string& stuno)
{
    if (stuno.length() != 7)
        return 0;
    for (size_t i = 0; i < stuno.length(); i++)
        if (stuno[i] < '0' || stuno[i] > '9')
            return 0;
    return 1;
}
/* 2.检查文件是否为pdf文件 */
int  is_PDF_file(ifstream& fin)
{
    fin.clear();
    fin.seekg(0, ios::beg);
    char header[8];
    fin.read(header, 8);
    // 检查文件头是否以 "%PDF-1." 开头
    string pdfHeader(header, 7); // 读取前 7 个字符
    if (pdfHeader == "%PDF-1.")
    {
        char version = header[7];// 读取版本号字符
        if (version >= '0' && version <= '9')
            return 1;
    }
    return 0;
}
/* 3.检查源文件是否为UTF-8编码 */
static int preNUm(unsigned char byte) 
{
    unsigned char mask = 0x80;
    int num = 0;
    for (int i = 0; i < 8; i++) 
    {
        if ((byte & mask) == mask) 
        {
            mask = mask >> 1;
            num++;
        }
        else 
            break;
    }
    return num;
}
//int isUTF8(ifstream& fin)
//{
//    fin.clear();
//    fin.seekg(0, ios::beg);
//    unsigned char ch;
//    int num = 0;
//    while (1) 
//    {
//        ch = fin.get();
//        if (fin.eof()) 
//            break;
//        if ((ch & 0x80) == 0x00)         // 1字节, 0XXX_XXXX
//            continue;
//        else if ((num = preNUm(ch)) > 2) // preNUm返回首个字节8个bits中首个0前面1的个数，该数量也是该字符所使用的字节数
//        {
//            ch = fin.get();
//            if (fin.eof())
//                break;
//            for (int j = 0; j < num - 1; j++) 
//            {
//                if ((ch & 0xc0) != 0x80) //判断后面num - 1 个字节是不是都是10开头
//                    return 0;
//                ch = fin.get();
//                if (fin.eof())
//                    break;
//            }
//        }
//        else 
//            return 0;
//    }
//    return 1;
//}
int isUTF8(ifstream& fin)
{
    unsigned char temp_ch;
    bool ascii = true;
    fin.clear();
    fin.seekg(0, ios::beg);
    while (1) 
    {
        temp_ch = fin.get();
        if (fin.eof()) 
            break;
        if ((temp_ch & 0x80) == 0)          // 1字节
            ;
        else if ((temp_ch & 0xe0) == 0xc0)  // 2字节，110xxxxx
        { 
            temp_ch = fin.get();
            if (fin.eof()) 
                return 0;
            if ((temp_ch & 0xc0) != 0x80)
                return 0; 
            ascii = false;
        }
        else if ((temp_ch & 0xf0) == 0xe0)  // 3字节，1110xxxx
        { 
            for (int i = 0; i < 2; i++) 
            {
                temp_ch = fin.get();
                if (fin.eof()) 
                    return 0;
                if ((temp_ch & 0xc0) != 0x80)
                    return 0; 
            }
            ascii = false;
        }
        else if ((temp_ch & 0xf8) == 0xf0)  //4字节，11110xxx
        { 
            for (int i = 0; i < 3; i++) 
            {
                temp_ch = fin.get();
                if (fin.eof())
                    return 0;
                if ((temp_ch & 0xc0) != 0x80)
                    return 0; 
            }
            ascii = false;
        }
        else 
            return 0;
    }
    if (ascii) 
        return 0;
    else
        return 1;
}
/* 4.判断文件的种类:1.源程序文件;2.PDF文件;3.非pdf且非源程序文件的文件 */
int get_file_kind(const string& filename)
{
    size_t len = filename.length();
    size_t dotPos = string::npos;

    // 手动查找文件名中最后一个点的位置
    for (int i = len - 1; i >= 0; i--) 
    {
        if (filename[i] == '.') 
        {
            dotPos = i;
            break;
        }
    }
    if (dotPos != string::npos) {
        string extension = filename.substr(dotPos + 1);
        // 将扩展名转换为小写字母以进行比较
        for (char& c : extension)
            c = std::tolower(c);
        if (extension == "h" || extension == "hpp" || extension == "c" || extension == "cpp")
            return SOURCEFILE;
        else if (extension == "pdf")
            return PDFFILE;
        else
            return OTHERFILE;
    }
    return ERRORFILE; // 找不到文件名中的'.'，返回ERRORFILE
}
/* 5.忽视左右空格 */
void trim_left(vector<char>& line_content)
{
    while (!line_content.empty() && (line_content.front() == ' ' || line_content.front() == '\t'))
        line_content.erase(line_content.begin());
}
void trim_right(vector<char>& line_content)
{
    while (!line_content.empty() && (line_content.back() == ' ' || line_content.back() == '\t'))
        line_content.pop_back();
}
/* 6.是否为合法注释 */
int  is_validcomment(const vector<char>& firstlinecontent, vector<char>& comcontent)
{
    // 检测单行注释
    if (firstlinecontent[0] == '/' && firstlinecontent[1] == '/')
    {
        size_t startIdx = 2;
        comcontent.assign(firstlinecontent.begin() + startIdx, firstlinecontent.end());
        return 1; // 合法的单行注释（不考虑内容）
    }
    /* 检测多行注释 */
    size_t len = firstlinecontent.size();
    if (firstlinecontent[0] == '/' && firstlinecontent[1] == '*')
    {
        if (firstlinecontent[len - 1] == '/' && firstlinecontent[len - 2] == '*')
        {
            size_t startIdx = 2;
            comcontent.assign(firstlinecontent.begin() + startIdx, firstlinecontent.end() - 2);
            return 1; // 合法的多行注释（不考虑内容）
        }
        else
            return (int)FIRSTCOMERR; // 多行注释格式不正确
    }
    return (int)FIRSTNOTCOM; // 首行不是注释行
}
/* 7.按空格划分字符串 */
vector<string> splitBySpace(const vector<char>& comcontent)
{
    string str(comcontent.begin(), comcontent.end());
    // 使用 stringstream 分割字符串
    stringstream ss(str);
    istream_iterator<string> begin(ss), end;
    vector<string> result(begin, end);
    return result;
}

/* Student类的实现 */
Student::Student(const string& s1, const string& s2, const string& s3, const string& s4, const string& s5, const string& s6, const string& s7, const string& s8)
{
    term             = s1;
    grade            = s2;
    no               = s3;
    name             = s4;
    sex              = s5;
    majorfullname    = s6;
    majorshortname   = s7;
    cno              = s8;
}
Student::Student()
{
    term = "";
    grade = "";
    no = "";
    name = "";
    sex = "";
    majorfullname = "";
    majorshortname = "";
    cno = "";
}

/* HW类的实现 */
HW::HW(const string& s1, const string& s2, const string& s3, const string& s4, const string& s5, const string& s6, const string& s7)
{
    kind     = s1;
    cno      = s2;
    number   = s3;
    chapter  = s4;
    week     = s5;
    filename = s6;
    point    = s7;
}

/* Db_conf类的实现 */
/* 读hw_check.conf配置文件，参数是配置文件名，外部传入 */
int  Db_cnof::read_db_config(const string& cfgfile)
{
    string _cfgfile = cfgfile;
    replace(_cfgfile.begin(), _cfgfile.end(), '\\', '/'); // 替换
    cfgfile_read_tools cf(_cfgfile);
    if (!cf.is_open())
    {
        cerr << "无法打开配置文件[" << cfgfile << "]，结束运行." << endl;
        return 0;
    }
    /* 读取src_rootdir */
    if (cf.item_get_value(CONFGROUPNAME, CONFITEMNAME, DEFSRCROOTDIR, this->srcrootdir, false) < 0)
    {
        cerr << "取配置文件 [" << cfgfile << "] 的" << CONFGROUPNAME << "组的[" << CONFITEMNAME << "]项的值出错." << endl;
        return 0;
    }
    /* 读取数据库相关参数 */
    if (cf.item_get_value(DBGROUPNAME, DBITEM_HOST, DEFDB_HOST, this->dbhost, false) < 0)
    {
        cerr << "取配置文件 [" << cfgfile << "] 的" << DBGROUPNAME << "组的[" << DBITEM_HOST << "]项的值出错." << endl;
        return 0;
    }
    if (cf.item_get_value(DBGROUPNAME, DBITEM_PORT, 0, INT_MAX, DEFDB_PORT, this->dbport, false) < 0)
    {
        cerr << "取配置文件 [" << cfgfile << "] 的" << DBGROUPNAME << "组的[" << DBITEM_PORT << "]项的值出错." << endl;
        return 0;
    }
    if (cf.item_get_value(DBGROUPNAME, DBITEM_NAME, DEFDB_NAME, this->dbname, false) < 0)
    {
        cerr << "取配置文件 [" << cfgfile << "] 的" << DBGROUPNAME << "组的[" << DBITEM_NAME << "]项的值出错." << endl;
        return 0;
    }
    if (cf.item_get_value(DBGROUPNAME, DBITEM_USERNAME, DEFDB_USERNAME, this->dbusername, false) < 0)
    {
        cerr << "取配置文件 [" << cfgfile << "] 的" << DBGROUPNAME << "组的[" << DBITEM_USERNAME << "]项的值出错." << endl;
        return 0;
    }
    if (cf.item_get_value(DBGROUPNAME, DBITEM_PASSWD, DEFDB_PASSWD, this->dbpasswd, false) < 0)
    {
        cerr << "取配置文件 [" << cfgfile << "] 的" << DBGROUPNAME << "组的[" << DBITEM_PASSWD << "]项的值出错." << endl;
        return 0;
    }
    if (cf.item_get_value(DBGROUPNAME, DBITEM_CURRTERM, DEFDB_CURRTERM, this->dbcurrterm, false) < 0)
    {
        cerr << "取配置文件 [" << cfgfile << "] 的" << DBGROUPNAME << "组的[" << DBITEM_CURRTERM << "]项的值出错." << endl;
        return 0;
    }
    return 1;
}

/* hw_check类的部分实现 */
/* 1.读取命令行参数，检测并写入hwcheck对象中 */
int  hw_check::read_hwcheck_cmdpara(const args_analyse_tools* const args)
{
    if (args[OPT_ARGS_STU].get_string() != "all")
    {
        if (!is_stuno_valid(args[OPT_ARGS_STU].get_string()))
        {
            cout << "文件[" << args[OPT_ARGS_STU].get_string() << "]无法打开." << endl;
            cout << endl;
            cout << "[--严重错误--] 读取 [--stu] 指定的文件出错." << endl;
            return STUNOERROR;
        }
    }
    if (args[OPT_ARGS_CNO].get_string().length() != 8 && args[OPT_ARGS_CNO].get_string().length() != 13)
    {
        cout << "课号不是8/13位" << endl;
        return CNOERROR;
    }
    // 暂时认为其它参数正确，会在后续读取数据库时检测
    this->action = args[OPT_ARGS_ACTION].get_string();
    this->cno = args[OPT_ARGS_CNO].get_string();
    this->stu = args[OPT_ARGS_STU].get_string();
    this->file = args[OPT_ARGS_FILE].get_string();
    this->chapter = args[OPT_ARGS_CHAPTER].existed() ? args[OPT_ARGS_CHAPTER].get_int() : -1;
    this->week = args[OPT_ARGS_WEEK].existed() ? args[OPT_ARGS_WEEK].get_int() : -1;
    this->cfgfile = args[OPT_ARGS_CFGFILE].get_string();
    this->display = args[OPT_ARGS_DISPLAY].get_string();
    return 1;
}
/* 2.从数据库中读出：对应课号的对应学生的学生数据；对应课号的对应章节和周的文件数据 */
int  hw_check::read_db_content()
{
    MYSQL* mysql;
    MYSQL_RES* result;
    MYSQL_ROW  row;
    /* 初始化 mysql 变量，失败返回NULL */
    if ((mysql = mysql_init(NULL)) == NULL) {
        cerr << "mysql_init failed" << endl;
        return 0;
    }
    /* 连接数据库，失败返回NULL */
    if (mysql_real_connect(mysql, dbhost.c_str(), dbusername.c_str(), dbpasswd.c_str(), dbname.c_str(), dbport, NULL, 0) == NULL) {
        cerr << "mysql_real_connect failed(" << mysql_error(mysql) << ")" << endl;
        return 0;
    }
    /* 设置字符集，否则读出的字符乱码 */
    mysql_set_character_set(mysql, "gbk");
    /* 查询hwlist并保存，查询对应cno的chapter和week */
    string sql_hwquery_command = "select * from view_hwcheck_hwlist";
    sql_hwquery_command = sql_hwquery_command + " where hw_cno = " + cno;
    if (mysql_query(mysql, sql_hwquery_command.c_str())) {
        cerr << "mysql_query failed(" << mysql_error(mysql) << ")" << endl;
        return 0;
    }
    if ((result = mysql_store_result(mysql)) == NULL) {
        cout << "mysql_store_result failed" << endl;
        return 0;
    }
    if ((int)mysql_num_rows(result) <= 0){
        cerr << "mysql execute [call proc_hwcheck_get_stulist_for_multifile" << "(\"" << dbcurrterm << "\", \"" << cno << "\"); ] 查询到符合要求的记录为[0]." << endl;
        mysql_free_result(result);
        mysql_close(mysql);
        return 0;
    }
    mysql_free_result(result);
    if (chapter != -1)
        sql_hwquery_command = sql_hwquery_command + " and hw_chapter = " + to_string(chapter);
    if (week != -1)
        sql_hwquery_command = sql_hwquery_command + " and hw_week = " + to_string(week);
    if (mysql_query(mysql, sql_hwquery_command.c_str())) {
        cerr << "mysql_query failed(" << mysql_error(mysql) << ")" << endl;
        return 0;
    }
    if ((result = mysql_store_result(mysql)) == NULL) {
        cerr << "mysql_store_result failed" << endl;
        return 0;
    }
    if ((int)mysql_num_rows(result) <= 0) {
        cerr << "本次操作的学生数量为0/文件数量为0，未执行" << endl;
        mysql_free_result(result);
        mysql_close(mysql);
        return 0;
    }
    while ((row = mysql_fetch_row(result)) != NULL) {
        HW hw(row[0], row[1], row[2], row[3], row[4], row[5], row[6]);
        hwlist.push_back(hw);
    }
    mysql_free_result(result);
    /* 查询stulist并保存，查找对应cno的stu */
    string sql_stuquery_command = "select * from view_hwcheck_stulist";
    sql_stuquery_command = sql_stuquery_command + " where stu_cno = " + cno;
    if (stu != "all")
        sql_stuquery_command = sql_stuquery_command + " and stu_no = " + stu;
    if (mysql_query(mysql, sql_stuquery_command.c_str())) {
        cerr << "mysql_query failed(" << mysql_error(mysql) << ")" << endl;
        return 0;
    }
    if ((result = mysql_store_result(mysql)) == NULL) {
        cerr << "mysql_store_result failed" << endl;
        return 0;
    }
    if ((int)mysql_num_rows(result) <= 0) {
        cerr << "本次操作的学生数量为0/文件数量为0，未执行" << endl;
        mysql_free_result(result);
        mysql_close(mysql);
        return 0;
    }
    while ((row = mysql_fetch_row(result)) != NULL) {
        Student stu(row[0], row[1], row[2], row[3], row[4], row[5], row[6], row[7]);
        stulist.push_back(stu);
    }
    mysql_free_result(result);
    /* 关闭整个连接 */
    mysql_close(mysql);
    
    /* checkfirst需要对读到的文件进行处理 */
    if (this->action == "firstline")
    {
        if (this->file == "all")
        {
            for (auto it = hwlist.begin(); it != hwlist.end();)
            {
                if (get_file_kind(it->filename) != SOURCEFILE)
                    it = hwlist.erase(it);
                else
                    ++it;
            }
        }
        else
        {
            if (get_file_kind(this->file) != SOURCEFILE)
            {
                cerr << "首行检查的文件[" << this->file << "]必须是源程序文件." << endl;
                return 0;
            }
        }
    }
    else if (this->action == "secondline")
    {
        if(get_file_kind(this->file) != SOURCEFILE)
        {
            cerr << "次行检查的文件[" << this->file << "]必须是源程序文件." << endl;
            return 0;
        }
    }
    
    return 1;
}
/* 3.得到stulist中的最大长度 */
int  hw_check::maxstunamelen()
{
    int maxlen = 0;
    for (size_t i = 0; i < this->stulist.size(); i++)
    {
        int templen = this->stulist[i].name.length();
        maxlen = max(maxlen, templen);
    }
    return maxlen;
}
/* 4.得到hwlist中的最大长度 */
int  hw_check::maxhwfilelen()
{
    int maxlen = 0;
    for (size_t i = 0; i < this->hwlist.size(); i++)
    {
        int templen = this->hwlist[i].filename.length();
        maxlen = max(maxlen, templen);
    }
    return maxlen;
}
/* 5.choice分为三个，0代表file!=all的结尾;1代表file==all的每个学生;2代表file==all的结尾 */
void hw_check::print_hw_check_result(int choice, const int filestatus_num[], const int total_filestatus_num[])
{
    size_t maxlen = 0, filestatus_cnt = 0;
    int  secondlinestatus_set[] = { 0, 1, 3, 4, 10, 11, 12, 13, -1 };
    if (this->action == "base")
        filestatus_cnt = 4;
    else if (this->action == "firstline")
        filestatus_cnt = 10;
    else if (this->action == "secondline")
        filestatus_cnt = 14; 
    for (size_t i = 0; i < filestatus_cnt; i++)
    {
        if (this->action != "base" && i == 2)
            continue; 
        if (this->action == "secondline")
        {
            size_t j = 0;
            for (; secondlinestatus_set[j] != -1; j++)
            {
                if (i == secondlinestatus_set[j])
                    break;
            }
            if (secondlinestatus_set[j] == -1)
                continue;
        }
        if ((choice == 1 || choice == 0) && filestatus_num[i] != 0)
            maxlen = max(FILESTATUS_STR[i].length(), maxlen);
        if (choice == 2 && total_filestatus_num[i] != 0)
            maxlen = max(FILESTATUS_STR[i].length(), maxlen);
    }
    cout << setiosflags(ios::right);
    char setfill_char = '=';
    int  setw_word = 2, setw_seg = 12;
    if (choice == 1)
        setfill_char = '-';
    cout << setfill(setfill_char) << setw(setw_seg + maxlen) << setfill_char << endl;
    if (choice == 0)
        cout << "详细信息" << endl;
    else if (choice == 1)
        cout << "学生详细信息" << endl;
    else if (choice == 2)
        cout << "整体详细信息" << endl;
    cout << setfill(setfill_char) << setw(setw_seg + maxlen) << setfill_char << endl;
    cout << setfill(' ');
    for (size_t i = 0; i <= filestatus_cnt; i++)
    {
        if (this->action != "base" && i == 2)
            continue; // 除base外，不是PDF
        if (this->action == "secondline")
        {
            size_t j = 0;
            for (; secondlinestatus_set[j] != -1; j++)
            {
                if (i == secondlinestatus_set[j])
                    break;
            }
            if (secondlinestatus_set[j] == -1)
                continue;
        }
        if (choice == 2 && total_filestatus_num[i] != 0)
        {
            cout << setw(maxlen + setw_word) << FILESTATUS_STR[i] << " : ";
            cout << total_filestatus_num[i] << endl;
        }
        if ((choice == 1 || choice == 0) && filestatus_num[i] != 0)
        {
            if (this->action == "secondline") // 需要对secondline进行特殊处理
            {
                if (i == OTHERERR)
                    continue; // 与PASS合并，不需要单独打印
                cout << setw(maxlen + setw_word) << FILESTATUS_STR[i] << " : ";
                if (i == PASS)
                    cout << filestatus_num[i] + filestatus_num[OTHERERR] << endl;
                else
                    cout << filestatus_num[i] << endl;
            }
            else
            {
                cout << setw(maxlen + setw_word) << FILESTATUS_STR[i] << " : ";
                cout << filestatus_num[i] << endl;
            }
        }
    }
    cout << setfill(setfill_char) << setw(setw_seg + maxlen) << setfill_char << endl;
    cout << resetiosflags(ios::right) << setiosflags(ios::left);
    cout << setfill(' ');
}
/* 6.hw_check最重要的检测函数，三合一 */
int  hw_check::hw_check_threeinone()
{
    /* 1.得到最大学生和文件长度，控制输出格式 */
    int Maxstulen = maxstunamelen();
    int Maxhwfilelen = maxhwfilelen();
    cout << setiosflags(ios::left);
    /* 2.得到对应的filepath */
    bool file_is_all = this->file == "all" ? true : false; // 根据file是否为all分类，是all需要遍历数据库中所有filename
    int stunum_cnt = 0;
    int filestatus_num[FILESTATUS_NUM] = { 0 };
    int total_filestatus_num[FILESTATUS_NUM] = { 0 };
    vector<vector<Student>> total_check_stulist; // 次行的所有互验学生名单
    if (!file_is_all)
        cout << "课号 : " << cno << " 学生数量 : " << stulist.size() << " 源文件名 : " << this->file << endl;
    for (const auto& student : this->stulist) // 遍历学生
    {
        if (file_is_all)
            cout << setw(3) << ++stunum_cnt << ": 学号-" << student.no << " 姓名-" << student.name << " 课号-" << student.cno << " 文件数量-" << hwlist.size() << endl;
        else
            cout << setw(3) << ++stunum_cnt << ": " << student.no << "/" << setw(Maxstulen) << student.name << " : ";
        for (const auto& hwfile : this->hwlist) // 遍历作业
        {
            string filepath = srcrootdir;
            filepath = filepath + student.cno + "-" + student.no + "\\";
            filepath += file_is_all ? hwfile.filename : this->file;
            string filename = file_is_all ? hwfile.filename : this->file;
            if (file_is_all)
                cout << "  " << setw(Maxhwfilelen) << hwfile.filename << " : ";
            /* 检查每个文件的状态 */
            FILE_STATUS filestatus;
            if (this->action == "base")
            {
                filestatus = get_basefilestatus(filepath, filename);
                print_basefilestatus(filestatus);
            }
            else if (this->action == "firstline")
            {
                filestatus = getaprint_firfilestatus(filepath, filename, student);
            }
            else if (this->action == "secondline")
            {
                vector<Student> check_stulist; // 次行的互验学生名单
                filestatus = getaprint_secfilestatus(filepath, check_stulist, student.no);
                if (filestatus == OTHERERR)
                    filestatus = PASS; // 特殊判断
                total_check_stulist.push_back(check_stulist);
            }
            ++filestatus_num[filestatus];
            if (!file_is_all)
                break; // 如果file不是all，内循环只执行一次
        }
        if (file_is_all)
        {
            /*total_filestatus_num[NOTSUBMIT] += filestatus_num[NOTSUBMIT], total_filestatus_num[PASS] += filestatus_num[PASS];
            total_filestatus_num[ERRPDF] += filestatus_num[ERRPDF], total_filestatus_num[NOTGB] += filestatus_num[NOTGB];*/
            for (size_t i = 0; i < FILESTATUS_NUM; i++)
                total_filestatus_num[i] += filestatus_num[i];
            if (filestatus_num[PASS] == (int)hwlist.size())
                cout << "全部通过" << filestatus_num[PASS] << "/" << hwlist.size() << "个文件，本次通过" << filestatus_num[PASS] << "个" << endl;
            else
                cout << "检查通过" << filestatus_num[PASS] << "/" << hwlist.size() << "个文件，本次通过" << filestatus_num[PASS] << "个" << endl;
            print_hw_check_result(1, filestatus_num, total_filestatus_num);// 打印信息1
            memset(filestatus_num, 0, sizeof(filestatus_num));
            cout << endl;
        }
    }
    cout << endl;
    if (file_is_all)
    {
        cout << "共完成" << stulist.size() << "个学生的检查，文件总数:" << stulist.size() * hwlist.size() << "，通过总数:" << total_filestatus_num[PASS] << "，本次通过" << total_filestatus_num[PASS] << "个" << endl;
        print_hw_check_result(2, filestatus_num, total_filestatus_num); // 打印信息2
        cout << endl;
    }
    else
    {
        if (filestatus_num[PASS] == this->stulist.size())
            cout << "全部通过" << filestatus_num[PASS] << "/" << stulist.size() << "个学生，本次通过" << filestatus_num[PASS] << "个" << endl;
        else
            cout << "检查通过" << filestatus_num[PASS] << "/" << stulist.size() << "个学生，本次通过" << filestatus_num[PASS] << "个" << endl;
        print_hw_check_result(0, filestatus_num, total_filestatus_num); // 打印信息0
    }
    cout << endl;
    if (this->action == "secondline")
    {
        Stucrossheck(total_check_stulist, stulist);
        cout << endl;
    }
    return 0;
}
