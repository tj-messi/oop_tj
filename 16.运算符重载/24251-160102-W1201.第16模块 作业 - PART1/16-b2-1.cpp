/*2351114 �쿡�� ������*/
#include <iostream>
using namespace std;

#include "16-b2-1.h" //16-b2-1.h�ڱ���ʱ�ᱻ�滻������Ҫ�ύ���Լ�����ʱ��������Ķ�

class matrix {
private:
	int value[ROW][COL];
	//����֮�ⲻ������������ݳ�Ա
public:
	matrix(const int(*p)[COL]);	//���캯�����������ʼ������
	matrix();

#if OPERATOR_IS_MENBER_FUNCTION
	//����+�ĳ�Ա����ʵ�ַ�ʽ������
	matrix operator+(const matrix& m2);
#else
	//����+����Ԫ����ʵ�ַ�ʽ������
	frined matrix operator+(const matrix& m1 ,const matrix& m2);
#endif

	/* ----������Ҫ���������Ա�����Ķ������Ԫ��������������������---- */
	friend ostream& operator<<(ostream& out, const matrix& m);  // ����<<
	friend istream& operator>>(istream& in, matrix& m);         // ����>>
};

/* ---- ������Ա����������ʵ��/��Ԫ������ʵ�֣�����+��ʵ���г�Ա����Ԫ������ʽ��Ҫ����������Ԥ������ ---- */

matrix::matrix()
{
	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COL; j++)
		{
			value[i][j] = 0;
		}
	}
}

matrix::matrix(const int(*p)[COL])
{
	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COL; j++)
		{
			value[i][j] = p[i][j];
		}
	}
}

ostream& operator<<(ostream& out, const matrix& m)
{
	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COL; j++)
		{
			out << m.value[i][j] << " ";
		}
		out << endl;
	}
	return out;
}

istream& operator>>(istream& in, matrix& m)
{
	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COL; j++)
		{
			in >> m.value[i][j];
		}
	}
	return in;
}

#if OPERATOR_IS_MENBER_FUNCTION
//����+�ĳ�Ա������ʽ������ʵ��

matrix matrix::operator+(const matrix& m2)
{
	matrix res;
	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COL; j++)
		{
			res.value[i][j] = value[i][j] + m2.value[i][j];
		}
	}
	return res;
}

#else
//����+����Ԫ������ʽ������ʵ��
matrix operator+(const matrix& m1, const matrix& m2)
{
	matrix res;
	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COL; j++)
		{
			res.value[i][j] = m1.value[i][j] + m2.value[i][j];
		}
	}
	return res;
}
#endif


/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����main������׼��
***************************************************************************/
int main()
{
//	int a[ROW][COL] = { { 1,2,3 },{ 4,5,6 } };
//	int b[ROW][COL] = { { 2,4,6 },{ 3,6,9 } };
//   a/b������ά��������16-b2-1.h����ҵ���ʱ�ᱻ�滻

	matrix m1(a), m2(b), m3; //m3�ĳ�ֵΪȫ0

	/* ����Ϊ��ֵ���� */
	cout << "��ʼ����m1��ֵ" << endl;
	cout << m1 << endl;
	cout << "��ʼ����m2��ֵ" << endl;
	cout << m2 << endl;

	m3 = m1 + m2;
	cout << "��Ӻ����m3��ֵ" << endl;
	cout << m3 << endl;

	cout << "------------------" << endl;

	/* ����Ϊ����������� */
	cout << "�������ʼ����m1" << endl;
	cin >> m1;
	cout << "�������ʼ����m2" << endl;
	cin >> m2;

	cout << "��ʼ����m1��ֵ" << endl;
	cout << m1 << endl;
	cout << "��ʼ����m2��ֵ" << endl;
	cout << m2 << endl;
	cout << "��Ӻ����m3��ֵ" << endl;
	cout << (m3 = m1 + m2) << endl;

	return 0;
}
