#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "utilities/matrix.hpp"
#include "utilities/vector.hpp"

class Camera {
public:
    Camera();
    Matrix getProj();
    Matrix getView();
    Vector3 GetForward();
    void Move(Vector3 offset, double mx, double my);
private:
    Vector3 position;
    Vector3 angles;
};

#endif