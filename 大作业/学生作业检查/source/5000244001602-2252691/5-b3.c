#include <stdio.h>

int is_leap(int year) {
    // �����жϣ�����1��ʾ���꣬0��ʾƽ��
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
