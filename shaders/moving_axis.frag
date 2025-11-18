#version 330 core
in vec4 vColor;
out vec4 FragColor;

void main()
{   //Este shader permite establecer el el valor de alpha al devolver el vector completo
    FragColor = vColor;
}
