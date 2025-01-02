/*朱俊泽 2351114 大数据*/
#include<iostream>
#include<fstream>
using namespace std;
//#include<fstream> //文件操作需要的头文件 
//不许动 
struct student {
	int  no;          //学号，不考虑0开头
	char name[9];     //姓名，最长四个汉字（无生僻字，均为双字节汉字）
	int  socre;       //成绩，不考虑小数点
	int  rank;        //名次
};

void checknull(void *p)
{
	if(p==NULL)
		printf("空间分配失败！\n");		
}

int main()
{
	ifstream stu_file;							
	stu_file.open("student.txt", ios::in);
	
	int num;
	
	stu_file >> num;
	//cout<<num<<endl;
	//printf("%d",num);--91
	
	struct student * p = new(nothrow) student[num];
	checknull(p);
	
	for (int i = 0; i < num; i++)
		stu_file >> p[i].no >> p[i].name >> p[i].socre;
		//fscanf(stu_file, "%d %s %d", &p[i].no, p[i].name, &p[i].socre);
	
	for (int i = 0; i < num - 1; i++)
	{
		for (int j = 0; j < num - i - 1; j++)
		{
			if (p[j].socre < p[j + 1].socre)
			{
				struct student temp = p[j];
				p[j] = p[j + 1];
				p[j + 1] = temp;
			}
		}
	}
	
	int ranknow = 1, scorenow = p[0].socre;
	for (int i = 0; i < num; i++)
	{
		if (p[i].socre == scorenow)
		{
			p[i].rank = ranknow;
		}
		else
		{
			ranknow = i + 1;
			p[i].rank = ranknow;
			scorenow = p[i].socre;
		}
	}
	
	for (int i = 0; i < num - 1; i++)
	{
		for (int j = 0; j < num- i - 1; j++)
		{
			if (p[j].no > p[j + 1].no)
			{
				struct student temp = p[j];
				p[j] = p[j + 1];
				p[j + 1] = temp;
			}
		}
	}
	
	for (int i = 0; i < num; i++)
	{
		cout << p[i].no << " " << p[i].name << " " << p[i].socre << " " << p[i].rank << endl;
	}
	
	delete[]p;
	//free(p);
	stu_file.close();	
	
	return 0;
}
