/*2351114 朱俊泽 大数据*/
#include <iostream>
#include <iomanip>
using namespace std;

#define STUDENT_NUM	4
#define SCORE_NUM	5

/* --- 不允许定义任何形式的全局变量 --- */

/***************************************************************************
  函数名称：
  功    能：求第一门课的平均分
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
void average(int(*score)[STUDENT_NUM])
{
	/* 函数定义语句部分：
	   1、本函数中仅允许定义 1个简单变量 + 1个指针变量 */

	   /* 函数执行语句部分：
		  1、不允许再定义任何类型的变量，包括 for (int i=0;...）等形式定义变量
		  2、循环变量必须是指针变量，后续语句中不允许出现[]形式访问数组
			 不允许：int a[10], i;
					 for(i=0; i<10; i++)
						 cout << a[i];
			 允许  ：int a[10], p;
					 for(p=a; p<a+10; p++)
						 cout << *p;          */

	int sum = 0;
	int* ptr;

	for (ptr = &score[0][0]; ptr < &score[0][0] + STUDENT_NUM; ptr++)
	{
		sum += *ptr;
	}

	//sum =  1.0*(sum) / STUDENT_NUM;  
	cout << "第1门课平均分：" << 1.0 * (sum) / STUDENT_NUM << endl << endl;

}

/***************************************************************************
  函数名称：
  功    能：找出有两门以上课程不及格的学生
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
void fail(int(*score)[STUDENT_NUM])
{
	/* 函数定义语句部分：
	   1、本函数中仅允许定义 3个简单变量 + 1个行指针变量 + 1个简单指针变量 */

	   /* 函数执行语句部分（要求同average）*/
	int sum = 0;
	int idx = 0;
	int cnt;
	int* ptr;
	//int(*rowptr)[4] = score;

	for (; idx <= 3; idx++)
	{
		 cnt = 0;
		for (ptr = score[0] + idx; ptr < &score[0][0] + SCORE_NUM * STUDENT_NUM; ptr += STUDENT_NUM)
		{
			if (*ptr < 60)
				cnt++;
		}
		if (cnt >= 2)
			break;
	}

	cout << "2门以上不及格的学生：" << endl;
	cout << "No：" << idx + 1 << " ";

	for (ptr = score[0] + idx; ptr < &score[0][0] + SCORE_NUM * STUDENT_NUM; ptr += STUDENT_NUM)
	{
		sum += *ptr;
		cout << *ptr << " ";
	}
	cout << "平均：" << 1.0 * (sum) / SCORE_NUM << endl << endl;
}

/***************************************************************************
  函数名称：
  功    能：找出平均成绩在90分以上或全部成绩在85分以上的学生
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
void good(int(*score)[STUDENT_NUM])
{
	/* 函数定义语句部分：
	   1、本函数中仅允许定义 3个简单变量 + 1个行指针变量 + 1个简单指针变量 */

	   /* 函数执行语句部分（要求同average）*/

	int sum = 0;
	int idx = 0;
	int cnt;
	int* ptr;
	//int(*rowptr)[4] = score;
	cout << "平均90以上或全部85以上的学生：" << endl;
	for (; idx <= 3; idx++)
	{
		cnt = 0;
		sum = 0;
		for (ptr = score[0] + idx; ptr < &score[0][0] + SCORE_NUM * STUDENT_NUM; ptr += STUDENT_NUM)
		{
			sum += *ptr;
			if (*ptr >= 60)
				cnt++;
		}
		if (cnt >= 5 || sum >= 450)
		{
			sum = 0;
			cout << "No：" << idx + 1 << " ";
			for (ptr = score[0] + idx; ptr <= &score[0][0] + SCORE_NUM * STUDENT_NUM; ptr += STUDENT_NUM)
			{
				sum += *ptr;
				cout << *ptr << " ";
			}
			cout << "平均：" << 1.0 * (sum) / SCORE_NUM << endl;
		}
	}
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
int main()
{
	int a[SCORE_NUM][STUDENT_NUM] = {
		{91,92,93,97},  //第1-4个学生的第1门课成绩
		{81,82,83,85},  //第1-4个学生的第2门课成绩
		{71,72,99,87},  //第1-4个学生的第3门课成绩
		{61,32,80,91},  //第1-4个学生的第4门课成绩
		{51,52,95,88} };//第1-4个学生的第5门课成绩
	/* 除上面的预置数组外，本函数中仅允许定义 1个行指针变量 + 1个简单指针变量 */
	cout << "初始信息：" << endl;
	int* ptr;
	int(*rowptr)[4] = a;

	for (; rowptr - a <= 4; rowptr++)
	{
		//cnt=0;
		cout << "No.1-4学生的第" << rowptr - a + 1 << "门课成绩：";
		for (ptr = a[rowptr - a]; ptr < a[rowptr - a] + STUDENT_NUM; ptr++)
		{
			cout << *ptr << " ";
		}
		cout << endl;
	}

	cout << endl;
	/* 函数执行语句部分（要求同average）*/

	average(a);

	fail(a);

	good(a);

	return 0;
}
