/*�쿡�� 2351114 ������*/
#include<iostream>
#include<fstream>
using namespace std;
//#include<fstream> //�ļ�������Ҫ��ͷ�ļ� 
//���� 
struct student {
	int  no;          //ѧ�ţ�������0��ͷ
	char name[9];     //��������ĸ����֣�����Ƨ�֣���Ϊ˫�ֽں��֣�
	int  socre;       //�ɼ���������С����
	int  rank;        //����
};

void checknull(void *p)
{
	if(p==NULL)
		printf("�ռ����ʧ�ܣ�\n");		
}

int main()
{
	ifstream stu_file;							
	stu_file.open("student.txt", ios::in);
	
	int num;
	
	stu_file >> num;
	//cout<<num<<endl;
	//printf("%d",num);--91
	
	struct student * p = new(nothrow) student[num];
	checknull(p);
	
	for (int i = 0; i < num; i++)
		stu_file >> p[i].no >> p[i].name >> p[i].socre;
		//fscanf(stu_file, "%d %s %d", &p[i].no, p[i].name, &p[i].socre);
	
	for (int i = 0; i < num - 1; i++)
	{
		for (int j = 0; j < num - i - 1; j++)
		{
			if (p[j].socre < p[j + 1].socre)
			{
				struct student temp = p[j];
				p[j] = p[j + 1];
				p[j + 1] = temp;
			}
		}
	}
	
	int ranknow = 1, scorenow = p[0].socre;
	for (int i = 0; i < num; i++)
	{
		if (p[i].socre == scorenow)
		{
			p[i].rank = ranknow;
		}
		else
		{
			ranknow = i + 1;
			p[i].rank = ranknow;
			scorenow = p[i].socre;
		}
	}
	
	for (int i = 0; i < num - 1; i++)
	{
		for (int j = 0; j < num- i - 1; j++)
		{
			if (p[j].no > p[j + 1].no)
			{
				struct student temp = p[j];
				p[j] = p[j + 1];
				p[j + 1] = temp;
			}
		}
	}
	
	for (int i = 0; i < num; i++)
	{
		cout << p[i].no << " " << p[i].name << " " << p[i].socre << " " << p[i].rank << endl;
	}
	
	delete[]p;
	//free(p);
	stu_file.close();	
	
	return 0;
}
