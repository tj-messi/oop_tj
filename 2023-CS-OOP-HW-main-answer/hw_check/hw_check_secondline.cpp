/* 2150792 计科 牛禄阳 */
#define _CRT_SECURE_NO_WARNINGS
#include "hw_check.h"
#include "../include/class_aat.h"
#include "../include_mariadb_x86/mysql/mysql.h"

/* 根据文件的路径的文件名称判断并打印文件的状态 */
FILE_STATUS getaprint_secfilestatus(const string& filepath, vector<Student>& check_stulist, const string& own_no)
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

	string line;
	size_t line_count = 0;
	while (getline(fin, line)) 
	{
		line_count++;
		if (line_count > 1) 
			break; // 如果发现多于一行，立即结束循环
	}
	if (line_count <= 1)
	{
		fin.close();
		cout << FILESTATUS_STR[SECLINEERR] << endl; // 次行其它错误
		return SECLINEERR;
	}
	fin.clear();
	fin.seekg(0, ios::beg);
	/* 循环读，直到找到两行不空 */
	vector<char> line_content, firstlinecontent, secondlinecontent;
	char ch;
	line_count = 0;
	while (!fin.eof())
	{
		line_content.clear();
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
		if (!line_content.empty()) // 如果不空读到一行
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
			cout << FILESTATUS_STR[LESS2LINE] << endl; // 文件小于两行
			fin.close();
			return LESS2LINE;
		}
	}
	fin.close();
	/* 对次行进行检测 */
	if (secondlinecontent.size() < 2)
	{
		cout << FILESTATUS_STR[SECLINENOTCOM] << endl;
		return SECLINENOTCOM;
	}
	vector<char> comcontent;
	int comstatus = is_validcomment(secondlinecontent, comcontent);
	if (comstatus == (int)FIRSTNOTCOM || comstatus == (int)FIRSTCOMERR)
	{
		cout << FILESTATUS_STR[SECLINENOTCOM] << endl; // 次行不是注释
		return SECLINENOTCOM;
	}
	vector<string> comitem = splitBySpace(comcontent);
	/* 得到互验学生名单 */
	for (size_t i = 0; i < comitem.size(); i = i + 2)
	{
		if (i >= comitem.size() - 1) // 仅在结尾处出现此错误
		{
			cout << "第[" << i / 2 << "]个学生后面的信息不全(只读到一项)，后续内容忽略" <<endl; 
			return OTHERERR;
		}
		string stu_no = comitem[i], stu_name = comitem[i + 1];
		if (stu_no.length() != 7)
		{
			cout << "第" << i / 2 + 1 << "位同学的学号[" << stu_no << "]不是7位，后续内容忽略" << endl;
			return OTHERERR;
		}
		if (!is_stuno_valid(stu_no))
		{
			cout << "第" << i / 2 + 1 << "位同学的学号[" << stu_no << "]中有非数字存在，后续内容忽略" << endl;
			return OTHERERR;
		}
		if (stu_no == own_no)
		{
			cout << "第[" << i / 2 + 1 << "]项写了自己，后续内容忽略" << endl;
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
	cout << "交叉检查结果：" << endl;
	for (size_t i = 0; i < total_stulist.size(); i++) // i是当前检测的学生
	{
		cout << setw(3) << i + 1 << ": " << total_stulist[i].no << " " << total_stulist[i].name << endl;
		for (size_t j = 0; j < total_check_stulist[i].size(); j++) // j是和你互验的学生
		{
			cout << '\t' << total_check_stulist[i][j].no << " " << total_check_stulist[i][j].name << '\t';
			size_t k = 0;
			for (; k < total_stulist.size(); k++) // k是互验学生在total_stulist中的序号
			{
				if (total_stulist[k].no == total_check_stulist[i][j].no)
					break;
			}
			if (k == total_stulist.size())
			{
				cout << "对方学号不存在" << endl;
			}
			else
			{
				if (total_stulist[k].name != total_check_stulist[i][j].name)
				{
					cout << "对方姓名不正确" << endl;
					continue;
				}
				size_t m = 0;
				for (; m < total_check_stulist[k].size(); m++) // 遍历对方的check_list，看有没有你
				{
					if (total_check_stulist[k][m].no == total_stulist[i].no) // 学号对
					{
						if (total_check_stulist[k][m].name != total_stulist[i].name) // 姓名错
							cout << "没写对你名字" << endl;
						else
							cout << endl; // 姓名对，下一行
						break;
					}
				}
				if (m == total_check_stulist[k].size())
					cout << "抛弃了你" << endl;
			}
		}
	}
}
