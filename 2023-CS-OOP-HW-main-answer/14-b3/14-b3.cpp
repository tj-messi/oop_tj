/*2150792 计科 牛禄阳*/
#include<iostream>
#include<iomanip>
#include<cmath>
#include<string>
#include<cstring>
using namespace std;

int usage(const char* const procname)
{
	cout << "Usage: " << procname << " 要检查的学号/all 匹配学号/all 源程序名/all 相似度阀值(60-100) 输出(filename/screen)" << endl << endl;
	cout << "e.g. : " << procname << " 2159999 2159998 all       80 screen" << endl;
	cout << "       " << procname << " 2159999 all     14-b1.cpp 75 result.txt" << endl;
	cout << "       " << procname << " all     all     14-b2.cpp 80 check.dat" << endl;
	cout << "       " << procname << " all     all     all       85 screen" << endl;

	return 0;
}

int str_to_int(const char* const str, int start, int end) //将下标[start end)的字符串转化为int
{
	int temp = 0;
	int real_end = int(strlen(str)) < end ? int(strlen(str)) : end; //取strlen(str)和end中较小的那个 
	if (start == real_end)
		return -1;
	for (int i = start; i < real_end; i++)
	{
		temp *= 10;
		if (str[i] >= '0' && str[i] <= '9') //是数字继续
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
		cout << "要检查的学号不是7位" << endl;
		return 0;
	}
	for (int i = 0; i < 7; i++)
	{
		if (stu_id[i] < '0' || stu_id[i] > '9')
		{
			cout << "要检查的学号不是7位数字" << endl;
			return 0;
		}
	}
	return 1;
}

int main(int argc, char* argv[])
{
	/*======需要提前结束的检查======*/
	// 检测参数个数是否小于6
	if (argc < 6)                                         
	{
		usage(argv[0]);
		return 0;
	}
	// 检测检查学生的学号
	bool flag_all = false;
	if (strcmp(argv[1], "all") == 0)		 			  
		flag_all = true;
	else
	{
		if (check_stu_id(argv[1]) == 0)      
			return 0;//检测学号位数和数字
	}
	// 检测匹配学生的学号
	if (!flag_all && strcmp(argv[1], argv[2]) == 0)       // 除了均为all外，检查和匹配学号不能相同
	{
		cout << "匹配学号与要检查学号相同" << endl;
		return 0;
	}
	if (strcmp(argv[2], "all") != 0)                    
	{
		if (check_stu_id(argv[2]) == 0)
			return 0;//检测学号位数和数字
	}
	if (flag_all == true && strcmp(argv[2], "all"))       // 检查学号是all，匹配学号不是all
	{
		cout << "检查学号是all，匹配学号必须是all" << endl;
		return 0;
	}
	// 检测输出结果文件名的长度是否超过32字节
	if (strlen(argv[3]) > 32)                             
	{
		cout << "源程序文件名超过了32字节" << endl;
		return 0;
	}
	// 检测输出结果文件名的长度是否超过32字节
	if (strlen(argv[5]) > 32)                             
	{
		cout << "输出结果文件名超过了32字节" << endl;
		return 0;
	}

	cout << "参数检查通过" << endl;
	cout << "检查学号：" << argv[1] << endl;
	cout << "匹配学号：" << argv[2] << endl;

	/*======源文件检查======*/
	if (strcmp(argv[3], "all") == 0)
		cout << "源文件名：" << "all" << endl;
	else
		cout << "源文件名：" << argv[3] << endl;

	/*======相似度检查======*/
	char* similarity_set = argv[4];
	if (similarity_set[0] >= '6' && similarity_set[0] <= '9')
	{
		if (similarity_set[1] >= '0' && similarity_set[1] <= '9')
			cout << "匹配阈值：" << str_to_int(similarity_set, 0, 2) << endl;//判断60-99的情况
	}
	else if (similarity_set[0] == '1' && similarity_set[1] == '0' && similarity_set[2] == '0')
		cout << "匹配阈值：" << str_to_int(similarity_set, 0, 3) << endl;//判断100的情况
	else
		cout << "匹配阈值：" << 80 << endl;

	/*======输出方式检查======*/
	char* outfile = argv[5];
	if (strcmp(outfile, "screen") == 0)
		cout << "输出目标：" << "screen" << endl;
	else
		cout << "输出目标：" << outfile << endl;

	return 0;
}
