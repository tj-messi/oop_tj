/* 2150792 �ƿ� ţ»�� */
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
struct student {
	int  no;          //ѧ�ţ�������0��ͷ
	char name[9];     //��������ĸ����֣�����Ƨ�֣���Ϊ˫�ֽں��֣�
	int  socre;       //�ɼ���������С����
	struct student* next;
};
void checkNull(void* ptr, const char* errormsg)
{
	if (ptr == NULL)
	{
#ifdef __cplusplus
		cout << errormsg << " �˳�����." << endl;
#else
		printf("%s �˳�����.\n", errormsg);
#endif
		exit(-1);
	}
}
int main()
{
	FILE* infile;									 //infileΪ������
	infile = fopen("list.txt", "r");				 //�Զ���ʽ��student.txt�ļ�
	checkNull(infile, "��list.txt�ļ�ʧ��");
	struct student* head = (struct student*)malloc(sizeof(struct student));       //headΪͷָ��,����ͷ���
	checkNull(head, "malloc����ռ�ʧ��");
	struct student* p = (struct student*)malloc(sizeof(struct student));
	checkNull(p, "malloc����ռ�ʧ��");
	p = head;
	p->next = NULL;
	/*======β�巨�������ڵ�======*/
	while (1)
	{
		struct student* q = (struct student*)malloc(sizeof(struct student));
		checkNull(q, "malloc����ռ�ʧ��");
		fscanf(infile, "%d %s %d", &q->no, q->name, &q->socre);
		if (q->no == 9999999)
		{
			free(q);
			break;
		}
		p->next = q;
		p = q;
		q->next = NULL;
	}

	/*======�������������Ϣ======*/
	p = head->next;                                     
	while (p != NULL)
	{
		printf("%d %s %d\n", p->no, p->name, p->socre);
		p = p->next;
	}

	/*======������������������ͷ�malloc�ռ�======*/
	p = head;
	while (p != NULL)
	{
		struct student* temp = p;
		p = p->next;
		free(temp); // �ͷŵ�ǰ�ڵ�
	}
	fclose(infile);								     //�ر��ļ�
	return 0;
}
