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
     * @brief Genera los vértices de un triángulo.
     * @return Vector de posiciones (x, y, z) de los vértices.
     */
    std::vector<float> makeTriangle();

    /**
     * @brief Genera los vértices de un cuadrado usando TRIANGLE_STRIP.
     * @return Vector de posiciones (x, y, z) de los vértices.
     */
    std::vector<float> makeSquare();

    /**
     * @brief Genera los vértices de un círculo usando TRIANGLE_FAN.
     * @param segments Número de segmentos para aproximar el círculo.
     * @param cx Centro x.
     * @param cy Centro y.
     * @param r Radio.
     * @return Vector de posiciones (x, y, z) de los vértices.
     */
    std::vector<float> makeCircle(int segments = 64, float cx = -0.5f, float cy = -0.5f, float r = 0.28f);

    /**
     * @brief Genera los vértices de un hexágono usando TRIANGLE_FAN.
     * @param sides Número de lados (por defecto 6).
     * @param cx Centro x.
     * @param cy Centro y.
     * @param r Radio.
     * @return Vector de posiciones (x, y, z) de los vértices.
     */
    std::vector<float> makeHex(int sides = 6, float cx = 0.5f, float cy = -0.5f, float r = 0.25f);
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
    std::vector<float> makeAxes();
}

#endif
