#include "models/ImportedModel.h"
#include <iostream>

void ImportedModel::loadFromOBJ(const char* filePath) {
    importer.parseOBJ(filePath);

    m_vertices = importer.getVertices();
    m_normals = importer.getNormals();
    m_texCoords = importer.getTextureCoords();

    if (m_vertices.empty()) {
        std::cerr << "Error: no se cargaron vértices desde " << filePath << std::endl;
        return;
    }
    std::cout << "Modelo cargado: " << m_vertices.size() / 3 << " vértices\n";
    // Usa la función base "upload" del Model
    upload(m_vertices, GL_TRIANGLES);
}

void ImportedModel::draw() const {
    Model::draw(); // Usa la implementación base
}
