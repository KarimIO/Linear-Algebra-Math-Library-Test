#version 330 core

layout(location = 0) in vec3 inPos;

uniform mat4 perspectiveView;
uniform mat4 world;

out vec3 position;

void main() {
	gl_Position = perspectiveView * world * vec4(inPos, 1.0);
	position = vec4(world * vec4(inPos, 1.0)).xyz;
}
