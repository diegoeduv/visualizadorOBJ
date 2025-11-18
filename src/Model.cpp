#include "Model.h"

// Sube vértices (posición) al VBO y configura el VAO.
void Model::upload(const std::vector<float>& vertices, GLenum drawMode) {
    mode = drawMode;
    count = static_cast<GLsizei>(vertices.size() / 3);

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, 
                 static_cast<GLsizeiptr>(vertices.size() * sizeof(float)), 
                 vertices.data(), 
                 GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);
}

// Sube vértices con color RGB.
void Model::uploadColored(const std::vector<float>& vertices, GLenum drawMode) {
    mode = drawMode;
    count = static_cast<GLsizei>(vertices.size() / 6); // 6 floats por vértice

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

    // Posición
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Color
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
}

// Sube vértices con color + alpha (RGBA).
void Model::uploadColoredAlpha(const std::vector<float>& vertices, GLenum drawMode) {
    mode = drawMode;

    count = static_cast<GLsizei>(vertices.size() / 7);

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

    // Posición (3 floats)
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Color + alpha (4 floats)
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
}

// Sube vértices + índices (para drawElements).
void Model::uploadEBO(const std::vector<float>& vertices,
                      const std::vector<unsigned int>& indices,
                      GLenum drawMode)
{
    mode = drawMode;
    count = static_cast<GLsizei>(indices.size());

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    // Vértices
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER,
                 static_cast<GLsizeiptr>(vertices.size() * sizeof(float)),
                 vertices.data(),
                 GL_STATIC_DRAW);

    // Índices
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                 static_cast<GLsizeiptr>(indices.size() * sizeof(unsigned int)),
                 indices.data(),
                 GL_STATIC_DRAW);

    // Atributo de posición
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
}

// Sube posiciones + texcoords + normales en VBOs separados.
void Model::uploadFullModel(const std::vector<float>& verts, const std::vector<float>& tcs, const std::vector<float>& normals, GLenum drawMode)
{
    mode = drawMode;
    count = static_cast<GLsizei>(verts.size() / 3); // 3 floats por posición

    glGenVertexArrays(1, &VAO);
    glGenBuffers(3, VBOs);

    glBindVertexArray(VAO);

    // Posiciones
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
    glBufferData(GL_ARRAY_BUFFER, verts.size() * sizeof(float), verts.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Coordenadas de textura
    if (!tcs.empty()) {
        glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
        glBufferData(GL_ARRAY_BUFFER, tcs.size() * sizeof(float), tcs.data(), GL_STATIC_DRAW);

        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(1);
    }

    // Normales
    if (!normals.empty()) {
        glBindBuffer(GL_ARRAY_BUFFER, VBOs[2]);
        glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(float), normals.data(), GL_STATIC_DRAW);

        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(2);
    }

    glBindVertexArray(0);
}


// Dibuja con drawArrays.
void Model::draw() const {
    glBindVertexArray(VAO);
    glDrawArrays(mode, 0, count);
    glBindVertexArray(0);
}

// Dibuja con drawElements.
void Model::drawElements(int count) const {
    glBindVertexArray(VAO);
    glDrawElements(mode, count, GL_UNSIGNED_INT, nullptr);
    glBindVertexArray(0);
}

// Libera VAO, VBO y EBO.
void Model::destroy() {
    if (EBO) glDeleteBuffers(1, &EBO);
    if (VBO) glDeleteBuffers(1, &VBO);
    if (VAO) glDeleteVertexArrays(1, &VAO);
    EBO = VBO = VAO = 0;
}
