#ifndef WINDOW_H
#define WINDOW_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdexcept>

/**
 * @class Window
 * @brief Encapsula una ventana GLFW con contexto OpenGL.
 */
class Window {
public:
    GLFWwindow* handle = nullptr; ///< Puntero a la ventana GLFW.
    unsigned width; ///< Ancho.
    unsigned height; ///< Alto.

    /**
     * @brief Crea la ventana e inicializa GLFW/GLEW.
     */
    Window(unsigned w, unsigned h, const char* title);

    /// Cierra la ventana y termina GLFW.
    ~Window();

    /// Indica si debe cerrarse.
    bool shouldClose() const;

    /// Procesa eventos.
    void poll() const;

    /// Intercambia buffers.
    void swap() const;

    /// Retorna width/height.
    float getAspectRatio() const {
        return static_cast<float>(width) / static_cast<float>(height);
    }
};

#endif
