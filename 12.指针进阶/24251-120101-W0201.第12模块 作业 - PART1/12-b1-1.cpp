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
  说    明：相关输出都放在函数中即可
***************************************************************************/
void average(int (*score)[SCORE_NUM])
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
 
    for (ptr = &score[0][0]; ptr < &score[0][0]+SCORE_NUM*STUDENT_NUM; ptr += SCORE_NUM)
    {  
        sum += *ptr;  
    }  
 
    //sum =  1.0*(sum) / STUDENT_NUM;  
    cout  << "第1门课平均分：" <<1.0*(sum) / STUDENT_NUM << endl <<endl;

}

/***************************************************************************
  函数名称：
  功    能：找出有两门以上课程不及格的学生
  输入参数：
  返 回 值：
  说    明：相关输出都放在函数中即可
***************************************************************************/
void fail(int (*score)[SCORE_NUM])
{
    /* 函数定义语句部分：
       1、本函数中仅允许定义 2个简单变量 + 1个行指针变量 + 1个简单指针变量 */

    /* 函数执行语句部分（要求同average）*/
	int sum=0;
	int cnt;
	int* ptr;
	int (*rowptr) [5] = score;
    
    for(;rowptr-score<=3;rowptr++)
    {
    	cnt=0;
    	for(ptr=score[rowptr-score];ptr<score[rowptr-score]+SCORE_NUM;ptr++)
    	{
    		if(*ptr<60)
    			cnt++;
		}
		if(cnt>=2)
			break;
	}
 	//cout<<cnt;
 	cout<<"2门以上不及格的学生："<<endl;
	cout<<"No："<<rowptr-score+1<<" ";
 	for (ptr = &score[rowptr-score][0]; ptr < &score[rowptr-score][0]+SCORE_NUM; ptr ++)
    {  
    	cout<<*ptr<<" ";
        sum += *ptr;  
    }  
 
    //sum =  (sum) / SCORE_NUM;  
    cout   << "平均：" << 1.0* (sum) / SCORE_NUM << endl <<endl;
}

/***************************************************************************
  函数名称：
  功    能：找出平均成绩在90分以上或全部成绩在85分以上的学生
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
void good(int (*score)[SCORE_NUM])
{
    /* 函数定义语句部分：
       1、本函数中仅允许定义 2个简单变量 + 1个行指针变量 + 1个简单指针变量 */

    /* 函数执行语句部分（要求同average）*/
	int sum=0;
	int cnt;
	int* ptr;
	int (*rowptr) [5] = score;
    cout<<"平均90以上或全部85以上的学生："<<endl;
    for(;rowptr-score<=3;rowptr++)
    {
    	sum=0;
    	cnt=0;
    	for(ptr=score[rowptr-score];ptr<score[rowptr-score]+SCORE_NUM;ptr++)
    	{
    		sum+=*ptr;
    		if(*ptr>=85)
    			cnt++;
		}
		if(cnt>=5||sum>=450)
		{
			sum=0;
			cout<<"No："<<rowptr-score+1<<" ";
 			for (ptr = &score[rowptr-score][0]; ptr < &score[rowptr-score][0]+SCORE_NUM; ptr ++)
    		{  
    			cout<<*ptr<<" ";
        		sum += *ptr;  
   			}  
    		//sum =  (sum) / SCORE_NUM;  
    		cout << "平均：" << 1.0*(sum) / SCORE_NUM<< endl;
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
    int a[STUDENT_NUM][SCORE_NUM] = {
		{91, 81, 71, 61, 51},	//第1个学生的1-5门课的成绩
		{92, 82, 72, 32, 52},   //第2个学生的1-5门课的成绩
		{93, 83, 99, 80, 95},   //第3个学生的1-5门课的成绩
		{97, 85, 87, 91, 88} }; //第4个学生的1-5门课的成绩
	
	
    /* 除上面的预置数组外，本函数中仅允许定义 1个行指针变量 + 1个简单指针变量 */
    cout<<"初始信息："<<endl;
	int* ptr;
	int (*rowptr) [5] = a;
    
    for(;rowptr-a<=3;rowptr++)
    {
    	//cnt=0;
    	cout<<"No."<<rowptr-a+1<<"的1-5门课成绩：";
    	for(ptr=a[rowptr-a];ptr<a[rowptr-a]+SCORE_NUM;ptr++)
    	{
    		cout<<*ptr<<" ";
		}
		cout<<endl;
	}
	
	cout<<endl;
    /* 函数执行语句部分（要求同average）*/
	average(a);
	
	fail(a);
	
	good(a);
	
    return 0;
}
