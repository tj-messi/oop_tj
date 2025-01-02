/* 2150792 计科 牛禄阳 */
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h> //malloc/free用
struct student {
	char name[20];
	int num;
	char sex;
	struct student* next;//指向结构体自身的指针(下个结点)
};

#define OK	1
#define ERROR	0

int linklist_create(struct student** head);//修改
int linklist_traverse(struct student* head);
int linklist_destroy(struct student* head);

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
int linklist_create(struct student** head)//修改
{
	struct student* p = NULL, * q = NULL;
	int i;

	for (i = 0; i < 5; i++) {
		if (i > 0)
			q = p;
		p = (struct student*)malloc(sizeof(struct student));
		if (p == NULL)
			return ERROR;	//注:此处未释放之前的链表节点，就借助操作系统来释放（非标用法）
		if (i == 0)
			*head = p; //head指向第1个结点  //修改
		else
			q->next = p;
		printf("请输入第%d个人的基本信息\n", i + 1);
		scanf("%s %d %c", p->name, &(p->num), &(p->sex)); //键盘输入基本信息
		p->next = NULL;
	}
	return OK;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
int linklist_traverse(struct student* head)
{
	struct student* p;

	p = head; //p复位，指向第1个结点
	while (p != NULL) { //循环进行输出
		printf("%s %d %c\n", p->name, p->num, p->sex);
		p = p->next;
	}
	return OK;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
int linklist_destroy(struct student* head)
{
	struct student* p, * q;

	p = head; //p复位，指向第1个结点
	while (p) {  //循环进行各结点释放
		q = p->next;
		free(p);
		p = q;
	}
	return OK;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
int main()
{
	struct student* head = NULL;

	if (linklist_create(&head) == OK) {//修改
		linklist_traverse(head);
		linklist_destroy(head);
	}
	else
		printf("LinkList Create failed.\n");

	return 0;
}
