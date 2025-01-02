/* 2150792 �ƿ� ţ»�� */
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
    T** value;           // ���ö�̬����
public:

    // ���캯��
    matrix() 
    {
        value = new(nothrow) T* [ROW];
        if (value == NULL)
            exit(-1);
        for (int i = 0; i < ROW; ++i) 
        {
            value[i] = new(nothrow) T[COL];
            if (value[i] == NULL) 
            {   // �����ѷ�����ڴ�
                for (int j = 0; j < i; ++j) 
                    delete[] value[j];
                delete[] value;
                exit(-1);
            }

            // ��ʼ������Ԫ��
            for (int j = 0; j < COL; ++j) 
                value[i][j] = T();  // ʹ��Ĭ�Ϲ��캯����ʼ��
        }
    }

    // ��������
    ~matrix() 
    {
        for (int i = 0; i < ROW; ++i)
            delete[] value[i];
        delete[] value;
    }

    // ���ƹ��캯��
    matrix(const matrix& other)
    {
        value = new(nothrow) T * [ROW];
        if (value == NULL)
            exit(-1);
        for (int i = 0; i < ROW; ++i) 
        {
            value[i] = new(nothrow) T[COL];
            if (value[i] == NULL)
            {   // �����ѷ�����ڴ�
                for (int j = 0; j < i; ++j)
                    delete[] value[j];
                delete[] value;
                exit(-1);
            }
            for (int j = 0; j < COL; ++j) 
                value[i][j] = other.value[i][j];
        }
    }

    // ����>>����
    friend istream& operator>>(istream& in, matrix& m)
    {
        for (int i = 0; i < ROW; ++i)
            for (int j = 0; j < COL; ++j)
                in >> m.value[i][j];
        return in;
    }

    // ����<<���
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

    // ����=��ֵ���������Ϊ�������ݳ�Ա������̬������ڴ�ָ��
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
    //����+�ĳ�Ա����ʵ�ַ�ʽ������
    matrix<T, ROW, COL> operator+(const matrix< T, ROW, COL>& other) const;
#else
    //����+����Ԫ����ʵ�ַ�ʽ������
    template<typename T, const int ROW, const int COL>
    friend matrix<T, ROW, COL> operator+(const matrix<T, ROW, COL>& a, const matrix<T, ROW, COL>& b);
#endif
};

#if OPERATOR_IS_MENBER_FUNCTION
//����+�ĳ�Ա������ʽ������ʵ��
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
//����+����Ԫ������ʽ������ʵ��
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
