#include "matrix.hpp"
#include <iostream>

Matrix::Matrix(float i) : mat_ {
    {i, 0.0f, 0.0f, 0.0f},
    {0.0f, i, 0.0f, 0.0f},
    {0.0f, 0.0f, i, 0.0f},
    {0.0f, 0.0f, 0.0f, i}
} {

}

const float * const Matrix::getMatrix() {
    return &mat_[0][0];
}

/*Matrix::Matrix(Vector a1, Vector a2, Vector a3, Vector a4) : mat_ {
    {a1.X(), a1.Y(), a1.Z(), a1.W()},
    {a2.X(), a2.Y(), a2.Z(), a2.W()},
    {a3.X(), a3.Y(), a3.Z(), a3.W()},
    {a4.X(), a4.Y(), a4.Z(), a4.W()}} {

}*/

Matrix::Matrix( float a11, float a12, float a13, float a14,
                float a21, float a22, float a23, float a24,
                float a31, float a32, float a33, float a34,
                float a41, float a42, float a43, float a44) : mat_ {
                    a11, a12, a13, a14,
                    a21, a22, a23, a24,
                    a31, a32, a33, a34,
                    a41, a42, a43, a44
                } {

}

Matrix Matrix::operator+(const Matrix &r) const {
    Matrix out;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            out[i][j] = mat_[i][j] + r.mat_[i][j];
        }
    }

    return out;
}

Matrix Matrix::operator-(const Matrix &r) const {
    Matrix out;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            out[i][j] = mat_[i][j] - r.mat_[i][j];
        }
    }

    return out;
}

Matrix Matrix::operator*(const Matrix &r) const {
    Matrix out;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            out[i][j] = mat_[i][0] * r.mat_[0][j];
            for (int k = 1; k < 4; ++k) {
                out[i][j] += mat_[i][k] * r.mat_[k][j];
            }
        }
    }
    return out;
}

void Matrix::print() const {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            std::cout << mat_[i][j] << " ";
        }
        std::cout << "\n";
    }
}

float* Matrix::operator[](long unsigned int p) {
    return mat_[p];
}

const float* Matrix::operator[](long unsigned int p) const {
    return mat_[p];
}