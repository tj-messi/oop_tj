/*2351114 �쿡�� ������*/
#include "16-b6.h"
#include <algorithm> // ���� std::transform

// �������������ַ���ת��ΪСд
std::string to_lower(const std::string& str) {
    std::string lower_str = str;
    std::transform(lower_str.begin(), lower_str.end(), lower_str.begin(), ::tolower);
    return lower_str;
}

// ����ת�� week ���ַ����ĸ�������
static const std::string week_names[] = {
    "������", "����һ", "���ڶ�", "������", "������", "������", "������"
};
static const std::string week_abbr[] = {
    "sun", "mon", "tue", "wed", "thu", "fri", "sat"
};

// week ������������
std::ostream& operator<<(std::ostream& os, const week& w) {
    int value = static_cast<int>(w);
    
    if (-858993460 == value)
    {
        os << "���";
        return os;
    }

    if (value < 0 || value > 6) {
        os << "����";
    } else {
        os << week_names[value];
    }
    return os;
}

// week �������������
std::istream& operator>>(std::istream& is, week& w) {
    std::string input;
    is >> input;
    input = to_lower(input); // ������ͳһתΪСд

    for (int i = 0; i < 7; ++i) {
        if (input == week_abbr[i]) {
            w = static_cast<week>(i);
            return is;
        }
    }

    w = static_cast<week>(-1); // ����Ϊ�Ƿ�ֵ
    is.clear();                // �������״̬����������������
    return is;
}

// ǰ��++
week operator++(week& w) {
    w = static_cast<week>((static_cast<int>(w) + 1) % 7);
    return w;
}

// ����++
week operator++(week& w, int) {
    week temp = w;
    w = static_cast<week>((static_cast<int>(w) + 1) % 7);
    return temp;
}

// ǰ��--
week operator--(week& w) {
    w = static_cast<week>((static_cast<int>(w) + 6) % 7);
    return w;
}

// ����--
week operator--(week& w, int) {
    week temp = w;
    w = static_cast<week>((static_cast<int>(w) + 6) % 7);
    return temp;
}

// + ������
week operator+(const week& w, int n) {
    return static_cast<week>((static_cast<int>(w) + n % 7 + 7) % 7);
}

// - ������
week operator-(const week& w, int n) {
    return static_cast<week>((static_cast<int>(w) - n % 7 + 7) % 7);
}

// += ������
week& operator+=(week& w, int n) {
    w = w + n;
    return w;
}

// -= ������
week& operator-=(week& w, int n) {
    w = w - n;
    return w;
}
