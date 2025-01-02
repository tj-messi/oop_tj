/*2351114 �쿡�� ������*/
#pragma once

//����������κ�ͷ�ļ����ر���<Windows.h>���鵽����0�������ǵ���-20 ������

//���в���������ϣ��˽������⼸��Ԥ������������ã����ܷ�������ҵ�������㣡����
//#pragma pack(show) //�Ծ�����Ϣ����ʽ��ʾ��ǰ�ֽڶ����ֵ
//#pragma pack(push) //����ǰ�ֽڶ���ֵѹ�������ջ��ջ��
//#pragma pack(push, 4) //����ǰ�ֽڶ���ֵѹ�������ջ��ջ����Ȼ���ٽ�4���õ�ǰֵ
//#pragma pack(pop)  //��������ջջ�����ֽڶ���ֵ����������Ϊ��ǰֵ
//#pragma pack() //���������ǻָ�Ĭ��ֵ

//������������Ҫ�Ľṹ�壨�ࣩ����������������


struct color_palette
{
    unsigned char blue;
    unsigned char green;
    unsigned char red;
    unsigned char reserved_byte;
};


class bitmap {
private:
    int bmp_start_pos; // BMP������ʼλ��
    int width;         // ͼ����
    int height;        // ͼ��߶�
    unsigned short bits_per_pixel; // ÿ����λ��
    int bits_per_row;  // ÿ��������ռ��λ��
    int bytes_per_row; // ÿ���ֽ���ռ�Ĵ�С
    char* _file_name;  // �ļ���
    unsigned char* pixel_data; // �洢��������
    color_palette* palette; // ��ɫ��

    unsigned int get_pixel_color(int x, int y) const; // ��ȡ���ص���ɫֵ

public:
    //���в��ֲ���������κ�����
    bitmap(const char* const filename);
    ~bitmap();
    int show(const int top_left_x, const int top_left_y, const int angle, const bool is_mirror,
        void (*draw_point)(const int x, const int y, const unsigned char red, const unsigned char green, const unsigned char blue)) const;
};