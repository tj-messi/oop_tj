/* 2150792 �ƿ� ţ»�� */
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct student {
	int  *no;          //ѧ�ţ�������0��ͷ
	char *name;        //��������ĸ����֣�����Ƨ�֣���Ϊ˫�ֽں��֣�
	int  *socre;       //�ɼ���������С����
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
	/* ====== ����ͷָ��ռ� ====== */
	struct student* head = (struct student*)malloc(sizeof(struct student));       //headΪͷָ��,����ͷ���
	checkNull(head, "malloc����ռ�ʧ��");
	/* ====== ����pָ��ռ� ======*/
	struct student* p = (struct student*)malloc(sizeof(struct student));
	checkNull(p, "malloc����ռ�ʧ��");
	p = head;
	p->next = NULL;

	while (1)
	{
		int temp_no = 0, temp_score = 0;
		char temp_name[9];
		fscanf(infile, "%d %s %d", &temp_no, temp_name, &temp_score);
		if (temp_no == 9999999)
			break;
		struct student* q = (struct student*)malloc(sizeof(struct student));
		checkNull(q, "malloc����ռ�ʧ��");

		/*======��������ռ�======*/
		q->no = (int*)malloc(sizeof(int));
		checkNull(q->no, "malloc����ռ�ʧ��");
		q->socre = (int*)malloc(sizeof(int));
		checkNull(q->socre, "malloc����ռ�ʧ��");
		q->name = (char*)malloc((strlen(temp_name) + 1) * sizeof(char));
		checkNull(q->name, "malloc����ռ�ʧ��");

		*(q->no) = temp_no;
		*(q->socre) = temp_score;
		strcpy(q->name, temp_name);
		p->next = q;
		p = q;
		q->next = NULL;
	}
	
	/*======�������������Ϣ======*/
	p = head->next;
	while (p != NULL)
	{
		printf("%d %s %d\n", *(p->no), p->name, *(p->socre));
		p = p->next;
	}

	/*======������������������ͷ�malloc�ռ�======*/
	p = head->next;
	free(head);//headû�ж������룬��Ҫ�ȱ��ͷ�
	while (p != NULL)
	{
		struct student* temp = p;
		p = p->next;

		free(temp->name); // ���ͷŶ�������ĳ�Ա
		free(temp->socre);
		free(temp->no);
		free(temp);       // ���ͷ�����Ľṹ�����
	}
	fclose(infile);		 //�ر��ļ�
	return 0;
}