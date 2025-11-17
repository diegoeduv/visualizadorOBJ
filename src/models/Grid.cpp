#include "models/Grid.h"
#include <glm/gtc/matrix_transform.hpp>


// ------------------------------------------------------
// Genera VAO + VBO + EBO y sube geometría a la GPU
// ------------------------------------------------------
void Grid::CreateTriangleList() {
    initGeometry();
}

// ------------------------------------------------------
// Inicializa un vértice con posición (x,y,z)
// ------------------------------------------------------
void Grid::Vertex::InitVertex(int x, int y, int z) {
    Pos = glm::vec3(x, y, z);
}

// ------------------------------------------------------
// Genera todos los vértices del grid según la función seleccionada
// ------------------------------------------------------
void Grid::InitVertices(std::vector<Vertex>& Vertices) {
    int Index = 0;
    float radius = std::max(m_width, m_depth) / 2.0f;

    for (int z = -m_depth / 2; z < m_depth / 2; z++) {
        for (int x = -m_width / 2; x < m_width / 2; x++) {
            assert(Index < (int)Vertices.size());

            float y = 0.0f;

            if (m_funcType == 1) {
                cosSinFunc((float)x, (float)z, y);
            } else if (m_funcType == 2) {
                expFunc((float)x, (float)z, y);
            } else {
                // función gaussiana
                float dist = sqrtf(x * x + z * z);
                y = radius * 0.2f * expf(-powf(dist / (radius * 0.5f), 2.0f));
            }

            Vertices[Index].InitVertex(x, y, z);
            Index++;
        }
    }
}

// ------------------------------------------------------
// f(x,z) = cos(x) + sin(z)
// ------------------------------------------------------
void Grid::cosSinFunc(float x, float z, float& y) const {
    float freq = 0.2f;    // frecuencia de ondas (espaciado)
    float amp  = 8.0f;    // amplitud (altura de las olas)
    y = amp * (std::cos(freq * x) + std::sin(freq * z));
}


// ------------------------------------------------------
// f(x,z) = exp(-0.02 * (x² + z²))  (función gaussiana)
// ------------------------------------------------------
void Grid::expFunc(float x, float z, float& y) const {
    float k = 0.006f;        // ← más pequeño = más ancha
    float amp = 50.0f;       // altura
    y = amp * std::exp(-k * (x * x + z * z));
}



// ------------------------------------------------------
// Inicializa los índices de la malla (triángulos)
// ------------------------------------------------------
void Grid::InitIndices(std::vector<unsigned int>& Indices) {
    int Index = 0;

    for (int z = 0; z < m_depth - 1; z++) {
        for (int x = 0; x < m_width - 1; x++) {
            assert(Index < (int)Indices.size());

            unsigned int IndexBottomLeft = z * m_width + x;
            unsigned int IndexTopLeft = (z + 1) * m_width + x;
            unsigned int IndexTopRight = (z + 1) * m_width + (x + 1);
            unsigned int IndexBottomRight = z * m_width + (x + 1);

            // Primer triángulo
            Indices[Index++] = IndexBottomLeft;
            Indices[Index++] = IndexTopLeft;
            Indices[Index++] = IndexTopRight;

            // Segundo triángulo
            Indices[Index++] = IndexBottomLeft;
            Indices[Index++] = IndexTopRight;
            Indices[Index++] = IndexBottomRight;
        }
    }
}

// ------------------------------------------------------
// Genera la geometría y la sube al GPU con uploadEBO()
// ------------------------------------------------------
void Grid::initGeometry() {
    std::vector<Vertex> vertices;
    vertices.resize(m_width * m_depth);
    InitVertices(vertices);

    std::vector<unsigned int> indices;
    int NumQuads = (m_width - 1) * (m_depth - 1);
    indices.resize(NumQuads * 6);
    InitIndices(indices);

    // Convertimos a un vector plano de floats
    std::vector<float> vertexData;
    vertexData.reserve(vertices.size() * 3);
    for (const auto& v : vertices) {
        vertexData.push_back(v.Pos.x);
        vertexData.push_back(v.Pos.y);
        vertexData.push_back(v.Pos.z);
    }

    // Subimos datos usando el método del modelo base
    uploadEBO(vertexData, indices, GL_TRIANGLES);
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // -> Para modo wireframe
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // -> Para modo wireframe

    // Escala del modeloGL_

    m_model_mat = glm::mat4(1.0f);
    m_model_mat = glm::scale(m_model_mat, glm::vec3(0.25f, 5.0f, 0.25f));

}

// ------------------------------------------------------
// Dibuja la malla usando glDrawElements()
// ------------------------------------------------------
void Grid::draw() const {
    Model::drawElements(static_cast<int>((m_width - 1) * (m_depth - 1) * 6));
}

std::vector<float> Grid::getVertices() const {
    std::vector<float> verts;
    verts.reserve(m_width * m_depth * 3);

    // Generar los vértices con la misma lógica que initGeometry
    for (int z = -m_depth / 2; z < m_depth / 2; ++z) {
        for (int x = -m_width / 2; x < m_width / 2; ++x) {
            float y = 0.0f;
            if (m_funcType == 1)
                cosSinFunc((float)x, (float)z, y);
            else if (m_funcType == 2)
                expFunc((float)x, (float)z, y);
            else {
                float dist = sqrtf(x * x + z * z);
                y = std::exp(-0.02f * (x * x + z * z));
            }

            verts.push_back((float)x);
            verts.push_back(y);
            verts.push_back((float)z);
        }
    }

    return verts;
}

int Grid::getNumVertices() const {
    return m_width * m_depth;
}
