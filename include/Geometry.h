#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <vector>

/**
 * @namespace Geometry
 * @brief Funciones para generar vértices de figuras geométricas en OpenGL.
 *
 * Incluye utilidades para crear triángulos, cuadrados, círculos y hexágonos.
 */
namespace Geometry {
    /**
     * @brief Genera los vértices de los ejes de coordenadas (X,Y,Z).
     * 
     * Cada eje es una línea de color diferente:
     * - X: rojo (1,0,0)
     * - Y: verde (0,1,0)
     * - Z: azul (0,0,1)
     *
     * @return Vector de floats con formato intercalado [x, y, z, r, g, b].
     */
    std::vector<float> makeAxes(float length);

    std::vector<float> makeAxesAlpha(float length, float alpha);
}

#endif
