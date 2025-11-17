#ifndef MODEL_IMPORTER_H
#define MODEL_IMPORTER_H

#include <vector>
#include <string>

/**
 * @class ModelImporter
 * @brief Parser básico para archivos .OBJ.
 *
 * Lee vértices, coordenadas de textura y normales de un archivo .obj
 * y genera vectores listos para ser usados como atributos de vértices en OpenGL.
 */
class ModelImporter {
private:
    // Datos originales leídos del archivo .obj
    std::vector<float> vertVals;  ///< posiciones (v)
    std::vector<float> stVals;    ///< coordenadas de textura (vt)
    std::vector<float> normVals;  ///< normales (vn)

    // Datos finales listos para cargar al GPU
    std::vector<float> triangleVerts;
    std::vector<float> textureCoords;
    std::vector<float> normals;

public:
    /// Constructor por defecto.
    ModelImporter() = default;

    /**
     * @brief Parsea un archivo OBJ.
     * @param filePath Ruta al archivo OBJ.
     */
    void parseOBJ(const char* filePath);

    /// @return Número de vértices cargados.
    int getNumVertices() const;

    /// @return Vector de vértices (x, y, z).
    std::vector<float> getVertices() const;

    /// @return Vector de coordenadas de textura (u, v).
    std::vector<float> getTextureCoords() const;

    /// @return Vector de normales (x, y, z).
    std::vector<float> getNormals() const;
};

#endif
