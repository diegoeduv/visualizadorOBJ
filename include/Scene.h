#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Window.h"
#include "Shader.h"
#include "Model.h"
#include "Render.h"
#include "Geometry.h"
#include "models/ImportedModel.h"
#include "models/Grid.h"

#include <iostream>
#include <vector>
#include <string>

/**
 * @class Scene
 * @brief Maneja todos los modelos, las mallas (grids), la cámara y la interacción general.
 */
class Scene {
    static const unsigned SCR_WIDTH = 800;
    static const unsigned SCR_HEIGHT = 600;

    // --- Componentes principales ---
    Window window;
    Shader shader, shaderAxes, shaderMovingAxes;
    Model axes, movingAxes;

    // --- Matrices ---
    glm::mat4 m_view;
    glm::mat4 m_projection;
    glm::mat4 m_model = glm::mat4(1.0f);

    // --- Modelos OBJ ---
    std::vector<ImportedModel> m_models;
    std::vector<std::string> m_modelNames;
    int m_currentModel = 0;

    // --- Grids matemáticos ---
    std::vector<Grid> m_grids;
    int m_currentGrid = 0;

    // --- Estado ---
    bool showingGrids = false; // false = modelos OBJ, true = grids

    float modelScale = 1.0f;
    float zoomStep = 0.05f;

    float axesLength = 1.0f;
    float movingAxesLength = 1.0f;

    float alpha = 0.55f;





public:
    Scene();
    ~Scene();

    /**
     * @brief Inicia el bucle principal de renderizado.
     */
    void run();

private:
    /**
     * @brief Carga los modelos OBJ desde los archivos.
     */
    void loadModels();

    /**
     * @brief Genera las mallas (grids) matemáticas.
     */
    void loadGrids();

    /**
     * @brief Imprime estadísticas del modelo o grid actual.
     */
    void printCurrentModelStats();

    /**
     * @brief Actualiza la cámara según el modelo o grid actual.
     */
    void updateCameraToCurrentModel();

    /**
     * @brief Renderiza los modelos OBJ.
     */
    void renderModels();

    /**
     * @brief Renderiza las mallas (grids) matemáticas.
     */
    void renderGrids();

    void updateCameraToModel(const ImportedModel& model);
    void updateCameraToGrid(const Grid& grid);
};
