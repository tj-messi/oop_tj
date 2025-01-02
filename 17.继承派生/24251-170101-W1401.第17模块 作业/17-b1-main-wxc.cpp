/* 2353597 ��ѩ� �ư� */
/* 2351577 ��巺� 2353259 ������ 2351114 �쿡�� */
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include <stdio.h>
#include <cstring>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include "17-b1-TStringAdv.h"
using namespace std;


#if defined(__linux) || defined(__linux__)
#include <sys/time.h>
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


#else
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
	cout << endl << "���س���������Ctrl+C�ж�ִ��";

	char ch;
	while (1) {
		ch = _getch();
		if (ch == '\3')
			exit(-1);	//Ctrl+Cǿ���ж�
		if (ch == '\r')
			break; //����ѭ��
	}

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
		const TStringAdv s1;                 //s1Ϊ��
		const TStringAdv s2 = nullptr;        //s2Ϊ��
		const TStringAdv s3(nullptr);         //s3Ϊ��
		const TStringAdv s4 = "";            //s4Ϊ��
		const TStringAdv s5("");             //s5Ϊ��
		const TStringAdv s6("teststr2");      //s6Ϊ"teststr2"
		const TStringAdv s7 = "teststr3";     //s7Ϊ"teststr3"

		cout << "������󲢳�ʼ������(nullptr���ַ���������ʼ��)" << endl;

		cout << "s1Ӧ����<EMPTY>�� ʵ�������" << s1 << endl;
		cout << "s2Ӧ����<EMPTY>�� ʵ�������" << s2 << endl;
		cout << "s3Ӧ����<EMPTY>�� ʵ�������" << s3 << endl;
		cout << "s4Ӧ����<EMPTY>�� ʵ�������" << s4 << endl;
		cout << "s5Ӧ����<EMPTY>�� ʵ�������" << s5 << endl;
		cout << "s6Ӧ����teststr2��ʵ�������" << s6 << endl;
		cout << "s7Ӧ����teststr3��ʵ�������" << s7 << endl;

		wait_for_enter();
	}

	if (1) {
		const TStringAdv s0 = "teststr1";
		const char* str1 = "teststr2";
		const char  str2[] = "teststr3";
		const char* str3 = nullptr;
		const char  str4[] = "";
		const TStringAdv s1 = s0, s2 = str1, s3 = str2, s4 = str3, s5 = str4;
		const TStringAdv s6(s0), s7(str1), s8(str2), s9(str3), s10(str4);

		cout << "������󲢳�ʼ������(TStringAdv�����ַ�ָ�롢�ַ�����)" << endl;

		cout << "s1 Ӧ����teststr1�� ʵ�������" << s1 << endl;
		cout << "s2 Ӧ����teststr2�� ʵ�������" << s2 << endl;
		cout << "s3 Ӧ����teststr3�� ʵ�������" << s3 << endl;
		cout << "s4 Ӧ����<EMPTY>��  ʵ�������" << s4 << endl;
		cout << "s5 Ӧ����<EMPTY>��  ʵ�������" << s5 << endl;
		cout << "s6 Ӧ����teststr1�� ʵ�������" << s6 << endl;
		cout << "s7 Ӧ����teststr2�� ʵ�������" << s7 << endl;
		cout << "s8 Ӧ����teststr3�� ʵ�������" << s8 << endl;
		cout << "s9 Ӧ����<EMPTY>��  ʵ�������" << s9 << endl;
		cout << "s10Ӧ����<EMPTY>��  ʵ�������" << s10 << endl;

		wait_for_enter();
	}

	if (1) {
		TStringAdv s1;

		cout << "����cin����" << endl;

		cout << "���ڼ���������Hello" << endl;
		cin >> s1;
		cout << "s1Ӧ����Hello��ʵ�������" << s1 << endl;

		cout << "���ڼ���������Hello 123" << endl;
		cin >> s1;
		cout << "s1Ӧ����Hello��ʵ�������" << s1 << endl;

		wait_for_enter();
	}

	if (1) {
		TStringAdv s1("Hello"), s2;

		cout << "��ֵ��������" << endl;

		cout << "s1Ӧ����Hello��  ʵ�������" << s1 << endl;

		s2 = s1;
		cout << "s2Ӧ����Hello��  ʵ�������" << s2 << endl;

		s1 = "Hi";
		cout << "s1Ӧ����Hi��     ʵ�������" << s1 << endl;

		s2 = "";
		cout << "s2Ӧ����<EMPTY>��ʵ�������" << s2 << endl;

		s1 = nullptr;
		cout << "s1Ӧ����<EMPTY>��ʵ�������" << s1 << endl;

		s1 = "Hello";
		cout << "s1Ӧ����Hello��  ʵ�������" << (s1 = s1) << endl;
		cout << "s1Ӧ����Hello��  ʵ�������" << (s1 = s1 = s1 = s1 = s1) << endl;
		cout << "s1Ӧ����Hello��  ʵ�������" << (((s1 = s1) = s1) = s1) << endl;

		wait_for_enter();
	}

	if (1) {
		TStringAdv s0, s1("tong"), s2("ji"), s3;

		cout << "����(+)����(����TStringAdv��)" << endl;

		s3 = s1 + s2;
		cout << "s3ӦΪtongji��ʵ�������" << s3 << endl;

		s3 = s2 + s1;
		cout << "s3ӦΪjitong��ʵ�������" << s3 << endl;

		s3 = s1 + s0;
		cout << "s3ӦΪtong��  ʵ�������" << s3 << endl;

		s3 = s0 + s2;
		cout << "s3ӦΪji��    ʵ�������" << s3 << endl;

		wait_for_enter();
	}

	if (1) {
		TStringAdv s1("tong"), s2, s3;

		cout << "����(+)����(TStringAdv����ַ�������)" << endl;

		s3 = s1 + "ji";
		cout << "s3ӦΪtongji�� ʵ�������" << s3 << endl;

		s3 = "ji" + s1;
		cout << "s3ӦΪjitong�� ʵ�������" << s3 << endl;

		s3 = s1 + "";
		cout << "s3ӦΪtong��   ʵ�������" << s3 << endl;

		s3 = s1 + nullptr;
		cout << "s3ӦΪtong��   ʵ�������" << s3 << endl;

		s3 = "" + s1;
		cout << "s3ӦΪtong��   ʵ�������" << s3 << endl;

		s3 = nullptr + s1;
		cout << "s3ӦΪtong��   ʵ�������" << s3 << endl;

		s3 = s2 + nullptr;
		cout << "s3ӦΪ<EMPTY>��ʵ�������" << s3 << endl;

		s3 = nullptr + s2;
		cout << "s3ӦΪ<EMPTY>��ʵ�������" << s3 << endl;

		s3 = s2 + "";
		cout << "s3ӦΪ<EMPTY>��ʵ�������" << s3 << endl;

		s3 = "" + s2;
		cout << "s3ӦΪ<EMPTY>��ʵ�������" << s3 << endl;

		wait_for_enter();
	}

	if (1) {
		TStringAdv s1("tong"), s3;
		const char* str1 = "ji", * str2 = "", * str3 = nullptr, * str4 = NULL;

		cout << "����(+)����(TStringAdv����ַ�ָ��)" << endl;

		s3 = s1 + str1;
		cout << "s3ӦΪtongji��ʵ�������" << s3 << endl;

		s3 = str1 + s1;
		cout << "s3ӦΪjitong��ʵ�������" << s3 << endl;

		s3 = s1 + str2;
		cout << "s3ӦΪtong��  ʵ�������" << s3 << endl;

		s3 = str2 + s1;
		cout << "s3ӦΪtong��  ʵ�������" << s3 << endl;

		s3 = s1 + str3;
		cout << "s3ӦΪtong��  ʵ�������" << s3 << endl;

		s3 = str3 + s1;
		cout << "s3ӦΪtong��  ʵ�������" << s3 << endl;

		s3 = s1 + str4;
		cout << "s3ӦΪtong��  ʵ�������" << s3 << endl;

		s3 = str4 + s1;
		cout << "s3ӦΪtong��  ʵ�������" << s3 << endl;

		wait_for_enter();
	}

	if (1) {
		TStringAdv s1("tong"), s3;
		char str1[] = "ji", str2[] = "";

		cout << "����(+)����(TStringAdv����ַ�����)" << endl;

		s3 = s1 + str1;
		cout << "s3ӦΪtongji��ʵ�������" << s3 << endl;

		s3 = str1 + s1;
		cout << "s3ӦΪjitong��ʵ�������" << s3 << endl;

		s3 = s1 + str2;
		cout << "s3ӦΪtong��  ʵ�������" << s3 << endl;

		s3 = str2 + s1;
		cout << "s3ӦΪtong��  ʵ�������" << s3 << endl;

		wait_for_enter();
	}

	if (1) {
		TStringAdv s1("Hello"), s3;
		char c = '!';

		cout << "����(+)����(TStringAdv����ַ�)" << endl;

		s3 = s1 + c;
		cout << "s3ӦΪHello!��ʵ�������" << s3 << endl;

		s3 = c + s1;
		cout << "s3ӦΪ!Hello��ʵ�������" << s3 << endl;

		s1 = "ello";
		cout << "s3ӦΪHello!��ʵ�������" << 'H' + s1 + c << endl;

		s1 = "hina";
		cout << "s3ӦΪChina!��ʵ�������" << (s1 = 'C' + s1 + c) << endl;

		wait_for_enter();
	}

	if (1) {
		const TStringAdv s1("��"), s3 = "��", s5 = "Ҳ";
		TStringAdv s;
		const char* str2 = "��", str4[] = "��";
		const char c = '!';

		cout << "����(+)�ۺϲ���(TStringAdv���TStringAdv�ࡢ�ַ�ָ�롢�ַ����顢�ַ�)" << endl;
		s = s1 + str2 + s3 + str4 + s5 + c;
		cout << "sӦ���ǿ�������Ҳ!��ʵ�������" << s << endl;

		cout << "sӦ����Ҳ��������!��ʵ�������" << (s = s5 + s1 + str2 + s3 + str4[0] + str4[1] + c) << endl;
		cout << "sӦ������Ҳ������!��ʵ�������" << (s = str4 + s5 + s1.c_str() + str2 + s3 + c) << endl;
		cout << "sӦ��������Ҳ����!��ʵ�������" << (s = s3 + str4 + s5 + s1 + str2[0] + &str2[1] + c) << endl;
		cout << "sӦ����������Ҳ��!��ʵ�������" << (s = str2 + s3 + str4 + s5.c_str() + s1.c_str() + c) << endl;

		wait_for_enter();
	}

	if (1) {
		TStringAdv s1("tong"), s2 = "ji", s3;

		cout << "������(+=)�򵥲���(TStringAdv���TStringAdv��)" << endl;

		s1 += s2;
		cout << "s1ӦΪtongji��ʵ�������" << s1 << endl;

		s1 = "tong";
		s2 += s1;
		cout << "s2ӦΪjitong��ʵ�������" << s2 << endl;

		s1 = "tong";
		s1 += s3;
		cout << "s1ӦΪtong��  ʵ�������" << s1 << endl;

		s1 = "tong";
		s3 += s1;
		cout << "s3ӦΪtong��  ʵ�������" << s3 << endl;

		wait_for_enter();
	}

	if (1) {
		TStringAdv s1;
		const char* str1 = "tong", * str2 = nullptr, * str3 = NULL, str4[] = "ji", str5[] = "";

		cout << "������(+=)�򵥲���(TStringAdv����ַ�ָ�롢�ַ����顢�ַ����������ַ�����)" << endl;

		s1 = "ji";
		s1 += str1;
		cout << "s1ӦΪjitong��ʵ�������" << s1 << endl;

		s1 = "tong";
		s1 += str2;
		cout << "s1ӦΪtong��  ʵ�������" << s1 << endl;

		s1 = "tong";
		s1 += str3;
		cout << "s1ӦΪtong��  ʵ�������" << s1 << endl;

		s1 = "tong";
		s1 += str4;
		cout << "s1ӦΪtongji��ʵ�������" << s1 << endl;

		s1 = "tong";
		s1 += str5;
		cout << "s1ӦΪtong��  ʵ�������" << s1 << endl;

		s1 = "tong";
		s1 += "ji";
		cout << "s1ӦΪtongji��ʵ�������" << s1 << endl;

		s1 = "tong";
		s1 += 'j';
		s1 += 'i';
		cout << "s1ӦΪtongji��ʵ�������" << s1 << endl;

		wait_for_enter();
	}

	

	if (1) {
		TStringAdv s1("��"), s3 = "��", s5 = "Ҳ";
		TStringAdv s;
		const char* str2 = "��", str4[] = "��";
		const char c = '!';

		cout << "������(+=)�ۺϲ���(TStringAdv���TStringAdv�ࡢ�ַ�ָ�롢�ַ����顢�ַ�)" << endl;

		s = "1.";
		s += s1 + str2 + s3 + str4 + s5 + c;
		cout << "sӦ����1.��������Ҳ!��ʵ�������" << s << endl;

		s = "2.";
		cout << "sӦ����2.Ҳ��������!��ʵ�������" << (s += s5 + s1 + str2 + s3 + str4[0] + str4[1] + c) << endl;

		s = nullptr;
		cout << "sӦ����3.��Ҳ������!��ʵ�������" << ((s = "3.") += str4 + s5 + s1.c_str() + str2 + s3 + c) << endl;

		s = nullptr;
		cout << "sӦ����4.����Ҳ����!��ʵ�������" << (((s += "4." + s3) += (str4 + s5)) += (((s1 += str2[0]) += &str2[1]) += c)) << endl;

		s = nullptr;
		s += '5';
		s += '.';
		s1 = "��";
		cout << "sӦ����5.������Ҳ��!��ʵ�������" << ((((((s += str2) += s3) += str4) += s5.c_str()) += s1.c_str()) += c) << endl;

		wait_for_enter();
	}

	if (1) {
		TStringAdv s1("This is a pencil"), s2("is"), s3;

		cout << "ɾ��(-)����(TStringAdv���TStringAdv��)" << endl;

		cout << "s1ӦΪTh is a pencil��ʵ�������" << (s1 = s1 - s2) << endl;
		s3 = s1 - s2;
		cout << "s3ӦΪTh  a pencil��  ʵ�������" << s3 << endl;

		s1 = "This is a pencil";
		cout << "s1ӦΪTh  a pencil��  ʵ�������" << s1 - s2 - s2 - s2 - s2 - s2 << endl;

		wait_for_enter();
	}

	if (1) {
		TStringAdv s1("This is a pencil"), s2;
		const char* str1 = "is";
		const char str2[] = "is";

		cout << "ɾ��(-)����(TStringAdv���charָ�뼰����)" << endl;

		cout << "s1ӦΪTh is a pencil��ʵ�������" << (s1 = s1 - str1) << endl;
		s2 = s1 - str1;
		cout << "s2ӦΪTh  a pencil��  ʵ�������" << s2 << endl;

		s1 = "This is a pencil";
		cout << "s1ӦΪTh is a pencil��ʵ�������" << (s1 = s1 - str2) << endl;
		s2 = s1 - str2;
		cout << "s2ӦΪTh  a pencil��  ʵ�������" << s2 << endl;

		s1 = "This is a pencil";
		cout << "s1ӦΪTh  a pencil��  ʵ�������" << s1 - str1 - str1 - str1 - str1 - str1 << endl;

		s1 = "This is a pencil";
		cout << "s1ӦΪTh  a pencil��  ʵ�������" << s1 - str2 - str2 - str2 - str2 - str2 << endl;

		wait_for_enter();
	}

	if (1) {
		TStringAdv s1("This is a pencil"), s2;
		char c1 = 'i';

		cout << "ɾ��(-)����(TStringAdv���char�ַ�)" << endl;

		cout << "s1ӦΪThs is a pencil��ʵ�������" << (s1 = s1 - c1) << endl;
		s2 = s1 - c1;
		cout << "s2ӦΪThs s a pencil�� ʵ�������" << s2 << endl;

		s1 = "This is a pencil";
		cout << "s2ӦΪThs s a pencl��  ʵ�������" << (s1 - c1 - c1 - c1 - c1 - c1 - c1 - c1) << endl;

		s1 = "This is a pencil";
		cout << "s1ӦΪThi is a pencil��ʵ�������" << (s1 = s1 - 's') << endl;
		s2 = s1 - 's';
		cout << "s2ӦΪThi i a pencil�� ʵ�������" << s2 << endl;

		s1 = "This is a pencil";
		cout << "s2ӦΪThi i a pencil�� ʵ�������" << (s1 - 's' - 's' - 's' - 's' - 's' - 's') << endl;

		wait_for_enter();
	}

	if (1) {
		TStringAdv s1;
		const TStringAdv s2 = "is";
		const char* str3 = "pen", str4[] = "a";
		const char c = ' ';

		cout << "��ɾ��(-=)�򵥲���(TStringAdv���TStringAdv�ࡢ�ַ�ָ�롢�ַ����顢�ַ�)" << endl;

		s1 = "This is a red pencil";
		cout << "s1ӦΪTh is a red pencil�� ʵ�������" << (s1 -= s2) << endl;

		s1 = "This is a red pencil";
		cout << "s1ӦΪThis is a red cil��  ʵ�������" << (s1 -= str3) << endl;

		s1 = "This is a red pencil";
		cout << "s1ӦΪThis is  red pencil��ʵ�������" << (s1 -= str4) << endl;

		s1 = "This is a red pencil";
		cout << "s1ӦΪThisis a red pencil��ʵ�������" << (s1 -= c) << endl;

		wait_for_enter();
	}

	if (1) {
		TStringAdv s1;
		const TStringAdv s2 = "is";
		const char* str3 = "pen", str4[] = "a";
		const char c = ' ';

		cout << "��ɾ��(-=)�ۺϲ���(TStringAdv���TStringAdv�ࡢ�ַ�ָ�롢�ַ����顢�ַ�)" << endl;

		s1 = "This is a red pencil";
		cout << "s1ӦΪTh  a red pencil��   ʵ�������" << ((s1 -= s2) -= s2) << endl;

		s1 = "This is a red pencil";
		cout << "s1ӦΪThis is  red cil��   ʵ�������" << ((s1 -= str3) -= str4) << endl;

		s1 = "This is a red pencil";
		cout << "s1ӦΪThisisaredpencil��   ʵ�������" << ((((s1 -= c) -= c) -= c) -= c) << endl;

		s1 = "This is a red pencil";
		cout << "s1ӦΪTh��                 ʵ�������" << ((((((((((((s1 -= s2) -= s2) -= str3) -= str4) -= c) -= c) -= c) -= c) -= "red") -= 'c') -= 'i') -= 'l') << endl;

		wait_for_enter();
	}

	if (1) {
		TStringAdv s1("Hello"), s2;

		cout << "����(*)����(TStringAdv���int)" << endl;

		s2 = s1 * 2;
		cout << "s2ӦΪHelloHello��     ʵ�������" << s2 << endl;
		cout << "s1ӦΪHelloHelloHello��ʵ�������" << (s1 = s1 * 3) << endl;

		TStringAdv s3;
		cout << "s3ӦΪ<EMPTY>��        ʵ�������" << (s3 * 5) << endl;
		cout << "s3ӦΪ<EMPTY>��        ʵ�������" << (s3 = s3 * 5) << endl;

		int i, n = 100;
		s1 = "Hello";
		s2 = s1 * n;
		for (i = 1; i < n; i++)
			s2 = s2 - s1;
		cout << "s2ӦΪHello��          ʵ�������" << s2 << endl;

		s1 = "Hello";
		s2 = s1 * n;
		for (i = 0; i < n; i++)
			s2 = s2 - 'l';
		for (i = 0; i < n; i++)
			s2 = s2 - 'l';
		for (i = 0; i < n; i++)
			s2 = s2 - 'o';
		for (i = 0; i < n; i++)
			s2 = s2 - 'H';
		for (i = 1; i < n; i++)  //ע�⣬ֻ�����ѭ���Ǵ�1��ʼ������1��
			s2 = s2 - 'e';
		cout << "s2ӦΪe��              ʵ�������" << s2 << endl;

		wait_for_enter();
	}

	if (1) {
		TStringAdv s1;

		cout << "�Ը���(*=)����(TStringAdv���int)" << endl;

		s1 = "Hello";
		cout << "s1ӦΪHelloHello��                       ʵ�������" << (s1 *= 2) << endl;
		s1 += '!';
		cout << "s1ӦΪHelloHello!HelloHello!HelloHello!��ʵ�������" << (s1 *= 3) << endl;

		s1 = "Hello";
		cout << "s1ӦΪHelloHello!HelloHello!HelloHello!��ʵ�������" << (((s1 *= 2) += '!') *= 3) << endl;

		//		�ر���ԣ����������е�ע�ͣ������������ᱨ�����������˵�����������⣬������Ԥ�ڵ����壨Ϊʲô����ϸ��!!!��
		//		cout << "s1ӦΪHelloHello!HelloHello!HelloHello!��ʵ�������" << (((s1 *= 2) + '!') *= 3) << endl;

		s1 = nullptr;
		cout << "s1ӦΪ<EMPTY>��                          ʵ�������" << (s1 *= 100) << endl;

		wait_for_enter();
	}

	if (1) {
		TStringAdv s1;

		cout << "������(+=)/��ɾ��(-=)/�Ը���(*=)�ۺϲ���" << endl;

		s1 = "Hello";
		cout << "s1ӦΪHello!Hello!Hello!��ʵ�������" << ((s1 += '!') *= 3) << endl;

		s1 = "Hello";
		cout << "s1ӦΪHeo!Heo!Heo!Heo!��  ʵ�������" << (((s1 += '!') -= "ll") *= 4) << endl;

		s1 = "Hello";
		cout << "s1ӦΪHellHello!��        ʵ�������" << (((s1 *= 2) -= 'o') += '!') << endl;

		wait_for_enter();
	}

	if (1) {
		TStringAdv s1("This is a pencil");

		cout << "��ת(!)����" << endl;

		cout << " s1ӦΪThis is a pencil��ʵ�������" << s1 << endl;
		cout << "!s1ӦΪlicnep a si sihT��ʵ�������" << !s1 << endl;
		cout << " s1��ΪThis is a pencil��ʵ�������" << s1 << endl;

		s1 = nullptr;
		cout << " s1ӦΪ<EMPTY>��         ʵ�������" << s1 << endl;
		cout << "!s1ӦΪ<EMPTY>��         ʵ�������" << !s1 << endl;
		cout << " s1��Ϊ<EMPTY>��         ʵ�������" << s1 << endl;

		wait_for_enter();
	}

	if (1) {
		TStringAdv s1 = "house", s2 = "horse", s3 = "house", s4 = "", s5 = nullptr;

		cout << "�Ƚ��������(����TStringAdv��)" << endl;

		cout << "��1=" << s1 << " ��2=" << s2 << "   > ���ӦΪ1��ʵ�ʣ�" << (s1 > s2) << endl;
		cout << "��1=" << s1 << " ��2=" << s2 << "   >=���ӦΪ1��ʵ�ʣ�" << (s1 >= s2) << endl;
		cout << "��1=" << s1 << " ��2=" << s2 << "   < ���ӦΪ0��ʵ�ʣ�" << (s1 < s2) << endl;
		cout << "��1=" << s1 << " ��2=" << s2 << "   <=���ӦΪ0��ʵ�ʣ�" << (s1 <= s2) << endl;
		cout << "��1=" << s1 << " ��2=" << s2 << "   ==���ӦΪ0��ʵ�ʣ�" << (s1 == s2) << endl;
		cout << "��1=" << s1 << " ��2=" << s2 << "   !=���ӦΪ1��ʵ�ʣ�" << (s1 != s2) << endl;

		cout << "��1=" << s1 << " ��3=" << s3 << "   > ���ӦΪ0��ʵ�ʣ�" << (s1 > s3) << endl;
		cout << "��1=" << s1 << " ��3=" << s3 << "   >=���ӦΪ1��ʵ�ʣ�" << (s1 >= s3) << endl;
		cout << "��1=" << s1 << " ��3=" << s3 << "   < ���ӦΪ0��ʵ�ʣ�" << (s1 < s3) << endl;
		cout << "��1=" << s1 << " ��3=" << s3 << "   <=���ӦΪ1��ʵ�ʣ�" << (s1 <= s3) << endl;
		cout << "��1=" << s1 << " ��3=" << s3 << "   ==���ӦΪ1��ʵ�ʣ�" << (s1 == s3) << endl;
		cout << "��1=" << s1 << " ��3=" << s3 << "   !=���ӦΪ0��ʵ�ʣ�" << (s1 != s3) << endl;

		cout << "��1=" << s1 << " ��4=" << s4 << " > ���ӦΪ1��ʵ�ʣ�" << (s1 > s4) << endl;
		cout << "��1=" << s1 << " ��4=" << s4 << " >=���ӦΪ1��ʵ�ʣ�" << (s1 >= s4) << endl;
		cout << "��1=" << s1 << " ��4=" << s4 << " < ���ӦΪ0��ʵ�ʣ�" << (s1 < s4) << endl;
		cout << "��1=" << s1 << " ��4=" << s4 << " <=���ӦΪ0��ʵ�ʣ�" << (s1 <= s4) << endl;
		cout << "��1=" << s1 << " ��4=" << s4 << " ==���ӦΪ0��ʵ�ʣ�" << (s1 == s4) << endl;
		cout << "��1=" << s1 << " ��4=" << s4 << " !=���ӦΪ1��ʵ�ʣ�" << (s1 != s4) << endl;

		cout << "��1=" << s1 << " ��5=" << s5 << " > ���ӦΪ1��ʵ�ʣ�" << (s1 > s5) << endl;
		cout << "��1=" << s1 << " ��5=" << s5 << " >=���ӦΪ1��ʵ�ʣ�" << (s1 >= s5) << endl;
		cout << "��1=" << s1 << " ��5=" << s5 << " < ���ӦΪ0��ʵ�ʣ�" << (s1 < s5) << endl;
		cout << "��1=" << s1 << " ��5=" << s5 << " <=���ӦΪ0��ʵ�ʣ�" << (s1 <= s5) << endl;
		cout << "��1=" << s1 << " ��5=" << s5 << " ==���ӦΪ0��ʵ�ʣ�" << (s1 == s5) << endl;
		cout << "��1=" << s1 << " ��5=" << s5 << " !=���ӦΪ1��ʵ�ʣ�" << (s1 != s5) << endl;

		wait_for_enter();
	}

	if (1) {
		TStringAdv s1 = "house";

		cout << "�Ƚ��������(TStringAdv����ַ�������1)" << endl;

		cout << "��1=" << s1 << " ����=horse" << "     > ���ӦΪ1��ʵ�ʣ�" << (s1 > "horse") << endl;
		cout << "��1=" << s1 << " ����=horse" << "     >=���ӦΪ1��ʵ�ʣ�" << (s1 >= "horse") << endl;
		cout << "��1=" << s1 << " ����=horse" << "     < ���ӦΪ0��ʵ�ʣ�" << (s1 < "horse") << endl;
		cout << "��1=" << s1 << " ����=horse" << "     <=���ӦΪ0��ʵ�ʣ�" << (s1 <= "horse") << endl;
		cout << "��1=" << s1 << " ����=horse" << "     ==���ӦΪ0��ʵ�ʣ�" << (s1 == "horse") << endl;
		cout << "��1=" << s1 << " ����=horse" << "     !=���ӦΪ1��ʵ�ʣ�" << (s1 != "horse") << endl;

		cout << "��1=" << s1 << " ����=house" << "     > ���ӦΪ0��ʵ�ʣ�" << (s1 > "house") << endl;
		cout << "��1=" << s1 << " ����=house" << "     >=���ӦΪ1��ʵ�ʣ�" << (s1 >= "house") << endl;
		cout << "��1=" << s1 << " ����=house" << "     < ���ӦΪ0��ʵ�ʣ�" << (s1 < "house") << endl;
		cout << "��1=" << s1 << " ����=house" << "     <=���ӦΪ1��ʵ�ʣ�" << (s1 <= "house") << endl;
		cout << "��1=" << s1 << " ����=house" << "     ==���ӦΪ1��ʵ�ʣ�" << (s1 == "house") << endl;
		cout << "��1=" << s1 << " ����=house" << "     !=���ӦΪ0��ʵ�ʣ�" << (s1 != "house") << endl;

		cout << "��1=" << s1 << " ����=" << "          > ���ӦΪ1��ʵ�ʣ�" << (s1 > "") << endl;
		cout << "��1=" << s1 << " ����=" << "          >=���ӦΪ1��ʵ�ʣ�" << (s1 >= "") << endl;
		cout << "��1=" << s1 << " ����=" << "          < ���ӦΪ0��ʵ�ʣ�" << (s1 < "") << endl;
		cout << "��1=" << s1 << " ����=" << "          <=���ӦΪ0��ʵ�ʣ�" << (s1 <= "") << endl;
		cout << "��1=" << s1 << " ����=" << "          ==���ӦΪ0��ʵ�ʣ�" << (s1 == "") << endl;
		cout << "��1=" << s1 << " ����=" << "          !=���ӦΪ1��ʵ�ʣ�" << (s1 != "") << endl;

		cout << "��1=" << s1 << " ����=<nullptr>" << " > ���ӦΪ1��ʵ�ʣ�" << (s1 > nullptr) << endl;
		cout << "��1=" << s1 << " ����=<nullptr>" << " >=���ӦΪ1��ʵ�ʣ�" << (s1 >= nullptr) << endl;
		cout << "��1=" << s1 << " ����=<nullptr>" << " < ���ӦΪ0��ʵ�ʣ�" << (s1 < nullptr) << endl;
		cout << "��1=" << s1 << " ����=<nullptr>" << " <=���ӦΪ0��ʵ�ʣ�" << (s1 <= nullptr) << endl;
		cout << "��1=" << s1 << " ����=<nullptr>" << " ==���ӦΪ0��ʵ�ʣ�" << (s1 == nullptr) << endl;
		cout << "��1=" << s1 << " ����=<nullptr>" << " !=���ӦΪ1��ʵ�ʣ�" << (s1 != nullptr) << endl;

		wait_for_enter();
	}

	if (1) {
		TStringAdv s1 = nullptr, s2 = "";

		cout << "�Ƚ��������(TStringAdv����ַ�������2)" << endl;
		/* �յ�TStringAdv��nullptr��"" ����Ϊ��ȣ������ϣ�nullptr�ǵ�ַ��""�Ǵ���û�пɱ��ԣ����Ǵ˴������⴦�� */
		cout << "��1=" << s1 << " ��2=" << s2 << "    > ���ӦΪ0��ʵ�ʣ�" << (s1 > s2) << endl;
		cout << "��1=" << s1 << " ��2=" << s2 << "    >=���ӦΪ1��ʵ�ʣ�" << (s1 >= s2) << endl;
		cout << "��1=" << s1 << " ��2=" << s2 << "    < ���ӦΪ0��ʵ�ʣ�" << (s1 < s2) << endl;
		cout << "��1=" << s1 << " ��2=" << s2 << "    <=���ӦΪ1��ʵ�ʣ�" << (s1 <= s2) << endl;
		cout << "��1=" << s1 << " ��2=" << s2 << "    ==���ӦΪ1��ʵ�ʣ�" << (s1 == s2) << endl;
		cout << "��1=" << s1 << " ��2=" << s2 << "    !=���ӦΪ0��ʵ�ʣ�" << (s1 != s2) << endl;

		cout << "��1=" << s1 << " ����=" << "          > ���ӦΪ0��ʵ�ʣ�" << (s1 > "") << endl;
		cout << "��1=" << s1 << " ����=" << "          >=���ӦΪ1��ʵ�ʣ�" << (s1 >= "") << endl;
		cout << "��1=" << s1 << " ����=" << "          < ���ӦΪ0��ʵ�ʣ�" << (s1 < "") << endl;
		cout << "��1=" << s1 << " ����=" << "          <=���ӦΪ1��ʵ�ʣ�" << (s1 <= "") << endl;
		cout << "��1=" << s1 << " ����=" << "          ==���ӦΪ1��ʵ�ʣ�" << (s1 == "") << endl;
		cout << "��1=" << s1 << " ����=" << "          !=���ӦΪ0��ʵ�ʣ�" << (s1 != "") << endl;

		cout << "��1=" << s1 << " ����=<nullptr>" << " > ���ӦΪ0��ʵ�ʣ�" << (s1 > nullptr) << endl;
		cout << "��1=" << s1 << " ����=<nullptr>" << " >=���ӦΪ1��ʵ�ʣ�" << (s1 >= nullptr) << endl;
		cout << "��1=" << s1 << " ����=<nullptr>" << " < ���ӦΪ0��ʵ�ʣ�" << (s1 < nullptr) << endl;
		cout << "��1=" << s1 << " ����=<nullptr>" << " <=���ӦΪ1��ʵ�ʣ�" << (s1 <= nullptr) << endl;
		cout << "��1=" << s1 << " ����=<nullptr>" << " ==���ӦΪ1��ʵ�ʣ�" << (s1 == nullptr) << endl;
		cout << "��1=" << s1 << " ����=<nullptr>" << " !=���ӦΪ0��ʵ�ʣ�" << (s1 != nullptr) << endl;

		wait_for_enter();
	}

	if (1) {
		TStringAdv s1 = "house";
		const char* str2 = "horse", * str3 = "house", * str4 = "", * str5 = nullptr, * str6 = NULL;

		cout << "�Ƚ��������(TStringAdv����ַ�ָ��)" << endl;

		cout << "��1=" << s1 << " ��2=" << str2 << "     > ���ӦΪ1��ʵ�ʣ�" << (s1 > str2) << endl;
		cout << "��1=" << s1 << " ��2=" << str2 << "     >=���ӦΪ1��ʵ�ʣ�" << (s1 >= str2) << endl;
		cout << "��1=" << s1 << " ��2=" << str2 << "     < ���ӦΪ0��ʵ�ʣ�" << (s1 < str2) << endl;
		cout << "��1=" << s1 << " ��2=" << str2 << "     <=���ӦΪ0��ʵ�ʣ�" << (s1 <= str2) << endl;
		cout << "��1=" << s1 << " ��2=" << str2 << "     ==���ӦΪ0��ʵ�ʣ�" << (s1 == str2) << endl;
		cout << "��1=" << s1 << " ��2=" << str2 << "     !=���ӦΪ1��ʵ�ʣ�" << (s1 != str2) << endl;

		cout << "��1=" << s1 << " ��3=" << str3 << "     > ���ӦΪ0��ʵ�ʣ�" << (s1 > str3) << endl;
		cout << "��1=" << s1 << " ��3=" << str3 << "     >=���ӦΪ1��ʵ�ʣ�" << (s1 >= str3) << endl;
		cout << "��1=" << s1 << " ��3=" << str3 << "     < ���ӦΪ0��ʵ�ʣ�" << (s1 < str3) << endl;
		cout << "��1=" << s1 << " ��3=" << str3 << "     <=���ӦΪ1��ʵ�ʣ�" << (s1 <= str3) << endl;
		cout << "��1=" << s1 << " ��3=" << str3 << "     ==���ӦΪ1��ʵ�ʣ�" << (s1 == str3) << endl;
		cout << "��1=" << s1 << " ��3=" << str3 << "     !=���ӦΪ0��ʵ�ʣ�" << (s1 != str3) << endl;

		cout << "��1=" << s1 << " ��4=" << str4 << "*        > ���ӦΪ1��ʵ�ʣ�" << (s1 > str4) << endl;
		cout << "��1=" << s1 << " ��4=" << str4 << "*        >=���ӦΪ1��ʵ�ʣ�" << (s1 >= str4) << endl;
		cout << "��1=" << s1 << " ��4=" << str4 << "*        < ���ӦΪ0��ʵ�ʣ�" << (s1 < str4) << endl;
		cout << "��1=" << s1 << " ��4=" << str4 << "*        <=���ӦΪ0��ʵ�ʣ�" << (s1 <= str4) << endl;
		cout << "��1=" << s1 << " ��4=" << str4 << "*        ==���ӦΪ0��ʵ�ʣ�" << (s1 == str4) << endl;
		cout << "��1=" << s1 << " ��4=" << str4 << "*        !=���ӦΪ1��ʵ�ʣ�" << (s1 != str4) << endl;

		cout << "��1=" << s1 << " ��5=<nullptr>" << " > ���ӦΪ1��ʵ�ʣ�" << (s1 > str5) << endl;
		cout << "��1=" << s1 << " ��5=<nullptr>" << " >=���ӦΪ1��ʵ�ʣ�" << (s1 >= str5) << endl;
		cout << "��1=" << s1 << " ��5=<nullptr>" << " < ���ӦΪ0��ʵ�ʣ�" << (s1 < str5) << endl;
		cout << "��1=" << s1 << " ��5=<nullptr>" << " <=���ӦΪ0��ʵ�ʣ�" << (s1 <= str5) << endl;
		cout << "��1=" << s1 << " ��5=<nullptr>" << " ==���ӦΪ0��ʵ�ʣ�" << (s1 == str5) << endl;
		cout << "��1=" << s1 << " ��5=<nullptr>" << " !=���ӦΪ1��ʵ�ʣ�" << (s1 != str5) << endl;

		cout << "��1=" << s1 << " ��6=<NULL>" << "    > ���ӦΪ1��ʵ�ʣ�" << (s1 > str6) << endl;
		cout << "��1=" << s1 << " ��6=<NULL>" << "    >=���ӦΪ1��ʵ�ʣ�" << (s1 >= str6) << endl;
		cout << "��1=" << s1 << " ��6=<NULL>" << "    < ���ӦΪ0��ʵ�ʣ�" << (s1 < str6) << endl;
		cout << "��1=" << s1 << " ��6=<NULL>" << "    <=���ӦΪ0��ʵ�ʣ�" << (s1 <= str6) << endl;
		cout << "��1=" << s1 << " ��6=<NULL>" << "    ==���ӦΪ0��ʵ�ʣ�" << (s1 == str6) << endl;
		cout << "��1=" << s1 << " ��6=<NULL>" << "    !=���ӦΪ1��ʵ�ʣ�" << (s1 != str6) << endl;

		wait_for_enter();
	}

	if (1) {
		TStringAdv s1 = "house";
		char str2[] = "horse", str3[] = "house", str4[] = "";

		cout << "�Ƚ��������(TStringAdv����ַ�����)" << endl;

		cout << "��1=" << s1 << " ��2=" << str2 << " > ���ӦΪ1��ʵ�ʣ�" << (s1 > str2) << endl;
		cout << "��1=" << s1 << " ��2=" << str2 << " >=���ӦΪ1��ʵ�ʣ�" << (s1 >= str2) << endl;
		cout << "��1=" << s1 << " ��2=" << str2 << " < ���ӦΪ0��ʵ�ʣ�" << (s1 < str2) << endl;
		cout << "��1=" << s1 << " ��2=" << str2 << " <=���ӦΪ0��ʵ�ʣ�" << (s1 <= str2) << endl;
		cout << "��1=" << s1 << " ��2=" << str2 << " ==���ӦΪ0��ʵ�ʣ�" << (s1 == str2) << endl;
		cout << "��1=" << s1 << " ��2=" << str2 << " !=���ӦΪ1��ʵ�ʣ�" << (s1 != str2) << endl;

		cout << "��1=" << s1 << " ��3=" << str3 << " > ���ӦΪ0��ʵ�ʣ�" << (s1 > str3) << endl;
		cout << "��1=" << s1 << " ��3=" << str3 << " >=���ӦΪ1��ʵ�ʣ�" << (s1 >= str3) << endl;
		cout << "��1=" << s1 << " ��3=" << str3 << " < ���ӦΪ0��ʵ�ʣ�" << (s1 < str3) << endl;
		cout << "��1=" << s1 << " ��3=" << str3 << " <=���ӦΪ1��ʵ�ʣ�" << (s1 <= str3) << endl;
		cout << "��1=" << s1 << " ��3=" << str3 << " ==���ӦΪ1��ʵ�ʣ�" << (s1 == str3) << endl;
		cout << "��1=" << s1 << " ��3=" << str3 << " !=���ӦΪ0��ʵ�ʣ�" << (s1 != str3) << endl;

		cout << "��1=" << s1 << " ��4=" << str4 << "      > ���ӦΪ1��ʵ�ʣ�" << (s1 > str4) << endl;
		cout << "��1=" << s1 << " ��4=" << str4 << "      >=���ӦΪ1��ʵ�ʣ�" << (s1 >= str4) << endl;
		cout << "��1=" << s1 << " ��4=" << str4 << "      < ���ӦΪ0��ʵ�ʣ�" << (s1 < str4) << endl;
		cout << "��1=" << s1 << " ��4=" << str4 << "      <=���ӦΪ0��ʵ�ʣ�" << (s1 <= str4) << endl;
		cout << "��1=" << s1 << " ��4=" << str4 << "      ==���ӦΪ0��ʵ�ʣ�" << (s1 == str4) << endl;
		cout << "��1=" << s1 << " ��4=" << str4 << "      !=���ӦΪ1��ʵ�ʣ�" << (s1 != str4) << endl;

		wait_for_enter();
	}

	if (1) {
		TStringAdv s1 = "tong", s2;

		cout << "�󳤶Ȳ���(length()����)" << endl;

		cout << "s1Ϊtong��     ����ӦΪ4�� ʵ�ʣ�" << s1.length() << endl;
		cout << "s2Ϊ<nullptr>������ӦΪ0�� ʵ�ʣ�" << s2.length() << endl;
		s2 = s1 + "ji";
		cout << "s2Ϊtongji��   ����ӦΪ6�� ʵ�ʣ�" << s2.length() << endl;

		cout << "��Ϊtongji��   ����ӦΪ6�� ʵ�ʣ�" << (s1 += (s2 = "ji")).length() << endl;
		cout << "��Ϊtongji��   ����ӦΪ8�� ʵ�ʣ�" << (s1 += "ji").length() << endl;
		cout << "��Ϊtongji��   ����ӦΪ12��ʵ�ʣ�" << (s2 += s1 + "ji").length() << endl;

		wait_for_enter();
	}

	if (1) {
		TStringAdv s1 = "tong", s2;

		cout << "�󳤶Ȳ���(TStringAdvLen()����)" << endl;

		cout << "s1Ϊtong��     ����ӦΪ4�� ʵ�ʣ�" << TStringAdvLen(s1) << endl;
		cout << "s2Ϊ<nullptr>������ӦΪ0�� ʵ�ʣ�" << TStringAdvLen(s2) << endl;
		cout << "��Ϊtongji��   ����ӦΪ6�� ʵ�ʣ�" << TStringAdvLen(s1 + (s2 = "ji")) << endl;
		cout << "��Ϊtongji��   ����ӦΪ6�� ʵ�ʣ�" << TStringAdvLen(s1 + "ji") << endl;
		cout << "��Ϊtongji��   ����ӦΪ6�� ʵ�ʣ�" << TStringAdvLen(s2 = s1 + "ji") << endl;
		cout << "��Ϊtong��     ����ӦΪ4�� ʵ�ʣ�" << TStringAdvLen(s1 + nullptr) << endl;

		cout << "��Ϊtongji��   ����ӦΪ6�� ʵ�ʣ�" << TStringAdvLen(s1 += (s2 = "ji")) << endl;
		cout << "��Ϊtongji��   ����ӦΪ8�� ʵ�ʣ�" << TStringAdvLen(s1 += "ji") << endl;
		cout << "��Ϊtongji��   ����ӦΪ12��ʵ�ʣ�" << TStringAdvLen(s2 += s1 + "ji") << endl;

		wait_for_enter();
	}

	if (1) {
		TStringAdv s1 = "house";
		TStringAdv s2[4] = { "yangpu", "sipingroad", "tongji", "shanghai" };
		int i, j;
		char ch = 'P';

		cout << "[]���������" << endl;

		cout << "��1��" << s1 << "�����δ�ӡ�ַ��Ľ���ǣ�";
		for (i = 0; i < s1.length(); i++)
			cout << s1[i] << ' ';
		cout << endl << endl;

		cout << "��1��" << s1 << "�����δ�ӡ�ַ�intֵ�Ľ���ǣ���Խ�����ǰ4��3ֵ�����ţ���" << endl;
		for (i = -4; i < s1.length() + 4; i++)
			cout << int(s1[i]) << ' ';
		cout << endl << endl;

		s1[0] = s1[0] - 32;
		cout << "��1��" << s1 << "�����δ�ӡ�ַ��Ľ���ǣ�";
		for (i = 0; i < s1.length(); i++)
			cout << s1[i] << ' ';
		cout << endl << endl;

		s1[1] = 'A';
		s1[2] = ch;
		ch += 32;
		s1[3] = ch;
		s1[4] = 'Y';
		cout << "��1��" << s1 << "�����δ�ӡ�ַ��Ľ���ǣ�";
		for (i = 0; i < s1.length(); i++)
			cout << s1[i] << ' ';
		cout << endl << endl;

		cout << "��2������4���ַ��������δ�ӡ�ַ��Ľ���ǣ�" << endl;
		for (i = 0; i < 4; i++) {
			cout << setw(16) << s2[i] << " => ";
			for (j = 0; j < s2[i].length(); j++)
				cout << s2[i][j] << ' ';
			cout << endl;
		}
		cout << endl;

		cout << "��2������4���ַ���������ĸ��д�����δ�ӡ�ַ��Ľ���ǣ�" << endl;
		for (i = 0; i < 4; i++) {
			s2[i][0] -= 32;
			cout << setw(16) << s2[i] << " => ";
			for (j = 0; j < s2[i].length(); j++)
				cout << s2[i][j] << ' ';
			cout << endl;
		}
		cout << endl;

		wait_for_enter();
	}
	if (1) {
		TStringAdv s1("Hello"), s2("World");

		// assign ��������
		cout << "assign ��������" << endl;
		s1.assign(s2);
		cout << "s1Ӧ����World��  ʵ�������" << s1 << endl;
		s1.assign("Hi");
		cout << "s1Ӧ����Hi��     ʵ�������" << s1 << endl;
		s1.assign("");
		cout << "s1Ӧ����<EMPTY>��ʵ�������" << s1 << endl;
		s1.assign(nullptr);
		cout << "s1Ӧ����<EMPTY>��ʵ�������" << s1 << endl;

		wait_for_enter();
	}

	if (1) {
		TStringAdv s1("Hello"), s2("World");

		// append ��������
		cout << "append ��������" << endl;
		s1.append(s2);
		cout << "s1Ӧ����HelloWorld��ʵ�������" << s1 << endl;
		s1.append("Hi");
		cout << "s1Ӧ����HelloWorldHi��ʵ�������" << s1 << endl;
		s1.append("");
		cout << "s1Ӧ����HelloWorldHi��ʵ�������" << s1 << endl;
		s1.append(nullptr);
		cout << "s1Ӧ����HelloWorldHi��ʵ�������" << s1 << endl;
		s1.append('!');
		cout << "s1Ӧ����HelloWorldHi!��ʵ�������" << s1 << endl;

		wait_for_enter();
	}

	if (1) {
		TStringAdv s1("Tong"), s2("Ji"), s3;

		cout << "����(insert()����)����" << endl;

		s3.insert(s1, 1);
		cout << "s3ӦΪTong��            ʵ�������" << s3 << endl;

		s3.insert(" ", 5);
		s3.insert(s2, 6);
		cout << "s3ӦΪTong Ji��         ʵ�������" << s3 << endl;

		s3.insert('!', 8);
		cout << "s3ӦΪTong Ji!��        ʵ�������" << s3 << endl;

		s3.insert("JiaDing ", 6);
		cout << "s3ӦΪTong JiaDing Ji!��ʵ�������" << s3 << endl;

		s3.insert('\0', 5);
		cout << "s3ӦΪTong��            ʵ�������" << s3 << endl;

		s3.insert("", 1);
		cout << "s3ӦΪTong��            ʵ�������" << s3 << endl;

		s1 = "";
		s3.insert(s1, 1);
		cout << "s3ӦΪTong��            ʵ�������" << s3 << endl;

		s3.insert('\0', 1);
		cout << "s3ӦΪ<EMPTY>��         ʵ�������" << s3 << endl;

		// ���ԷǷ�����λ��
		s3.insert("Hello World!", 1);
		s3.insert("oop", 20); // Ӧ�ò����룬����ԭֵ
		cout << "s3ӦΪHello World!��    ʵ�������" << s3 << endl;

		s3.insert('*', 1);
		s3.insert("Error", -1); // Ӧ�ò����룬����ԭֵ
		cout << "s3ӦΪ*Hello World!��   ʵ�������" << s3 << endl;

		wait_for_enter();
	}

	if (1) {
		TStringAdv s1("HelloWorld"), s2("World");

		// erase ��������
		cout << "erase ��������" << endl;
		s1.erase(s2);
		cout << "s1Ӧ����Hello��ʵ�������" << s1 << endl;
		s1.erase("Hello");
		cout << "s1Ӧ����<EMPTY>��ʵ�������" << s1 << endl;
		s1 = "HelloWorld";
		s1.erase("");
		cout << "s1Ӧ����HelloWorld��ʵ�������" << s1 << endl;
		s1.erase(nullptr);
		cout << "s1Ӧ����HelloWorld��ʵ�������" << s1 << endl;
		s1.erase('o');
		cout << "s1Ӧ����HellWorld��ʵ�������" << s1 << endl;

		wait_for_enter();
	}

	if (1) {
		TStringAdv s1("HelloWorld");

		// substr ��������
		cout << "substr ��������" << endl;
		TStringAdv s2 = s1.substr(1, 5);
		cout << "s2Ӧ����Hello��ʵ�������" << s2 << endl;
		s2 = s1.substr(6);
		cout << "s2Ӧ����World��ʵ�������" << s2 << endl;
		s2 = s1.substr(0, 5);
		cout << "s2Ӧ����<EMPTY>��ʵ�������" << s2 << endl;
		s2 = s1.substr(10, 5);
		cout << "s2Ӧ����d��ʵ�������" << s2 << endl;
		s2 = s1.substr(1, 0);
		cout << "s2Ӧ����<EMPTY>��ʵ�������" << s2 << endl;
		s2 = s1.substr(1, -1);
		cout << "s2Ӧ����<EMPTY>��ʵ�������" << s2 << endl;

		wait_for_enter();
	}

	if (1) {
		TStringAdv s1("HelloWorld");

		// at ��������
		cout << "at ��������" << endl;
		cout << "s1[1]Ӧ����e��ʵ�������" << s1.at(1) << endl;
		cout << "s1[6]Ӧ����o��ʵ�������" << s1.at(6) << endl;
		cout << "s1[11]Ӧ���� ��ʵ�������" << s1.at(11) << endl;

		wait_for_enter();
	}

	if (1) {
		TStringAdv s1("HelloWorld");

		// TStringAdvLen ��������
		cout << "TStringAdvLen ��������" << endl;
		cout << "s1�ĳ���Ӧ����10��ʵ�������" << TStringAdvLen(s1) << endl;
		s1 = "";
		cout << "s1�ĳ���Ӧ����0��ʵ�������" << TStringAdvLen(s1) << endl;
		s1 = nullptr;
		cout << "s1�ĳ���Ӧ����0��ʵ�������" << TStringAdvLen(s1) << endl;

		wait_for_enter();
	}


#if !(defined(__linux) || defined(__linux__))
	system("pause"); //Linux����Ҫ
#endif

	return 0;
}
