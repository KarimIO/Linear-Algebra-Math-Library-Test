#include "object.hpp"
#include <GL/gl3w.h>
#include <stdio.h>

#include "utilities/transform.hpp"

Object::Object() {

}

Object::Object(const Vector3 vertices[], unsigned int num_vertices, Vector3 position, Vector3 scale, Vector3 angles) {
    position_ = position;
    scale_ = scale;
    angles_ = angles;
    GenerateWorldMatrix();

    num_vertices_ = num_vertices;

    glGenVertexArrays(1, &vao_);
	glBindVertexArray(vao_);
	glGenBuffers(1, &vbo_);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_);
	glBufferData(GL_ARRAY_BUFFER, num_vertices * 3 * sizeof(float), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(
	   0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
	   3,                  // size
	   GL_FLOAT,           // type
	   GL_FALSE,           // normalized?
	   0,                  // stride
	   (void*)0            // array buffer offset
	);
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);
}

void Object::Draw(unsigned int world_matrix_uniform_location_) {
    //printf("Drawing %u vertices.\n", num_vertices_);
    if (should_update_world_)
        GenerateWorldMatrix();

    // Set the world matrix
    glUniformMatrix4fv(world_matrix_uniform_location_, 1, true, world_.getMatrix());
    
    // Set the vertices and draw the object
    glBindVertexArray(vao_);
	glDrawArrays(GL_TRIANGLES, 0, num_vertices_);
	glBindVertexArray(0);
}

void Object::SetPosition(Vector3 position) {
    position_ = position;
    should_update_world_ = true;
}

void Object::SetPosition(float x, float y, float z) {
    SetPosition(Vector3(x, y, z));
}

void Object::SetAngles(Vector3 angles) {
    angles_ = angles;
    should_update_world_ = true;
}

void Object::SetAngles(float x, float y, float z) {
    SetAngles(Vector3(x, y, z));
}

void Object::SetScale(Vector3 scale) {
    scale_ = scale;
    should_update_world_ = true;
}

void Object::SetScale(float x, float y, float z) {
    SetScale(Vector3(x, y, z));
}

Vector3 Object::GetPosition() const {
    return position_;
}

Vector3 Object::GetAngles() const {
    return angles_;
}

Vector3 Object::GetScale() const {
    return scale_;
}

Matrix Object::GetWorldMatrix() {
    if (should_update_world_)
        GenerateWorldMatrix();

    return world_;
}

void Object::GenerateWorldMatrix() {
    world_ = translate(position_) * rotate(angles_) * scale(scale_);
    should_update_world_ = false;
}

Object::~Object() {

}