#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <vector>

/**
 * @namespace Geometry
 * @brief Genera vértices para figuras simples en OpenGL.
 */
namespace Geometry {

    /**
     * @brief Crea ejes XYZ coloreados.
     * @return Vértices en formato [x,y,z,r,g,b].
     */
    std::vector<float> makeAxes(float length);

    /**
     * @brief Crea ejes XYZ con alpha.
     * @return Vértices en formato [x,y,z,r,g,b,a].
     */
    std::vector<float> makeAxesAlpha(float length, float alpha);

}

#endif
