/* 2150792 �ƿ� ţ»�� */
#define _CRT_SECURE_NO_WARNINGS
#include "hw_check.h"
#include "../include/class_aat.h"
#include "../include_mariadb_x86/mysql/mysql.h"
/* �����ļ���·�����ļ������жϲ���ӡ�ļ���״̬ */
FILE_STATUS getaprint_firfilestatus(const string& filepath, const string& filename, const Student& student)
{
	ifstream fin;
	string _filepath = filepath;
	replace(_filepath.begin(), _filepath.end(), '\\', '/'); // �滻
	fin.open(_filepath, ios::in | ios::binary | ios::ate); //ate��ʽ�򿪣��ж��Ƿ�С�����ֽ�
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
	if (isUTF8(fin)) // һ����sourcefile,����Ҫ�ж��Ƿ����GB����
	{
		cout << FILESTATUS_STR[NOTGB] << endl;
		fin.close();
		return NOTGB;
	}
	fin.clear();
	fin.seekg(0, ios::beg);
	/* ѭ������ֱ���ҵ�ĳ�в��� */
	vector<char> line_content, firstlinecontent;
	char ch;
	while (!fin.eof())
	{   
		/* ��ȡ���е����ݣ�ȥ�����е�ǰ��ո�/tab��ʣ��Ϊ��Ч���� */
		while ((ch = fin.get()) != '\r' && ch != '\n' && (!fin.eof()))// �����ȡ�ַ���ֱ�����л�eof
			line_content.push_back(ch);
		if (ch == '\r')
			ch = fin.get();  // �������'\r'��˵����Windows����Ҫ�ٶ�һ��
		/* ȥ������ǰ��ո��Tab */
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
			cout << FILESTATUS_STR[NOFIRSTLINE] << endl; // ����Ч����
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
		cout << "���в��Ƿ���Ҫ���/* */��ʽ [" << str << "]" << endl;
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
	/* ��Ӧע���е�ѧ����Ϣ */
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
		cout << "����";
		if(!have_no)
			cout << "ѧ�Ų�ƥ�� ";
		if(!have_name)
			cout << "������ƥ�� ";
		if(!have_major)
			cout << "�༶��ƥ�� ";
		cout << " [" << str << "]" << endl;
		return FIRSTERR;
	}
}
