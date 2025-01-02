/* 2150792 �ƿ� ţ»�� */
#include <fstream>
#include <iomanip>
#include <cmath>
#include <iostream>
#include <string.h>
using namespace std;

int usage(const char* const procname)
{
	cout << "Usage : " << procname << " --check �ļ��� | --convert { wtol|ltow } Դ�ļ��� Ŀ���ļ���" << endl;
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
		return 0; // �޷���
	}
	while (!in.eof())
	{
		now = in.get(); // bug��������unsigned char ȥ��EOF
		if (in.eof())
			break;
		if (first == true)
		{
			pre = now;
			first = false;
			continue;
		}
		if (pre == '\x0D' && now == '\x0A')    // ���ֹ� OD OA
			Linux_file = false;
		if (pre != '\x0D' && now == '\x0A')    // ���ֹ� 0A ǰû�� OD
			Windows_file = false;
		pre = now;
	}
	in.close();
	if (Linux_file == true && Windows_file == false)
		return 1; // Linux�ļ�
	else if (Linux_file == false && Windows_file == true)
		return 2; // Windows�ļ�
	else
		return 3; // �޷�ʶ��
}

int convert_file(const char* file_name1, const char* file_name2, const char* convert_cmd)
{
	ifstream in;
	ofstream out;
	in.open(file_name1, ios::in | ios::binary);
	if (!in.is_open())
		return 0; //�ļ��޷���
	int option = strcmp(convert_cmd, "wtol") == 0 ? 1 : 2; // wtolΪ1��ltowΪ2
	if (option == 1 && check_file(file_name1) != 2) // Windows�޷�ʶ��
	{
		in.close();
		return 1; // �ļ���ʽ�޷�ʶ��
	}
	if (option == 2 && check_file(file_name1) != 1) //Linux�޷�ʶ��
	{
		in.close();
		return 1; // �ļ���ʽ�޷�ʶ��
	}

	out.open(file_name2, ios::out | ios::binary);
	if (!out.is_open())
	{
		in.close();
		return 0; //�ļ��޷���
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
			if (now == '\x0A') //����\x0Aǰ���\x0D
			{
				out.put('\x0D');
				++cnt;
			}
		}
		pre = now;
		out.put(now);
	}
	
	if (option == 1)
		cout << "ת����ɣ�ȥ��" << cnt << "��0x0D" << endl;
	else if (option == 2)
		cout << "ת����ɣ�����" << cnt << "��0x0D" << endl;

	in.close();
	out.close();
	return 2;
}

int main(int argc, char** argv)
{
	/* ����main���������ж� */
	if (!(argc == 3 || argc == 5)) // ���������Ȳ���3���ֲ���5��
	{
		usage(argv[0]);
		return 0;
	}
	if (argc == 3 && strcmp(argv[1], "--check"))   // ������3����������"--check"
	{
		usage(argv[0]);
		return 0;
	}
	if (argc == 5 && (strcmp(argv[1], "--convert")
		|| (strcmp(argv[2], "wtol") && strcmp(argv[2], "ltow")))) // ������5��������"--convert",����"wtol"��"ltow"
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
			cout << "�ļ���ʧ��" << endl;
		else if (temp == 1)
			cout << "Linux��ʽ" << endl;
		else if (temp == 2)
			cout << "Windows��ʽ" << endl;
		else
			cout << "�ļ���ʽ�޷�ʶ��" << endl;
	}
	if (argc == 5)
	{
		int temp = convert_file(file_name1, file_name2, convert_cmd);
		if (temp == 0)
			cout << "�ļ���ʧ��" << endl;
		else if (temp == 1)
			cout << "�ļ���ʽ�޷�ʶ��" << endl;
	}

	return 0;
}
