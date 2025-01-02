/*2351114 朱俊泽 大数据*/
#pragma once

//不允许加入任何头文件，特别是<Windows.h>，查到就是0分甚至是倒扣-20 ！！！

//自行查阅相关资料，了解下面这几个预编译命令的作用，看能否给你的作业带来方便！！！
//#pragma pack(show) //以警告信息的形式显示当前字节对齐的值
//#pragma pack(push) //将当前字节对齐值压入编译器栈的栈顶
//#pragma pack(push, 4) //将当前字节对齐值压入编译器栈的栈顶，然后再将4设置当前值
//#pragma pack(pop)  //将编译器栈栈顶的字节对齐值弹出并设置为当前值
//#pragma pack() //不带参数是恢复默认值

//允许定义其它需要的结构体（类）、常量、常变量等


struct color_palette
{
    unsigned char blue;
    unsigned char green;
    unsigned char red;
    unsigned char reserved_byte;
};


class bitmap {
private:
    int bmp_start_pos; // BMP数据起始位置
    int width;         // 图像宽度
    int height;        // 图像高度
    unsigned short bits_per_pixel; // 每像素位数
    int bits_per_row;  // 每行像素所占的位数
    int bytes_per_row; // 每行字节所占的大小
    char* _file_name;  // 文件名
    unsigned char* pixel_data; // 存储像素数据
    color_palette* palette; // 调色板

    unsigned int get_pixel_color(int x, int y) const; // 获取像素的颜色值

public:
    //公有部分不允许添加任何内容
    bitmap(const char* const filename);
    ~bitmap();
    int show(const int top_left_x, const int top_left_y, const int angle, const bool is_mirror,
        void (*draw_point)(const int x, const int y, const unsigned char red, const unsigned char green, const unsigned char blue)) const;
};