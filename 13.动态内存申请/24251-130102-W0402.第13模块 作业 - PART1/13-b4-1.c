/*朱俊泽 2351114 大数据*/
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
//不许改
struct student {
	int  *no;          //学号，不考虑0开头
	char *name;        //姓名，最长四个汉字（无生僻字，均为双字节汉字）
	int  *socre;       //成绩，不考虑小数点
	struct student* next;
};

void checknull(void *p)
{
	if(p==NULL)
		printf("空间分配失败！\n");		
} 

int main()
{
	FILE*  stu_list; 
	stu_list = fopen("list.txt", "r");
	
	struct student* head = (struct student*)malloc(sizeof(struct student));
	checknull(head);
	struct student* p = (struct student*)malloc(sizeof(struct student));
	checknull(p);
	
	p=head;
	p->next=NULL;
	
	while(1)
	{	
		int temp_no = 0;
		int temp_score = 0;
		char temp_name[9];
		fscanf(stu_list, "%d %s %d", &temp_no, temp_name, &temp_score);
			
		if(temp_no== 9999999)
		{
			//free(q);
			break;
		}
		else
		{	
			struct student* q = (struct student*)malloc(sizeof(struct student));
			checknull(q);
			q->no = (int*)malloc(sizeof(int));
			checknull(q->no);
			q->socre = (int*)malloc(sizeof(int));
			checknull(q->socre);
			q->name = (char*)malloc((strlen(temp_name) + 1) * sizeof(char));
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
		free(temp->name);
		free(temp->socre);
		free(temp->no);
		p = p->next;
		free(temp);
	}
	
	free(p);
	fclose(stu_list);	
	
	return 0;
}
