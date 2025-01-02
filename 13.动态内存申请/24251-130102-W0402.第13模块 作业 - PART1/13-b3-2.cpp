/*�쿡�� 2351114 ������*/
#include<iostream>
#include<fstream>
using namespace std;
//#include<fstream> //�ļ�������Ҫ��ͷ�ļ� 
//���� 
//�����
struct student {
	int  no;          //ѧ�ţ�������0��ͷ
	char name[9];     //��������ĸ����֣�����Ƨ�֣���Ϊ˫�ֽں��֣�
	int  socre;       //�ɼ���������С����
	struct student* next;
};

void checknull(void *p)
{
	if(p==NULL)
		printf("�ռ����ʧ�ܣ�\n");		
}

int main()
{
	ifstream stu_list;							
	stu_list.open("list.txt", ios::in);
	
	struct student* head = new(nothrow) student;
	checknull(head);
	struct student* p = new(nothrow) student;
	checknull(p);
	
	p=head;
	p->next=NULL;
	
	while(1)
	{
		struct student* q = new(nothrow) student;
		checknull(q);
		
		stu_list >> q->no >> q->name >> q->socre;
		if(q->no== 9999999)
		{
			free(q);
			break;
		}
		else
		{
			p->next=q;
			p=q;
			q->next = NULL;
		}

	}

	p=head->next;
	while(p!=NULL)
	{
		cout<< p->no<<" " << p->name <<" "<< p->socre << endl;
		struct student* temp = p;
		p = p->next;
		free(temp);
	}
	
	delete[]p;
	//free(p);
	stu_list.close();	
	
	return 0;
}
