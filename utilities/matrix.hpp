#ifndef MATRIX_HPP
#define MATRIX_HPP

#include "vector.hpp"

class Matrix {
public:
    Matrix();
    Matrix(Vector a1, Vector a2, Vector a3, Vector a4);
    Matrix(float a11, float a12, float a13, float a14, float a21, float a22, float a23, float a24, float a31, float a32, float a33, float a34, float a41, float a42, float a43, float a44);

    Matrix operator+(const Matrix &r);
    Matrix operator*(const Matrix &r);

    const float * const getMatrix();
    
private:
    float mat_[4][4];
};

#endif