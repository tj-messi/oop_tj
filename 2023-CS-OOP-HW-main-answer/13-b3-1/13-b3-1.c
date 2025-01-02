/* 2150792 计科 牛禄阳 */
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct student {
	int  *no;          //学号，不考虑0开头
	char *name;        //姓名，最长四个汉字（无生僻字，均为双字节汉字）
	int  *socre;       //成绩，不考虑小数点
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
	/* ====== 分配头指针空间 ====== */
	struct student* head = (struct student*)malloc(sizeof(struct student));       //head为头指针,存在头结点
	checkNull(head, "malloc分配空间失败");
	/* ====== 分配p指针空间 ======*/
	struct student* p = (struct student*)malloc(sizeof(struct student));
	checkNull(p, "malloc分配空间失败");
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
		checkNull(q, "malloc分配空间失败");

		/*======二次申请空间======*/
		q->no = (int*)malloc(sizeof(int));
		checkNull(q->no, "malloc分配空间失败");
		q->socre = (int*)malloc(sizeof(int));
		checkNull(q->socre, "malloc分配空间失败");
		q->name = (char*)malloc((strlen(temp_name) + 1) * sizeof(char));
		checkNull(q->name, "malloc分配空间失败");

		*(q->no) = temp_no;
		*(q->socre) = temp_score;
		strcpy(q->name, temp_name);
		p->next = q;
		p = q;
		q->next = NULL;
	}
	
	/*======遍历链表输出信息======*/
	p = head->next;
	while (p != NULL)
	{
		printf("%d %s %d\n", *(p->no), p->name, *(p->socre));
		p = p->next;
	}

	/*======程序结束，遍历链表释放malloc空间======*/
	p = head->next;
	free(head);//head没有二次申请，需要先被释放
	while (p != NULL)
	{
		struct student* temp = p;
		p = p->next;

		free(temp->name); // 先释放二次申请的成员
		free(temp->socre);
		free(temp->no);
		free(temp);       // 再释放申请的结构体变量
	}
	fclose(infile);		 //关闭文件
	return 0;
}