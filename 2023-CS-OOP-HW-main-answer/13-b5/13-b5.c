/* 2150792 �ƿ� ţ»�� */
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h> //malloc/free��
struct student {
	char name[20];
	int num;
	char sex;
	struct student* next;//ָ��ṹ�������ָ��(�¸����)
};

#define OK	1
#define ERROR	0

int linklist_create(struct student** head);//�޸�
int linklist_traverse(struct student* head);
int linklist_destroy(struct student* head);

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
int linklist_create(struct student** head)//�޸�
{
	struct student* p = NULL, * q = NULL;
	int i;

	for (i = 0; i < 5; i++) {
		if (i > 0)
			q = p;
		p = (struct student*)malloc(sizeof(struct student));
		if (p == NULL)
			return ERROR;	//ע:�˴�δ�ͷ�֮ǰ������ڵ㣬�ͽ�������ϵͳ���ͷţ��Ǳ��÷���
		if (i == 0)
			*head = p; //headָ���1�����  //�޸�
		else
			q->next = p;
		printf("�������%d���˵Ļ�����Ϣ\n", i + 1);
		scanf("%s %d %c", p->name, &(p->num), &(p->sex)); //�������������Ϣ
		p->next = NULL;
	}
	return OK;
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
int linklist_traverse(struct student* head)
{
	struct student* p;

	p = head; //p��λ��ָ���1�����
	while (p != NULL) { //ѭ���������
		printf("%s %d %c\n", p->name, p->num, p->sex);
		p = p->next;
	}
	return OK;
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
int linklist_destroy(struct student* head)
{
	struct student* p, * q;

	p = head; //p��λ��ָ���1�����
	while (p) {  //ѭ�����и�����ͷ�
		q = p->next;
		free(p);
		p = q;
	}
	return OK;
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
int main()
{
	struct student* head = NULL;

	if (linklist_create(&head) == OK) {//�޸�
		linklist_traverse(head);
		linklist_destroy(head);
	}
	else
		printf("LinkList Create failed.\n");

	return 0;
}
