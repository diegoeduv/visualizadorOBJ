#include "Scene.h"

// ======================================================
// CONSTRUCTOR / DESTRUCTOR
// ======================================================

// Inicializa ventana, shaders, ejes y carga modelos/grids.
Scene::Scene()
    : window(SCR_WIDTH, SCR_HEIGHT, "Visualizador OpenGL"),
      shader("../shaders/height.vert", "../shaders/height.frag"),
      shaderAxes("../shaders/axis.vert", "../shaders/axis.frag"),
      shaderMovingAxes("../shaders/moving_axis.vert", "../shaders/moving_axis.frag")
{
    axes.uploadColored(Geometry::makeAxes(axesLength), GL_LINES);
    movingAxes.uploadColoredAlpha(Geometry::makeAxesAlpha(axesLength, alpha), GL_LINES);

    loadModels();
    loadGrids();
    updateCameraToCurrentModel();

    glEnable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

// Libera modelos, grids y ejes.
Scene::~Scene() {
    axes.destroy();
    movingAxes.destroy();
    for (auto& m : m_models) m.destroy();
    for (auto& g : m_grids) g.destroy();
}

// ======================================================
// HELPERS
// ======================================================

// Devuelve min/max en eje Y.
std::pair<float,float> Scene::computeMinMaxY(const std::vector<float>& verts) {
    float minY = verts[1], maxY = verts[1];
    for (size_t i = 1; i < verts.size(); i += 3) {
        minY = std::min(minY, verts[i]);
        maxY = std::max(maxY, verts[i]);
    }
    return {minY, maxY};
}

// Detecta una pulsación única.
bool Scene::keyPressedOnce(int key, bool& state) {
    if (glfwGetKey(window.handle, key) == GLFW_PRESS) {
        if (!state) {
            state = true;
            return true;
        }
    } else {
        state = false;
    }
    return false;
}

// Envia matrices al shader.
void Scene::applyShader(Shader& s) {
    s.setMat4("uModel", glm::scale(m_model, glm::vec3(modelScale)));
    s.setMat4("uView", m_view);
    s.setMat4("uProjection", m_projection);
}

// ======================================================
// LOADERS
// ======================================================

// Carga modelos OBJ predefinidos.
void Scene::loadModels() {
    std::vector<std::string> paths = {
        "../assets/obj/dragon.obj",
        "../assets/obj/bunny.obj",
        "../assets/obj/Teapot.obj",
        "../assets/obj/Cube_Triangles.obj"
    };

    for (const auto& path : paths) {
        ImportedModel model;
        model.loadFromOBJ(path.c_str());
        m_models.push_back(model);

        size_t pos = path.find_last_of('/');
        m_modelNames.push_back(path.substr(pos + 1));
    }

    printCurrentModelStats();
}

// Crea y carga grids configurados.
void Scene::loadGrids() {
    std::vector<std::vector<int>> cfg = {
        {100, 100, 1},
        {100, 100, 2}
    };

    for (auto& c : cfg) {
        Grid g(c[0], c[1], c[2]);
        g.initGeometry();
        m_grids.push_back(g);
        m_gridNames.push_back(g.m_name);
    }
}

// ======================================================
// STATS / CAMERA
// ======================================================

// Calcula límites XYZ del mesh.
Bounds Scene::computeBounds(const std::vector<float>& verts) {
    Bounds b;
    if (verts.empty()) return b;

    b.minP = glm::vec3(verts[0], verts[1], verts[2]);
    b.maxP = b.minP;

    for (size_t i = 0; i < verts.size(); i += 3) {
        b.minP.x = std::min(b.minP.x, verts[i]);
        b.minP.y = std::min(b.minP.y, verts[i + 1]);
        b.minP.z = std::min(b.minP.z, verts[i + 2]);

        b.maxP.x = std::max(b.maxP.x, verts[i]);
        b.maxP.y = std::max(b.maxP.y, verts[i + 1]);
        b.maxP.z = std::max(b.maxP.z, verts[i + 2]);
    }
    return b;
}

// Imprime stats del modelo/grid actual.
void Scene::printCurrentModelStats() {
    Bounds b;

    if (showingGrids) {
        auto& g = m_grids[m_currentGrid];
        b = computeBounds(g.getVertices());
        std::cout << "Grid: " << m_gridNames[m_currentGrid] << "\n";
        std::cout << "Vértices: " << g.getNumVertices() << "\n";
    } else {
        auto& m = m_models[m_currentModel];
        b = computeBounds(m.getVertices());
        std::cout << "Modelo: " << m_modelNames[m_currentModel] << "\n";
        std::cout << "Vértices: " << m.getNumVertices() << "\n";
    }

    std::cout << "X: [" << b.minP.x << ", " << b.maxP.x << "]\n";
    std::cout << "Y: [" << b.minP.y << ", " << b.maxP.y << "]\n";
    std::cout << "Z: [" << b.minP.z << ", " << b.maxP.z << "]\n\n";
}

// Ajusta cámara al modelo/grid actual.
void Scene::updateCameraToCurrentModel() {
    const auto& verts = showingGrids ?
        m_grids[m_currentGrid].getVertices()
        : m_models[m_currentModel].getVertices();

    Bounds b = computeBounds(verts);
    glm::vec3 center = (b.minP + b.maxP) * 0.5f;
    glm::vec3 size   = b.maxP - b.minP;
    float maxDim = std::max(size.x, std::max(size.y, size.z));
    float dist   = maxDim * 1.5f;

    glm::vec3 camPos = center + glm::vec3(dist, dist, dist);
    m_view = glm::lookAt(camPos, center, glm::vec3(0, 1, 0));

    float aspect = window.getAspectRatio();
    m_projection = glm::perspective(glm::radians(45.0f), aspect, 0.1f, maxDim * 10.0f);

    axesLength = dist * 1.6f;
    movingAxesLength = maxDim;

    axes.destroy();
    axes.uploadColored(Geometry::makeAxes(axesLength), GL_LINES);

    movingAxes.destroy();
    movingAxes.uploadColoredAlpha(Geometry::makeAxesAlpha(movingAxesLength, alpha), GL_LINES);
}

// ======================================================
// RENDER
// ======================================================

// Renderiza modelo/grid con shader y color por altura.
void Scene::render() {
    std::vector<float> verts = showingGrids ?
        m_grids[m_currentGrid].getVertices()
        : m_models[m_currentModel].getVertices();

    shader.use();
    applyShader(shader);

    auto [minY, maxY] = computeMinMaxY(verts);
    glUniform1f(glGetUniformLocation(shader.id(), "uMinY"), minY);
    glUniform1f(glGetUniformLocation(shader.id(), "uMaxY"), maxY);

    if (showingGrids)
        m_grids[m_currentGrid].draw();
    else
        m_models[m_currentModel].draw();
}

// Limpia la pantalla con el color indicado (Fondo) y borra color + profundidad.
void Scene::clear(float r, float g, float b, float a) {
    glClearColor(r, g, b, a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}


// ======================================================
// INPUT HANDLER
// ======================================================

// Rotaciones básicas y ESC.
void Scene::pollRotation() {
    const float rot = glm::radians(1.0f);
    if (glfwGetKey(window.handle, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window.handle, 1);
    if (glfwGetKey(window.handle, GLFW_KEY_X) == GLFW_PRESS)
        m_model = glm::rotate(m_model, rot, glm::vec3(1, 0, 0));
    if (glfwGetKey(window.handle, GLFW_KEY_Y) == GLFW_PRESS)
        m_model = glm::rotate(m_model, rot, glm::vec3(0, 1, 0));
    if (glfwGetKey(window.handle, GLFW_KEY_Z) == GLFW_PRESS)
        m_model = glm::rotate(m_model, rot, glm::vec3(0, 0, 1));
}

// Cambiar modelos/grids y navegación.
void Scene::pollModelSwitching() {
    static bool gState=false, nState=false, pState=false;

    if (keyPressedOnce(GLFW_KEY_G, gState)) {
        showingGrids = !showingGrids;
        updateCameraToCurrentModel();
        m_model = glm::mat4(1.0f);
        printCurrentModelStats();
    }

    if (keyPressedOnce(GLFW_KEY_N, nState)) {
        if (showingGrids)
            m_currentGrid = (m_currentGrid + 1) % m_grids.size();
        else
            m_currentModel = (m_currentModel + 1) % m_models.size();
        updateCameraToCurrentModel();
        m_model = glm::mat4(1.0f);
        printCurrentModelStats();
    }

    if (keyPressedOnce(GLFW_KEY_P, pState)) {
        if (showingGrids)
            m_currentGrid = (m_currentGrid - 1 + m_grids.size()) % m_grids.size();
        else
            m_currentModel = (m_currentModel - 1 + m_models.size()) % m_models.size();
        updateCameraToCurrentModel();
        m_model = glm::mat4(1.0f);
        printCurrentModelStats();
    }
}

// Cambia modo de render (1,2,3).
void Scene::pollRenderModeKeys() {
    if (glfwGetKey(window.handle, GLFW_KEY_1) == GLFW_PRESS) {
        if (showingGrids)
            m_grids[m_currentGrid].setMode(GL_POINTS);
        else
            m_models[m_currentModel].setMode(GL_POINTS);
    }

    if (glfwGetKey(window.handle, GLFW_KEY_2) == GLFW_PRESS) {
        if (showingGrids)
            m_grids[m_currentGrid].setMode(GL_LINES);
        else
            m_models[m_currentModel].setMode(GL_LINES);
    }

    if (glfwGetKey(window.handle, GLFW_KEY_3) == GLFW_PRESS) {
        if (showingGrids)
            m_grids[m_currentGrid].setMode(GL_TRIANGLES);
        else
            m_models[m_currentModel].setMode(GL_TRIANGLES);
    }
}

// Zoom básico.
void Scene::pollZoom() {
    if (glfwGetKey(window.handle, GLFW_KEY_F1) == GLFW_PRESS)
        modelScale += zoomStep;

    if (glfwGetKey(window.handle, GLFW_KEY_F2) == GLFW_PRESS) {
        modelScale -= zoomStep;
        if (modelScale < 0.05f) modelScale = 0.05f;
    }
}

// Alternar ejes.
void Scene::pollAxesToggles() {
    static bool hState=false, jState=false;

    if (keyPressedOnce(GLFW_KEY_H, hState))
        axesVisible = !axesVisible;

    if (keyPressedOnce(GLFW_KEY_J, jState))
        movingAxesVisible = !movingAxesVisible;
}

// ======================================================
// RUN LOOP
// ======================================================

// Loop principal: input, ejes, render y swap.
void Scene::run() {
    while (!window.shouldClose()) {

        pollRotation();
        pollModelSwitching();
        pollRenderModeKeys();
        pollZoom();
        pollAxesToggles();

        clear(0.12f, 0.13f, 0.15f, 1.0f);

        if (axesVisible) {
            shaderAxes.use();
            shaderAxes.setMat4("uView", m_view);
            shaderAxes.setMat4("uProjection", m_projection);
            axes.draw();
        }

        if (movingAxesVisible) {
            shaderMovingAxes.use();
            applyShader(shaderMovingAxes);
            movingAxes.draw();
        }

        render();

        window.swap();
        window.poll();
    }
}
