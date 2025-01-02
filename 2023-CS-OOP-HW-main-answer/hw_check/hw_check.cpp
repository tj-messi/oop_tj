/* 2150792 �ƿ� ţ»�� */
#define _CRT_SECURE_NO_WARNINGS
#include "hw_check.h"
#include "../include/class_aat.h"
#include "../include/class_crt.h"
#include "../include_mariadb_x86/mysql/mysql.h"
const char* CONFGROUPNAME = "[�ļ�Ŀ¼]";
const char* CONFITEMNAME = "src_rootdir";
const char* DEFSRCROOTDIR = "D:\\oop_hw_cpp\\BigHW\\hw_check\\23241-source\\";
/* ���ݿ���س����� */
const char* DBGROUPNAME = "[���ݿ�]";
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

/* ͨ�ú�������ʱ�������� */
/* 1.���cmd����Ĳ���stu�Ƿ�Ϸ� */
int  is_stuno_valid(const string& stuno)
{
    if (stuno.length() != 7)
        return 0;
    for (size_t i = 0; i < stuno.length(); i++)
        if (stuno[i] < '0' || stuno[i] > '9')
            return 0;
    return 1;
}
/* 2.����ļ��Ƿ�Ϊpdf�ļ� */
int  is_PDF_file(ifstream& fin)
{
    fin.clear();
    fin.seekg(0, ios::beg);
    char header[8];
    fin.read(header, 8);
    // ����ļ�ͷ�Ƿ��� "%PDF-1." ��ͷ
    string pdfHeader(header, 7); // ��ȡǰ 7 ���ַ�
    if (pdfHeader == "%PDF-1.")
    {
        char version = header[7];// ��ȡ�汾���ַ�
        if (version >= '0' && version <= '9')
            return 1;
    }
    return 0;
}
/* 3.���Դ�ļ��Ƿ�ΪUTF-8���� */
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
//        if ((ch & 0x80) == 0x00)         // 1�ֽ�, 0XXX_XXXX
//            continue;
//        else if ((num = preNUm(ch)) > 2) // preNUm�����׸��ֽ�8��bits���׸�0ǰ��1�ĸ�����������Ҳ�Ǹ��ַ���ʹ�õ��ֽ���
//        {
//            ch = fin.get();
//            if (fin.eof())
//                break;
//            for (int j = 0; j < num - 1; j++) 
//            {
//                if ((ch & 0xc0) != 0x80) //�жϺ���num - 1 ���ֽ��ǲ��Ƕ���10��ͷ
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
        if ((temp_ch & 0x80) == 0)          // 1�ֽ�
            ;
        else if ((temp_ch & 0xe0) == 0xc0)  // 2�ֽڣ�110xxxxx
        { 
            temp_ch = fin.get();
            if (fin.eof()) 
                return 0;
            if ((temp_ch & 0xc0) != 0x80)
                return 0; 
            ascii = false;
        }
        else if ((temp_ch & 0xf0) == 0xe0)  // 3�ֽڣ�1110xxxx
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
        else if ((temp_ch & 0xf8) == 0xf0)  //4�ֽڣ�11110xxx
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
/* 4.�ж��ļ�������:1.Դ�����ļ�;2.PDF�ļ�;3.��pdf�ҷ�Դ�����ļ����ļ� */
int get_file_kind(const string& filename)
{
    size_t len = filename.length();
    size_t dotPos = string::npos;

    // �ֶ������ļ��������һ�����λ��
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
        // ����չ��ת��ΪСд��ĸ�Խ��бȽ�
        for (char& c : extension)
            c = std::tolower(c);
        if (extension == "h" || extension == "hpp" || extension == "c" || extension == "cpp")
            return SOURCEFILE;
        else if (extension == "pdf")
            return PDFFILE;
        else
            return OTHERFILE;
    }
    return ERRORFILE; // �Ҳ����ļ����е�'.'������ERRORFILE
}
/* 5.�������ҿո� */
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
/* 6.�Ƿ�Ϊ�Ϸ�ע�� */
int  is_validcomment(const vector<char>& firstlinecontent, vector<char>& comcontent)
{
    // ��ⵥ��ע��
    if (firstlinecontent[0] == '/' && firstlinecontent[1] == '/')
    {
        size_t startIdx = 2;
        comcontent.assign(firstlinecontent.begin() + startIdx, firstlinecontent.end());
        return 1; // �Ϸ��ĵ���ע�ͣ����������ݣ�
    }
    /* ������ע�� */
    size_t len = firstlinecontent.size();
    if (firstlinecontent[0] == '/' && firstlinecontent[1] == '*')
    {
        if (firstlinecontent[len - 1] == '/' && firstlinecontent[len - 2] == '*')
        {
            size_t startIdx = 2;
            comcontent.assign(firstlinecontent.begin() + startIdx, firstlinecontent.end() - 2);
            return 1; // �Ϸ��Ķ���ע�ͣ����������ݣ�
        }
        else
            return (int)FIRSTCOMERR; // ����ע�͸�ʽ����ȷ
    }
    return (int)FIRSTNOTCOM; // ���в���ע����
}
/* 7.���ո񻮷��ַ��� */
vector<string> splitBySpace(const vector<char>& comcontent)
{
    string str(comcontent.begin(), comcontent.end());
    // ʹ�� stringstream �ָ��ַ���
    stringstream ss(str);
    istream_iterator<string> begin(ss), end;
    vector<string> result(begin, end);
    return result;
}

/* Student���ʵ�� */
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

/* HW���ʵ�� */
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

/* Db_conf���ʵ�� */
/* ��hw_check.conf�����ļ��������������ļ������ⲿ���� */
int  Db_cnof::read_db_config(const string& cfgfile)
{
    string _cfgfile = cfgfile;
    replace(_cfgfile.begin(), _cfgfile.end(), '\\', '/'); // �滻
    cfgfile_read_tools cf(_cfgfile);
    if (!cf.is_open())
    {
        cerr << "�޷��������ļ�[" << cfgfile << "]����������." << endl;
        return 0;
    }
    /* ��ȡsrc_rootdir */
    if (cf.item_get_value(CONFGROUPNAME, CONFITEMNAME, DEFSRCROOTDIR, this->srcrootdir, false) < 0)
    {
        cerr << "ȡ�����ļ� [" << cfgfile << "] ��" << CONFGROUPNAME << "���[" << CONFITEMNAME << "]���ֵ����." << endl;
        return 0;
    }
    /* ��ȡ���ݿ���ز��� */
    if (cf.item_get_value(DBGROUPNAME, DBITEM_HOST, DEFDB_HOST, this->dbhost, false) < 0)
    {
        cerr << "ȡ�����ļ� [" << cfgfile << "] ��" << DBGROUPNAME << "���[" << DBITEM_HOST << "]���ֵ����." << endl;
        return 0;
    }
    if (cf.item_get_value(DBGROUPNAME, DBITEM_PORT, 0, INT_MAX, DEFDB_PORT, this->dbport, false) < 0)
    {
        cerr << "ȡ�����ļ� [" << cfgfile << "] ��" << DBGROUPNAME << "���[" << DBITEM_PORT << "]���ֵ����." << endl;
        return 0;
    }
    if (cf.item_get_value(DBGROUPNAME, DBITEM_NAME, DEFDB_NAME, this->dbname, false) < 0)
    {
        cerr << "ȡ�����ļ� [" << cfgfile << "] ��" << DBGROUPNAME << "���[" << DBITEM_NAME << "]���ֵ����." << endl;
        return 0;
    }
    if (cf.item_get_value(DBGROUPNAME, DBITEM_USERNAME, DEFDB_USERNAME, this->dbusername, false) < 0)
    {
        cerr << "ȡ�����ļ� [" << cfgfile << "] ��" << DBGROUPNAME << "���[" << DBITEM_USERNAME << "]���ֵ����." << endl;
        return 0;
    }
    if (cf.item_get_value(DBGROUPNAME, DBITEM_PASSWD, DEFDB_PASSWD, this->dbpasswd, false) < 0)
    {
        cerr << "ȡ�����ļ� [" << cfgfile << "] ��" << DBGROUPNAME << "���[" << DBITEM_PASSWD << "]���ֵ����." << endl;
        return 0;
    }
    if (cf.item_get_value(DBGROUPNAME, DBITEM_CURRTERM, DEFDB_CURRTERM, this->dbcurrterm, false) < 0)
    {
        cerr << "ȡ�����ļ� [" << cfgfile << "] ��" << DBGROUPNAME << "���[" << DBITEM_CURRTERM << "]���ֵ����." << endl;
        return 0;
    }
    return 1;
}

/* hw_check��Ĳ���ʵ�� */
/* 1.��ȡ�����в�������Ⲣд��hwcheck������ */
int  hw_check::read_hwcheck_cmdpara(const args_analyse_tools* const args)
{
    if (args[OPT_ARGS_STU].get_string() != "all")
    {
        if (!is_stuno_valid(args[OPT_ARGS_STU].get_string()))
        {
            cout << "�ļ�[" << args[OPT_ARGS_STU].get_string() << "]�޷���." << endl;
            cout << endl;
            cout << "[--���ش���--] ��ȡ [--stu] ָ�����ļ�����." << endl;
            return STUNOERROR;
        }
    }
    if (args[OPT_ARGS_CNO].get_string().length() != 8 && args[OPT_ARGS_CNO].get_string().length() != 13)
    {
        cout << "�κŲ���8/13λ" << endl;
        return CNOERROR;
    }
    // ��ʱ��Ϊ����������ȷ�����ں�����ȡ���ݿ�ʱ���
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
/* 2.�����ݿ��ж�������Ӧ�κŵĶ�Ӧѧ����ѧ�����ݣ���Ӧ�κŵĶ�Ӧ�½ں��ܵ��ļ����� */
int  hw_check::read_db_content()
{
    MYSQL* mysql;
    MYSQL_RES* result;
    MYSQL_ROW  row;
    /* ��ʼ�� mysql ������ʧ�ܷ���NULL */
    if ((mysql = mysql_init(NULL)) == NULL) {
        cerr << "mysql_init failed" << endl;
        return 0;
    }
    /* �������ݿ⣬ʧ�ܷ���NULL */
    if (mysql_real_connect(mysql, dbhost.c_str(), dbusername.c_str(), dbpasswd.c_str(), dbname.c_str(), dbport, NULL, 0) == NULL) {
        cerr << "mysql_real_connect failed(" << mysql_error(mysql) << ")" << endl;
        return 0;
    }
    /* �����ַ���������������ַ����� */
    mysql_set_character_set(mysql, "gbk");
    /* ��ѯhwlist�����棬��ѯ��Ӧcno��chapter��week */
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
        cerr << "mysql execute [call proc_hwcheck_get_stulist_for_multifile" << "(\"" << dbcurrterm << "\", \"" << cno << "\"); ] ��ѯ������Ҫ��ļ�¼Ϊ[0]." << endl;
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
        cerr << "���β�����ѧ������Ϊ0/�ļ�����Ϊ0��δִ��" << endl;
        mysql_free_result(result);
        mysql_close(mysql);
        return 0;
    }
    while ((row = mysql_fetch_row(result)) != NULL) {
        HW hw(row[0], row[1], row[2], row[3], row[4], row[5], row[6]);
        hwlist.push_back(hw);
    }
    mysql_free_result(result);
    /* ��ѯstulist�����棬���Ҷ�Ӧcno��stu */
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
        cerr << "���β�����ѧ������Ϊ0/�ļ�����Ϊ0��δִ��" << endl;
        mysql_free_result(result);
        mysql_close(mysql);
        return 0;
    }
    while ((row = mysql_fetch_row(result)) != NULL) {
        Student stu(row[0], row[1], row[2], row[3], row[4], row[5], row[6], row[7]);
        stulist.push_back(stu);
    }
    mysql_free_result(result);
    /* �ر��������� */
    mysql_close(mysql);
    
    /* checkfirst��Ҫ�Զ������ļ����д��� */
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
                cerr << "���м����ļ�[" << this->file << "]������Դ�����ļ�." << endl;
                return 0;
            }
        }
    }
    else if (this->action == "secondline")
    {
        if(get_file_kind(this->file) != SOURCEFILE)
        {
            cerr << "���м����ļ�[" << this->file << "]������Դ�����ļ�." << endl;
            return 0;
        }
    }
    
    return 1;
}
/* 3.�õ�stulist�е���󳤶� */
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
/* 4.�õ�hwlist�е���󳤶� */
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
/* 5.choice��Ϊ������0����file!=all�Ľ�β;1����file==all��ÿ��ѧ��;2����file==all�Ľ�β */
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
        cout << "��ϸ��Ϣ" << endl;
    else if (choice == 1)
        cout << "ѧ����ϸ��Ϣ" << endl;
    else if (choice == 2)
        cout << "������ϸ��Ϣ" << endl;
    cout << setfill(setfill_char) << setw(setw_seg + maxlen) << setfill_char << endl;
    cout << setfill(' ');
    for (size_t i = 0; i <= filestatus_cnt; i++)
    {
        if (this->action != "base" && i == 2)
            continue; // ��base�⣬����PDF
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
            if (this->action == "secondline") // ��Ҫ��secondline�������⴦��
            {
                if (i == OTHERERR)
                    continue; // ��PASS�ϲ�������Ҫ������ӡ
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
/* 6.hw_check����Ҫ�ļ�⺯��������һ */
int  hw_check::hw_check_threeinone()
{
    /* 1.�õ����ѧ�����ļ����ȣ����������ʽ */
    int Maxstulen = maxstunamelen();
    int Maxhwfilelen = maxhwfilelen();
    cout << setiosflags(ios::left);
    /* 2.�õ���Ӧ��filepath */
    bool file_is_all = this->file == "all" ? true : false; // ����file�Ƿ�Ϊall���࣬��all��Ҫ�������ݿ�������filename
    int stunum_cnt = 0;
    int filestatus_num[FILESTATUS_NUM] = { 0 };
    int total_filestatus_num[FILESTATUS_NUM] = { 0 };
    vector<vector<Student>> total_check_stulist; // ���е����л���ѧ������
    if (!file_is_all)
        cout << "�κ� : " << cno << " ѧ������ : " << stulist.size() << " Դ�ļ��� : " << this->file << endl;
    for (const auto& student : this->stulist) // ����ѧ��
    {
        if (file_is_all)
            cout << setw(3) << ++stunum_cnt << ": ѧ��-" << student.no << " ����-" << student.name << " �κ�-" << student.cno << " �ļ�����-" << hwlist.size() << endl;
        else
            cout << setw(3) << ++stunum_cnt << ": " << student.no << "/" << setw(Maxstulen) << student.name << " : ";
        for (const auto& hwfile : this->hwlist) // ������ҵ
        {
            string filepath = srcrootdir;
            filepath = filepath + student.cno + "-" + student.no + "\\";
            filepath += file_is_all ? hwfile.filename : this->file;
            string filename = file_is_all ? hwfile.filename : this->file;
            if (file_is_all)
                cout << "  " << setw(Maxhwfilelen) << hwfile.filename << " : ";
            /* ���ÿ���ļ���״̬ */
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
                vector<Student> check_stulist; // ���еĻ���ѧ������
                filestatus = getaprint_secfilestatus(filepath, check_stulist, student.no);
                if (filestatus == OTHERERR)
                    filestatus = PASS; // �����ж�
                total_check_stulist.push_back(check_stulist);
            }
            ++filestatus_num[filestatus];
            if (!file_is_all)
                break; // ���file����all����ѭ��ִֻ��һ��
        }
        if (file_is_all)
        {
            /*total_filestatus_num[NOTSUBMIT] += filestatus_num[NOTSUBMIT], total_filestatus_num[PASS] += filestatus_num[PASS];
            total_filestatus_num[ERRPDF] += filestatus_num[ERRPDF], total_filestatus_num[NOTGB] += filestatus_num[NOTGB];*/
            for (size_t i = 0; i < FILESTATUS_NUM; i++)
                total_filestatus_num[i] += filestatus_num[i];
            if (filestatus_num[PASS] == (int)hwlist.size())
                cout << "ȫ��ͨ��" << filestatus_num[PASS] << "/" << hwlist.size() << "���ļ�������ͨ��" << filestatus_num[PASS] << "��" << endl;
            else
                cout << "���ͨ��" << filestatus_num[PASS] << "/" << hwlist.size() << "���ļ�������ͨ��" << filestatus_num[PASS] << "��" << endl;
            print_hw_check_result(1, filestatus_num, total_filestatus_num);// ��ӡ��Ϣ1
            memset(filestatus_num, 0, sizeof(filestatus_num));
            cout << endl;
        }
    }
    cout << endl;
    if (file_is_all)
    {
        cout << "�����" << stulist.size() << "��ѧ���ļ�飬�ļ�����:" << stulist.size() * hwlist.size() << "��ͨ������:" << total_filestatus_num[PASS] << "������ͨ��" << total_filestatus_num[PASS] << "��" << endl;
        print_hw_check_result(2, filestatus_num, total_filestatus_num); // ��ӡ��Ϣ2
        cout << endl;
    }
    else
    {
        if (filestatus_num[PASS] == this->stulist.size())
            cout << "ȫ��ͨ��" << filestatus_num[PASS] << "/" << stulist.size() << "��ѧ��������ͨ��" << filestatus_num[PASS] << "��" << endl;
        else
            cout << "���ͨ��" << filestatus_num[PASS] << "/" << stulist.size() << "��ѧ��������ͨ��" << filestatus_num[PASS] << "��" << endl;
        print_hw_check_result(0, filestatus_num, total_filestatus_num); // ��ӡ��Ϣ0
    }
    cout << endl;
    if (this->action == "secondline")
    {
        Stucrossheck(total_check_stulist, stulist);
        cout << endl;
    }
    return 0;
}
