/*朱俊泽 2351114 大数据*/
#include<iostream>
#include<iomanip>
#include<cmath>
#include<string>
#include<cstring>
using namespace std;
/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
int usage(const char* const procname)
{
	cout << "Usage: " << procname << " 要检查的学号/all 匹配学号/all 源程序名/all 相似度阀值(60-100) 输出(filename/screen)" << endl << endl;
	cout << "e.g. : " << procname << " 2159999 2159998 all       80 screen" << endl;
	cout << "       " << procname << " 2159999 all     14-b1.cpp 75 result.txt" << endl;
	cout << "       " << procname << " all     all     14-b2.cpp 80 check.dat" << endl;
	cout << "       " << procname << " all     all     all       85 screen" << endl;

	return 0;
}


int check_id(const char* const id)
{
	if (strlen(id) != 7)
	{
		return 1;
	}
	for (int i = 0; i < 7; i++)
	{
		if (id[i] < '0' || id[i] > '9')
		{
			return 2;
		}
	}
	return 3;
}

int main(int argc, char* argv[])
{
	if(argc<6) 
	{
		usage("14-b3-demo.exe");
		return 0;
	}
	bool flag1_all = false;
	if (strcmp(argv[1], "all") == 0 )//检查all 
	{
		flag1_all = true;
	}
	else//不是all 
	{
		int res1 = check_id(argv[1]);
		if(res1==1)
		{
			cout<<"要检查的学号不是7位"<<endl; 
			return 0;
		}
		else if(res1==2)
		{
			cout<<"要检查的学号不是7位数字"<<endl; 
			return 0;
		}
	}
	
	if(strcmp(argv[2], "all") == 0)//匹配all 
		;
	else
	{
		if(flag1_all)
		{
			cout<<"检查学号是all，匹配学号必须是all"<<endl; 
			return 0;
		}
		int res2 = check_id(argv[2]);
		if(res2==1)
		{
			cout<<"要匹配的学号不是7位"<<endl; 
			return 0;
		}
		else if(res2==2)
		{
			cout<<"要匹配的学号不是7位数字"<<endl; 
			return 0;
		}
		
	}
	
	if(strcmp(argv[1],argv[2])==0)
	{
		cout<<"匹配学号与要检查学号相同"<<endl;
		return 0;
	}
	
	if (strlen(argv[3]) > 32)                             
	{
		cout << "源程序文件名超过了32字节" << endl;
		return 0;
	}
	
	char* similarity_set = argv[4];
	if(strlen(similarity_set)==2)
	{
		if (similarity_set[0] >= '6' && similarity_set[0] <= '9')
			;
		else
		{
			similarity_set[0]='8';
			similarity_set[1]='0';
			similarity_set[2]='\0';
		}
	}
	else if(strlen(similarity_set)==3)
	{
		if (similarity_set[0] == '1' && similarity_set[1] == '0' && similarity_set[2] == '0')
			;
		else
		{
			similarity_set[0]='8';
			similarity_set[1]='0';
			similarity_set[2]='\0';
		}
	}
	else
	{
		similarity_set[0]='8';
		similarity_set[1]='0';
		similarity_set[2]='\0';
	}
	
	char* outfile = argv[5];
	if (strcmp(outfile, "screen") == 0)
		;
	else if(strlen(argv[5])>32)
	{
		cout << "输出结果文件名超过了32字节" << endl;
		return 0;
	}
	
	{
		cout << "参数检查通过" << endl;
		cout << "检查学号：" << argv[1] << endl;
		cout << "匹配学号：" << argv[2] << endl;
		cout << "源文件名：" << argv[3] << endl;
		cout << "匹配阈值：" << similarity_set << endl;
		cout << "输出目标：" << outfile << endl;
	}
	
}
