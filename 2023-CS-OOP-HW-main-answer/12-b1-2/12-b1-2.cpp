/* 2150792 计科 牛禄阳 */
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
    int* p = *score;//行指针p指向a[0]
    double sum = 0;    //简单变量记录第一门成绩的和
    for (p = *score; p < *score +STUDENT_NUM; p++)
        sum += *p;
    cout << "第1门课平均分：" << sum / STUDENT_NUM << endl;


       /* 函数执行语句部分：
          1、不允许再定义任何类型的变量，包括 for (int i=0;...）等形式定义变量
          2、循环变量必须是指针变量，后续语句中不允许出现[]形式访问数组
             不允许：int a[10], i;
                     for(i=0; i<10; i++)
                         cout << a[i];
             允许  ：int a[10], p;
                     for(p=a; p<a+10; p++)
                         cout << *p;          */



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
    double sum = 0;
    int cnt = 0;
    int(*p1)[STUDENT_NUM] = score;//定义行指针变量
    int* p2 = *score;//定义简单指针变量指向一维数组a[0]
    /* 函数执行语句部分（要求同average）*/
    cout << "2门以上不及格的学生：" << endl;
    for (p2 = *score; p2 < *score + STUDENT_NUM; p2++)//外循环遍历列
    {
        for (p1 = score; p1 < score + SCORE_NUM; p1++)//内循环遍历行
        {
            if ( *(* p1 + (p2 - *score)) < 60)
                ++cnt;
            sum += *(*p1 + (p2 - *score));
        }
        if (cnt >= 2)
        {
            cout << "No：" << p2 - *score + 1 << " ";
            for (p1 = score; p1 < score + SCORE_NUM; p1++)
                cout << *(*p1 + (p2 - *score)) << " ";
            cout << "平均：" << sum / SCORE_NUM << endl;
        }
        cnt = 0;
        sum = 0;
    }
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

    double sum = 0;
    int cnt = 0;
    int(*p1)[STUDENT_NUM] = score;//定义行指针变量
    int* p2 = *score;//定义简单指针变量指向一维数组a[0]
    /* 函数执行语句部分（要求同average）*/
    cout << "平均90以上或全部85以上的学生：" << endl;
    for (p2 = *score; p2 < *score + STUDENT_NUM; p2++)//外循环遍历列
    {
        for (p1 = score; p1 < score + SCORE_NUM; p1++)//内循环遍历行
        {
            if (*(*p1 + (p2 - *score)) >= 85)
                ++cnt;
            sum += *(*p1 + (p2 - *score));
        }
        if (cnt == SCORE_NUM || sum / SCORE_NUM >= 90)
        {
            cout << "No：" << p2 - *score + 1 << " ";
            for (p1 = score; p1 < score + SCORE_NUM; p1++)
                cout << *(*p1 + (p2 - *score)) << " ";
            cout << "平均：" << sum / SCORE_NUM << endl;
        }
        cnt = 0;
        sum = 0;
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
    int (*p1)[STUDENT_NUM] = a;//行指针变量
    int* p2 = *a;//简单指针变量
    cout << "初始信息：" << endl;
    for (p1 = a; p1 < a + SCORE_NUM; p1++)
    {
        cout << "No.1-4学生的第" << p1 - a + 1 << "门课的成绩：";
        for (p2 = *p1; p2 < *p1 + STUDENT_NUM; p2++)
            cout << *p2 << " ";
        cout << endl;
    }
    cout << endl;
    /* 函数执行语句部分（要求同average）*/
    p1 = a;
    p2 = *a;
    average(p1);
    cout << endl;
    fail(p1);
    cout << endl;
    good(p1);

    return 0;
}
