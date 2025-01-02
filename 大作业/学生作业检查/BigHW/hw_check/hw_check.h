/*2351114 ������ �쿡��*/
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

    FILE_NOT_FOUND,//û��
    NOT_PDF,//����pdf�ļ�
    CORRECT,//��ȷ
    INVALID_ENCODING,//��GB����
    NOT_VS,//��vsʶ��

    FIRSTLINE_NOT_3_ITEMS,//��������
    FIRSTLINE_ERROR,//���м�����
    FIRSTLINE_NOT_DEFINE, //���в���ע����
    FIRSTLINE_MULTIERROR,//����ע�ʹ���

    STU_NO_ERROR,//ĳһλ��ѧ�ſ�ʼ����
    WRITE_SELF,//��ĳһλ��ʼд���Լ�
    SECONDLINE_NOT_DEFINE,//���в���ע��
    NOT_DOUBLE,//�������Ϣ��ȫ(ֻ����һ��)
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

//����������Ч������
struct valid_stu
{
    string no;//ѧ��
    string name;//����
};

struct student
{
    string no;//ѧ��
    string name;//����
    string cno;//�κ�
    string secondline;//��ѧ�����ļ��ĵڶ�������
    vector<valid_stu> valid_stu;//��Ч��
};


struct Cross
{
    string filename;//�����ļ�����
    vector<student> stu_list;//ѧ���б�
    string source_root;
};

void Crosscheck(Cross cross);