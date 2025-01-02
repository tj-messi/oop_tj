/* 2150792 计科 牛禄阳*/
#include <iostream>
#include <fstream>
#include<iomanip>
#include <string.h>
using namespace std;

int tj_strlen(const char* str)
{
	/* 注意：函数内不允许定义任何形式的数组（包括静态数组） */
	if (str == NULL)
		return 0;
	char* p = (char*)str;
	int length = 0;
	while (*p != '\0')
	{
		++length;
		++p;
	}
	return length;
}

int main(int argc, char* argv[])
{
	cerr << "文件名以下形式均可以:" << endl;
	cerr << "    a.txt                     : 不带路径形式" << endl;
	cerr << "    ..\\data\\b.dat             : 相对路径形式" << endl;
	cerr << "    C:\\Windows\\System32\\c.dat : 绝对相对路径形式" << endl;
	cerr << "请输入文件名 : ";
	ifstream in;
	char file_title[300];
	fgets(file_title, 299, stdin);
	file_title[tj_strlen(file_title) - 1] = '\0';
	in.open((const char*)file_title, ios::in | ios::binary);
	if (in.is_open() == 0)
	{
		in.close();
		cout << "输入文件" << file_title << "打开失败!" << endl;
		return -1;
	}

	unsigned char ch[20];
	int i = 0;
	int line = 0, col = 0;
	while (!in.eof())
	{
		char tmp = in.get();
		++i;
	}
	--i;//多读入了EOF

	in.clear();
	line = i / 16;
	col = i % 16;
	in.seekg(0, ios::beg);//指针回到初始位置

	for (int k = 0; k < line; k++)
	{
		cout << hex << setw(8) << setfill('0') << setiosflags(ios::uppercase) << 16 * k << ":  ";
		for (int t = 0; t < 16; t++)
			ch[t] = in.get();
		for (int t = 0; t < 16; t++)
		{
			if (t == 8)
				cout << "- ";
			cout << hex << setw(2) << setfill('0') << setiosflags(ios::uppercase) << int(ch[t]) << " ";
		}
		cout << " ";
		for (int t = 0; t < 16; t++)
		{
			if (ch[t] >= 33 && ch[t] <= 126)
				cout << ch[t];
			else
				cout << ".";
		}
		cout << endl;
	}

	if (col != 0)
	{
		cout << hex << setfill('0') << setw(8) << 16 * line << ":  ";
		for (int t = 0; t < col; t++)
			ch[t] = in.get();
		for (int t = 0; t < col; t++)
		{
			if (t == 8)
				cout << "- ";
			cout << hex << setw(2) << setfill('0') << setiosflags(ios::uppercase) << int(ch[t]) << " ";
		}
		if (col <= 8)
			cout << setw(51 - 3 * col) << setfill(' ') << " ";
		else
			cout << setw(51 - 3 * col - 2) << setfill(' ') << " ";
		for (int t = 0; t < col; t++)
		{
			if (ch[t] >= 33 && ch[t] <= 126)
				cout << ch[t];
			else
				cout << ".";
		}
		cout << endl;
	}

	in.close();
	return 0;
}
