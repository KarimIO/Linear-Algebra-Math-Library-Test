#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "utilities/matrix.hpp"
#include "utilities/vector.hpp"

class Camera {
public:
    Matrix getWVP();
    Matrix getWorld();
private:
    Vector3 position;
};

#endif