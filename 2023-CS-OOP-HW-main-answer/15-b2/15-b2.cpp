/* 2150792 牛禄阳 计科*/
/* 1850772 张哲源 2151187 袁之典 2152202 戚峻榕 2152988 杨恺铭 2153731 胡语诺 2154146 吴金轩 2154270 赵楚钧 2251206 冯羽芯 2252210 韩慕非 */
#include <fstream>
#include <iomanip>
#include <cmath>
#include <iostream>
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
	cerr << "    a.hex                     : 不带路径形式" << endl;
	cerr << "    ..\\data\\b.txt             : 相对路径形式" << endl;
	cerr << "    C:\\Windows\\System32\\c.hex : 绝对相对路径形式" << endl;
	cerr << "请输入要转换的hex格式文件名 : ";

	ifstream in;
	ofstream out;
	char input_file[300];
	char out_file[300];
	fgets(input_file, 299, stdin);
	input_file[tj_strlen(input_file) - 1] = '\0';
	cerr << "请输入转换后的文件名        : ";
	fgets(out_file, 299, stdin);
	out_file[tj_strlen(out_file) - 1] = '\0';
	in.open((const char*)(input_file), ios::in | ios::binary);
	out.open((const char*)(out_file), ios::out | ios::binary);
	if (in.is_open() == 0)
	{
		in.close();
		out.close();
		cout << "输入文件" << input_file << "打开失败" << endl;
		return -1;
	}
	unsigned char wenjian_all[100];
	int file_sta = 0;
	int i = 0;
	int line = 0, col = 0;
	int flag = 0;
	while (!in.eof())
	{
		char ch;
		if (i % 78 == 0 && i != 0)
		{
			ch = in.get();
			if (in.good() == 0)
			{
				i = i - 2;
				flag = 1;
			}
			else
			{
				ch = in.get();
				if (in.good() == 0)
				{
					--i;
					flag = 1;
				}

			}
		}
		ch = in.get();
		++i;
	}
	--i;

	//每行填满是78个数字
	if (i % 78 == 0)
		;
	else if (flag == 0)
		i = i - 2;

	line = i / 78;

	if (i % 78 == 0)
		col = 0;
	else
		col = i % 78 - 62;

	in.clear();
	in.seekg(0, ios::beg);//指针回到初始位置

	for (int t = 0; t < line; t++)
	{
		char ch;
		file_sta = 0;
		int j = 0;
		for (int k = 0; k < 78; k++)
			wenjian_all[k] = in.get();
		ch = in.get();
		ch = in.get();
		while ((wenjian_all[j] != ':') && (wenjian_all[j] != '\r'))
			j++;
		for (int k = j - 1; k >= 0; k--)
		{
			if (wenjian_all[k] >= '0' && wenjian_all[k] <= '9')
				file_sta += (wenjian_all[k] - '0') * int(pow(16, j - k - 1));
			else if (wenjian_all[k] >= 'A' && wenjian_all[k] <= 'F')
				file_sta += (wenjian_all[k] - 'A' + 10) * int(pow(16, j - k - 1));
		}
		if (file_sta != 16 * t)
		{
			cout << "最左侧的偏移量0x" << hex << setw(8) << setfill('0') << setiosflags(ios::uppercase) << file_sta
				<< "不是期望值0x" << hex << setw(8) << setfill('0') << setiosflags(ios::uppercase) << (t * 16) << endl;
			return 0;
		}

		for (int k = 0; k < 8; k++)
		{
			int tmp = 0;
			if (wenjian_all[3 * k + 11] >= '0' && wenjian_all[3 * k + 11] <= '9')
				tmp += (wenjian_all[3 * k + 11] - '0') * int(pow(16, 1));
			else if (wenjian_all[3 * k + 11] >= 'A' && wenjian_all[3 * k + 11] <= 'F')
				tmp += (wenjian_all[3 * k + 11] - 'A' + 10) * int(pow(16, 1));

			if (wenjian_all[3 * k + 11 + 1] >= '0' && wenjian_all[3 * k + 11 + 1] <= '9')
				tmp += (wenjian_all[3 * k + 11 + 1] - '0') * int(pow(16, 0));
			else if (wenjian_all[3 * k + 11 + 1] >= 'A' && wenjian_all[3 * k + 11 + 1] <= 'F')
				tmp += (wenjian_all[3 * k + 11 + 1] - 'A' + 10) * int(pow(16, 0));

			out << char(tmp);
		}

		for (int k = 0; k < 8; k++)
		{
			int tmp = 0;
			if (wenjian_all[3 * k + 37] >= '0' && wenjian_all[3 * k + 37] <= '9')
				tmp += (wenjian_all[3 * k + 37] - '0') * int(pow(16, 1));
			else if (wenjian_all[3 * k + 37] >= 'A' && wenjian_all[3 * k + 37] <= 'F')
				tmp += (wenjian_all[3 * k + 37] - 'A' + 10) * int(pow(16, 1));

			if (wenjian_all[3 * k + 37 + 1] >= '0' && wenjian_all[3 * k + 37 + 1] <= '9')
				tmp += (wenjian_all[3 * k + 37 + 1] - '0') * int(pow(16, 0));
			else if (wenjian_all[3 * k + 37 + 1] >= 'A' && wenjian_all[3 * k + 37 + 1] <= 'F')
				tmp += (wenjian_all[3 * k + 37 + 1] - 'A' + 10) * int(pow(16, 0));

			out << char(tmp);
		}
	}

	if (col != 0)
	{
		char ch;
		int j = 0;
		file_sta = 0;
		for (int k = 0; k < col + 62; k++)
			wenjian_all[k] = in.get();
		ch = in.get();
		ch = in.get();
		while ((wenjian_all[j] != ':') && (wenjian_all[j] != '\r'))
			j++;
		for (int k = j - 1; k >= 0; k--)
		{
			if (wenjian_all[k] >= '0' && wenjian_all[k] <= '9')
				file_sta += (wenjian_all[k] - '0') * int(pow(16, j - k - 1));
			else if (wenjian_all[k] >= 'A' && wenjian_all[k] <= 'F')
				file_sta += (wenjian_all[k] - 'A' + 10) * int(pow(16, j - k - 1));
		}

		if (file_sta != 16 * line)
		{
			cout << "最左侧的偏移量0x" << hex << setw(8) << setfill('0') << file_sta
				<< "不是期望值0x" << hex << setw(8) << setfill('0') << (line * 16) << endl;
			return 0;
		}

		if (col <= 8)
		{
			for (int k = 0; k < col; k++)
			{
				int tmp = 0;
				if (wenjian_all[3 * k + 11] >= '0' && wenjian_all[3 * k + 11] <= '9')
					tmp += (wenjian_all[3 * k + 11] - '0') * int(pow(16, 1));
				else if (wenjian_all[3 * k + 11] >= 'A' && wenjian_all[3 * k + 11] <= 'F')
					tmp += (wenjian_all[3 * k + 11] - 'A' + 10) * int(pow(16, 1));

				if (wenjian_all[3 * k + 11 + 1] >= '0' && wenjian_all[3 * k + 11 + 1] <= '9')
					tmp += (wenjian_all[3 * k + 11 + 1] - '0') * int(pow(16, 0));
				else if (wenjian_all[3 * k + 11 + 1] >= 'A' && wenjian_all[3 * k + 11 + 1] <= 'F')
					tmp += (wenjian_all[3 * k + 11 + 1] - 'A' + 10) * int(pow(16, 0));

				out << char(tmp);
			}

		}
		if (col > 8)
		{
			for (int k = 0; k < 8; k++)
			{
				int tmp = 0;
				if (wenjian_all[3 * k + 11] >= '0' && wenjian_all[3 * k + 11] <= '9')
					tmp += (wenjian_all[3 * k + 11] - '0') * int(pow(16, 1));
				else if (wenjian_all[3 * k + 11] >= 'A' && wenjian_all[3 * k + 11] <= 'F')
					tmp += (wenjian_all[3 * k + 11] - 'A' + 10) * int(pow(16, 1));

				if (wenjian_all[3 * k + 11 + 1] >= '0' && wenjian_all[3 * k + 11 + 1] <= '9')
					tmp += (wenjian_all[3 * k + 11 + 1] - '0') * int(pow(16, 0));
				else if (wenjian_all[3 * k + 11 + 1] >= 'A' && wenjian_all[3 * k + 11 + 1] <= 'F')
					tmp += (wenjian_all[3 * k + 11 + 1] - 'A' + 10) * int(pow(16, 0));

				out << char(tmp);
			}

			for (int k = 0; k < col - 8; k++)
			{
				int tmp = 0;
				if (wenjian_all[3 * k + 37] >= '0' && wenjian_all[3 * k + 37] <= '9')
					tmp += (wenjian_all[3 * k + 37] - '0') * int(pow(16, 1));
				else if (wenjian_all[3 * k + 37] >= 'A' && wenjian_all[3 * k + 37] <= 'F')
					tmp += (wenjian_all[3 * k + 37] - 'A' + 10) * int(pow(16, 1));

				if (wenjian_all[3 * k + 37 + 1] >= '0' && wenjian_all[3 * k + 37 + 1] <= '9')
					tmp += (wenjian_all[3 * k + 37 + 1] - '0') * int(pow(16, 0));
				else if (wenjian_all[3 * k + 37 + 1] >= 'A' && wenjian_all[3 * k + 37 + 1] <= 'F')
					tmp += (wenjian_all[3 * k + 37 + 1] - 'A' + 10) * int(pow(16, 0));

				out << char(tmp);
			}
		}
	}

	in.close();
	out.close();
	return 0;
}
