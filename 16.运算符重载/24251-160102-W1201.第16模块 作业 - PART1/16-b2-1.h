#pragma once

/* ROW �� COL �ᱻ�滻Ϊ����ֵ */
const int ROW = 2;
const int COL = 3;

/* �궨���ֵ����0/1֮��������� */
#define OPERATOR_IS_MENBER_FUNCTION		1	//������������ó�Ա������ʽʵ�֣����ֵΪ0����ʾ����Ԫ��ʽʵ�֣�

/* Ϊ�˲��ԣ��˴�ֻ����ȫ�ֱ�����Ϊ����Ȩ�ޣ�ʹ�þ�̬ȫ�� */
static int a[ROW][COL] = { { 1,2,3 },{ 4,5,6 } };
static int b[ROW][COL] = { { 2,4,6 },{ 3,6,9 } };

//���ļ�����Ҫ�ύ���Լ�����ʱ��������Ķ�
