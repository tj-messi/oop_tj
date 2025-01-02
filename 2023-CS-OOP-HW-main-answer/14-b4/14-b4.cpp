/*2150792 �ƿ� ţ»��*/
#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>
#include <cstring>
using namespace std;

struct ping_para {
	const char* name;			   
	const char* description;       
	const int number;              
	const int def_value;           
	const int low;                
	const int top;                 
	int value;                     
};
const int ping_para_num = 3;
const char* const infor_print[4] = { "����","���Ӳ���","��Χ","Ĭ��ֵ" };
int int_bit_num(int a)
{
	int cnt = 1;
	while (a / 10)
	{
		cnt++;
		a = a / 10;
	}
	return cnt;
}

static int str_to_int(const char* const str, int start, int end, bool& flag) //���±�[start end)���ַ���ת��Ϊint
{
	int temp = 0;
	int minus_flag = 1;
	int real_end = int(strlen(str)) < end ? int(strlen(str)) : end; //ȡstrlen(str)��end�н�С���Ǹ� 
	if (start == real_end)
	{
		flag = false;
		return INT_MIN;
	}
	for (int i = start; i < real_end; i++)
	{
		if (i == start && str[i] == '-')
		{
			minus_flag = -1;
			continue;
		}
		temp *= 10;
		if (str[i] >= '0' && str[i] <= '9') //�����ּ���
			temp += (str[i] - '0');
		else
		{
			flag = false;
			return INT_MIN;
		}
	}
	return minus_flag * temp;
}

static int check_IP(const char* ip_str)
{
	string temp_str = ip_str;
	int end_index[5] = { -1,0,0,0,int(strlen(ip_str)) };		  // �������Ԫ��-1���ı�
	int j = 1;
	//����ip��ַ���ҵ�'.'���ڵ��±�
	for (int i = 0; i < int(strlen(ip_str)); i++)
	{
		if (ip_str[i] == '.')
		{
			if (j >= 4)                      // '.'�ĸ�������4����
				return 0;
			else
				end_index[j++] = i;
		}
	}
	if (j < 4)								// '.'�ĸ���С��3Ҳ����
		return 0;
	for (int i = 0; i < 4; i++)
	{
		int temp = 0;
		bool flag = true;
		temp = str_to_int(ip_str, end_index[i] + 1, end_index[i + 1], flag);
		string check_zero = temp_str.substr(end_index[i] + 1, end_index[i + 1] - end_index[i] - 1); // ��ȡ��Ӧ��str�Ӵ�
		if ((check_zero != to_string(temp) || temp < 0 || temp>255))			// �ֱ����ĸ�'.'֮����ĸ����֣���������ǰ��0
			return 0;
	}
	return 1;
}

int usage(const char* const procname, const ping_para para_menu[])
{
	cout << "Usage: " << procname << " ";
	for (int i = 0; i < ping_para_num; i++)
	{
		cout << "[" << para_menu[i].name;
		if (para_menu[i].description != NULL)
			cout << " " << para_menu[i].description;
		cout << "] ";
	}
	cout << "IP��ַ" << endl;
	/* ������Ĳ����������Ӧ�ô�ӡ�ĳ��� */
	int max_length[4] = { 5,9,12,6 };
	int temp_length[4] = { 0 };
	for (int j = 0; j < ping_para_num; j++)
	{
		temp_length[0] = max(int(strlen(para_menu[j].name)), temp_length[0]);
		temp_length[1] = max(int_bit_num(para_menu[j].number), temp_length[1]);
		temp_length[2] = max(int_bit_num(para_menu[j].low) + int_bit_num(para_menu[j].top) + 4, temp_length[2]);
		temp_length[3] = max(int_bit_num(para_menu[j].def_value), temp_length[3]);
	}
	for (int i = 0; i < 4; i++)
		max_length[i] = max(max_length[i], temp_length[i] + 1);
	/*��ӡ"       =================================="*/
	cout << "       =";
	for (int i = 0; i < 4; i++)
		cout << setiosflags(ios::left) << setw(max_length[i]) << setfill('=') << '=';
	cout << "=" << endl;
	/*��ӡ"        ���� ���Ӳ��� ��Χ        Ĭ��ֵ"*/
	cout << "        ";
	for (int i = 0; i < 4; i++)
		cout << setiosflags(ios::left) << setw(max_length[i]) << setfill(' ') << infor_print[i];
	cout << endl;
	/*��ӡ"       =================================="*/
	cout << "       =";
	for (int i = 0; i < 4; i++)
		cout << setiosflags(ios::left) << setw(max_length[i]) << setfill('=') << '=';
	cout << "=" << endl;
	for (int i = 0; i < ping_para_num; i++)
	{
		int tem_len = max_length[2] - 3 - int_bit_num(para_menu[i].low) - int_bit_num(para_menu[i].top);
		cout << setw(8) << setfill(' ') << " ";
		cout << setiosflags(ios::left) << setw(max_length[0]) << setfill(' ') << para_menu[i].name;
		cout << setiosflags(ios::left) << setw(max_length[1]) << setfill(' ') << para_menu[i].number;
		cout << "[" << para_menu[i].low << ".." << para_menu[i].top << setw(tem_len) << setfill(' ') << "]";
		cout << para_menu[i].def_value << endl;
	}
	/*��ӡ"       =================================="*/
	cout << "       =";
	for (int i = 0; i < 4; i++)
		cout << setiosflags(ios::left) << setw(max_length[i]) << setfill('=') << '=';
	cout << "=" << endl;
	return 0;
}

int main(int argc, char* argv[])
{
	ping_para para_menu[ping_para_num] = {
  // name descrip number def low top value
		{"-l","��С",1,64,32,64000,64},
		{"-n","����",1,4,1,1024,4},
		{"-t",NULL,0,0,0,1,0}
	};
	/*======��Ҫ��ǰ�����ļ��======*/
    // �����������Ƿ�С��2
	if (argc < 2)
	{
		usage(argv[0], para_menu);
		return 0;
	}
	if (check_IP(argv[argc - 1]) == 0)
	{
		cout << "IP��ַ����" << endl;
		return 0;
	}
	for (int i = 1; i < argc - 1; i++)
	{
		int para_id = 0, para_value = 0;
		/*======�������Ƿ���'-'��ͷ======*/
		if (argv[i][0] != '-')
		{
			cout << "����" << argv[i] << "������-��ͷ�ĺϷ�����" << endl;
			return 0;
		}
		/*======�������Ƿ����======*/
		int j = 0;
		for (j = 0; j < ping_para_num; j++)
		{
			if (strcmp(argv[i], para_menu[j].name) == 0)
			{
				para_id = j;//���ڶ�λ��ǰ������para_menu�е�λ��
				break;
			}
		}
		if (j == ping_para_num)
		{
			cout << "����" << argv[i] << "������" << endl;
			return 0;
		}
		/*======�������ĺ�������(-l��Ĳ���ֻҪ����-��ͷ����Ϊ��Ч����)======*/
		if (para_menu[para_id].number==0)            // ��ǰ�����ĸ��Ӳ�������Ϊ0������Ҫ�ٴ��ж�
		{
			para_menu[para_id].value = 1;            // �в���Ϊ1���޲���Ϊ0����Ȼ���Ǹ���"-t"���е�����
			continue;
		}
		if (argv[i + 1][0] == '-' || (i + 1 == argc - 1))
		{
			cout << "����" << argv[i] << "û�к�������" << endl;
			return 0;
		}
		bool checkend=false;
		para_value = str_to_int(argv[i + 1], 0, strlen(argv[i + 1]),checkend);
		if (para_value<para_menu[para_id].low || para_value>para_menu[para_id].top)
			para_menu[para_id].value = para_menu[para_id].def_value;
		else
			para_menu[para_id].value = para_value;
		++i; //��һλ�����Ѿ����жϣ���������
	}
	/*======������======*/
	cout << "�������ͨ��" << endl;
	for (int i = 0; i < ping_para_num; i++)
		cout << para_menu[i].name << " ������" << para_menu[i].value << endl;
	cout << "IP��ַ��" << argv[argc - 1] << endl;

	return 0;
}
