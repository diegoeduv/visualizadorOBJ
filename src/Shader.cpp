#include "Shader.h"

// Lee un archivo completo y devuelve su contenido.
std::string Shader::readFile(const std::string& path) {
    std::ifstream file(path, std::ios::binary);
    if (!file)
        throw std::runtime_error("No se pudo abrir: " + path);

    file.seekg(0, std::ios::end);
    std::size_t size = file.tellg();
    std::string buffer(size, '\0');

    file.seekg(0);
    file.read(&buffer[0], size);

    return buffer;
}

// Compila un shader (vertex o fragment) a partir de código fuente.
GLuint Shader::compile(GLenum type, const std::string& src) {
    GLuint id = glCreateShader(type);
    const char* c = src.c_str();
    glShaderSource(id, 1, &c, nullptr);
    glCompileShader(id);

    GLint ok;
    glGetShaderiv(id, GL_COMPILE_STATUS, &ok);
    if (!ok) {
        char log[2048];
        glGetShaderInfoLog(id, 2048, nullptr, log);
        std::string kind = (type == GL_VERTEX_SHADER ? "VERTEX" : "FRAGMENT");
        throw std::runtime_error("Compilación " + kind + " falló:\n" + std::string(log));
    }

    return id;
}

// Carga, compila y enlaza vertex + fragment shader.
Shader::Shader(const std::string& vertPath, const std::string& fragPath) {
    std::string vsrc = readFile(vertPath);
    std::string fsrc = readFile(fragPath);

    GLuint vs = compile(GL_VERTEX_SHADER, vsrc);
    GLuint fs = compile(GL_FRAGMENT_SHADER, fsrc);

    program_ = glCreateProgram();
    glAttachShader(program_, vs);
    glAttachShader(program_, fs);
    glLinkProgram(program_);

    GLint ok;
    glGetProgramiv(program_, GL_LINK_STATUS, &ok);

    glDeleteShader(vs);
    glDeleteShader(fs);

    if (!ok) {
        char log[2048];
        glGetProgramInfoLog(program_, 2048, nullptr, log);
        throw std::runtime_error(std::string("Linkeo falló:\n") + log);
    }
}

// Libera el programa.
Shader::~Shader() {
    if (program_)
        glDeleteProgram(program_);
}

// Activa el shader.
void Shader::use() const {
    glUseProgram(program_);
}

// Devuelve el ID del programa.
GLuint Shader::id() const {
    return program_;
}

// Envía un vec3 al shader.
void Shader::setVec3(const char* name, float x, float y, float z) const {
    GLint loc = glGetUniformLocation(program_, name);
    glUniform3f(loc, x, y, z);
}

// Envía una matriz 4x4 al shader.
void Shader::setMat4(const char* name, const glm::mat4& mat) const {
    GLint loc = glGetUniformLocation(program_, name);
    glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(mat));
}
