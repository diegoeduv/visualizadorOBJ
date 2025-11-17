#include "Window.h"

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
    glfwSetFramebufferSizeCallback(handle, [](GLFWwindow*, int W, int H) {
        glViewport(0, 0, W, H);
    });

    if (glewInit() != GLEW_OK) {
        glfwDestroyWindow(handle);
        glfwTerminate();
        throw std::runtime_error("glewInit falló");
    }
}

Window::~Window() {
    glfwTerminate();
}

bool Window::shouldClose() const {
    return glfwWindowShouldClose(handle);
}

void Window::poll() const {
    glfwPollEvents();
}

void Window::swap() const {
    glfwSwapBuffers(handle);
}
