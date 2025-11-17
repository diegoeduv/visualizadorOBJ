#ifndef MODEL_H
#define MODEL_H

#include <GL/glew.h>
#include <vector>

/**
 * @struct Model
 * @brief Representa una malla simple para renderizado en OpenGL.
 *
 * Permite cargar vértices, dibujar la malla y liberar recursos. Es un struct en vez de una clase ya que
 * facilita la llamada a las funciones al trabajar con múltiples figuras.
 */
struct Model {
    GLuint VAO = 0;   ///< Identificador del Vertex Array Object (VAO).
    GLuint VBO = 0;   ///< Identificador del Vertex Buffer Object (VBO).
    GLuint EBO = 0;   ///< Identificador del Element Buffer Object (EBO).
    GLsizei count = 0;///< Número de vértices a dibujar.
    GLenum mode = GL_TRIANGLES; ///< Modo de dibujo (GL_TRIANGLES, GL_TRIANGLE_STRIP, etc).

    /**
     * @brief Carga los vértices en la GPU y configura el VAO/VBO.
     * @param vertices Vector de posiciones (x, y, z) de los vértices.
     * @param drawMode Modo de dibujo de OpenGL.
     */
    void upload(const std::vector<float>& vertices, GLenum drawMode);

    void uploadColored(const std::vector<float>& vertices, GLenum drawMode);

    void uploadEBO(const std::vector<float>& vertices, const std::vector<unsigned int>& indices, GLenum drawMode);

    /**
     * @brief Dibuja la malla usando el modo configurado.
     */
    void draw() const;

    void drawElements(int count) const;

    /**
     * @brief Libera los recursos de la malla (VAO y VBO).
     */
    void destroy();

    void setMode(GLenum newMode) { mode = newMode; }
};

#endif
