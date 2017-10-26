#version 330 core

layout(location = 0) out vec3 color;

in vec3 position;

void main(){
  color = position;
}

