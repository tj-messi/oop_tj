/* 2150792 �ƿ� ţ»�� */
#include<iostream>
#include<fstream>
using namespace std;
struct student {
	int  no;          //ѧ�ţ�������0��ͷ
	char name[9];     //��������ĸ����֣�����Ƨ�֣���Ϊ˫�ֽں��֣�
	int  socre;       //�ɼ���������С����
	int  rank;        //����
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
	in.open("student.txt", ios::in);				 //�Զ���ʽ��student.txt�ļ�
	if (!in.is_open())
	{
		cout << "��student.txt�ļ�ʧ��" << endl;
		return -1;
	}
	int num_stu;
	in >> num_stu;					                //����ѧ������
	student* p = new(nothrow) student[num_stu];	    //new��ʽ��̬����ѧ����Ϣ����ռ�
	checkNull(p, "new����ռ�ʧ��");
	for (int i = 0; i < num_stu; i++)
		in >> p[i].no >> p[i].name >> p[i].socre;
	/*====== ð�ݷ����ɼ��ݼ����� ======*/
	for (int i = 0; i < num_stu - 1; i++)
	{
		for (int j = 0; j < num_stu - i - 1; j++)
		{
			if (p[j].socre < p[j + 1].socre)
			{
				student temp = p[j];
				p[j] = p[j + 1];
				p[j + 1] = temp;
				continue;
			}
			if (p[j].socre == p[j + 1].socre)//�ɼ���ͬ��ѧ��С����ǰ��
			{
				if (p[j].no > p[j + 1].no)
				{
					student temp = p[j];
					p[j] = p[j + 1];
					p[j + 1] = temp;
				}
			}
		}
	}
	/*====== ���ṹ���Աrank��ֵ ======*/
	int temp_rank = 1, temp_score = p[0].socre;
	for (int i = 0; i < num_stu; i++)
	{
		if (p[i].socre == temp_score)
		{
			p[i].rank = temp_rank;
		}
		else
		{
			temp_rank = i + 1;
			p[i].rank = temp_rank;
			temp_score = p[i].socre;
		}
	}
	/*====== ��������С����������� ======*/
	for (int i = 0; i < num_stu; i++)
		cout << p[i].no << " " << p[i].name << " " << p[i].socre << " " << p[i].rank << endl;

	delete[]p;
	in.close();
	return 0;
}
