/*2351114 大数据 朱俊泽*/
#pragma once
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <iomanip>
#include <string.h>
#include "../include/class_aat.h"
#include "../include/class_cft.h"
#include "../include_mariadb_x86/mysql/mysql.h"

enum Check {

    FILE_NOT_FOUND,//没交
    NOT_PDF,//不是pdf文件
    CORRECT,//正确
    INVALID_ENCODING,//非GB编码
    NOT_VS,//非vs识别

    FIRSTLINE_NOT_3_ITEMS,//不是三项
    FIRSTLINE_ERROR,//首行检查错误
    FIRSTLINE_NOT_DEFINE, //首行不是注释行
    FIRSTLINE_MULTIERROR,//多行注释错误

    STU_NO_ERROR,//某一位的学号开始错误
    WRITE_SELF,//从某一位开始写了自己
    SECONDLINE_NOT_DEFINE,//次行不是注释
    NOT_DOUBLE,//后面的信息不全(只读到一项)
};


//base
Check checkPDF(const std::string& path);
bool fileExists(const std::string& path);
bool isUTF8(const std::string& file_path);
Check checkfilebase(const std::string& path);
bool checkvs(const std::string& filePath);

//firstline
Check checkfilefirst(const string& firstline, const MYSQL_ROW& row, const string& stuNo, const string& stuName);
bool isMatch(const string& part, const string& target);

//secondline
Check checkfilesecond(const string& secondline , const string& own_stu_no);

//次行真正有效的名字
struct valid_stu
{
    string no;//学号
    string name;//名字
};

struct student
{
    string no;//学号
    string name;//名字
    string cno;//课号
    string secondline;//该学生该文件的第二行内容
    vector<valid_stu> valid_stu;//有效行
};


struct Cross
{
    string filename;//交叉文件名字
    vector<student> stu_list;//学生列表
    string source_root;
};

void Crosscheck(Cross cross);