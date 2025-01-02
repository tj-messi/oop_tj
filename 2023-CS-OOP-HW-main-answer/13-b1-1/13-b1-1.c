/* 2150792 计科 牛禄阳 */
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
struct student {
	int  no;          //学号，不考虑0开头
	char name[9];     //姓名，最长四个汉字（无生僻字，均为双字节汉字）
	int  socre;       //成绩，不考虑小数点
	int  rank;        //名次
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
	int num_stu;
	FILE* infile;									 //infile为变量名
	infile = fopen("student.txt", "r");				 //以读方式打开student.txt文件
	checkNull(infile, "打开student.txt文件失败");
	fscanf(infile, "%d", &num_stu);					                //读入学生数量
	struct student* p = (struct student*)malloc(num_stu * sizeof(struct student));		//malloc方式动态分配学生信息数组空间
	checkNull(p, "malloc分配空间失败");
	for (int i = 0; i < num_stu; i++)
		fscanf(infile, "%d %s %d", &p[i].no, p[i].name, &p[i].socre);//读入学生信息

	/*====== 冒泡法按成绩递减排序 ======*/
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
	/*====== 给结构体成员rank赋值 ======*/
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
	/*====== 冒泡法按学号递增排序 ======*/
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
	/*====== 按学号从小到大依次输出 ======*/
	for (int i = 0; i < num_stu; i++)
		printf("%d %s %d %d\n", p[i].no, p[i].name, p[i].socre, p[i].rank);

	free(p);
	fclose(infile);								     //关闭文件
	return 0;
}