#include <stdio.h>

int zeller(int y, int m, int d) {
    if (m < 3) {
        m += 12; // ��1�º�2�¿�����һ���13�º�14��
