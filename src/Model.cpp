#include "Model.h"

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


void Model::uploadEBO(const std::vector<float>& vertices, const std::vector<unsigned int>& indices, GLenum drawMode)
{
    mode = drawMode;
    count = static_cast<GLsizei>(indices.size()); // cantidad de índices, no de vértices

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO); // nuevo buffer para índices

    glBindVertexArray(VAO);

    // --- Vértices ---
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER,
                 static_cast<GLsizeiptr>(vertices.size() * sizeof(float)),
                 vertices.data(),
                 GL_STATIC_DRAW);

    // --- Índices ---
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                 static_cast<GLsizeiptr>(indices.size() * sizeof(unsigned int)),
                 indices.data(),
                 GL_STATIC_DRAW);

    // --- Atributos de vértices ---
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
}


void Model::draw() const {
    glBindVertexArray(VAO);
    glDrawArrays(mode, 0, count);
    glBindVertexArray(0);
}


void Model::drawElements(int count) const{
    glBindVertexArray(VAO);
    glDrawElements(mode, count, GL_UNSIGNED_INT, nullptr);
    glBindVertexArray(0);
}


void Model::destroy() {
    if (EBO) glDeleteBuffers(1, &EBO);
    if (VBO) glDeleteBuffers(1, &VBO);
    if (VAO) glDeleteVertexArrays(1, &VAO);
    EBO = VBO = VAO = 0;
}

