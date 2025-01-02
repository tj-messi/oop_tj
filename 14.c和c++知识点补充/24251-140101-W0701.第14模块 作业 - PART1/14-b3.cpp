/*�쿡�� 2351114 ������*/
#include<iostream>
#include<iomanip>
#include<cmath>
#include<string>
#include<cstring>
using namespace std;
/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
int usage(const char* const procname)
{
	cout << "Usage: " << procname << " Ҫ����ѧ��/all ƥ��ѧ��/all Դ������/all ���ƶȷ�ֵ(60-100) ���(filename/screen)" << endl << endl;
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
	if (strcmp(argv[1], "all") == 0 )//���all 
	{
		flag1_all = true;
	}
	else//����all 
	{
		int res1 = check_id(argv[1]);
		if(res1==1)
		{
			cout<<"Ҫ����ѧ�Ų���7λ"<<endl; 
			return 0;
		}
		else if(res1==2)
		{
			cout<<"Ҫ����ѧ�Ų���7λ����"<<endl; 
			return 0;
		}
	}
	
	if(strcmp(argv[2], "all") == 0)//ƥ��all 
		;
	else
	{
		if(flag1_all)
		{
			cout<<"���ѧ����all��ƥ��ѧ�ű�����all"<<endl; 
			return 0;
		}
		int res2 = check_id(argv[2]);
		if(res2==1)
		{
			cout<<"Ҫƥ���ѧ�Ų���7λ"<<endl; 
			return 0;
		}
		else if(res2==2)
		{
			cout<<"Ҫƥ���ѧ�Ų���7λ����"<<endl; 
			return 0;
		}
		
	}
	
	if(strcmp(argv[1],argv[2])==0)
	{
		cout<<"ƥ��ѧ����Ҫ���ѧ����ͬ"<<endl;
		return 0;
	}
	
	if (strlen(argv[3]) > 32)                             
	{
		cout << "Դ�����ļ���������32�ֽ�" << endl;
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
		cout << "�������ļ���������32�ֽ�" << endl;
		return 0;
	}
	
	{
		cout << "�������ͨ��" << endl;
		cout << "���ѧ�ţ�" << argv[1] << endl;
		cout << "ƥ��ѧ�ţ�" << argv[2] << endl;
		cout << "Դ�ļ�����" << argv[3] << endl;
		cout << "ƥ����ֵ��" << similarity_set << endl;
		cout << "���Ŀ�꣺" << outfile << endl;
	}
	
}
