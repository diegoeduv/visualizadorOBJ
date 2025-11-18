#ifndef MODEL_H
#define MODEL_H

#include <GL/glew.h>
#include <vector>

/**
 * @struct Model
 * @brief Malla básica para render en OpenGL.
 */
struct Model {

    GLuint VAO = 0; ///< Vertex Array Object.
    GLuint VBO = 0; ///< Vertex Buffer Object.
    GLuint VBOs[3] = {0, 0, 0}; ///< VBO 0 = posiciones, 1 = texcoords, 2 = normales / otros
    GLuint EBO = 0; ///< Element Buffer Object. Si se usan índices.

    GLsizei count = 0; ///< Número de vértices o índices.
    GLenum mode = GL_TRIANGLES; ///< Modo de dibujo.

    // Carga de vertices y configuración de buffers, adapatadas a distintas necesidades.

    /// Carga posiciones (3 floats por vértice).
    void upload(const std::vector<float>& vertices, GLenum drawMode);

    /// Carga vértices con color (RGB, 6 floats por vértice).
    void uploadColored(const std::vector<float>& vertices, GLenum drawMode);

    /// Carga vértices con color + alpha (RGBA, 7 floats p/ vértice).
    void uploadColoredAlpha(const std::vector<float>& vertices, GLenum drawMode);

    /// Carga vértices + índices en VAO/VBO/EBO.
    void uploadEBO(const std::vector<float>& vertices, const std::vector<unsigned int>& indices, GLenum drawMode);

    /// Carga posiciones + texcoords + normales (en 3 VBOs separados).
    void uploadFullModel(const std::vector<float>& verts, const std::vector<float>& tcs, const std::vector<float>& normals, GLenum drawMode = GL_TRIANGLES);

    /// Dibujo con drawArrays.
    void draw() const;

    /// Dibujo con drawElements.
    void drawElements(int count) const;

    /// Limpieza.
    void destroy();

    /// Cambia el modo de dibujo.
    void setMode(GLenum newMode) { mode = newMode; }
};

#endif
