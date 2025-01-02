/*�쿡�� 2351114 ������*/
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
//�����
struct student {
	int  *no;          //ѧ�ţ�������0��ͷ
	char *name;        //��������ĸ����֣�����Ƨ�֣���Ϊ˫�ֽں��֣�
	int  *socre;       //�ɼ���������С����
	struct student* next;
};

void checknull(void *p)
{
	if(p==NULL)
		printf("�ռ����ʧ�ܣ�\n");		
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
