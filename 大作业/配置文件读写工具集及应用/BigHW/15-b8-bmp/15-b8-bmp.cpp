/*2351114 �쿡�� ������*/
#define _CRT_SECURE_NO_WARNINGS 
#include <iostream>
#include <fstream>
//������������κ�ͷ�ļ����ر���<Windows.h>���鵽����0�������ǵ���-20!!!!!
#include "15-b8-bmp.h"

using namespace std;

/***************************************************************************
  �������ƣ�
  ��    �ܣ���ȡBMP�ļ�
  ���������const char* filename
  �� �� ֵ��
  ˵    �������貹��
***************************************************************************/
bitmap::bitmap(const char* const filename) : _file_name(nullptr), pixel_data(nullptr), palette(nullptr) {
    // �� BMP �ļ�
    ifstream bmp_file(filename, ios::binary);
    if (!bmp_file) {
        cerr << "Failed to open BMP file." << endl;
        return;
    }

    // ��ȡ BMP �ļ�ͷ��Ϣ
    char header[54];
    bmp_file.read(header, 54);

    // ����Ƿ�Ϊ BMP �ļ�
    if (header[0] != 'B' || header[1] != 'M') {
        cerr << "Not a valid BMP file." << endl;
        return;
    }

    // ��ȡͼ���ȡ��߶ȡ�λ��ȵ���Ϣ
    width = *(int*)&header[18];
    height = *(int*)&header[22];
    bits_per_pixel = *(short*)&header[28];
    bmp_start_pos = *(int*)&header[10];

    // ����ÿ���ֽ���
    bytes_per_row = ((bits_per_pixel * width + 31) / 32) * 4;

    // ����λ��ȶ�ȡ��ɫ�壨�����Ҫ��
    if (bits_per_pixel == 1 || bits_per_pixel == 4 || bits_per_pixel == 8) {
        int palette_size = (bmp_start_pos - 54) / 4; // ÿ����ɫ����Ŀ4���ֽ�
        palette = new color_palette[palette_size];

        // ��ȡ��ɫ��
        bmp_file.read(reinterpret_cast<char*>(palette), palette_size * 4);
    }

    // �����������ݿռ�
    pixel_data = new unsigned char[height * bytes_per_row];

    // ����ͼ������λ��
    bmp_file.seekg(bmp_start_pos, ios::beg);

    // ��ȡ��������
    bmp_file.read(reinterpret_cast<char*>(pixel_data), height * bytes_per_row);

    // �ر��ļ�
    bmp_file.close();
}

bitmap::~bitmap() {
    delete[] pixel_data;
    delete[] palette; // �ͷŵ�ɫ���ڴ�
}

// ����λ��Ⱥ���ɫģʽ��ȡ��Ӧ���ص���ɫֵ
unsigned int bitmap::get_pixel_color(int x, int y) const {
    // ���㵱ǰ�����������е�ƫ����
    int pixel_offset = y * bytes_per_row + x * (bits_per_pixel / 8);
    unsigned int color = 0;

    if (bits_per_pixel == 1) {
        // 1λɫ��ÿ��������1λ��ʾ��0��1�ǵ�ɫ������
        int byte_pos = y * bytes_per_row + x / 8; // ���㵱ǰ�������ڵ��ֽ�λ��
        int bit_pos = 7 - (x % 8);               // �����ֽ��ڵı���λ�ã���λ���ȣ�
        unsigned char pixel_byte = pixel_data[byte_pos];
        unsigned int color_index = (pixel_byte >> bit_pos) & 0x01; // ��ȡĿ��λ
        color = (palette[color_index].red << 16) |
            (palette[color_index].green << 8) |
            palette[color_index].blue;
    }
    else if (bits_per_pixel == 4) {
        // 4λɫ��ÿ��������4λ��ʾ��ÿ�ֽڱ�ʾ2������
        int byte_pos = y * bytes_per_row + x / 2; // ���㵱ǰ�������ڵ��ֽ�λ��
        unsigned char pixel_byte = pixel_data[byte_pos];
        unsigned int color_index;
        if (x % 2 == 0) {
            // ��4λ
            color_index = (pixel_byte >> 4) & 0x0F;
        }
        else {
            // ��4λ
            color_index = pixel_byte & 0x0F;
        }
        color = (palette[color_index].red << 16) |
            (palette[color_index].green << 8) |
            palette[color_index].blue;
    }
    else if (bits_per_pixel == 8) {
        // 256ɫͼ��ÿ�������� 8 λ��ʾ����� 256 ����ɫ
        unsigned char color_index = pixel_data[pixel_offset];

        // �ӵ�ɫ���л�ȡ��ɫֵ
        color = (palette[color_index].red << 16) | (palette[color_index].green << 8) | palette[color_index].blue;
    }
    else if (bits_per_pixel == 24) {
        // 24λɫͼ��ÿ�������� 24 λ��ʾ��RGB
        unsigned char blue = pixel_data[pixel_offset];
        unsigned char green = pixel_data[pixel_offset + 1];
        unsigned char red = pixel_data[pixel_offset + 2];

        // ���� RGB ��ɫֵ
        color = (red << 16) | (green << 8) | blue;
    }
    else if (bits_per_pixel == 32) {
        // 32λɫͼ��ÿ�������� 32 λ��ʾ��RGBA������͸����
        unsigned char blue = pixel_data[pixel_offset];
        unsigned char green = pixel_data[pixel_offset + 1];
        unsigned char red = pixel_data[pixel_offset + 2];
        unsigned char alpha = pixel_data[pixel_offset + 3]; // Alpha ͨ��������

        // ���� RGB ��ɫֵ
        color = (red << 16) | (green << 8) | blue;
    }
    else {
        // ��֧�ֵ�λ���
        cerr << "Unsupported bit depth: " << bits_per_pixel << endl;
        return 0;
    }

    return color;
}

int bitmap::show(const int top_left_x, const int top_left_y, const int angle, const bool is_mirror,
    void (*draw_point)(const int x, const int y, const unsigned char red, const unsigned char green, const unsigned char blue)) const {
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            unsigned int color = get_pixel_color(x, y);
            unsigned char red = (color >> 16) & 0xFF;
            unsigned char green = (color >> 8) & 0xFF;
            unsigned char blue = color & 0xFF;

            // �����Ҫ�������תͼ��������Խ�������任
            int new_x = x;
            int new_y = y;
            switch (angle) {
                case 0:
                    new_x = is_mirror ? width - 1 - x : x;
                    new_y = height - 1 - y; // ��ֱ�������
                    break;
                case 90:
                    new_x = is_mirror ? y : height - 1 - y; // ˮƽ�������
                    new_y = width - 1 - x;
                    break;
                case 180:
                    new_x = is_mirror ? x : width - 1 - x;
                    new_y = y; // ��ֱ�������
                    break;
                case 270:
                    new_x = is_mirror ? height - 1 - y : y; // ˮƽ�������
                    new_y = x;
                    break;
                default:
                    cerr << "Unsupported angle: " << angle << endl;
                    return -1;
            }

            // ���û��㺯����������
            draw_point(new_x + top_left_x, new_y + top_left_y, red, green, blue);
        }
    }
    return 0;
}