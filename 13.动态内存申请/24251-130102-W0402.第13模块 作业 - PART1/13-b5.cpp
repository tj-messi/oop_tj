/*朱俊泽 2351114 大数据*/
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<fstream>
#include<ctime>
#include<cstring>
#include<string.h>
using namespace std;


struct student {
	char* no;          //学号，不考虑0开头
	char* name;        //姓名，最长四个汉字（无生僻字，均为双字节汉字）
	char* school;       //成绩，不考虑小数点
};

void checknull(void *p)
{
	if(p==NULL)
		printf("空间分配失败！\n");		
}

int main()
{
	srand((unsigned int)(time(0)));
	
	ifstream in;
	in.open("stulist.txt", ios::in);
	ofstream out;
	out.open("result.txt", ios::out);
	
	int MAX_LEN = 100;
	int N,M;
	in >> N >> M;
	//cout<< N <<" "<<M<<endl;//N==652 M==19300
	
	student* all_stu_list = new(nothrow) student[M];
	checknull(all_stu_list);
	
	for(int i=0;i<M;i++)
	{
		char temp_no[MAX_LEN];
		char temp_name[MAX_LEN];
		char temp_school[MAX_LEN];
		in >> temp_no >> temp_name >> temp_school;
		
		all_stu_list[i].name = new(nothrow) char[strlen(temp_name) + 1];
		checknull(all_stu_list[i].name);
		all_stu_list[i].school = new(nothrow)char[strlen(temp_school) + 1];
		checknull(all_stu_list[i].school);
		all_stu_list[i].no = new(nothrow)char[strlen(temp_no) + 1];
		checknull(all_stu_list[i].no);
		
		strcpy(all_stu_list[i].name, temp_name);
		strcpy(all_stu_list[i].school, temp_school);
		strcpy(all_stu_list[i].no, temp_no);
	}
	
	int* rand_stu_list = new (nothrow)int[N];
	checknull(rand_stu_list);
	
	for(int i=0;i<N;i++)
	{
		int idx = rand() % M;
		bool flag = false;
		for(int j=0;j<=i;j++)
		{
			if(rand_stu_list[j]==idx)flag=true;
		}
		if(flag)//之前有相同的 
		{
			i--;
			continue;
		}
		else//之前没相同的 
		{
			rand_stu_list[i]=idx;
		}
	}
	/*
	for(int i=0;i<N;i++)
	{
		cout<<rand_stu_list[i]<<endl;
	}
	*/
	for (int i = 0; i < N; i++)
	{
		out << all_stu_list[rand_stu_list[i]].no << " "
		<< all_stu_list[rand_stu_list[i]].name << " " 
		<< all_stu_list[rand_stu_list[i]].school << endl;
	}
	
	for (int i = 0; i < N; i++)
	{
		delete[]all_stu_list[i].school;
		delete[]all_stu_list[i].name;
		delete[]all_stu_list[i].no;
	}
	delete[]all_stu_list;
	delete[]rand_stu_list;
	
	in.close();
	out.close();
	return 0;
}
