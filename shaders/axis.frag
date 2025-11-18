#version 330 core
in vec3 vColor;
out vec4 FragColor;

void main() {
    // El color se pasa directamente desde el vértice. (Y este a su vez lo devuelve para establecerlo en Geometry::makeAxes)
    FragColor = vec4(vColor, 1.0);
}
