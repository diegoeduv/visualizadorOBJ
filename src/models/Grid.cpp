#include "models/Grid.h"

// Inicializa un vértice con posición (x,y,z)
void Grid::Vertex::InitVertex(int x, int y, int z) {
    Pos = glm::vec3(x, y, z);
}

// Función f(x,z) = cos(x) + sin(z)
void Grid::cosSinFunc(float x, float z, float& y) const {
    float freq = 0.2f;
    float amp  = 8.0f;
    y = amp * (std::cos(freq * x) + std::sin(freq * z));
}

// Función gaussiana f(x,z) = exp(-k(x²+z²))
void Grid::expFunc(float x, float z, float& y) const {
    float k   = 0.001f;
    float amp = 50.0f;
    y = amp * std::exp(-k * (x * x + z * z));
}

// Evalúa la función de altura según m_funcType
float Grid::evalFunc(float x, float z) const {
    float y = 0.0f;

    if (m_funcType == 1)
        cosSinFunc(x, z, y);
    else if (m_funcType == 2)
        expFunc(x, z, y);
    else {
        float radius = std::max(m_width, m_depth) / 2.0f;
        float dist   = std::sqrt(x * x + z * z);
        y = radius * 0.2f * std::exp(-std::pow(dist / (radius * 0.5f), 2.0f));
    }

    return y;
}

// Genera los vértices del grid
void Grid::InitVertices(std::vector<Vertex>& Vertices) {
    int index = 0;

    if (m_funcType == 1)      m_name = "cos(x) + sin(z)";
    else if (m_funcType == 2) m_name = "exp(-0.02*(x²+z²))";
    else                      m_name = "radial-gaussian";

    for (int z = -m_depth / 2; z < m_depth / 2; z++) {
        for (int x = -m_width / 2; x < m_width / 2; x++) {
            float y = evalFunc((float)x, (float)z);
            Vertices[index].InitVertex(x, y, z);
            index++;
        }
    }
}

// Genera índices (2 triángulos por celda)
void Grid::InitIndices(std::vector<unsigned int>& Indices) {
    int index = 0;

    for (int z = 0; z < m_depth - 1; z++) {
        for (int x = 0; x < m_width - 1; x++) {
            unsigned bl = z * m_width + x;
            unsigned tl = (z + 1) * m_width + x;
            unsigned tr = (z + 1) * m_width + (x + 1);
            unsigned br = z * m_width + (x + 1);

            Indices[index++] = bl;
            Indices[index++] = tl;
            Indices[index++] = tr;

            Indices[index++] = bl;
            Indices[index++] = tr;
            Indices[index++] = br;
        }
    }
}

// Genera vértices/índices y los sube al GPU
void Grid::initGeometry() {
    std::vector<Vertex> vertices(m_width * m_depth);
    InitVertices(vertices);

    int numQuads = (m_width - 1) * (m_depth - 1);
    std::vector<unsigned int> indices(numQuads * 6);
    InitIndices(indices);

    // Aplana a floats
    std::vector<float> data;
    data.reserve(vertices.size() * 3);
    for (auto& v : vertices) {
        data.push_back(v.Pos.x);
        data.push_back(v.Pos.y);
        data.push_back(v.Pos.z);
    }

    uploadEBO(data, indices, GL_TRIANGLES);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    m_model_mat = glm::scale(glm::mat4(1.0f), glm::vec3(0.25f, 5.0f, 0.25f));
}

// Dibuja la malla
void Grid::draw() const {
    int triCount = (m_width - 1) * (m_depth - 1) * 6;
    Model::drawElements(triCount);
}

// Regenera vértices como lista plana
std::vector<float> Grid::getVertices() const {
    std::vector<float> verts;
    verts.reserve(m_width * m_depth * 3);

    for (int z = -m_depth / 2; z < m_depth / 2; ++z) {
        for (int x = -m_width / 2; x < m_width / 2; ++x) {
            float y = evalFunc((float)x, (float)z);
            verts.push_back(x);
            verts.push_back(y);
            verts.push_back(z);
        }
    }
    return verts;
}

int Grid::getNumVertices() const {
    return m_width * m_depth;
}
