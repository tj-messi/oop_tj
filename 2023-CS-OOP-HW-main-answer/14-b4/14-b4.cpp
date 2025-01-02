/*2150792 计科 牛禄阳*/
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
const char* const infor_print[4] = { "参数","附加参数","范围","默认值" };
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

static int str_to_int(const char* const str, int start, int end, bool& flag) //将下标[start end)的字符串转化为int
{
	int temp = 0;
	int minus_flag = 1;
	int real_end = int(strlen(str)) < end ? int(strlen(str)) : end; //取strlen(str)和end中较小的那个 
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
		if (str[i] >= '0' && str[i] <= '9') //是数字继续
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
	int end_index[5] = { -1,0,0,0,int(strlen(ip_str)) };		  // 数组的首元素-1不改变
	int j = 1;
	//遍历ip地址，找到'.'所在的下标
	for (int i = 0; i < int(strlen(ip_str)); i++)
	{
		if (ip_str[i] == '.')
		{
			if (j >= 4)                      // '.'的个数大于4错误
				return 0;
			else
				end_index[j++] = i;
		}
	}
	if (j < 4)								// '.'的个数小于3也错误
		return 0;
	for (int i = 0; i < 4; i++)
	{
		int temp = 0;
		bool flag = true;
		temp = str_to_int(ip_str, end_index[i] + 1, end_index[i + 1], flag);
		string check_zero = temp_str.substr(end_index[i] + 1, end_index[i + 1] - end_index[i] - 1); // 截取相应的str子串
		if ((check_zero != to_string(temp) || temp < 0 || temp>255))			// 分别检测四个'.'之间的四个数字，不允许有前导0
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
	cout << "IP地址" << endl;
	/* 按输入的参数长度求出应该打印的长度 */
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
	/*打印"       =================================="*/
	cout << "       =";
	for (int i = 0; i < 4; i++)
		cout << setiosflags(ios::left) << setw(max_length[i]) << setfill('=') << '=';
	cout << "=" << endl;
	/*打印"        参数 附加参数 范围        默认值"*/
	cout << "        ";
	for (int i = 0; i < 4; i++)
		cout << setiosflags(ios::left) << setw(max_length[i]) << setfill(' ') << infor_print[i];
	cout << endl;
	/*打印"       =================================="*/
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
	/*打印"       =================================="*/
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
		{"-l","大小",1,64,32,64000,64},
		{"-n","数量",1,4,1,1024,4},
		{"-t",NULL,0,0,0,1,0}
	};
	/*======需要提前结束的检查======*/
    // 检测参数个数是否小于2
	if (argc < 2)
	{
		usage(argv[0], para_menu);
		return 0;
	}
	if (check_IP(argv[argc - 1]) == 0)
	{
		cout << "IP地址错误" << endl;
		return 0;
	}
	for (int i = 1; i < argc - 1; i++)
	{
		int para_id = 0, para_value = 0;
		/*======检测参数是否以'-'开头======*/
		if (argv[i][0] != '-')
		{
			cout << "参数" << argv[i] << "不是以-开头的合法参数" << endl;
			return 0;
		}
		/*======检测参数是否存在======*/
		int j = 0;
		for (j = 0; j < ping_para_num; j++)
		{
			if (strcmp(argv[i], para_menu[j].name) == 0)
			{
				para_id = j;//用于定位当前参数在para_menu中的位置
				break;
			}
		}
		if (j == ping_para_num)
		{
			cout << "参数" << argv[i] << "不存在" << endl;
			return 0;
		}
		/*======检测参数的后续参数(-l后的参数只要不是-开头均视为有效参数)======*/
		if (para_menu[para_id].number==0)            // 当前参数的附加参数个数为0，则不需要再次判断
		{
			para_menu[para_id].value = 1;            // 有参数为1，无参数为0，当然这是根据"-t"进行的特判
			continue;
		}
		if (argv[i + 1][0] == '-' || (i + 1 == argc - 1))
		{
			cout << "参数" << argv[i] << "没有后续参数" << endl;
			return 0;
		}
		bool checkend=false;
		para_value = str_to_int(argv[i + 1], 0, strlen(argv[i + 1]),checkend);
		if (para_value<para_menu[para_id].low || para_value>para_menu[para_id].top)
			para_menu[para_id].value = para_menu[para_id].def_value;
		else
			para_menu[para_id].value = para_value;
		++i; //下一位参数已经被判断，现在跳过
	}
	/*======输出结果======*/
	cout << "参数检查通过" << endl;
	for (int i = 0; i < ping_para_num; i++)
		cout << para_menu[i].name << " 参数：" << para_menu[i].value << endl;
	cout << "IP地址：" << argv[argc - 1] << endl;

	return 0;
}
