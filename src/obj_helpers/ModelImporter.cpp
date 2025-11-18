#include "obj_helpers/ModelImporter.h"
#include <iostream>
#include <fstream>
#include <sstream>

// Convierte un índice OBJ (positivo o negativo) a índice válido 0-based
static int resolveIndex(int idx, int size) {
    return (idx > 0) ? idx - 1 : size + idx;
}

// Parsea un archivo .OBJ simple (v, vt, vn, f)
void ModelImporter::parseOBJ(const char* filePath) {
    std::ifstream fileStream(filePath, std::ios::in);
    if (!fileStream) {
        std::cerr << "Error: no se pudo abrir el archivo OBJ: " << filePath << std::endl;
        return;
    }

    float x, y, z;
    std::string line;

    while (std::getline(fileStream, line)) {
        if (line.compare(0, 2, "v ") == 0) { // vértices
            std::stringstream ss(line.substr(2));
            ss >> x >> y >> z;
            vertVals.insert(vertVals.end(), {x, y, z});
        }
        else if (line.compare(0, 3, "vt ") == 0) { // coordenadas de textura
            std::stringstream ss(line.substr(3));
            ss >> x >> y;
            stVals.insert(stVals.end(), {x, y});
        }
        else if (line.compare(0, 3, "vn ") == 0) { // normales
            std::stringstream ss(line.substr(3));
            ss >> x >> y >> z;
            normVals.insert(normVals.end(), {x, y, z});
        }
        else if (line.compare(0, 2, "f ") == 0) { // caras
            std::stringstream ss(line.substr(2));
            std::string oneCorner, v, t, n;

            while (std::getline(ss, oneCorner, ' ')) {
                if (oneCorner.empty()) continue;

                std::stringstream oneCornerSS(oneCorner);
                std::getline(oneCornerSS, v, '/');
                std::getline(oneCornerSS, t, '/');
                std::getline(oneCornerSS, n, '/');

                // índices (pueden ser negativos)
                int vIndex = resolveIndex(std::stoi(v), vertVals.size() / 3);
                int tIndex = (!t.empty()) ? resolveIndex(std::stoi(t), stVals.size() / 2) : -1;
                int nIndex = (!n.empty()) ? resolveIndex(std::stoi(n), normVals.size() / 3) : -1;

                // vértices
                triangleVerts.push_back(vertVals[vIndex * 3 + 0]);
                triangleVerts.push_back(vertVals[vIndex * 3 + 1]);
                triangleVerts.push_back(vertVals[vIndex * 3 + 2]);

                // coordenadas de textura
                if (tIndex >= 0) {
                    textureCoords.push_back(stVals[tIndex * 2 + 0]);
                    textureCoords.push_back(stVals[tIndex * 2 + 1]);
                } else {
                    textureCoords.insert(textureCoords.end(), {0.0f, 0.0f});
                }

                // normales
                if (nIndex >= 0) {
                    normals.push_back(normVals[nIndex * 3 + 0]);
                    normals.push_back(normVals[nIndex * 3 + 1]);
                    normals.push_back(normVals[nIndex * 3 + 2]);
                } else {
                    normals.insert(normals.end(), {0.0f, 0.0f, 0.0f});
                }
            }
        }
    }
}

int ModelImporter::getNumVertices() const {
    return static_cast<int>(triangleVerts.size() / 3);
}
// Devuelve vector plano de posiciones (x,y,z).
std::vector<float> ModelImporter::getVertices() const { return triangleVerts; }

// Devuelve vector plano de coordenadas de textura (u,v).
std::vector<float> ModelImporter::getTextureCoords() const { return textureCoords; }

// Devuelve vector plano de normales (x,y,z).
std::vector<float> ModelImporter::getNormals() const { return normals; }
