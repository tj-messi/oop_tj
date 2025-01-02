/*朱俊泽 2351114 大数据*/
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<fstream>
#include<string.h>
using namespace std;
struct student {
	int* no;          //学号，不考虑0开头
	char* name;        //姓名，最长四个汉字（无生僻字，均为双字节汉字）
	int* socre;       //成绩，不考虑小数点
	struct student* next;
};

void checknull(void *p)
{
	if(p==NULL)
		printf("空间分配失败！\n");		
} 

int main()
{
	ifstream  stu_list; 
	stu_list.open("list.txt", ios::in);
	
	struct student* head = new(nothrow) student;
	checknull(head);
	struct student* p = new(nothrow) student;
	checknull(p);
	
	p=head;
	p->next=NULL;
	
	while(1)
	{	
		int temp_no = 0;
		int temp_score = 0;
		char temp_name[9];
		stu_list >> temp_no >> temp_name >> temp_score;
			
		if(temp_no== 9999999)
		{
			//free(q);
			break;
		}
		else
		{	
			struct student* q =  new(nothrow) student;
			checknull(q);
			q->no = new(nothrow) int;
			checknull(q->no);
			q->socre = new(nothrow) int;
			checknull(q->socre);
			q->name = new(nothrow) char[strlen(temp_name) + 1];
			checknull(q->name);
			
			*(q->no) = temp_no;
			*(q->socre) = temp_score;
			strcpy(q->name, temp_name);
			
			p->next=q;
			p=q;
			q->next = NULL;
		}

	}

	p=head->next;
	free(head);
	while(p!=NULL)
	{
		printf("%d %s %d\n", *(p->no), p->name, *(p->socre));
		struct student* temp = p;
		delete[]temp->name;
		delete temp->socre;
		delete temp->no;
		p = p->next;
		delete temp; 
	}
	
	//free(p);
	delete p;
	stu_list.close();	
	
	return 0;
}
