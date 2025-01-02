/* 2150792 计科 牛禄阳 */
#ifndef MATRIX_ADDITION_HPP
#define MATRIX_ADDITION_HPP
#include <iostream>
#include <string>
#include <cstring>
using namespace std;

#define OPERATOR_IS_MENBER_FUNCTION		1	

template<typename T, const int ROW, const int COL>
class matrix {
private:
    // T value[ROW][COL];
    T** value;           // 采用动态分配
public:

    // 构造函数
    matrix() 
    {
        value = new(nothrow) T* [ROW];
        if (value == NULL)
            exit(-1);
        for (int i = 0; i < ROW; ++i) 
        {
            value[i] = new(nothrow) T[COL];
            if (value[i] == NULL) 
            {   // 清理已分配的内存
                for (int j = 0; j < i; ++j) 
                    delete[] value[j];
                delete[] value;
                exit(-1);
            }

            // 初始化矩阵元素
            for (int j = 0; j < COL; ++j) 
                value[i][j] = T();  // 使用默认构造函数初始化
        }
    }

    // 析构函数
    ~matrix() 
    {
        for (int i = 0; i < ROW; ++i)
            delete[] value[i];
        delete[] value;
    }

    // 复制构造函数
    matrix(const matrix& other)
    {
        value = new(nothrow) T * [ROW];
        if (value == NULL)
            exit(-1);
        for (int i = 0; i < ROW; ++i) 
        {
            value[i] = new(nothrow) T[COL];
            if (value[i] == NULL)
            {   // 清理已分配的内存
                for (int j = 0; j < i; ++j)
                    delete[] value[j];
                delete[] value;
                exit(-1);
            }
            for (int j = 0; j < COL; ++j) 
                value[i][j] = other.value[i][j];
        }
    }

    // 重载>>输入
    friend istream& operator>>(istream& in, matrix& m)
    {
        for (int i = 0; i < ROW; ++i)
            for (int j = 0; j < COL; ++j)
                in >> m.value[i][j];
        return in;
    }

    // 重载<<输出
    friend ostream& operator<<(ostream& out, const matrix& m) 
    {
        for (int i = 0; i < ROW; ++i) 
        {
            for (int j = 0; j < COL; ++j)
            {
                out << m.value[i][j] << ' ';
            }
            out << endl;
        }
        return out;
    }

    // 重载=赋值运算符，因为对象数据成员包含动态申请的内存指针
    matrix& operator=(const matrix& other) 
    {
        if (this != &other) 
        {
            for (int i = 0; i < ROW; ++i) 
            {
                delete[] value[i];
            }
            delete[] value;

            value = new T * [ROW];
            for (int i = 0; i < ROW; ++i) 
            {
                value[i] = new T[COL];
                for (int j = 0; j < COL; ++j) 
                    value[i][j] = other.value[i][j];
            }
        }
        return *this;
    }

#if OPERATOR_IS_MENBER_FUNCTION
    //给出+的成员函数实现方式的声明
    matrix<T, ROW, COL> operator+(const matrix< T, ROW, COL>& other) const;
#else
    //给出+的友元函数实现方式的声明
    template<typename T, const int ROW, const int COL>
    friend matrix<T, ROW, COL> operator+(const matrix<T, ROW, COL>& a, const matrix<T, ROW, COL>& b);
#endif
};

#if OPERATOR_IS_MENBER_FUNCTION
//给出+的成员函数方式的体外实现
template<typename T, const int ROW, const int COL>
matrix<T, ROW, COL> matrix<T, ROW, COL>::operator+(const matrix< T, ROW, COL>& other) const
{
    matrix result;
    for (int i = 0; i < ROW; ++i) 
        for (int j = 0; j < COL; ++j)
            result.value[i][j] = value[i][j] + other.value[i][j];
    return result;
}
#else
//给出+的友元函数方式的体外实现
template<typename T, const int ROW, const int COL>
matrix<T, ROW, COL> operator+(const matrix<T, ROW, COL>& a, const matrix<T, ROW, COL>& b)
{
    matrix result;
    for (int i = 0; i < ROW; i++)
        for (int j = 0; j < COL; j++)
            result.value[i][j] = a.value[i][j] + b.value[i][j];
    return result;
}
#endif // OPERATOR_IS_MENBER_FUNCTION

#endif // MATRIX_ADDITION_HPP
