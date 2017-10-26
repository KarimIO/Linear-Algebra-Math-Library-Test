#version 330 core

layout(location = 0) in vec2 inPos;

out vec2 UV;
out vec3 viewRay;

uniform mat4 proj;

void main() {
	gl_Position = vec4(inPos, 0.0, 1.0);
	UV = ((inPos.xy) + vec2(1.0f, 1.0f))/2.0f;

    vec3 positionVS = vec4(inverse(proj) * gl_Position).xyz;
    viewRay = vec3(positionVS.xy / positionVS.z, 1.0f);
}
