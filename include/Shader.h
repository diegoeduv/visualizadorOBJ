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
 * @brief Encapsula la gestión de shaders OpenGL (vertex y fragment).
 *
 * Permite cargar, compilar, enlazar y usar programas de shaders, así como establecer uniformes.
 */
class Shader {
    GLuint program_ = 0; ///< Identificador del programa de shader OpenGL.

    /**
     * @brief Lee el contenido de un archivo y lo retorna como string.
     * @param path Ruta del archivo.
     * @return Contenido del archivo.
     * @throws std::runtime_error si no se puede abrir el archivo.
     */
    static std::string readFile(const std::string& path);

    /**
     * @brief Compila un shader de tipo dado a partir de su código fuente.
     * @param type Tipo de shader (GL_VERTEX_SHADER o GL_FRAGMENT_SHADER).
     * @param src Código fuente GLSL.
     * @return Identificador del shader compilado.
     * @throws std::runtime_error si la compilación falla.
     */
    static GLuint compile(GLenum type, const std::string& src);

public:
    /// Constructor por defecto. No carga ningún shader.
    Shader() = default;

    /**
     * @brief Constructor. Carga, compila y enlaza los shaders desde archivos.
     * @param vertPath Ruta al archivo de shader de vértices.
     * @param fragPath Ruta al archivo de shader de fragmentos.
     * @throws std::runtime_error si falla la compilación o el enlace.
     */
    Shader(const std::string& vertPath, const std::string& fragPath);

    /// Destructor. Libera el programa de shader.
    ~Shader();

    /// Activa el programa de shader para su uso.
    void use() const;

    /// Obtiene el identificador del programa de shader.
    GLuint id() const;

    /**
     * @brief Establece un uniforme vec3 en el shader.
     * @param name Nombre del uniforme.
     * @param x Componente x.
     * @param y Componente y.
     * @param z Componente z.
     */
    void setVec3(const char* name, float x, float y, float z) const;

    void setMat4(const char* name, const glm::mat4& mat) const;

    
};


#endif
