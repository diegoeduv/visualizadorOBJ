#ifndef SHADER_H
#define SHADER_H

#include <glm/gtc/type_ptr.hpp>
#include <GL/glew.h>
#include <string>
#include <fstream>
#include <stdexcept>
#include <vector>

/**
 * @class Shader
 * @brief Maneja carga, compilación y uso de shaders OpenGL.
 */
class Shader {
    GLuint program_ = 0; /// ID del programa GLSL.

    /**
     * @brief Lee un archivo y devuelve su contenido.
     */
    static std::string readFile(const std::string& path);

    /**
     * @brief Compila un shader desde código fuente.
     */
    static GLuint compile(GLenum type, const std::string& src);

public:
    /// Constructor vacío (shader no cargado).
    Shader() = default;

    /**
     * @brief Carga, compila y enlaza shaders de vértice y fragmento.
     */
    Shader(const std::string& vertPath, const std::string& fragPath);

    /// Destructor: libera el programa.
    ~Shader();

    /// Activa el programa de shader.
    void use() const;

    /// Obtiene el ID interno del programa.
    GLuint id() const;

    /**
     * @brief Envía un vec3 al uniform especificado.
     */
    void setVec3(const char* name, float x, float y, float z) const;

    /**
     * @brief Envía una matriz 4x4 al uniform especificado.
     */
    void setMat4(const char* name, const glm::mat4& mat) const;
};

#endif
