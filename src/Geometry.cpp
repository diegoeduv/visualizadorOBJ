#include "Geometry.h"
#include <cmath>

// Crea ejes XYZ con color (sin alpha).
std::vector<float> Geometry::makeAxes(float length) {
    return {
        // Eje X
        0.0f, 0.0f, 0.0f,   1.0f, 0.0f, 0.0f,
        length, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,

        // Eje Y
        0.0f, 0.0f, 0.0f,   0.0f, 1.0f, 0.0f,
        0.0f, length, 0.0f, 0.0f, 1.0f, 0.0f,

        // Eje Z
        0.0f, 0.0f, 0.0f,   0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, length, 0.0f, 0.0f, 1.0f
    };
}

// Crea ejes XYZ con color y canal alpha.
std::vector<float> Geometry::makeAxesAlpha(float length, float alpha /*=1.0f*/) {
    return {
        // Eje X
        0.0f, 0.0f, 0.0f,   1.0f, 0.0f, 0.0f, alpha,
        length, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, alpha,

        // Eje Y
        0.0f, 0.0f, 0.0f,   0.0f, 1.0f, 0.0f, alpha,
        0.0f, length, 0.0f, 0.0f, 1.0f, 0.0f, alpha,

        // Eje Z
        0.0f, 0.0f, 0.0f,   0.0f, 0.0f, 1.0f, alpha,
        0.0f, 0.0f, length, 0.0f, 0.0f, 1.0f, alpha
    };
}
