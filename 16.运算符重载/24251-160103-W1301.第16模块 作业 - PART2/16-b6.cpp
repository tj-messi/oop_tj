/*2351114 朱俊泽 大数据*/
#include "16-b6.h"
#include <algorithm> // 用于 std::transform

// 辅助函数：将字符串转换为小写
std::string to_lower(const std::string& str) {
    std::string lower_str = str;
    std::transform(lower_str.begin(), lower_str.end(), lower_str.begin(), ::tolower);
    return lower_str;
}

// 用于转换 week 到字符串的辅助数组
static const std::string week_names[] = {
    "星期日", "星期一", "星期二", "星期三", "星期四", "星期五", "星期六"
};
static const std::string week_abbr[] = {
    "sun", "mon", "tue", "wed", "thu", "fri", "sat"
};

// week 对象的输出重载
std::ostream& operator<<(std::ostream& os, const week& w) {
    int value = static_cast<int>(w);
    
    if (-858993460 == value)
    {
        os << "随机";
        return os;
    }

    if (value < 0 || value > 6) {
        os << "错误";
    } else {
        os << week_names[value];
    }
    return os;
}

// week 对象的输入重载
std::istream& operator>>(std::istream& is, week& w) {
    std::string input;
    is >> input;
    input = to_lower(input); // 将输入统一转为小写

    for (int i = 0; i < 7; ++i) {
        if (input == week_abbr[i]) {
            w = static_cast<week>(i);
            return is;
        }
    }

    w = static_cast<week>(-1); // 设置为非法值
    is.clear();                // 清除错误状态，允许程序继续运行
    return is;
}

// 前置++
week operator++(week& w) {
    w = static_cast<week>((static_cast<int>(w) + 1) % 7);
    return w;
}

// 后置++
week operator++(week& w, int) {
    week temp = w;
    w = static_cast<week>((static_cast<int>(w) + 1) % 7);
    return temp;
}

// 前置--
week operator--(week& w) {
    w = static_cast<week>((static_cast<int>(w) + 6) % 7);
    return w;
}

// 后置--
week operator--(week& w, int) {
    week temp = w;
    w = static_cast<week>((static_cast<int>(w) + 6) % 7);
    return temp;
}

// + 操作符
week operator+(const week& w, int n) {
    return static_cast<week>((static_cast<int>(w) + n % 7 + 7) % 7);
}

// - 操作符
week operator-(const week& w, int n) {
    return static_cast<week>((static_cast<int>(w) - n % 7 + 7) % 7);
}

// += 操作符
week& operator+=(week& w, int n) {
    w = w + n;
    return w;
}

// -= 操作符
week& operator-=(week& w, int n) {
    w = w - n;
    return w;
}
