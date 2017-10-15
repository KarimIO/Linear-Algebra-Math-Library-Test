#include "camera.hpp"
#include "utilities/transform.hpp"

Matrix Camera::getWVP() {
    Vector3 lookAt;
    Vector3 up = Vector3(0,1,0);
    position = Vector3(3,3,3);
    static float fov = toRadians(90.0f);
    static float ratio = 1024.0f / 768.0f;
    Matrix projection = perspective(0.1f, 100.0f, fov, ratio);
    Matrix viewMat = view(position, lookAt, up);
    Matrix world = getWorld();

    return projection * viewMat * world;
}

Matrix Camera::getWorld() {
    return Matrix();
}