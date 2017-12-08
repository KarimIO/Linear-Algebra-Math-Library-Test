#ifndef QUAT_HPP
#define QUAT_HPP

#include "matrix.hpp"
#include <cmath>

class Quaternion {
public:
    Quaternion() : x_(0), y_(0), z_(0), w_(0) {};
    Quaternion(float p, float y, float r) {
        float cy = cos(y * 0.5f);
        float sy = sin(y * 0.5f);
        float cr = cos(r * 0.5f);
        float sr = sin(r * 0.5f);
        float cp = cos(p * 0.5f);
        float sp = sin(p * 0.5f);

        w_ = cy * cr * cp + sy * sr * sp;
        x_ = cy * sr * cp - sy * cr * sp;
        y_ = cy * cr * sp + sy * sr * cp;
        z_ = sy * cr * cp - cy * sr * sp;
    };
    Quaternion(Vector3 angles) {
        float p = angles.X();
        float y = angles.Y();
        float r = angles.Z();
        float cy = cos(y * 0.5f);
        float sy = sin(y * 0.5f);
        float cr = cos(r * 0.5f);
        float sr = sin(r * 0.5f);
        float cp = cos(p * 0.5f);
        float sp = sin(p * 0.5f);

        w_ = cy * cr * cp + sy * sr * sp;
        x_ = cy * sr * cp - sy * cr * sp;
        y_ = cy * cr * sp + sy * sr * cp;
        z_ = sy * cr * cp - cy * sr * sp;
    };
    Quaternion(float x, float y, float z, float w) : x_(x), y_(y), z_(z), w_(w) {};
    Quaternion &operator+(const Quaternion &in) const {};
    operator Matrix() {
        float n = 1.0f / sqrt(x_*x_ + y_*y_ + z_*z_ + w_*w_);
        float qx = x_ * n;
        float qy = y_ * n;
        float qz = z_ * n;
        float qw = w_ * n;
        return Matrix(
            (1.0f - 2.0f*qy*qy - 2.0f*qz*qz), (2.0f*qx*qy - 2.0f*qz*qw), (2.0f*qx*qz + 2.0f*qy*qw), 0.0f,
            (2.0f*qx*qy + 2.0f*qz*qw), (1.0f - 2.0f*qx*qx - 2.0f*qz*qz), (2.0f*qy*qz - 2.0f*qx*qw), 0.0f,
            (2.0f*qx*qz - 2.0f*qy*qw), (2.0f*qy*qz + 2.0f*qx*qw), (1.0f - 2.0f*qx*qx - 2.0f*qy*qy), 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f
        );
    };
private:
    float x_, y_, z_, w_;
};

#endif