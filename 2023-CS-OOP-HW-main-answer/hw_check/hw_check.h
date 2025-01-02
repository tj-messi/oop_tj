/* 2150792 计科 牛禄阳 */
#pragma once
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <string>
#include <cstring>
#include <sstream>
#include <algorithm>
#include "../include/class_aat.h"
#include "../include_mariadb_x86/mysql/mysql.h"
using namespace std;

class hw_check;
class Student;
class HW;
/* 课号或学号错误 */
const int CNOERROR = -1;
const int STUNOERROR = -2;
/* 文件种类常变量 */
const int ERRORFILE = 0;
const int SOURCEFILE = 1;
const int PDFFILE = 2;
const int OTHERFILE = 3;
/* 文件的状态的string */
const string FILESTATUS_STR[] = { "正确" ,"未提交" , "PDF文件格式不正确" ,
"源文件格式不正确(非GB编码)" ,"文件小于3字节","无有效首行","首行多行注释格式不正确",
"首行不是注释行","首行不是三项","首行检查出错","文件小于两行", "次行不是注释","次行其它错误","" };
const int FILESTATUS_NUM = 14;

enum OPT_ARGS {
	OPT_ARGS_HELP = 0,
	OPT_ARGS_DEBUG,
	OPT_ARGS_ACTION,
	OPT_ARGS_CNO,
	OPT_ARGS_STU,
	OPT_ARGS_FILE,
	OPT_ARGS_CHAPTER,
	OPT_ARGS_WEEK,
	OPT_ARGS_DISPLAY,
	OPT_ARGS_CFGFILE,
};
enum FILE_STATUS {
	/* base */
	PASS = 0,      // 通过
	NOTSUBMIT,     // 未提交
	ERRPDF,        // 错误的PDF文件，只有base会使用
	NOTGB,         // 不符合GB编码
	/* first */
	LESS3BIT,      // 文件小于3字节
	NOFIRSTLINE,   // 无有效首行
	FIRSTCOMERR,   // 首行多行注释格式不正确
	FIRSTNOTCOM,   // 首行不是注释行
	FIRSTNOT3,     // 首行不是三项
	FIRSTERR,      // 首行检查出错
	/* second */
	LESS2LINE,     // 文件小于两行
	SECLINENOTCOM, // 次行不是注释
	SECLINEERR,    // 次行其它错误
	OTHERERR       // 检测出错，但仍正常继续
};

/* 公共的自定义函数 */
int  is_stuno_valid(const string& stuno);
int  get_file_kind(const string& filename);
int  isUTF8(ifstream& fin);
int  is_PDF_file(ifstream& fin);
void trim_left(vector<char>& line_content);
void trim_right(vector<char>& line_content);
int  is_validcomment(const vector<char>& firstlinecontent, vector<char>& comcontent);
vector<string> splitBySpace(const vector<char>& comcontent);

/*  check_base用的函数 */
FILE_STATUS get_basefilestatus(const string& filepath, const string& filename);
void print_basefilestatus(FILE_STATUS filestatus);

/* check_firstline用的函数 */
FILE_STATUS getaprint_firfilestatus(const string& filepath, const string& filename, const Student& student);

/* check_secondline用的函数 */
FILE_STATUS getaprint_secfilestatus(const string& filepath, vector<Student>& check_stulist, const string& own_no);
void Stucrossheck(const vector<vector<Student>>& total_check_stulist, const vector<Student>& total_stulist);

/* 类的声明 */
class Student {
	friend class hw_check;
	friend FILE_STATUS getaprint_secfilestatus(const string& filepath, vector<Student>& check_stulist, const string& own_no);
	friend FILE_STATUS getaprint_firfilestatus(const string& filepath, const string& filename, const Student& student);
	friend void Stucrossheck(const vector<vector<Student>>& total_check_stulist, const vector<Student>& total_stulist);
protected:
	string term;
	string grade;
	string no;
	string name;
	string sex;
	string majorfullname;
	string majorshortname;
	string cno;
public:
	Student();
	Student(const string& s1, const string& s2, const string& s3, const string& s4, const string& s5, const string& s6, const string& s7, const string& s8);
};

class HW {
	friend class hw_check;
protected:
	string kind;
	string cno;
	string number;
	string chapter;
	string week;
	string filename;
	string point;
public:
	HW(const string& s1, const string& s2, const string& s3, const string& s4, const string& s5, const string& s6, const string& s7);
};

class Db_cnof {
protected:
	string dbhost;
	int    dbport;
	string dbname;
	string dbusername;
	string dbpasswd;
	string dbcurrterm;
	string srcrootdir;
public:
	int  read_db_config(const string& cfgfile);
};

class hw_check : public Db_cnof {
protected:
	vector<Student> stulist;
	vector<HW>      hwlist;
public:
	string action;
	string cno;
	string stu;
	string file;
	string cfgfile;
	string display;
	int    chapter;
	int    week;
	int    read_hwcheck_cmdpara(const args_analyse_tools* const args);
	int    hw_check_threeinone();
	int    read_db_content();
	int    maxstunamelen();
	int    maxhwfilelen();
	void   print_hw_check_result(int choice, const int filestatus_num[], const int total_filestatus_num[]);
};
