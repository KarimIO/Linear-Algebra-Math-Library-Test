#include "transform.hpp"
#include <cmath>
#include <iostream>
#include <stdio.h>

Matrix inverse(const Matrix &m) {
    // Insert Inverse Code Here
    return Matrix(1.0f);
}

Matrix transpose(const Matrix &m) {
    return Matrix(
        m[0][0], m[1][0], m[2][0], m[3][0],
        m[0][1], m[1][1], m[2][1], m[3][1],
        m[0][2], m[1][2], m[2][2], m[3][2],
        m[0][3], m[1][3], m[2][3], m[3][3]);
}

Matrix perspective(float near, float far, float fov, float ratio) {
    float ty = tan(fov/2);
    float tx = ratio * ty;
    return Matrix(  1.0f/tx, 0, 0, 0,
                    0, 1.0f/ty, 0, 0,
                    0, 0, -(far + near) / (far - near), (-2.0f * near * far)/(far - near),
                    0, 0, -1.0f, 0);
}

Matrix orthographic(float near, float far, float width, float height) {
    return Matrix(  1/width, 0, 0, 0,
                    0, 1/height, 0, 0,
                    0, 0, -2 * (far - near), (-far - near)/(far - near),
                    0, 0, 0, 1);
}

Matrix view(Vector3 position, Vector3 target, Vector3 upVec) {
    Vector3 forward = normalize(target - position);
    Vector3 right   = normalize(cross(forward, upVec));
    Vector3 up      = cross(right, forward);

    float dotr = -dot(right, position);
    float dotu = -dot(up, position);
    float dotf = dot(forward, position);

    return Matrix(  right.X(), right.Y(), right.Z(), dotr,
    up.X(), up.Y(), up.Z(), dotu,
    -forward.X(), -forward.Y(), -forward.Z(), dotf,
    0, 0, 0, 1);
}

Matrix world(Vector3 translation, Vector3 rotation, Vector3 scaling) {
    return translate(translation) * rotate(rotation) * scale(scaling);
}

Matrix translate(Vector3 a) {
    return Matrix(  1, 0, 0, a.X(),
                    0, 1, 0, a.Y(),
                    0, 0, 1, a.Z(),
                    0, 0, 0, 1);
}

Matrix rotate(Vector3 amount) {
    return Matrix();
}

Matrix scale(Vector3 a) {
    return Matrix(  a.X(), 0, 0, 0,
                    0, a.Y(), 0, 0,
                    0, 0, a.Z(), 0,
                    0, 0, 0, 1);
}

Vector3 cross(Vector3 a, Vector3 b) {
    return Vector3(a.Y()*b.Z() - a.Z()*b.Y(), a.Z()*b.X() - a.X()*b.Z(), a.X()*b.Y() - a.Y()*b.X());
}

float dot(Vector3 a, Vector3 b) {
    return a.X() * b.X() + a.Y() * b.Y() + a.Z() * b.Z();
}

Vector3 normalize(Vector3 in) {
    float x = in.X();
    float y = in.Y();
    float z = in.Z();
    float length = sqrt(x*x+y*y+z*z); // Use dot instead
    return Vector3(x/length, y/length, z/length);
}

float toRadians(float degrees) {
    return degrees * 3.14159f / 180.0f;
}