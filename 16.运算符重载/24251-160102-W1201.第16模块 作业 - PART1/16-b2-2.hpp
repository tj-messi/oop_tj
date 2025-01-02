/*2351114 Öì¿¡Ôó ´óÊý¾Ý*/
#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <iostream>
#include <cstring>
using namespace std;

template <typename T, int ROW, int COL>
class matrix {
private:
    T value[ROW][COL];
public:
    matrix();                              
    matrix(const T(&p)[ROW][COL]);         

    matrix operator+(const matrix& b) const;

    template <typename U, int R, int C>
    friend ostream& operator<<(ostream& out, const matrix<U, R, C>& mat);

    template <typename U, int R, int C>
    friend istream& operator>>(istream& in, matrix<U, R, C>& mat);
};

template <typename T, int ROW, int COL>
matrix<T, ROW, COL>::matrix() {
    for (int i = 0; i < ROW; ++i)
        for (int j = 0; j < COL; ++j)
            value[i][j] = T();
}

template <typename T, int ROW, int COL>
matrix<T, ROW, COL>::matrix(const T(&p)[ROW][COL]) {
    for (int i = 0; i < ROW; ++i)
        for (int j = 0; j < COL; ++j)
            value[i][j] = p[i][j];
}

template <typename T, int ROW, int COL>
matrix<T, ROW, COL> matrix<T, ROW, COL>::operator+(const matrix& b) const {
    matrix result;
    for (int i = 0; i < ROW; ++i)
        for (int j = 0; j < COL; ++j)
            result.value[i][j] = this->value[i][j] + b.value[i][j];
    return result;
}

template <typename T, int ROW, int COL>
ostream& operator<<(ostream& out, const matrix<T, ROW, COL>& mat) {
    for (int i = 0; i < ROW; ++i) {
        for (int j = 0; j < COL; ++j) {
            out << mat.value[i][j] << " ";
        }
        out << endl;
    }
    return out;
}

template <typename T, int ROW, int COL>
istream& operator>>(istream& in, matrix<T, ROW, COL>& mat) {
    for (int i = 0; i < ROW; ++i)
        for (int j = 0; j < COL; ++j)
            in >> mat.value[i][j];
    return in;
}

#endif 
