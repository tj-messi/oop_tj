#include <stdio.h>

int is_leap(int year) {
    // 闰年判断，返回1表示闰年，0表示平年
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
