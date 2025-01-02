/*������ 2351114 �쿡��*/
#include <iostream>
#include <iomanip>
using namespace std;

const char* sp = "=====================================";

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����ÿ�����ֿ��Ϊ8���Ҷ���
***************************************************************************/
template<typename n,int len,int high>
void matrix_print(const char* str,n(&matrix) [high][len])	//��...�滻Ϊ��Ӧ����
{
	/* ������������ */
	cout<<str<<endl;
	
	for(int i=0;i<high;i++)
	{
		for(int j=0;j<len;j++)
		{
			cout<<setw(8)<<matrix[i][j];
		}
		
		cout<<endl;
	}
	
	return;
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
template<typename n1,typename n2,typename n3,int len,int high>
void matrix_addition(n1(&matrix_add)[high][len],n2(&matrix1)[high][len],n3(&matrix2)[high][len])	//��...�滻Ϊ��Ӧ����
{
	/* ������������ */
	cout << "Դ����1 : ��=" << high << " ��=" << len<< " ռ�ÿռ�=" << sizeof(matrix1) << "�ֽ�" << endl;
	cout << "Դ����2 : ��=" <<  high << " ��=" << len << " ռ�ÿռ�=" << sizeof(matrix2) << "�ֽ�" << endl;
	cout << "�;���  : ��=" <<  high << " ��=" << len << " ռ�ÿռ�=" << sizeof(matrix_add) << "�ֽ�" << endl;
	for(int i=0;i<high;i++)
	{
		for(int j=0;j<len;j++)
		{
			matrix_add[i][j]=(n1)(matrix1[i][j]+matrix2[i][j]);
		}
		
		//cout<<endl;
	}
	return;
}


/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
template<typename n1,typename n2,typename n3,int len,int mid,int high>
void matrix_multiplication(n1(&matrix_mul)[high][len],n2(&matrix1)[high][mid],n3(&matrix2)[mid][len])	//��...�滻Ϊ��Ӧ����
{
	/* ������������ */
	cout << "Դ����1 : ��=" << high << " ��=" << mid<< " ռ�ÿռ�=" << sizeof(matrix1) << "�ֽ�" << endl;
	cout << "Դ����2 : ��=" <<  mid << " ��=" << len << " ռ�ÿռ�=" << sizeof(matrix2) << "�ֽ�" << endl;
	cout << "�;���  : ��=" <<  high << " ��=" << len << " ռ�ÿռ�=" << sizeof(matrix_mul) << "�ֽ�" << endl;
	//memset(matrix_mul,0,sizeof matrix_mul);
	for(int i=0;i<high;i++)
	{
		for(int j=0;j<len;j++)
			matrix_mul[i][j]=0;
	}
	for(int i=0;i<high;i++)
	{
		for(int j=0;j<len;j++)
		{
			for(int k=0;k<mid;k++)
				matrix_mul[i][j]+=(n1)(matrix1[i][k]*matrix2[k][j]);
		}
		
		//cout<<endl;
	}
	return;
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����main������׼����
***************************************************************************/
int main()
{
	int t1[3][4] = {
		{1,2,3,4},
		{5,6,7,8},
		{9,10,11,12}
	};
	int t2[3][4] = {
		{12,11,10,9},
		{8,7,6,5},
		{4,3,2,1}
	};
	int t3[4][2] = {
		{1, 2},
		{3, 4},
		{5, 6},
		{7, 8}
	};
	int t_add[3][4], t_mul[3][2];

	cout << sp << endl;
	matrix_print("�ӷ����㣬Դ����1��", t1);
	matrix_print("�ӷ����㣬Դ����2��", t2);
	matrix_addition(t_add, t1, t2);	//��t1��t2�ĺͷ���t_add�У��˹���֤������������һ��
	matrix_print("�ӷ����㣬�;��� ��", t_add);
	cout << sp << endl;
	matrix_print("�˷����㣬Դ����1��", t1);
	matrix_print("�˷����㣬Դ����2��", t3);
	matrix_multiplication(t_mul, t1, t3);	//��t1��t2�ĺͷ���t_add�У��˹���֤������������һ��
	matrix_print("�˷����㣬������ ��", t_mul);
	cout << sp << endl;

	double d1[2][4] = {
		{1.1, 2.2, 3.3, 4.4},
		{5.5 ,6.6, 7.7, 8.8}
	};
	double d2[2][4] = {
		{8.8, 7.7, 6.6, 5.5},
		{4.4, 3.3, 2.2, 1.1}
	};
	double d_add[2][4];
	/* ��Ҫ��Ϊʲô����˷��������Ͳ�ͬ������� */
	float f3[4][3] = {
		{12.12f, 11.11f, 10.10f},
		{9.9f, 8.8f, 7.7f},
		{6.6f, 5.5f, 4.4f},
		{3.3f, 2.2f, 1.1f}
	};
	int i_mul[2][3];

	matrix_print("�ӷ����㣬Դ����1��", d1);
	matrix_print("�ӷ����㣬Դ����2��", d2);
	matrix_addition(d_add, d1, d2);	//��d1��d2�ĺͷ���d_add�У��˹���֤������������һ��
	matrix_print("�ӷ����㣬�;��� ��", d_add);
	cout << sp << endl;
	matrix_print("�˷����㣬Դ����1��", d1);
	matrix_print("�˷����㣬Դ����2��", f3);
	matrix_multiplication(i_mul, d1, f3);	//��t1��t2�ĺͷ���t_add�У��˹���֤������������һ��
	matrix_print("�˷����㣬������ ��", i_mul);
	cout << sp << endl;

	return 0;
}
