#include "transform.hpp"
#include <cmath>

Matrix perspective(float near, float far, float fov, float ratio) {
    float ty = tan(fov/2);
    float tx = ratio * ty;
    return Matrix(  tx, 0, 0, 0,
                    0, ty, 0, 0,
                    0, 0, -(far + near) / (far - near), (-2 * near * far)/(far - near),
                    0, 0, -1, 0);
}

Matrix orthographic(float near, float far, float width, float height) {
    return Matrix(  1/width, 0, 0, 0,
                    0, 1/height, 0, 0,
                    0, 0, -2 * (far - near), (-far - near)/(far - near),
                    0, 0, 0, 1);
}

Matrix view(Vector3 position, Vector3 target, Vector3 upVec) {
    Vector3 forward = normalize(position - target);
    Vector3 right   = normalize(cross(upVec, forward));
    Vector3 up      = cross(forward, right);

    Matrix orientation( right.X(), up.X(), forward.X(), 0,
                        right.Y(), up.Y(), forward.Y(), 0,
                        right.Z(), up.Z(), forward.Z(), 0,
                        0, 0, 0, 1);

    Matrix invTrans(1,0,0,0,
                    0,1,0,0,
                    0,0,1,0,
                    -position.X(), -position.Y(), -position.Z(), 1);
    return orientation * invTrans;
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

Vector3 normalize(Vector3 in) {
    float x = in.X();
    float y = in.Y();
    float z = in.Z();
    float length = x*x+y*y+z*z;
    return Vector3(x/length, y/length, z/length);
}

float toRadians(float degrees) {
    return degrees * 3.14159f / 180.0f;
}