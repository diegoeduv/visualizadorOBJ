#include "Geometry.h"
#include <cmath>

std::vector<float> Geometry::makeTriangle() {
    return {
        -0.8f,  0.2f, 0.0f,
        -0.5f,  0.7f, 0.0f,
        -0.2f,  0.2f, 0.0f
    };
}

std::vector<float> Geometry::makeSquare() {
    return {
         0.2f,  0.2f, 0.0f,
         0.7f,  0.2f, 0.0f,
         0.2f,  0.7f, 0.0f,
         0.7f,  0.7f, 0.0f
    };
}

std::vector<float> Geometry::makeCircle(int segments, float cx, float cy, float r) {
    std::vector<float> v;
    v.reserve((segments + 2) * 3);
    v.insert(v.end(), {cx, cy, 0.0f});

    for (int i = 0; i <= segments; ++i) {
        float ang = static_cast<float>(i) / segments * 2.0f * M_PI;
        v.push_back(cx + std::cos(ang) * r);
        v.push_back(cy + std::sin(ang) * r);
        v.push_back(0.0f);
    }

    return v;
}

std::vector<float> Geometry::makeHex(int sides, float cx, float cy, float r) {
    std::vector<float> v;
    v.reserve((sides + 2) * 3);
    v.insert(v.end(), {cx, cy, 0.0f});

    for (int i = 0; i <= sides; ++i) {
        float ang = static_cast<float>(i) / sides * 2.0f * M_PI + M_PI / 6.0f;
        v.push_back(cx + std::cos(ang) * r);
        v.push_back(cy + std::sin(ang) * r);
        v.push_back(0.0f);
    }

    return v;
}
std::vector<float> Geometry::makeAxes() {
    // Cada línea con color distinto: X (rojo), Y (verde), Z (azul)
    return {
        // Eje X (rojo)
        0.0f, 0.0f, 0.0f,  1.0f, 0.0f, 0.0f,   // origen
        1.0f, 0.0f, 0.0f,  1.0f, 0.0f, 0.0f,   // +X

        // Eje Y (verde)
        0.0f, 0.0f, 0.0f,  0.0f, 1.0f, 0.0f,   // origen
        0.0f, 1.0f, 0.0f,  0.0f, 1.0f, 0.0f,   // +Y

        // Eje Z (azul)
        0.0f, 0.0f, 0.0f,  0.0f, 0.0f, 1.0f,   // origen
        0.0f, 0.0f, 1.0f,  0.0f, 0.0f, 1.0f    // +Z
    };
}

