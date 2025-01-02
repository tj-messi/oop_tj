/*�쿡�� 2351114 ������*/
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
//�����
struct student {
	int  no;          //ѧ�ţ�������0��ͷ
	char name[9];     //��������ĸ����֣�����Ƨ�֣���Ϊ˫�ֽں��֣�
	int  socre;       //�ɼ���������С����
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
		struct student* q = (struct student*)malloc(sizeof(struct student));
		checknull(q);
		fscanf(stu_list, "%d %s %d", &q->no, q->name, &q->socre);
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
	free(head);
	while(p!=NULL)
	{
		printf("%d %s %d\n", p->no, p->name, p->socre);
		struct student* temp = p;
		p = p->next;
		free(temp);
	}
	
	free(p);
	fclose(stu_list);	
	
	return 0;
}
