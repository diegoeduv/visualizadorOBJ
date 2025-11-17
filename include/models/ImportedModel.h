#ifndef IMPORTEDMODEL_H
#define IMPORTEDMODEL_H

#include <GL/glew.h>
#include <vector>
#include "Model.h"
#include "obj_helpers/ModelImporter.h"

/**
 * @class ImportedModel
 * @brief Modelo que carga geometría desde un archivo .OBJ usando ModelImporter.
 *
 * Hereda de Model y permite subir a GPU los vértices obtenidos desde el parser OBJ.
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
     * @brief Carga el modelo desde un archivo .OBJ.
     * @param filePath Ruta al archivo OBJ.
     */
    void loadFromOBJ(const char* filePath);

    /**
     * @brief Dibuja el modelo (usa draw() heredado de Model).
     */
    void draw() const;

    int getNumVertices() const { return static_cast<int>(m_vertices.size() / 3); }
    std::vector<float> getVertices() const { return m_vertices; }

};



#endif
