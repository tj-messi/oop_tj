/*朱俊泽 2351114 大数据*/
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
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
	FILE*  stu_file; 
	stu_file = fopen("student.txt", "r");
	
	int num;
	
	fscanf(stu_file,"%d",&num);
	//printf("%d",num);--91
	
	struct student * p = (struct student*)malloc(num * sizeof(struct student));
	checknull(p);
	
	for (int i = 0; i < num; i++)
		fscanf(stu_file, "%d %s %d", &p[i].no, p[i].name, &p[i].socre);
	
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
		printf("%d %s %d %d\n", p[i].no, p[i].name, p[i].socre, p[i].rank);
	}
	
	free(p);
	fclose(stu_file);	
	
	return 0;
}
