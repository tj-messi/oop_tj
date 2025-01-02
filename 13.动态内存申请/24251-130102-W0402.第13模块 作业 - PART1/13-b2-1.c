/*�쿡�� 2351114 ������*/
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
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
	FILE*  stu_file; 
	stu_file = fopen("student.txt", "r");
	
	int num;
	
	fscanf(stu_file,"%d",&num);
	//printf("%d",num);--91
	
	struct student * p = (struct student*)malloc(num * sizeof(struct student));
	checknull(p);
	
	for (int i = 0; i < num; i++)
		fscanf(stu_file, "%d %s %d", &p[i].no, p[i].name, &p[i].socre);
	
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
		printf("%d %s %d %d\n", p[i].no, p[i].name, p[i].socre, p[i].rank);
	}
	
	free(p);
	fclose(stu_file);	
	
	return 0;
}
