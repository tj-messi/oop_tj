/* 2150792 �ƿ� ţ»�� */
#include <iostream>
#include <string>
#include <cstring>
#include "16-b2-2.hpp"
using namespace std;

/* ----main������׼��---- */
int main()
{
	if (1) {
		matrix<int, 2, 3> m1, m2, m3;

		/* ������������� */
		cout << "���������m1��ֵ(int�ͣ���2��3�У������к��е�˳������)" << endl;
		cin >> m1;
		cout << "���������m2��ֵ(int�ͣ���2��3�У������к��е�˳������)" << endl;
		cin >> m2;

		cout << "��ʼ����m1��ֵ��" << endl;
		cout << m1 << endl;
		cout << "��ʼ����m2��ֵ��" << endl;
		cout << m2 << endl;
		cout << "��Ӻ����m3��ֵ��" << endl;
		cout << (m3 = m1 + m2) << endl;
		cout << endl;
	}

	if (1) {
		matrix<double, 3, 2> m1, m2, m3;

		/* ������������� */
		cout << "���������m1��ֵ(double�ͣ���3��2�У������к��е�˳������)" << endl;
		cin >> m1;
		cout << "���������m2��ֵ(double�ͣ���3��2�У������к��е�˳������)" << endl;
		cin >> m2;

		cout << "��ʼ����m1��ֵ��" << endl;
		cout << m1 << endl;
		cout << "��ʼ����m2��ֵ��" << endl;
		cout << m2 << endl;
		cout << "��Ӻ����m3��ֵ��" << endl;
		cout << (m3 = m1 + m2) << endl;
		cout << endl;
	}

	if (1) {
		matrix<string, 3, 3> m1, m2, m3;

		/* ��������������ַ���Ϊ��Сд��ĸ��������м��ɣ������Ǻ��ո�/tab/��˫���ŵ������ַ�
		   �ַ���+�Ĺ���ȼ���string��+����ab+cd�Ľ����abcd */
		cout << "���������m1��ֵ(string�ͣ���3��3�У������к��е�˳������)" << endl;
		cin >> m1;
		cout << "���������m2��ֵ(string�ͣ���3��3�У������к��е�˳������)" << endl;
		cin >> m2;

		cout << "��ʼ����m1��ֵ��" << endl;
		cout << m1 << endl;
		cout << "��ʼ����m2��ֵ��" << endl;
		cout << m2 << endl;
		cout << "��Ӻ����m3��ֵ��" << endl;
		cout << (m3 = m1 + m2) << endl;
		cout << endl;
	}

	return 0;
}

