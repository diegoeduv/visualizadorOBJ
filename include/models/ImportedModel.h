#ifndef IMPORTEDMODEL_H
#define IMPORTEDMODEL_H

#include <GL/glew.h>
#include <vector>
#include "Model.h"
#include "obj_helpers/ModelImporter.h"

/**
 * @class ImportedModel
 * @brief Modelo cargado desde un archivo OBJ.
 *
 * Usa ModelImporter y sube la geometría al GPU mediante la base Model.
 */
class ImportedModel : public Model {

private:
    ModelImporter importer;
    std::vector<float> m_vertices;
    std::vector<float> m_normals;
    std::vector<float> m_texCoords;

public:
    ImportedModel() = default;

    /**
     * @brief Carga un modelo OBJ desde filePath.
     */
    void loadFromOBJ(const char* filePath);

    /**
     * @brief Renderiza el modelo (draw heredado).
     */
    void draw() const;

    /// Número total de vértices (Esto considera los vertices adicionales que se generaron al leer las caras)
    int getNumVertices() const { return static_cast<int>(m_vertices.size() / 3); }

    /// Devuelve el arreglo plano de vértices (x,y,z)
    std::vector<float> getVertices() const { return m_vertices; }
};

#endif
