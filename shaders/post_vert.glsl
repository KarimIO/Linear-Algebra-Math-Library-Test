#version 330 core

layout(location = 0) in vec2 inPos;

out vec2 UV;

void main() {
	gl_Position = vec4(inPos, 0.0, 1.0);
	UV = (inPos + vec2(1.0f, 1.0f)/2.0f);
}
