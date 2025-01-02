/* 2150792 �ƿ� ţ»��*/
#include <iostream>
#include <fstream>
#include<iomanip>
#include <string.h>
using namespace std;

int tj_strlen(const char* str)
{
	/* ע�⣺�����ڲ��������κ���ʽ�����飨������̬���飩 */
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
	cerr << "�ļ���������ʽ������:" << endl;
	cerr << "    a.txt                     : ����·����ʽ" << endl;
	cerr << "    ..\\data\\b.dat             : ���·����ʽ" << endl;
	cerr << "    C:\\Windows\\System32\\c.dat : �������·����ʽ" << endl;
	cerr << "�������ļ��� : ";
	ifstream in;
	char file_title[300];
	fgets(file_title, 299, stdin);
	file_title[tj_strlen(file_title) - 1] = '\0';
	in.open((const char*)file_title, ios::in | ios::binary);
	if (in.is_open() == 0)
	{
		in.close();
		cout << "�����ļ�" << file_title << "��ʧ��!" << endl;
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
	--i;//�������EOF

	in.clear();
	line = i / 16;
	col = i % 16;
	in.seekg(0, ios::beg);//ָ��ص���ʼλ��

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
