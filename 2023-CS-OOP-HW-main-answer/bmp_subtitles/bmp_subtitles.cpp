/* 2150792 �ƿ� ţ»�� */
#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <sstream>
#include <fstream>
#include <string>
#include "bmp_subtitles.h"
#define RGB(r,g,b)   ((COLORREF)(((BYTE)(r)|((WORD)((BYTE)(g))<<8))|(((DWORD)(BYTE)(b))<<16)))
using namespace std;
/* ======ʹ�õ������ຯ��====== */
/* ���������ַ��Ļ����룬�õ���GB2312�����16X16������Ϣ */
void Ch_to_dotmartix(ifstream& Chdotfile, int(*dotmatrix)[CHDOT_WIDTH], const unsigned char Ch_encoding[2])
{
	int areacode = Ch_encoding[1] - 160;             // ��λ������
	int bitcode = Ch_encoding[0] - 160;              // ��λ��λ��
	int Chdotsize = (CHDOT_WIDTH * CHDOT_HEIGHT) / 8;// ÿ�����ֵĵ�����Ϣ�ֽ���
	int dotoffset = Chdotsize * ((areacode - 1) * AREACODE_NUM + bitcode - 1); // ��ǰ�����ڵ����ļ��е�λ��
	Chdotfile.seekg(0, ios::beg);
	Chdotfile.seekg(dotoffset, ios::cur);
	unsigned char temp[CHDOT_WIDTH / 8] = { 0 };      // ����ÿ�е������������ֽ�
	for (int i = 0; i < CHDOT_HEIGHT; i++)            // ����������У���Ӧ����y
	{
		Chdotfile.read((char*)temp, 2 * sizeof(unsigned char)); // ��ȡ��ǰ�е�������
		for (int j = 0; j < CHDOT_WIDTH; j++)         // ����������У���Ӧ����x
			dotmatrix[i][j] = temp[j / 8] & ((unsigned char)1 << (7 - j % 8)); // ȡ��ָ��λ��0/1
	}
}
/* ��hex�ַ���ת��Ϊunsigned char */
unsigned char hexToChar(const string& hexStr) 
{
	return (unsigned char)(stoi(hexStr, nullptr, 16));
}
/* ���hex�ַ����Ƿ�Ϸ�������Ϸ�����hex�ַ���ת��ΪRGB */
bool isValidRGBColor(const string& hexColor, unsigned char rgb[3])
{
	// ����ַ��������Ƿ�Ϊ6
	if (hexColor.length() != 6)
		return false;

	// ����ÿ�����ַ�������ת���ͷ�Χ���
	for (int i = 0; i < 6; i += 2)
	{
		unsigned char value = hexToChar(hexColor.substr(i, 2)); // ȡ��ÿ�����ַ������ַ���
		// ���ת�����ֵ�Ƿ���0��255�ķ�Χ��
		if (value < 0 || value > 255)
			return false;
		rgb[i / 2] = value;
	}
	return true; // �ַ�������Ҫ��
}
/* �ļ��ĸ��� */
bool copyFile(const string& sourceFile, const string& destinationFile) 
{
	ifstream inputFile(sourceFile, ios::in | ios::binary);       // ��Դ�ļ���Ϊ������
	if (!inputFile.is_open())
	{
		cout << "�޷���" << sourceFile << endl;
		return false;
	}
	ofstream outputFile(destinationFile, ios::out | ios::binary); // �������Ŀ���ļ���Ϊ�����
	if (!inputFile.is_open())
	{
		cout << "�޷���" << destinationFile << endl;
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

/* bitmap_image������ʵ�� */
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
	if (biBitCount <= 8) // ֻ��biBitCountС�ڵ���8ʱ����Ҫ�õ���ɫ��
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
	return abs(b_height);   // ������λͼ�߶ȿ����Ǹ���������ȡ����ֵ
}

short bitmap_image::get_biBitCount() const
{
	return  biBitCount;
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
		int pixeloffset = (b_row * RowByteCnt) + b_col / PixelPerbytes;  // ����������λͼ�����е�ƫ����
		unsigned int index = bmp_data[pixeloffset];
		int indexoffset = (PixelPerbytes - 1 - b_col % PixelPerbytes) * biBitCount;// ���㵱ǰ����������λƫ����
		index >>= indexoffset; // ����ǰ���ص���ɫ����λ�Ƶ��ֽڵ����λ
		index = index % biClrUsed;
		unsigned char B = color_board[index][0];
		unsigned char G = color_board[index][1];
		unsigned char R = color_board[index][2];
		return RGB(R, G, B);
	}
	else // 24/32λλͼ
	{
		int bytesPerPixel = biBitCount / 8;  //ÿ������ռ�õ��ֽ���
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
			int b_row = (b_height) > 0 ? (b_height - row - 1) : row; // λͼ�ĸ߶���������������
			int b_col = col;
			int RowByteCnt = (((b_width * biBitCount) + 31) >> 5) << 2;
			if (dotmatrix[y][x])
			{
				if (biBitCount <= 8)
				{
					int PixelPerbytes = 8 / biBitCount;  //ÿ���ֽڶ�Ӧ��������
					int pixeloffset = (b_row * RowByteCnt) + b_col / PixelPerbytes;  // ����������λͼ�����е�ƫ����
					int indexoffset = (PixelPerbytes - 1 - b_col % PixelPerbytes) * biBitCount;// ���㵱ǰ����������λƫ����
					bmp_data[pixeloffset] &= ~((biClrUsed - 1) << indexoffset);
				}
				else
				{
					int bytesPerPixel = biBitCount / 8;  //ÿ������ռ�õ��ֽ���
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
{  // ֻ��Ҫ�޸�bmp�ļ���λͼ��Ϣ,Ҳ����bmpdate����
	fstream outputFile(filename, ios::in | ios::out | ios::binary | ios::ate); // �������Ŀ���ļ���Ϊ�����
	if (!outputFile.is_open())
	{
		cout << "�޷���д�ص�BMP�ļ�" << endl;
		return false;
	}
	outputFile.seekp(0, ios::beg);
	outputFile.seekp(bfoffBits, ios::cur); // �ƶ���λͼ��Ϣλ��
	outputFile.write((char*)bmp_data, filesize - bfoffBits); // �ļ���С��ȥ�ļ�ͷ��λͼ���ݵ�ƫ��

	outputFile.close();
	return true;
}
