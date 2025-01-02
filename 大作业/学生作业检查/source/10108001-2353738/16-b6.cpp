/* 2353738 姜观博 计科 */
#include "16-b6.h"
#include <ctime>
ostream& operator<<(ostream& os, const week& w) {
    static const char* names[] = { "星期日", "星期一", "星期二", "星期三", "星期四", "星期五", "星期六", "错误" };
