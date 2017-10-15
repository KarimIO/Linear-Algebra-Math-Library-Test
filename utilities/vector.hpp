#ifndef VECTOR_HPP
#define VECTOR_HPP

class Vector {
public:
    Vector() : vector_{0,0,0,0} {};
    Vector(float x, float y, float z, float w) : vector_{x,y,z,w} {};
    Vector operator-(const Vector &in) {
        vector_[0] -= in.X();
        vector_[1] -= in.Y();
        vector_[2] -= in.Z();
        vector_[3] -= in.W();
    };
    Vector operator+(const Vector &in) {
        vector_[0] += in.X();
        vector_[1] += in.Y();
        vector_[2] += in.Z();
        vector_[3] += in.W();
    };
    inline float X() const {return vector_[0];};
    inline float Y() const {return vector_[1];};
    inline float Z() const {return vector_[2];};
    inline float W() const {return vector_[3];};
private:
    float vector_[4];
};

class Vector3 {
public:
    Vector3() : vector_{0,0,0} {};
    Vector3(float x, float y, float z) : vector_{x,y,z} {};
    Vector3 operator-(const Vector3 &in) {
        vector_[0] -= in.X();
        vector_[1] -= in.Y();
        vector_[2] -= in.Z();
    };
    Vector3 operator+(const Vector3 &in) {
        vector_[0] += in.X();
        vector_[1] += in.Y();
        vector_[2] += in.Z();
    };
    inline float X() const {return vector_[0];};
    inline float Y() const {return vector_[1];};
    inline float Z() const {return vector_[2];};
private:
    float vector_[3];
};

#endif