#version 330 core
layout (location = 0) in vec3 aPos;   // posición
layout (location = 1) in vec3 aColor; // color por vértice

uniform mat4 uMVP;

out vec3 vColor;

void main() {
    vColor = aColor;
    gl_Position = uMVP * vec4(aPos, 1.0);
}
