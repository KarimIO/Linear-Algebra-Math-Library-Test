#ifndef OBJECT_HPP_
#define OBJECT_HPP_

#include "utilities/matrix.hpp"
#include "utilities/vector.hpp"

class Object {
public:
    Object();
    Object(const Vector3 vertices[], unsigned int num_vertices, Vector3 position = Vector3(0,0,0), Vector3 scale = Vector3(1, 1, 1), Vector3 angles = Vector3(0,0,0));

    void Draw(unsigned int world_matrix_uniform_location_);

    void SetPosition(Vector3 position);
    void SetPosition(float x, float y, float z);
    void SetAngles(Vector3 angles);
    void SetAngles(float x, float y, float z);
    void SetScale(Vector3 scale);
    void SetScale(float x, float y, float z);

    Vector3 GetPosition() const;
    Vector3 GetAngles() const;
    Vector3 GetScale() const;
    Matrix GetWorldMatrix();

    void GenerateWorldMatrix();

    ~Object();
private:
    bool should_update_world_;
    Vector3 position_;
    Vector3 scale_;
    Vector3 angles_;
    Matrix  world_;

    unsigned int num_vertices_;
    unsigned int vao_;
    unsigned int vbo_;
};

#endif