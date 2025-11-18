#ifndef SCENE_H
#define SCENE_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Window.h"
#include "Shader.h"
#include "Model.h"
#include "Geometry.h"
#include "models/ImportedModel.h"
#include "models/Grid.h"

#include <iostream>
#include <vector>
#include <string>

/// Límites mínimos y máximos del mesh
struct Bounds {
    glm::vec3 minP;
    glm::vec3 maxP;
};

/**
 * @class Scene
 * @brief Controla ventana, cámara, shaders, modelos, grids e input.
 */
class Scene {

    // Tamaño de ventana
    static const unsigned SCR_WIDTH  = 800;
    static const unsigned SCR_HEIGHT = 600;

    // Componentes principales
    Window window;
    Shader shader, shaderAxes, shaderMovingAxes;
    Model axes, movingAxes;

    // Matrices principales
    glm::mat4 m_view;
    glm::mat4 m_projection;
    glm::mat4 m_model = glm::mat4(1.0f);

    // Modelos OBJ cargados
    std::vector<ImportedModel> m_models;
    std::vector<std::string>   m_modelNames;
    int m_currentModel = 0;

    // Grids matemáticos
    std::vector<Grid> m_grids;
    std::vector<std::string> m_gridNames;
    int m_currentGrid = 0;

    // Estado de visualización
    bool showingGrids = false;

    // Escalado
    float modelScale = 1.0f;
    float zoomStep   = 0.05f;

    // Longitud de ejes auxiliares
    float axesLength       = 1.0f;
    float movingAxesLength = 1.0f;
    float alpha = 0.55f;

    // Visibilidad de ejes
    bool axesVisible       = true;
    bool movingAxesVisible = true;

public:
    /// Constructor: inicializa ventana, shaders, ejes y modelos.
    Scene();

    /// Destructor: libera recursos y buffers.
    ~Scene();

    /**
     * @brief Ejecuta el ciclo principal de renderizado.
     */
    void run();

private:

    /// Carga modelos OBJ predefinidos.
    void loadModels();

    /// Inicializa los grids matemáticos.
    void loadGrids();

    /// Imprime en consola los datos del modelo/grid activo.
    void printCurrentModelStats();

    /// Ajusta cámara y matrices según el modelo/grid actual.
    void updateCameraToCurrentModel();

    /// Renderiza el modelo o grid activo.
    void render();

    /// Envía matrices al shader indicado.
    void applyShader(Shader& s);

    /// Limpia la pantalla con color RGBA.
    void clear(float r, float g, float b, float a);

    /// Calcula los límites (min/max XYZ) de una lista de vértices.
    Bounds computeBounds(const std::vector<float>& verts);

    /// Retorna min/max del eje Y.
    std::pair<float,float> computeMinMaxY(const std::vector<float>& verts);

    /// Detecta pulsación única (previene repetición constante).
    bool keyPressedOnce(int key, bool& state);

    /// Controla rotación del modelo con X/Y/Z y escape.
    void pollRotation();

    /// Cambia modelo/grid y permite navegar entre ellos.
    void pollModelSwitching();

    /// Cambia modo de render (puntos, líneas, triángulos).
    void pollRenderModeKeys();

    /// Zoom simple con F1 / F2.
    void pollZoom();

    /// Alterna visibilidad de ejes.
    void pollAxesToggles();
};

#endif
