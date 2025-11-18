#include "models/ImportedModel.h"
#include <iostream>

// Carga un archivo OBJ y sube sus vértices al GPU
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

    // Sube solo posiciones
    uploadFullModel(m_vertices, m_texCoords, m_normals, GL_TRIANGLES);
}

// Dibuja el modelo usando drawArrays del Model base
void ImportedModel::draw() const {
    Model::draw();
}
