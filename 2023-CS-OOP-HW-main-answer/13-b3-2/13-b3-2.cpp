/* 2150792 计科 牛禄阳 */
#include<iostream>
#include<fstream>
#include<cstring>
using namespace std;
struct student {
	int* no;          //学号，不考虑0开头
	char* name;        //姓名，最长四个汉字（无生僻字，均为双字节汉字）
	int* socre;       //成绩，不考虑小数点
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
	p->next = NULL;

	while (1)
	{
		int temp_no = 0, temp_score = 0;
		char temp_name[9];
		in >> temp_no >> temp_name >> temp_score;
		if (temp_no == 9999999)
			break;
		student* q = new(nothrow) student;
		checkNull(q, "new分配空间失败");

		/*======二次申请空间======*/
		q->no = new(nothrow) int;
		checkNull(q->no, "new分配空间失败");
		q->socre = new(nothrow) int;
		checkNull(q->socre, "new分配空间失败");
		q->name = new(nothrow) char[strlen(temp_name) + 1];//二次申请空间
		checkNull(q->name, "new分配空间失败");

		*(q->no) = temp_no;
		*(q->socre) = temp_score;
		for (int i = 0;; i++)
		{
			(q->name)[i] = temp_name[i];
			if (temp_name[i] == '\0')
				break;
		}
		p->next = q;
		p = q;
		q->next = NULL;
	}

	/*======遍历链表输出信息======*/
	p = head->next;        //头结点没有存储数据
	while (p != NULL)
	{
		cout << *(p->no) << " " << p->name << " " << *(p->socre) << endl;
		p = p->next;
	}

	/*======程序结束，遍历链表释放malloc空间======*/
	p = head->next;
	delete head;
	while (p != NULL)
	{
		student* temp = p;
		p = p->next;
		delete[]temp->name;
		delete temp->socre;
		delete temp->no;
		delete temp; // 释放当前节点
	}
	in.close();
	return 0;
}