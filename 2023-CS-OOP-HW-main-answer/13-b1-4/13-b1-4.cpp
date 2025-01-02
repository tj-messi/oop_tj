/* 2150792 计科 牛禄阳 */
#include<iostream>
#include<fstream>
using namespace std;
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
	ifstream in;									 //infile为变量名
	in.open("student.txt", ios::in);				 //以读方式打开student.txt文件
	if (!in.is_open())
	{
		cout << "打开student.txt文件失败" << endl;
		return -1;
	}
	int num_stu;
	in >> num_stu;					                //读入学生数量
	student* p = new(nothrow) student[num_stu];	    //new方式动态分配学生信息数组空间
	checkNull(p, "new分配空间失败");
	for (int i = 0; i < num_stu; i++)
		in >> p[i].no >> p[i].name >> p[i].socre;
	/*====== 冒泡法按成绩递减排序 ======*/
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
			if (p[j].socre == p[j + 1].socre)//成绩相同，学号小的在前面
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
	/*====== 给结构体成员rank赋值 ======*/
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
	/*====== 按排名从小到大依次输出 ======*/
	for (int i = 0; i < num_stu; i++)
		cout << p[i].no << " " << p[i].name << " " << p[i].socre << " " << p[i].rank << endl;

	delete[]p;
	in.close();
	return 0;
}
