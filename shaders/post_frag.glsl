#version 330 core

out vec3 color;
in vec2 UV;
in vec3 viewRay;

uniform uint selector;
uniform sampler2D colorTex;
uniform sampler2D depthTex;
uniform mat4 proj;
uniform mat4 view;

vec4 ViewPosFromDepth(float depth) {
    float z = depth * 2.0 - 1.0;

    vec4 clipSpacePosition = vec4(UV * 2.0 - 1.0, z, 1.0);
    vec4 viewSpacePosition = inverse(proj) * clipSpacePosition;
    viewSpacePosition /= viewSpacePosition.w;

    return viewSpacePosition;
}

vec4 ViewPosFromDepth2(float depth) {
	float near = 0.1;
  float far = 100;
  float ProjectionA = (far + near) / (far - near);
  float ProjectionB = (far * near) / (far - near);
  float linearDepth = ProjectionB / ((depth - ProjectionA));
  vec4 position = vec4(viewRay * linearDepth, 1.0);
  return position;
}

vec3 WorldPosFromViewPos(vec4 viewIn) {
    vec4 worldSpacePosition = inverse(view) * viewIn;

    return worldSpacePosition.xyz;
}

vec3 WorldPosFromDepth(float depth) {
    return WorldPosFromViewPos(ViewPosFromDepth(depth));
}

vec3 WorldPosFromDepth2(float depth) {
    return WorldPosFromViewPos(ViewPosFromDepth2(depth));
}

void main() {
  float depth = texture(depthTex, UV).r;
  if (selector == uint(0)) {
    color = texture(colorTex, UV).rgb;
  }
  else if (selector == uint(1)) {
    color = vec3(depth);
  }
  else if (selector == uint(2)) {
    color = (depth == 1) ? vec3(0.66,0.33,0.99) : WorldPosFromDepth(depth).xyz;
  }
  else {
    color = (depth == 1) ? vec3(0.99,0.66,0.33) : WorldPosFromDepth2(depth).xyz;
  }
}

