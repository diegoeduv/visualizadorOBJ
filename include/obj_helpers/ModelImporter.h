#ifndef MODEL_IMPORTER_H
#define MODEL_IMPORTER_H

#include <vector>
#include <string>

/**
 * @class ModelImporter
 * @brief Parser básico para archivos .OBJ.
 *
 * Lee posiciones, UVs y normales desde un archivo .OBJ y genera
 * buffers listos para cargar en OpenGL.
 */
class ModelImporter {
private:
    // Datos crudos leídos del archivo .OBJ
    std::vector<float> vertVals; ///< Posiciones (v)
    std::vector<float> stVals; ///< Coord. de textura (vt)
    std::vector<float> normVals; ///< Normales (vn)

    // Datos expandidos listos para GPU
    std::vector<float> triangleVerts;
    std::vector<float> textureCoords;
    std::vector<float> normals;

public:
    /// Constructor por defecto.
    ModelImporter() = default;

    /**
     * @brief Parsea un archivo .OBJ.
     * @param filePath Ruta del archivo.
     */
    void parseOBJ(const char* filePath);

    /// Devuelve número total de vértices.
    int getNumVertices() const;

    /// Devuelve vector plano de posiciones (x,y,z).
    std::vector<float> getVertices() const;

    /// Devuelve vector de coordenadas UV (u,v).
    std::vector<float> getTextureCoords() const;

    /// Devuelve vector de normales (x,y,z).
    std::vector<float> getNormals() const;
};

#endif
