/* 2351584 ÐÅ°² ºú½ÝÃù */
#include "16-b4.h"

bool isLeapYear(int y) {
    return (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0);
