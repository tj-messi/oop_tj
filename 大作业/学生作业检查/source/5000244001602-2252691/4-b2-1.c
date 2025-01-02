#include <stdio.h>

int zeller(int y, int m, int d) {
    if (m < 3) {
        m += 12; // 把1月和2月看作上一年的13月和14月
