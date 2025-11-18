#version 330 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec4 aColor;

uniform mat4 uView;
uniform mat4 uProjection;
uniform mat4 uModel;

out vec4 vColor;

void main()
{   
    // Calculamos la posición final del vértice, este eje se mueve con una matriz de modelo
    // Este fue un detalle que yo quise agregar para que se visualice muy bien como el objeto
    // rota al rededor del eje deseado
    gl_Position = uProjection * uView * uModel * vec4(aPos, 1.0);
    // Pasamos el color con alpha incluido
    vColor = aColor;
}
