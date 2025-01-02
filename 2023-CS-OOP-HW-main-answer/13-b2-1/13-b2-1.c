/* 2150792 计科 牛禄阳 */
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
struct student {
	int  no;          //学号，不考虑0开头
	char name[9];     //姓名，最长四个汉字（无生僻字，均为双字节汉字）
	int  socre;       //成绩，不考虑小数点
	struct student* next;
};
void checkNull(void* ptr, const char* errormsg)
{
	if (ptr == NULL)
	{
#ifdef __cplusplus
		cout << errormsg << " 退出进程." << endl;
#else
		printf("%s 退出进程.\n", errormsg);
#endif
		exit(-1);
	}
}
int main()
{
	FILE* infile;									 //infile为变量名
	infile = fopen("list.txt", "r");				 //以读方式打开student.txt文件
	checkNull(infile, "打开list.txt文件失败");
	struct student* head = (struct student*)malloc(sizeof(struct student));       //head为头指针,存在头结点
	checkNull(head, "malloc分配空间失败");
	struct student* p = (struct student*)malloc(sizeof(struct student));
	checkNull(p, "malloc分配空间失败");
	p = head;
	p->next = NULL;
	/*======尾插法添加链表节点======*/
	while (1)
	{
		struct student* q = (struct student*)malloc(sizeof(struct student));
		checkNull(q, "malloc分配空间失败");
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

	/*======遍历链表输出信息======*/
	p = head->next;                                     
	while (p != NULL)
	{
		printf("%d %s %d\n", p->no, p->name, p->socre);
		p = p->next;
	}

	/*======程序结束，遍历链表释放malloc空间======*/
	p = head;
	while (p != NULL)
	{
		struct student* temp = p;
		p = p->next;
		free(temp); // 释放当前节点
	}
	fclose(infile);								     //关闭文件
	return 0;
}
