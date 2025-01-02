/* 2150792 �ƿ� ţ»�� */
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
		cout << "���ļ�ʧ�ܣ�" << endl;
		exit(-1);
	}
	/* ���ļ�ͷ��Ч���� */
	in.seekg(2, ios::cur);
	in.read((char*)(&filesize), sizeof(int));
	in.seekg(4, ios::cur);
	in.read((char*)(&bfoffBits), sizeof(unsigned long));
	/* ��λͼ��Ϣͷ��Ч���� */
	in.seekg(4, ios::cur);
	in.read((char*)(&b_width), sizeof(int));
	in.read((char*)(&b_height), sizeof(int));
	in.seekg(2, ios::cur);
	in.read((char*)(&biBitCount), sizeof(short));
	in.seekg(16, ios::cur);
	in.read((char*)(&biClrUsed), sizeof(int));
	if (biClrUsed == 0)
		biClrUsed = (1 << biBitCount);
	/* ����ɫ����ɫ��Ϣ */
	in.seekg(4, ios::cur);
	if (biBitCount <= 8)
	{	
		color_board = new(nothrow) unsigned char[biClrUsed][4]; // ����ʹ�õ�����ɫ��ȷ����ɫ������
		if (color_board == NULL)
		{
			cout << "����ռ�ʧ�ܣ�" << endl;
			exit(-1);
		}
		memset(color_board, 0, sizeof(color_board));
		in.read((char*)color_board, biClrUsed * 4); // ÿ����ɫ��Ҫ�ĸ��ֽ�
	}
	else
		color_board = NULL;
	/* ��λͼ���� */
	bmp_data = new(nothrow)unsigned char[filesize];
	if (bmp_data == NULL)
	{
		cout << "����ռ�ʧ�ܣ�" << endl;
		exit(-1);
	}
	in.read((char*)bmp_data, filesize - bfoffBits); // �ļ���С��ȥ�ļ�ͷ��λͼ���ݵ�ƫ��
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
	return abs(b_height);   // ������λͼ�߶ȿ����Ǹ���������ȡ����ֵ
}

unsigned int bitmap_image::get_pixel(int row, int col) const
{
	int b_row = (b_height) > 0 ? (b_height - row - 1) : row; // λͼ�ĸ߶���������������
	int b_col = col;
	int RowByteCnt = (((b_width * biBitCount) + 31) >> 5) << 2;
	/* �ڴ��� 8 λ�����µ�λͼ��ʹ�õ�ɫ��ʱ��һ���ֽڿ��ܰ���������ص���ɫ������
	   ÿ����������ռ�ò�ͬ������λ */
	if (biBitCount <= 8) // ��/16/256ɫλͼ
	{
		int PixelPerbytes = 8 / biBitCount;  //ÿ���ֽڶ�Ӧ��������
		int pixelOffset = (b_row * RowByteCnt) + b_col / PixelPerbytes;  // ����������λͼ�����е�ƫ����
		unsigned int index = bmp_data[pixelOffset];
		int indexOffset = (PixelPerbytes - 1 - b_col % PixelPerbytes) * biBitCount;// ���㵱ǰ����������λƫ����
		index >>= indexOffset; // ����ǰ���ص���ɫ����λ�Ƶ��ֽڵ����λ
		index = index % biClrUsed;
		unsigned char B = color_board[index][0];
		unsigned char G = color_board[index][1];
		unsigned char R = color_board[index][2];
		return RGB(R, G, B);
	}
	else // 24/32λλͼ
	{
		int bytesPerPixel = biBitCount / 8;  //ÿ������ռ�õ��ֽ���
		int pixelOffset = (b_row * RowByteCnt) + bytesPerPixel * b_col;
		unsigned char B = bmp_data[pixelOffset];
		unsigned char G = bmp_data[pixelOffset + 1];
		unsigned char R = bmp_data[pixelOffset + 2];
		return RGB(R, G, B);
	}
}
