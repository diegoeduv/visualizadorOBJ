#ifndef GRID_H
#define GRID_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include <string>
#include <cmath>
#include <cassert>
#include <GL/glew.h>
#include "Model.h"

/**
 * @class Grid
 * @brief Genera y dibuja una malla matemática con distintas funciones de altura.
 */
class Grid : public Model {
private:

    /// Estructura interna de un vértice (posición)
    struct Vertex {
        glm::vec3 Pos;
        /// Inicializa posición del vértice
        void InitVertex(int x, int y, int z);
    };

    /// Genera todos los vértices usando la función seleccionada
    void InitVertices(std::vector<Vertex>& vertices);

    /// Genera los índices de triángulos de la malla
    void InitIndices(std::vector<unsigned int>& indices);

    /// Función y = cos(x) + sin(z)
    void cosSinFunc(float x, float z, float& y) const;

    /// Función gaussiana y = exp(...)
    void expFunc(float x, float z, float& y) const;

    /// Devuelve y para el punto (x,z) según m_funcType
    float evalFunc(float x, float z) const;

    glm::mat4 m_model_mat = glm::mat4(1.0f);

public:
    int m_width  = 0; ///< Ancho del grid
    int m_depth  = 0; ///< Profundidad del grid
    int m_funcType = 0; ///< Tipo de función usada
    std::string m_name; ///< Nombre identificador

    Grid() = default;

    /// Constructor con dimensiones y tipo de función
    Grid(int width, int depth, int funcType)
        : m_width(width), m_depth(depth), m_funcType(funcType) {}

    /**
     * @brief Genera la malla y la sube a GPU.
     */
    void initGeometry();

    /**
     * @brief Dibuja el grid usando glDrawElements().
     */
    void draw() const;

    /**
     * @brief Devuelve los vértices como float[x,y,z].
     */
    std::vector<float> getVertices() const;

    /**
     * @brief Número total de vértices.
     */
    int getNumVertices() const;
};

#endif
