/* 2150792 �ƿ� ţ»�� */
#pragma once
#include <iostream>
#include <string>
#include <fstream>
using namespace std;
/* �������Լ�ö�ٶ��� */
const int CHDOT_WIDTH = 16;
const int CHDOT_HEIGHT = 16;
const int AREACODE_NUM = 94;
enum OPT_ARGS {
    OPT_ARGS_BMPFILE = 0,
    OPT_ARGS_OUTFILE,
    OPT_ARGS_TRADITIONAL,
    OPT_ARGS_SUBTITLES,
    OPT_ARGS_POSX,
    OPT_ARGS_POSY,
    OPT_ARGS_COLOR,
    OPT_ARGS_STYLE,
};


/*
�ļ�ͷ��14�ֽ�
0 - 1  ���ļ����ͣ��̶�ΪBM�������ȡ
2 - 5: ���ļ���С����Ҫ����
6 - 9  ������λ���̶�Ϊ0�������ȡ
a - d  ��ƫ�������ļ�ͷ��λͼ���ݵ�ƫ�ƣ���Ҫ��ȡ

λͼ��Ϣͷ��
e  - 11  ����Ϣͷ�Ĵ�С���̶�Ϊ40�������ȡ
12 - 15  ��ͼ��Ŀ�ȣ���Ҫ��ȡ
16 - 19  ��ͼ��ĸ߶ȣ���Ҫ��ȡ������˵��ͼ���ǵ���
1a - 1b  ����ɫƽ�������̶�Ϊ1�������ȡ
1c - 1d  ��ÿ�����ص�bit������Ҫ��ȡ��ֵһ��Ϊ1/4/8/24�ȣ���Ӧ��ɫλͼ/16ɫλͼ/256ɫλͼ/24λλͼ
1e - 2d  ��������������ݣ��������ȡ
2e - 31  ��ʹ�õ���ɫ����������Ҫ��ȡ
32 - 35  ����Ҫ����ɫ�������������ȡ

��ɫ�壺
��ɫ����ʵ��һ��ӳ�����ʶ��ɫ����������������ɫ�Ķ�Ӧ��ϵ��
�����ļ��еĲ��־���һ����ά����palette[N][4],����N��ʾ�ܵ���ɫ��������
ÿ�е��ĸ�Ԫ�طֱ��ʾ��������Ӧ��B��G��R��Alpha��ֵ��ÿ������ռһ���ֽڡ�
�粻��͸��ͨ��ʱ��AlphaΪ0��
��Ϊǰ��֪������ͼ��256����ɫ���������N = 256��
�����ž��������е��кţ���Ӧ����ɫ���������е��ĸ�Ԫ�ء�

λͼ���ݣ�
ÿ������ռһ���ֽڣ�ȡ������ֽں��Ը��ֽ�Ϊ������ѯ��Ӧ����ɫ
��ʾ����Ӧ����ʾ�豸��

��Ȼ���������ʹ��seekg������ֱ�ӽ�ֹ�ṹ����롣
Ȼ�����Windows��bmp�ļ���ʽ���нṹ��Ķ��壬һ����14�ֽڣ���һ��40�ֽڡ�

*/
class bitmap_image
{
protected:
    /* ������Ҫ�����Լ��Ķ��� */
    int filesize;            // �ļ�ͷ2-5�ֽڣ�˵���ļ��Ĵ�С
    int b_width;
    int b_height;
    short biBitCount;        // ÿ�����ص��bit�� 
    int  biClrUsed;          // ��ɫ����
    unsigned long bfoffBits; // �ļ�ͷ��λͼ���ݵ�ƫ��
    unsigned char* bmp_data; // λͼ����
    unsigned char(*color_board)[4];      // ��ɫ��,ÿ�е��ĸ�Ԫ�طֱ��ʾ��������Ӧ��B��G��R��Alpha��ֵ
public:
    int width() const;	//����ͼƬ�Ŀ��
    int height() const; //����ͼƬ�ĸ߶�
    short get_biBitCount() const;
    unsigned int get_pixel(int row, int col) const; //����ָ�����RGB��ɫ
    /* ������Ҫ�����Լ��Ķ��� */
    bitmap_image(const char* filename);   // ���캯��,filename��inbmp������
    bool update_bmpfile(const char* filename); // �����º������Ϣд��bmp�ļ�
    ~bitmap_image();
    void add_Ch_subtitles(ifstream& Chdotfile, const unsigned char Ch_encoding[2], const int posx, const int posy, const unsigned char rgb[3]);
};

/* �õ����������������� */
unsigned char hexToChar(const string& hexStr);
bool isValidRGBColor(const string& hexColor, unsigned char rgb[3]);
void Ch_to_dotmartix(ifstream& Chdotfile, int(*dotmatrix)[CHDOT_WIDTH], const unsigned char Ch_encoding[2]);
bool copyFile(const string& sourceFile, const string& destinationFile);
