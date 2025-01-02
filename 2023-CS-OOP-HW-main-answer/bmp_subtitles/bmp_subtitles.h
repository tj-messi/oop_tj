/* 2150792 计科 牛禄阳 */
#pragma once
#include <iostream>
#include <string>
#include <fstream>
using namespace std;
/* 常变量以及枚举定义 */
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
文件头：14字节
0 - 1  ：文件类型，固定为BM，无需读取
2 - 5: ：文件大小，需要读入
6 - 9  ：保留位，固定为0，无需读取
a - d  ：偏移量，文件头到位图数据的偏移，需要读取

位图信息头：
e  - 11  ：信息头的大小，固定为40，无需读取
12 - 15  ：图像的宽度，需要读取
16 - 19  ：图像的高度，需要读取，正数说明图像是倒向
1a - 1b  ：颜色平面数，固定为1，无需读取
1c - 1d  ：每个像素的bit数，需要读取，值一般为1/4/8/24等，对应单色位图/16色位图/256色位图/24位位图
1e - 2d  ：定义的其他数据，均无需读取
2e - 31  ：使用的颜色索引数，需要读取
32 - 35  ：重要的颜色索引数，无需读取

调色板：
调色板其实是一张映射表，标识颜色索引号与其代表的颜色的对应关系。
它在文件中的布局就像一个二维数组palette[N][4],其中N表示总的颜色索引数，
每行的四个元素分别表示该索引对应的B、G、R和Alpha的值，每个分量占一个字节。
如不设透明通道时，Alpha为0。
因为前面知道，本图有256个颜色索引，因此N = 256。
索引号就是所在行的行号，对应的颜色就是所在行的四个元素。

位图数据：
每个像素占一个字节，取得这个字节后，以该字节为索引查询相应的颜色
显示到相应的显示设备上

当然，如果不想使用seekg，可以直接禁止结构体对齐。
然后仿照Windows下bmp文件格式进行结构体的定义，一个是14字节，另一个40字节。

*/
class bitmap_image
{
protected:
    /* 根据需要加入自己的定义 */
    int filesize;            // 文件头2-5字节，说明文件的大小
    int b_width;
    int b_height;
    short biBitCount;        // 每个像素点的bit数 
    int  biClrUsed;          // 颜色个数
    unsigned long bfoffBits; // 文件头到位图数据的偏移
    unsigned char* bmp_data; // 位图数据
    unsigned char(*color_board)[4];      // 调色板,每行的四个元素分别表示该索引对应的B、G、R和Alpha的值
public:
    int width() const;	//返回图片的宽度
    int height() const; //返回图片的高度
    short get_biBitCount() const;
    unsigned int get_pixel(int row, int col) const; //返回指定点的RGB颜色
    /* 根据需要加入自己的定义 */
    bitmap_image(const char* filename);   // 构造函数,filename是inbmp的名称
    bool update_bmpfile(const char* filename); // 将更新后的类信息写回bmp文件
    ~bitmap_image();
    void add_Ch_subtitles(ifstream& Chdotfile, const unsigned char Ch_encoding[2], const int posx, const int posy, const unsigned char rgb[3]);
};

/* 用到的其他函数的声明 */
unsigned char hexToChar(const string& hexStr);
bool isValidRGBColor(const string& hexColor, unsigned char rgb[3]);
void Ch_to_dotmartix(ifstream& Chdotfile, int(*dotmatrix)[CHDOT_WIDTH], const unsigned char Ch_encoding[2]);
bool copyFile(const string& sourceFile, const string& destinationFile);
