/*�쿡�� 2351114 ������*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h> //malloc/free��

struct student {
	char name[20];
	int num;
	char sex;
	struct student *next;//ָ��ṹ�������ָ��(�¸����)
};

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
int main()
{
	struct student *head = NULL, *p = NULL, *q = NULL;
	int i;

	for (i = 0; i < 5; i++) {
		if (i > 0)
			q = p;
		p = (struct student *)malloc(sizeof(struct student));
		if (p == NULL)
			return -1;	//ע:ע:�˴�δ�ͷ�֮ǰ������ڵ㣬�ͽ�������ϵͳ���ͷţ��Ǳ��÷���
		if (i == 0)
			head = p; //headָ���1�����
		else
			q->next = p;
		printf("�������%d���˵Ļ�����Ϣ\n", i+1);
		scanf("%s %d %c", p->name, &(p->num), &(p->sex)); //�������������Ϣ
		p->next = NULL;
	}

	p = head; //p��λ��ָ���1�����
	while (p != NULL) { //ѭ���������
		printf("%s %d %c\n", p->name, p->num, p->sex);
		p = p->next;
	}

	p = head; //p��λ��ָ���1�����
	while (p) {  //ѭ�����и�����ͷ�
		q = p->next;
		free(p);
		p = q;
	}

	return 0;
}
