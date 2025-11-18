#include "Window.h"

// Inicializa GLFW/GLEW y crea la ventana.
Window::Window(unsigned w, unsigned h, const char* title)
    : width(w), height(h)
{
    if (!glfwInit())
        throw std::runtime_error("glfwInit falló");

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    handle = glfwCreateWindow(static_cast<int>(w), static_cast<int>(h), title, nullptr, nullptr);
    if (!handle) {
        glfwTerminate();
        throw std::runtime_error("No se pudo crear la ventana GLFW");
    }

    glfwMakeContextCurrent(handle);

    // Ajusta el viewport al redimensionar.
    glfwSetFramebufferSizeCallback(handle, [](GLFWwindow*, int W, int H) {
        glViewport(0, 0, W, H);
    });

    if (glewInit() != GLEW_OK) {
        glfwDestroyWindow(handle);
        glfwTerminate();
        throw std::runtime_error("glewInit falló");
    }
}

// Cierra GLFW.
Window::~Window() {
    glfwTerminate();
}

// Devuelve true si la ventana debe cerrarse.
bool Window::shouldClose() const {
    return glfwWindowShouldClose(handle);
}

// Procesa eventos pendientes.
void Window::poll() const {
    glfwPollEvents();
}

// Intercambia buffers.
void Window::swap() const {
    glfwSwapBuffers(handle);
}
