/*2351114 �쿡�� ������*/
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
#include <cctype>
//#include <string.h>
using namespace std;

int checkformat(const char* input_file_name)
{
	ifstream in(input_file_name,ios::binary);
	if(!in)
	{
		//cout<<"�����ļ�"<<input_file_name<<"��ʧ�ܣ�"<<endl;
		return 3;
	} 
	
	bool rn = false;
	bool n = false;
	char nowch;
	while(in.get(nowch))
	{
		if(nowch == '\r')
		{
			if(in.get(nowch))
			{
				if(nowch == '\n')
					rn=true;
				else
					return 3;
			}
			else
			{
				return 3;
			}
		}
		else if(nowch == '\n')
		{
			n = true;
		}
	}
	
	//return 1;
	
	if(rn&&n)
		return 3;
	else if(rn)
		return 1;
	else if(n)
		return 2;
	else	
		return 3;
} 

void convert(int op,const char* input_file_name, const char* output_file_name)
{
	ifstream in(input_file_name,ios::binary);
	if(!in)
	{
		//cout<<"�����ļ�"<<input_file_name<<"��ʧ�ܣ�"<<endl;
		return;
	} 
	ofstream out(output_file_name, ios::binary);
	
	char nowch;
	int cnt = 0;
	if(op==1)//תlinux 
	{
		while (in.get(nowch))
		{
   			if (nowch == '\r') 
			{
        		if (in.get(nowch) && nowch == '\n')
				{
            		out.put('\n');
            		cnt++; 
        		}
    		}
    		else
			{
        		out.put(nowch);
    		}
		}
		cout<<"ת����ɣ�ȥ��"<<cnt<<"��0x0D"<<endl;		
	}
	if(op==2)//תwindowss 
	{
		while (in.get(nowch)) 
		{
   			if (nowch == '\n') 
			{
        		out.put('\r');
        		out.put('\n');
        		cnt++;
    		}
    		else 
			{
        		out.put(nowch);
    		}
		}
		cout<<"ת����ɣ�����"<<cnt<<"��0x0D"<<endl;
	}
}

void usage()
{
	//	"Usage: 15-b2 --infile b.hex --outfile a.txt" 
	/* 
	Usage : 15-b3-demo.exe --check �ļ��� | --convert { wtol|ltow } Դ�ļ��� Ŀ���ļ���
        15-b3-demo.exe --check a.txt
        15-b3-demo.exe --convert wtol a.win.txt a.linux.txt
        15-b3-demo.exe --convert ltow a.linux.txt a.win.txt
    */
	cout << "Usage : 15-b3.exe --check �ļ��� | --convert { wtol|ltow } Դ�ļ��� Ŀ���ļ���" << endl;
	cout << "        15-b3.exe --check a.txt" << endl;
	cout << "        15-b3.exe --convert wtol a.win.txt a.linux.txt" << endl;
	cout << "        15-b3.exe --convert ltow a.linux.txt a.win.txt" << endl;
}

int main(int argc,char* argv[])
{
	//const char* my_file_name = argv[0];
	const char* input_file_name = nullptr;
	const char* output_file_name = nullptr;
	if(argc==3)
	{
		if(strcmp(argv[1],"--check") == 0)
		{
			input_file_name = argv[2];
			int op = checkformat(input_file_name);
			//�����ʽ��� 
			switch(op)
			{
				case 1:
					cout<<"Windows��ʽ"<<endl;
					break;
				case 2:
					cout<<"Linux��ʽ"<<endl;
					break;
				case 3:
					cout<<"�ļ���ʽ�޷�ʶ��"<<endl;
					break;
				default:
					cout<<"�ļ���ʽ�޷�ʶ��"<<endl;
					break;				
			}
		}
		else
		{
			usage();
			return 0;
		}
	}
	else if(argc==5)
	{	
		input_file_name = argv[3];
		output_file_name = argv[4];	
		if(strcmp(argv[1],"--convert") == 0)
		{
			if(strcmp(argv[2],"wtol") == 0)//תlinux 
			{
				if(checkformat(input_file_name) != 1)
				{
					cout<<"�ļ���ʽ�޷�ʶ��"<<endl;
					return 0;
				}
				convert(1,input_file_name,output_file_name);
			}
			else if(strcmp(argv[2],"ltow") == 0)//תwindows 
			{
				if(checkformat(input_file_name) != 2)
				{
					cout<<"�ļ���ʽ�޷�ʶ��"<<endl;
					return 0;
				}
				convert(2,input_file_name,output_file_name);
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
		
	}
	else
	{
		usage();
		return 0;
	}
}
