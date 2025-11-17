#ifndef WINDOW_H
#define WINDOW_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdexcept>

/**
 * @class Window
 * @brief Encapsula la creación y gestión de una ventana GLFW con contexto OpenGL.
 *
 * Esta clase inicializa GLFW y GLEW, crea una ventana y gestiona el ciclo de vida de la misma.
 */
class Window {
public:
    GLFWwindow* handle = nullptr; ///< Puntero al objeto de ventana GLFW.
    unsigned width;  ///< Ancho de la ventana.
    unsigned height; ///< Alto de la ventana.

    /**
     * @brief Constructor. Inicializa GLFW, GLEW y crea la ventana.
     * @param w Ancho de la ventana.
     * @param h Alto de la ventana.
     * @param title Título de la ventana.
     * @throws std::runtime_error si falla la inicialización o creación de la ventana.
     */
    Window(unsigned w, unsigned h, const char* title);

    /// Destructor. Libera los recursos terminando GLFW.
    ~Window();

    /// Indica si la ventana debe cerrarse.
    bool shouldClose() const;

    /// Procesa los eventos de la ventana.
    void poll() const;

    /// Intercambia los buffers de la ventana.
    void swap() const;

    float getAspectRatio() const {
    return static_cast<float>(width) / static_cast<float>(height);
}

};

#endif
