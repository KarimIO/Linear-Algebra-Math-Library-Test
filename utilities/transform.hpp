#ifndef TRANSFORM_HPP
#define TRANSFORM_HPP

#include "matrix.hpp"
#include "vector.hpp"

Matrix transpose(const Matrix &m);
Matrix perspective(float near, float far, float fovX, float fovY);
Matrix orthographic(float near, float far, float width, float height);
Matrix view(Vector3 position, Vector3 forward, Vector3 up);
Matrix world(Vector3 translate, Vector3 rotation, Vector3 scaling);
Matrix translate(Vector3 a);
Matrix rotate(Vector3 a);
Matrix scale(Vector3 a);
float toRadians(float degrees);
Vector3 normalize(Vector3);
Vector3 cross(Vector3 a, Vector3 b);
float dot(Vector3 a, Vector3 b);

#endif