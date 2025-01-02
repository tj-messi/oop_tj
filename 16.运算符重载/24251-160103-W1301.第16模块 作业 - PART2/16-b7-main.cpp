#include <iostream>
#include "16-b7.h"
using namespace std;

#if defined(__linux) || defined(__linux__) //Linux
/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void wait_for_enter()
{
	cout << endl << "���س�������";
	while (getchar() != '\n')
		;
	cout << endl << endl;
}

#else //VS+Dev
#include <Windows.h>
#include <conio.h>
/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void wait_for_enter()
{
	cout << endl << "���س�������";
	while (_getch() != '\r')
		;
	cout << endl << endl;
}
#endif

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
int main()
{
	if (1) {
		week w1 = wed, w2;
		static week w3;

		cout << "enum ��cout�����������(��/����):" << endl;
		cout << "=================================" << endl;
		cout << "������� : ������ ʵ����� : " << w1 << endl;
		cout << "������� : ���   ʵ����� : " << w2 << endl; //�����������˼ֵ"������/../������/����"�����Խ���
		cout << "������� : ������ ʵ����� : " << w3 << endl;
		cout << "������� : ������ ʵ����� : " << sat << endl;
		cout << "������� : ����   ʵ����� : " << static_cast<week>(9) << endl;
		cout << "������� : ����   ʵ����� : " << week(11) << endl;
		cout << "������� : ����   ʵ����� : " << (week)12 << endl;
		cout << endl;

		wait_for_enter();
	}

	if (1) {
		week w;

		cout << "enum ��cin�����������:" << endl;
		cout << "=======================" << endl;
		cout << "������mon�����ִ�Сд��" << endl;
		cin >> w;
		cout << "������� : ����һ ʵ����� : " << w << endl;

		cout << "������Mon�����ִ�Сд��" << endl;
		cin >> w;
		cout << "������� : ����һ ʵ����� : " << w << endl;

		cout << "������mOn�����ִ�Сд��" << endl;
		cin >> w;
		cout << "������� : ����һ ʵ����� : " << w << endl;

		cout << "������moN�����ִ�Сд��" << endl;
		cin >> w;
		cout << "������� : ����һ ʵ����� : " << w << endl;

		cout << "������MOn�����ִ�Сд��" << endl;
		cin >> w;
		cout << "������� : ����һ ʵ����� : " << w << endl;

		cout << "������mON�����ִ�Сд��" << endl;
		cin >> w;
		cout << "������� : ����һ ʵ����� : " << w << endl;

		cout << "������MoN�����ִ�Сд��" << endl;
		cin >> w;
		cout << "������� : ����һ ʵ����� : " << w << endl;

		cout << "������MON�����ִ�Сд��" << endl;
		cin >> w;
		cout << "������� : ����һ ʵ����� : " << w << endl;

		cout << "ѭ��7�Σ�ÿ���������Сд�����������sun / mon / tue / wed / thu / fri / sat" << endl;
		for (int i = 0; i < 7; i++) {
			cin >> w;
			cout << "������� : " << week(i) << " ʵ����� : " << w << endl;
		}

		cout << "ѭ��3�Σ�ÿ�����������sun / mon / tue / wed / thu / fri / sat������" << endl;
		for (int i = 0; i < 3; i++) {
			cin >> w;
			cout << "������� : ����   ʵ����� : " << w << endl;
		}

		wait_for_enter();
	}

	if (1) {
		week w1 = wed, w2;

		cout << "enum��++����:" << endl;
		cout << "=============" << endl;
		w2 = w1++;
		cout << "������� : ������ ʵ����� : " << w1 << endl;
		cout << "������� : ������ ʵ����� : " << w2 << endl;
		cout << endl;

		w1 = sat;
		w2 = w1++;
		cout << "������� : ������ ʵ����� : " << w1 << endl;
		cout << "������� : ������ ʵ����� : " << w2 << endl;
		cout << endl;

		w1 = wed;
		w2 = ++w1;
		cout << "������� : ������ ʵ����� : " << w1 << endl;
		cout << "������� : ������ ʵ����� : " << w2 << endl;
		cout << endl;

		w1 = sat;
		w2 = ++w1;
		cout << "������� : ������ ʵ����� : " << w1 << endl;
		cout << "������� : ������ ʵ����� : " << w2 << endl;
		cout << endl;

		wait_for_enter();
	}

	if (1) {
		cout << "enum��ѭ��ǰ׺++����:" << endl;
		cout << "=====================" << endl;

		week w1 = fri;
		const char chn[] = "����һ��������";
		for (int i = 0; i < 7; i++) {
			cout << "������� : ����" << chn[i * 2] << chn[i * 2 + 1] << " ʵ����� : " << ++w1 << endl;
		}

		wait_for_enter();
	}

	if (1) {
		cout << "enum��ѭ����׺++����:" << endl;
		cout << "=====================" << endl;

		week w1 = wed;
		const char chn[] = "����������һ��";
		for (int i = 0; i < 7; i++) {
			cout << "������� : ����" << chn[i * 2] << chn[i * 2 + 1] << " ʵ����� : " << w1++ << endl;
		}

		wait_for_enter();
	}

	if (1) {
		week w1 = wed, w2;

		cout << "enum��--����:" << endl;
		cout << "=============" << endl;
		w2 = w1--;
		cout << "������� : ���ڶ� ʵ����� : " << w1 << endl;
		cout << "������� : ������ ʵ����� : " << w2 << endl;
		cout << endl;

		w1 = sun;
		w2 = w1--;
		cout << "������� : ������ ʵ����� : " << w1 << endl;
		cout << "������� : ������ ʵ����� : " << w2 << endl;
		cout << endl;

		w1 = wed;
		w2 = --w1;
		cout << "������� : ���ڶ� ʵ����� : " << w1 << endl;
		cout << "������� : ���ڶ� ʵ����� : " << w2 << endl;
		cout << endl;

		w1 = sun;
		w2 = --w1;
		cout << "������� : ������ ʵ����� : " << w1 << endl;
		cout << "������� : ������ ʵ����� : " << w2 << endl;
		cout << endl;

		wait_for_enter();
	}

	if (1) {
		cout << "enum��ѭ��ǰ׺--����:" << endl;
		cout << "=====================" << endl;

		week w1 = fri;
		const char chn[] = "������һ������";
		for (int i = 6; i >= 0; i--) {
			cout << "������� : ����" << chn[i * 2] << chn[i * 2 + 1] << " ʵ����� : " << --w1 << endl;
		}

		wait_for_enter();
	}

	if (1) {
		cout << "enum��ѭ����׺--����:" << endl;
		cout << "=====================" << endl;

		week w1 = wed;
		const char chn[] = "��������һ����";
		for (int i = 6; i >= 0; i--) {
			cout << "������� : ����" << chn[i * 2] << chn[i * 2 + 1] << " ʵ����� : " << w1-- << endl;
		}

		wait_for_enter();
	}

	if (1) {
		week w1 = wed, w2;

		cout << "enum��+/-����1:" << endl;
		cout << "===============" << endl;
		w2 = w1 + 2;
		cout << "������� : ������ ʵ����� : " << w1 << endl;
		cout << "������� : ������ ʵ����� : " << w2 << endl;
		cout << endl;

		w1 = wed;
		w2 = w1 + 15;
		cout << "������� : ������ ʵ����� : " << w1 << endl;
		cout << "������� : ������ ʵ����� : " << w2 << endl;
		cout << endl;

		w1 = wed;
		w2 = w1 - 3;
		cout << "������� : ������ ʵ����� : " << w1 << endl;
		cout << "������� : ������ ʵ����� : " << w2 << endl;
		cout << endl;

		w1 = wed;
		w2 = w1 - 7006;
		cout << "������� : ������ ʵ����� : " << w1 << endl;
		cout << "������� : ������ ʵ����� : " << w2 << endl;
		cout << endl;

		wait_for_enter();
	}

	if (1) {
		week w1 = wed;

		cout << "enum��+/-����2:" << endl;
		cout << "===============" << endl;
		w1 = w1 + 2;
		cout << "������� : ������ ʵ����� : " << w1 << endl;

		w1 = wed;
		w1 = w1 + 15;
		cout << "������� : ������ ʵ����� : " << w1 << endl;

		w1 = wed;
		w1 = w1 - 3;
		cout << "������� : ������ ʵ����� : " << w1 << endl;

		w1 = wed;
		w1 = w1 - 7006;
		cout << "������� : ������ ʵ����� : " << w1 << endl;

		wait_for_enter();
	}

	if (1) {
		week w1 = wed;

		cout << "enum��+=/-=����:" << endl;
		cout << "================" << endl;

		w1 += 2;
		cout << "������� : ������ ʵ����� : " << w1 << endl;

		w1 = wed;
		w1 += 15;
		cout << "������� : ������ ʵ����� : " << w1 << endl;

		w1 = wed;
		w1 -= 3;
		cout << "������� : ������ ʵ����� : " << w1 << endl;

		w1 = wed;
		w1 -= 7006;
		cout << "������� : ������ ʵ����� : " << w1 << endl;

		cout << endl;
		wait_for_enter();
	}

	return 0;
}
