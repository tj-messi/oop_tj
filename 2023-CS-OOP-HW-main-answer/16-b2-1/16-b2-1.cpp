/* 2150792 �ƿ� ţ»�� */
#include <iostream>
#include <cstring>
using namespace std;

const int ROW = 2;
const int COL = 3;

#define OPERATOR_IS_MENBER_FUNCTION		1	//������������ó�Ա������ʽʵ�֣����ֵΪ0����ʾ����Ԫ��ʽʵ�֣�
/* !@#$%^&*() �滻�ָ��ߣ����м�֮ǰ�е����ݾ��ᱻ�滻�����˵�8�е��޸�0/1֮�⣬��Ҫ���Լ������� )(*&^%$#@! */

class matrix {
private:
	int value[ROW][COL];
	//����֮�ⲻ�������������ݳ�Ա
public:
	matrix(const int(*p)[COL]);	//���캯��-1�Σ��������ʼ������
	matrix();					//���캯��-0��
#if OPERATOR_IS_MENBER_FUNCTION
	//����+�ĳ�Ա����ʵ�ַ�ʽ������
	matrix operator+(const matrix& b);
#else
	//����+����Ԫ����ʵ�ַ�ʽ������
	friend matrix operator+(const matrix& a, const matrix& b);
#endif
	/* ----������Ҫ����������Ա�����Ķ������Ԫ��������������������---- */
	friend ostream& operator<<(ostream& out, const matrix& mat);  // ����<<
	friend istream& operator>>(istream& in, matrix& mat);         // ����>>
};

/* ---- ������Ա����������ʵ��/��Ԫ������ʵ�֣�����+��ʵ���г�Ա����Ԫ������ʽ��Ҫ����������Ԥ������ ---- */
/* ���캯��-0�Σ���ʼ������ */
matrix::matrix()
{
	memset(value, 0, sizeof(value));	
}

/* ���캯��-1�Σ���ʼ������ */
matrix::matrix(const int(*p)[COL])
{
	for (int i = 0; i < ROW; i++)
		for (int j = 0; j < COL; j++)
			value[i][j] = p[i][j];
}

ostream& operator<<(ostream& out, const matrix& mat)
{
	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COL; j++)
			out << mat.value[i][j] << " ";
		out << endl;
	}
	return out;
}

istream& operator>>(istream& in, matrix& mat)
{
	for (int i = 0; i < ROW; i++)
		for (int j = 0; j < COL; j++)
			in >> mat.value[i][j];
	return in;
}

#if OPERATOR_IS_MENBER_FUNCTION
//����+�ĳ�Ա������ʽ������ʵ��
matrix matrix::operator+(const matrix& b)
{
	matrix res;
	for (int i = 0; i < ROW; i++)
		for (int j = 0; j < COL; j++)
			res.value[i][j] = value[i][j] + b.value[i][j];
	return res;
}

#else
//����+����Ԫ������ʽ������ʵ��
matrix operator+(const matrix& a, const matrix& b)
{
	matrix res;
	for (int i = 0; i < ROW; i++)
		for (int j = 0; j < COL; j++)
			res.value[i][j] = a.value[i][j] + b.value[i][j];
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
	int a[ROW][COL] = { { 1,2,3 },{ 4,5,6 } };
	int b[ROW][COL] = { { 2,4,6 },{ 3,6,9 } };
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