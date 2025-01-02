/* 2150792 ţ»�� �ƿ� */
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <sstream>
#include <tchar.h>
#include <string>
#include "../include/class_aat.h"
#include "../include/cmd_console_tools.h"
#include "bmp_subtitles.h"
using namespace std;

static void intercept_txt_compare(char* procname, const char* const argv0)
{
	int i = strlen(argv0) - 1;
	string des_name = "";
	while (i >= 0) // �������ȶ���Ҳ����ֹ
	{
		if (argv0[i] == '\\' || argv0[i] == '/') // �����ָ��ֹͣ
			break;
		else
		{
			des_name += argv0[i];
			--i;
		}
	}
	reverse(des_name.begin(), des_name.end()); // �Ӻ���ǰ����������Ҫ��ת
	des_name.copy(procname, des_name.length());
	procname[des_name.length()] = '\0';
}

static void usage(const char* const argv0)
{
	char procname[256];
	intercept_txt_compare(procname, argv0); // �޸�Ϊ�Լ��Ľ�ȡ����

	cout << endl;
	cout << "Usage: " << procname << " --bmpfile xxx.bmp --outfile xxx.bmp [ --traditional | --subtitles ���� | --posx 0..1919 | --posy 0..1079 | --color FF0000 | --style horizontal/vertical ]" << endl;
	cout << endl;
	cout << "��ѡ�" << endl;
	cout << "    --bmpfile xxx.bmp    ��ԭʼ bmp ͼƬ�ļ�������ѡ��" << endl;
	cout << "    --outfile xxx.bmp    ������Ļ��� bmp ͼƬ�ļ�������ѡ��" << endl;
	cout << endl;
	cout << "��ѡ�" << endl;
	cout << "    --traditional        ��bool ֵ���������ʾ�����ַ�(traditional_Chinese)��ȱʡΪ����" << endl;
	cout << "    --subtitles ����     ��Ҫ�������Ļ���֣������� 10 �����֣������� GB2312 �еĺ��֣���ȱʡ�������" << endl;
	cout << "    --posx 0..1919       ��Ҫ����ĵ�һ�����ֵ����Ͻ� x ���꣬ȱʡΪ0" << endl;
	cout << "    --posy 0..1079       ��Ҫ����ĵ�һ�����ֵ����Ͻ� y ���꣬ȱʡΪ0" << endl;
	cout << "    --color FF0000       ������ǰ��ɫ��6 �� 16 �����ַ����ֱ�Ϊ RGB������FF0000-ȫ�죩��ȱʡΪȫ��" << endl;
	cout << "    --style horizontal/vertical  ����ʾ��񣬽�����/���������ѡ��ȱʡΪ����" << endl;
	cout << endl;
}

int main(int argc, char** argv)
{
	/* ����/���� */
	const string StyleType[] = { "horizontal",	"vertical", "" };
	args_analyse_tools args[] = {
	args_analyse_tools("--bmpfile",     ST_EXTARGS_TYPE::str, 1, string("")), // ԭʼ bmp ͼƬ
	args_analyse_tools("--outfile",     ST_EXTARGS_TYPE::str, 1, string("")), // �����Ļ��� bmp ͼƬ
	args_analyse_tools("--traditional", ST_EXTARGS_TYPE::boolean, 0, false),            // true ��ʾ�����ַ����������
	args_analyse_tools("--subtitles",	ST_EXTARGS_TYPE::str, 1, string("�������")),   // Ҫ�������Ļ���֣������� 10 �����֣������� GB2312 �еĺ��֣�,Ĭ��Ϊ"�������"
	args_analyse_tools("--posx",		ST_EXTARGS_TYPE::int_with_default, 1, 0, 0, 1919),// ��һ�����ֵ����Ͻ� x ���꣬Ĭ��ֵΪ0
	args_analyse_tools("--posy",		ST_EXTARGS_TYPE::int_with_default, 1, 0, 0, 1079),// ��һ�����ֵ����Ͻ� y ���꣬Ĭ��ֵΪ0
	args_analyse_tools("--color",		ST_EXTARGS_TYPE::str, 1, string("FF0000")),       // ����ǰ��ɫ��6 ��16 �����ַ����ֱ�ΪRGB��Ĭ��Ϊȫ��
	args_analyse_tools("--style",	    ST_EXTARGS_TYPE::str_with_set_default, 1, 0, StyleType),//��ʾ��񣬽�����/���������ѡ��Ĭ��Ϊ����
	args_analyse_tools()  //���һ�������ڽ���
	};

	int cur_argc, ret = 0;
	//���һ������1����ʾ��ѡ������⣬������������
	if ((cur_argc = args_analyse_process(argc, argv, args, 0)) < 0) {
		//������Ϣ�ں������Ѵ�ӡ
		args_analyse_print(args);
		usage(argv[0]);
		return -1;
	}
	/* ����ָ������[bmpfile]��[outfile] */
	if (args[OPT_ARGS_BMPFILE].existed() + args[OPT_ARGS_OUTFILE].existed() != 2) {
		usage(argv[0]);
		cout << "����ָ������[" << args[OPT_ARGS_BMPFILE].get_name() << "��" << args[OPT_ARGS_OUTFILE].get_name() << "]" << endl;
		return -1;
	}

	// �Ȱ�infile�е�����ȫ��д��outfile�У�Ȼ������outfile�����޸���λͼ���ݺ󣬽��޸ĵ�λͼ����д��ָ��λ��
	/* bmpfile */
	string bmpfile = args[OPT_ARGS_BMPFILE].get_string();
	/* outfile */
	string outfile = args[OPT_ARGS_OUTFILE].get_string();
	if (copyFile(bmpfile, outfile) == false)  // ��infile�����ݸ��Ƶ�outfile��
		return -1;
	bitmap_image outbmpfile(outfile.c_str()); // �����ʱoutfile�е�bmp��Ϣ
	/* subtitles */
	string subtitles = args[OPT_ARGS_SUBTITLES].get_string();
	if (subtitles.length() > 20)
		cerr << "����ĺ��ָ�������10����Ĭ��ȡǰʮ" << endl;
	int numsubtitles = min((int)subtitles.length(), 20);
	/* posx,posy */
	int posx = args[OPT_ARGS_POSX].get_int();
	int posy = args[OPT_ARGS_POSY].get_int();
	if (args[OPT_ARGS_STYLE].get_string() == "horizontal" && ((posy + CHDOT_HEIGHT > outbmpfile.height()) || (posx + numsubtitles / 2 * CHDOT_WIDTH > outbmpfile.width()))) // Ҫ��ʾ��λ�ó���ͼƬ��Χ������ʾ��Ļ����������ʾ
	{
		numsubtitles = 0;
		cerr << "��Ҫ��ʾ����Ļ����ͼƬ��Χ��������ʾ" << endl;
	}
	if (args[OPT_ARGS_STYLE].get_string() == "vertical" && ((posx + CHDOT_WIDTH > outbmpfile.width()) || (posy + numsubtitles / 2 * CHDOT_HEIGHT > outbmpfile.height())))
	{
		numsubtitles = 0;
		cerr << "��Ҫ��ʾ����Ļ����ͼƬ��Χ��������ʾ" << endl;
	}
	/* color */
	unsigned char rgb[3] = { 0 };
	string rgbhex = args[OPT_ARGS_COLOR].get_string();
	if (outbmpfile.get_biBitCount() <= 8) // С��24λ����Ϊȫ0��Ҳ���Ǻ�ɫ
	{
		rgbhex.clear();
		rgbhex = "000000"; 
	}
	if (isValidRGBColor(rgbhex, rgb) == false) // ����Ϸ������Ѿ�ʵ��ת��
	{
		cerr << "�������ɫ���Ϸ���Ĭ����Ϊȫ��" << endl;
		rgb[0] = 255; 
		rgb[1] = 0;
		rgb[2] = 0;   // ������Ϸ�����Ĭ��ֵ��Ϊȫ��ɫ
	}

	/* traditional */
	ifstream Chdotfile;
	if(args[OPT_ARGS_TRADITIONAL].existed())
		Chdotfile.open("HZK16F", ios::in | ios::binary);
	else
		Chdotfile.open("HZK16",  ios::in | ios::binary);
	if (!Chdotfile.is_open())
	{
		cout << "�޷���GB2312���ֵ����ֿ��ļ�" << endl;
		return -1;
	}
	/* style */
	if (args[OPT_ARGS_STYLE].get_string() == "horizontal")
	{
		unsigned char Ch_encoding[2] = { 0 };
		for (int i = 0; i < numsubtitles; i = i + 2)
		{
			Ch_encoding[1] = subtitles[i], Ch_encoding[0] = subtitles[i + 1];
			outbmpfile.add_Ch_subtitles(Chdotfile, Ch_encoding, posx + i / 2 * CHDOT_WIDTH, posy, rgb);
		}
	}
	else
	{
		unsigned char Ch_encoding[2] = { 0 };
		for (int i = 0; i < numsubtitles; i = i + 2)
		{
			Ch_encoding[1] = subtitles[i], Ch_encoding[0] = subtitles[i + 1];
			outbmpfile.add_Ch_subtitles(Chdotfile, Ch_encoding, posx, posy + i / 2 * CHDOT_HEIGHT, rgb);
		}
	}
	/* ��bmpdata�ı仯д��outbmpfile */
	outbmpfile.update_bmpfile(outfile.c_str());

	Chdotfile.close();
	return 0;
}
