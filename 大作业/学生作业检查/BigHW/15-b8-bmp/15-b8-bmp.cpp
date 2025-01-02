/*2351114 朱俊泽 大数据*/
#define _CRT_SECURE_NO_WARNINGS 
#include <iostream>
#include <fstream>
//不再允许加入任何头文件，特别是<Windows.h>，查到就是0分甚至是倒扣-20!!!!!
#include "15-b8-bmp.h"

using namespace std;

/***************************************************************************
  函数名称：
  功    能：读取BMP文件
  输入参数：const char* filename
  返 回 值：
  说    明：按需补充
***************************************************************************/
bitmap::bitmap(const char* const filename) : _file_name(nullptr), pixel_data(nullptr), palette(nullptr) {
    // 打开 BMP 文件
    ifstream bmp_file(filename, ios::binary);
    if (!bmp_file) {
        cerr << "Failed to open BMP file." << endl;
        return;
    }

    // 读取 BMP 文件头信息
    char header[54];
    bmp_file.read(header, 54);

    // 检查是否为 BMP 文件
    if (header[0] != 'B' || header[1] != 'M') {
        cerr << "Not a valid BMP file." << endl;
        return;
    }

    // 获取图像宽度、高度、位深度等信息
    width = *(int*)&header[18];
    height = *(int*)&header[22];
    bits_per_pixel = *(short*)&header[28];
    bmp_start_pos = *(int*)&header[10];

    // 计算每行字节数
    bytes_per_row = ((bits_per_pixel * width + 31) / 32) * 4;

    // 根据位深度读取调色板（如果需要）
    if (bits_per_pixel == 1 || bits_per_pixel == 4 || bits_per_pixel == 8) {
        int palette_size = (bmp_start_pos - 54) / 4; // 每个调色板条目4个字节
        palette = new color_palette[palette_size];

        // 读取调色板
        bmp_file.read(reinterpret_cast<char*>(palette), palette_size * 4);
    }

    // 分配像素数据空间
    pixel_data = new unsigned char[height * bytes_per_row];

    // 跳到图像数据位置
    bmp_file.seekg(bmp_start_pos, ios::beg);

    // 读取像素数据
    bmp_file.read(reinterpret_cast<char*>(pixel_data), height * bytes_per_row);

    // 关闭文件
    bmp_file.close();
}

bitmap::~bitmap() {
    delete[] pixel_data;
    delete[] palette; // 释放调色板内存
}

// 根据位深度和颜色模式读取相应像素的颜色值
unsigned int bitmap::get_pixel_color(int x, int y) const {
    // 计算当前像素在数据中的偏移量
    int pixel_offset = y * bytes_per_row + x * (bits_per_pixel / 8);
    unsigned int color = 0;

    if (bits_per_pixel == 1) {
        // 1位色，每个像素用1位表示，0或1是调色板索引
        int byte_pos = y * bytes_per_row + x / 8; // 计算当前像素所在的字节位置
        int bit_pos = 7 - (x % 8);               // 计算字节内的比特位置（高位优先）
        unsigned char pixel_byte = pixel_data[byte_pos];
        unsigned int color_index = (pixel_byte >> bit_pos) & 0x01; // 提取目标位
        color = (palette[color_index].red << 16) |
            (palette[color_index].green << 8) |
            palette[color_index].blue;
    }
    else if (bits_per_pixel == 4) {
        // 4位色，每个像素用4位表示，每字节表示2个像素
        int byte_pos = y * bytes_per_row + x / 2; // 计算当前像素所在的字节位置
        unsigned char pixel_byte = pixel_data[byte_pos];
        unsigned int color_index;
        if (x % 2 == 0) {
            // 高4位
            color_index = (pixel_byte >> 4) & 0x0F;
        }
        else {
            // 低4位
            color_index = pixel_byte & 0x0F;
        }
        color = (palette[color_index].red << 16) |
            (palette[color_index].green << 8) |
            palette[color_index].blue;
    }
    else if (bits_per_pixel == 8) {
        // 256色图像，每个像素用 8 位表示，最大 256 种颜色
        unsigned char color_index = pixel_data[pixel_offset];

        // 从调色板中获取颜色值
        color = (palette[color_index].red << 16) | (palette[color_index].green << 8) | palette[color_index].blue;
    }
    else if (bits_per_pixel == 24) {
        // 24位色图像，每个像素用 24 位表示，RGB
        unsigned char blue = pixel_data[pixel_offset];
        unsigned char green = pixel_data[pixel_offset + 1];
        unsigned char red = pixel_data[pixel_offset + 2];

        // 返回 RGB 颜色值
        color = (red << 16) | (green << 8) | blue;
    }
    else if (bits_per_pixel == 32) {
        // 32位色图像，每个像素用 32 位表示，RGBA，忽略透明度
        unsigned char blue = pixel_data[pixel_offset];
        unsigned char green = pixel_data[pixel_offset + 1];
        unsigned char red = pixel_data[pixel_offset + 2];
        unsigned char alpha = pixel_data[pixel_offset + 3]; // Alpha 通道，忽略

        // 返回 RGB 颜色值
        color = (red << 16) | (green << 8) | blue;
    }
    else {
        // 不支持的位深度
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

            // 如果需要镜像或旋转图像，这里可以进行坐标变换
            int new_x = x;
            int new_y = y;
            switch (angle) {
                case 0:
                    new_x = is_mirror ? width - 1 - x : x;
                    new_y = height - 1 - y; // 垂直镜像调整
                    break;
                case 90:
                    new_x = is_mirror ? y : height - 1 - y; // 水平镜像调整
                    new_y = width - 1 - x;
                    break;
                case 180:
                    new_x = is_mirror ? x : width - 1 - x;
                    new_y = y; // 垂直镜像调整
                    break;
                case 270:
                    new_x = is_mirror ? height - 1 - y : y; // 水平镜像调整
                    new_y = x;
                    break;
                default:
                    cerr << "Unsupported angle: " << angle << endl;
                    return -1;
            }

            // 调用画点函数绘制像素
            draw_point(new_x + top_left_x, new_y + top_left_y, red, green, blue);
        }
    }
    return 0;
}