#include "Scene.h"
#include <iostream>

Scene::Scene()
    : window(SCR_WIDTH, SCR_HEIGHT, "Visualizador OpenGL"),
      shader("../shaders/height.vert", "../shaders/height.frag"),
      shaderAxes("../shaders/axis.vert", "../shaders/axis.frag")
{
    axes.uploadColored(Geometry::makeAxes(), GL_LINES);

    loadModels();
    loadGrids();

    updateCameraToCurrentModel();

    glEnable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);
}

Scene::~Scene() {
    axes.destroy();
    for (auto& m : m_models) m.destroy();
    for (auto& g : m_grids) g.destroy();
}

// ----------------------------------------------------------
// Carga los modelos .OBJ
// ----------------------------------------------------------
void Scene::loadModels() {
    std::vector<std::string> paths = {
        "../assets/obj/dragon.obj",
        "../assets/obj/bunny.obj",
        "../assets/obj/Teapot.obj"
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

// ----------------------------------------------------------
// Crea las grids de funciones matemáticas
// ----------------------------------------------------------
void Scene::loadGrids() {
    std::vector<std::vector<int>> gridConf = {
        {100, 100, 1},
        {100, 100, 2}
    };

    for (const auto& conf : gridConf) {
        int width = conf[0];
        int depth = conf[1];
        int funcType = conf[2];

        Grid grid(width, depth, funcType);
        grid.CreateTriangleList();
        m_grids.push_back(grid);
    }
}

// ----------------------------------------------------------
// Imprime estadísticas del modelo actual
// ----------------------------------------------------------
void Scene::printCurrentModelStats() {
    if (showingGrids) {
        std::cout << "Grid actual: " << m_currentGrid + 1 << " / " << m_grids.size() << "\n";
        std::cout << "Función: f" << m_grids[m_currentGrid].m_funcType << "\n";
    } else {
        const auto& name = m_modelNames[m_currentModel];
        auto verts = m_models[m_currentModel].getVertices();
        if (verts.empty()) return;

        glm::vec3 minP(verts[0], verts[1], verts[2]);
        glm::vec3 maxP = minP;

        for (size_t i = 0; i < verts.size(); i += 3) {
            minP.x = std::min(minP.x, verts[i]);
            minP.y = std::min(minP.y, verts[i + 1]);
            minP.z = std::min(minP.z, verts[i + 2]);
            maxP.x = std::max(maxP.x, verts[i]);
            maxP.y = std::max(maxP.y, verts[i + 1]);
            maxP.z = std::max(maxP.z, verts[i + 2]);
        }

        std::cout << "Modelo: " << name << '\n';
        std::cout << "Vértices: " << m_models[m_currentModel].getNumVertices() << '\n';
        std::cout << "X: [" << minP.x << ", " << maxP.x << "]\n";
        std::cout << "Y: [" << minP.y << ", " << maxP.y << "]\n";
        std::cout << "Z: [" << minP.z << ", " << maxP.z << "]\n\n";
    }
}

// ----------------------------------------------------------
// Actualiza la cámara para el modelo actual
// ----------------------------------------------------------
void Scene::updateCameraToCurrentModel() {
    if (showingGrids) {
        updateCameraToGrid(m_grids[m_currentGrid]);
    } else {
        updateCameraToModel(m_models[m_currentModel]);
    }
}

void Scene::updateCameraToModel(const ImportedModel& model) {
    auto verts = model.getVertices();
    if (verts.empty()) return;

    glm::vec3 minP(verts[0], verts[1], verts[2]);
    glm::vec3 maxP = minP;

    for (size_t i = 0; i < verts.size(); i += 3) {
        minP.x = std::min(minP.x, verts[i]);
        minP.y = std::min(minP.y, verts[i + 1]);
        minP.z = std::min(minP.z, verts[i + 2]);
        maxP.x = std::max(maxP.x, verts[i]);
        maxP.y = std::max(maxP.y, verts[i + 1]);
        maxP.z = std::max(maxP.z, verts[i + 2]);
    }

    glm::vec3 center = (minP + maxP) * 0.5f;
    glm::vec3 size   = maxP - minP;
    float maxDim = std::max(std::max(size.x, size.y), size.z);
    float distance = maxDim * 1.5f;

    glm::vec3 cameraPos = center + glm::vec3(distance, distance, distance);
    m_view = glm::lookAt(cameraPos, center, glm::vec3(0, 1, 0));

    float aspect = window.getAspectRatio();
    m_projection = glm::perspective(glm::radians(45.0f), aspect, 0.1f, maxDim * 10.0f);
}


void Scene::updateCameraToGrid(const Grid& grid) {
    auto verts = grid.getVertices();
    if (verts.empty()) return;

    glm::vec3 minP(verts[0], verts[1], verts[2]);
    glm::vec3 maxP = minP;

    for (size_t i = 0; i < verts.size(); i += 3) {
        minP.x = std::min(minP.x, verts[i]);
        minP.y = std::min(minP.y, verts[i + 1]);
        minP.z = std::min(minP.z, verts[i + 2]);
        maxP.x = std::max(maxP.x, verts[i]);
        maxP.y = std::max(maxP.y, verts[i + 1]);
        maxP.z = std::max(maxP.z, verts[i + 2]);
    }

    glm::vec3 center = (minP + maxP) * 0.5f;
    glm::vec3 size   = maxP - minP;
    float maxDim = std::max(std::max(size.x, size.y), size.z);
    float distance = maxDim * 2.0f; // un poco más lejos para grids grandes

    glm::vec3 cameraPos = center + glm::vec3(distance, distance * 0.8f, distance);
    m_view = glm::lookAt(cameraPos, center, glm::vec3(0, 1, 0));

    float aspect = window.getAspectRatio();
    m_projection = glm::perspective(glm::radians(45.0f), aspect, 0.1f, maxDim * 10.0f);
}


// ----------------------------------------------------------
// Render de modelos .OBJ
// ----------------------------------------------------------
void Scene::renderModels() {
    auto& model = m_models[m_currentModel];
    shader.use();
    shader.setMat4("uModel", m_model);
    shader.setMat4("uView", m_view);
    shader.setMat4("uProjection", m_projection);

    auto verts = model.getVertices();
    float minY = verts[1], maxY = verts[1];
    for (size_t i = 1; i < verts.size(); i += 3) {
        minY = std::min(minY, verts[i]);
        maxY = std::max(maxY, verts[i]);
    }

    glUniform1f(glGetUniformLocation(shader.id(), "uMinY"), minY);
    glUniform1f(glGetUniformLocation(shader.id(), "uMaxY"), maxY);
    model.draw();
}

// ----------------------------------------------------------
// Render de grids
// ----------------------------------------------------------
void Scene::renderGrids() {
    auto& grid = m_grids[m_currentGrid];
    shader.use();
    shader.setMat4("uModel", m_model);
    shader.setMat4("uView", m_view);
    shader.setMat4("uProjection", m_projection);

    // Colores por altura
    std::vector<float> verts = grid.getVertices();
    float minY = verts[1], maxY = verts[1];
    for (size_t i = 1; i < verts.size(); i += 3) {
        minY = std::min(minY, verts[i]);
        maxY = std::max(maxY, verts[i]);
    }

    glUniform1f(glGetUniformLocation(shader.id(), "uMinY"), minY);
    glUniform1f(glGetUniformLocation(shader.id(), "uMaxY"), maxY);
    grid.draw();
}

// ----------------------------------------------------------
// Bucle principal
// ----------------------------------------------------------
void Scene::run() {
        // -----------------------------
    // Control de cámara orbital
    // -----------------------------
    // Variables de cámara orbital (antes del while)
    float radius = 120.0f;   // distancia inicial
    float angleY = glm::radians(45.0f); // vista diagonal
    float angleX = glm::radians(20.0f); // vista desde arriba


    while (!window.shouldClose()) {
        if (glfwGetKey(window.handle, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window.handle, 1);

        const float rotationSpeed = glm::radians(1.0f);
        if (glfwGetKey(window.handle, GLFW_KEY_X) == GLFW_PRESS)
            m_model = glm::rotate(m_model, rotationSpeed, glm::vec3(1, 0, 0));
        if (glfwGetKey(window.handle, GLFW_KEY_Y) == GLFW_PRESS)
            m_model = glm::rotate(m_model, rotationSpeed, glm::vec3(0, 1, 0));
        if (glfwGetKey(window.handle, GLFW_KEY_Z) == GLFW_PRESS)
            m_model = glm::rotate(m_model, rotationSpeed, glm::vec3(0, 0, 1));

        // Cambiar entre OBJ y Grid
        static bool gPressed = false;
        if (glfwGetKey(window.handle, GLFW_KEY_G) == GLFW_PRESS && !gPressed) {
            showingGrids = !showingGrids;
            updateCameraToCurrentModel();
            m_model = glm::mat4(1.0f);
            std::cout << (showingGrids ? "Modo GRID\n" : "Modo MODELOS\n");
            printCurrentModelStats();
            gPressed = true;
        }
        if (glfwGetKey(window.handle, GLFW_KEY_G) == GLFW_RELEASE) gPressed = false;

        // Cambio de modelo / grid (N / P)
        static bool nPressed = false, pPressed = false;
        if (glfwGetKey(window.handle, GLFW_KEY_N) == GLFW_PRESS && !nPressed) {
            nPressed = true;
            if (!showingGrids)
                m_currentModel = (m_currentModel + 1) % m_models.size();
            else
                m_currentGrid = (m_currentGrid + 1) % m_grids.size();
            updateCameraToCurrentModel();
            m_model = glm::mat4(1.0f);
            printCurrentModelStats();
        }
        if (glfwGetKey(window.handle, GLFW_KEY_N) == GLFW_RELEASE) nPressed = false;

        if (glfwGetKey(window.handle, GLFW_KEY_P) == GLFW_PRESS && !pPressed) {
            pPressed = true;
            if (!showingGrids)
                m_currentModel = (m_currentModel - 1 + m_models.size()) % m_models.size();
            else
                m_currentGrid = (m_currentGrid - 1 + m_grids.size()) % m_grids.size();
            updateCameraToCurrentModel();
            m_model = glm::mat4(1.0f);
            printCurrentModelStats();
        }
        if (glfwGetKey(window.handle, GLFW_KEY_P) == GLFW_RELEASE) pPressed = false;

                // --- Cambio de modo de renderizado (1, 2, 3) ---
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

        // -----------------------------
        // Control de cámara orbital
        // -----------------------------

        // --- Rotación con flechas ---
        if (glfwGetKey(window.handle, GLFW_KEY_LEFT) == GLFW_PRESS)
            angleY -= 0.02f;
        if (glfwGetKey(window.handle, GLFW_KEY_RIGHT) == GLFW_PRESS)
            angleY += 0.02f;
        if (glfwGetKey(window.handle, GLFW_KEY_UP) == GLFW_PRESS)
            angleX += 0.02f;
        if (glfwGetKey(window.handle, GLFW_KEY_DOWN) == GLFW_PRESS)
            angleX -= 0.02f;

        // Limita el ángulo vertical para no voltear la cámara
        angleX = glm::clamp(angleX, -1.2f, 1.2f);

        // --- Zoom con + y - ---
        if (glfwGetKey(window.handle, GLFW_KEY_KP_ADD) == GLFW_PRESS || glfwGetKey(window.handle, GLFW_KEY_EQUAL) == GLFW_PRESS)
            radius -= 2.0f;
        if (glfwGetKey(window.handle, GLFW_KEY_KP_SUBTRACT) == GLFW_PRESS || glfwGetKey(window.handle, GLFW_KEY_MINUS) == GLFW_PRESS)
            radius += 2.0f;

        radius = glm::clamp(radius, 10.0f, 500.0f); // evita zoom extremo

        // --- Cálculo de posición orbital ---
        float camX = radius * cos(angleX) * sin(angleY);
        float camY = radius * sin(angleX);
        float camZ = radius * cos(angleX) * cos(angleY);

        // --- Define el punto de enfoque (centro del modelo o grid) ---
        glm::vec3 target(0.0f, 0.0f, 0.0f);
        if (showingGrids && !m_grids.empty()) {
            auto verts = m_grids[m_currentGrid].getVertices();
            if (!verts.empty()) {
                glm::vec3 minP(verts[0], verts[1], verts[2]);
                glm::vec3 maxP = minP;
                for (size_t i = 0; i < verts.size(); i += 3) {
                    minP.x = std::min(minP.x, verts[i]);
                    minP.y = std::min(minP.y, verts[i + 1]);
                    minP.z = std::min(minP.z, verts[i + 2]);
                    maxP.x = std::max(maxP.x, verts[i]);
                    maxP.y = std::max(maxP.y, verts[i + 1]);
                    maxP.z = std::max(maxP.z, verts[i + 2]);
                }
                target = (minP + maxP) * 0.5f;
            }
        }

        // --- Actualiza la vista ---
        glm::vec3 cameraPos = glm::vec3(camX, camY, camZ);
        glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
        m_view = glm::lookAt(cameraPos, target, up);



        // --- Render ---
        Renderer::clear(0.12f, 0.13f, 0.15f, 1.0f);
        shaderAxes.use();
        shaderAxes.setMat4("uModel", glm::mat4(1.0f));      // los ejes están en el origen
        shaderAxes.setMat4("uView", m_view);                // usa la misma vista
        shaderAxes.setMat4("uProjection", m_projection);    // misma proyección
        axes.draw();


        if (showingGrids)
            renderGrids();
        else
            renderModels();

        window.swap();
        window.poll();
    }
}
