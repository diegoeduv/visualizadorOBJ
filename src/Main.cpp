/**
 * @file Main.cpp
 * @brief Programa principal para ejecutar la aplicación de visualización OpenGL.
 *
 * Inicializa la clase App y captura excepciones.
 */
#include "Scene.h"
#include <iostream>


/**
 * @brief Función principal del programa.
 *
 * Crea una instancia de App y ejecuta el ciclo principal. Captura errores y los muestra en consola.
 * @return 0 si la ejecución fue exitosa, -1 si ocurre una excepción.
 */
int main() {
    try {
        Scene scene;
        scene.run();
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return -1;
    }
    return 0;
}
