/* 2150792 计科 牛禄阳 */
#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <sstream>
#include <fstream>
#include <string>
#include "bmp_subtitles.h"
#define RGB(r,g,b)   ((COLORREF)(((BYTE)(r)|((WORD)((BYTE)(g))<<8))|(((DWORD)(BYTE)(b))<<16)))
using namespace std;
/* ======使用到的其余函数====== */
/* 根据中文字符的机内码，得到其GB2312编码的16X16点阵信息 */
void Ch_to_dotmartix(ifstream& Chdotfile, int(*dotmatrix)[CHDOT_WIDTH], const unsigned char Ch_encoding[2])
{
	int areacode = Ch_encoding[1] - 160;             // 高位是区码
	int bitcode = Ch_encoding[0] - 160;              // 低位是位码
	int Chdotsize = (CHDOT_WIDTH * CHDOT_HEIGHT) / 8;// 每个汉字的点阵信息字节数
	int dotoffset = Chdotsize * ((areacode - 1) * AREACODE_NUM + bitcode - 1); // 当前汉字在点阵文件中的位置
	Chdotfile.seekg(0, ios::beg);
	Chdotfile.seekg(dotoffset, ios::cur);
	unsigned char temp[CHDOT_WIDTH / 8] = { 0 };      // 点阵每行的数据是两个字节
	for (int i = 0; i < CHDOT_HEIGHT; i++)            // 遍历点阵的行，对应坐标y
	{
		Chdotfile.read((char*)temp, 2 * sizeof(unsigned char)); // 读取当前行点阵数据
		for (int j = 0; j < CHDOT_WIDTH; j++)         // 遍历点阵的列，对应坐标x
			dotmatrix[i][j] = temp[j / 8] & ((unsigned char)1 << (7 - j % 8)); // 取出指定位的0/1
	}
}
/* 将hex字符串转化为unsigned char */
unsigned char hexToChar(const string& hexStr) 
{
	return (unsigned char)(stoi(hexStr, nullptr, 16));
}
/* 检测hex字符串是否合法，如果合法，将hex字符串转化为RGB */
bool isValidRGBColor(const string& hexColor, unsigned char rgb[3])
{
	// 检查字符串长度是否为6
	if (hexColor.length() != 6)
		return false;

	// 遍历每两个字符并进行转换和范围检查
	for (int i = 0; i < 6; i += 2)
	{
		unsigned char value = hexToChar(hexColor.substr(i, 2)); // 取出每两个字符的子字符串
		// 检查转换后的值是否在0到255的范围内
		if (value < 0 || value > 255)
			return false;
		rgb[i / 2] = value;
	}
	return true; // 字符串符合要求
}
/* 文件的复制 */
bool copyFile(const string& sourceFile, const string& destinationFile) 
{
	ifstream inputFile(sourceFile, ios::in | ios::binary);       // 打开源文件作为输入流
	if (!inputFile.is_open())
	{
		cout << "无法打开" << sourceFile << endl;
		return false;
	}
	ofstream outputFile(destinationFile, ios::out | ios::binary); // 创建或打开目标文件作为输出流
	if (!inputFile.is_open())
	{
		cout << "无法打开" << destinationFile << endl;
		inputFile.close();
		return false;
	}

	char ch;
	while (inputFile.get(ch)) 
		outputFile.put(ch);

	inputFile.close();
	outputFile.close();
	return true;
}

/* bitmap_image类体外实现 */
bitmap_image::bitmap_image(const char* filename)
{
	ifstream in;
	in.open(filename, ios::in | ios::binary);
	if (!in.is_open())
	{
		cout << "打开文件失败！" << endl;
		exit(-1);
	}
	/* 读文件头有效内容 */
	in.seekg(2, ios::cur);
	in.read((char*)(&filesize), sizeof(int));
	in.seekg(4, ios::cur);
	in.read((char*)(&bfoffBits), sizeof(unsigned long));
	/* 读位图信息头有效内容 */
	in.seekg(4, ios::cur);
	in.read((char*)(&b_width), sizeof(int));
	in.read((char*)(&b_height), sizeof(int));
	in.seekg(2, ios::cur);
	in.read((char*)(&biBitCount), sizeof(short));
	in.seekg(16, ios::cur);
	in.read((char*)(&biClrUsed), sizeof(int));
	if (biClrUsed == 0)
		biClrUsed = (1 << biBitCount);
	/* 读调色板颜色信息 */
	in.seekg(4, ios::cur);
	if (biBitCount <= 8) // 只有biBitCount小于等于8时才需要用到调色板
	{
		color_board = new(nothrow) unsigned char[biClrUsed][4]; // 根据使用到的颜色数确定调色板数组
		if (color_board == NULL)
		{
			cout << "申请空间失败！" << endl;
			exit(-1);
		}
		memset(color_board, 0, sizeof(color_board));
		in.read((char*)color_board, biClrUsed * 4); // 每个颜色需要四个字节
	}
	else
		color_board = NULL;
	/* 读位图数据 */
	bmp_data = new(nothrow)unsigned char[filesize];
	if (bmp_data == NULL)
	{
		cout << "申请空间失败！" << endl;
		exit(-1);
	}
	in.read((char*)bmp_data, filesize - bfoffBits); // 文件大小减去文件头到位图数据的偏移
	in.close();
}

bitmap_image::~bitmap_image()
{
	delete[] color_board;
	delete[] bmp_data;
}

int bitmap_image::width() const
{
	return b_width;
}

int bitmap_image::height() const
{
	return abs(b_height);   // 读到的位图高度可能是负数，这里取绝对值
}

short bitmap_image::get_biBitCount() const
{
	return  biBitCount;
}

unsigned int bitmap_image::get_pixel(int row, int col) const
{
	int b_row = (b_height) > 0 ? (b_height - row - 1) : row; // 位图的高度正负决定倒和正
	int b_col = col;
	int RowByteCnt = (((b_width * biBitCount) + 31) >> 5) << 2;
	/* 在处理 8 位及以下的位图，使用调色板时，一个字节可能包含多个像素的颜色索引，
	   每个索引可能占用不同数量的位 */
	if (biBitCount <= 8) // 单/16/256色位图
	{
		int PixelPerbytes = 8 / biBitCount;  //每个字节对应的像素数
		int pixeloffset = (b_row * RowByteCnt) + b_col / PixelPerbytes;  // 计算像素在位图数据中的偏移量
		unsigned int index = bmp_data[pixeloffset];
		int indexoffset = (PixelPerbytes - 1 - b_col % PixelPerbytes) * biBitCount;// 计算当前像素索引的位偏移量
		index >>= indexoffset; // 将当前像素的颜色索引位移到字节的最低位
		index = index % biClrUsed;
		unsigned char B = color_board[index][0];
		unsigned char G = color_board[index][1];
		unsigned char R = color_board[index][2];
		return RGB(R, G, B);
	}
	else // 24/32位位图
	{
		int bytesPerPixel = biBitCount / 8;  //每个像素占用的字节数
		int pixeloffset = (b_row * RowByteCnt) + bytesPerPixel * b_col;
		unsigned char B = bmp_data[pixeloffset];
		unsigned char G = bmp_data[pixeloffset + 1];
		unsigned char R = bmp_data[pixeloffset + 2];
		return RGB(R, G, B);
	}
}

void bitmap_image::add_Ch_subtitles(ifstream& Chdotfile, const unsigned char Ch_encoding[2], const int posx, const int posy, const unsigned char rgb[3])
{
	int  dotmatrix[CHDOT_HEIGHT][CHDOT_WIDTH] = { 0 };
	Ch_to_dotmartix(Chdotfile, dotmatrix, Ch_encoding);
	for (int y = 0; y < CHDOT_HEIGHT; y++)
	{
		for (int x = 0; x < CHDOT_WIDTH; x++)
		{
			int row = posy + y, col = posx + x;
			int b_row = (b_height) > 0 ? (b_height - row - 1) : row; // 位图的高度正负决定倒和正
			int b_col = col;
			int RowByteCnt = (((b_width * biBitCount) + 31) >> 5) << 2;
			if (dotmatrix[y][x])
			{
				if (biBitCount <= 8)
				{
					int PixelPerbytes = 8 / biBitCount;  //每个字节对应的像素数
					int pixeloffset = (b_row * RowByteCnt) + b_col / PixelPerbytes;  // 计算像素在位图数据中的偏移量
					int indexoffset = (PixelPerbytes - 1 - b_col % PixelPerbytes) * biBitCount;// 计算当前像素索引的位偏移量
					bmp_data[pixeloffset] &= ~((biClrUsed - 1) << indexoffset);
				}
				else
				{
					int bytesPerPixel = biBitCount / 8;  //每个像素占用的字节数
					int pixeloffset = (b_row * RowByteCnt) + bytesPerPixel * b_col;
					bmp_data[pixeloffset] = rgb[2];       // B
					bmp_data[pixeloffset + 1] = rgb[1];   // G
					bmp_data[pixeloffset + 2] = rgb[0];   // R
				}
			}
		}
	}
}

bool bitmap_image::update_bmpfile(const char* filename) 
{  // 只需要修改bmp文件的位图信息,也就是bmpdate即可
	fstream outputFile(filename, ios::in | ios::out | ios::binary | ios::ate); // 创建或打开目标文件作为输出流
	if (!outputFile.is_open())
	{
		cout << "无法打开写回的BMP文件" << endl;
		return false;
	}
	outputFile.seekp(0, ios::beg);
	outputFile.seekp(bfoffBits, ios::cur); // 移动到位图信息位置
	outputFile.write((char*)bmp_data, filesize - bfoffBits); // 文件大小减去文件头到位图数据的偏移

	outputFile.close();
	return true;
}
