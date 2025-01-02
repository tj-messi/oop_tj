/*2351114 �쿡�� ������*/
/*2353597 ��ѩ� 2351577 ��巺� 2353259 ������ 2251174 ������ 2252109 ������*/ 
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
#include <cctype>
//#include <string.h>
using namespace std;

// ������ʮ�������ַ�ת��Ϊһ���ֽ�
unsigned char convertHexPairToByte(const char* hexPair) 
{
    unsigned char result = 0;
    for (int i = 0; i < 2; ++i) {
        result <<= 4; // ����4λΪ��һ��ʮ�����������ڳ��ռ�
        char currentChar = hexPair[i];
        if (isdigit(currentChar))
		{
            result |= currentChar - '0'; // �����ַ�ת��Ϊ��Ӧ����ֵ
        } 
		else 
		{
            result |= tolower(currentChar) - 'a' + 10; // ��ĸ�ַ�ת��Ϊ��Ӧ��ʮ������ֵ
        }
    }
    return result;
}

void hex_to_bin(const char* input_file_name, const char* output_file_name)
{
	ifstream in(input_file_name,ios::binary);
	if(!in)
	{
		cout<<"�����ļ�"<<input_file_name<<"��ʧ�ܣ�"<<endl;
		return;
	} 
	
	ofstream out(output_file_name,ios::binary);
	
	char lineBuffer[100];
    while (in.getline(lineBuffer, sizeof(lineBuffer))) {
        size_t lineLength = strlen(lineBuffer);
        if (lineLength < 10)
		{
            continue; // ��������
        }
 
        for (size_t i = 10; i < 58 && i < lineLength;i++) {
            // �����ո�Ͷ̺���
            if (lineBuffer[i] == ' ' || lineBuffer[i] == '-') 
			{
                continue;
            }
 
            // ��鵱ǰλ�ü������ַ��Ƿ�Ϊʮ����������
            if (isxdigit(lineBuffer[i]) && isxdigit(lineBuffer[i + 1])) {
                unsigned char byte = convertHexPairToByte(&lineBuffer[i]);
                out.write(reinterpret_cast<const char*>(&byte), sizeof(byte));
                i ++ ; // �ƶ�����һ��ʮ�����ƶ�
            } else {
                break; // �������ʮ�����ƶԣ���ֹͣ����ǰ��
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
	
	//�������� 
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
	
	//���ļ�
	ifstream in(input_file_name,ios::binary);
	if(!in)
	{
		cout<<"�����ļ�"<<input_file_name<<"��ʧ�ܣ�"<<endl;
		return 0;
	} 

	//����ļ�
	hex_to_bin(input_file_name,output_file_name);
	
}
