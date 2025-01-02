/* 2150792 计科 牛禄阳 */
#include<iostream>
#include<fstream>
using namespace std;
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
	ifstream in;									 //infile为变量名
	in.open("list.txt", ios::in);				 //以读方式打开student.txt文件
	if (!in.is_open())
	{
		cout << "打开list.txt文件失败" << endl;
		return -1;
	}
	student* head = new(nothrow) student;
	checkNull(head, "new分配空间失败");
	student* p = new(nothrow) student;
	checkNull(p, "new分配空间失败");
	p = head;
	p->next=NULL;

	/*======尾插法添加链表节点======*/
	while (1)
	{
		student* q = new(nothrow) student;
		checkNull(q, "new分配空间失败");
		in >> q->no >> q->name >> q->socre;
		if (q->no == 9999999)
		{
			delete q;
			break;
		}
		p->next = q;
		p = q;
		q->next = NULL;
	}

	/*======遍历链表输出信息======*/
	p = head->next;      //头结点没有存储数据
	while (p != NULL)
	{
		cout << p->no << " " << p->name << " " << p->socre << endl;
		p = p->next;
	}

	/*======程序结束，遍历链表释放new空间======*/
	p = head;
	while (p != NULL)
	{
		student* temp = p;
		p = p->next;
		delete temp; // 释放当前节点
	}
	in.close();
	return 0;
}