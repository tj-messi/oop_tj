/* 2150792 计科 牛禄阳 */
#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <fstream>
#include "15-b6-bmp.h"
#define RGB(r,g,b)   ((COLORREF)(((BYTE)(r)|((WORD)((BYTE)(g))<<8))|(((DWORD)(BYTE)(b))<<16)))
using namespace std;

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
	if (biBitCount <= 8)
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

bitmap_image :: ~bitmap_image()
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
		int pixelOffset = (b_row * RowByteCnt) + b_col / PixelPerbytes;  // 计算像素在位图数据中的偏移量
		unsigned int index = bmp_data[pixelOffset];
		int indexOffset = (PixelPerbytes - 1 - b_col % PixelPerbytes) * biBitCount;// 计算当前像素索引的位偏移量
		index >>= indexOffset; // 将当前像素的颜色索引位移到字节的最低位
		index = index % biClrUsed;
		unsigned char B = color_board[index][0];
		unsigned char G = color_board[index][1];
		unsigned char R = color_board[index][2];
		return RGB(R, G, B);
	}
	else // 24/32位位图
	{
		int bytesPerPixel = biBitCount / 8;  //每个像素占用的字节数
		int pixelOffset = (b_row * RowByteCnt) + bytesPerPixel * b_col;
		unsigned char B = bmp_data[pixelOffset];
		unsigned char G = bmp_data[pixelOffset + 1];
		unsigned char R = bmp_data[pixelOffset + 2];
		return RGB(R, G, B);
	}
}
