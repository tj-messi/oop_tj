/* 2150792 计科 牛禄阳 */
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

/* 根据文件的路径的文件名称判断文件的状态 */
FILE_STATUS get_basefilestatus(const string& filepath, const string& filename)
{
	ifstream fin;
	string _filepath = filepath;
	replace(_filepath.begin(), _filepath.end(), '\\', '/'); // 替换
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

/* 根据文件的状态进行输出 */
void print_basefilestatus(FILE_STATUS filestatus)
{
	cout << FILESTATUS_STR[filestatus] << endl;
}
