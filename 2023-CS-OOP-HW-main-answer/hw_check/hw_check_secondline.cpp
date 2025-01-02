/* 2150792 �ƿ� ţ»�� */
#define _CRT_SECURE_NO_WARNINGS
#include "hw_check.h"
#include "../include/class_aat.h"
#include "../include_mariadb_x86/mysql/mysql.h"

/* �����ļ���·�����ļ������жϲ���ӡ�ļ���״̬ */
FILE_STATUS getaprint_secfilestatus(const string& filepath, vector<Student>& check_stulist, const string& own_no)
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

	string line;
	size_t line_count = 0;
	while (getline(fin, line)) 
	{
		line_count++;
		if (line_count > 1) 
			break; // ������ֶ���һ�У���������ѭ��
	}
	if (line_count <= 1)
	{
		fin.close();
		cout << FILESTATUS_STR[SECLINEERR] << endl; // ������������
		return SECLINEERR;
	}
	fin.clear();
	fin.seekg(0, ios::beg);
	/* ѭ������ֱ���ҵ����в��� */
	vector<char> line_content, firstlinecontent, secondlinecontent;
	char ch;
	line_count = 0;
	while (!fin.eof())
	{
		line_content.clear();
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
		if (!line_content.empty()) // ������ն���һ��
		{
			++line_count;
			if (line_count == 1)
				firstlinecontent = line_content;
			else if (line_count == 2)
			{
				secondlinecontent = line_content;
				break;
			}
		}
		if (fin.eof())
		{
			cout << FILESTATUS_STR[LESS2LINE] << endl; // �ļ�С������
			fin.close();
			return LESS2LINE;
		}
	}
	fin.close();
	/* �Դ��н��м�� */
	if (secondlinecontent.size() < 2)
	{
		cout << FILESTATUS_STR[SECLINENOTCOM] << endl;
		return SECLINENOTCOM;
	}
	vector<char> comcontent;
	int comstatus = is_validcomment(secondlinecontent, comcontent);
	if (comstatus == (int)FIRSTNOTCOM || comstatus == (int)FIRSTCOMERR)
	{
		cout << FILESTATUS_STR[SECLINENOTCOM] << endl; // ���в���ע��
		return SECLINENOTCOM;
	}
	vector<string> comitem = splitBySpace(comcontent);
	/* �õ�����ѧ������ */
	for (size_t i = 0; i < comitem.size(); i = i + 2)
	{
		if (i >= comitem.size() - 1) // ���ڽ�β�����ִ˴���
		{
			cout << "��[" << i / 2 << "]��ѧ���������Ϣ��ȫ(ֻ����һ��)���������ݺ���" <<endl; 
			return OTHERERR;
		}
		string stu_no = comitem[i], stu_name = comitem[i + 1];
		if (stu_no.length() != 7)
		{
			cout << "��" << i / 2 + 1 << "λͬѧ��ѧ��[" << stu_no << "]����7λ���������ݺ���" << endl;
			return OTHERERR;
		}
		if (!is_stuno_valid(stu_no))
		{
			cout << "��" << i / 2 + 1 << "λͬѧ��ѧ��[" << stu_no << "]���з����ִ��ڣ��������ݺ���" << endl;
			return OTHERERR;
		}
		if (stu_no == own_no)
		{
			cout << "��[" << i / 2 + 1 << "]��д���Լ����������ݺ���" << endl;
			return OTHERERR;
		}

		Student temp_check_stu;
		temp_check_stu.no = stu_no, temp_check_stu.name = stu_name;
		check_stulist.push_back(temp_check_stu);
	}
	cout << FILESTATUS_STR[PASS] << endl;
	return PASS;
}

void Stucrossheck(const vector<vector<Student>>& total_check_stulist, const vector<Student>& total_stulist)
{
	cout << "����������" << endl;
	for (size_t i = 0; i < total_stulist.size(); i++) // i�ǵ�ǰ����ѧ��
	{
		cout << setw(3) << i + 1 << ": " << total_stulist[i].no << " " << total_stulist[i].name << endl;
		for (size_t j = 0; j < total_check_stulist[i].size(); j++) // j�Ǻ��㻥���ѧ��
		{
			cout << '\t' << total_check_stulist[i][j].no << " " << total_check_stulist[i][j].name << '\t';
			size_t k = 0;
			for (; k < total_stulist.size(); k++) // k�ǻ���ѧ����total_stulist�е����
			{
				if (total_stulist[k].no == total_check_stulist[i][j].no)
					break;
			}
			if (k == total_stulist.size())
			{
				cout << "�Է�ѧ�Ų�����" << endl;
			}
			else
			{
				if (total_stulist[k].name != total_check_stulist[i][j].name)
				{
					cout << "�Է���������ȷ" << endl;
					continue;
				}
				size_t m = 0;
				for (; m < total_check_stulist[k].size(); m++) // �����Է���check_list������û����
				{
					if (total_check_stulist[k][m].no == total_stulist[i].no) // ѧ�Ŷ�
					{
						if (total_check_stulist[k][m].name != total_stulist[i].name) // ������
							cout << "ûд��������" << endl;
						else
							cout << endl; // �����ԣ���һ��
						break;
					}
				}
				if (m == total_check_stulist[k].size())
					cout << "��������" << endl;
			}
		}
	}
}
