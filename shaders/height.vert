#version 330 core
layout (location = 0) in vec3 aPos;

out float vHeight; // Pasamos la altura Y al fragment shader

uniform mat4 uModel;
uniform mat4 uView;
uniform mat4 uProjection;

void main()
{
    gl_Position = uProjection * uView * uModel * vec4(aPos, 1.0);
    vHeight = aPos.y; // enviamos la coordenada Y
}
