#version 330 core

layout(location = 0) in vec3 inPos;

uniform mat4 pvw;
uniform mat4 world;

void main() {
	gl_Position = pvw * vec4(inPos, 1.0);
}
