/*2351114 �쿡�� ������*/
#include <iostream>
#include <iomanip>
using namespace std;

#define STUDENT_NUM	4
#define SCORE_NUM	5

/* --- ���������κ���ʽ��ȫ�ֱ��� --- */

/***************************************************************************
  �������ƣ�
  ��    �ܣ����һ�ſε�ƽ����
  ���������
  �� �� ֵ��
  ˵    ���������������ں����м���
***************************************************************************/
void average(int (*score)[SCORE_NUM])
{
    /* ����������䲿�֣�
       1���������н������� 1���򵥱��� + 1��ָ����� */

    /* ����ִ����䲿�֣�
       1���������ٶ����κ����͵ı��������� for (int i=0;...������ʽ�������
       2��ѭ������������ָ���������������в��������[]��ʽ��������
          ������int a[10], i;
                  for(i=0; i<10; i++)
                      cout << a[i];
          ����  ��int a[10], p;
                  for(p=a; p<a+10; p++)
                      cout << *p;          */
	int sum = 0;  
    int* ptr;
 
    for (ptr = &score[0][0]; ptr < &score[0][0]+SCORE_NUM*STUDENT_NUM; ptr += SCORE_NUM)
    {  
        sum += *ptr;  
    }  
 
    //sum =  1.0*(sum) / STUDENT_NUM;  
    cout  << "��1�ſ�ƽ���֣�" <<1.0*(sum) / STUDENT_NUM << endl <<endl;

}

/***************************************************************************
  �������ƣ�
  ��    �ܣ��ҳ����������Ͽγ̲������ѧ��
  ���������
  �� �� ֵ��
  ˵    ���������������ں����м���
***************************************************************************/
void fail(int (*score)[SCORE_NUM])
{
    /* ����������䲿�֣�
       1���������н������� 2���򵥱��� + 1����ָ����� + 1����ָ����� */

    /* ����ִ����䲿�֣�Ҫ��ͬaverage��*/
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
 	cout<<"2�����ϲ������ѧ����"<<endl;
	cout<<"No��"<<rowptr-score+1<<" ";
 	for (ptr = &score[rowptr-score][0]; ptr < &score[rowptr-score][0]+SCORE_NUM; ptr ++)
    {  
    	cout<<*ptr<<" ";
        sum += *ptr;  
    }  
 
    //sum =  (sum) / SCORE_NUM;  
    cout   << "ƽ����" << 1.0* (sum) / SCORE_NUM << endl <<endl;
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ��ҳ�ƽ���ɼ���90�����ϻ�ȫ���ɼ���85�����ϵ�ѧ��
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void good(int (*score)[SCORE_NUM])
{
    /* ����������䲿�֣�
       1���������н������� 2���򵥱��� + 1����ָ����� + 1����ָ����� */

    /* ����ִ����䲿�֣�Ҫ��ͬaverage��*/
	int sum=0;
	int cnt;
	int* ptr;
	int (*rowptr) [5] = score;
    cout<<"ƽ��90���ϻ�ȫ��85���ϵ�ѧ����"<<endl;
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
			cout<<"No��"<<rowptr-score+1<<" ";
 			for (ptr = &score[rowptr-score][0]; ptr < &score[rowptr-score][0]+SCORE_NUM; ptr ++)
    		{  
    			cout<<*ptr<<" ";
        		sum += *ptr;  
   			}  
    		//sum =  (sum) / SCORE_NUM;  
    		cout << "ƽ����" << 1.0*(sum) / SCORE_NUM<< endl;
		}
	}
 
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
int main()
{
    int a[STUDENT_NUM][SCORE_NUM] = {
		{91, 81, 71, 61, 51},	//��1��ѧ����1-5�ſεĳɼ�
		{92, 82, 72, 32, 52},   //��2��ѧ����1-5�ſεĳɼ�
		{93, 83, 99, 80, 95},   //��3��ѧ����1-5�ſεĳɼ�
		{97, 85, 87, 91, 88} }; //��4��ѧ����1-5�ſεĳɼ�
	
	
    /* �������Ԥ�������⣬�������н������� 1����ָ����� + 1����ָ����� */
    cout<<"��ʼ��Ϣ��"<<endl;
	int* ptr;
	int (*rowptr) [5] = a;
    
    for(;rowptr-a<=3;rowptr++)
    {
    	//cnt=0;
    	cout<<"No."<<rowptr-a+1<<"��1-5�ſγɼ���";
    	for(ptr=a[rowptr-a];ptr<a[rowptr-a]+SCORE_NUM;ptr++)
    	{
    		cout<<*ptr<<" ";
		}
		cout<<endl;
	}
	
	cout<<endl;
    /* ����ִ����䲿�֣�Ҫ��ͬaverage��*/
	average(a);
	
	fail(a);
	
	good(a);
	
    return 0;
}
