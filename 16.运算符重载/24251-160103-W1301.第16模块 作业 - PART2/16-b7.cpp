/*2351114 �쿡�� ������*/
#include "16-b7.h"
#include <algorithm> // for std::transform

static const string weekNames[] = { "������", "����һ", "���ڶ�", "������", "������", "������", "������" };

// ���������������
ostream& operator<<(ostream& os, const week& w) {
    if (static_cast<int>(w) == -858993460)
    {
        os << "���";
        return os;
    }
    if (w >= sun && w <= sat) {
        os << weekNames[w];
    }
    else {
        os << "����";
    }
    return os;
}


istream& operator>>(istream& is, week& w) {
    string input;
    is >> input;

    // תΪСд
    transform(input.begin(), input.end(), input.begin(), ::tolower);

    // ƥ����������
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
        w = static_cast<week>(-1); // ��Чֵ
    }

    return is;
}


// ǰ��++
week& operator++(week& w) {
    w = static_cast<week>((w + 1) % 7);
    return w;
}

// ����++
week operator++(week& w, int) {
    week temp = w;
    ++w;
    return temp;
}

// ǰ��--
week& operator--(week& w) {
    w = static_cast<week>((w + 6) % 7); // �൱�� (w - 1 + 7) % 7
    return w;
}

// ����--
week operator--(week& w, int) {
    week temp = w;
    --w;
    return temp;
}

// �ӷ�������
week operator+(const week& w, int n) {
    // ʹ����ȷ�ļ����߼�����ݹ����
    int result = (static_cast<int>(w) + n % 7 + 7) % 7;
    return static_cast<week>(result);
}

// ����������
week operator-(const week& w, int n) {
    // ʹ����ȷ�ļ����߼�����ݹ����
    int result = (static_cast<int>(w) - n % 7 + 7) % 7;
    return static_cast<week>(result);
}


// �ӵȲ�����
week& operator+=(week& w, int n) {
    w = w + n;
    return w;
}

// ���Ȳ�����
week& operator-=(week& w, int n) {
    w = w - n;
    return w;
}
