/* 2150792 �ƿ� ţ»�� */
#include<iostream>
#include<fstream>
using namespace std;
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
	ifstream in;									 //infileΪ������
	in.open("list.txt", ios::in);				 //�Զ���ʽ��student.txt�ļ�
	if (!in.is_open())
	{
		cout << "��list.txt�ļ�ʧ��" << endl;
		return -1;
	}
	student* head = new(nothrow) student;
	checkNull(head, "new����ռ�ʧ��");
	student* p = new(nothrow) student;
	checkNull(p, "new����ռ�ʧ��");
	p = head;
	p->next=NULL;

	/*======β�巨�������ڵ�======*/
	while (1)
	{
		student* q = new(nothrow) student;
		checkNull(q, "new����ռ�ʧ��");
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

	/*======�������������Ϣ======*/
	p = head->next;      //ͷ���û�д洢����
	while (p != NULL)
	{
		cout << p->no << " " << p->name << " " << p->socre << endl;
		p = p->next;
	}

	/*======������������������ͷ�new�ռ�======*/
	p = head;
	while (p != NULL)
	{
		student* temp = p;
		p = p->next;
		delete temp; // �ͷŵ�ǰ�ڵ�
	}
	in.close();
	return 0;
}