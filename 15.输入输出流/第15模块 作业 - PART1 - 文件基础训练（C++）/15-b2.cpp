/*2351114 朱俊泽 大数据*/
/*2353597 王雪宸 2351577 张宸浩 2353259 梁家瑞 2251174 付沐鑫 2252109 段威呈*/ 
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
#include <cctype>
//#include <string.h>
using namespace std;

// 将两个十六进制字符转换为一个字节
unsigned char convertHexPairToByte(const char* hexPair) 
{
    unsigned char result = 0;
    for (int i = 0; i < 2; ++i) {
        result <<= 4; // 左移4位为下一个十六进制数字腾出空间
        char currentChar = hexPair[i];
        if (isdigit(currentChar))
		{
            result |= currentChar - '0'; // 数字字符转换为对应的数值
        } 
		else 
		{
            result |= tolower(currentChar) - 'a' + 10; // 字母字符转换为对应的十六进制值
        }
    }
    return result;
}

void hex_to_bin(const char* input_file_name, const char* output_file_name)
{
	ifstream in(input_file_name,ios::binary);
	if(!in)
	{
		cout<<"输入文件"<<input_file_name<<"打开失败！"<<endl;
		return;
	} 
	
	ofstream out(output_file_name,ios::binary);
	
	char lineBuffer[100];
    while (in.getline(lineBuffer, sizeof(lineBuffer))) {
        size_t lineLength = strlen(lineBuffer);
        if (lineLength < 10)
		{
            continue; // 跳过短行
        }
 
        for (size_t i = 10; i < 58 && i < lineLength;i++) {
            // 跳过空格和短横线
            if (lineBuffer[i] == ' ' || lineBuffer[i] == '-') 
			{
                continue;
            }
 
            // 检查当前位置及其后的字符是否为十六进制数字
            if (isxdigit(lineBuffer[i]) && isxdigit(lineBuffer[i + 1])) {
                unsigned char byte = convertHexPairToByte(&lineBuffer[i]);
                out.write(reinterpret_cast<const char*>(&byte), sizeof(byte));
                i ++ ; // 移动到下一个十六进制对
            } else {
                break; // 如果不是十六进制对，则停止处理当前行
            }
        }
    }
	
}

void usage()
{
	//	"Usage: 15-b2 --infile b.hex --outfile a.txt" 
	cout << "Usage : 15-b2 --infile b.hex --outfile a.txt" << endl;
	cout << "        15-b2 --outfile a.txt --infile b.hex" << endl;
}

int main(int argc, char* argv[])
{
	//const char* my_file_name = argv[0];
	const char* input_file_name = nullptr;
	const char* output_file_name = nullptr;
	
	if(argc != 5)
	{
		usage();
		return 0;
	} 
	
	//输入正常 
	if(strcmp(argv[1],"--infile") == 0)
	{
		input_file_name = argv[2];
		if(strcmp(argv[3],"--outfile")==0)
		{
			output_file_name = argv[4];
		}
		else
		{
			usage();
			return 0;
		}
	}
	else if(strcmp(argv[3],"--infile")==0)
	{
		input_file_name = argv[4];
		if(strcmp(argv[1],"--outfile")==0)
		{
			output_file_name = argv[2];
		}
		else
		{
			usage();
			return 0;
		}
	}
	else
	{
		usage();
		return 0;
	}
	
	//
	
	//打开文件
	ifstream in(input_file_name,ios::binary);
	if(!in)
	{
		cout<<"输入文件"<<input_file_name<<"打开失败！"<<endl;
		return 0;
	} 

	//输出文件
	hex_to_bin(input_file_name,output_file_name);
	
}
