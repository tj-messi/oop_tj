/*2351114 朱俊泽 大数据*/
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
//#include <string.h>
using namespace std;

void Hexcout(ostream& out, const unsigned char* buffer, int size, int offset) {
    
    out << setw(8) << setfill('0') << hex << offset << "  ";

    for (int i = 0; i < size; ++i) {
        if (i > 0 && i % 8 == 0) {
            out << "- ";
        }
        out << setw(2) << setfill('0') << hex << static_cast<int>(buffer[i]) << " ";
    }

    if (size < 16) {
        for (int i = size; i < 16; ++i) {
            if (i > 0 && i % 8 == 0) {
                out << "  ";
            }
            out << "   ";
        }
    }

    out << "    ";

    for (int i = 0; i < size; ++i) {
        unsigned char ch = buffer[i];
        if (ch >= 33 && ch <= 126) {
            out << ch;
        }
        else {
            out << '.';
        }
    }

    out << endl;
}

void dealfile(const char* filename, ostream& outputStream) {
    unsigned char dataBuffer[16];
    int currentOffset = 0;
    ifstream inputFile(filename, ios::binary);
 
    if (!inputFile.is_open()) {
		cout<<"输入文件"<<filename<<"打开失败！"<<endl;
        return;
    }

    while (true) {
        inputFile.read(reinterpret_cast<char*>(dataBuffer), sizeof(dataBuffer));
        int bytesRead = inputFile.gcount();
 
        if (bytesRead == 0) {
            break;
        }
 
        Hexcout(outputStream, dataBuffer, bytesRead, currentOffset);
 
        currentOffset += bytesRead;
    }

}
void usage()
{
	cout << "Usage : 15-b1 --infile 原始文件 [ --outfile hex格式文件 ]" << endl;
	cout << "        15-b1 --infile a.docx" << endl;
	cout << "        15-b1 --infile a.docx --outfile a.hex" << endl;
}

int main(int argc, char* argv[])
{
	//const char* my_file_name = argv[0];
	const char* input_file_name = nullptr;
	const char* output_file_name = nullptr;
	
	if(argc <= 2)
	{
		usage();
		return 0;
	} 
	
	//输入正常 
	if(strcmp(argv[1],"--infile") == 0)
	{
		input_file_name = argv[2];
	}
	else
	{
		usage();
		return 0;
	}
	
	//
	if(argc == 5)
	{
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
	else if(argc == 4)
	{
		usage();
		return 0;
	}
	
	
	//打开文件
	ifstream in(input_file_name,ios::binary);
	if(!in)
	{
		cout<<"输入文件"<<input_file_name<<"打开失败！"<<endl;
		return 0;
	} 

	//输出文件
	if(output_file_name)
	{
		ofstream out(output_file_name);
		dealfile(input_file_name,out);
	}
	else
	{
		dealfile(input_file_name,cout);
	}
	
}
