#include <stdio.h>
#include <string.h>

void rotateString(const char* src, char* dest, int n, int m) {
    m = m % n;  // ��ֹ m �����ַ�������
