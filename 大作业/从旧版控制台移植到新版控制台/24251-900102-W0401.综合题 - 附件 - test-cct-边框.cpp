/* -----------------------------------------

     ���ļ�����Ҫ�ύ��������Ķ�

   ----------------------------------------- */
#include <iostream>
#include <iomanip>
#include <ctime>
#include <cmath>
#include <cstdio>
#include <conio.h>
#include <Windows.h>
#include "../BigHW/include/cmd_console_tools.h"
using namespace std;

/***************************************************************************
  �������ƣ�
  ��    �ܣ���ʾ��ʾ��Ϣ
  ���������
  �� �� ֵ��
  ˵    �����������������ʱ���ţ���ָ�������ѧϰ��ɺ����Ķ�
***************************************************************************/
static void to_be_continued(const char *prompt, const int X = 0, const int Y = 22)
{
	cct_setcolor(); //�ָ�ȱʡ��ɫ
	cct_gotoxy(X, Y);

	if (prompt)
		cout << prompt << "�����س�������...";
	else
		cout << "���س�������...";

	/* ���Գ��س�������������루ע�⣺_getch�Ļس���\r����getchar��\n��*/
	while (_getch() != '\r')
		;

	cct_cls();

	return;
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ���ָ��λ�ã���ָ����ɫ����ʾһ���ַ����ɴ�
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
int main()
{
	

	/* �������͵Ŀ�ܣ�ÿ��11��Ԫ�أ�ÿ��Ԫ�ؾ�Ϊһ�������ַ���2�ֽڣ�
		˫�߿�ܣ�"�X", "�^", "�[", "�a", "�T", "�U", "�j", "�m", "�d", "�g", "�p"
		���߿�ܣ�"��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��"
		��˫����: "�V", "�\", "�Y", "�_", "�T", "��", "�h", "�k", "�b", "�e", "�n"
		�ᵥ��˫��"�W", "�]", "�Z", "�`", "��", "�U", "�i", "�l", "�c", "�f", "�o"

		˫�߿��ʹ���������������滻Ϊ�������ͣ�
		   �X�T�j�T�[
		   �U  �U  �U
		   �d�T�p�T�g
		   �U  �U  �U
		   �^�T�m�T�a  */

   /* ���������壬28���� */
	cct_setconsoleborder(80, 25);
	cct_setfontsize("������", 28); //Truetype����ֻ��Ҫ����һ�������߶ȼ���
	cout << "��������Ϊ������28" << endl << endl;
	const char* str = "��";
	cout << (int)(str[1]);
	to_be_continued("intֵ");
//	˫�߿�ܣ�"�X", "�^", "�[", "�a", "�T", "�U", "�j", "�m", "�d", "�g", "�p"
	cct_gotoxy(0, 5);
	cout << "**�X�T�j�T�[ ��" << endl;
	cout << "�ШU��U�ԨU**" << endl;
	cout << "**�d�T�p�T�g**" << endl;
	cout << "�ШUab�U12�U��" << endl;
	cout << "**�^�T�m�T�a��" << endl;
	to_be_continued("����������ɰ����̨���ң��°���...");

	cout << "**�X�T�T�j�T�T�[��" << endl;
	cout << "�ШU��U�ԨU**" << endl;
	cout << "**�d�T�T�p�T�T�g**" << endl;
	cout << "�ШUab�U12�U��" << endl;
	cout << "**�^�T�T�m�T�T�a��" << endl;
	to_be_continued("ÿ�����߷����ظ�������Σ��°治�ң���λ�ò���...");

	cct_gotoxy(0, 5);
	cout << "**�X �T �j �T �[ ��" << endl;
	cout << "�ШU ��U �ԨU **" << endl;
	cout << "**�d �T �p �T �g **" << endl;
	cout << "�ШU ab�U 12�U ��" << endl;
	cout << "**�^ �T �m �T �a ��" << endl;
	to_be_continued("ÿ�������Ʊ�������һ���ո񣬾ɰ����̨�ң��°治��...");

	cct_showstr(0, 5, "**�X�T�j�T�[��");
	cct_showstr(0, 6, "�ШU��U�ԨU**");
	cct_showstr(0, 7, "**�d�T�p�T�g**");
	cct_showstr(0, 8, "�ШUab�U12�U��");
	cct_showstr(0, 9, "**�^�T�m�T�a��");
	to_be_continued("������cct_showstr�����°����̨����...");

	return 0;
}
