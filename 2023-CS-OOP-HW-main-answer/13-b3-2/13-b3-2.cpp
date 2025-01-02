/* 2150792 �ƿ� ţ»�� */
#include<iostream>
#include<fstream>
#include<cstring>
using namespace std;
struct student {
	int* no;          //ѧ�ţ�������0��ͷ
	char* name;        //��������ĸ����֣�����Ƨ�֣���Ϊ˫�ֽں��֣�
	int* socre;       //�ɼ���������С����
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
	p->next = NULL;

	while (1)
	{
		int temp_no = 0, temp_score = 0;
		char temp_name[9];
		in >> temp_no >> temp_name >> temp_score;
		if (temp_no == 9999999)
			break;
		student* q = new(nothrow) student;
		checkNull(q, "new����ռ�ʧ��");

		/*======��������ռ�======*/
		q->no = new(nothrow) int;
		checkNull(q->no, "new����ռ�ʧ��");
		q->socre = new(nothrow) int;
		checkNull(q->socre, "new����ռ�ʧ��");
		q->name = new(nothrow) char[strlen(temp_name) + 1];//��������ռ�
		checkNull(q->name, "new����ռ�ʧ��");

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

	/*======�������������Ϣ======*/
	p = head->next;        //ͷ���û�д洢����
	while (p != NULL)
	{
		cout << *(p->no) << " " << p->name << " " << *(p->socre) << endl;
		p = p->next;
	}

	/*======������������������ͷ�malloc�ռ�======*/
	p = head->next;
	delete head;
	while (p != NULL)
	{
		student* temp = p;
		p = p->next;
		delete[]temp->name;
		delete temp->socre;
		delete temp->no;
		delete temp; // �ͷŵ�ǰ�ڵ�
	}
	in.close();
	return 0;
}