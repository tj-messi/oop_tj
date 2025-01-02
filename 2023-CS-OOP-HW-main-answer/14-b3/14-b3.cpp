/*2150792 �ƿ� ţ»��*/
#include<iostream>
#include<iomanip>
#include<cmath>
#include<string>
#include<cstring>
using namespace std;

int usage(const char* const procname)
{
	cout << "Usage: " << procname << " Ҫ����ѧ��/all ƥ��ѧ��/all Դ������/all ���ƶȷ�ֵ(60-100) ���(filename/screen)" << endl << endl;
	cout << "e.g. : " << procname << " 2159999 2159998 all       80 screen" << endl;
	cout << "       " << procname << " 2159999 all     14-b1.cpp 75 result.txt" << endl;
	cout << "       " << procname << " all     all     14-b2.cpp 80 check.dat" << endl;
	cout << "       " << procname << " all     all     all       85 screen" << endl;

	return 0;
}

int str_to_int(const char* const str, int start, int end) //���±�[start end)���ַ���ת��Ϊint
{
	int temp = 0;
	int real_end = int(strlen(str)) < end ? int(strlen(str)) : end; //ȡstrlen(str)��end�н�С���Ǹ� 
	if (start == real_end)
		return -1;
	for (int i = start; i < real_end; i++)
	{
		temp *= 10;
		if (str[i] >= '0' && str[i] <= '9') //�����ּ���
			temp += (str[i] - '0');
		else
			return -1;
	}
	return temp;
}

int check_stu_id(const char* const stu_id)
{
	if (strlen(stu_id) != 7)
	{
		cout << "Ҫ����ѧ�Ų���7λ" << endl;
		return 0;
	}
	for (int i = 0; i < 7; i++)
	{
		if (stu_id[i] < '0' || stu_id[i] > '9')
		{
			cout << "Ҫ����ѧ�Ų���7λ����" << endl;
			return 0;
		}
	}
	return 1;
}

int main(int argc, char* argv[])
{
	/*======��Ҫ��ǰ�����ļ��======*/
	// �����������Ƿ�С��6
	if (argc < 6)                                         
	{
		usage(argv[0]);
		return 0;
	}
	// �����ѧ����ѧ��
	bool flag_all = false;
	if (strcmp(argv[1], "all") == 0)		 			  
		flag_all = true;
	else
	{
		if (check_stu_id(argv[1]) == 0)      
			return 0;//���ѧ��λ��������
	}
	// ���ƥ��ѧ����ѧ��
	if (!flag_all && strcmp(argv[1], argv[2]) == 0)       // ���˾�Ϊall�⣬����ƥ��ѧ�Ų�����ͬ
	{
		cout << "ƥ��ѧ����Ҫ���ѧ����ͬ" << endl;
		return 0;
	}
	if (strcmp(argv[2], "all") != 0)                    
	{
		if (check_stu_id(argv[2]) == 0)
			return 0;//���ѧ��λ��������
	}
	if (flag_all == true && strcmp(argv[2], "all"))       // ���ѧ����all��ƥ��ѧ�Ų���all
	{
		cout << "���ѧ����all��ƥ��ѧ�ű�����all" << endl;
		return 0;
	}
	// ����������ļ����ĳ����Ƿ񳬹�32�ֽ�
	if (strlen(argv[3]) > 32)                             
	{
		cout << "Դ�����ļ���������32�ֽ�" << endl;
		return 0;
	}
	// ����������ļ����ĳ����Ƿ񳬹�32�ֽ�
	if (strlen(argv[5]) > 32)                             
	{
		cout << "�������ļ���������32�ֽ�" << endl;
		return 0;
	}

	cout << "�������ͨ��" << endl;
	cout << "���ѧ�ţ�" << argv[1] << endl;
	cout << "ƥ��ѧ�ţ�" << argv[2] << endl;

	/*======Դ�ļ����======*/
	if (strcmp(argv[3], "all") == 0)
		cout << "Դ�ļ�����" << "all" << endl;
	else
		cout << "Դ�ļ�����" << argv[3] << endl;

	/*======���ƶȼ��======*/
	char* similarity_set = argv[4];
	if (similarity_set[0] >= '6' && similarity_set[0] <= '9')
	{
		if (similarity_set[1] >= '0' && similarity_set[1] <= '9')
			cout << "ƥ����ֵ��" << str_to_int(similarity_set, 0, 2) << endl;//�ж�60-99�����
	}
	else if (similarity_set[0] == '1' && similarity_set[1] == '0' && similarity_set[2] == '0')
		cout << "ƥ����ֵ��" << str_to_int(similarity_set, 0, 3) << endl;//�ж�100�����
	else
		cout << "ƥ����ֵ��" << 80 << endl;

	/*======�����ʽ���======*/
	char* outfile = argv[5];
	if (strcmp(outfile, "screen") == 0)
		cout << "���Ŀ�꣺" << "screen" << endl;
	else
		cout << "���Ŀ�꣺" << outfile << endl;

	return 0;
}
