#include "camera.hpp"
#include "utilities/transform.hpp"

#include <iostream>
#include <stdio.h>
#include <cmath>

Camera::Camera() {
    position = Vector3(0.0f, 0.0f, -2.0f);
    angles = Vector3(0.0f, 0.0f, 0.0f);    
}

void Camera::Move(Vector3 offset, double mx, double my) {
    Vector3 forward = GetForward();
    Vector3 right   = normalize(cross(forward, Vector3(0,1,0)));
    Vector3 up      = cross(right, forward);
    Vector3 worldOffset = forward * offset.Z() + up * offset.Y() + right * offset.X();

    position = position + worldOffset * 10.0f;
    angles[0] -= tan(my)*0.2f;
    angles[1] -= tan(mx)*0.2f;
}

Vector3 Camera::GetForward() {
    return Vector3(cos(angles.X()) * sin(angles.Y()), sin(angles.X()), cos(angles.X()) * cos(angles.Y()));
}

Matrix Camera::getVP() {
    Vector3 up = Vector3(0,1,0);
    static float fov = 45.0f;
    static float ratio = 1024.0f / 768.0f;

    Matrix projection = perspective(0.1f, 100.0f, fov, ratio);
    Matrix viewMat = view(position, position + GetForward(), up);
    
    return projection * viewMat;
}