/* 2150792 计科 牛禄阳 */
#include <fstream>
#include <iomanip>
#include <cmath>
#include <iostream>
#include <string.h>
using namespace std;

int usage(const char* const procname)
{
	cout << "Usage : " << procname << " --check 文件名 | --convert { wtol|ltow } 源文件名 目标文件名" << endl;
	cout << "        " << procname << " --check a.txt" << endl;
	cout << "        " << procname << " --convert wtol a.win.txt a.linux.txt" << endl;
	cout << "        " << procname << " --convert ltow a.linux.txt a.win.txt" << endl;
	return 0;
}

int check_file(const char* file_name)
{
	unsigned char pre, now;
	bool first = true, Linux_file = true, Windows_file = true;
	ifstream in;
	in.open(file_name, ios::in | ios::binary);
	if (!in.is_open())
	{
		in.close();
		return 0; // 无法打开
	}
	while (!in.eof())
	{
		now = in.get(); // bug：不能用unsigned char 去读EOF
		if (in.eof())
			break;
		if (first == true)
		{
			pre = now;
			first = false;
			continue;
		}
		if (pre == '\x0D' && now == '\x0A')    // 出现过 OD OA
			Linux_file = false;
		if (pre != '\x0D' && now == '\x0A')    // 出现过 0A 前没有 OD
			Windows_file = false;
		pre = now;
	}
	in.close();
	if (Linux_file == true && Windows_file == false)
		return 1; // Linux文件
	else if (Linux_file == false && Windows_file == true)
		return 2; // Windows文件
	else
		return 3; // 无法识别
}

int convert_file(const char* file_name1, const char* file_name2, const char* convert_cmd)
{
	ifstream in;
	ofstream out;
	in.open(file_name1, ios::in | ios::binary);
	if (!in.is_open())
		return 0; //文件无法打开
	int option = strcmp(convert_cmd, "wtol") == 0 ? 1 : 2; // wtol为1，ltow为2
	if (option == 1 && check_file(file_name1) != 2) // Windows无法识别
	{
		in.close();
		return 1; // 文件格式无法识别
	}
	if (option == 2 && check_file(file_name1) != 1) //Linux无法识别
	{
		in.close();
		return 1; // 文件格式无法识别
	}

	out.open(file_name2, ios::out | ios::binary);
	if (!out.is_open())
	{
		in.close();
		return 0; //文件无法打开
	}
	unsigned char pre, now;
	bool first = true;
	int cnt = 0;
	while (!in.eof())
	{
		now = in.get();
		if (in.eof())
			break;
		if (first == true)
		{
			pre = now;
			out.put(now);
			first = false;
			continue;
		}
		if (option == 1)      // Windows
		{
			if (pre == '\x0D' && now == '\x0A')
			{
				out.seekp(-1, ios::cur);
				++cnt;
			}
		}
		else if (option == 2) // Linux
		{
			if (now == '\x0A') //所有\x0A前添加\x0D
			{
				out.put('\x0D');
				++cnt;
			}
		}
		pre = now;
		out.put(now);
	}
	
	if (option == 1)
		cout << "转换完成，去除" << cnt << "个0x0D" << endl;
	else if (option == 2)
		cout << "转换完成，加入" << cnt << "个0x0D" << endl;

	in.close();
	out.close();
	return 2;
}

int main(int argc, char** argv)
{
	/* 进行main函数参数判断 */
	if (!(argc == 3 || argc == 5)) // 参数个数既不是3个又不是5个
	{
		usage(argv[0]);
		return 0;
	}
	if (argc == 3 && strcmp(argv[1], "--check"))   // 参数是3个，但不是"--check"
	{
		usage(argv[0]);
		return 0;
	}
	if (argc == 5 && (strcmp(argv[1], "--convert")
		|| (strcmp(argv[2], "wtol") && strcmp(argv[2], "ltow")))) // 参数是5个，不是"--convert",不是"wtol"或"ltow"
	{
		usage(argv[0]);
		return 0;
	}
	char* file_name1 = NULL, * file_name2 = NULL, * convert_cmd = NULL;
	if (argc == 3)
		file_name1 = argv[2];
	else if (argc == 5)
	{
		convert_cmd = argv[2];
		file_name1 = argv[3];
		file_name2 = argv[4];
	}
	if (argc == 3)
	{
		int temp = check_file(file_name1);
		if (temp == 0)
			cout << "文件打开失败" << endl;
		else if (temp == 1)
			cout << "Linux格式" << endl;
		else if (temp == 2)
			cout << "Windows格式" << endl;
		else
			cout << "文件格式无法识别" << endl;
	}
	if (argc == 5)
	{
		int temp = convert_file(file_name1, file_name2, convert_cmd);
		if (temp == 0)
			cout << "文件打开失败" << endl;
		else if (temp == 1)
			cout << "文件格式无法识别" << endl;
	}

	return 0;
}
