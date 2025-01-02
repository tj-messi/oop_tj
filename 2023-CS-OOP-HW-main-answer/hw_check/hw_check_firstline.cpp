/* 2150792 计科 牛禄阳 */
#define _CRT_SECURE_NO_WARNINGS
#include "hw_check.h"
#include "../include/class_aat.h"
#include "../include_mariadb_x86/mysql/mysql.h"
/* 根据文件的路径的文件名称判断并打印文件的状态 */
FILE_STATUS getaprint_firfilestatus(const string& filepath, const string& filename, const Student& student)
{
	ifstream fin;
	string _filepath = filepath;
	replace(_filepath.begin(), _filepath.end(), '\\', '/'); // 替换
	fin.open(_filepath, ios::in | ios::binary | ios::ate); //ate方式打开，判断是否小于三字节
	if (!fin.is_open())
	{
		cout << FILESTATUS_STR[NOTSUBMIT] << endl;
		return NOTSUBMIT;
	}
	streamsize filesize = fin.tellg();
	if (filesize < 3)
	{
		cout << FILESTATUS_STR[LESS3BIT] << endl;
		fin.close();
		return LESS3BIT;
	}
	fin.close();

	fin.open(_filepath, ios::in | ios::binary);
	if (isUTF8(fin)) // 一定是sourcefile,但需要判断是否符合GB编码
	{
		cout << FILESTATUS_STR[NOTGB] << endl;
		fin.close();
		return NOTGB;
	}
	fin.clear();
	fin.seekg(0, ios::beg);
	/* 循环读，直到找到某行不空 */
	vector<char> line_content, firstlinecontent;
	char ch;
	while (!fin.eof())
	{   
		/* 读取此行的数据，去除此行的前后空格/tab，剩下为有效内容 */
		while ((ch = fin.get()) != '\r' && ch != '\n' && (!fin.eof()))// 逐个读取字符，直到换行或eof
			line_content.push_back(ch);
		if (ch == '\r')
			ch = fin.get();  // 如果读到'\r'，说明是Windows，需要再读一次
		/* 去除此行前后空格和Tab */
		if (!line_content.empty())
		{
			trim_left(line_content);
			trim_right(line_content);
		}
		if (!line_content.empty())
		{
			firstlinecontent = line_content;
			break;
		}
		if (fin.eof())
		{
			cout << FILESTATUS_STR[NOFIRSTLINE] << endl; // 无有效首行
			fin.close();
			return NOFIRSTLINE;
		}
	}
	fin.close();
	string str(firstlinecontent.begin(), firstlinecontent.end());
	if (firstlinecontent.size() < 2)
	{
		cout << FILESTATUS_STR[FIRSTNOTCOM];
		cout << " [" << str << "]" << endl;
		return FIRSTNOTCOM;
	}
	vector<char> comcontent;
	int comstatus = is_validcomment(firstlinecontent, comcontent);
	if (comstatus == (int)FIRSTNOTCOM)
	{
		cout << FILESTATUS_STR[FIRSTNOTCOM];
		cout << " [" << str << "]" << endl;
		return FIRSTNOTCOM;
	}
	else if (comstatus == (int)FIRSTCOMERR)
	{
		cout << "首行不是符合要求的/* */格式 [" << str << "]" << endl;
		return FIRSTCOMERR;
	}
	int have_no = 0, have_major = 0, have_name = 0;
	vector<string> comitem = splitBySpace(comcontent);
	if (comitem.size() != 3)
	{
		cout << FILESTATUS_STR[FIRSTNOT3];
		cout << " [" << str << "]" << endl;
		return FIRSTNOT3;
	}
	/* 对应注释中的学生信息 */
	auto it = find(comitem.begin(), comitem.end(), student.no);
	if (it != comitem.end())
		have_no = 1;
	it = find(comitem.begin(), comitem.end(), student.majorshortname);
	if (it != comitem.end())
		have_major = 1;
	it = find(comitem.begin(), comitem.end(), student.majorfullname);
	if (it != comitem.end())
		have_major = 1;
	it = find(comitem.begin(), comitem.end(), student.name);
	if (it != comitem.end())
		have_name = 1;
	if ((have_no + have_major + have_name) == 3)
	{
		cout << FILESTATUS_STR[PASS] << endl;
		return PASS;
	}
	else
	{
		cout << "首行";
		if(!have_no)
			cout << "学号不匹配 ";
		if(!have_name)
			cout << "姓名不匹配 ";
		if(!have_major)
			cout << "班级不匹配 ";
		cout << " [" << str << "]" << endl;
		return FIRSTERR;
	}
}
