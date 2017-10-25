#version 330 core

out vec3 color;
in vec2 UV;

uniform sampler2D depth;

void main(){
  color = vec3(texture(depth, UV).rr,0);
}

