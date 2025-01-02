/*2351114 朱俊泽 大数据*/
#include "17-b1-TStringAdv.h"

// Constructors
TStringAdv::TStringAdv() : TString() {}
TStringAdv::TStringAdv(const char* s) : TString(s) {}
TStringAdv::TStringAdv(const TString& s) : TString(s) {}
TStringAdv::TStringAdv(const TStringAdv& s) : TString(s) {}

// Assign methods
TStringAdv& TStringAdv::assign(const TStringAdv& ts2) {
    *this = ts2;
    return *this;
}
TStringAdv& TStringAdv::assign(const char* s) {
    *this = s;
    return *this;
}

// Append methods
TStringAdv& TStringAdv::append(const TStringAdv& ts2) {
    *this += ts2;
    return *this;
}
TStringAdv& TStringAdv::append(const char* s) {
    *this += s;
    return *this;
}
TStringAdv& TStringAdv::append(const char& c) {
    *this += c;
    return *this;
}

// Insert methods
TStringAdv& TStringAdv::insert(const TStringAdv& ts2, int pos) {
    if (pos < 1 || pos > length() + 1 || ts2.length() == 0) {
        // 插入位置非法或字符串为空，返回原值
        return *this;
    }

    if (ts2.c_str()[0] == '\0') {
        // 插入尾零处理：释放后续内容
        if (pos == 1) {
            delete[] content;
            content = nullptr;
            len = 0;
        }
        else {
            content[pos - 1] = '\0'; // 截断字符串
            len = pos - 1;
        }
        return *this;
    }

    // 插入逻辑
    TString left = substr(1, pos - 1);
    TString right = substr(pos,length());
    *this = left + ts2 + right;
    return *this;
}

TStringAdv& TStringAdv::insert(const char* s, int pos) {
    return insert(TStringAdv(s), pos);
}

TStringAdv& TStringAdv::insert(const char& c, int pos) {
    if (pos < 1 || pos > length() + 1) {
        // 插入位置非法，直接返回原值
        return *this;
    }

    if (c == '\0') {
        // 插入尾零：释放后续内容
        if (pos == 1) {
            delete[] content;
            content = nullptr;
            len = 0;
        }
        else {
            content[pos - 1] = '\0'; // 截断字符串
            len = pos - 1;
        }
        return *this;
    }

    // 插入单字符
    TString left = substr(1, pos - 1); // 左段内容
    TString right = substr(pos,length());      // 右段内容
    *this = left + c + right;         // 拼接
    return *this;
}


// Erase methods
TStringAdv& TStringAdv::erase(const TStringAdv& ts2) {
    if (length() == 0 || ts2.length() == 0) {
        return *this; // 如果原字符串或目标子串为空，直接返回
    }

    const char* found = std::strstr(c_str(), ts2.c_str());
    if (found) {
        // 将 const char* 转为 char*，通过偏移量操作原始内容
        char* writableFound = content + (found - c_str());
        std::memmove(writableFound, writableFound + ts2.length(), strlen(writableFound + ts2.length()) + 1);
    }

    return *this;
}


TStringAdv& TStringAdv::erase(const char* s) {
    *this -= s;
    return *this;
}
TStringAdv& TStringAdv::erase(const char& c) {
    *this -= c;
    return *this;
}

// Access character method
char& TStringAdv::at(const int n) {
    static char c = ' ';
    if (n < 0 || n > length()) return c;
    return (*this)[n];
}

// Substring method
TStringAdv TStringAdv::substr(const int pos, const int len) const {
    int effectiveLen = (len == SUBSTRMAXNUM) ? length() - pos + 1 : len; // 使用默认逻辑
    if (pos < 1 || pos > length() || effectiveLen <= 0) {
        return TStringAdv(); // 返回空串
    }
    if (pos + len  > length())
    {
        int effectiveLen = length() - pos + 1;
        TStringAdv result;
        for (int i = pos - 1; i < pos - 1 + effectiveLen; ++i) {
            result += (*this)[i];
        }
        return result;
    }
    TStringAdv result;
    for (int i = pos - 1; i < pos - 1 + effectiveLen; ++i) {
        result += (*this)[i];
    }
    return result;
}



// Length function equivalent
int TStringAdvLen(const TString& obj) {
    return obj.length();  // 调用 TString 的 length() 函数
}