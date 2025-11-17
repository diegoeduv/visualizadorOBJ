#ifndef RENDER_H
#define RENDER_H

#include <GL/glew.h>

/**
 * @struct Renderer
 * @brief Utilidades para operaciones de renderizado en OpenGL.
 *
 * Proporciona métodos estáticos para limpiar el buffer de color y establecer el color de fondo.
 * Mantiene App.h libre de dependencias directas con GLFW o GLEW.
 */
struct Renderer {
    /**
     * @brief Limpia el buffer de color y establece el color de fondo.
     * @param r Rojo
     * @param g Verde
     * @param b Azul
     * @param a Alfa (por defecto 1.0)
     */
    static void clear(float r, float g, float b, float a = 1.0f);
};

#endif
