/*2351114 朱俊泽 大数据*/
#include "16-b7.h"
#include <algorithm> // for std::transform

static const string weekNames[] = { "星期日", "星期一", "星期二", "星期三", "星期四", "星期五", "星期六" };

// 重载输出流操作符
ostream& operator<<(ostream& os, const week& w) {
    if (static_cast<int>(w) == -858993460)
    {
        os << "随机";
        return os;
    }
    if (w >= sun && w <= sat) {
        os << weekNames[w];
    }
    else {
        os << "错误";
    }
    return os;
}


istream& operator>>(istream& is, week& w) {
    string input;
    is >> input;

    // 转为小写
    transform(input.begin(), input.end(), input.begin(), ::tolower);

    // 匹配输入内容
    if (input == "sun") {
        w = sun;
    }
    else if (input == "mon") {
        w = mon;
    }
    else if (input == "tue") {
        w = tue;
    }
    else if (input == "wed") {
        w = wed;
    }
    else if (input == "thu") {
        w = thu;
    }
    else if (input == "fri") {
        w = fri;
    }
    else if (input == "sat") {
        w = sat;
    }
    else {
        w = static_cast<week>(-1); // 无效值
    }

    return is;
}


// 前置++
week& operator++(week& w) {
    w = static_cast<week>((w + 1) % 7);
    return w;
}

// 后置++
week operator++(week& w, int) {
    week temp = w;
    ++w;
    return temp;
}

// 前置--
week& operator--(week& w) {
    w = static_cast<week>((w + 6) % 7); // 相当于 (w - 1 + 7) % 7
    return w;
}

// 后置--
week operator--(week& w, int) {
    week temp = w;
    --w;
    return temp;
}

// 加法操作符
week operator+(const week& w, int n) {
    // 使用明确的计算逻辑避免递归调用
    int result = (static_cast<int>(w) + n % 7 + 7) % 7;
    return static_cast<week>(result);
}

// 减法操作符
week operator-(const week& w, int n) {
    // 使用明确的计算逻辑避免递归调用
    int result = (static_cast<int>(w) - n % 7 + 7) % 7;
    return static_cast<week>(result);
}


// 加等操作符
week& operator+=(week& w, int n) {
    w = w + n;
    return w;
}

// 减等操作符
week& operator-=(week& w, int n) {
    w = w - n;
    return w;
}
