/* 2150792 牛禄阳 计科 */
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
	while (i >= 0) // 参数长度读完也会终止
	{
		if (argv0[i] == '\\' || argv0[i] == '/') // 读到分割符停止
			break;
		else
		{
			des_name += argv0[i];
			--i;
		}
	}
	reverse(des_name.begin(), des_name.end()); // 从后向前读，所以需要反转
	des_name.copy(procname, des_name.length());
	procname[des_name.length()] = '\0';
}

static void usage(const char* const argv0)
{
	char procname[256];
	intercept_txt_compare(procname, argv0); // 修改为自己的截取函数

	cout << endl;
	cout << "Usage: " << procname << " --bmpfile xxx.bmp --outfile xxx.bmp [ --traditional | --subtitles 汉字 | --posx 0..1919 | --posy 0..1079 | --color FF0000 | --style horizontal/vertical ]" << endl;
	cout << endl;
	cout << "必选项：" << endl;
	cout << "    --bmpfile xxx.bmp    ：原始 bmp 图片文件名（必选）" << endl;
	cout << "    --outfile xxx.bmp    ：加字幕后的 bmp 图片文件名（必选）" << endl;
	cout << endl;
	cout << "可选项：" << endl;
	cout << "    --traditional        ：bool 值，存在则表示繁体字符(traditional_Chinese)，缺省为简体" << endl;
	cout << "    --subtitles 汉字     ：要加入的字幕文字（不超过 10 个汉字，仅考虑 GB2312 有的汉字），缺省面向对象" << endl;
	cout << "    --posx 0..1919       ：要加入的第一个汉字的左上角 x 坐标，缺省为0" << endl;
	cout << "    --posy 0..1079       ：要加入的第一个汉字的左上角 y 坐标，缺省为0" << endl;
	cout << "    --color FF0000       ：汉字前景色，6 个 16 进制字符，分别为 RGB（例：FF0000-全红），缺省为全黑" << endl;
	cout << "    --style horizontal/vertical  ：显示风格，仅横向/纵向两项可选，缺省为横向" << endl;
	cout << endl;
}

int main(int argc, char** argv)
{
	/* 横向/纵向 */
	const string StyleType[] = { "horizontal",	"vertical", "" };
	args_analyse_tools args[] = {
	args_analyse_tools("--bmpfile",     ST_EXTARGS_TYPE::str, 1, string("")), // 原始 bmp 图片
	args_analyse_tools("--outfile",     ST_EXTARGS_TYPE::str, 1, string("")), // 添加字幕后的 bmp 图片
	args_analyse_tools("--traditional", ST_EXTARGS_TYPE::boolean, 0, false),            // true 表示繁体字符，无则简体
	args_analyse_tools("--subtitles",	ST_EXTARGS_TYPE::str, 1, string("面向对象")),   // 要加入的字幕汉字（不超过 10 个汉字，仅考虑 GB2312 中的汉字）,默认为"面向对象"
	args_analyse_tools("--posx",		ST_EXTARGS_TYPE::int_with_default, 1, 0, 0, 1919),// 第一个汉字的左上角 x 坐标，默认值为0
	args_analyse_tools("--posy",		ST_EXTARGS_TYPE::int_with_default, 1, 0, 0, 1079),// 第一个汉字的左上角 y 坐标，默认值为0
	args_analyse_tools("--color",		ST_EXTARGS_TYPE::str, 1, string("FF0000")),       // 汉字前景色，6 个16 进制字符，分别为RGB，默认为全红
	args_analyse_tools("--style",	    ST_EXTARGS_TYPE::str_with_set_default, 1, 0, StyleType),//显示风格，仅横向/纵向两项可选，默认为横向
	args_analyse_tools()  //最后一个，用于结束
	};

	int cur_argc, ret = 0;
	//最后一个参数1，表示除选项参数外，还有其它参数
	if ((cur_argc = args_analyse_process(argc, argv, args, 0)) < 0) {
		//错误信息在函数中已打印
		args_analyse_print(args);
		usage(argv[0]);
		return -1;
	}
	/* 必须指定参数[bmpfile]和[outfile] */
	if (args[OPT_ARGS_BMPFILE].existed() + args[OPT_ARGS_OUTFILE].existed() != 2) {
		usage(argv[0]);
		cout << "必须指定参数[" << args[OPT_ARGS_BMPFILE].get_name() << "和" << args[OPT_ARGS_OUTFILE].get_name() << "]" << endl;
		return -1;
	}

	// 先把infile中的内容全部写到outfile中，然后声明outfile对象，修改其位图数据后，将修改的位图数据写回指定位置
	/* bmpfile */
	string bmpfile = args[OPT_ARGS_BMPFILE].get_string();
	/* outfile */
	string outfile = args[OPT_ARGS_OUTFILE].get_string();
	if (copyFile(bmpfile, outfile) == false)  // 将infile的数据复制到outfile中
		return -1;
	bitmap_image outbmpfile(outfile.c_str()); // 读入此时outfile中的bmp信息
	/* subtitles */
	string subtitles = args[OPT_ARGS_SUBTITLES].get_string();
	if (subtitles.length() > 20)
		cerr << "输入的汉字个数大于10个，默认取前十" << endl;
	int numsubtitles = min((int)subtitles.length(), 20);
	/* posx,posy */
	int posx = args[OPT_ARGS_POSX].get_int();
	int posy = args[OPT_ARGS_POSY].get_int();
	if (args[OPT_ARGS_STYLE].get_string() == "horizontal" && ((posy + CHDOT_HEIGHT > outbmpfile.height()) || (posx + numsubtitles / 2 * CHDOT_WIDTH > outbmpfile.width()))) // 要显示的位置超出图片范围，则不显示字幕，并给出提示
	{
		numsubtitles = 0;
		cerr << "需要显示的字幕超出图片范围，不予显示" << endl;
	}
	if (args[OPT_ARGS_STYLE].get_string() == "vertical" && ((posx + CHDOT_WIDTH > outbmpfile.width()) || (posy + numsubtitles / 2 * CHDOT_HEIGHT > outbmpfile.height())))
	{
		numsubtitles = 0;
		cerr << "需要显示的字幕超出图片范围，不予显示" << endl;
	}
	/* color */
	unsigned char rgb[3] = { 0 };
	string rgbhex = args[OPT_ARGS_COLOR].get_string();
	if (outbmpfile.get_biBitCount() <= 8) // 小于24位，置为全0，也就是黑色
	{
		rgbhex.clear();
		rgbhex = "000000"; 
	}
	if (isValidRGBColor(rgbhex, rgb) == false) // 如果合法，则已经实现转换
	{
		cerr << "输入的颜色不合法，默认置为全红" << endl;
		rgb[0] = 255; 
		rgb[1] = 0;
		rgb[2] = 0;   // 如果不合法，将默认值置为全红色
	}

	/* traditional */
	ifstream Chdotfile;
	if(args[OPT_ARGS_TRADITIONAL].existed())
		Chdotfile.open("HZK16F", ios::in | ios::binary);
	else
		Chdotfile.open("HZK16",  ios::in | ios::binary);
	if (!Chdotfile.is_open())
	{
		cout << "无法打开GB2312汉字点阵字库文件" << endl;
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
	/* 将bmpdata的变化写回outbmpfile */
	outbmpfile.update_bmpfile(outfile.c_str());

	Chdotfile.close();
	return 0;
}
