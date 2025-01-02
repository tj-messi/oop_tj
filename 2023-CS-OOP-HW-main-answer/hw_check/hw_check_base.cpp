/* 2150792 �ƿ� ţ»�� */
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <string>
#include <cstring>
#include <sstream>
#include "hw_check.h"
#include "../include/class_aat.h"
#include "../include_mariadb_x86/mysql/mysql.h"

/* �����ļ���·�����ļ������ж��ļ���״̬ */
FILE_STATUS get_basefilestatus(const string& filepath, const string& filename)
{
	ifstream fin;
	string _filepath = filepath;
	replace(_filepath.begin(), _filepath.end(), '\\', '/'); // �滻
	fin.open(_filepath, ios::in | ios::binary);
	if (!fin.is_open())
		return NOTSUBMIT;

	int file_kind = get_file_kind(filename);
	if (file_kind == SOURCEFILE)
	{
		if (isUTF8(fin))
		{
			fin.close();
			return NOTGB;
		}
	}
	if (file_kind == PDFFILE)
	{
		if (!is_PDF_file(fin))
		{
			fin.close();
			return ERRPDF;
		}
	}
	fin.close();
	return PASS;
}

/* �����ļ���״̬������� */
void print_basefilestatus(FILE_STATUS filestatus)
{
	cout << FILESTATUS_STR[filestatus] << endl;
}
