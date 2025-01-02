/*朱俊泽 2351114 大数据*/
#include<iostream>
#include<fstream>
using namespace std;
//#include<fstream> //文件操作需要的头文件 
//不许动 
//不许改
struct student {
	int  no;          //学号，不考虑0开头
	char name[9];     //姓名，最长四个汉字（无生僻字，均为双字节汉字）
	int  socre;       //成绩，不考虑小数点
	struct student* next;
};

void checknull(void *p)
{
	if(p==NULL)
		printf("空间分配失败！\n");		
}

int main()
{
	ifstream stu_list;							
	stu_list.open("list.txt", ios::in);
	
	struct student* head = new(nothrow) student;
	checknull(head);
	struct student* p = new(nothrow) student;
	checknull(p);
	
	p=head;
	p->next=NULL;
	
	while(1)
	{
		struct student* q = new(nothrow) student;
		checknull(q);
		
		stu_list >> q->no >> q->name >> q->socre;
		if(q->no== 9999999)
		{
			free(q);
			break;
		}
		else
		{
			p->next=q;
			p=q;
			q->next = NULL;
		}

	}

	p=head->next;
	while(p!=NULL)
	{
		cout<< p->no<<" " << p->name <<" "<< p->socre << endl;
		struct student* temp = p;
		p = p->next;
		free(temp);
	}
	
	delete[]p;
	//free(p);
	stu_list.close();	
	
	return 0;
}
