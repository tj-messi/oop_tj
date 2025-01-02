/* 2150792 �ƿ� ţ»�� */
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
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
	int num_stu;
	FILE* infile;									 //infileΪ������
	infile = fopen("student.txt", "r");				 //�Զ���ʽ��student.txt�ļ�
	checkNull(infile, "��student.txt�ļ�ʧ��");
	fscanf(infile, "%d", &num_stu);					                //����ѧ������
	struct student* p = (struct student*)malloc(num_stu * sizeof(struct student));		//malloc��ʽ��̬����ѧ����Ϣ����ռ�
	checkNull(p, "malloc����ռ�ʧ��");
	for (int i = 0; i < num_stu; i++)
		fscanf(infile, "%d %s %d", &p[i].no, p[i].name, &p[i].socre);//����ѧ����Ϣ

	/*====== ð�ݷ����ɼ��ݼ����� ======*/
	for (int i = 0; i < num_stu - 1; i++)
	{
		for (int j = 0; j < num_stu - i - 1; j++)
		{
			if (p[j].socre < p[j + 1].socre)
			{
				struct student temp = p[j];
				p[j] = p[j + 1];
				p[j + 1] = temp;
			}
		}
	}
	/*====== ���ṹ���Աrank��ֵ ======*/
	int temp_rank = 1, temp_score = p[0].socre;
	for (int i = 0; i < num_stu; i++)
	{
		if (p[i].socre == temp_score)
			p[i].rank = temp_rank;
		else
		{
			temp_rank = i + 1;
			p[i].rank = temp_rank;
			temp_score = p[i].socre;
		}
	}
	/*====== ð�ݷ���ѧ�ŵ������� ======*/
	for (int i = 0; i < num_stu - 1; i++)
	{
		for (int j = 0; j < num_stu - i - 1; j++)
		{
			if (p[j].no > p[j + 1].no)
			{
				struct student temp = p[j];
				p[j] = p[j + 1];
				p[j + 1] = temp;
			}
		}
	}
	/*====== ��ѧ�Ŵ�С����������� ======*/
	for (int i = 0; i < num_stu; i++)
		printf("%d %s %d %d\n", p[i].no, p[i].name, p[i].socre, p[i].rank);

	free(p);
	fclose(infile);								     //�ر��ļ�
	return 0;
}