/*朱俊泽 2351114 大数据*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h> //malloc/free用

struct student {
	char name[20];
	int num;
	char sex;
	struct student *next;//指向结构体自身的指针(下个结点)
};

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
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
			return -1;	//注:注:此处未释放之前的链表节点，就借助操作系统来释放（非标用法）
		if (i == 0)
			head = p; //head指向第1个结点
		else
			q->next = p;
		printf("请输入第%d个人的基本信息\n", i+1);
		scanf("%s %d %c", p->name, &(p->num), &(p->sex)); //键盘输入基本信息
		p->next = NULL;
	}

	p = head; //p复位，指向第1个结点
	while (p != NULL) { //循环进行输出
		printf("%s %d %c\n", p->name, p->num, p->sex);
		p = p->next;
	}

	p = head; //p复位，指向第1个结点
	while (p) {  //循环进行各结点释放
		q = p->next;
		free(p);
		p = q;
	}

	return 0;
}
