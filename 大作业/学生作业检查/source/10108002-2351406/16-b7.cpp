#include "16-b7.h"

// 输出 week 枚举类型
ostream& operator<<(ostream& os, const week& w) {
    static const char* names[] = { "星期日", "星期一", "星期二", "星期三", "星期四", "星期五", "星期六" };
